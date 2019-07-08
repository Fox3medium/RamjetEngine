#pragma once

#include <Utils/Log.h>
#include <Utils/types.h>
#include <cstddef>
#include "Renderer2D.h"
#include "Renderable2D.h"
#include "Buffers/IndexBuffer.h"
#include "Buffers/FrameBuffer.h"

namespace Core {

	namespace Rendering {
	
		#define RENDERER_MAX_SPRITES	60000
		#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
		#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
		#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6
		#define RENDERER_MAX_TEXTURES	32

		enum class RenderTarget
		{
			SCREEN = 0,
			BUFFER = 1
		};

		class Batch2DRenderer : public Renderer2D {

		private :
			GLuint m_VAO;
			GLuint m_VBO;
			IndexBuffer* m_IBO;
			GLsizei m_IndexCount;
			VertexData* m_Buffer;
			std::vector<GLuint> m_TextureSlots;

			FrameBuffer* m_Framebuffer;
			int m_ScreenBuffer;
			Maths::tvec2<uint> m_ViewportSize, m_ScreenSize;
			Shader* m_SimpleShader;
			uint m_ScreenQuad;
			RenderTarget m_Target;

		public:
			Batch2DRenderer(const Maths::tvec2<uint>& screenSize);
			~Batch2DRenderer();

			void begin() override;
			void submit(const Renderable2D* renderable) override;
			void drawString(const std::string& text, const Maths::vec3& position, const Font& font, unsigned int color) override;
			void end() override;
			void flush() override;

			inline void setScreenSize(const Maths::tvec2<uint>& size) { m_ScreenSize = size; }
			inline const Maths::tvec2<uint>& getScreenSize() const { return m_ScreenSize; }
			inline void setViewportSize(const Maths::tvec2<uint>& size) { m_ViewportSize = size; }
			inline const Maths::tvec2<uint>& getViewportSize() const { return m_ViewportSize; }

			inline void setRenderTarget(RenderTarget target) { m_Target = target; }
			inline const RenderTarget getRenderTarget() const { return m_Target; }

		private:
			void init();
			float submitTexture(uint textureID);
			float submitTexture(const Texture* texture);

		};

	}

}