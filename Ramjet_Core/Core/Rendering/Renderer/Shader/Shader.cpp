#include "Shader.h"
#include <GLEW/glew.h>
#include <iostream>
#include <vector>

using namespace Utils;

namespace Core { 

	namespace Rendering {

		Shader::Shader(const String& name, const char* vertPath, const char* fragPath, bool isFromCode)
			: m_Name(name), m_VertSrc(vertPath), m_FragSrc(fragPath)
		{
			String vertSourceString;
			String fragSourceString;

			if (!isFromCode) {
				vertSourceString = read_file(m_VertSrc);
				fragSourceString = read_file(m_FragSrc);

				m_VertSrc = vertSourceString.c_str();
				m_FragSrc = fragSourceString.c_str();
			}
			m_ShaderID = load(m_VertSrc, m_FragSrc, isFromCode);
		}

		Shader::~Shader()
		{
			glDeleteProgram(m_ShaderID);
			m_UniformMap.clear();
		}

		uint Shader::getUniformLocation(const char* name)
		{
			std::map<String, uint>::iterator i = m_UniformMap.find(name);
			if (i == m_UniformMap.end()) {
				uint result = glGetUniformLocation(m_ShaderID, name);
				if (result == -1) {
					CORE_ERROR(m_Name.c_str(), ": Could not find uniform ", name, " in shader!");
					return NULL;
				}					
				else
					m_UniformMap[name] = result;
			}
			return m_UniformMap.at(name);
		}

		void Shader::setUniform1i(const char* uniVarName, int value)
		{
			glUniform1i(getUniformLocation(uniVarName), value);
		}

		void Shader::setUniform1iv(const char* uniVarName, int* value, int count)
		{
			glUniform1iv(getUniformLocation(uniVarName), count, value);
		}

		void Shader::setUniform1f(const char* uniVarName, float value)
		{
			glUniform1f(getUniformLocation(uniVarName), value);
		}

		void Shader::setUniform1fv(const char* uniVarName, float* value, int count)
		{
			glUniform1fv(getUniformLocation(uniVarName), count, value);
		}

		void Shader::setUniform2f(const char* uniVarName, const Maths::vec2& value)
		{
			glUniform2f(getUniformLocation(uniVarName), value.x, value.y);
		}

		void Shader::setUniform3f(const char* uniVarName, const Maths::vec3& value)
		{
			glUniform3f(getUniformLocation(uniVarName), value.x, value.y, value.z);
		}

		void Shader::setUniform4f(const char* uniVarName, const Maths::vec4& value)
		{
			glUniform4f(getUniformLocation(uniVarName), value.x, value.y, value.z, value.w);
		}

		void Shader::setUniformMat4(const char* uniVarName, const Maths::mat4& mat)
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

		uint Shader::load(const char* vertSrc, const char* fragSrc, bool isFromCode)
		{
			uint program = glCreateProgram();

			uint vertex = glCreateShader(GL_VERTEX_SHADER); //How the GPU works on vertices
			uint fragment = glCreateShader(GL_FRAGMENT_SHADER); // how the GPU work on fragment (usualy pixels)

			// link the shader ID to the shader file
			glShaderSource(vertex, 1, &m_VertSrc, NULL);
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
				CORE_ERROR("Failed to compile vertex shader!");
				CORE_ERROR(&error[0]);
				CORE_ASSERT(false, "failed to compile vertex shader!");
				glDeleteShader(vertex);
				return 0;
			}

			// link the shader ID to the shader file
			glShaderSource(fragment, 1, &m_FragSrc, NULL);
			// Compile the shader
			glCompileShader(fragment);

			// Check that it's correctly compile. RESULT ALREADY INITIALIZED
			glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE) {
				GLint length;
				glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(fragment, length, &length, &error[0]);
				CORE_ERROR("Failed to compile fragment shader!");
				CORE_ERROR(&error[0]);
				CORE_ASSERT(false, "failed to compile fragment shader!");
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