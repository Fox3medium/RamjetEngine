#include "DebugMenu.h"
#include <CoreBasicInclude.h>

namespace Core
{

	namespace Debug
	{
		DebugMenu* DebugMenu::s_Instance = nullptr;

		DebugMenu::DebugMenu() 
			: m_Visible(false)
		{

		}

		void DebugMenu::init()			
		{
			s_Instance = new DebugMenu();
		}

		void DebugMenu::add()
		{
		}

		bool DebugMenu::isVisible()
		{
			return s_Instance->m_Visible;
		}

		void DebugMenu::setVisible(bool visible)
		{
			s_Instance->m_Visible = visible;
		}

	}

}