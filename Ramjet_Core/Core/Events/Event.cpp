#include <CoreBasicInclude.h>
#include "Event.h"

namespace Core 
{ 
	namespace Events 
	{

		Event::Event(Type type)
			: m_Type(type), m_Handled(false)
		{
		}

	}
}