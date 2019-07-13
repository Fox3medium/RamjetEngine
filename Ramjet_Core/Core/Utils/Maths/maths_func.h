#pragma once

#include <math.h>
#include <Core/Common.h>

#define CORE_PI 3.14159265358f
#define _USE_MATH_DEFINES

namespace Maths {

	CORE_API inline float toRadians(float degrees)
	{
		return (float)(degrees * (CORE_PI / 180.0f));
	}

	CORE_API inline float toDegrees(float radians)
	{
		return (float)(radians * (180.0f / CORE_PI));
	}

	CORE_API inline int sign(float value)
	{
		return (value > 0) - (value < 0);
	}

	CORE_API inline float sin(float angle)
	{
		return ::sin(angle);
	}

	CORE_API inline float cos(float angle)
	{
		return ::cos(angle);
	}

	CORE_API inline float tan(float angle)
	{
		return ::tan(angle);
	}

	CORE_API inline float sqrt(float value)
	{
		return ::sqrt(value);
	}

	CORE_API inline float rsqrt(float value)
	{
		return 1.0f / ::sqrt(value);
	}

	CORE_API inline float asin(float value)
	{
		return ::asin(value);
	}

	CORE_API inline float acos(float value)
	{
		return ::acos(value);
	}

	CORE_API inline float atan(float value)
	{
		return ::atan(value);
	}

	CORE_API inline float atan2(float y, float x)
	{
		return ::atan2(y, x);
	}

	CORE_API inline float _min(float value, float minimum)
	{
		return (value < minimum) ? minimum : value;
	}

	CORE_API inline float _max(float value, float maximum)
	{
		return (value > maximum) ? maximum : value;
	}

	CORE_API inline float clamp(float value, float minimum, float maximum)
	{
		return (value > minimum) ? (value < maximum) ? value : maximum : minimum;
	}

}