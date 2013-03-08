// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies). 
// See Licence.txt 

#ifndef __FDK_RANDOM_H__
#define __FDK_RANDOM_H__

#include "fdk/ftl_defs.h"

namespace fdk {

	void RandIntSetSeed(unsigned int seed);
	int  RandInt();

}

#include "fdk/random_inl.h"

#endif