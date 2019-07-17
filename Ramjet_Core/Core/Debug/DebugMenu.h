#pragma once

#include <CoreBasicInclude.h>
#include <Rendering/Renderer/Renderer2D.h>

namespace Core 
{
	namespace Debug 
	{
		struct IAction
		{
			String name;
			IAction(const String& name)
				: name(name) {}
			virtual String toString() const { return name; }
		};

		template<typename T>
		struct ValueAction : IAction
		{
		private:
			using Getter = std::function<T()>;
			using Setter = std::function<void(T)>;

			Getter m_Getter;
			Setter m_Setter;
		public:
			ValueAction(const String& name, const Getter& getter, const Setter& setter)
				: IAction(name), m_Getter(getter), m_Setter(setter)
			{
			}
			String toString() const override
			{
				return name + " " + std::to_string(m_Getter());
			}
		};

		typedef ValueAction<int>	IntAction;
		typedef ValueAction<float>	FloatAction;

		class DebugMenu
		{
		public:
			static DebugMenu* s_Instance;

			bool m_Visible;
			std::vector<IAction*> m_DebugMenuItems;

			float m_Padding, m_FontSize;

		public:
			static void init();
			static void add(const String& name);
			static void add(const String& name, float* value);

			static bool isVisible();
			static void setVisible(bool visible);

			static void onRender(Rendering::Renderer2D& renderer);

		private:
			DebugMenu();
		};
	}
}