#include "MeshComponent.h"

namespace Core
{
	namespace Entity
	{
		namespace Component
		{
			MeshComponent::MeshComponent(Rendering::Mesh* mesh)
				: mesh(mesh)
			{
			}
		}
	}
}