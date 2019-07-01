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

#include "Rendering/Renderer/Batch2DRenderer.h"
#include "Rendering/Renderer/Models/Static_Sprite.h"
#include "Rendering/Renderer/Models/Sprite.h"

#include "Test/Layers/TopLayer.h"

#include <time.h>

#include <Utils/Timer.h>

using namespace Utils;
using namespace Core::Init;
using namespace Core::Manager;
using namespace Core::Rendering;

#define BATCH_RENDERER		1
#define TEST_50K_SPRITES	0

int main() {

	Window window("Test", 800, 600);

	Control_Manager* C_Manager = new Control_Manager();
	window.setControl(C_Manager);

	Shader* s1 = new Shader("Assets/Shaders/vertex_shader_test.glsl", "Assets/Shaders/fragment_shader_test.glsl");
	Shader* s2 = new Shader("Assets/Shaders/vertex_shader_test.glsl", "Assets/Shaders/fragment_shader_test.glsl");
	Shader& shader1 = *s1;
	Shader& shader2 = *s2;
	shader1.enable();
	shader2.enable();

	std::vector<Renderable2D*> sprites;

	srand(time(NULL));
	   
	// SETTING LAYER 1 (Top Layer)
	Core::Tests::TopLayer TLayer1(&shader1);
	TLayer1.add(new Sprite(-2, -2, 4, 4, Maths::vec4(1, 0, 1, 1)));

	// SETTING LAYER 2 (Bottom Layer)
	Core::Tests::TopLayer TLayer2(&shader2);

#if TEST_50K_SPRITES
	
	for (float y = -9.0f; y < 9.0f; y += 0.1) {		

		for (float x = -16.0f; x < 16.0f; x += 0.1) {
		
			TLayer2.add(new Sprite(x, y, 0.04f, 0.04f, Maths::vec4(rand() % 1000 / 1000.0f, 0.3f, 0.5f, 1)));

		}

	}

#else

	Sprite* button = new Sprite(-15.0f, 5.0f, 6, 3, Maths::vec4(1, 1, 1, 1));
	TLayer2.add(button);
	TLayer2.add(new Sprite(0.5f, 0.5f, 5.0f, 2.0f, Maths::vec4(1, 0, 1, 1)));

#endif

	Sprite sprite(5, 5, 4, 4, Maths::vec4(1, 0, 1, 1));
	Sprite sprite2(7, 1, 2, 3, Maths::vec4(0.2f, 0, 1, 1));
	Batch2DRenderer renderer;

	// SHADER 1
	shader1.setUniform2f("light_pos", Maths::vec2(4.0f, 1.5f));
	Maths::mat4 ortho = Maths::mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
	shader1.setUniformMat4("pr_matrix", ortho);

	// SHADER 2
	shader2.setUniform2f("light_pos", Maths::vec2(4.0f, 1.5f));


	Timer time;
	float timer = 0.0f;
	unsigned int fps = 0;

	while (!window.closed()) {
		window.clear();
		double x, y;
		C_Manager->getMousePosition(x, y);
		// WHEN MULTIPLE SHADER. SHADERS MUST BE ENABLED !!!
		shader1.enable();
		shader1.setUniform2f("light_pos", Maths::vec2((float)(x * 32.0f / 960.0f - 16.0f)*3.0f, (float)(9.0f - y * 18.0f / 540.0f)*3.0f));

		shader2.enable();
		shader2.setUniform2f("light_pos", Maths::vec2((float) (x * 32.0f / 960.0f - 16.0f), (float)(9.0f - y * 18.0f / 540.0f)));

		TLayer1.render();
		TLayer2.render();

		window.update();
		fps++;
		if (time.elapsed() - timer > 1.0f) {
			timer += 1.0f;
			printf("%d fps\n", fps);
			fps = 0;
		}
	}

	return 0;
}