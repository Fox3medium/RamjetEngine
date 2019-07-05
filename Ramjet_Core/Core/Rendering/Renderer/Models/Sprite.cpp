#include "Sprite.h"

using namespace Utils;

namespace Core {

	namespace Rendering {
		Sprite::Sprite(Texture* texture)
			: Renderable2D(Maths::vec3(0, 0, 0), Maths::vec2(texture->getWidth(), texture->getHeight()), 0xBD92DFFF), position(m_Position), size(m_Size)
		{
		}

		Sprite::Sprite(float x, float y, float width, float height, const unsigned int color)
			: Renderable2D(Maths::vec3(x, y, 0), Maths::vec2(width, height), color), position(m_Position), size(m_Size)
		{
		}

		Sprite::Sprite(float x, float y, float width, float height, Maths::vec4 color)
			: Renderable2D(Maths::vec3(x, y, 0), Maths::vec2(width, height), 0), position(m_Position), size(m_Size)
		{
			setColor(color);
		}

		Sprite::Sprite(float x, float y, float width, float height, Texture* texture)
			: Renderable2D(Maths::vec3(x, y, 0), Maths::vec2(width, height), 0xBD92DFFF), position(m_Position), size(m_Size)
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

		void Sprite::setUV(std::vector<Maths::vec2> uv)
		{
			m_UV = uv;
		}

	}

}