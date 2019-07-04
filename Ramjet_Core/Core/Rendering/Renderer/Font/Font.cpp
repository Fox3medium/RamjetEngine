#include "Font.h"
namespace Core {

	namespace Rendering {

		Font::Font(std::string name, std::string filename, int size)
			: m_Name(name), m_Filename(filename), m_Size(size)
		{
			if (size != FONT_STD_SIZE)
				m_Name = name + std::to_string(size);
			m_FTAtlas = ftgl::texture_atlas_new(512, 512, 2);
			m_FTFont = ftgl::texture_font_new_from_file(m_FTAtlas, 32, filename.c_str());
		}

	}

}