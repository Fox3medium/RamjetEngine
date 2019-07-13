#include "Scene.h"

#include <CoreBasicInclude.h>
#include "../Renderer/Renderer3D.h"
#include "../Camera/FPS_Camera.h"

namespace Core 
{
	namespace Rendering 
	{

		using namespace Entities;
		using namespace Components;
		using namespace Cameras;

		Scene::Scene()
			: m_Camera(new FPS_Camera(Maths::mat4::Perspective(65.0f, 16.0f / 9.0f, 0.1f, 1000.0f)))
		{
		}

		Scene::Scene(Camera* camera)
			: m_Camera(camera)
		{
		}

		Scene::~Scene()
		{
			for (uint i = 0; i < m_Entities.size(); i++)
				delete m_Entities[i];

			m_Entities.clear();
		}

		void Scene::add(Entity* entity)
		{
			m_Entities.push_back(entity);
			if (!entity->getComponent<TransformComponent>())
			{
				CORE_WARN("Entity does not have Transform, creating...");
				entity->addComponent(new TransformComponent(Maths::mat4::Identity()));
			}
		}

		void Scene::add(Model* model)
		{
			// TODO 
			
		}

		void Scene::update()
		{
		}

		void Scene::render(Renderer3D& renderer)
		{
			Camera* camera = m_Camera;
			camera->update();

			renderer.begin();

			for (Entity* entity : m_Entities)
			{
				ModelComponent* model = entity->getComponent<ModelComponent>();
				for (Mesh* mesh: model->model->getMesh()) 
				{
					if (mesh)
					{
						TransformComponent* tc = entity->getComponent<TransformComponent>();
						CORE_ASSERT(tc, "Mesh does not have transform!"); // Meshes MUST have transforms
						renderer.submitMesh(camera, mesh, tc->transform);
					}
				}				
			}

			renderer.end();
		}

	}
}