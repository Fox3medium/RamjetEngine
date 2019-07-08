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

			std::string m_Text;

			Label(std::string text, float x, float y, unsigned int color);
			Label(std::string text, float x, float y, Font* font, unsigned int color);
			Label(std::string text, float x, float y, const std::string& font, unsigned int color);
			Label(std::string text, float x, float y, const std::string& font, unsigned int size, unsigned int color);
			void submit(Renderer2D* renderer) const override;

			void setText(unsigned int i , std::string s);
			void setText(std::string s);

			void validateFont(const std::string& name, int size = -1);
		};

	}

}

