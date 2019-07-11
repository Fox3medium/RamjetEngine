#pragma once

#include <Utils/types.h>

namespace Core 
{
	namespace Rendering 
	{
		class ShaderUniform 
		{
		public:
			enum class Type 
			{
				NONE, 
				FLOAT32, 
				INT32, 
				VEC2, 
				VEC3, 
				VEC4, 
				MAT3, 
				MAT4, 
				SAMPLER2D
			};

		private:
			friend class Shader;

			Type m_Type;
			
		};
	}
}