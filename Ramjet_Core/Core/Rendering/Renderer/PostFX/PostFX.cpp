#include "PostFX.h"

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

		void PostFX::RenderPostFX(FrameBuffer* source, FrameBuffer* target, uint quad, IndexBuffer* indices)
		{
			target->bind();
			glActiveTexture(GL_TEXTURE0);
			source->getTexture()->bind();

			glBindVertexArray(quad);
			indices->bind();

			for (PostFXPass* pass : m_Passes)
				pass->RenderPass(target);

			indices->unbind();
			glBindVertexArray(0);
		}

	}

}