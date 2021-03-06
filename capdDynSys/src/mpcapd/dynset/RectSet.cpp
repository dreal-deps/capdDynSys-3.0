


/////////////////////////////////////////////////////////////////////////////
/// @file RectSet.cpp
///
/// @author The CAPD Group
/////////////////////////////////////////////////////////////////////////////

// Copyright (C) 2000-2005 by the CAPD Group.
//
// This file constitutes a part of the CAPD library, 
// distributed under the terms of the GNU General Public License.
// Consult  http://capd.wsb-nlu.edu.pl/ for details. 

#include "capd/vectalg/mplib.h"
#include "capd/dynset/RectSet.hpp"

#ifdef __HAVE_MPFR__
  template class capd::dynset::RectSet<capd::MpIMatrix >;
#endif


