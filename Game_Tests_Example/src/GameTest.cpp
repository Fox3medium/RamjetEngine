#include <Core.h>


using namespace Core::Rendering;
using namespace Core::Manager;
using namespace Core::Init;
using namespace Core::Audio;
using namespace Utils;

class GameTest : public Core::Core {

private:
	Window* window;
	Control_Manager* C_Manager;
	Layer* layer;
	Layer* layerUI;
	Label* debugInfo;
	Sprite* sprite;
	Shader* shader;
	Shader* shader1;
	Mask* mask;

public:
	GameTest() 
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
		uint x = 1280;
		uint y = 720;
		window = createWindow("Test", x, y);
		C_Manager = new Control_Manager();

		// WAIT FOR THE WINDOW TO BE INITIALIZED !!
		Shader_Manager::init();
		Sound_Manager::init();

		window->setControl(C_Manager);
		shader = Shader_Manager::DefaultShader();
		shader1 = Shader_Manager::DefaultShader();
		layer = new Layer(new Batch2DRenderer(Maths::tvec2<uint>(x, y)), shader, Maths::mat4::Orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
		layerUI = new Layer(new Batch2DRenderer(Maths::tvec2<uint>(x, y)), shader1, Maths::mat4::Orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
		Texture_Manager::add(new Texture("tb", "Assets/Test/awesomeface.png"));
		Texture_Manager::add(new Texture("747", "Assets/Test/747.png"));
		sprite = new Sprite(0.0f, 0.0f, 4, 4, Texture_Manager::get("tb"));

		for (float y = -9.0f; y < 9.0f; y+=1.0) {		

				for (float x = -16.0f; x < 16.0f; x+=1.0) {
		
				if (rand() % 4 == 0) 
				{
					int r = rand() % 256;

					int col = 0xffff00 << 8 | r;

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
		debugInfo = new Label("SourceSansPro", -15.5f, 7.8f, DEBUG_COLOR_RED);
		layerUI->add(debugInfo);

		Sound_Manager::add(new Sound("test", "Assets/Test/untitled.wav"));
	}

	void tick() override
	{
		unsigned int f = m_Fps;
		debugInfo->setText(f, " fps");
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
			size.x++;
			size.y++;
		}
		else if (C_Manager->isKeyPressed(GLFW_KEY_E))
		{
			size.x--;
			size.y--;
		}

		Sound_Manager::update();
		double x, y;
		C_Manager->getMousePosition(x, y);
		mask->SetModifier(pos, scale);
		((Batch2DRenderer*)layer->m_Renderer)->setViewportSize(size);
	}

	void render() override
	{
		shader->enable();
		layer->render();
		shader1->enable();
		layerUI->render();
	}	

};

#include <iostream>

int main()
{
	GameTest game;
	game.start();
	return 0;
}
