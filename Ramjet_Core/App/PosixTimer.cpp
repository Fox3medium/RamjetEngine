#include <CoreBasicInclude.h>
#include <Utils/Timer.h>

#include <chrono>

namespace Utils
{
	typedef std::chrono::high_resolution_clock HighResolutionClock;
	typedef std::chrono::duration<float, std::milli> milliseconds_type;

	static std::chrono::time_point<HighResolutionClock> s_Start;

	Timer::Timer()
	{
		reset();
	}

	void Timer::reset()
	{
		s_Start = HighResolutionClock::now();
	}

	float Timer::elapsed()
	{
		return std::chrono::duration_cast<milliseconds_type>(HighResolutionClock::now() - s_Start).count() / 1000.0f;
	}

}