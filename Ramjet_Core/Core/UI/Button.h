#pragma once

#include <CoreBasicInclude.h>
#include <Utils/String.h>

#include "Widget.h"

namespace Core 
{
	namespace UI 
	{
		class Button : public Widget
		{
		public:
			using ActionHandler = std::function<void()>;
		private:
			enum class ButtonState
			{
				UNPRESSED, PRESSED
			};
		protected:
			String m_Label;
			ButtonState m_State;
			ActionHandler m_ActionHandler;
			Font* m_Font;
		public:
			Button(const String& label, const Maths::Rectangle& bounds, const ActionHandler& handler = &Button::noAction);

			bool onMousePressed() override;
			bool onMouseReleased() override;
			bool onMouseMoved() override;

			virtual void onAction();
			virtual void onUpdate() override;
			virtual void onRender(Renderer2D& renderer) override;

			inline void setLabel(const String& label) { m_Label = label; }
			inline const String& getLabel() const { return m_Label; }

			inline void setFont(Font* font) { m_Font = font; }
			inline const Font& getFont() const { return *m_Font; }

			inline void setAction(const ActionHandler& action) { m_ActionHandler = action; }
		private:
			static void noAction() {}
		};
	}
}