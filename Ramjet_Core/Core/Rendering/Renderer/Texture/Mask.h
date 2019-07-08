#pragma once

#include "Texture.h"
#include <Utils/Maths/maths.h>

namespace Core {

	namespace Rendering {
	
		struct Mask 
		{
			Texture* texture;
			Maths::mat4 transform;

			Mask(Texture* in_texture, const Maths::mat4& in_transform = Maths::mat4::Identity()) 
				: texture(in_texture), transform(in_transform)
			{
				/*m_Translate = Maths::vec3(-16.0f, -9.0f, 1.0f);
				m_Scale = Maths::vec3(32.0f, 18.0f, 1.0f);*/
			}

			void SetPosition(const Maths::vec3& translate)
			{
				Update(translate, Maths::vec3(0.0f, 0.0f, 0.0f));
			}

			void SetScale(const Maths::vec3& scale)
			{
				Update(Maths::vec3(0.0f, 0.0f, 0.0f), scale);
			}

			void SetModifier(const Maths::vec3& translate, const Maths::vec3& scale)
			{
				Update(translate, scale);
			}

		private:

		/*	Maths::vec3 m_Translate;
			Maths::vec3 m_Scale;
*/
			void Update(const Maths::vec3& translate, const Maths::vec3& scale)
			{
				/*transform = Maths::mat4::Translate(m_Translate + translate) * Maths::mat4::Scale(m_Scale + scale);*/
			}
		};

	}

}