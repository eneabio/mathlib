//#define FDK_FORGE_EXPORTS
#include "fdk/version.h"

FDK_NS_BEGIN

void VersionGet(ForgeVersion* outVersion) {
	outVersion->mayor = 0;
	outVersion->minor = 5;
	outVersion->build = 100;
}

FDK_NS_END
