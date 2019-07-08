#pragma once

#include <GLEW/glew.h>
#include <Utils/types.h>

#include "../Texture/Texture.h"

#include <Utils/Maths/vec4.h>
#include <Utils/Maths/tvec2.h>

namespace Core {

	namespace Rendering {

		struct FramebufferData
		{
			uint framebufferID;
			uint depthbufferID;
		};
	
		class FrameBuffer {

		private:			

			Texture* m_Texture;
			FramebufferData m_Data;
			Maths::tvec2<uint> m_Size;
			uint& m_Width;
			uint& m_Height;

			Maths::vec4 m_ClearColor;

		public:
			FrameBuffer(const Maths::tvec2<uint>& size);
			FrameBuffer(uint width, uint height);

			~FrameBuffer();

			void bind();
			void clear();

			inline const Maths::tvec2<uint>& getSize() const { return m_Size; }
			inline const uint getWidth() const { return m_Width; }
			inline const uint getHeight() const { return m_Height; }
			inline const Texture* getTexture() const { return m_Texture; }

			inline void setClearColor(const Maths::vec4& color) { m_ClearColor = color; }

		private:
			void create(uint width, uint height);

		};

	}

}