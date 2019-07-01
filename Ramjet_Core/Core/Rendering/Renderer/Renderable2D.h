#pragma once

#include "Buffers/Buffers.h"
#include "Shader/Shader.h"
#include <Utils/Maths/maths.h>

using namespace Utils;

namespace Core {

	namespace Rendering {

		struct VertexData {
			Maths::vec3 vertex;
			Maths::vec4 color;
		};
	
		class Renderable2D {

		protected:
			Maths::vec3 m_Position;
			Maths::vec2 m_Size;
			Maths::vec4 m_Color;

		public:
			Renderable2D(Maths::vec3 position, Maths::vec2 size, Maths::vec4 color)
				: m_Position(position), m_Size(size), m_Color(color)
			{
			}

			virtual ~Renderable2D() {

			}

			inline const Maths::vec3& getPosition() const { return m_Position; }
			inline const Maths::vec2& getSize() const { return m_Size; }
			inline const Maths::vec4& getColor() const { return m_Color; }

		};

	}

}