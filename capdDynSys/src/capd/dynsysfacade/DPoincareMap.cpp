/// @addtogroup facade
/// @{

/////////////////////////////////////////////////////////////////////////////
/// @file DPoincareMap.cpp
///
/// @author Daniel Wilczak
/////////////////////////////////////////////////////////////////////////////

// Copyright (C) 2000-2005 by the CAPD Group.
//
// This file constitutes a part of the CAPD library, 
// distributed under the terms of the GNU General Public License.
// Consult  http://capd.wsb-nlu.edu.pl/ for details. 


#include "capd/facade/DMap.h"
#include "capd/facade/DTaylor.h"
#include "capd/poincare/BasicPoincareMap.hpp"

template class capd::poincare::BasicPoincareMap<capd::facade::DTaylor>;

/// @}
