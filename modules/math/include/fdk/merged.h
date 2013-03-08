// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#ifndef __FDK_MERGED_H__
#define __FDK_MERGED_H__

#include "fdk/base_defs.h"
#include "fdk/forge_defs.h"
#include "fdk/geometryd.h"
#include "fdk/mathd.h"

FDK_NS_BEGIN

void MergeAABBAABB3d (const AABB3d& FDK_RESTRICT a, const AABB3d& FDK_RESTRICT b, AABB3d* FDK_RESTRICT outBox);
void MergeAABBAABB2d (const AABB2d& FDK_RESTRICT a, const AABB2d& FDK_RESTRICT b, AABB2d* FDK_RESTRICT outBox);

void MergeSpheredSphered3d (const Sphered& FDK_RESTRICT a, const Sphered& FDK_RESTRICT b, Sphered* FDK_RESTRICT outSphered);

FDK_NS_END

#endif
