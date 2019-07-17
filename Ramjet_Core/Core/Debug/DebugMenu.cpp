#include "DebugMenu.h"
#include <CoreBasicInclude.h>

namespace Core
{

	namespace Debug
	{
		DebugMenu* DebugMenu::s_Instance = nullptr;

		DebugMenu::DebugMenu() 
			: m_Visible(false), m_Padding(1.5f), m_FontSize(24.0f)
		{

		}

		void DebugMenu::init()			
		{
			s_Instance = new DebugMenu();
		}

		void DebugMenu::add(const String& name)
		{
			s_Instance->m_DebugMenuItems.push_back(new IAction(name));
		}

		void DebugMenu::add(const String& name, float* value)
		{
			s_Instance->m_DebugMenuItems.push_back(new FloatAction(name, [value]() { return *value; }, [value](float v) { *value = v; }));
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
			float yOffset = s_Instance->m_Padding;
			for (IAction* item : s_Instance->m_DebugMenuItems)
			{
				float y = -7.0f + yOffset;
				renderer.fillRect(-16, y, 4 + s_Instance->m_Padding, s_Instance->m_Padding, 0xcf7f7f7f);
				renderer.drawString(item->toString(), Maths::vec3(-16.0f + 0.2f, y + s_Instance->m_Padding / 2.0f));

				yOffset += s_Instance->m_Padding;
			}
		}

	}

}