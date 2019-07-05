#include "Batch2DRenderer.h"

namespace Core {

	namespace Rendering {

		Batch2DRenderer::Batch2DRenderer()
		{
			init();
		}

		Batch2DRenderer::~Batch2DRenderer()
		{
			delete m_IBO;
			glDeleteBuffers(1, &m_VBO);
		}

		void Batch2DRenderer::begin()
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		void Batch2DRenderer::submit(const Renderable2D* renderable)
		{
			const Maths::vec3& position = renderable->getPosition();
			const Maths::vec2& size = renderable->getSize();
			const unsigned int color = renderable->getColor();
			const std::vector<Maths::vec2>& uv = renderable->getUV();
			const GLuint tid = renderable->getTextureID();

			float textureSlot = 0.0f;

			if (tid > 0)
			{
				bool found = false;
				for (int i = 0; i < m_TextureSlots.size(); i++)
				{
					if (m_TextureSlots[i] == tid)
					{
						textureSlot = (float)(i + 1);
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
					m_TextureSlots.push_back(tid);
					textureSlot = (float)(m_TextureSlots.size());
				}
			}			

			m_Buffer->vertex = *m_TransformationBack * position;
			m_Buffer->uv = uv[0];
			m_Buffer->tid = textureSlot;
			m_Buffer->color = color;
			m_Buffer++;

			m_Buffer->vertex = *m_TransformationBack * Maths::vec3(position.x, position.y + size.y, position.z);
			m_Buffer->uv = uv[1];
			m_Buffer->tid = textureSlot;
			m_Buffer->color = color;
			m_Buffer++;

			m_Buffer->vertex = *m_TransformationBack * Maths::vec3(position.x + size.x, position.y + size.y, position.z);
			m_Buffer->uv = uv[2];
			m_Buffer->tid = textureSlot;
			m_Buffer->color = color;
			m_Buffer++;

			m_Buffer->vertex = *m_TransformationBack * Maths::vec3(position.x + size.x, position.y, position.z);
			m_Buffer->uv = uv[3];
			m_Buffer->tid = textureSlot;
			m_Buffer->color = color;
			m_Buffer++;

			m_IndexCount += 6;
		}

		void Batch2DRenderer::drawString(const std::string& text, const Maths::vec3& position, const Font& font, unsigned int color)
		{
			using namespace ftgl;

			float ts = 0.0f;
			bool found = false;
			for (int i = 0; i < m_TextureSlots.size(); i++)
			{
				if (m_TextureSlots[i] == font.getID())
				{
					ts = (float)(i + 1);
					found = true;
					break;
				}
			}

			if (!found)
			{
				if (m_TextureSlots.size() >= 32)
				{
					end();
					flush();
					begin();
				}
				m_TextureSlots.push_back(font.getID());
				ts = (float)(m_TextureSlots.size());
			}

			/*float scaleX = 960.0f / 32.0f;
			float scaleY = 540.0f / 18.0f;*/
			const Maths::vec2& scale = font.getScale();

			float x = position.x;

			texture_font_t* ftFont = font.getFTFont();

			for (int i = 0; i < text.length(); i++)
			{
				char c = text[i];
				texture_glyph_t* glyph = texture_font_get_glyph(ftFont, c);
				if (glyph != NULL)
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

		void Batch2DRenderer::end()
		{
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void Batch2DRenderer::flush()
		{
			for (int i = 0; i < m_TextureSlots.size(); i++)
			{
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, m_TextureSlots[i]);
			}

			glBindVertexArray(m_VAO);
			m_IBO->bind();

			glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL);

			m_IBO->unbind();
			glBindVertexArray(0);

			m_IndexCount = 0;
			m_TextureSlots.clear();
		}

		void Batch2DRenderer::init()
		{
			glGenVertexArrays(1, &m_VAO);
			glGenBuffers(1, &m_VBO);

			glBindVertexArray(m_VAO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

			glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
			glEnableVertexAttribArray(SHADER_UV_INDEX);
			glEnableVertexAttribArray(SHADER_TEXTURE_INDEX);
			glEnableVertexAttribArray(SHADER_COLOR_INDEX);

			glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
			glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::uv)));
			glVertexAttribPointer(SHADER_TEXTURE_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::tid)));
			// Using multiplications to know get the offset needed for the buffer size is quite slow.
			//glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(3 * sizeof(GLfloat)));
			// Using offsetof will directly check in memory the space needed. REQUIRE <cstddef>
			// USE VEC 4
			//glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::color)));
			// USE UNSIGNED INT
			glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::color)));		

			glBindBuffer(GL_ARRAY_BUFFER, 0);

			GLuint* indices = new GLuint[RENDERER_INDICES_SIZE];

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

			glBindVertexArray(0);
		}

	}
}