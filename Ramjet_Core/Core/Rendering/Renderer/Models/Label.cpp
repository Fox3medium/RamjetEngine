#include "Label.h"
#include <CoreBasicInclude.h>

namespace Core {

	using namespace Manager;

	namespace Rendering {
		Label::Label(const String& text, float x, float y, unsigned int color)
			: Renderable2D(), m_Text(text), position(m_Position), m_Font(Font_Manager::get(text))
		{
			position = Maths::vec3(x, y, 0.0f);
			m_Color = color;
		}

		Label::Label(const String& text, float x, float y, Font* font, unsigned int color)
			: Renderable2D(), m_Text(text), position(m_Position), m_Font(font)
		{
			position = Maths::vec3(x, y, 0.0f);
			m_Color = color;
		}

		Label::Label(const String& text, float x, float y, const String& font, unsigned int color)
			: Renderable2D(), m_Text(text), position(m_Position), m_Font(Font_Manager::get(font))
		{
			position = Maths::vec3(x, y, 0.0f);
			m_Color = color;

			validateFont(font);
		}

		Label::Label(const String& text, float x, float y, const String& font, unsigned int size, unsigned int color)
			: Renderable2D(), m_Text(text), position(m_Position), m_Font(Font_Manager::get(font,size))
		{
			position = Maths::vec3(x, y, 0.0f);
			m_Color = color;

			validateFont(font, size);
		}

		void Label::submit(Renderer2D* renderer) const
		{
			renderer->drawString(m_Text, position, *m_Font, m_Color);
		}
		void Label::setText(unsigned int i,String s)
		{
			m_Text = std::to_string(i) + s;
		}

		void Label::setText(String s)
		{
			m_Text = s;
		}

		void Label::validateFont(const String& name, int size)
		{
			if (m_Font != nullptr)
				return;

			std::cout << "NULL FONT Font=" << name;
			if (size > 0)
				std::cout << ", Size= " << size;
			std::cout << std::endl;

			m_Font = Font_Manager::get(name);
		}
	}

}