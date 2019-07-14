#pragma once

#include <Utils/String.h>
#include <Core/Common.h>

namespace Core { 

	namespace Events {

		#undef MOUSE_PRESSED
		#undef MOUSE_RELEASED
		#undef MOUSE_MOVED
		#undef KEY_PRESSED
		#undef KEY_RELEASED

		class CORE_API Event
		{
		private:
			friend class EventDispatcher;

		public:
			enum class Type
			{
				KEY_PRESSED =		BIT(0),
				KEY_RELEASED =		BIT(1),

				MOUSE_PRESSED =		BIT(2),
				MOUSE_RELEASED =	BIT(3),
				MOUSE_MOVED =		BIT(4)
			};
		protected:
			bool b_Handled;
			Type m_Type;

		protected:
			Event(Type type);

		public:
			inline Type getType() const { return m_Type; }
			inline bool isHandled() const { return b_Handled; }
			virtual String toString() const;
			static String typeToString(Type type);


		};

	}
}