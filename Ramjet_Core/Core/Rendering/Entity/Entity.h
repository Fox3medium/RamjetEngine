#pragma once

#include <vector>
#include "Component/Components.h"

namespace Core
{
	namespace Rendering {
		class Model;
	}
	namespace Entities
	{
		class Entity 
		{
		protected:
			std::vector<Components::Component*> m_Components;

		public:
			Entity();
			~Entity();

			void addComponent(Components::Component* component);
			void addModel(Core::Rendering::Model* model);

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
				Components::ComponentType* type = T::getStaticType();
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