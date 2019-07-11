#include "FrameBuffer.h"

namespace Core {

	namespace Rendering {

		FrameBuffer::FrameBuffer(const Maths::tvec2<uint>& size)
			: m_Size(size), m_Width(m_Size.x), m_Height(m_Size.y), m_ClearColor(Maths::vec4(0.0f, 0.0f, 0.0f, 1.0f))
		{
			create(m_Width, m_Height);
		}

		FrameBuffer::FrameBuffer(uint width, uint height)
			: m_Size(width, height), m_Width(m_Size.x), m_Height(m_Size.y), m_ClearColor(Maths::vec4(0.0f, 0.0f, 0.0f, 1.0f))
		{
			create(width, height);
		}

		FrameBuffer::~FrameBuffer()
		{
			// GPU -> MEMORY LEAK TODO RESOLVE
			glDeleteFramebuffers(1, &m_Data.framebufferID);
			// SHOULD NOT BE REQUIRED
			glDeleteRenderbuffers(1, &m_Data.depthbufferID);
			delete m_Texture;	
		}

		void FrameBuffer::bind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_Data.framebufferID);
			glViewport(0, 0, m_Width, m_Height);
		}

		void FrameBuffer::clear()
		{
			//NOT FUNCTIONAL?!
			glClearColor(m_ClearColor.x, m_ClearColor.y, m_ClearColor.z, m_ClearColor.w);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void FrameBuffer::create(uint width, uint height)
		{
			glGenFramebuffers(1, &m_Data.framebufferID);
			glGenRenderbuffers(1, &m_Data.depthbufferID);

			Texture::setFilter(TextureFilter::LINEAR);
			m_Texture = new Texture(width, height);

			glBindRenderbuffer(GL_RENDERBUFFER, m_Data.depthbufferID);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);

			glBindFramebuffer(GL_FRAMEBUFFER, m_Data.framebufferID);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Texture->getID(), 0);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_Data.depthbufferID);
			GLenum error = glGetError();
			if (error != GL_NO_ERROR)
				std::cout << "OpenGL Error: " << error << std::endl;
		}

	}

}