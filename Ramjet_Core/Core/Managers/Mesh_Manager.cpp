#include <CoreBasicInclude.h>
#include "Mesh_Manager.h"

#include <Rendering/Renderer/Batch2DRenderer.h>

#include <Rendering/Renderer/Renderable2D.h>
#include <Rendering/Renderer/Shader/Shader.h>

#include <GLEW/glew.h>

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

		VertexArray* Mesh_Manager::CreateQuad(float x, float y, float width, float height)
		{
			VertexData data[4];
			data[0].vertex = Maths::vec3(x, y, 0);
			data[0].uv = Maths::vec2(0, 1);

			data[1].vertex = Maths::vec3(x, y + height, 0);
			data[1].uv = Maths::vec2(0, 0);

			data[2].vertex = Maths::vec3(x + width, y + height, 0);
			data[2].uv = Maths::vec2(1, 0);

			data[3].vertex = Maths::vec3(x + width, y, 0);
			data[3].uv = Maths::vec2(1, 1);

			//uint buffer;
			//glGenVertexArrays(1, &result);
			//glGenBuffers(1, &buffer);

			//glBindVertexArray(result);
			//glBindBuffer(GL_ARRAY_BUFFER, buffer);

			//glBufferData(GL_ARRAY_BUFFER, RENDERER_VERTEX_SIZE * 4, data, GL_STATIC_DRAW);

			//glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
			//glEnableVertexAttribArray(SHADER_UV_INDEX);
			//glEnableVertexAttribArray(SHADER_MASK_UV_INDEX);
			//glEnableVertexAttribArray(SHADER_TEXTURE_INDEX);
			//glEnableVertexAttribArray(SHADER_MASK_INDEX);
			//glEnableVertexAttribArray(SHADER_COLOR_INDEX);

			//glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
			//glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, uv)));
			//glVertexAttribPointer(SHADER_MASK_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, mask_uv)));
			//glVertexAttribPointer(SHADER_TEXTURE_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, tid)));
			//glVertexAttribPointer(SHADER_MASK_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, mid)));
			//glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, color)));

			//glBindBuffer(GL_ARRAY_BUFFER, 0);
			//glBindVertexArray(0);
			
			API::Buffer* buffer = new API::Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
			buffer->bind();
			buffer->setData(RENDERER_VERTEX_SIZE * 4, data);

			buffer->layout.push<Maths::vec3>("position");
			buffer->layout.push<Maths::vec2>("uv");
			buffer->layout.push<Maths::vec2>("mask_uv");
			buffer->layout.push<float>("tid");
			buffer->layout.push<float>("mid");
			buffer->layout.push<byte>("color", 4, true);

			VertexArray* result = new VertexArray();
			result->bind();
			result->addBuffer(buffer);

			return result;
		}

		VertexArray* Mesh_Manager::CreateQuad(const Maths::vec2& position, const Maths::vec2& size)
		{
			return CreateQuad(position.x, position.y, size.x, size.y);
		}

		Mesh* Mesh_Manager::CreateCube(float size, MaterialInstance* material)
		{
			using namespace Maths;

			Vertex data[8];

			memset(data, 0, 8 * sizeof(Vertex));

			data[0].position = vec3(-size / 2.0f, -size / 2.0f, size / 2.0f);
			data[1].position = vec3(size / 2.0f, -size / 2.0f, size / 2.0f);
			data[2].position = vec3(size / 2.0f, size / 2.0f, size / 2.0f);
			data[3].position = vec3(-size / 2.0f, size / 2.0f, size / 2.0f);
			data[4].position = vec3(-size / 2.0f, -size / 2.0f, -size / 2.0f);
			data[5].position = vec3(size / 2.0f, -size / 2.0f, -size / 2.0f);
			data[6].position = vec3(size / 2.0f, size / 2.0f, -size / 2.0f);
			data[7].position = vec3(-size / 2.0f, size / 2.0f, -size / 2.0f);

			data[0].normal = vec3(-1.0f, -1.0f, 1.0f);
			data[1].normal = vec3(1.0f, -1.0f, 1.0f);
			data[2].normal = vec3(1.0f, 1.0f, 1.0f);
			data[3].normal = vec3(-1.0f, 1.0f, 1.0f);
			data[4].normal = vec3(-1.0f, -1.0f, -1.0f);
			data[5].normal = vec3(1.0f, -1.0f, -1.0f);
			data[6].normal = vec3(1.0f, 1.0f, -1.0f);
			data[7].normal = vec3(-1.0f, 1.0f, -1.0f);

			API::Buffer* buffer = new API::Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
			buffer->bind();
			buffer->setData(8 * sizeof(Vertex), data);

			buffer->layout.push<vec3>("position");
			buffer->layout.push<vec3>("normal");
			buffer->layout.push<vec2>("uv");

			VertexArray* va = new VertexArray();
			va->bind();
			va->addBuffer(buffer);

			uint* indices = new uint[36]
			{
				0, 1, 2, 2, 3, 0,
				3, 2, 6, 6, 7, 3,
				7, 6, 5, 5, 4, 7,
				4, 0, 3, 3, 7, 4,
				0, 1, 5, 5, 4, 0,
				1, 5, 6, 6, 2, 1
			};

			IndexBuffer* ib = new IndexBuffer(indices, 36);
			return new Mesh(va, ib, material);
		}

	}

}