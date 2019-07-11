#pragma once

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

		private: 
			void initUniformStorage();
			//const ShaderUniformDeclaration* getUniformDeclaration(const String& name) const;
		};
	}
}