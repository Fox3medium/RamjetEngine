#pragma once

#include "Buffers/Buffers.h"
#include "Shader/Shader.h"
#include <Utils/Maths/maths.h>

using namespace Utils;

namespace Core {

	namespace Rendering {

		struct VertexData {
			vec3 vertex;
			vec4 color;
		};
	
		class Renderable2D {

		protected:
			vec3 m_Position;
			vec2 m_Size;
			vec4 m_Color;

		public:
			Renderable2D(vec3 position, vec2 size, vec4 color)
				: m_Position(position), m_Size(size), m_Color(color)
			{
			}

			virtual ~Renderable2D() {

			}

			inline const vec3& getPosition() const { return m_Position; }
			inline const vec2& getSize() const { return m_Size; }
			inline const vec4& getColor() const { return m_Color; }

		};

	}

}