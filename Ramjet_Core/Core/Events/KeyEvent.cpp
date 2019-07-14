#include <CoreBasicInclude.h>
#include "KeyEvent.h"

namespace Core { 
	namespace Events {

		KeyEvent::KeyEvent(int keyCode, Event::Type type)
			: Event(type), m_KeyCode(keyCode)
		{
		}

		KeyPressedEvent::KeyPressedEvent(int button, int repeat)
			: KeyEvent(button, KeyPressedEvent::getStaticType()), m_Repeat(repeat)
		{
		}

		KeyReleasedEvent::KeyReleasedEvent(int button)
			: KeyEvent(button, KeyReleasedEvent::getStaticType())
		{
		}

	}
}