#pragma once

#include "../Buffers/VertexArray.h"
#include "../Buffers/IndexBuffer.h"
#include <Rendering/Material/Material.h>

namespace Core 
{
	namespace Rendering 
	{
		class Renderer3D;

		struct Vertex 
		{
			Maths::vec3 position;
			Maths::vec3 normal;
			Maths::vec2 uv;
		};

		class Mesh
		{
		private:
			VertexArray* m_VertexArray;
			IndexBuffer* m_IndexBuffer;
			MaterialInstance* m_MaterialInstance;

		public:
			Mesh(VertexArray* vertexArray, IndexBuffer* indexBuffer, MaterialInstance* materialInstance);
			~Mesh();

			inline MaterialInstance* getMaterialInstance() const { return m_MaterialInstance; }

			void render(Renderer3D& renderer);
		};
	}
}