#pragma once

#include <map>
#include <Rendering/Renderer/Shader/Shader.h>

namespace Core {
	
	using namespace Rendering;

	namespace Manager {
	
		class Shader_Manager
		{
		private:
			static std::map <std::string, Shader*> m_Shaders;
			static std::map <std::string, GLuint> m_SID;

		public:
			static void init();
			static Shader* add(const std::string& name, Shader* shader);
			/*return Shader*/
			static Shader* get(const std::string& name);
			/*Return shader's ID*/
			static GLuint getSID(const std::string& name);
			static void clean();

			static Shader* FromFile(const std::string& name, const char* vertPath, const char* fragPath);
			static Shader* FromSource(const std::string& name, const char* vertSrc, const char* fragSrc);

			static Shader* DefaultShader();
			static Shader* BasicLightShader();
			static Shader* SimpleShader();

		private:
			Shader_Manager() {}

		};

	}

}

