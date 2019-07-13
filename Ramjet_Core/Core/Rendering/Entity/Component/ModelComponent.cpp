#include "ModelComponent.h"

#include <Rendering/Renderer/Models/Model.h>

namespace Core
{
	namespace Entities
	{
		namespace Components
		{
			ModelComponent::ModelComponent(Rendering::Model* Model)
				: model(Model)
			{
			}
		}
	}
}