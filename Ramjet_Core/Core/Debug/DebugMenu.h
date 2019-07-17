#pragma once

#include <CoreBasicInclude.h>
#include <Rendering/Renderer/Renderer2D.h>

namespace Core 
{
	namespace Debug 
	{
		struct DebugMenuItem
		{
			String name;
		};

		class DebugMenu
		{
		private:
			static DebugMenu* s_Instance;

			bool m_Visible;
			std::vector<DebugMenuItem> m_DebugMenuItems;
		public:
			static void init();
			static void add(const String& name);

			static bool isVisible();
			static void setVisible(bool visible);

			static void onRender(Rendering::Renderer2D& renderer);

		private:
			DebugMenu();
		};
	}
}