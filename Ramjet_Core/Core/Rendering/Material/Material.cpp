#include "Material.h"

#include <sstream>

namespace Core 
{
	namespace Rendering 
	{

		Material::Material(Shader* shader)
			: m_Shader(shader)			
		{
			initUniformStorage();
		}

		Material::~Material()
		{
			delete m_Shader;
		}

		void Material::bind() const
		{
			m_Shader->enable();
			m_Shader->resolveAndSetUniforms(m_UniformData, m_UniformDataSize);
		}

		void Material::unbind() const
		{
			m_Shader->disable();
		}

		void Material::dumpUniformData() const
		{
			CORE_INFO("Dumping uniforms for Material ", (long)this);
			const std::vector<ShaderUniformDeclaration*>& uniforms = m_Shader->getUniformDeclarations();
			for (uint i = 0; i < uniforms.size(); i++)
			{
				ShaderUniformDeclaration* declaration = uniforms[i];
				switch (declaration->getType())
				{
				case ShaderUniformDeclaration::Type::MAT4:
					//CORE_INFO(declaration->getName(), " = ", getUniform<Maths::mat4>(declaration)->ToString());
					break;
				}
			}
		}

		void Material::initUniformStorage()
		{
			m_UniformDataSize = 0;
			const std::vector<ShaderUniformDeclaration*>& uniforms = m_Shader->getUniformDeclarations();
			for (ShaderUniformDeclaration* uniform : uniforms)
				m_UniformDataSize += uniform->getSize();

			m_UniformData = new byte[m_UniformDataSize];
			memset(m_UniformData, 0, m_UniformDataSize);
		}

		const ShaderUniformDeclaration* Material::getUniformDeclaration(const String& name) const
		{
			for (ShaderUniformDeclaration* uniform : m_Shader->getUniformDeclarations())
			{
				if (uniform->getName() == name)
					return uniform;
			}
			return nullptr;
		}

		MaterialInstance::MaterialInstance(Material* material)
			: m_Material(material)
		{
		}

	}
}