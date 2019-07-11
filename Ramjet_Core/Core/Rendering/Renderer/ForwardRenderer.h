#pragma once

#include "Renderer3D.h"

namespace Core 
{
	namespace Rendering 
	{
		class ForwardRenderer : public Renderer3D 
		{
		private:

		public:
			ForwardRenderer();
			void init() override;
			void begin() override;
			void submit(Mesh* mesh) override;
			void end() override;
			void flush() override;
		};
	}
}