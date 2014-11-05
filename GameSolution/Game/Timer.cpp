#include "Timer.h"

double Timer::LIToSecs(LARGE_INTEGER& L)
{
	return ((double)L.QuadPart/(double)frequency.QuadPart);
};

void Timer::Start()
{
	QueryPerformanceCounter(&timer.start);
};

void Timer::Stop()
{
	QueryPerformanceCounter(&timer.stop);
};

float Timer::Interval()
{
	LARGE_INTEGER time;
	time.QuadPart=timer.stop.QuadPart-timer.start.QuadPart;
	return (float)LIToSecs(time);
};