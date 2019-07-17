#include "DebugMenuItem.h"
#include <CoreBasicInclude.h>
#include <Managers/Font_Manager.h>
#include "../DebugMenu.h"

namespace Core
{
	namespace Debug
	{
		using namespace Rendering;

		DebugMenuItem::DebugMenuItem(IAction* action, const Maths::Rectangle& bounds)
			: Button(action->toString(), bounds, [action]() { action->onAction(); }), m_Action(action)
		{
		}

		void DebugMenuItem::onUpdate()
		{
			m_Label = m_Action->toString();
			m_Font = Font_Manager::get();
		}
	}
}