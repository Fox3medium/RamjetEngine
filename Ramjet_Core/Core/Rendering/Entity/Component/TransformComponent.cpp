#include "TransformComponent.h"

namespace Core
{
	namespace Entity
	{
		namespace Component
		{
			TransformComponent::TransformComponent(const Maths::mat4& in_transform)
				: transform(in_transform)
			{
			}
		}
	}
}