#ifndef TIM
#define TIME

#include <window.h>

typedef struct
{
	LARGE_INTEGER start;
	LARGE_INTEGER stop;
} stopWatch;

class Timer
{
private:
	stopWatch timer;
	LARGE_INTEGER frequency;
	double LIToSecs(LARGE_INTEGER& L);
public:
	Timer()
	{
		timer.start.QuadPart=0;
		timer.stop.QuadPart=0;
		QueryPerformanceFrequency(&frequency);
	};
	void Start();
	void Stop();
	float Interval();
};

#endif