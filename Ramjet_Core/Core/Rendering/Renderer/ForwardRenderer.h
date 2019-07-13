#pragma once

#include <Core/Common.h>
#include "Renderer3D.h"

namespace Core 
{
	namespace Rendering 
	{
		class CORE_API ForwardRenderer : public Renderer3D 
		{
		private:

		public:
			ForwardRenderer();
			void init() override;
			void begin() override;
			void submit(const RenderCommand& command) override;
			void submitMesh(Cameras::Camera* camera, Mesh* mesh, const Maths::mat4& transform) override;
			void end() override;
			void flush() override;

		private:
			void setRequiredUniforms(Shader* shader, const std::vector<RendererUniform>& uniforms);
		};
	}
}