#include "Shader_Manager.h"

namespace Core {

	using namespace Rendering;

	namespace Manager {

		std::map<std::string, Shader* > Shader_Manager::m_Shaders;
		std::map<std::string, GLuint > Shader_Manager::m_SID;

		Shader* Shader_Manager::add(std::string name, Shader* shader)
		{
			m_Shaders[name] = shader;
			m_SID[name] = shader->getShaderID();
			return m_Shaders[name];
		}

		Shader* Shader_Manager::get(const std::string& name)
		{
			std::map<std::string, Shader*>::iterator i = m_Shaders.find(name);
			if (i != m_Shaders.end())
				return m_Shaders[name];
			return DefaultShader();
		}

		GLuint Shader_Manager::getSID(const std::string& name)
		{
			std::map<std::string, GLuint>::iterator i = m_SID.find(name);
			if (i != m_SID.end())
				return m_SID[name];
			return DefaultShader()->getShaderID();
		}

		void Shader_Manager::clean()
		{
			m_Shaders.clear();
		}

		Shader* Shader_Manager::FromFile(const std::string& name, const char* vertPath, const char* fragPath)
		{
			return add(name, new Shader(name, vertPath, fragPath, false));
		}

		Shader* Shader_Manager::FromSource(const std::string& name, const char* vertSrc, const char* fragSrc)
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

		const char* default_shader_vert =
			"#version 330 core\n"
			"\n"
			"layout (location = 0) in vec4 position;\n"
			"layout (location = 1) in vec2 uv;\n"
			"layout (location = 2) in float tid;\n"
			"layout (location = 3) in vec4 color;\n"
			"\n"
			"uniform mat4 pr_matrix;\n"
			"uniform mat4 vw_matrix = mat4(1.0);\n"
			"uniform mat4 ml_matrix = mat4(1.0);\n"
			"\n"
			"uniform mat4 mask_matrix;\n"
			"\n"
			"out DATA\n"
			"{\n"
			"	vec4 position;\n"
			"	vec2 uv;\n"
			"	float tid;\n"
			"	vec4 color;\n"
			"\n"
			"	vec2 mask_uv;\n"
			"} vs_out;\n"
			"\n"
			"void main()\n"
			"{\n"
			"	gl_Position = pr_matrix * vw_matrix * ml_matrix * position;\n"
			"	vs_out.position = ml_matrix * position;\n"
			"	vs_out.uv = uv;\n"
			"	vs_out.tid = tid;\n"
			"	vs_out.color = color;\n"
			"	vs_out.mask_uv = (mask_matrix * gl_Position).xy * 0.5 + 0.5;\n"
			"}\n";

		const char* default_shader_frag =
			"#version 330 core\n"
			"\n"
			"layout (location = 0) out vec4 color;\n"
			"\n"
			"in DATA\n"
			"{\n"
			"	vec4 position;\n"
			"	vec2 uv;\n"
			"	float tid;\n"
			"	vec4 color;\n"
			"\n"
			"	vec2 mask_uv;\n"
			"} fs_in;\n"
			"\n"
			"uniform sampler2D textures[31];\n"
			"uniform sampler2D mask_texture;\n"
			"\n"
			"void main()\n"
			"{\n"
			"	vec4 texColor = fs_in.color;\n"
			"	if (fs_in.tid > 0.0)\n"
			"	{\n"
			"		int tid = int(fs_in.tid - 0.5);\n"
			"		texColor = fs_in.color * texture(textures[tid], fs_in.uv);\n"
			"	}\n"
			"	vec4 maskColor = texture(mask_texture, fs_in.mask_uv);\n"
			"	color = texColor * maskColor; // vec4(1.0 - maskColor.x, 1.0 - maskColor.y, 1.0 - maskColor.z, 1.0);\n"
			"}\n";

		const char* basic_light_shader_vert =
			"#version 330 core\n"
			"\n"
			"layout (location = 0) in vec4 position;\n"
			"layout (location = 1) in vec2 uv;\n"
			"layout (location = 2) in float tid;\n"
			"layout (location = 3) in vec4 color;\n"
			"\n"
			"uniform mat4 pr_matrix;\n"
			"uniform mat4 vw_matrix = mat4(1.0);\n"
			"uniform mat4 ml_matrix = mat4(1.0);\n"
			"\n"
			"out DATA\n"
			"{\n"
			"	vec4 position;\n"
			"	vec2 uv;\n"
			"	float tid;\n"
			"	vec4 color;\n"
			"} vs_out;\n"
			"\n"
			"void main()\n"
			"{\n"
			"	gl_Position = pr_matrix * vw_matrix * ml_matrix * position;\n"
			"	vs_out.position = ml_matrix * position;\n"
			"	vs_out.uv = uv;\n"
			"	vs_out.tid = tid;\n"
			"	vs_out.color = color;\n"
			"}\n";

		const char* basic_light_shader_frag =
			"#version 330 core\n"
			"\n"
			"layout (location = 0) out vec4 color;\n"
			"\n"
			"uniform vec4 colour;\n"
			"uniform vec2 light_pos;\n"
			"\n"
			"in DATA\n"
			"{\n"
			"	vec4 position;\n"
			"	vec2 uv;\n"
			"	float tid;\n"
			"	vec4 color;\n"
			"} fs_in;\n"
			"\n"
			"uniform sampler2D textures[32];\n"
			"\n"
			"void main()\n"
			"{\n"
			"	float intensity = 1.0 / length(fs_in.position.xy - light_pos);\n"
			"	vec4 texColor = fs_in.color;\n"
			"	if (fs_in.tid > 0.0)\n"
			"	{\n"
			"		int tid = int(fs_in.tid - 0.5);\n"
			"		texColor = fs_in.color * texture(textures[tid], fs_in.uv);\n"
			"	}\n"
			"	color = texColor * intensity;\n"
			"}\n";

		void Shader_Manager::init()
		{
			add("DefaultShader", new Shader("DefaultVertShader", default_shader_vert, default_shader_frag, true));
			add("BasicLightShader", new Shader("BasicLightShader", basic_light_shader_vert, basic_light_shader_frag, true));
		}

	}

}