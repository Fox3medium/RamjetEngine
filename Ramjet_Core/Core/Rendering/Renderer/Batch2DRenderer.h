#pragma once

#include "Renderer2D.h"
#include "Buffers/IndexBuffer.h"

namespace Core {

	namespace Rendering {
	
		#define RENDERER_MAX_SPRITES	60000
		#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
		#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
		#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
		#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6

		#define SHADER_VERTEX_INDEX		0
		#define SHADER_COLOR_INDEX		1

		class Batch2DRenderer : public Renderer2D {

		private :
			GLuint m_VAO;
			GLuint m_VBO;
			IndexBuffer* m_IBO;
			GLsizei m_IndexCount;
			VertexData* m_Buffer;

		public:
			Batch2DRenderer();
			~Batch2DRenderer();

			void begin();
			void submit(const Renderable2D* renderable) override;
			void end();
			void flush() override;

		private:
			void init();

		};

	}

}