#pragma once

#include "Event.h"

namespace Core 
{ 
	namespace Events 
	{
		class CORE_API IEventListener
		{
		public:
			virtual bool OnEvent(const Event& event) = 0;
		};
	} 
}