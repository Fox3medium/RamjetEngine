#pragma once

#include <CoreBasicInclude.h>
#include <Rendering/Renderer/Renderer2D.h>
#include <Rendering/Renderer/Layers/Layer2D.h>

namespace Core 
{
	namespace UI 
	{
		class Widget;

		class Panel : public Layer2D
		{
		private:
			std::vector<Widget*> m_Widgets;
		public:
			Panel();
			~Panel();

			Widget* add(Widget* widget);
			void remove(Widget* widget);
			void clear();

			void onEvent() override;
			bool onMousePressedEvent();
			bool onMouseReleasedEvent();
			bool onMouseMovedEvent();

			void onUpdate() override;
			void onRender(Renderer2D& renderer) override;
		};
	}
}