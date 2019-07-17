#pragma once

#include <CoreBasicInclude.h>
#include "Panel.h"

#include <Utils/Maths/maths.h>

namespace Core {

	namespace UI {

		class CORE_API Widget
		{
		protected:
			bool m_Active;
			bool m_Focused;

			Panel* m_Panel;
			Maths::Rectangle m_Bounds;
		private:
			Widget() {}
		protected:
			Widget(const Maths::Rectangle& bounds);
		public:
			virtual bool onMousePressed();
			virtual bool onMouseReleased();
			virtual bool onMouseMoved();

			virtual void onUpdate();
			virtual void onRender(Renderer2D& renderer);

			inline const Maths::Rectangle& getBounds() const { return m_Bounds; }
			inline void setBounds(const Maths::Rectangle& bounds) { m_Bounds = bounds; }

			inline bool isActive() const { return m_Active; }
			inline void setActive(bool active) { m_Active = active; }
		};

	}
}
