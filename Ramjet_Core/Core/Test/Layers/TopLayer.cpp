#include "TopLayer.h"

namespace Core {

	namespace Tests {

		TopLayer::TopLayer(Shader* shader)
			: Layer(new Batch2DRenderer(), shader, Maths::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f))
		{
		}

		TopLayer::~TopLayer()
		{
		}

	}

}