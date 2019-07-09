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
	Label* debugInfo;
	Sprite* sprite;
	Shader* shader;
	Shader* shader1;
	Mask* mask;
	Batch2DRenderer* B2R;

public:
	GameTest() 
		: Application ("Test", 1280, 720)
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
		uint x = 1280;
		uint y = 720;
		C_Manager = new Control_Manager();

		// WAIT FOR THE WINDOW TO BE INITIALIZED !!
		Shader_Manager::init();
		Sound_Manager::init();

		window->setControl(C_Manager);
		shader = Shader_Manager::DefaultShader();
		shader1 = Shader_Manager::DefaultShader();
		B2R = new Batch2DRenderer(Maths::tvec2<uint>(x, y));
		layer = new Layer(B2R, shader, Maths::mat4::Orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
		layerUI = new Layer(new Batch2DRenderer(Maths::tvec2<uint>(x, y)), shader1, Maths::mat4::Orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
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

		debugInfo = new Label("SourceSansPro12", -15.5f, 6.8f, DEBUG_COLOR_WHITE);
		layer->add(debugInfo);

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
			((Batch2DRenderer*)layer->m_Renderer)->setRenderTarget(RenderTarget::SCREEN);
		if (C_Manager->isKeyPressed(GLFW_KEY_1))
			((Batch2DRenderer*)layer->m_Renderer)->setRenderTarget(RenderTarget::BUFFER);

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
		//mask->SetModifier(pos, scale);
		debugInfo->m_Text = std::to_string(size.x) + ", " + std::to_string(size.y);
		((Batch2DRenderer*)layer->m_Renderer)->setViewportSize(size);
		((Batch2DRenderer*)layer->m_Renderer)->setScreenSize(Maths::tvec2<uint>(window->getWidth(), window->getHeight()));
	}

	void render() override
	{
		//window->clear();
		shader->enable();
		layer->render();
		shader1->enable();
		layerUI->render();
		//window->update();
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
