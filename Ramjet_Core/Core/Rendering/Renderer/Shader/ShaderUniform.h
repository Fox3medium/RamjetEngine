#pragma once

#include <Core/Common.h>
#include <Utils/types.h>
#include <Utils/String.h>

namespace Core 
{
	namespace Rendering
	{
		class CORE_API ShaderUniformDeclaration 
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
			String m_Name;
			uint m_Size;
			uint m_Count;
			uint m_Offset;
			const Shader* m_Shader;
			mutable int m_Location;

		public:
			ShaderUniformDeclaration(Type type, const String& name, const Shader* shader, uint count = 1);
			uint getSize() const;
			int getLocation() const;
			inline int getOffset() const { return m_Offset; }
			inline const String& getName() const { return m_Name; }
			inline Type getType() const { return m_Type; }

		private:
			uint sizeOfUniformType(Type type);
			
		};
	}
}