#include "PostFXPass.h"
#include <CoreBasicInclude.h>
#include <Rendering/Platform/CoreRenderAPI.h>

namespace Core {

	namespace Rendering {

		PostFXPass::PostFXPass(Shader* shader)
			: m_Shader(shader)
		{
			m_Shader->enable();
			m_Shader->setUniform1i("tex", 0);
			m_Shader->disable();
		}

		PostFXPass::~PostFXPass()
		{			
		}

		void PostFXPass::RenderPass(FrameBuffer* target)
		{
			m_Shader->enable();
			m_Shader->setUniformMat4("pr_matrix", Maths::mat4::Orthographic(0, target->getWidth(), target->getHeight(), 0, -1.0f, 1.0f));
			API::drawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
			m_Shader->disable();
		}

	}
}