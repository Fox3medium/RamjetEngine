#include <CoreBasicInclude.h>
#include "FrameBuffer.h"

#include <Rendering/Platform/CoreRenderAPI.h>

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
			API::freeFramebuffers(m_Data.framebufferID, m_Data.depthbufferID);
			delete m_Texture;	
		}

		void FrameBuffer::bind()
		{
			API::bindFramebuffer(GL_FRAMEBUFFER, m_Data.framebufferID);
			API::setViewport(0, 0, m_Width, m_Height);
		}

		void FrameBuffer::clear()
		{
			//NOT FUNCTIONAL?!
			API::setClearColor(m_ClearColor.x, m_ClearColor.y, m_ClearColor.z, m_ClearColor.w);
			API::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void FrameBuffer::create(uint width, uint height)
		{
			m_Data.framebufferID = API::createFramebuffer();
			m_Data.depthbufferID = API::createRenderbuffer();

			Texture::setFilter(TextureFilter::LINEAR);
			m_Texture = new Texture(width, height);

			API::bindRenderbuffer(GL_RENDERBUFFER, m_Data.depthbufferID);
			API::renderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);

			API::bindFramebuffer(GL_FRAMEBUFFER, m_Data.framebufferID);
			API::framebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Texture->getID(), 0);
			API::framebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_Data.depthbufferID);
		}

	}

}