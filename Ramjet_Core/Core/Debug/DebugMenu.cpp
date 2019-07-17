#include "DebugMenu.h"
#include <CoreBasicInclude.h>

namespace Core
{

	namespace Debug
	{
		using namespace Maths;
		using namespace UI;

		DebugMenu* DebugMenu::s_Instance = nullptr;

		DebugMenu::DebugMenu()
			: m_Visible(false), m_Slider(nullptr)
		{
			s_Instance = this;

			m_Settings.padding = 0.75f;
			m_Settings.fontSize = 24.0f;

			add("Padding", &m_Settings.padding, 0.0f, 2.0f);
			add("Font Size", &m_Settings.fontSize, 8.0f, 48.0f);

			m_Slider = nullptr;
			m_Panel = new Panel();
		}

		DebugMenu* DebugMenu::get()
		{
			return s_Instance;
		}

		void DebugMenu::init()
		{
			s_Instance = new DebugMenu();
		}

		void DebugMenu::add(const String& name)
		{
			s_Instance->m_ActionList.push_back(new EmptyAction(name));
		}

		void DebugMenu::add(const String& name, float* value)
		{
			add(name, value, 0.0f, 100.0f);
		}

		void DebugMenu::add(const String& name, float* value, float minimum, float maximum)
		{
			s_Instance->m_ActionList.push_back(new FloatAction(name, [value]() { return *value; }, [value](float v) { *value = v; }, minimum, maximum));
		}

		bool DebugMenu::isVisible()
		{
			return s_Instance->m_Visible;
		}

		void DebugMenu::setVisible(bool visible)
		{
			s_Instance->m_Visible = visible;
			if (visible)
				s_Instance->onActivate();
			else
				s_Instance->onDeactivate();
		}

		DebugMenuSettings& DebugMenu::getSettings()
		{
			return s_Instance->m_Settings;
		}

		bool DebugMenu::onMousePressed()
		{
			return false;
		}

		bool DebugMenu::onMouseReleased()
		{
			return false;
		}

		void DebugMenu::onActivate()
		{
			float width = 5.0f + m_Settings.padding;
			float height = 1.0f + m_Settings.padding;
			float yOffset = height;
			for (IAction* action : m_ActionList)
			{
				float y = 18.0f - yOffset;
				m_Panel->add(new DebugMenuItem(action, Rectangle(0.0f, y, width, height)));
				yOffset += height;
			}

			m_Slider = new Slider({ width, 0.0f, 1.5f, 18.0f }, true);
			m_Panel->add(m_Slider)->setActive(false);
		}

		void DebugMenu::onDeactivate()
		{
			m_Panel->clear();
		}

		void DebugMenu::editValue(float value, const Slider::ValueChangedCallback& callback)
		{
			// m_Slider = new DebugMenuSlider(m_DebugMenuItems[0].GetBounds().x + m_DebugMenuItems[0].GetBounds().width, 0.5f);
			m_Slider->setCallback(callback);
			m_Slider->setActive(true);
			m_Slider->setValue(value);
		}

		void DebugMenu::onUpdate()
		{
			if (m_Slider && m_Slider->isActive())
			{
				float value = m_Slider->getValue();

			}
		}

		void DebugMenu::onRender(Rendering::Renderer2D& renderer)
		{
			//CORE_WARN(m_Settings.fontSize);
			// 		if (m_Slider)
			// 			m_Slider->OnRender(renderer);
		}

	}

}