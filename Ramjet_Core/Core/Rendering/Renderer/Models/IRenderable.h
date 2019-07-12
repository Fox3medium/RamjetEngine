#pragma once

namespace Core 
{
	namespace Rendering 
	{
		class Renderer3D;

		class IRenderable
		{
		public:
			virtual void render(Renderer3D& renderer) = 0;
		};
	}
}