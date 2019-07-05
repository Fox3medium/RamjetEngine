#pragma once

#include <GLEW/glew.h>

#include <FreeImage/FreeImage.h>

#include <iostream>
#include <Utils/Log.h>


#include <Utils/String.h>
#include <Utils/ImageLoader.h>

using namespace Utils;

namespace Core {

	namespace Rendering {
	
		class Texture
		{

		private:
			String m_Name, m_FileName;
			GLuint m_TextureID;
			GLsizei m_Width, m_Height;
			unsigned int m_Bits;

		public:
			Texture(const String& fileName);
			Texture(const String& mname, const String& fileName);
			~Texture();
			void bind() const;
			void unbind() const;

			inline const String getName() const { return m_Name; }
			inline const unsigned int getID() const { return m_TextureID; }
			inline const unsigned int getWidth() const { return m_Width; }
			inline const unsigned int getHeight() const { return m_Height; }

		private:
			GLuint load();
					   
		};

	}

}

