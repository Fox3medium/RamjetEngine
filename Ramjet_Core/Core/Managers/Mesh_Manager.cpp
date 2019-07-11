#include "Mesh_Manager.h"

#include <Core_OpenGL.h>
#include <Rendering/Renderer/Renderable2D.h>
#include <Rendering/Renderer/Shader/Shader.h>

namespace Core {

	using namespace Rendering;

	namespace Manager {

		std::map<String, Sprite*> Mesh_Manager::m_Meshes;

		void Mesh_Manager::init()
		{
		}

		Sprite* Mesh_Manager::add(const String& name, Sprite* sprite)
		{
			return nullptr;
		}

		Sprite* Mesh_Manager::getMesh(const String& name)
		{
			std::map<String, Sprite*>::iterator i = m_Meshes.find(name);
			if (i != m_Meshes.end())
				return m_Meshes[name];
			return nullptr;
		}

		void Mesh_Manager::clean()
		{
			m_Meshes.clear();
		}

		void Mesh_Manager::fromFile(const String& name, const char* filePath)
		{
			// TODO
		}

		uint Mesh_Manager::CreateQuad(float x, float y, float width, float height)
		{
			uint result;

			VertexData data[4];
			data[0].vertex = Maths::vec3(x, y, 0);
			data[0].uv = Maths::vec2(0, 1);

			data[1].vertex = Maths::vec3(x, y + height, 0);
			data[1].uv = Maths::vec2(0, 0);

			data[2].vertex = Maths::vec3(x + width, y + height, 0);
			data[2].uv = Maths::vec2(1, 0);

			data[3].vertex = Maths::vec3(x + width, y, 0);
			data[3].uv = Maths::vec2(1, 1);

			uint buffer;
			glGenVertexArrays(1, &result);
			glGenBuffers(1, &buffer);

			glBindVertexArray(result);
			glBindBuffer(GL_ARRAY_BUFFER, buffer);

			glBufferData(GL_ARRAY_BUFFER, RENDERER_VERTEX_SIZE * 4, data, GL_STATIC_DRAW);

			glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
			glEnableVertexAttribArray(SHADER_UV_INDEX);
			glEnableVertexAttribArray(SHADER_MASK_UV_INDEX);
			glEnableVertexAttribArray(SHADER_TEXTURE_INDEX);
			glEnableVertexAttribArray(SHADER_MASK_INDEX);
			glEnableVertexAttribArray(SHADER_COLOR_INDEX);

			glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
			glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, uv)));
			glVertexAttribPointer(SHADER_MASK_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, mask_uv)));
			glVertexAttribPointer(SHADER_TEXTURE_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, tid)));
			glVertexAttribPointer(SHADER_MASK_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, mid)));
			glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, color)));

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

			return result;
		}

		uint Mesh_Manager::CreateQuad(const Maths::vec2& position, const Maths::vec2& size)
		{
			return CreateQuad(position.x, position.y, size.x, size.y);
		}

	}

}