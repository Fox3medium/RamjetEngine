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
#include "Rendering/Renderer/Groups/Group.h"


#include "Test/Layers/TopLayer.h"

#include <time.h>

#include <Utils/Timer.h>// NEEDS TO BE OVER FREE IMAGE !!!!!!
#include "Rendering/Texture/Texture.h"

using namespace Utils;
using namespace Core::Init;
using namespace Core::Manager;
using namespace Core::Rendering;

#define BATCH_RENDERER		1
#define TEST_50K_SPRITES	1

int main() {

	Window window("Test", 800, 600);

	Control_Manager* C_Manager = new Control_Manager();
	window.setControl(C_Manager);

	Shader* s1 = new Shader("Assets/Shaders/vertex_shader_test.glsl", "Assets/Shaders/fragment_shader_test.glsl");
	Shader& shader1 = *s1;
	shader1.enable();


	std::vector<Renderable2D*> sprites;

	srand(time(NULL));
	   
	// SETTING LAYER 1 (Top Layer)
	/*Core::Tests::TopLayer TLayer1(&shader1);
	TLayer1.add(new Sprite(-2, -2, 4, 4, Maths::vec4(0.3, 0.5, 0.6, 1)));*/

	// SETTING LAYER 2 (Bottom Layer)
	Core::Tests::TopLayer TLayer2(&shader1);
	//Core::Tests::TopLayer TLayer3(&shader3);
	
	for (float y = -9.0f; y < 9.0f; y+=0.1) {		

		for (float x = -16.0f; x < 16.0f; x+=0.1) {
		
			TLayer2.add(new Sprite(x, y, 0.09f, 0.09f, Maths::vec4(rand() % 1000 / 1000.0f, 0.3f, 0.5f, 1)));

		}

	}

	// Declare the renderer
	Batch2DRenderer renderer;

	Maths::mat4 ortho = Maths::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f);

	// SHADER 3
	glActiveTexture(GL_TEXTURE0);
	Texture texture("Assets/Test/747.png");
	texture.bind();
	shader1.enable();
	shader1.setUniform1i("tex", 0); //0 because Texture is set on chanel 0
	shader1.setUniform2f("light_pos", Maths::vec2(4.0f, 1.5f));
	shader1.setUniformMat4("pr_matrix", ortho);

	Timer time;
	float timer = 0.0f;
	unsigned int fps = 0;

	while (!window.closed()) {
		window.clear();
		double x, y;
		C_Manager->getMousePosition(x, y);
		// WHEN MULTIPLE SHADER. SHADERS MUST BE ENABLED !!!
		shader1.enable();
		shader1.setUniform2f("light_pos", Maths::vec2((float)(x * 32.0f / 960.0f - 16.0f), (float)(9.0f - y * 18.0f / 540.0f)));

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
