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

#include <time.h>

#define BATCH_RENDERER 1

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

	Maths::mat4 ortho = Maths::mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
	shader.setUniformMat4("pr_matrix", ortho);

	/*shader.setUniformMat4("ml_matrix", mat4::translation(vec3(4,3,0)));
	Static_Sprite sprite(5.0f, 5.0f, 4.0f, 4.0f, vec4(1, 0, 0, 1), shader);
	Static_Sprite sprite1(7.0f, 1.0f, 2.0f, 5.0f, vec4(0, 1, 0, 1), shader);*/

	std::vector<Renderable2D*> sprites;

	srand(time(NULL));

	for (float y = 0; y < 9.0f; y += 0.05) {

		for (float x = 0; x < 16.0f; x += 0.05) {
		
			sprites.push_back(new
#if BATCH_RENDERER
				Sprite
#else
				Static_Sprite
#endif
				(x, y, 0.04f, 0.04f, Maths::vec4(rand() % 1000 / 1000.0f, 0.3f, 0.5f, 1)
#if !BATCH_RENDERER
					, shader
#endif
					));

		}

	}

#if BATCH_RENDERER
	Sprite sprite(5, 5, 4, 4, Maths::vec4(1, 0, 1, 1));
	Sprite sprite2(7, 1, 2, 3, Maths::vec4(0.2f, 0, 1, 1));
	Batch2DRenderer renderer;
#else
	Static_Sprite sprite(5, 5, 4, 4, Maths::vec4(1, 0, 1, 1), shader);
	Static_Sprite sprite2(7, 1, 2, 3, Maths::vec4(0.2f, 0, 1, 1), shader);
	Simple2DRenderer renderer;
#endif

	shader.setUniform4f("color", Maths::vec4(0.2f, 0.3f, 0.8f, 1.0f));
	shader.setUniform2f("light_pos", Maths::vec2(4.0f, 1.5f));

	while (!window.closed()) {
		window.clear();
		double x, y;
		C_Manager->getMousePosition(x, y);
		shader.setUniform2f("light_pos", Maths::vec2((float) (x * 16.0f / 960.0f),(float) (9.0f - y * 9.0f / 540.0f )));

#if BATCH_RENDERER
		renderer.begin();
#endif
		for (int i = 0; i < sprites.size(); i++)
		{
			renderer.submit(sprites[i]);
		}
#if BATCH_RENDERER
		renderer.end();
#endif
		renderer.flush();

		window.update();
	}

	return 0;
}