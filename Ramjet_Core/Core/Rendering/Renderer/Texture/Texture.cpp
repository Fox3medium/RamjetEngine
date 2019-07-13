#include "Texture.h"
#include <CoreBasicInclude.h>

#include <GLEW/glew.h>
#include <Utils/Log.h>
#include <FreeImage/FreeImage.h>
#include <Utils/ImageLoader.h>
#include <Rendering/Platform/CoreRenderAPI.h>

namespace Core {

	namespace Rendering {

		TextureWrap Texture::s_WrapMode = TextureWrap::REPEAT;
		TextureFilter Texture::s_Filter = TextureFilter::LINEAR;

		Texture::Texture(uint width, uint height, uint bits)
			: m_Width(width), m_Height(height), m_FileName("NULL"), m_Name("Name"), m_Bits(bits)
		{
			m_TextureID = load();
		}

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
			API::freeTexture(m_TextureID);
		}

		void Texture::bind() const
		{
			API::bindTexture(GL_TEXTURE_2D, m_TextureID);
		}

		void Texture::unbind() const
		{
			API::unbindTexture(GL_TEXTURE_2D);
		}

		GLuint Texture::load()
		{
			BYTE* pixels = nullptr;

			if (m_FileName != "NULL")
				pixels = load_image(m_FileName.c_str(), &m_Width, &m_Height, &m_Bits);

			/*GLuint result;
			glGenTextures(1, &result);
			glBindTexture(GL_TEXTURE_2D, result);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLint) s_Filter);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLint) s_Filter);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLuint)s_WrapMode);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLuint)s_WrapMode);*/
			uint result = API::createTexture();
			API::bindTexture(GL_TEXTURE_2D, result);
			API::setTextureParameter(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (int)s_Filter);
			API::setTextureParameter(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (int)s_Filter);
			API::setTextureParameter(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (int)s_WrapMode);
			API::setTextureParameter(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (int)s_WrapMode);

			if (m_Bits != 24 && m_Bits != 32)
				CORE_ERROR("[TEXTURE] unsupporred image bit depth! %d on file ", m_Bits, " '",m_FileName.c_str(),"'!");

			int internalFormat = m_Bits == 32 ? GL_RGBA : GL_RGB;
			uint format = m_Bits == 32 ? GL_BGRA : GL_BGR;

			// If the image format is not a multiple of 4 it require GL_UNPACK_ALIGNMENT to 1 for it to be loaded
			if (m_Width % 4 != 0) 
			{
				glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
				CORE_WARN("[TEXTURE] Mmage format is not a multiple of 4 it require GL_UNPACK_ALIGNMENT to 1 for it to be loaded ", m_FileName.c_str());
			}
			/*glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, pixels ? pixels : NULL);
			glBindTexture(GL_TEXTURE_2D, 0);*/
			API::setTextureData(GL_TEXTURE_2D, internalFormat, m_Width, m_Height, format, GL_UNSIGNED_BYTE, pixels ? pixels : NULL);
			API::unbindTexture(GL_TEXTURE_2D);
			if(pixels != nullptr)
				delete[] pixels;

			return result;
		}

	}

}
