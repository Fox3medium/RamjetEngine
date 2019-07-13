#pragma once

#include <vector>

#include <Utils/types.h>
#include <Rendering/Entity/Entity.h>
#include <Rendering/Renderer/Models/Model.h>
#include <Rendering/Camera/Camera.h>

namespace Core 
{
	using namespace Entities;
	namespace Rendering 
	{
		using namespace Cameras;

		class Renderer3D;

		class CORE_API Scene
		{
		private:
			std::vector<Entity*> m_Entities;

			Camera* m_Camera;

		public:
			Scene();
			Scene(Camera* camera);
			~Scene();

			void add(Entity* entity);
			void add(Model* model);
			void update();
			void render(Renderer3D& renderer);
			const std::vector<Entity*>& getMeshes() const { return m_Entities; }
		};
	}
}