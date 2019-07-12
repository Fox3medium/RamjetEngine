#pragma once

#include <vector>

#include <Utils/types.h>
#include "../Renderer/Models/Mesh.h"
#include "../Renderer/Models/Model.h"

namespace Core 
{
	namespace Rendering 
	{
		class Renderer3D;

		class Scene
		{
		private:
			std::vector<Mesh*> m_Meshes;
		public:
			Scene();
			~Scene();

			void add(Mesh* mesh);
			void add(Model* model);
			void render(Renderer3D& renderer);
			const std::vector<Mesh*>& getMeshes() const { return m_Meshes; }
		};
	}
}