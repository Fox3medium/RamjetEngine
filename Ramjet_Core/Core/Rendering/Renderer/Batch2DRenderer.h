#pragma once

#include <cstddef>
#include "Renderer2D.h"
#include "Renderable2D.h"
#include "Buffers/IndexBuffer.h"

#include <freetype-gl.h>

namespace Core {

	namespace Rendering {
	
		#define RENDERER_MAX_SPRITES	60000
		#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
		#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
		#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
		#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6

		#define SHADER_VERTEX_INDEX		0
		#define SHADER_UV_INDEX			1
		#define SHADER_TEXTURE_INDEX	2
		#define SHADER_COLOR_INDEX		3

		class Batch2DRenderer : public Renderer2D {

		private :
			GLuint m_VAO;
			GLuint m_VBO;
			IndexBuffer* m_IBO;
			GLsizei m_IndexCount;
			VertexData* m_Buffer;
			std::vector<GLuint> m_TextureSlots;

			ftgl::texture_atlas_t* m_FTAtlas;
			ftgl::texture_font_t* m_FTFont;

		public:
			Batch2DRenderer();
			~Batch2DRenderer();

			void begin() override;
			void submit(const Renderable2D* renderable) override;
			void drawString(std::string& text, const Maths::vec3& position, const Maths::vec4& Color) override;
			void end() override;
			void flush() override;

		private:
			void init();

		};

	}

}