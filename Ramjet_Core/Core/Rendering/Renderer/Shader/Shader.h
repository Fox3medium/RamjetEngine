#pragma once

#include <Utils/types.h>
#include <Utils/Fileutils.h>
#include <Utils/Maths/maths.h>
#include <map>

using namespace Utils;

namespace Core {

	namespace Rendering {

		#define SHADER_VERTEX_INDEX		0
		#define SHADER_UV_INDEX			1
		#define SHADER_MASK_UV_INDEX	2
		#define SHADER_TEXTURE_INDEX	3
		#define SHADER_MASK_INDEX		4
		#define SHADER_COLOR_INDEX		5
	
		class Shader {
			private :
				//Shader ID
				String m_Name;
				uint m_ShaderID;

				const char* m_VertSrc;
				const char* m_FragSrc;

				std::map<String, uint> m_UniformMap;

			public:
				/*Load a shader stored in code if true*/
				Shader(const String& name, const char* vertPath, const char* fragPath, bool isFromCode = false);
				~Shader();				

				void setUniform1i(const char* uniVarName, int value);
				void setUniform1iv(const char* uniVarName, int* value, int count);
				void setUniform1f(const char* uniVarName, float value);
				void setUniform1fv(const char* uniVarName, float* value, int count);
				void setUniform2f(const char* uniVarName, const Maths::vec2& value);
				void setUniform3f(const char* uniVarName, const Maths::vec3& value);
				void setUniform4f(const char* uniVarName, const Maths::vec4& value);
				void setUniformMat4(const char* uniVarName, const Maths::mat4& mat);

				void enable() const;
				void disable() const;

				inline const uint getShaderID() { return m_ShaderID; }
				inline const String getShaderName() { return m_Name; }

			private:
				uint getUniformLocation(const char* name);

				uint load(const char* vertSrc, const char* fragSrc, bool isFromCode);
		};

	}

}