#ifndef FDK_VERSION_H
#define FDK_VERSION_H

#include "fdk/base_defs.h"
#include "fdk/forge_defs.h"

FDK_NS_BEGIN

struct ForgeVersion {
	int mayor;
	int minor;
	int build;
	int __pad;
};

FDK_FORGE_API  void VersionGet(ForgeVersion* outVersion);

FDK_NS_END

#endif
