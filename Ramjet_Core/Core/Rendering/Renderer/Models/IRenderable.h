#pragma once

#include <Core/Common.h>

namespace Core 
{
	namespace Rendering 
	{
		class Renderer3D;

		class CORE_API IRenderable
		{
		public:
			virtual void render(Renderer3D& renderer) = 0;
		};
	}
}