#pragma once

#include <Core/Common.h>
#include "Buffers/Buffer.h"
#include "Buffers/IndexBuffer.h"
#include "Shader/Shader.h"
#include "Renderer2D.h"
#include "Texture/Texture.h"

#include <Utils/types.h>

using namespace Utils;

namespace Core {

	namespace Rendering {

		struct CORE_API VertexData {
			// Vertex point 
			Maths::vec3 vertex;
			// UV of that vertex
			Maths::vec2 uv;
			// UV of the mask
			Maths::vec2 mask_uv;
			// Texture ID
			float tid;
			// Mask ID
			float mid;
			// Color
			uint color;
		};

#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
	
		class CORE_API Renderable2D {

		protected:
			Maths::vec3 m_Position;
			Maths::vec2 m_Size;
			uint m_Color;
			std::vector<Maths::vec2> m_UVs;
			Texture* m_Texture;
			bool m_Visible;

		protected:
			Renderable2D() : m_Texture(nullptr) { m_UVs = getUVDefault();  }

		public:
			Renderable2D(const Maths::vec3 position, const Maths::vec2 size, uint color)
				: m_Position(position), m_Size(size), m_Color(color), m_Texture(nullptr), m_Visible(true)
			{
				m_UVs = getUVDefault();
			}

			virtual ~Renderable2D() {

			}

			virtual void submit(Renderer2D* renderer) const 
			{
				renderer->submit(this);
			}

			void setColor(unsigned int color) { m_Color = color; }
			void setColor(const Maths::vec4& color)
			{
				uint r = color.x * 255.0f;
				uint g = color.y * 255.0f;
				uint b = color.z * 255.0f;
				uint a = color.w * 255.0f;

				m_Color = a << 24 | b << 16 | g << 8 | r;
			}

			inline const Maths::vec3& getPosition() const { return m_Position; }
			inline const Maths::vec2& getSize() const { return m_Size; }
			inline const unsigned int getColor() const { return m_Color; }
			inline const std::vector<Maths::vec2>& getUV() const { return m_UVs; }
			// Return texture ID if texture is not nullptr
			inline const uint getTextureID() const { return m_Texture ? m_Texture->getID() : 0; }
			inline const Texture* getTexture() const { return m_Texture; }

			inline bool isVisible() const { return m_Visible; }
			inline void setVisible(bool visible) { m_Visible = visible; }

			static std::vector<Maths::vec2> getUVDefault() 
			{
				static std::vector<Maths::vec2> results;
				if (!results.size()) 
				{
					results.push_back(Maths::vec2(0, 0));
					results.push_back(Maths::vec2(0, 1));
					results.push_back(Maths::vec2(1, 1));
					results.push_back(Maths::vec2(1, 0));
				}			
				return results;
			}

		};

	}

}