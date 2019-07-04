#include "Sprite.h"

using namespace Utils;

namespace Core {

	namespace Rendering {
		Sprite::Sprite(float x, float y, float width, float height, const unsigned int color)
			: Renderable2D(Maths::vec3(x, y, 0), Maths::vec2(width, height), color)
		{
		}
		Sprite::Sprite(float x, float y, float width, float height, Texture* texture)
				: Renderable2D(Maths::vec3(x, y, 0), Maths::vec2(width, height), 0xBD92DFFF)
			{
				m_Texture = texture;
			}

	}

}