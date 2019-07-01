#include "Simple2DRenderer.h"

namespace Core {

	namespace Rendering {

		void Simple2DRenderer::submit(const Renderable2D* renderable)
		{
			m_RenderQueue.push_back((Static_Sprite*) renderable);
		}

		void Simple2DRenderer::flush()
		{
			while (!m_RenderQueue.empty()) {
				const Static_Sprite* sprite = m_RenderQueue.front();
				sprite->getVAO()->bind();
				sprite->getIBO()->bind();

				sprite->getShader().setUniformMat4("ml_matrix", Maths::mat4::translation(sprite->getPosition()));
				glDrawElements(GL_TRIANGLES, sprite->getIBO()->getCount(), GL_UNSIGNED_INT, nullptr);

				sprite->getIBO()->unbind();
				sprite->getVAO()->unbind();

				m_RenderQueue.pop_front();
			}
		}

	}

}