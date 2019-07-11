#pragma once

#include <map>

#include <Utils/types.h>
#include <Rendering/Renderer/Shader/Shader.h>

namespace Core
{
	namespace Rendering
	{
		class Material 
		{
		private:
			Shader* m_Shader;
			byte* m_UniformData;
			uint m_UniformDataSize;

		public:
			Material(Shader* shader);
			~Material();

			void bind() const;
			void unbind() const;
			void dumpUniformData() const;

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

		class MaterialInstance 
		{
		private:
			Material* m_Material;
			byte* m_UniformData;

		public:
			MaterialInstance(Material* material);

			inline Material* getMaterial() const { return m_Material; }

			void bind() const;
			void unbind() const;

			template<typename T>
			void setUniform(const String& name, const T& value)
			{
				CORE_ASSERT(false, "Unknown type");
			}

			template<> void setUniform<float>(const String& name, const float& value) { }
		private:
			void initUniformStorage();
		};
	}
}