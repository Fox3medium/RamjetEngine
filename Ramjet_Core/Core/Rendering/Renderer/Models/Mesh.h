#pragma once

#include <Core/Common.h>
#include "../Buffers/VertexArray.h"
#include "../Buffers/IndexBuffer.h"
#include <Rendering/Material/Material.h>
#include "IRenderable.h"

namespace Core 
{
	namespace Rendering 
	{
		class Renderer3D;

		struct CORE_API Vertex 
		{
			Maths::vec3 position;
			Maths::vec3 normal;
			Maths::vec2 uv;
		};

		class CORE_API Mesh : public IRenderable
		{
		private:
			VertexArray* m_VertexArray;
			IndexBuffer* m_IndexBuffer;
			MaterialInstance* m_MaterialInstance;

		public:
			Mesh(VertexArray* vertexArray, IndexBuffer* indexBuffer, MaterialInstance* materialInstance);
			~Mesh();

			inline MaterialInstance* getMaterialInstance() const { return m_MaterialInstance; }
			inline void setMaterial(MaterialInstance* material) { m_MaterialInstance = material; }

			void render(Renderer3D& renderer) override;
		};
	}
}