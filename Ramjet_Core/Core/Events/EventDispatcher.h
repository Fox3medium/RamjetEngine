#pragma once

#include <Core/Common.h>
#include "Events.h"
#include <functional>

namespace Core {

	namespace Events {

		class CORE_API EventDispatcher
		{
		private:
			Event& m_Event;
		public:
			EventDispatcher(Event& event)
				: m_Event(event) {}

			template<typename T>
			void dispatch(std::function<bool(T&)> func)
			{
				if ((int)m_Event.getType() & (int)T::getStaticType())
					m_Event.m_Handled = func(*(T*)& m_Event);
			}
		};

	}

}