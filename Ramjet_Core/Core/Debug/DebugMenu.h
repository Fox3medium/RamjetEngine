#pragma once

#include <CoreBasicInclude.h>
#include <Rendering/Renderer/Renderer2D.h>
#include <UI/Panel.h>
#include "Items/DebugMenuAction.h"
#include "Items/DebugMenuItem.h"
#include "Items/DebugMenuSlider.h"
#include <UI/Slider.h>

namespace Core 
{
	namespace Debug 
	{
		typedef std::vector<IAction*> ActionList;

		struct DebugMenuSettings
		{
			float padding;
			float fontSize;
		};

		class CORE_API DebugMenu
		{
		private:
			static DebugMenu* s_Instance;
		private:
			bool m_Visible;
			DebugMenuSettings m_Settings;
			ActionList m_ActionList;

			// DebugMenuSlider* m_Slider;
			UI::Panel* m_Panel;
			UI::Slider* m_Slider;
		public:
			static DebugMenu* get();

			static void init();
			static void add(const String& name);
			static void add(const String& name, float* value);
			static void add(const String& name, float* value, float mininmum, float maximum);

			static bool isVisible();
			static void setVisible(bool visible);

			static DebugMenuSettings& getSettings();

			void onActivate();
			void onDeactivate();
			void editValue(float value, const UI::Slider::ValueChangedCallback& callback);

			bool onMousePressed();
			bool onMouseReleased();
			void onUpdate();
			void onRender(Rendering::Renderer2D& renderer);
		private:
			DebugMenu();
		};
	}
}