#include <CoreBasicInclude.h>
#include "MouseEvent.h"

namespace Core { 
	namespace Events {

		MouseButtonEvent::MouseButtonEvent(int button, float x, float y, Type type)
			: Event(type), m_Button(button), m_Position(Maths::vec2(x, y))
		{
		}

		MousePressedEvent::MousePressedEvent(int button, float x, float y)
			: MouseButtonEvent(button, x, y, MouseMovedEvent::getStaticType())
		{
		}

		String MousePressedEvent::toString() const
		{
			char buffer[256];
			sprintf(buffer, "MouseReleasedEvent: (%d, %f, %f)", getButton(), getX(), getY());
			return String(buffer);
		}

		MouseReleasedEvent::MouseReleasedEvent(int button, float x, float y)
			: MouseButtonEvent(button, x, y, MouseReleasedEvent::getStaticType())
		{
		}

		MouseMovedEvent::MouseMovedEvent(float x, float y, bool dragged)
			: Event(MouseMovedEvent::getStaticType()), m_Position(Maths::vec2(x, y)), m_Dragged(dragged)
		{
		}
	}
}