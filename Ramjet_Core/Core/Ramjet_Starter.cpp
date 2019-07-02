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

#if 1
int main() {

	Window window("Test", 800, 600);

	Control_Manager* C_Manager = new Control_Manager();
	window.setControl(C_Manager);

	Shader* s1 = new Shader("Assets/Shaders/vertex_shader_test.glsl", "Assets/Shaders/fragment_shader_test.glsl");
	Shader* s2 = new Shader("Assets/Shaders/vertex_shader_test.glsl", "Assets/Shaders/fragment_shader_test.glsl");
	Shader* s3 = new Shader("Assets/Shaders/textVertShader.glsl", "Assets/Shaders/textFragShader.glsl");
	Shader& shader1 = *s1;
	Shader& shader2 = *s2;
	Shader& shader3 = *s3;
	shader1.enable();
	shader2.enable();
	shader3.enable();

	std::vector<Renderable2D*> sprites;

	srand(time(NULL));
	   
	// SETTING LAYER 1 (Top Layer)
	Core::Tests::TopLayer TLayer1(&shader1);
	TLayer1.add(new Sprite(-2, -2, 4, 4, Maths::vec4(1, 0, 1, 1)));

	// SETTING LAYER 2 (Bottom Layer)
	Core::Tests::TopLayer TLayer2(&shader2);
	Core::Tests::TopLayer TLayer3(&shader3);

#if TEST_50K_SPRITES
	
	for (float y = -9.0f; y < 9.0f; y += 0.1) {		

		for (float x = -16.0f; x < 16.0f; x += 0.1) {
		
			TLayer2.add(new Sprite(x, y, 0.04f, 0.04f, Maths::vec4(rand() % 1000 / 1000.0f, 0.3f, 0.5f, 1)));

		}

	}

#else

	Group* group = new Group(Maths::mat4::translation(Maths::vec3(-15.0f, 5.0f, 0.0f)));
	group->add(new Sprite(0, 0, 6, 3, Maths::vec4(1, 1, 1, 1)));

	Group* button = new Group(Maths::mat4::translation(Maths::vec3(0.5f, 0.5f, 0.0f)));
	button->add(new Sprite(0, 0, 5.0f, 2.0f, Maths::vec4(1, 0, 1, 1)));
	button->add(new Sprite(0.5f, 0.5f, 3.0f, 1.0f, Maths::vec4(0.2f, 0.3f, 0.8f, 1)));
	group->add(button);

	TLayer2.add(group);

#endif	

	Sprite sprite(5, 5, 4, 4, Maths::vec4(1, 0, 1, 1));
	Sprite sprite2(7, 1, 2, 3, Maths::vec4(0.2f, 0, 1, 1));
	Batch2DRenderer renderer;



	Maths::mat4 ortho = Maths::mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	// SHADER 3
	glActiveTexture(GL_TEXTURE0);
	Texture texture("Assets/Test/test.png");
	texture.bind();
	shader3.enable();
	shader3.setUniform1i("tex", 0); //0 because Texture is set on chanel 0
	shader3.setUniform2f("light_pos", Maths::vec2(4.0f, 1.5f));
	shader3.setUniformMat4("pr_matrix", ortho);

	// SHADER 1
	shader1.setUniform2f("light_pos", Maths::vec2(4.0f, 1.5f));	
	shader1.setUniformMat4("pr_matrix", ortho);

	// SHADER 2
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
		shader1.setUniform2f("light_pos", Maths::vec2((float)(x * 32.0f / 960.0f - 16.0f)*0.9f, (float)(9.0f - y * 18.0f / 540.0f)*0.9f));

		shader2.enable();
		shader2.setUniform2f("light_pos", Maths::vec2((float) (x * 32.0f / 960.0f - 16.0f), (float)(9.0f - y * 18.0f / 540.0f)));

		shader3.enable();
		shader3.setUniform2f("light_pos", Maths::vec2((float)(x * 32.0f / 960.0f - 16.0f), (float)(9.0f - y * 18.0f / 540.0f)));

		TLayer2.render();
		TLayer1.render();
		TLayer3.render();

		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex2f(0, 0);
		glTexCoord2f(0, 1);
		glVertex2f(0, 4);
		glTexCoord2f(1, 1);
		glVertex2f(4, 4);
		glTexCoord2f(1, 0);
		glVertex2f(4, 0);
		glEnd();

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
#else

int main() {

	const char* filename = "Assets/Test/test.png";

	//image format
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	//pointer to the image, once loaded
	FIBITMAP* dib(0);
	//pointer to the image data
	BYTE* bits(0);
	//image width and height
	unsigned int width(0), height(0);
	//OpenGL's image ID to map to
	GLuint gl_texID;

	//check the file signature and deduce its format
	fif = FreeImage_GetFileType(filename, 0);
	//if still unknown, try to guess the file format from the file extension
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(filename);
	//if still unkown, return failure
	if (fif == FIF_UNKNOWN)
		return false;

	//check that the plugin has reading capabilities and load the file
	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filename);
	//if the image failed to load, return failure
	if (!dib)
		return false;

	//retrieve the image data
	bits = FreeImage_GetBits(dib);
	unsigned int bitsPerPixel = FreeImage_GetBPP(dib);
	unsigned int pitch = FreeImage_GetPitch(dib);
	//get the image width and height

	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);
	//if this somehow one of these failed (they shouldn't), return failure
	if ((bits == 0) || (width == 0) || (height == 0))
		return false;

	for (int y = height; y > 0; y--)
	{
		BYTE* pixel = (BYTE*)bits;
		for (int x = 0; x < width; x++)
		{
			std::cout << +pixel[FI_RGBA_RED] << " " << +pixel[FI_RGBA_GREEN] << " " << +pixel[FI_RGBA_BLUE] << std::endl;
			pixel += 3;
		}
		// next line
		bits += pitch;
	}
	FreeImage_Unload(dib);	

	system("PAUSE");

	return 0;

}

#endif