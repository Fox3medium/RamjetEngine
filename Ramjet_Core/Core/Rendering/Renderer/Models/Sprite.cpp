#include "Sprite.h"

using namespace Utils;

namespace Core {

	namespace Rendering {
		Sprite::Sprite(float x, float y, float width, float height, const Maths::vec4& color)
			: Renderable2D(Maths::vec3(x, y, 0), Maths::vec2(width, height), color)
		{
		}
		Sprite::Sprite(float x, float y, float width, float height, Texture* texture)
				: Renderable2D(Maths::vec3(x, y, 0), Maths::vec2(width, height), Maths::vec4(0.6, 0.3, 0.8, 1.0))
			{
				m_Texture = texture;
			}

	}

}