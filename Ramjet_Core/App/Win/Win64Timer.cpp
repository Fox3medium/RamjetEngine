#include <CoreBasicInclude.h>
#include <Utils/Timer.h>
#include <Windows.h>

namespace Utils 
{
	static LARGE_INTEGER s_Start;
	static double s_Frequency;

	Timer::Timer()
	{
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		s_Frequency = 1.0 / frequency.QuadPart;

		reset();
	}

	void Timer::reset()
	{
		QueryPerformanceCounter(&s_Start);
	}

	float Timer::elapsed()
	{
		LARGE_INTEGER current;
		QueryPerformanceCounter(&current);
		unsigned __int64 cycles = current.QuadPart - s_Start.QuadPart;
		return (float)(cycles * s_Frequency);
	}
}