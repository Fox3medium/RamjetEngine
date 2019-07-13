#pragma once

#include <CoreBasicInclude.h>
#include <Core/Common.h>

#include "Component/Components.h"

namespace Core
{
	namespace Rendering {
		class Model;
	}
	namespace Entities
	{
		class CORE_API Entity 
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