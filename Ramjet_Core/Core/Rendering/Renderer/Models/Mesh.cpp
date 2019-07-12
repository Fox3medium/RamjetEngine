#include "Mesh.h"
#include <Rendering/Material/Material.h>

#include "../Renderer3D.h"

namespace Core 
{
	namespace Rendering 
	{

		Mesh::Mesh(VertexArray* vertexArray, IndexBuffer* indexBuffer, MaterialInstance* materialInstance)
			: m_VertexArray(vertexArray), m_IndexBuffer(indexBuffer), m_MaterialInstance(materialInstance)
		{
		}

		Mesh::~Mesh()
		{
			delete m_VertexArray;
			delete m_MaterialInstance;
			delete m_IndexBuffer;
		}

		void Mesh::render(Renderer3D& renderer)
		{
			m_MaterialInstance->bind();

			m_VertexArray->bind();
			m_IndexBuffer->bind();
			m_VertexArray->draw(m_IndexBuffer->getCount());
			m_IndexBuffer->unbind();
			m_VertexArray->unbind();

			m_MaterialInstance->unbind();
		}

	}
}


