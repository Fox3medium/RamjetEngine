#pragma once

#include <Utils/types.h>$

namespace Core 
{
	namespace Entity 
	{
		class Entity;
	}
}

namespace Core
{
	namespace Entity
	{
		namespace Component 
		{
			struct ComponentType
			{
				String name;
			};

			class Component 
			{
			protected:
				Entity* m_Entity;

			public:
				// Test as const TODO
				virtual Entity* getEntity() { return m_Entity; }
				virtual ComponentType* getType() const { return nullptr; }
			};
		}
	}
}

