#include "Shaders.h"

#include <Utils/Maths/maths.h>

Core::Rendering::Shader* Shaders::BLOCK = nullptr;
Core::Rendering::Shader* Shaders::HUD = nullptr;

void Shaders::Init()
{
	Maths::mat4 pr_matrix = Maths::mat4::Perspective(90.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
	BLOCK = new Core::Rendering::Shader("Block", "Assets/Shaders/BlockVert.glsl", "Assets/Shaders/BlockFrag.glsl");
	BLOCK->enable();
	BLOCK->setUniformMat4("pr_matrix", pr_matrix);
	BLOCK->setUniformMat4("vw_matrix", Maths::mat4::Translate(Maths::vec3(0.0f, 0.0f, -500.0f)));
	BLOCK->setUniform1i("tex_id", 0);
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
		std::cout << "OpenGL Error: " << error << std::endl;
	BLOCK->disable();

	Maths::mat4 ortho = Maths::mat4::Orthographic(-16.0f * 2.0f, 16.0f * 2.0f, 9.0f * 2.0f, -9.0f * 2.0f, -1.0f, 1.0f);
	HUD = new Core::Rendering::Shader("UI", "Assets/Shaders/UIVert.glsl", "Assets/Shaders/UIFrag.glsl");
	HUD->enable();
	HUD->setUniformMat4("pr_matrix", ortho);
	HUD->disable();
}
