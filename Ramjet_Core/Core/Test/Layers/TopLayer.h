#pragma once

#include "../../Rendering/Renderer/Layers/Layer.h"
#include "../../Rendering/Renderer/Batch2DRenderer.h"

using namespace Core::Rendering;

namespace Core {

	namespace Tests {
	
		class TopLayer : public Layer
		{
		public:
			TopLayer(Shader* shader);
			~TopLayer();
		};

	}

}

