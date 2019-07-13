#pragma once

#include <CoreBasicInclude.h>
#include <Core/Common.h>
#include <Utils/types.h>
#include <Rendering/Renderer/Shader/Shader.h>

namespace Core
{
	namespace Rendering
	{
		class CORE_API Material 
		{
		private:
			friend class MaterialInstance;
			Shader* m_Shader;
			byte* m_UniformData;
			uint m_UniformDataSize;

		public:
			Material(Shader* shader);
			~Material();

			void bind() const;
			void unbind() const;
			void dumpUniformData() const;

			inline Shader* getShader() const { return m_Shader; }

			template<typename T>
			void setUniform(const String& name, const T& value)
			{
				const ShaderUniformDeclaration* uniform = getUniformDeclaration(name);
				if (!uniform)
				{
					// ERROR WITH THIS ONE
					//CORE_ERROR("Could not find uniform '", name, "'!");
					return;
				}
				memcpy(m_UniformData + uniform->getOffset(), &value, uniform->getSize());
			}

			template<typename T>
			const T* getUniform(const String& name) const
			{
				return getUniform<T>(getUniformDeclaration(name));
			}

			template<typename T>
			const T* getUniform(const ShaderUniformDeclaration* uniform) const
			{
				return (T*)& m_UniformData[uniform->getOffset()];
			}

		private: 
			// Prepar uniform buffer size.
			void initUniformStorage();

			const ShaderUniformDeclaration* getUniformDeclaration(const String& name) const;
		};

		class CORE_API MaterialInstance 
		{
		private:
			Material* m_Material;
			byte* m_UniformData;
			uint m_UniformDataSize;
			uint m_SetUniforms;

		public:
			MaterialInstance(Material* material);

			inline Material* getMaterial() const { return m_Material; }

			void bind() const;
			void unbind() const;
			void unsetUniform(const String& name);

			template<typename T>
			void setUniform(const String& name, const T& value)
			{
				int index = getUniformDeclarationIndex(name);
				if (index == -1)
				{
					//CORE_ERROR("Could not find uniform '", name, "'!");
					return;
				}
				ShaderUniformDeclaration* uniform = m_Material->m_Shader->getUniformDeclarations()[index];
				memcpy(m_UniformData + uniform->getOffset(), &value, uniform->getSize());
				m_SetUniforms |= 1 << index;
			}

			//template<> void setUniform<float>(const String& name, const float& value) { }

		private:
			void initUniformStorage();
			int getUniformDeclarationIndex(const String& name) const;
		};
	}
}