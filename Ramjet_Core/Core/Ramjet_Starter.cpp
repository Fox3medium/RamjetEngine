#include "Init/Window.h"
#include <Utils/String.h>
#include <Utils/Static/CInOut.h>
#include <Utils/Maths/maths.h>
#include <Utils/Fileutils.h>
#include "Rendering/Renderer/Shader/Shader.h"
#include "Managers/Control_Manager.h"
#include "Rendering/Renderer/Buffers/Buffers.h"
#include "Rendering/Renderer/Simple2DRenderer.h"
#include "Rendering/Renderer/Renderer2D.h"

using namespace Utils;
using namespace Core::Init;
using namespace Core::Manager;
using namespace Core::Rendering;

int main() {

	Window window("Test", 800, 600);
	//glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	Control_Manager* C_Manager = new Control_Manager();
	window.setControl(C_Manager);

	Shader shader("Assets/Shaders/vertex_shader_test.glsl", "Assets/Shaders/fragment_shader_test.glsl");
	shader.enable();

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
	shader.setUniformMat4("pr_matrix", ortho);
	shader.setUniformMat4("ml_matrix", mat4::translation(vec3(4,3,0)));
	shader.setUniform4f("color", vec4(0.0f, 0.3f, 0.8f, 1.0f));
	shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));

	Renderable2D sprite(vec3(5, 5, 0), vec2(4, 4), vec4(1, 0, 0, 1), shader);
	Renderable2D sprite1(vec3(7, 1, 0), vec2(2, 5), vec4(0, 1, 0, 1), shader);

	Simple2DRenderer renderer;

	while (!window.closed()) {
		window.clear();
		double x, y;
		C_Manager->getMousePosition(x, y);
		shader.setUniform2f("light_pos", vec2((float) (x * 16.0f / 960.0f),(float) (9.0f - y * 9.0f / 540.0f )));
		
		renderer.submit(&sprite);
		renderer.submit(&sprite1);
		renderer.flush();

		window.update();
	}

	return 0;
}