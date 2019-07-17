#pragma once

#include <CoreBasicInclude.h>
#include "DebugMenuAction.h"
#include <UI/Button.h>
#include <Utils/Maths/maths.h>

namespace Core
{
	namespace Debug
	{
		class DebugMenuItem : public UI::Button 
		{
		private:
			IAction* m_Action;
		public:
			DebugMenuItem(IAction* action, const Maths::Rectangle& bounds);

			void onUpdate() override;
		};
	}
}