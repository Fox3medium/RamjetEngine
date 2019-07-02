#pragma once

#include <GLEW/glew.h>

#include <FreeImage/FreeImage.h>

#include <Utils/String.h>
#include <Utils/ImageLoader.h>

using namespace Utils;

namespace Core {

	namespace Rendering {
	
		class Texture
		{

		private:
			String m_FileName;
			GLuint m_TextureID;
			GLsizei m_Width, m_Height;

		public:
			Texture(const String& fileName);
			~Texture();
			void bind() const;
			void unbind() const;

			inline const unsigned int getWidth() const { return m_Width; }
			inline const unsigned int getHeight() const { return m_Height; }

		private:
			GLuint load();
					   
		};

	}

}

