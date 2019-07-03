#include "Label.h"
#include <string>

namespace Core {

	namespace Rendering {
		Label::Label(std::string text, float x, float y, Maths::vec4 color)
			: Renderable2D(), m_Text(text), position(m_Position)
		{
			position = Maths::vec3(x, y, 0.0f);
			m_Color = color;
		}

		void Label::submit(Renderer2D* renderer) const
		{
			renderer->drawString(m_Text, position, m_Color);
		}
		void Label::setText(unsigned int i, std::string s)
		{
			m_Text = std::to_string(i) + s;
		}
	}

}