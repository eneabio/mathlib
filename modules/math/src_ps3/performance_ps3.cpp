// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#if defined(FDK_OS_PS3)

#include "fdk/performance.h"

FDK_NS_BEGIN

U64   Start() {
	return 0;
}
U64   Stop() {
	return 0;
}
F64   ExecutionTime  (U64 start, U64 stop) {
	(void)start;
	(void)stop;
	return 0;
}

FDK_NS_END

#endif
