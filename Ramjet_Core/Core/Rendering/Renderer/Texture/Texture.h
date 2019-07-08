#pragma once

#include <Utils/Log.h>
#include <GLEW/glew.h>

#include <FreeImage/FreeImage.h>

#include <iostream>


#include <Utils/String.h>
#include <Utils/ImageLoader.h>
#include <Utils/types.h>

using namespace Utils;

namespace Core {

	namespace Rendering {

		enum TextureWrap 
		{
			REPEAT				= GL_REPEAT,
			CLAMP				= GL_CLAMP,
			MIRRORED_REPEAT		= GL_MIRRORED_REPEAT,
			CLAMP_TO_EDGE		= GL_CLAMP_TO_EDGE,
			CLAMP_TO_BORDER		= GL_CLAMP_TO_BORDER
		};
	
		class Texture
		{

		private:
			String m_Name, m_FileName;
			GLuint m_TextureID;
			GLsizei m_Width, m_Height;
			unsigned int m_Bits;

			static TextureWrap m_WrapMode;

		public:
			Texture(uint width, uint height);
			Texture(const String& fileName);
			Texture(const String& name, const String& fileName);
			~Texture();
			void bind() const;
			void unbind() const;

			inline static void setWrap(TextureWrap mode) { m_WrapMode = mode; }

			inline const String getName() const { return m_Name; }
			inline const unsigned int getID() const { return m_TextureID; }
			inline const unsigned int getWidth() const { return m_Width; }
			inline const unsigned int getHeight() const { return m_Height; }

		private:
			GLuint load();
					   
		};

	}

}

