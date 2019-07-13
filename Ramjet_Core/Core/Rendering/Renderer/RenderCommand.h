#pragma once

#include <Core/Common.h>

#include "Models/Mesh.h"

namespace Core 
{
	namespace Rendering 
	{
		struct CORE_API RendererUniform
		{
			String uniform;
			byte* value;
		};

		struct CORE_API RenderCommand 
		{
			Mesh* mesh;
			std::vector<RendererUniform> uniforms;
		};
	}
}