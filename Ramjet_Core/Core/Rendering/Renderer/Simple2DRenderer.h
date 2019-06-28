#pragma once

#include <deque>
#include "Renderer2D.h"
#include "Models/Static_Sprite.h"

using namespace Utils;

namespace Core {

	namespace Rendering {

		class Simple2DRenderer : public Renderer2D
		{
		private:
			std::deque<const Static_Sprite*> m_RenderQueue;
		public:
			void submit(const Renderable2D* renderable) override;
			void flush() override;
		};

	}

}