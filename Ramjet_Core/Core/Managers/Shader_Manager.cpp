#include "Shader_Manager.h"

namespace Core {

	using namespace Rendering;

	namespace Manager {

		std::map<String, Shader* > Shader_Manager::m_Shaders;
		std::map<String, uint > Shader_Manager::m_SID;

		Shader* Shader_Manager::add(const String& name, Shader* shader)
		{
			m_Shaders[name] = shader;
			m_SID[name] = shader->getShaderID();
			return m_Shaders[name];
		}

		Shader* Shader_Manager::get(const String& name)
		{
			std::map<String, Shader*>::iterator i = m_Shaders.find(name);
			if (i != m_Shaders.end())
				return m_Shaders[name];
			return DefaultShader();
		}

		uint Shader_Manager::getSID(const String& name)
		{
			std::map<String, uint>::iterator i = m_SID.find(name);
			if (i != m_SID.end())
				return m_SID[name];
			return DefaultShader()->getShaderID();
		}

		void Shader_Manager::clean()
		{
			m_Shaders.clear();
		}

		Shader* Shader_Manager::FromFile(const String& name, const String& vertPath, const String& fragPath)
		{
			return add(name, new Shader(name, vertPath, fragPath));
		}

		Shader* Shader_Manager::FromSource(const String& name, const String& vertSrc, const String& fragSrc)
		{
			return add(name, new Shader(name, vertSrc, fragSrc, true));
		}

		Shader* Shader_Manager::DefaultShader()
		{
			return m_Shaders["DefaultShader"];
		}

		Shader* Shader_Manager::BasicLightShader()
		{
			return m_Shaders["BasicLightShader"];
		}

		Shader* Shader_Manager::SimpleShader()
		{
			return m_Shaders["SimpleShader"];
		}

		static const char* default_shader_vert = 
			"Assets/Shaders/DefaultVert.glsl"
			;

		static const char* default_shader_frag =
			"Assets/Shaders/DefaultFrag.glsl"
			;

		static const char* simple_shader_vert =
			"Assets/Shaders/SimpleVert.glsl"
			;

		static const char* simple_shader_frag =
			"Assets/Shaders/SimpleFrag.glsl"
			;

		static const char* basic_light_shader_vert =
			"Assets/Shaders/BaslicLightVert.glsl"
			;

		static const char* basic_light_shader_frag =
			"Assets/Shaders/BaslicLightFrag.glsl"
			;

		void Shader_Manager::init()
		{
			add("DefaultShader", new Shader("DefaultVertShader", default_shader_vert, default_shader_frag, false));
			add("BasicLightShader", new Shader("BasicLightShader", basic_light_shader_vert, basic_light_shader_frag, false));
			add("SimpleShader", new Shader("SimpleShader", simple_shader_vert, simple_shader_frag, false));
		}

	}

}