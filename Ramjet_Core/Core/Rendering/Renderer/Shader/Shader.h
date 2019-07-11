#pragma once

#include <Utils/types.h>
#include <Utils/Fileutils.h>
#include <Utils/StringUtils.h>
#include <Utils/Maths/maths.h>
#include <map>

#include "ShaderUniform.h"

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

				std::vector<ShaderUniform*> m_Uniforms;

			public:
				/*Load a shader stored in code if true*/
				Shader(const String& name, const String& vertPath, const String& fragPath, bool isFromCode = false);
				~Shader();				

				void setUniform1i(const char* uniVarName, int value);
				void setUniform1iv(const char* uniVarName, int* value, int count);
				void setUniform1f(const char* uniVarName, float value);
				void setUniform1fv(const char* uniVarName, float* value, int count);
				void setUniform2f(const char* uniVarName, const Maths::vec2& value);
				void setUniform3f(const char* uniVarName, const Maths::vec3& value);
				void setUniform4f(const char* uniVarName, const Maths::vec4& value);
				void setUniformMat4(const char* uniVarName, const Maths::mat4& mat);

				void resolveAndSetUniforms(byte* data, uint size);

				void enable() const;
				void disable() const;

				inline const uint getShaderID() { return m_ShaderID; }
				inline const String getShaderName() { return m_Name; }

				inline const std::vector<ShaderUniform*>& getUniformDeclarations() const { return m_Uniforms; }

			private:
				uint getUniformLocation(const char* name);
				void parseUniforms(const std::vector<String>& lines);
				ShaderUniform::Type getUniformTypeFromString(const String& token);
				void resolveUniforms();

				uint load(const String& vertSrc, const String& fragSrc, bool isFromCode);

				void resolveAndSetUniform(ShaderUniform* uniform, byte* data);

				void setUniform1i(	uint location, int value);
				void setUniform1iv(	uint location, int* value, int count);
				void setUniform1f(	uint location, float value);
				void setUniform1fv(	uint location, float* value, int count);
				void setUniform2f(	uint location, const Maths::vec2& value);
				void setUniform3f(	uint location, const Maths::vec3& value);
				void setUniform4f(	uint location, const Maths::vec4& value);
				void setUniformMat4(uint location, const Maths::mat4& mat);
		};

	}

}