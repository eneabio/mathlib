// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#ifndef __FDK_RANDOM_MATH_H__
#define __FDK_RANDOM_MATH_H__

#include "fdk/base_defs.h"
#include "fdk/forge_defs.h"
#include "fdk/random.h"
#include "fdk/vec2f.h"
#include "fdk/vec3f.h"
#include "fdk/vec2d.h"
#include "fdk/vec3d.h"
#include "fdk/mathf.h"
#include "fdk/mathd.h"
#include <time.h>

FDK_NS_BEGIN

// ::::: FLOAT :::::

//reference:  Urho3D Engine
// Return a random float between 0.0 (inclusive) and 1.0 (exclusive.)
FDK_FORGE_API F32 Randomf();

// Return a random float between 0.0 and range, inclusive.
FDK_FORGE_API F32 Randomf(const F32 range);

// Return a random integer between 0 and range, inclusive.
FDK_FORGE_API I32 Randomf(const I32 range);

//reference: OpenGL Mathematics (glm.g-truc.net)

// Generate random numbers in the interval [Min, Max], according a linear distribution
FDK_FORGE_API F32   LinearRandf      (F32 const & min, F32 const & max);

// Generate random numbers in the interval [Min, Max], according a gaussian distribution
FDK_FORGE_API F32   GaussRandf       (F32 const & mean, F32 const & deviation);

// Generate a random 2D vector which coordinates are regulary distributed on a circle of a given radius
FDK_FORGE_API void CircularRandf  (F32 const & radius, Vec2f* outVec);

// Generate a random 3D vector which coordinates are regulary distributed on a sphere of a given radius
FDK_FORGE_API void SphericalRandf (F32 const & radius, Vec3f* outVec);

// ::::: DOUBLE :::::

//reference:  Urho3D Engine
// Return a random double between 0.0 (inclusive) and 1.0 (exclusive.)
FDK_FORGE_API F64 Randomd();

// Return a random double between 0.0 and range, inclusive.
FDK_FORGE_API F64 Randomd(const F64 range);

// Return a random integer between 0 and range, inclusive.
FDK_FORGE_API I64 Randomd(const I64 range);

//reference: OpenGL Mathematics (glm.g-truc.net)

// Generate random numbers in the interval [Min, Max], according a linear distribution
FDK_FORGE_API F64   LinearRandd    (F64 const & min, F64 const & max);

// Generate random numbers in the interval [Min, Max], according a gaussian distribution
FDK_FORGE_API F64   GaussRandd     (F64 const & mean, F64 const & deviation);

// Generate a random 2D vector which coordinates are regulary distributed on a circle of a given radius
FDK_FORGE_API void CircularRandd  (F64 const & radius, Vec2d* outVec);

// Generate a random 3D vector which coordinates are regulary distributed on a sphere of a given radius
FDK_FORGE_API void SphericalRandd (F64 const & radius, Vec3d* outVec);


FDK_NS_END

#include "fdk/random_math_inl.h"

#endif
