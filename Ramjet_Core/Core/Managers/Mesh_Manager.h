#pragma once

#include <map>
#include <Utils/types.h>
#include <string>
#include <Rendering/Renderer/Buffers/VertexArray.h>
#include <Rendering/Renderer/Models/Sprite.h>

namespace Core {

	using namespace Rendering;

	namespace Manager {
	
		class Mesh_Manager 
		{
		private:
			// TODO add meshes instead of sprites
			static std::map<String, Sprite*> m_Meshes;

		public:
			static void init();
			static Sprite* add(const String& name, Sprite* sprite);
			static Sprite* getMesh(const String& name);
			static void clean();

			static void fromFile(const String& name, const char* filePath);

			static VertexArray* CreateQuad(float x, float y, float width, float height);
			static VertexArray* CreateQuad(const Maths::vec2& position, const Maths::vec2& size);

		private:
			Mesh_Manager() {}
			~Mesh_Manager() { clean(); }
		};
	}

}