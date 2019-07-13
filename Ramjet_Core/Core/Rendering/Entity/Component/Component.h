#pragma once

#include <Core/Common.h>

#include <Utils/types.h>
#include <Utils/String.h>

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
			struct CORE_API ComponentType
			{
				String name;
			};

			class CORE_API Component 
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

