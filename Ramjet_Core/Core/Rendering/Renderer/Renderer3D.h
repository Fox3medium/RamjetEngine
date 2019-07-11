#pragma once

#include <Rendering/Platform/CoreRenderAPI.h>

#include "Models/Mesh.h"

namespace Core 
{
	namespace Rendering 
	{
		class Renderer3D
		{
		protected:
			std::vector<Mesh*> m_DrawQueue;

		public:
			virtual void init() = 0;
			virtual void begin() = 0;
			virtual void submit(Mesh* mesh) = 0;
			virtual void end() = 0;
			virtual void flush() = 0;
		};
	}
}