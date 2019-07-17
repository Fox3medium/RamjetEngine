#include "Widget.h"

#include <CoreBasicInclude.h>

namespace Core 
{
	namespace UI 
	{
		Widget::Widget(const Maths::Rectangle& bounds)
			: m_Bounds(bounds), m_Active(true), m_Focused(false)
		{
		}

		bool Widget::onMousePressed()
		{
			return false;
		}

		bool Widget::onMouseReleased()
		{
			return false;
		}

		bool Widget::onMouseMoved()
		{
			return false;
		}

		void Widget::onUpdate()
		{
		}

		void Widget::onRender(Renderer2D& renderer)
		{
		}
	}
}