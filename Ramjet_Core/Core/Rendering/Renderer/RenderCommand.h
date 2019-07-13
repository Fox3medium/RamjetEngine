#pragma once

#include "Models/Mesh.h"
#include <Utils/types.h>
#include <vector>

namespace Core 
{
	namespace Rendering 
	{
		struct RendererUniform
		{
			String uniform;
			byte* value;
		};

		struct RenderCommand 
		{
			Mesh* mesh;
			std::vector<RendererUniform> uniform;
		};
	}
}