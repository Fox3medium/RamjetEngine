#pragma once

#include <CoreBasicInclude.h>
#include <Utils/Maths/maths.h>

#include "Widget.h"

namespace Core 
{
	namespace UI 
	{
		class CORE_API Slider : public Widget
		{
		public:
			using ValueChangedCallback = std::function<void(float)>;
		private:
			enum class SliderState
			{
				UNPRESSED, PRESSED, PRESSEDHEAD
			};
		private:
			Maths::Rectangle m_HeadBounds;
			float m_Value;
			float m_HeadOffset;
			SliderState m_State;
			ValueChangedCallback m_Callback;
			bool m_Vertical;
		public:
			Slider(const Maths::Rectangle& bounds, bool vertical = false);
			Slider(const Maths::Rectangle& bounds, float value = 0.0f, const ValueChangedCallback & callback = &Slider::noCallback, bool vertical = false);

			bool onMousePressed() override;
			bool onMouseReleased() override;
			bool onMouseMoved() override;
				 
			void onUpdate() override;
			void onRender(Renderer2D& renderer) override;

			inline void setCallback(const ValueChangedCallback& callback) { m_Callback = callback; }

			inline float getValue() const { return m_Value; }
			void setValue(float value);
		private:
			static void noCallback(float) {}
		};
	}
}