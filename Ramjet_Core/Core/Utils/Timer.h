#pragma once

#include <Windows.h>

namespace Utils {

	class Timer {
	
	private:
		LARGE_INTEGER m_TimeStart;
		double m_Frequency;

	public:
		Timer();

		void reset();

		float elapsed();

	};

}