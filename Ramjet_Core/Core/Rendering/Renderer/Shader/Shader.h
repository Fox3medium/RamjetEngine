#pragma once

#include <Utils\Fileutils.h>
#include <Utils\Maths\maths.h>
#include <GLEW\glew.h>

using namespace Utils;

namespace Core {

	namespace Rendering {
	
		class Shader {
			private :
				//Shader ID
				GLuint m_ShaderID;

				const char* m_VertPath;
				const char* m_FragPath;

			public:
				Shader(const char* vertPath, const char* fragPath);
				~Shader();				

				void setUniform1i(const GLchar* uniVarName, int value);
				void setUniform1f(const GLchar* uniVarName, float value);
				void setUniform2f(const GLchar* uniVarName, const Maths::vec2& value);
				void setUniform3f(const GLchar* uniVarName, const Maths::vec3& value);
				void setUniform4f(const GLchar* uniVarName, const Maths::vec4& value);
				void setUniformMat4(const GLchar* uniVarName, const Maths::mat4& mat);

				void enable() const;
				void disable() const;

			private:
				GLint getUniformLocation(const GLchar* name);

				GLuint load();
		};

	}

}