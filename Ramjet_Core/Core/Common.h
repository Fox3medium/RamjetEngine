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