#include "Sprite.h"

using namespace Utils;

namespace Core {

	namespace Rendering {

			Sprite::Sprite(float x, float y, float width, float height, const vec4& color)
				: Renderable2D(vec3(x, y, 0), vec2(width, height), color)
			{
			}

	}

}