#include "VertexArray.h"

namespace Core {

	namespace Rendering {

		uint VertexArray::s_CurrentBinding = 0;

		VertexArray::VertexArray()
		{
			m_ArrayID = API::createVertexArray();
		}

		VertexArray::~VertexArray()
		{
			for (uint i = 0; i < m_Buffers.size(); i++)
				delete m_Buffers[i];
			API::freeVertexArray(m_ArrayID);
		}

		API::Buffer* VertexArray::getBuffer(uint index)
		{
			return m_Buffers[index];
		}

		void VertexArray::addBuffer(API::Buffer* buffer)
		{
			CORE_ASSERT(s_CurrentBinding == m_ArrayID);

			m_Buffers.push_back(buffer);

			const std::vector<BufferLayoutType>& layout = buffer->layout.getLayout();
			for (uint i = 0; i < layout.size(); i++)
			{
				API::enableVertexAttribute(i);
				API::setVertexAttributePointer(i,
					layout[i].count, layout[i].type, layout[i].normalized,
					buffer->layout.getStride(), layout[i].offset);
			}
			//bind();
			//buffer->bind();

			//glEnableVertexAttribArray(index);
			//glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);

			//buffer->unbind();
			//unbind();

			//m_Buffers.push_back(buffer);
		}

		void VertexArray::bind() const
		{
			s_CurrentBinding = m_ArrayID;
			API::bindVertexArray(m_ArrayID);
		}

		void VertexArray::unbind() const
		{
			API::unbindVertexArrays();
		}

	}

}