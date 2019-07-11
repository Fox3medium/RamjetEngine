#pragma once

#include <map>
#include <Rendering/Renderer/Shader/Shader.h>

namespace Core {
	
	using namespace Rendering;

	namespace Manager {
	
		class Shader_Manager
		{
		private:
			static std::map <String, Shader*> m_Shaders;
			static std::map <String, GLuint> m_SID;

		public:
			static void init();
			static Shader* add(const String& name, Shader* shader);
			/*return Shader*/
			static Shader* get(const String& name);
			/*Return shader's ID*/
			static GLuint getSID(const String& name);
			static void clean();

			static Shader* FromFile(const String& name, const char* vertPath, const char* fragPath);
			static Shader* FromSource(const String& name, const char* vertSrc, const char* fragSrc);

			static Shader* DefaultShader();
			static Shader* BasicLightShader();
			static Shader* SimpleShader();

		private:
			Shader_Manager() {}

		};

	}

}

