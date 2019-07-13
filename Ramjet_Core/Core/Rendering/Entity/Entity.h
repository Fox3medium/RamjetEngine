#pragma once

#include <vector>

#include "Component/Component.h"

namespace Core
{
	namespace Entity
	{
		class Entity 
		{
		protected:
			std::vector<Component::Component*> m_Components;

		public:
			Entity();
			~Entity();

			void addComponent(Component::Component* component);

			template <typename T>
			const T* getComponent() const
			{
				return getComponentInternal<T>();
			}

			template <typename T>
			T* getComponent()
			{
				return (T*)getComponentInternal<T>();
			}

		private:
			template <typename T>
			const T* getComponentInternal() const
			{
				component::ComponentType* type = T::getStaticType();
				for (auto x : m_Components)
				{
					if (x->getType() == type)
						return (const T*)x;
				}
				return nullptr;
			}
		};
	}
}