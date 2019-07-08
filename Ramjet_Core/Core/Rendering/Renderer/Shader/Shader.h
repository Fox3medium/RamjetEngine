#pragma once

#include <Utils\Fileutils.h>
#include <Utils\Maths\maths.h>
#include <GLEW\glew.h>
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
				std::string m_Name;
				GLuint m_ShaderID;

				const char* m_VertSrc;
				const char* m_FragSrc;

				std::map<std::string, GLuint> m_UniformMap;

			public:
				/*Load a shader stored in code if true*/
				Shader(const std::string& name, const char* vertPath, const char* fragPath, bool isFromCode = false);
				~Shader();				

				void setUniform1i(const GLchar* uniVarName, int value);
				void setUniform1iv(const GLchar* uniVarName, int* value, int count);
				void setUniform1f(const GLchar* uniVarName, float value);
				void setUniform1fv(const GLchar* uniVarName, float* value, int count);
				void setUniform2f(const GLchar* uniVarName, const Maths::vec2& value);
				void setUniform3f(const GLchar* uniVarName, const Maths::vec3& value);
				void setUniform4f(const GLchar* uniVarName, const Maths::vec4& value);
				void setUniformMat4(const GLchar* uniVarName, const Maths::mat4& mat);

				void enable() const;
				void disable() const;

				inline const GLuint getShaderID() { return m_ShaderID; }
				inline const std::string getShaderName() { return m_Name; }

			private:
				GLuint getUniformLocation(const GLchar* name);

				GLuint load(const char* vertSrc, const char* fragSrc, bool isFromCode);
		};

	}

}