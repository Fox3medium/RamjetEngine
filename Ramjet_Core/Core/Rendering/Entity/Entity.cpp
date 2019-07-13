#include "Entity.h"

namespace Core
{
	namespace Entities
	{
		using namespace Components;

		Entity::Entity()
		{
		}

		Entity::~Entity()
		{
			/*for (Component::Component* component : m_Components)
				delete component;
			m_Components.clear();*/
		}

		void Entity::addComponent(Component* component)
		{
			m_Components.push_back(component);
		}

		void Entity::addModel(Core::Rendering::Model* model)
		{
			m_Components.push_back(new ModelComponent(model));
			/*for (Core::Rendering::Mesh* mesh : model->getMesh())
			{
				addComponent(new MeshComponent(mesh));
			}*/
		}

	}
}
