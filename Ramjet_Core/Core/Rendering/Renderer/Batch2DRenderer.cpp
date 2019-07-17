#include "Batch2DRenderer.h"

#include <CoreBasicInclude.h>

#include "Buffers/Buffer.h"
#include "Buffers/BufferLayout.h"

#include <Utils/Log.h>
#include <Rendering/Platform/CoreRenderAPI.h>

#include <Managers/Mesh_Manager.h>
#include <Managers/Shader_Manager.h>

#include <Freetype-GL/src/freetype-gl.h>

namespace Core {

	namespace Rendering {
		Batch2DRenderer::Batch2DRenderer(uint width, uint height)
			: m_IndexCount(0), // 3rd to be set 
			m_ScreenSize(Maths::tvec2<uint>(width, height)),  // 2nd to be set
			m_ViewportSize(Maths::tvec2<uint>(width, height)) // 1st to be set
		{
			init();
			m_Mask = nullptr;
		}
		Batch2DRenderer::Batch2DRenderer(const Maths::tvec2<uint>& screenSize)
			: m_IndexCount(0), m_ScreenSize(screenSize), m_ViewportSize(screenSize)
		{
			init();
			m_Mask = nullptr;
		}

		Batch2DRenderer::~Batch2DRenderer()
		{
			delete m_IBO;
			delete m_ScreenQuad;
			API::freeBuffer(m_VBO);
			API::freeVertexArray(m_VAO);
		}

		void Batch2DRenderer::begin()
		{
			if (m_Target == RenderTarget::BUFFER) 
			{
				if (m_ViewportSize != m_Framebuffer->getSize())
				{
					delete m_Framebuffer;
					m_Framebuffer = new FrameBuffer(m_ViewportSize);
					if (m_PostFXEnabled) 
					{
						delete m_PostFXBuffer;
						m_PostFXBuffer = new FrameBuffer(m_ViewportSize);
					}
				}
				if (m_PostFXEnabled) 
				{
					m_PostFXBuffer->bind();
					m_PostFXBuffer->clear();
				}

				m_Framebuffer->bind();
				m_Framebuffer->clear();
				// TODO put this into the OpenGL Renderer file
				glBlendFunc(GL_ONE, GL_ZERO);
			}
			else 
			{				
				API::bindFramebuffer(GL_FRAMEBUFFER, m_ScreenBuffer);
				API::setViewport(0, 0, m_ScreenSize.x, m_ScreenSize.y);
			}
			m_VertexArray->getBuffer()->bind();
			m_Buffer = m_VertexArray->getBuffer()->getPointer<VertexData>();
		}

		void Batch2DRenderer::submit(const Renderable2D* renderable)
		{
			if (!renderable->isVisible())
				return;

			const Maths::vec3& position = renderable->getPosition();
			const Maths::vec2& size = renderable->getSize();
			const uint color = renderable->getColor();
			const std::vector<Maths::vec2>& uv = renderable->getUV();
			const GLuint tid = renderable->getTextureID();

			float textureSlot = 0.0f;

			if (tid > 0)
				textureSlot = submitTexture(renderable->getTexture());

			Maths::mat4 maskTransform = Maths::mat4::Identity();
			const uint mid = m_Mask ? m_Mask->texture->getID() : 0;
			float ms = 0.0f;

			if (m_Mask != nullptr)
			{
				maskTransform = Maths::mat4::Invert(m_Mask->transform);
				ms = submitTexture(m_Mask->texture);
			}

			Maths::vec3 vertex = *m_TransformationBack * position;
			m_Buffer->vertex = vertex;
			m_Buffer->uv = uv[0];
			m_Buffer->mask_uv = maskTransform * vertex;
			m_Buffer->tid = textureSlot;
			m_Buffer->mid = ms;
			m_Buffer->color = color;
			m_Buffer++;

			vertex = *m_TransformationBack * Maths::vec3(position.x, position.y + size.y, position.z);
			m_Buffer->vertex = vertex;
			m_Buffer->uv = uv[1];
			m_Buffer->mask_uv = maskTransform * vertex;
			m_Buffer->tid = textureSlot;
			m_Buffer->mid = ms;
			m_Buffer->color = color;
			m_Buffer++;

			vertex = *m_TransformationBack * Maths::vec3(position.x + size.x, position.y + size.y, position.z);
			m_Buffer->vertex = vertex;
			m_Buffer->uv = uv[2];
			m_Buffer->mask_uv = maskTransform * vertex;
			m_Buffer->tid = textureSlot;
			m_Buffer->mid = ms;
			m_Buffer->color = color;
			m_Buffer++;

			vertex = *m_TransformationBack * Maths::vec3(position.x + size.x, position.y, position.z);
			m_Buffer->vertex = vertex;
			m_Buffer->uv = uv[3];
			m_Buffer->mask_uv = maskTransform * vertex;
			m_Buffer->tid = textureSlot;
			m_Buffer->mid = ms;
			m_Buffer->color = color;
			m_Buffer++;

			m_IndexCount += 6;
		}

		void Batch2DRenderer::drawString(const String& text, const Maths::vec2& position, const Font& font, uint color)
		{
			using namespace ftgl;

			float ts = 0.0f;
			
			ts = submitTexture(font.getID());

			const Maths::vec2& scale = font.getScale();

			float x = position.x;

			texture_font_t* ftFont = font.getFTFont();

			for (uint i = 0; i < text.length(); i++)
			{
				char c = text[i];
				texture_glyph_t* glyph = texture_font_get_glyph(ftFont, c);
				if (glyph)
				{

					if (i > 0)
					{
						float kerning = texture_glyph_get_kerning(glyph, text[i - 1]);
						x += kerning / scale.x;
					}

					float x0 = x + glyph->offset_x / scale.x;
					float y0 = position.y + glyph->offset_y / scale.y;
					float x1 = x0 + glyph->width / scale.x;
					float y1 = y0 - glyph->height / scale.y;

					float u0 = glyph->s0;
					float v0 = glyph->t0;
					float u1 = glyph->s1;
					float v1 = glyph->t1;

					m_Buffer->vertex = *m_TransformationBack * Maths::vec3(x0, y0, 0);
					m_Buffer->uv = Maths::vec2(u0, v0);
					m_Buffer->tid = ts;
					m_Buffer->color = color;
					m_Buffer++;

					m_Buffer->vertex = *m_TransformationBack * Maths::vec3(x0, y1, 0);
					m_Buffer->uv = Maths::vec2(u0, v1);
					m_Buffer->tid = ts;
					m_Buffer->color = color;
					m_Buffer++;

					m_Buffer->vertex = *m_TransformationBack * Maths::vec3(x1, y1, 0);
					m_Buffer->uv = Maths::vec2(u1, v1);
					m_Buffer->tid = ts;
					m_Buffer->color = color;
					m_Buffer++;

					m_Buffer->vertex = *m_TransformationBack * Maths::vec3(x1, y0, 0);
					m_Buffer->uv = Maths::vec2(u1, v0);
					m_Buffer->tid = ts;
					m_Buffer->color = color;
					m_Buffer++;

					m_IndexCount += 6;

					x += glyph->advance_x / scale.x;
				}

			}
		}

		void Batch2DRenderer::drawLine(float x0, float y0, float x1, float y1, float thickness, uint color)
		{
			using namespace Maths;

			const std::vector<vec2>& uv = Renderable2D::getUVDefault();
			float ts = 0.0f;
			mat4 maskTransform = mat4::Identity();
			uint mid = m_Mask ? m_Mask->texture->getID() : 0;

			float ms = 0.0f;
			if (m_Mask != nullptr)
			{
				maskTransform = mat4::Invert(m_Mask->transform);
				ms = submitTexture(m_Mask->texture);
			}

			vec2 normal = vec2(y1 - y0, -(x1 - x0)).Normalise() * thickness;

			vec3 vertex = *m_TransformationBack * vec3(x0 + normal.x, y0 + normal.y, 0.0f);
			m_Buffer->vertex = vertex;
			m_Buffer->uv = uv[0];
			m_Buffer->mask_uv = maskTransform * vertex;
			m_Buffer->tid = ts;
			m_Buffer->mid = ms;
			m_Buffer->color = color;
			m_Buffer++;

			vertex = *m_TransformationBack * vec3(x1 + normal.x, y1 + normal.y, 0.0f);
			m_Buffer->vertex = vertex;
			m_Buffer->uv = uv[1];
			m_Buffer->mask_uv = maskTransform * vertex;
			m_Buffer->tid = ts;
			m_Buffer->mid = ms;
			m_Buffer->color = color;
			m_Buffer++;

			vertex = *m_TransformationBack * vec3(x1 - normal.x, y1 - normal.y, 0.0f);
			m_Buffer->vertex = vertex;
			m_Buffer->uv = uv[2];
			m_Buffer->mask_uv = maskTransform * vertex;
			m_Buffer->tid = ts;
			m_Buffer->mid = ms;
			m_Buffer->color = color;
			m_Buffer++;

			vertex = *m_TransformationBack * vec3(x0 - normal.x, y0 - normal.y, 0.0f);
			m_Buffer->vertex = vertex;
			m_Buffer->uv = uv[3];
			m_Buffer->mask_uv = maskTransform * vertex;
			m_Buffer->tid = ts;
			m_Buffer->mid = ms;
			m_Buffer->color = color;
			m_Buffer++;

			m_IndexCount += 6;
		}

		void Batch2DRenderer::drawLine(const Maths::vec2& start, const Maths::vec2& end, float thickness, uint color)
		{
			drawLine(start.x, start.y, end.x, end.y, thickness, color);
		}

		void Batch2DRenderer::drawRect(float x, float y, float width, float height, uint color)
		{
			drawLine(x, y, x + width, y);
			drawLine(x + width, y, x + width, y + height);
			drawLine(x + width, y + height, x, y + height);
			drawLine(x, y + height, x, y);
		}

		void Batch2DRenderer::drawRect(const Maths::Rectangle& rectangle, uint color)
		{
			drawRect(rectangle.x, rectangle.y, rectangle.width, rectangle.height, color);
		}

		void Batch2DRenderer::fillRect(const Maths::Rectangle& rectangle, uint color)
		{
			fillRect(rectangle.x, rectangle.y, rectangle.width, rectangle.height, color);
		}

		void Batch2DRenderer::fillRect(float x, float y, float width, float height, uint color)
		{
			using namespace Maths;
			vec3 position(x, y, 0.0f);
			vec2 size(width, height);
			const std::vector<vec2>& uv = Renderable2D::getUVDefault();
			float ts = 0.0f;
			mat4 maskTransform = mat4::Identity();
			uint mid = m_Mask ? m_Mask->texture->getID() : 0;

			float ms = 0.0f;
			if (m_Mask != nullptr)
			{
				maskTransform = mat4::Invert(m_Mask->transform);
				ms = submitTexture(m_Mask->texture);
			}

			vec3 vertex = *m_TransformationBack * position;
			m_Buffer->vertex = vertex;
			m_Buffer->uv = uv[0];
			m_Buffer->mask_uv = maskTransform * vertex;
			m_Buffer->tid = ts;
			m_Buffer->mid = ms;
			m_Buffer->color = color;
			m_Buffer++;

			vertex = *m_TransformationBack * vec3(position.x, position.y + size.y, position.z);
			m_Buffer->vertex = vertex;
			m_Buffer->uv = uv[1];
			m_Buffer->mask_uv = maskTransform * vertex;
			m_Buffer->tid = ts;
			m_Buffer->mid = ms;
			m_Buffer->color = color;
			m_Buffer++;

			vertex = *m_TransformationBack * vec3(position.x + size.x, position.y + size.y, position.z);
			m_Buffer->vertex = vertex;
			m_Buffer->uv = uv[2];
			m_Buffer->mask_uv = maskTransform * vertex;
			m_Buffer->tid = ts;
			m_Buffer->mid = ms;
			m_Buffer->color = color;
			m_Buffer++;

			vertex = *m_TransformationBack * vec3(position.x + size.x, position.y, position.z);
			m_Buffer->vertex = vertex;
			m_Buffer->uv = uv[3];
			m_Buffer->mask_uv = maskTransform * vertex;
			m_Buffer->tid = ts;
			m_Buffer->mid = ms;
			m_Buffer->color = color;
			m_Buffer++;

			m_IndexCount += 6;
		}

		void Batch2DRenderer::end()
		{
			m_VertexArray->getBuffer()->releasePointer();
			m_VertexArray->getBuffer()->unbind();
		}

		void Batch2DRenderer::flush()
		{
			glDepthFunc(GL_NEVER);
			glDisable(GL_DEPTH_TEST);

			for (uint i = 0; i < m_TextureSlots.size(); i++)
			{
				API::setActiveTexture(GL_TEXTURE0 + i);
				API::bindTexture(GL_TEXTURE_2D, m_TextureSlots[i]);
			}

			m_VertexArray->bind();
			m_IBO->bind();

			API::drawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL);

			m_IBO->unbind();
			m_VertexArray->unbind();

			m_IndexCount = 0;
			m_TextureSlots.clear();

			if (m_Target == RenderTarget::BUFFER) 
			{
				if (m_PostFXEnabled)
					m_PostFX->RenderPostFX(m_Framebuffer, m_PostFXBuffer, m_ScreenQuad, m_IBO);
				// Display Framebuffer
				API::bindFramebuffer(GL_FRAMEBUFFER, m_ScreenBuffer);
				API::setViewport(0, 0, m_ScreenSize.x, m_ScreenSize.y);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				m_SimpleShader->enable();

				API::setActiveTexture(GL_TEXTURE0);
				if (m_PostFXEnabled)
					m_PostFXBuffer->getTexture()->bind();
				else
					m_Framebuffer->getTexture()->bind();

				m_ScreenQuad->bind();
				m_IBO->bind();
				API::drawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
				m_IBO->unbind();
				m_ScreenQuad->unbind();
				m_SimpleShader->disable();

			}
		}

		void Batch2DRenderer::init()
		{
			API::Buffer* buffer = new API::Buffer(GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW);
			buffer->bind();
			buffer->resize(RENDERER_BUFFER_SIZE);

			/*glGenVertexArrays(1, &m_VAO);
			glGenBuffers(1, &m_VBO);

			glBindVertexArray(m_VAO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

			glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
			glEnableVertexAttribArray(SHADER_UV_INDEX);
			glEnableVertexAttribArray(SHADER_MASK_UV_INDEX);
			glEnableVertexAttribArray(SHADER_TEXTURE_INDEX);
			glEnableVertexAttribArray(SHADER_MASK_INDEX);
			glEnableVertexAttribArray(SHADER_COLOR_INDEX);*/

			buffer->layout.push<Maths::vec3>("position");
			buffer->layout.push<Maths::vec2>("uv");
			buffer->layout.push<Maths::vec2>("mask_uv");
			buffer->layout.push<float>("tid");
			buffer->layout.push<float>("mid");
			buffer->layout.push<byte>("color", 4, true);
			
			m_VertexArray = new VertexArray();
			m_VertexArray->bind();
			m_VertexArray->addBuffer(buffer);

			//glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, 
			//	(const GLvoid*)0);
			//glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, 
			//	(const GLvoid*)(offsetof(VertexData,uv)));
			//glVertexAttribPointer(SHADER_MASK_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, 
			//	(const GLvoid*)(offsetof(VertexData, mask_uv)));
			//glVertexAttribPointer(SHADER_TEXTURE_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, 
			//	(const GLvoid*)(offsetof(VertexData, tid)));
			//glVertexAttribPointer(SHADER_MASK_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, 
			//	(const GLvoid*)(offsetof(VertexData, mid)));
			//// Using multiplications to know get the offset needed for the buffer size is quite slow.
			////glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(3 * sizeof(GLfloat)));
			//// Using offsetof will directly check in memory the space needed. REQUIRE <cstddef>
			//// USE VEC 4
			////glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::color)));
			//// USE UNSIGNED INT
			//glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, 
			//	(const GLvoid*)(offsetof(VertexData, VertexData::color)));		

			/*glBindBuffer(GL_ARRAY_BUFFER, 0);*/

			uint* indices = new uint[RENDERER_INDICES_SIZE];

			int offset = 0;
			for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6) {
				indices[i + 0] = offset + 0;
				indices[i + 1] = offset + 1;
				indices[i + 2] = offset + 2;

				indices[i + 3] = offset + 2;
				indices[i + 4] = offset + 3;
				indices[i + 5] = offset + 0;

				offset += 4;
			}

			m_IBO = new IndexBuffer(indices, RENDERER_INDICES_SIZE);

			m_VertexArray->unbind();


			using namespace Manager;
			//Set framebuffer
			m_ScreenBuffer = API::getScreenBuffer();
			CORE_ASSERT(m_ScreenBuffer == 0);
			m_Framebuffer = new FrameBuffer(m_ViewportSize);			
			m_SimpleShader = Shader_Manager::SimpleShader();
			m_SimpleShader->enable();
			m_SimpleShader->setUniformMat4("pr_matrix", Maths::mat4::Orthographic(0, (float)m_ScreenSize.x, (float)m_ScreenSize.y, 0, -1.0f, 1.0f));
			m_SimpleShader->setUniform1i("tex", 0);
			m_SimpleShader->disable();
			m_ScreenQuad = Mesh_Manager::CreateQuad(0, 0, (float)m_ScreenSize.x, (float)m_ScreenSize.y);
			GLenum error = glGetError();
			if (error != GL_NO_ERROR)
				std::cout << "OpenGL Error: " << error << std::endl;

			m_PostFX = new PostFX();
			m_PostFXBuffer = new FrameBuffer(m_ViewportSize);
			
			delete indices;
		}

		float Batch2DRenderer::submitTexture(uint textureID)
		{
			if (!textureID)
				CORE_WARN("Invalid texture ID submitted to 2D Renderer!");

			float result = 0.0f;
			bool found = false;
			for (uint i = 0; i < m_TextureSlots.size(); i++)
			{
				if (m_TextureSlots[i] == textureID)
				{
					result = (float)(i + 1);
					found = true;
					break;
				}
			}

			if (!found)
			{
				if (m_TextureSlots.size() >= RENDERER_MAX_TEXTURES)
				{
					end();
					flush();
					begin();
				}
				m_TextureSlots.push_back(textureID);
				result = (float)(m_TextureSlots.size());
			}
			return result;
		}

		float Batch2DRenderer::submitTexture(const Texture* texture)
		{
			return submitTexture(texture->getID());
		}

	}
}