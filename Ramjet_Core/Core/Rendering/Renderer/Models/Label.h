#pragma once

#include "../Renderable2D.h"
#include <Utils/String.h>

namespace Core {

	namespace Rendering {
	
		class Label : public Renderable2D
		{
		private:

			std::string& m_Text;
			Maths::vec3& position;
			float m_x, m_y;

		public:

			Label(std::string text, float x, float y, Maths::vec4 color);
			void submit(Renderer2D* renderer) const override;

			void setText(unsigned int i , std::string s);
		};

	}

}

