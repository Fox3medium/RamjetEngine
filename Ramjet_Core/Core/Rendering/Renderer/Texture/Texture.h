#pragma once

#include <Utils/Log.h>
#include <GLEW/glew.h>

#include <FreeImage/FreeImage.h>

#include <iostream>


//#include <Utils/String.h>
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
			std::string m_Name;
			std::string m_FileName;
			GLuint m_TextureID;
			GLsizei m_Width, m_Height;
			unsigned int m_Bits;

			static TextureWrap m_WrapMode;

		public:
			Texture(uint width, uint height);
			Texture(const std::string& fileName);
			Texture(const std::string& name, const std::string& fileName);
			~Texture();
			void bind() const;
			void unbind() const;

			inline static void setWrap(TextureWrap mode) { m_WrapMode = mode; }

			inline const std::string& getName() const { return m_Name; }
			inline const unsigned int getID() const { return m_TextureID; }
			inline const unsigned int getWidth() const { return m_Width; }
			inline const unsigned int getHeight() const { return m_Height; }

		private:
			GLuint load();
					   
		};

	}

}

