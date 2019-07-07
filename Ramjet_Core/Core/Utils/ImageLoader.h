#pragma once

#include <Utils/String.h>
#include <FreeImage/FreeImage.h>

namespace Utils {

	static BYTE* load_image(const char* filename, GLsizei* width, GLsizei* height, unsigned int* bits) {
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		FIBITMAP* dib = nullptr;
		fif = FreeImage_GetFileType(filename, 0);
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(filename);
		if (fif == FIF_UNKNOWN)
			return nullptr;

		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, filename);

		if (dib == nullptr)
			CORE_WARN("Could not load the file : ", filename);
		// TODO Uncomment
		// Must be commented for debug mode? Why? CHECK COMPILER AND C++ SETTINGS
		// CORE_ASSERT(dib, "Could not load image ", filename, " !");

		FIBITMAP* bitmap = FreeImage_ConvertTo32Bits(dib);
		FreeImage_Unload(dib);

		BYTE* pixels = FreeImage_GetBits(bitmap);
		*width = FreeImage_GetWidth(bitmap);
		*height = FreeImage_GetHeight(bitmap);
		*bits = FreeImage_GetBPP(bitmap);

		int size = *width * *height * (*bits / 8);
		BYTE* result = new BYTE[size];
		memcpy(result, pixels, size);

		FreeImage_Unload(bitmap);
		
		return result;
	}

}

