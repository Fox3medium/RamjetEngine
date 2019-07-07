#include "Texture.h"

namespace Core {

	namespace Rendering {

		TextureWrap Texture::m_WrapMode = REPEAT;

		Texture::Texture(const String& fileName)
			: m_FileName(fileName), m_Name(fileName)
		{
			m_TextureID = load();
		}
	
		Texture::Texture(const String& name,const String& fileName)
			: m_FileName(fileName), m_Name(name)
		{
			m_TextureID = load();
		}

		Texture::~Texture()
		{
			glDeleteTextures(1, &m_TextureID);
		}

		void Texture::bind() const
		{
			glBindTexture(GL_TEXTURE_2D, m_TextureID);
		}

		void Texture::unbind() const
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		GLuint Texture::load()
		{
			BYTE* pixels = load_image(m_FileName, &m_Width, &m_Height, &m_Bits);

			GLuint result;
			glGenTextures(1, &result);
			glBindTexture(GL_TEXTURE_2D, result);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLuint)m_WrapMode);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLuint)m_WrapMode);

			if (m_Bits != 24 && m_Bits != 32)
				CORE_ERROR("[TEXTURE] unsupporred image bit depth! %d", m_Bits);

			GLint internalFormat = m_Bits == 32 ? GL_RGBA : GL_RGB;
			GLenum format = m_Bits == 32 ? GL_BGRA : GL_BGR;

			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, pixels);
			glBindTexture(GL_TEXTURE_2D, 0);

			delete[] pixels;

			return result;
		}

	}

}
