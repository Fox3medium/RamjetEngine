#include <CoreBasicInclude.h>
#include "KeyEvent.h"

namespace Core { 
	namespace Events {

		KeyEvent::KeyEvent(int keyCode, Event::Type type)
			: Event(type)
		{
		}

		KeyPressedEvent::KeyPressedEvent(int button, int repeat)
			: KeyEvent(button, Event::Type::KEY_PRESSED)
		{
		}

		KeyReleasedEvent::KeyReleasedEvent(int button)
			: KeyEvent(button, Event::Type::KEY_RELEASED)
		{
		}

	} 
}