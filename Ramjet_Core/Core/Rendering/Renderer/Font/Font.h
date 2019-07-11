#pragma once

#include <Utils/Log.h>
#include <freetype-gl.h>
#include <string>

#include <Utils/Maths/vec2.h>

namespace Core {

	namespace Rendering {
	
		#define FONT_STD_SIZE	24
		class Font 
		{
		private:
			ftgl::texture_atlas_t* m_FTAtlas;
			ftgl::texture_font_t* m_FTFont;
			float m_Size;

			Maths::vec2 m_Scale;
			String m_Name;
			String m_Filename; 

		public:
			Font(String name, String filename, float size);
			Font(String name, const byte* data, unsigned int datasize, float size);

			inline ftgl::texture_font_t* getFTFont() const { return m_FTFont; }

			void setScale(float x, float y);

			inline const unsigned int getID() const { return m_FTAtlas->id; }
			inline const Maths::vec2& getScale() const { return m_Scale; }
			inline const String& getName() const { return m_Name; }
			inline const String& getFilename() const { return m_Filename; }
			inline const float getSize() const { return m_Size; }
		};

	}

}