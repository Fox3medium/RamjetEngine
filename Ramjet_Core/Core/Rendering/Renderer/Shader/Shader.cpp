#include "Shader.h"

#include <Utils/StringUtils.h>
#include <GLEW/glew.h>

using namespace Utils;

namespace Core { 

	namespace Rendering {

		Shader::Shader(const String& name, const String& vertPath, const String& fragPath, bool isFromCode)
			: m_Name(name), m_Paths(vertPath+" "+fragPath)
		{
			String vertSourceString;
			String fragSourceString;

			m_Uniforms.empty();
			
			m_VertSrc = vertPath.c_str();
			m_FragSrc = fragPath.c_str();

			if (!isFromCode) {
				vertSourceString = read_file(m_VertSrc);
				fragSourceString = read_file(m_FragSrc);

				m_VertSrc = vertSourceString.c_str();
				m_FragSrc = fragSourceString.c_str();
			}
			m_ShaderID = load(m_VertSrc, m_FragSrc, isFromCode);
			resolveUniforms();
		}

		Shader::~Shader()
		{
			glDeleteProgram(m_ShaderID);
			//m_UniformMap.clear();
		}

		uint Shader::getUniformLocation(const char* name)
		{
			GLint result = glGetUniformLocation(m_ShaderID, name);
			if (result == -1)
				CORE_ERROR(m_Name.c_str(), ": could not find uniform ", name, " in shader!");
			return result;
		}

		void Shader::parseUniforms(const std::vector<String>& lines)
		{
			for (uint i = 0; i < lines.size(); i++)
			{
				const char* str = lines[i].c_str();
				if (strstr(str, "uniform"))
				{
					std::vector<String> line = Utils::SplitString(str, ' ');
					for (uint i = 0; i < line.size(); i++)
					{
						// TODO: Precision
						String& token = line[i];
						ShaderUniformDeclaration::Type type = getUniformTypeFromString(token);
						if (type != ShaderUniformDeclaration::Type::NONE)
						{
							String& nextToken = line[i + 1];
							String name = nextToken;
							if (name[name.size() - 1] == ';')
								name = nextToken.substr(0, nextToken.size() - 1);

							uint count = 1;

							// Uniform arrays
							uint arrayToken = nextToken.find('[');
							if (arrayToken != -1)
							{
								name = name.substr(0, arrayToken - 1);
								uint arrayEnd = nextToken.find(']');
								CORE_ASSERT(arrayEnd != String::npos);
								count = atoi(nextToken.substr(arrayToken + 1, arrayEnd - arrayToken - 1).c_str());
							}

							ShaderUniformDeclaration* uniform = new ShaderUniformDeclaration(type, name, this, count);
							m_Uniforms.push_back(uniform);
							break;
						}
					}
				}
			}
		}

		ShaderUniformDeclaration::Type Shader::getUniformTypeFromString(const String& token)
		{
			if (token == "float") return ShaderUniformDeclaration::Type::FLOAT32;
			if (token == "int") return ShaderUniformDeclaration::Type::INT32;
			if (token == "vec2") return ShaderUniformDeclaration::Type::VEC2;
			if (token == "vec3") return ShaderUniformDeclaration::Type::VEC3;
			if (token == "vec4") return ShaderUniformDeclaration::Type::VEC4;
			if (token == "mat3") return ShaderUniformDeclaration::Type::MAT3;
			if (token == "mat4") return ShaderUniformDeclaration::Type::MAT4;
			if (token == "sampler2D") return ShaderUniformDeclaration::Type::SAMPLER2D;

			return ShaderUniformDeclaration::Type::NONE;
		}

		void Shader::resolveUniforms()
		{
			uint offset = 0;
			for (uint i = 0; i < m_Uniforms.size(); i++)
			{
				ShaderUniformDeclaration* uniform = m_Uniforms[i];
				uniform->m_Offset = offset;
				uniform->m_Location = getUniformLocation(uniform->m_Name.c_str());

				offset += uniform->getSize();
			}
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

		uint Shader::load(const String& vertSrc, const String& fragSrc, bool isFromCode)
		{
			uint program = glCreateProgram();

			uint vertex = glCreateShader(GL_VERTEX_SHADER); //How the GPU works on vertices
			uint fragment = glCreateShader(GL_FRAGMENT_SHADER); // how the GPU work on fragment (usualy pixels)		

			std::vector<String> lines = Utils::SplitString(vertSrc, '\n');
			parseUniforms(lines);
			lines = Utils::SplitString(fragSrc, '\n');
			parseUniforms(lines);

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

		void Shader::resolveAndSetUniforms(byte* data, uint size)
		{
			const std::vector<ShaderUniformDeclaration*>& uniforms = m_Uniforms;

			for (uint i = 0; i < uniforms.size(); i++)
				resolveAndSetUniform(uniforms[i], data);
		}

		void Shader::resolveAndSetUniform(ShaderUniformDeclaration* uniform, byte* data)
		{
			Maths::mat4 test;
			if (uniform->getName() == "pr_matrix")
				test = *(Maths::mat4*) & data[uniform->getOffset()];
			switch (uniform->getType())
			{
			case ShaderUniformDeclaration::Type::FLOAT32:
				setUniform1f(uniform->getLocation(), *(float*)& data[uniform->getOffset()]);
				break;
			case ShaderUniformDeclaration::Type::SAMPLER2D:
			case ShaderUniformDeclaration::Type::INT32:
				setUniform1i(uniform->getLocation(), *(int*)& data[uniform->getOffset()]);
				break;
			case ShaderUniformDeclaration::Type::VEC2:
				setUniform2f(uniform->getLocation(), *(Maths::vec2*) & data[uniform->getOffset()]);
				break;
			case ShaderUniformDeclaration::Type::VEC3:
				setUniform3f(uniform->getLocation(), *(Maths::vec3*) & data[uniform->getOffset()]);
				break;
			case ShaderUniformDeclaration::Type::VEC4:
				setUniform4f(uniform->getLocation(), *(Maths::vec4*) & data[uniform->getOffset()]);
				break;
			case ShaderUniformDeclaration::Type::MAT3:
				// TODO: SetUniformMat3(uniform->GetLocation(), *(maths::mat3*)&data[uniform->GetOffset()]);
				break;
			case ShaderUniformDeclaration::Type::MAT4:
				setUniformMat4(uniform->getLocation(), *(Maths::mat4*) & data[uniform->getOffset()]);
				break;
			default:
				CORE_ASSERT(false, "Unknown type!");
			}
		}

		void Shader::resolveAndSetUniform(uint index, byte* data)
		{
			ShaderUniformDeclaration* uniform = m_Uniforms[index];
			resolveAndSetUniform(uniform, data);
		}

		void Shader::setUniform1i(uint location, int value)
		{
			glUniform1i(location, value);
		}

		void Shader::setUniform1iv(uint location, int* value, int count)
		{
			glUniform1iv(location, count, value);
		}

		void Shader::setUniform1f(uint location, float value)
		{
			glUniform1f(location, value);
		}

		void Shader::setUniform1fv(uint location, float* value, int count)
		{
			glUniform1fv(location, count, value);
		}

		void Shader::setUniform2f(uint location, const Maths::vec2& value)
		{
			glUniform2f(location, value.x, value.y);
		}

		void Shader::setUniform3f(uint location, const Maths::vec3& value)
		{
			glUniform3f(location, value.x, value.y, value.z);

		}

		void Shader::setUniform4f(uint location, const Maths::vec4& value)
		{
			glUniform4f(location, value.x, value.y, value.z, value.w);
		}

		void Shader::setUniformMat4(uint location, const Maths::mat4& mat)
		{
			glUniformMatrix4fv(location, 1, GL_FALSE, mat.elements);
		}

	}
}