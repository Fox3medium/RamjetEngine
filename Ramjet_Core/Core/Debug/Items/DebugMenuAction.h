#pragma once

#include <CoreBasicInclude.h>
#include <Utils/String.h>

namespace Core
{
	namespace Debug
	{
		struct IAction
		{
			String name;
			virtual void onAction() = 0;
			virtual String toString() = 0;
		};

		struct EmptyAction : public IAction
		{
			EmptyAction(const String& name) { this->name = name; }
			void onAction() override {}
			String toString() override { return name; }
		};

		template<typename T>
		struct ValueAction : public IAction
		{
			using Getter = std::function<T()>;
			using Setter = std::function<void(T)>;
		private:
			Getter m_Getter;
			Setter m_Setter;
			T m_Min, m_Max;
		public:
			ValueAction(const String& name, const Getter& getter, const Setter& setter, T minValue, T maxValue)
				: m_Getter(getter), m_Setter(setter), m_Min(minValue), m_Max(maxValue) {
				this->name = name;
			}

			void onAction() override
			{
				DebugMenu::get()->editValue((m_Getter() - m_Min) / (m_Max - m_Min), METHOD(&ValueAction::onValueChanged));
			}

			void onValueChanged(float value)
			{
				m_Setter(value * (m_Max - m_Min) + m_Min);
			}

			String toString() override
			{
				return name + " " + std::to_string(m_Getter());
			}
		};

		typedef ValueAction<int> IntAction;
		typedef ValueAction<float> FloatAction;
	}
}