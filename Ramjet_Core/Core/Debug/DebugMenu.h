#pragma once

namespace Core 
{
	namespace Debug 
	{
		class DebugMenu
		{
		private:
			static DebugMenu* s_Instance;
		private:
			bool m_Visible;
		public:
			static void init();
			static void add();

			static bool isVisible();
			static void setVisible(bool visible);
		private:
			DebugMenu();
		};
	}
}