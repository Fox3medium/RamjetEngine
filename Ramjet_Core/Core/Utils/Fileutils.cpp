#include "fileutils.h"
#include <Utils\Static\CInOut.h>

namespace Utils {

	std::string read_file(const char* filepath)
	{
		FILE* file = fopen(filepath, "rt");
		if (file == nullptr)
			CORE_ASSERT(file, "Could not open file '", filepath, "' !");

		fseek(file, 0, SEEK_END);
		unsigned long length = ftell(file);
		char* data = new char[length + 1];
		memset(data, 0, length + 1); //Ensure to read the file without problem/artefacts at the end
		fseek(file, 0, SEEK_SET);
		fread(data, 1, length, file);
		fclose(file);

		std::string result(data);
		delete[] data;

		return result;
	}

}


