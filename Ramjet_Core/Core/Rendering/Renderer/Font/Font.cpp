#include "Font.h"

namespace Core {

	namespace Rendering {

		Font::Font(std::string name, std::string filename, float size)
			: m_Name(name), m_Filename(filename), m_Size(size), m_Scale(960 / (size), 540 / (size / 2))
		{
			if (size != FONT_STD_SIZE)
				m_Name = name + std::to_string(size);
			m_FTAtlas = ftgl::texture_atlas_new(512, 512, 2);
			m_FTFont = ftgl::texture_font_new_from_file(m_FTAtlas, m_Size, filename.c_str());
			CORE_ASSERT(m_FTFont, "Failed to load font '", filename.c_str(), "'!");			
		}

		void Font::setScale(float x, float y)
		{
			m_Scale = Maths::vec2(x, y);
		}

	}

}