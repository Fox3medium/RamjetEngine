#pragma once
#include <Core/Common.h>
#include "Component.h"

#include <Rendering/Renderer/Models/Mesh.h>

namespace Core 
{
	namespace Entities
	{
		namespace Components
		{
			class CORE_API MeshComponent : public Component
			{
			public:
				Rendering::Mesh* mesh;

			public:
				MeshComponent(Rendering::Mesh* mesh);

				static ComponentType* getStaticType()
				{
					static ComponentType type({ "Mesh" });
					return &type;
				}

				inline virtual ComponentType* getType() const override { return getStaticType(); }
			};
		}
	}
}