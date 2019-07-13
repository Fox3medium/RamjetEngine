#pragma once

#include <Core/Common.h>

namespace Utils {

	class CORE_API Timer {
	
	public:
		// Creates and starts timer
		Timer();
		// Resets and restarts timer
		void reset();
		// Returns time in milliseconds
		float elapsed();
	};

}