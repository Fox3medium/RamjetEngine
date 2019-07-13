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
			inline const int GetButton() const { return m_Button; }
			inline const float GetX() const { return m_Position.x; }
			inline const float GetY() const { return m_Position.y; }
			inline const Maths::vec2& GetPosition() const { return m_Position; }
		};

		class CORE_API MousePressedEvent : public MouseButtonEvent
		{
		public:
			MousePressedEvent(int button, float x, float y);
		};

		class CORE_API MouseReleasedEvent : public MouseButtonEvent
		{
		public:
			MouseReleasedEvent(int button, float x, float y);
		};

		class CORE_API MouseMovedEvent : public Event
		{
		private:
			Maths::vec2 m_Position;
			bool m_Dragged;
		public:
			MouseMovedEvent(float x, float y, bool dragged);

			inline const float GetX() const { return m_Position.x; }
			inline const float GetY() const { return m_Position.y; }
			inline const Maths::vec2& GetPosition() const { return m_Position; }
			inline const bool IsDragged() const { return m_Dragged; }
		};

	}
}