#include "PostFX.h"

#include <Rendering/Platform/CoreRenderAPI.h>

namespace Core {

	namespace Rendering {

		PostFX::PostFX()
		{
		}

		PostFX::~PostFX()
		{
		}

		void PostFX::push(PostFXPass* pass)
		{
			m_Passes.push_back(pass);
		}

		void PostFX::pop()
		{
			m_Passes.pop_back();
		}

		void PostFX::RenderPostFX(FrameBuffer* source, FrameBuffer* target, VertexArray* quad, IndexBuffer* indices)
		{
			target->bind();
			API::setActiveTexture(GL_TEXTURE0);
			source->getTexture()->bind();

			quad->bind();
			indices->bind();

			for (PostFXPass* pass : m_Passes)
				pass->RenderPass(target);

			indices->unbind();
			quad->unbind();
		}

	}

}