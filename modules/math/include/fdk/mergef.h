// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#ifndef __FDK_MERGEF_H__
#define __FDK_MERGEF_H__

#include "fdk/base_defs.h"
#include "fdk/forge_defs.h"
#include "fdk/geometryf.h"
#include "fdk/mathf.h"

FDK_NS_BEGIN

void MergeAABBAABB3f (const AABB3f& FDK_RESTRICT a, const AABB3f& FDK_RESTRICT b, AABB3f* FDK_RESTRICT outBox);
void MergeAABBAABB2f (const AABB2f& FDK_RESTRICT a, const AABB2f& FDK_RESTRICT b, AABB2f* FDK_RESTRICT outBox);

void MergeSpherefSpheref3f (const Spheref& FDK_RESTRICT a, const Spheref& FDK_RESTRICT b, Spheref* FDK_RESTRICT outSpheref);

FDK_NS_END

#endif