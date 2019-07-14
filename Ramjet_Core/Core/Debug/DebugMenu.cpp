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

		void DebugMenu::add(const String& name)
		{
			s_Instance->m_DebugMenuItems.push_back({ name });
		}

		bool DebugMenu::isVisible()
		{
			return s_Instance->m_Visible;
		}

		void DebugMenu::setVisible(bool visible)
		{
			s_Instance->m_Visible = visible;
		}

		void DebugMenu::onRender(Rendering::Renderer2D& renderer)
		{
			float yOffset = 1.7f;
			for (DebugMenuItem& item : s_Instance->m_DebugMenuItems)
			{
				float y = -7.0f + yOffset;
				renderer.fillRect(-16, y, 6, 1.5f, 0xcf7f7f7f);
				renderer.drawString(item.name, Maths::vec3(-16.0f + 0.2f, y + 0.4f));

				yOffset += 1.7f;
			}
		}

	}

}