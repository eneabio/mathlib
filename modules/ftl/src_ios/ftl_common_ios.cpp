#ifdef FDK_OS_IOS

#include "fdk/ftl_common.h"
#include <sys/types.h>
#include <sys/sysctl.h>
#include <mach/mach_time.h>

FDK_NS_BEGIN

void PerformanceTimer::init() {
	this->mFrequency = getFrequency();
	this->mStartTick = mach_absolute_time();
}

F64 PerformanceTimer::tick()  {
	uint64_t prov = mach_absolute_time();
	F64 res = prov - this->mStartTick;
	this->mStartTick = prov;
	static F64 conversion = 0.0;
	if( conversion == 0.0 )
	{
		mach_timebase_info_data_t info;
		kern_return_t err = mach_timebase_info( &info );
		
		//Convert the timebase into milliseconds
		if( err == 0  )
			conversion = 1e-6 * (F64) info.numer / (F64) info.denom;
	}
	return conversion * (F64) res;
}

U64 PerformanceTimer::tickCount() {
	return mach_absolute_time() - this->mStartTick;
}

U64 PerformanceTimer::getFrequency() const {
	uint64_t freq = 0;
	size_t size = sizeof(freq);
	if (sysctlbyname("hw.cpufrequency", &freq, &size, NULL, 0) < 0)
	{
		perror("sysctl");
	}
	return freq;
}

FDK_NS_END

#endif