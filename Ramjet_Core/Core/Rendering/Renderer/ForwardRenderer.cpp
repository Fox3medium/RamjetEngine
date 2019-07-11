#include "ForwardRenderer.h"

namespace Core
{
	namespace Rendering
	{
		ForwardRenderer::ForwardRenderer()
		{
		}

		void ForwardRenderer::init()
		{
		}

		void ForwardRenderer::begin()
		{
			m_DrawQueue.clear();
		}

		void ForwardRenderer::submit(Mesh* mesh)
		{
			m_DrawQueue.push_back(mesh);
		}

		void ForwardRenderer::end()
		{

		}

		void ForwardRenderer::flush()
		{
			for (uint i = 0; i < m_DrawQueue.size(); i++)
				m_DrawQueue[i]->render(*this);
		}

	}
}