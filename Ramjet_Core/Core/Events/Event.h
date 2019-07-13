#pragma once

#include <Core/Common.h>

namespace Core { 
	namespace Events {

		class CORE_API Event
		{
		public:
			enum class Type
			{
				MOUSE_PRESSED, MOUSE_RELEASED, MOUSE_MOVED,
				KEY_PRESSED, KEY_RELEASED
			};
		protected:
			bool m_Handled;
			Type m_Type;
		protected:
			Event(Type type);
			inline Type getType() const { return m_Type; }
		};

	}
}