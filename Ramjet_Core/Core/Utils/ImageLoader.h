#pragma once

#include <Utils/types.h>
#include <Utils/Log.h>
#include <string>
#include <FreeImage/FreeImage.h>

namespace Utils {

	CORE_API byte* load_image(const char* filename, uint* width, uint* height, uint* bits);	

}

