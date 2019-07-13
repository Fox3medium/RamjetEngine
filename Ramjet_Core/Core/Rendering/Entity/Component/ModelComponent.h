#pragma once

#include "Component.h"

#include <Core/Common.h>

namespace Core
{

	namespace Rendering 
	{
		class Model;
	}

	namespace Entities
	{
		namespace Components
		{
			class CORE_API ModelComponent : public Component
			{
			public:
				Rendering::Model* model;

			public:
				ModelComponent(Rendering::Model* Model);

				static ComponentType* getStaticType()
				{
					static ComponentType type({ "Model" });
					return &type;
				}

				inline virtual ComponentType* getType() const override { return getStaticType(); }
			};
		}
	}
}