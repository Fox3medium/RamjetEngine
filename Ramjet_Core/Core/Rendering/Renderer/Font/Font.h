#pragma once

#include <Core/Common.h>
#include <Utils/types.h>

#include <Utils/Maths/vec2.h>

namespace ftgl {
	struct texture_atlas_t;
	struct texture_font_t;
}

namespace Core {

	namespace Rendering {
	
		#define FONT_STD_SIZE	24

		class CORE_API Font 
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

			const uint getID() const;
			inline const Maths::vec2& getScale() const { return m_Scale; }
			inline const String& getName() const { return m_Name; }
			inline const String& getFilename() const { return m_Filename; }
			inline const float getSize() const { return m_Size; }
		};

	}

}