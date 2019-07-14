#pragma once

#pragma warning (disable:4251)

#ifdef CORE_PLATFORM_WINDOWS 
	#ifdef CORE_DLL
		#define CORE_API __declspec(dllexport)
	#else
		#define CORE_API __declspec(dllimport)
	#endif
#else 
	#define CORE_API
#endif

// Common defines
#define BIT(x) (1 << x)

#define METHOD_1(x) std::bind(x, this, std::placeholders::_1)
#define METHOD(x) METHOD_1(x)