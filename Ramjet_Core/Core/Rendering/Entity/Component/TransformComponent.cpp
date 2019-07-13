#include "TransformComponent.h"

namespace Core
{
	namespace Entities
	{
		namespace Components
		{
			TransformComponent::TransformComponent(const Maths::mat4& in_transform)
				: transform(in_transform)
			{
			}
		}
	}
}