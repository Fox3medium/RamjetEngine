#pragma once

#include "Event.h"

namespace Core { namespace Events {

	class CORE_API KeyEvent : public Event
	{
	protected:
		int m_KeyCode;
		int m_Count;
	public:
		KeyEvent(int keyCode, Event::Type type);

		inline int getKeyCode() const { return m_KeyCode; }

		inline static int getStaticType() { return (int)Event::Type::KEY_PRESSED | (int)Event::Type::KEY_RELEASED; }
	};

	class CORE_API KeyPressedEvent : public KeyEvent
	{
	private:
		int m_Repeat;
	public:
		KeyPressedEvent(int button, int repeat);

		inline int getRepeat() const { return m_Repeat; }
		inline static Type getStaticType() { return Event::Type::KEY_PRESSED; }
	};

	class CORE_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int button);

		inline static Type getStaticType() { return Event::Type::KEY_RELEASED; }
	};

} }