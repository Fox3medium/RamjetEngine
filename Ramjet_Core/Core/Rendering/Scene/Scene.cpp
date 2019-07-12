#include "Scene.h"

#include "../Renderer/Renderer3D.h"

namespace Core 
{
	namespace Rendering 
	{

		Scene::Scene()
		{
		}

		Scene::~Scene()
		{
			for (uint i = 0; i < m_Meshes.size(); i++)
				delete m_Meshes[i];

			m_Meshes.clear();
		}

		void Scene::add(Mesh* mesh)
		{
			m_Meshes.push_back(mesh);
		}

		void Scene::add(Model* model)
		{
			for(Mesh* mesh : model->getMesh())
			{
				m_Meshes.push_back(mesh);
			}
		}

		void Scene::render(Renderer3D& renderer)
		{
			for (Mesh* mesh : m_Meshes)
				renderer.submit(mesh);
		}

	}
}