#pragma once

#include <chrono>

namespace Utils {

	class Timer {
	
	private:
		typedef std::chrono::high_resolution_clock HighResolutionClock;
		typedef std::chrono::duration<float, std::milli> milliseconds_type;
		std::chrono::time_point<HighResolutionClock> m_Start;

	public:
		Timer();

		void reset();

		float elapsed();

	};

}