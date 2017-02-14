#include "FrameTimer.h"

using namespace std::chrono;

FrameTimer::FrameTimer()
{
	last = steady_clock::now();
}

float FrameTimer::Mark()
{
	const auto old = last;
	last = steady_clock::now();
	const duration<float> frameTime = last - old;
	return frameTime.count();
}

bool FrameTimer::HasTimePassed( float ms)
{
	const duration<float> frameTime = steady_clock::now() - last;
	return (ms < frameTime.count());
}
