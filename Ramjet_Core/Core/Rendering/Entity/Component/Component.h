#pragma once

#include <Utils/types.h>

namespace Core {
	namespace Entities {
		class Entity;
	}
}

namespace Core
{
	namespace Entities
	{
		namespace Components
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

