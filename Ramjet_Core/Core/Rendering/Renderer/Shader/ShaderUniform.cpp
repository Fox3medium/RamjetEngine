#include "ShaderUniform.h"
#include <CoreBasicInclude.h>
#include "Shader.h"

namespace Core
{

	namespace Rendering
	{

		ShaderUniformDeclaration::ShaderUniformDeclaration(Type type, const String& name, const Shader* shader, uint count)
			: m_Type(type), m_Name(name), m_Shader(shader), m_Count(count)
		{
			m_Size = sizeOfUniformType(type) * count;
		}

		uint ShaderUniformDeclaration::getSize() const
		{
			return m_Size;
		}

		int ShaderUniformDeclaration::getLocation() const
		{
			return m_Location;
		}

		uint ShaderUniformDeclaration::sizeOfUniformType(Type type)
		{
			switch (type)
			{
			case ShaderUniformDeclaration::Type::FLOAT32:		return 4;
			case ShaderUniformDeclaration::Type::INT32:			return 4;
			case ShaderUniformDeclaration::Type::VEC2:			return 4 * 2;
			case ShaderUniformDeclaration::Type::VEC3:			return 4 * 3;
			case ShaderUniformDeclaration::Type::VEC4:			return 4 * 4;
			case ShaderUniformDeclaration::Type::MAT3:			return 4 * 3 * 3;
			case ShaderUniformDeclaration::Type::MAT4:			return 4 * 4 * 4;
			case ShaderUniformDeclaration::Type::SAMPLER2D:		return 4;
			}
			return 0;
		}

	}

}