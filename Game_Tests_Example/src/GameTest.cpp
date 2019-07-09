#include <App/Application.h>

// MEMORY LEAK CHECKER
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

#define WIDTH 1280
#define HEIGHT 720


using namespace Core::Rendering;
using namespace Core::Manager;
using namespace Core::Init;
using namespace Core::Audio;
using namespace Utils;

class GameTest : public App::Application {

private:
	Control_Manager* C_Manager;
	Layer* layer;
	Layer* layerUI;
	Label* fps;
	Label** debugInfo;
	Sprite* sprite;
	Shader* shader;
	Shader* shader1;
	Mask* mask;
	Batch2DRenderer* B2R;

public:
	GameTest() 
		: Application ("Test", WIDTH, HEIGHT)
	{
	}

	~GameTest() 
	{
		delete layer;
		Font_Manager::clean();
		Sound_Manager::clean();
		Shader_Manager::clean();
	}

	void init() override
	{
		App::Application::init();
		C_Manager = new Control_Manager();

		// WAIT FOR THE WINDOW TO BE INITIALIZED !!
		Shader_Manager::init();
		Sound_Manager::init();

		window->setControl(C_Manager);
		shader = Shader_Manager::DefaultShader();
		shader1 = Shader_Manager::DefaultShader();
		B2R = new Batch2DRenderer(Maths::tvec2<uint>(WIDTH, HEIGHT));
		layer = new Layer(B2R, shader, Maths::mat4::Orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
		((Batch2DRenderer*)layer->m_Renderer)->setRenderTarget(RenderTarget::SCREEN);
		((Batch2DRenderer*)layer->m_Renderer)->addPostFXPass(
			new PostFXPass(Shader_Manager::FromFile("PostFX", "Assets/Shaders/postFXVert.glsl", "Assets/Shaders/postFXFrag.glsl")));
		((Batch2DRenderer*)layer->m_Renderer)->setPostFX(false);
		Texture_Manager::add(new Texture("tb", "Assets/Test/747.png"));
		Texture_Manager::add(new Texture("747", "Assets/Test/wall.jpg"));
		sprite = new Sprite(0.0f, 0.0f, 4, 4, Texture_Manager::get("tb"));

		for (float y = -9.0f; y < 9.0f; y+=1.0) {		

				for (float x = -16.0f; x < 16.0f; x+=1.0) {
		
				if (rand() % 4 == 0) 
				{
					int r = rand() % 256;
					int g = rand() % 256;
					int b = rand() % 256;

					int col = 0xff << 24 | b << 16 | g << 8 | r;

					layer->add(new Sprite(x, y, 0.9f, 0.9f, col));
				}				
				else
					layer->add(new Sprite(x, y, 0.9f, 0.9f, Texture_Manager::get("747")));

				}

		}
		layer->add(sprite);
		

		Texture::setWrap(TextureWrap::CLAMP_TO_BORDER);;
		mask = new Mask(new Texture("Mask", "Assets/Test/mask.tif"));
		layer->setMask(mask);

		Font_Manager::add(new Font("SourceSansPro", "Assets/Test/SourceSansPro-Light.ttf", 24));
		fps = new Label("SourceSansPro12", -15.5f, 7.8f, DEBUG_COLOR_WHITE);
		layer->add(fps);

		debugInfo = new Label*[10];
		debugInfo[0] = new Label("SourceSansPro12", -15.5f, 6.8f, DEBUG_COLOR_WHITE);
		debugInfo[1] = new Label("SourceSansPro12", -15.5f, 5.8f, DEBUG_COLOR_WHITE);
		layer->add(debugInfo[0]);
		layer->add(debugInfo[1]);

		//Sound_Manager::add(new Sound("test", "Assets/Test/untitled.wav"));
	}

	void tick() override
	{
		fps->setText(getFPS(), " fps");
		CORE_INFO(getUPS(), " ups, ", getFPS(), " fps");
	}

	void update() override
	{
		static Maths::vec3 pos(0, 0, 0);
		float speed = 0.05f;
		if (C_Manager->isKeyPressed(GLFW_KEY_W))
			pos.y += speed;
		if (C_Manager->isKeyPressed(GLFW_KEY_S))
			pos.y -= speed;
		if (C_Manager->isKeyPressed(GLFW_KEY_A))
			pos.x -= speed;
		if (C_Manager->isKeyPressed(GLFW_KEY_D))
			pos.x += speed;

		if (C_Manager->isKeyPressed(GLFW_KEY_2))
			((Batch2DRenderer*)layer->m_Renderer)->setRenderTarget(layer->m_Renderer->getRenderTarget() == RenderTarget::SCREEN ? RenderTarget::BUFFER : RenderTarget::SCREEN);
		if (C_Manager->isKeyPressed(GLFW_KEY_1))
			((Batch2DRenderer*)layer->m_Renderer)->setPostFX(!layer->m_Renderer->getPostFX());

		static Maths::vec3 scale(0, 0, 0);
		static Maths::tvec2<uint> size = ((Batch2DRenderer*)layer->m_Renderer)->getViewportSize();;
		if (C_Manager->isKeyPressed(GLFW_KEY_Q))
		{
			size.x+=16;
			size.y+=9;
		}
		else if (C_Manager->isKeyPressed(GLFW_KEY_E))
		{
			size.x-=16;
			size.y-=9;
		}

		if (size.x > 10000)
			size.x = 0;
		if (size.y > 10000)
			size.y = 0;

		Sound_Manager::update();
		double x, y;
		C_Manager->getMousePosition(x, y);

		debugInfo[0]->m_Text = std::to_string(size.x) + ", " + std::to_string(size.y);
		debugInfo[1]->m_Text = layer->m_Renderer->getRenderTarget() == RenderTarget::SCREEN ? "Screen" : "Buffer";
	}

	void render() override
	{
		shader->enable();
		layer->render();
	}	

};

#include <iostream>

int main()
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	GameTest game;
	game.start();
	_CrtDumpMemoryLeaks();
	return 0;
}
