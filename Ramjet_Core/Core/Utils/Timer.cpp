#include "Timer.h"

Utils::Timer::Timer()
{
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	m_Frequency = 1.0 / frequency.QuadPart;
	QueryPerformanceCounter(&m_TimeStart);
}

void Utils::Timer::reset()
{
	QueryPerformanceCounter(&m_TimeStart);

}

float Utils::Timer::elapsed()
{
	LARGE_INTEGER currentTIme;
	QueryPerformanceCounter(&currentTIme);
	unsigned __int64 cycle = currentTIme.QuadPart - m_TimeStart.QuadPart;
	return float(cycle * m_Frequency);
}
