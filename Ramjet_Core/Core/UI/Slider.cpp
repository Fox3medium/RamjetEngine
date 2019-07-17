#include "Slider.h"
#include <CoreBasicInclude.h>

namespace Core
{
	namespace UI
	{
		using namespace Maths;

		Slider::Slider(const Maths::Rectangle& bounds, bool vertical)
			: Widget(bounds), m_Value(0.0f), m_State(SliderState::UNPRESSED), m_HeadOffset(0.0f),
			m_Callback(&Slider::noCallback), m_Vertical(vertical)
		{
			float size = vertical ? bounds.width : bounds.height;
			m_HeadBounds = Rectangle(bounds.x, bounds.y, size, size);
		}

		Slider::Slider(const Maths::Rectangle& bounds, float value, const ValueChangedCallback& callback, bool vertical)
			: Widget(bounds), m_Value(value), m_State(SliderState::UNPRESSED), m_HeadOffset(0.0f),
			m_Callback(callback), m_Vertical(vertical)
		{
			float size = vertical ? bounds.width : bounds.height;
			m_HeadBounds = Rectangle(bounds.x, bounds.y, size, size);
		}

		bool Slider::onMousePressed()
		{
			vec2 mouse = Init::Window::getWindowClass()->getMousePos();

			if (m_HeadBounds.Contains(mouse))
			{
				m_State = SliderState::PRESSEDHEAD;
				m_HeadOffset = m_Vertical ? (mouse.y - m_HeadBounds.y) : (mouse.x - m_HeadBounds.x);
			}
			else
			{
				m_State = SliderState::PRESSED;
			}
			return true;
		}

		bool Slider::onMouseReleased()
		{
			m_State = SliderState::UNPRESSED;
			return true;
		}

		bool Slider::onMouseMoved()
		{
			vec2 mouse = Init::Window::getWindowClass()->getMousePos();

			if (m_State == SliderState::PRESSEDHEAD)
			{
				if (m_Vertical)
					setValue((mouse.y - m_Bounds.y - m_HeadOffset) / (m_Bounds.size.y - m_HeadBounds.size.y));
				else
					setValue((mouse.x - m_Bounds.x - m_HeadOffset) / (m_Bounds.size.x - m_HeadBounds.size.x));
			}

			return false;
		}

		void Slider::onUpdate()
		{
			if (!Manager::Control_Manager::isMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
				m_State = SliderState::UNPRESSED;

			if (m_Vertical)
			{
				float bounds = m_Bounds.size.y - m_HeadBounds.size.y;
				m_HeadBounds.y = m_Bounds.y + bounds * m_Value;
				m_HeadBounds.y = clamp(m_HeadBounds.y, m_Bounds.y, m_Bounds.y + m_Bounds.size.y - m_HeadBounds.size.y);
			}
			else
			{
				float bounds = m_Bounds.size.x - m_HeadBounds.size.x;
				m_HeadBounds.x = m_Bounds.x + bounds * m_Value;
				m_HeadBounds.x = clamp(m_HeadBounds.x, m_Bounds.x, m_Bounds.x + m_Bounds.size.x - m_HeadBounds.size.x);
			}
		}

		void Slider::onRender(Renderer2D& renderer)
		{
			renderer.fillRect(m_Bounds, 0xcf7f7f7f);
			renderer.drawRect(m_Bounds);

			renderer.fillRect(m_HeadBounds, 0xcfbfbfbf);
			renderer.drawRect(m_HeadBounds);

			vec2 offset = m_Vertical ? vec2(0, m_Bounds.size.y / 2.0f) : vec2(m_Bounds.size.x / 2.0f, 0);
			renderer.drawLine(m_Bounds.Center() - offset, m_Bounds.Center() + offset);
		}

		void Slider::setValue(float value)
		{
			value = clamp(value, 0.0f, 1.0f);
			m_Value = value;
			m_Callback(value);
		}
	}
}