#pragma once

#include "Event.h"

namespace Core 
{ 
	namespace Events 
	{
		class CORE_API IEventListener
		{
		public:
			virtual void onEvent(Event& event) = 0;
		};
	} 
}