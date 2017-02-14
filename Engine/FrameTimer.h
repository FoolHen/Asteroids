#pragma once
#include <chrono>

class FrameTimer
{
public:
	FrameTimer();
	float Mark();
	bool HasTimePassed(float milis);
private:
	std::chrono::steady_clock::time_point last;
};