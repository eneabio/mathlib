#ifdef FDK_OS_WIN

#include "fdk/ftl_common.h"

FDK_NS_BEGIN

void PerformanceTimer::init() {
	LARGE_INTEGER outFreq;
	BOOL status = QueryPerformanceFrequency(&outFreq);
	FDK_ASSERT( status != 0 );
	this->mFrequency = outFreq.QuadPart;
	this->mStartTick = tickCount();
}

F64 PerformanceTimer::tick()  {
	LARGE_INTEGER curr;
	BOOL status = QueryPerformanceCounter( &curr );
	FDK_ASSERT( status != 0 );
	double res =  double(curr.QuadPart - this->mStartTick) * 1000 / this->mFrequency;
	this->mStartTick = curr.QuadPart;
	return res;
}

U64 PerformanceTimer::tickCount() {
	LARGE_INTEGER outTick;
	BOOL status = QueryPerformanceCounter(&outTick);
	FDK_ASSERT( status != 0 );
	I64 val = outTick.QuadPart - this->mStartTick;
	this->mStartTick = outTick.QuadPart;
	return val;
}

U64 PerformanceTimer::getFrequency() const {
	return this->mFrequency;
}

FDK_NS_END

#endif
