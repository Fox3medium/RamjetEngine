#pragma once

#include <Utils/String.h>
#include <Utils/types.h>

using namespace Utils;

namespace Core {

	namespace Rendering {

		enum class CORE_API TextureWrap 
		{
			REPEAT				= 0x2901,		//GL_REPEAT,
			CLAMP				= 0x2900,		//GL_CLAMP,
			MIRRORED_REPEAT		= 0x8370,		//GL_MIRRORED_REPEAT,
			CLAMP_TO_EDGE		= 0x812F,		//GL_CLAMP_TO_EDGE,
			CLAMP_TO_BORDER		= 0x812D  		//GL_CLAMP_TO_BORDER
		};

		enum class CORE_API TextureFilter
		{
			LINEAR = 0x2601,	// GL_LINEAR,
			NEAREST = 0x2600 	// GL_NEAREST
		};
	
		class CORE_API Texture
		{

		private:
			String m_Name;
			String m_FileName;
			uint m_TextureID;
			uint m_Width, m_Height;
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
			inline const uint getID() const { return m_TextureID; }
			inline const uint getWidth() const { return m_Width; }
			inline const uint getHeight() const { return m_Height; }

		private:
			uint load();
					   
		};

	}

}

