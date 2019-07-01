#include "Shader.h"
#include <Utils\Static\CInOut.h>

#include <vector>

using namespace Utils;

namespace Core { 

	namespace Rendering {

		Shader::Shader(const char* vertPath, const char* fragPath)
			: m_VertPath(vertPath), m_FragPath(fragPath)
		{
			m_ShaderID = load();
		}

		Shader::~Shader()
		{
			glDeleteProgram(m_ShaderID);
			m_UniformMap.clear();
		}

		GLuint Shader::getUniformLocation(const GLchar* name)
		{
			std::map<String, GLuint>::iterator i = m_UniformMap.find(name);
			if (i == m_UniformMap.end()) {
				m_UniformMap[name] = glGetUniformLocation(m_ShaderID, name);
			}
			return m_UniformMap.at(name);
		}

		void Shader::setUniform1i(const GLchar* uniVarName, int value)
		{
			glUniform1i(getUniformLocation(uniVarName), value);
		}

		void Shader::setUniform1f(const GLchar* uniVarName, float value)
		{
			glUniform1f(getUniformLocation(uniVarName), value);
		}

		void Shader::setUniform2f(const GLchar* uniVarName, const Maths::vec2& value)
		{
			glUniform2f(getUniformLocation(uniVarName), value.x, value.y);
		}

		void Shader::setUniform3f(const GLchar* uniVarName, const Maths::vec3& value)
		{
			glUniform3f(getUniformLocation(uniVarName), value.x, value.y, value.z);
		}

		void Shader::setUniform4f(const GLchar* uniVarName, const Maths::vec4& value)
		{
			glUniform4f(getUniformLocation(uniVarName), value.x, value.y, value.z, value.w);
		}

		void Shader::setUniformMat4(const GLchar* uniVarName, const Maths::mat4& mat)
		{
			glUniformMatrix4fv(getUniformLocation(uniVarName), 1, GL_FALSE, mat.elements);
		}

		void Shader::enable() const
		{
			glUseProgram(m_ShaderID);
		}

		void Shader::disable() const
		{
			glUseProgram(0);
		}

		GLuint Shader::load()
		{
			GLuint program = glCreateProgram();

			GLuint vertex = glCreateShader(GL_VERTEX_SHADER); //How the GPU works on vertices
			GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER); // how the GPU work on fragment (usualy pixels)

			//load vertex and fragment files 
			std::string vertFileStr = read_file(m_VertPath);
			std::string fragFileStr = read_file(m_FragPath);

			// Longer but avoid problem with the vertFileStr being destroyed prematurely,
			// Then causing the shader loading and compiling errors.
			const char* vertFile = vertFileStr.c_str();
			const char* fragFile = fragFileStr.c_str();

			// link the shader ID to the shader file
			glShaderSource(vertex, 1, &vertFile, NULL);
			// Compile the shader
			glCompileShader(vertex);

			// Check that it's correctly compile.
			GLint result;
			glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE) {
				GLint length;
				glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(vertex, length, &length, &error[0]);
				std::cout << "Fail to compile vertex shader ! " << std::endl << &error[0] << std::endl;
				glDeleteShader(vertex);
				return 0;
			}

			// link the shader ID to the shader file
			glShaderSource(fragment, 1, &fragFile, NULL);
			// Compile the shader
			glCompileShader(fragment);

			// Check that it's correctly compile. RESULT ALREADY INITIALIZED
			glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE) {
				GLint length;
				glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(fragment, length, &length, &error[0]);
				std::cout << "Fail to compile fragment shader ! " << std::endl << &error[0] << std::endl;
				glDeleteShader(fragment);
				return 0;
			}

			//Attaching the shaders to the program.
			glAttachShader(program, vertex);
			glAttachShader(program, fragment);

			// Link and validate the program.
			glLinkProgram(program);
			glValidateProgram(program);

			//Delete shader to clean memory.
			glDeleteShader(vertex);
			glDeleteShader(fragment);

			return program;
		}

	}
}