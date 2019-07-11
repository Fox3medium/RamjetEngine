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

		enum class TextureWrap 
		{
			REPEAT				= GL_REPEAT,
			CLAMP				= GL_CLAMP,
			MIRRORED_REPEAT		= GL_MIRRORED_REPEAT,
			CLAMP_TO_EDGE		= GL_CLAMP_TO_EDGE,
			CLAMP_TO_BORDER		= GL_CLAMP_TO_BORDER
		};

		enum class TextureFilter
		{
			LINEAR = GL_LINEAR,
			NEAREST = GL_NEAREST
		};
	
		class Texture
		{

		private:
			String m_Name;
			String m_FileName;
			GLuint m_TextureID;
			GLsizei m_Width, m_Height;
			unsigned int m_Bits;

			static TextureWrap s_WrapMode;
			static TextureFilter s_Filter;

		public:
			Texture(uint width, uint height, uint bits = 24);
			Texture(const String& fileName);
			Texture(const String& name, const String& fileName);
			~Texture();
			void bind() const;
			void unbind() const;

			inline static void setWrap(TextureWrap mode) { s_WrapMode = mode; }
			inline static void setFilter(TextureFilter filter) { s_Filter = filter; }

			inline const String& getName() const { return m_Name; }
			inline const unsigned int getID() const { return m_TextureID; }
			inline const unsigned int getWidth() const { return m_Width; }
			inline const unsigned int getHeight() const { return m_Height; }

		private:
			GLuint load();
					   
		};

	}

}

