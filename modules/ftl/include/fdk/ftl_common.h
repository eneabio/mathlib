#ifndef __FDK_FLT_COMMON_H__
#define __FDK_FLT_COMMON_H__

#include "fdk/base_defs.h"

FDK_NS_BEGIN

U32 NextPow2(U32 val);
U32 ToPow2(U32 val);
/*
Example:
int main() {
	PerformanceTimer t;
	t.init();

	// Single call
	t.tick();
	doLongRunningRoutine();
	U32 time = tick();


	// Loop Call Without hasMoreJobs() cont
	while (hasMoreJobs()) {
		Job j = getJob();	
		t.tick();
		ExecuteJob(j);
		U32 timeMillSec = t.tick();
		PushResult(timeMillSec);
	}


	// Loop Call Without hasMoreJobs() cont
	t.tick();
	while (hasMoreJobs()) {
		ExecuteJob(j);
		U32 timeMillSec = t.tick();
		PushResult(timeMillSec);
	}


	return 0;
}


*/

struct PerformanceTimer {
	
	void init(); // initializzazione + tick
	
	// # of millis since last tick()
	F64  tick() ;
	// # of processor clocks since last tick()
	U64  tickCount() ;
	// # processor freq
	U64  getFrequency() const;

private:	
	U64 mFrequency;
	U64 mStartTick;
};
	
FDK_NS_END

#include "fdk/ftl_common_inl.h"

#endif

