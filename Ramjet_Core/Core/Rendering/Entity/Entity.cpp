#include "Entity.h"

namespace Core
{
	namespace Entity
	{
		Entity::Entity()
		{
		}

		Entity::~Entity()
		{
			/*for (Component::Component* component : m_Components)
				delete component;
			m_Components.clear();*/
		}

		void Entity::addComponent(Component::Component* component)
		{
			m_Components.push_back(component);
		}
	}
}
