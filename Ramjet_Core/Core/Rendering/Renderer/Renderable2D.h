#pragma once

#include "Buffers/Buffers.h"
#include "Shader/Shader.h"
#include "Renderer2D.h"
#include "Texture/Texture.h"

#include <Utils/Maths/maths.h>

using namespace Utils;

namespace Core {

	namespace Rendering {

		struct VertexData {
			Maths::vec3 vertex;
			Maths::vec2 uv;
			float tid;
			unsigned int color;
		};
	
		class Renderable2D {

		protected:
			Maths::vec3 m_Position;
			Maths::vec2 m_Size;
			Maths::vec4 m_Color;
			std::vector<Maths::vec2> m_UV;
			Texture* m_Texture;

		protected:
			Renderable2D() { setUVDefault();  }

		public:
			Renderable2D(Maths::vec3 position, Maths::vec2 size, Maths::vec4 color)
				: m_Position(position), m_Size(size), m_Color(color)
			{
				setUVDefault();
			}

			virtual ~Renderable2D() {

			}

			virtual void submit(Renderer2D* renderer) const 
			{
				renderer->submit(this);
			}

			inline const Maths::vec3& getPosition() const { return m_Position; }
			inline const Maths::vec2& getSize() const { return m_Size; }
			inline const Maths::vec4& getColor() const { return m_Color; }
			inline const std::vector<Maths::vec2>& getUV() const { return m_UV; }
			// Return texture ID if texture is not nullptr
			inline const GLuint getTextureID() const { return m_Texture == nullptr ? 0 : m_Texture->getID(); }

		private:

			void setUVDefault() 
			{
				m_UV.push_back(Maths::vec2(0, 0));
				m_UV.push_back(Maths::vec2(0, 1));
				m_UV.push_back(Maths::vec2(1, 1));
				m_UV.push_back(Maths::vec2(1, 0));			
			}

		};

	}

}