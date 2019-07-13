#pragma once

#include "Component.h"

#include <Utils/Maths/maths.h>

namespace Core
{
	namespace Entity
	{
		namespace Component
		{
			class TransformComponent : public Component 
			{
			public:
				Maths::mat4 transform;

			public:
				TransformComponent(const Maths::mat4& in_transform);

				static ComponentType* getStaticType()
				{
					static ComponentType type({ "Transform" });
					return &type;
				}

				inline virtual ComponentType* getType() const override { return getStaticType(); }
			};
		}
	}
}