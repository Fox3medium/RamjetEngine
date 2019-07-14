#pragma once

#include "Event.h"
#include <Utils/Maths/maths.h>

namespace Core {
	namespace Events {

		class CORE_API MouseButtonEvent : public Event
		{
		protected:
			int m_Button;
			Maths::vec2 m_Position;
		protected:
			MouseButtonEvent(int button, float x, float y, Event::Type type);
		public:
			inline const int getButton() const { return m_Button; }
			inline const float getX() const { return m_Position.x; }
			inline const float getY() const { return m_Position.y; }
			inline const Maths::vec2& getPosition() const { return m_Position; }

			inline static int getStaticType() { return (int)Event::Type::MOUSE_PRESSED | (int)Event::Type::MOUSE_RELEASED; }
		};

		class CORE_API MousePressedEvent : public MouseButtonEvent
		{
		public:
			MousePressedEvent(int button, float x, float y);

			String toString() const override;

			inline static Type getStaticType() { return Event::Type::MOUSE_PRESSED; }
		};

		class CORE_API MouseReleasedEvent : public MouseButtonEvent
		{
		public:
			MouseReleasedEvent(int button, float x, float y);
			inline static Type getStaticType() { return Event::Type::MOUSE_RELEASED; }
		};

		class CORE_API MouseMovedEvent : public Event
		{
		private:
			Maths::vec2 m_Position;
			bool m_Dragged;
		public:
			MouseMovedEvent(float x, float y, bool dragged);

			inline const float getX() const { return m_Position.x; }
			inline const float getY() const { return m_Position.y; }
			inline const Maths::vec2& getPosition() const { return m_Position; }
			inline const bool isDragged() const { return m_Dragged; }

			inline static Type getStaticType() { return Event::Type::MOUSE_MOVED; }
		};

	}
}