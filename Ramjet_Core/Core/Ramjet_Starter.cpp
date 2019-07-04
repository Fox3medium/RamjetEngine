#include <Utils/Timer.h>// NEEDS TO BE OVER FREE IMAGE !!!!!!
#include "Init/Window.h"
#include <Utils/String.h>
#include <Utils/Static/CInOut.h>
#include <Utils/Maths/maths.h>
#include <Utils/Fileutils.h>

#include <freetype/ft2build.h>
#include <freetype/freetype/freetype.h>

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

#include "Rendering/Renderer/Texture/Texture.h"
#include "Rendering/Renderer/Models/Label.h"

#include <Font_Manager.h>

using namespace Utils;
using namespace Core::Init;
using namespace Core::Manager;
using namespace Core::Rendering;

int main() {

	Window window("Test", 960, 540);

	Control_Manager* C_Manager = new Control_Manager();
	window.setControl(C_Manager);

	Font_Manager::add(new Font("SourceSansPro", "Assets/Test/SourceSansPro-Light.ttf", 32));
	Font_Manager::add(new Font("SourceSansPro", "Assets/Test/SourceSansPro-Light.ttf", 24));
	Font_Manager::add(new Font("SourceSansPro", "Assets/Test/SourceSansPro-Light.ttf", 12));

	Shader* s1 = new Shader("Assets/Shaders/vertex_shader_test.glsl", "Assets/Shaders/fragment_shader_test.glsl");
	Shader* s2 = new Shader("Assets/Shaders/textVertShader.glsl", "Assets/Shaders/textFragShader.glsl");
	Shader& shader1 = *s1;
	Shader& shader2 = *s2;
	shader1.enable();
	shader2.enable();

	srand(time(NULL));
	// SETTING LAYER 1 (Top Layer)
	Core::Tests::TopLayer TLayer1(&shader2);

	// SETTING LAYER 2 (Bottom Layer)
	Core::Tests::TopLayer TLayer2(&shader1);
	//Core::Tests::TopLayer TLayer3(&shader3);

	Texture* textures[] =
	{
		new Texture("Assets/Test/test.png"),
		new Texture("Assets/Test/tb.png"),
		new Texture("Assets/Test/tc.png")
	};
	
	for (float y = -9.0f; y < 9.0f; y+=1.0) {		

		for (float x = -16.0f; x < 16.0f; x+=1.0) {
		
			if (rand() % 4 == 0) 
			{
				int r = rand() % 256;

				int col = 0xffff00 << 8 | r;

				TLayer2.add(new Sprite(x, y, 0.9f, 0.9f, col));
			}				
			else
				TLayer2.add(new Sprite(x, y, 0.9f, 0.9f, textures[rand() % 3]));

		}

	}

	Group* g = new Group(Maths::mat4::translation(Maths::vec3(-15.8f, 7.0f, 0.0f)));
	Label* fpsL = new Label("", 0.4f, 0.4f, "SourceSansPro", 12, CONSOLE_COLOR_RED);
	g->add(new Sprite(0, 0, 5, 1.5f, CONSOLE_BACKGROUND));
	g->add(fpsL);

	TLayer1.add(g);

	GLint texIDs[] =
	{
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	};

	// Declare the renderer
	Batch2DRenderer renderer;

	Maths::mat4 ortho = Maths::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f);

	// SHADER 1
	shader1.enable();
	shader1.setUniform1iv("textures", texIDs, 10); 
	shader1.setUniform2f("light_pos", Maths::vec2(4.0f, 1.5f));
	shader1.setUniformMat4("pr_matrix", ortho);

	// SHADER 1
	shader2.enable();
	shader2.setUniform1iv("textures", texIDs, 10);
	shader2.setUniform2f("light_pos", Maths::vec2(4.0f, 1.5f));
	shader2.setUniformMat4("pr_matrix", ortho);

	Timer time;
	float timer = 0.0f;
	unsigned int fps = 0;

	while (!window.closed()) {

		window.clear();
		double x, y;
		C_Manager->getMousePosition(x, y);
		// WHEN MULTIPLE SHADER. SHADERS MUST BE ENABLED !!!
		shader1.enable();
		shader1.setUniform2f("light_pos", Maths::vec2((float)(x * 32.0f / window.getWidth() -16.0f), (float)(9.0f - y * 18.0f / window.getHeight())));

		shader2.enable();

		TLayer2.render();
		TLayer1.render();

		const std::vector<Renderable2D*>& rs = TLayer2.getRenderable();
		for (int i = 0; i < rs.size(); i++)
		{
			float c = sin(window.getLastTime()) / 2 + 0.5f;
			rs[i]->setColor(Maths::vec4(c, 0, 1, 1));
		}

		window.update();
		fps++;
		if (time.elapsed() - timer > 1.0f) {
			timer += 1.0f;
			fpsL->setText(fps, " fps");
			printf("%d fps\n", fps);
			fps = 0;
		}
	}

	for (int i = 0; i < 3; i++)
		delete textures[i];

	Font_Manager::clean();

	return 0;
}
