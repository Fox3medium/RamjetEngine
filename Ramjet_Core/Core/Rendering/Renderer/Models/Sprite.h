#pragma once

#include "../Renderable2D.h"

using namespace Utils;

namespace Core {

	namespace Rendering {

		class Sprite : public Renderable2D
		{			
		private:
			
		public:			
			Sprite(float x, float y, float width, float height, const vec4& color);			
		};

	}

}

