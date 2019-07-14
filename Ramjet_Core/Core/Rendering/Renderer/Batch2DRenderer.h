#pragma once

#include <CoreBasicInclude.h>
#include <Core/Common.h>
#include <Utils/types.h>

#include "Renderer2D.h"
#include "Renderable2D.h"

#include "Buffers/VertexArray.h"
#include "Buffers/IndexBuffer.h"
#include "Buffers/FrameBuffer.h"

namespace Core {

	namespace Rendering {
	
		#define RENDERER_MAX_SPRITES	60000
		#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
		#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
		#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6
		#define RENDERER_MAX_TEXTURES	32

		class CORE_API Batch2DRenderer : public Renderer2D {

		private :
			uint m_VAO;
			uint m_VBO;
			IndexBuffer* m_IBO;
			VertexArray* m_VertexArray;
			uint m_IndexCount, m_LineIndexCount;
			IndexBuffer* m_LineIBO;
			VertexData* m_Buffer;
			std::vector<uint> m_TextureSlots;

			FrameBuffer* m_Framebuffer;
			FrameBuffer* m_PostFXBuffer;
			int m_ScreenBuffer;
			Maths::tvec2<uint> m_ViewportSize, m_ScreenSize;
			Shader* m_SimpleShader;
			VertexArray* m_ScreenQuad;

		public:
			Batch2DRenderer(uint width, uint height);
			Batch2DRenderer(const Maths::tvec2<uint>& screenSize);
			~Batch2DRenderer();

			void begin() override;
			void submit(const Renderable2D* renderable) override;
			void drawAABB(const Maths::AABB& aabb, uint color = 0xFFFFFFFF);
			void drawString(const String& text, const Maths::vec3& position, const Font& font = *Manager::Font_Manager::get(), uint color = 0xffffffff) override;
			void fillRect(float x, float y, float width, float height, uint color = 0xffffffff) override;
			void end() override;
			void flush() override;

			inline void setScreenSize(const Maths::tvec2<uint>& size) { m_ScreenSize = size; }
			inline const Maths::tvec2<uint>& getScreenSize() const { return m_ScreenSize; }
			inline void setViewportSize(const Maths::tvec2<uint>& size) { m_ViewportSize = size; }
			inline const Maths::tvec2<uint>& getViewportSize() const { return m_ViewportSize; }

		private:
			void init();
			float submitTexture(uint textureID);
			float submitTexture(const Texture* texture);

		};

	}

}