#pragma once

#include "../Renderable2D.h"
//#include <Utils/String.h>
#include <Font_Manager.h>

namespace Core {

	namespace Rendering {
	
		class Label : public Renderable2D
		{
		private:

			Font* m_Font;			
			Maths::vec3& position;
			float m_x, m_y;

		public:

			String m_Text;

			Label(const String& text, float x, float y, unsigned int color);
			Label(const String& text, float x, float y, Font* font, unsigned int color);
			Label(const String& text, float x, float y, const String& font, unsigned int color);
			Label(const String& text, float x, float y, const String& font, unsigned int size, unsigned int color);
			void submit(Renderer2D* renderer) const override;

			void setText(unsigned int i , String s);
			void setText(String s);

			void validateFont(const String& name, int size = -1);
		};

	}

}

