#pragma once

#include <map>
#include <Utils/types.h>
#include <string>
#include <Rendering/Renderer/Models/Sprite.h>

namespace Core {

	using namespace Rendering;

	namespace Manager {
	
		class Mesh_Manager 
		{
		private:
			// TODO add meshes instead of sprites
			static std::map<std::string, Sprite*> m_Meshes;

		public:
			static void init();
			static Sprite* add(const std::string& name, Sprite* sprite);
			static Sprite* getMesh(const std::string& name);
			static void clean();

			static void fromFile(const std::string& name, const char* filePath);

			static uint CreateQuad(float x, float y, float width, float height);
			static uint CreateQuad(const Maths::vec2& position, const Maths::vec2& size);

		private:
			Mesh_Manager() {}
			~Mesh_Manager() { clean(); }
		};
	}

}