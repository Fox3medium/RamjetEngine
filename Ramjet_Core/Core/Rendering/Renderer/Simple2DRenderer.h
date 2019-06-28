#pragma once

#include <deque>
#include "Renderer2D.h"

using namespace Utils;

namespace Core {

	namespace Rendering {

		class Simple2DRenderer : public Renderer2D
		{
		private:
			std::deque<const Renderable2D*> m_RenderQueue;
		public:
			void submit(const Renderable2D* renderable) override;
			void flush() override;
		};

	}

}