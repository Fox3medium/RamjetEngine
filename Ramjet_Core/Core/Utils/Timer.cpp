#include "Timer.h"

Utils::Timer::Timer()
{
	reset();
}

void Utils::Timer::reset()
{
	m_Start = HighResolutionClock::now();
}

float Utils::Timer::elapsed()
{
	return std::chrono::duration_cast<milliseconds_type>(HighResolutionClock::now() - m_Start).count() / 1000.0f;
}
