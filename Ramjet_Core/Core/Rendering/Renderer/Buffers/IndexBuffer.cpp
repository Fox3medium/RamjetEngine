#include "IndexBuffer.h"

#include <CoreBasicInclude.h>
#include <Rendering/Platform/CoreRenderAPI.h>

namespace Core {

	namespace Rendering {

		IndexBuffer::IndexBuffer(short* data, uint count)
			: m_Count(count)
		{
			/*glGenBuffers(1, &m_BufferID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);*/
			m_Buffer = new API::Buffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
			m_Buffer->bind();
			m_Buffer->setData(count * sizeof(short), data);
			m_Buffer->unbind();

		}

		IndexBuffer::IndexBuffer(uint* data, uint count)
			: m_Count(count)
		{
			m_Buffer = new API::Buffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
			m_Buffer->bind();
			m_Buffer->setData(count * sizeof(uint), data);
			m_Buffer->unbind();
		}


		IndexBuffer::~IndexBuffer()
		{
			//glDeleteBuffers(1, &m_BufferID);
			API::freeBuffer(m_Buffer->id);
			delete m_Buffer;
		}

		void IndexBuffer::bind() const
		{
			m_Buffer->bind();
		}

		void IndexBuffer::unbind() const
		{
			m_Buffer->unbind();
		}

	}

}