#include <iostream>
#include "capd/capdlib.h"
#include "capd/poincare/PoincareMapJet.h"
using namespace capd;
using namespace std;
// The following example is a complete proof of the existence of 3 different
// periodic solution for the Rossler system
// with chaotic parameter values a=5.7, b=0.2
// First we define a class for easy computation of Poincare map and its derivative
class RosslerPoincareMap
{
public:
  typedef capd::poincare::PoincareMapJet<ITaylor> PoincareMap;
  IFunction section;
  IMap vectorField;
  ITaylor solver;
  PoincareMap pm;
  RosslerPoincareMap (int order, interval _a, interval _b)
    : section("var:x,y,z;fun:x;"), //  the section is x=0
      vectorField("par:a,b;var:x,y,z;fun:-(y+z),x+b*y,b+z*(x-a);"), // here is the vector field
      solver(vectorField,order,0.1), // 0.1 is the time step, ignored since step control is turned on by default
      pm(solver,section,poincare::MinusPlus)  // MinusPlus means that the section is crossed with 'x' changing sign from minus to plus
                                    // Other acceptable values are PlusMinus and None. The last means both directions are acceptable.
  {
    // set parameter values a and b
    vectorField.setParameter("a",_a);
    vectorField.setParameter("b",_b);
  }
  // this operator computes period-iteration of Poincare map
  IVector operator()(const IVector& u, int period)
  {
    // u is assumed to be on the section
    // so it is 2-dim, represented by coordinates (y,z).
    // We simply add 0 as the first coordinate i.e. we embed the vector
    // into the full 3d-space
    IVector x(3);
    x[0] = 0.;
    x[1] = u[0];
    x[2] = u[1];
    // we define a doubleton representation of the set
    C0Rect2Set s(x);
    for(int i=0;i<period;++i) // and compute period-iterations
      x = pm(s);
    // here we project the image 'x' onto 2-dimensional section
    return IVector(2,x.begin()+1);
    // If you do not understand what is above, just forget and simply do:
    // IVector result(2);
    // result[0] = x[1];
    // result[1] = x[2];
    // return result;
    // What is above is faster and shorter.
  }
  // This operator computes derivative of the Poincare map.
  IMatrix dx(const IVector& u, int period)
  {
    // Again u is two dimensional, so embed it.
    IVector x(3);
    x[0] = 0.;
    x[1] = u[0];
    x[2] = u[1];

    // for computing of derivative of PM we need an instance of logarithmic norm
    IEuclLNorm N;

    // We define a doubleton representation of the set and its derivative
    // constructor sets initial condition for variational equation to Identity
    C1Rect2Set s(x,N);

    // the matrix monodromyMatrix will store derivatives of the FLOW not Poincare map
    IMatrix monodromyMatrix(3,3);
    for(int i=0;i<period;++i)
      x = pm(s,monodromyMatrix);

    // This member function recomputes derivatives of the flow into derivatives of Poincare map
    IMatrix DP = pm.computeDP(x,monodromyMatrix);

    // as before, we extract from 3x3 matrix a 2x2 slice
    IMatrix result(2,2);
    result(1,1) = DP(2,2);
    result(1,2) = DP(2,3);
    result(2,1) = DP(3,2);
    result(2,2) = DP(3,3);
    // and return it
    return result;
  }

};

// ---------------------------------------------------------------------
// The following function computes the Interval Newton Operator for the Poincare map on a given set
// and verifies existence and uniqueness of a periodic point in a given set X.
// parameters are:
// pm - an instance of RosslerPoincareMap
// center - a very good approximation of a periodic point on section, center is assume dto be 2-dimensional
// X - interval vector in which we want to prove the existence of an unique periodic point.
// period - is a period of the point for the Poincare map
void verifyExistenceOfPeriodicOrbit(RosslerPoincareMap& pm, IVector center, IVector X, int period, int order)
{
  // using previously defined class RosslerPoincareMap we compute
  // Poincare Map at the center
  IVector imCenter = pm(center,period);

  // derivative of PM on the set X,
  IMatrix DP = pm.dx(X,period);

  // and well known interval Newton operator
  IVector N = center - capd::matrixAlgorithms::gauss(DP-IMatrix::Identity(2),imCenter-center);

  // Verification if N is a subset of X
  cout << "\n---------------------------------------------------\n\nN = " << N << "\n";
  cout << "X = " << X << "\n";
  if(subsetInterior(N,X))
    cout << "the existence of period " << period << " orbit verified\n" << endl;
  else
  {
    cout << "N is not a subset of X\n" << endl;
    cout << "diam(N)=" << diam(N) << endl;
    cout << "diam(X)=" << diam(X) << endl;
    cout << "N-X" << N-X << endl;
  }
}

// ----------------------------------- MAIN ----------------------------------------

int main(int argc, char* argv[])
{
  cout.precision(15);
  try{
    // Define an instance of RosslerPoincareMap with chaotic parameter values
    int order = 35;
    interval a = interval(57.)/10;
    interval b = interval(2.)/10;
    RosslerPoincareMap pm(order,a,b);

    IVector center(2), X(2);
// For all the orbits below the size of set in which we verify the existence of an unique orbit is set to 7e-13 (up to the rounding:)
    X[0] = X[1] = 3.5e-13*interval(-1,1);

// fixed point
    center[0] = -8.3809417428298;
    center[1] = 0.029590060630665;
    verifyExistenceOfPeriodicOrbit(pm,center,center+X,1,order);

// period 2 orbit
    center[0] = -5.4240738226652;
    center[1] = 0.031081210807875;
    verifyExistenceOfPeriodicOrbit(pm,center,center+X,2,order);

// period 3 orbit
    center[0] = -6.233158628537965;
    center[1] = 0.03064011165815;
    verifyExistenceOfPeriodicOrbit(pm,center,center+X,3,order);

   }catch(exception& e)
  {
    cout << "\n\nException caught: "<< e.what() << endl;
  }
  return 0;
} // END
