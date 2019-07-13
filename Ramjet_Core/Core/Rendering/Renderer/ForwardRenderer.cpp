#include <CoreBasicInclude.h>
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
			m_CommandQueue.clear();
		}

		void ForwardRenderer::submit(const RenderCommand& command)
		{
			m_CommandQueue.push_back(command);
		}

		void ForwardRenderer::submitMesh(Cameras::Camera* camera, Mesh* mesh, const Maths::mat4& transform)
		{
			RendererUniform pr_matrix;
			pr_matrix.uniform = SHADER_UNIFORM_PROJECTION_MATRIX_NAME;
			pr_matrix.value = (byte*)& camera->getProjectionMatrix();

			RendererUniform vw_matrix;
			vw_matrix.uniform = SHADER_UNIFORM_VIEW_MATRIX_NAME;
			vw_matrix.value = (byte*)& camera->getViewMatrix();

			RendererUniform ml_matrix;
			ml_matrix.uniform = SHADER_UNIFORM_MODEL_MATRIX_NAME;
			ml_matrix.value = (byte*)& transform;

			RenderCommand command;
			command.mesh = mesh;
			command.uniforms.push_back(pr_matrix);
			command.uniforms.push_back(vw_matrix);
			command.uniforms.push_back(ml_matrix);
			m_CommandQueue.push_back(command);
		}

		void ForwardRenderer::end()
		{

		}

		void ForwardRenderer::flush()
		{
			for (uint i = 0; i < m_CommandQueue.size(); i++)
			{
				const RenderCommand& command = m_CommandQueue[i];
				command.mesh->getMaterialInstance()->getMaterial()->getShader()->enable();
				setRequiredUniforms(command.mesh->getMaterialInstance()->getMaterial()->getShader(), command.uniforms);
				command.mesh->render(*this);
			}
		}

		void ForwardRenderer::setRequiredUniforms(Shader* shader, const std::vector<RendererUniform>& uniforms)
		{
			for (uint i = 0; i < uniforms.size(); i++)
				shader->setUniform(uniforms[i].uniform, uniforms[i].value);
		}

	}
}