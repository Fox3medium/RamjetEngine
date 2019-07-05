#include "Sprite.h"

using namespace Utils;

namespace Core {

	namespace Rendering {
		Sprite::Sprite(float x, float y, float width, float height, const unsigned int color)
			: Renderable2D(Maths::vec3(x, y, 0), Maths::vec2(width, height), color), position(m_Position)
		{
		}
		Sprite::Sprite(float x, float y, float width, float height, Texture* texture)
				: Renderable2D(Maths::vec3(x, y, 0), Maths::vec2(width, height), 0xBD92DFFF), position(m_Position)
			{
				m_Texture = texture;
			}

		void Sprite::setPosition(float x, float y, float z)
		{
			position = Maths::vec3(x, y, z);
		}

		void Sprite::setPosition(const Maths::vec3& vect)
		{
			position = vect;
		}

	}

}