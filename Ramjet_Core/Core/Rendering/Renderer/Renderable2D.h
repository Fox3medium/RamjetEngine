#pragma once

#include "Buffers/Buffers.h"
#include "Shader/Shader.h"
#include <Utils/Maths/maths.h>

using namespace Utils;

namespace Core {

	namespace Rendering {
	
		class Renderable2D {

		protected:
			vec3 m_Position;
			vec2 m_Size;
			vec4 m_Color;

			Shader& m_Shader;

			VertexArray* m_VertexArray; //VAO
			IndexBuffer* m_IndexBuffer; //IBO

		public:
			Renderable2D(vec3 position, vec2 size, vec4 color, Shader& shader)
				: m_Position(position), m_Size(size), m_Color(color), m_Shader(shader)
			{
				m_VertexArray = new VertexArray();

				GLfloat vertices[] = {
					0, 0, 0,
					0, size.y, 0,
					size.x, size.y, 0,
					size.x, 0, 0
				};

				GLfloat colors[] = {
					color.x, color.y, color.z, color.w,
					color.x, color.y, color.z, color.w,
					color.x, color.y, color.z, color.w,
					color.x, color.y, color.z, color.w
				};

				m_VertexArray->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
				m_VertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 1);

				GLuint indices[] = { 0, 1, 2, 2, 3, 0 };
				m_IndexBuffer = new IndexBuffer(indices, 6);
			}

			virtual ~Renderable2D() {
				delete m_VertexArray;
				delete m_IndexBuffer;
			}

			inline const VertexArray* getVAO() const { return m_VertexArray; }
			inline const IndexBuffer* getIBO() const { return m_IndexBuffer; }

			inline Shader& getShader() const { return m_Shader; }

			inline const vec3& getPosition() const { return m_Position; }
			inline const vec2& getSize() const { return m_Size; }
			inline const vec4& getColor() const { return m_Color; }

		};

	}

}