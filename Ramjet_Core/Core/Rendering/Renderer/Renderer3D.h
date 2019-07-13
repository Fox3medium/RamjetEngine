#pragma once

#include "RenderCommand.h"
#include "../Camera/Camera.h"

#include "Models/Mesh.h"

namespace Core 
{
	namespace Rendering 
	{
		//typedef std::vector<RenderCommand> CommandQueue;

		class CORE_API Renderer3D
		{
		protected:
			std::vector<RenderCommand> m_CommandQueue;

		public:
			virtual void init() = 0;
			virtual void begin() = 0;
			virtual void submit(const RenderCommand& command) = 0;
			virtual void submitMesh(Cameras::Camera* camera, Mesh* mesh, const Maths::mat4& transform) = 0;
			virtual void end() = 0;
			virtual void flush() = 0;
		};
	}
}