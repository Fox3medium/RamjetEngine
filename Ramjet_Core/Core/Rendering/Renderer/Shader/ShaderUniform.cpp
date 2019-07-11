#pragma once

#include "ShaderUniform.h"

#include "Shader.h"

namespace Core
{

	namespace Rendering
	{

		ShaderUniform::ShaderUniform(Type type, const String& name, const Shader* shader, uint count)
			: m_Type(type), m_Name(name), m_Shader(shader), m_Count(count)
		{
			m_Size = sizeOfUniformType(type) * count;
		}

		uint ShaderUniform::getSize() const
		{
			return m_Size;
		}

		int ShaderUniform::getLocation() const
		{
			return m_Location;
		}

		uint ShaderUniform::sizeOfUniformType(Type type)
		{
			switch (type)
			{
			case ShaderUniform::Type::FLOAT32:		return 4;
			case ShaderUniform::Type::INT32:		return 4;
			case ShaderUniform::Type::VEC2:			return 4 * 2;
			case ShaderUniform::Type::VEC3:			return 4 * 3;
			case ShaderUniform::Type::VEC4:			return 4 * 4;
			case ShaderUniform::Type::MAT3:			return 4 * 3 * 3;
			case ShaderUniform::Type::MAT4:			return 4 * 4 * 4;
			case ShaderUniform::Type::SAMPLER2D:	return 4;
			}
			return 0;
		}

	}

}