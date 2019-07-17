#include "Button.h"

#include <CoreBasicInclude.h>
#include <Managers/Font_Manager.h>

namespace Core 
{
	namespace UI 
	{
		using namespace Maths;

		Button::Button(const String& label, const Maths::Rectangle& bounds, const ActionHandler& handler)
			: Widget(bounds), m_Label(label), m_ActionHandler(handler), m_State(ButtonState::UNPRESSED)
		{
			m_Font = Font_Manager::get();
		}

		bool Button::onMousePressed()
		{
			m_State = ButtonState::PRESSED;
			return true;
		}

		bool Button::onMouseReleased()
		{
			if (m_State == ButtonState::PRESSED)
				onAction();

			m_State = ButtonState::UNPRESSED;
			return true;
		}

		bool Button::onMouseMoved()
		{
			vec2 mouse = Init::Window::getWindowClass()->getMousePos();

			if (m_State == ButtonState::PRESSED && !m_Bounds.Contains(mouse))
				m_State = ButtonState::UNPRESSED;

			return false;
		}

		void Button::onAction()
		{
			m_ActionHandler();
		}

		void Button::onUpdate()
		{
		}

		void Button::onRender(Renderer2D& renderer)
		{
			renderer.drawRect(m_Bounds);
			renderer.fillRect(m_Bounds, m_State == ButtonState::PRESSED ? 0xcfbbbbbb : 0xcf5f5f5f);
			renderer.drawString(m_Label, m_Bounds.position + vec2(0.2f, 0.7f), *m_Font);
		}
	}
}