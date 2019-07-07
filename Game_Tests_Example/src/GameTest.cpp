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
	Label* fps;
	Sprite* sprite;
	Shader* shader;
	Shader* shader1;
	Maths::vec3 mask;

public:
	GameTest() 
	{
	}

	~GameTest() 
	{
		delete layer;
		Font_Manager::clean();
		Sound_Manager::clean();
	}

	void init() override
	{

		window = createWindow("Test", 960, 540);
		C_Manager = new Control_Manager();

		// WAIT FOR THE WINDOW TO BE INITIALIZED !!
		Shader_Manager::init();
		Sound_Manager::init();

		window->setControl(C_Manager);
		shader =  Shader_Manager::get("DefaultShader");
		shader1 = Shader_Manager::get("DefaultShader");
		layer = new Layer(new Batch2DRenderer(), shader, Maths::mat4::Orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
		layerUI = new Layer(new Batch2DRenderer(), shader1, Maths::mat4::Orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
		sprite = new Sprite(0.0f, 0.0f, 4, 4, new Texture("tb","Assets/Test/awesomeface.png"));
		layer->add(sprite);

		for (float y = -9.0f; y < 9.0f; y+=1.0) {		

				for (float x = -16.0f; x < 16.0f; x+=1.0) {
		
				if (rand() % 4 == 0) 
				{
					int r = rand() % 256;

					int col = 0xffff00 << 8 | r;

					layer->add(new Sprite(x, y, 0.9f, 0.9f, col));
				}				
				else
					layer->add(new Sprite(x, y, 0.9f, 0.9f, Texture_Manager::get("tb")));

				}

		}

		Texture::setWrap(TextureWrap::CLAMP_TO_BORDER);
		layer->setMask(new Texture("Mask", "Assets/Test/mask.tif"));
		layerUI->setMask(new Texture("Mask2", "Assets/Test/tb.png"));
		shader->enable();
		shader->setUniformMat4("mask_matrix", Maths::mat4::Translate(mask));

		Font_Manager::add(new Font("SourceSansPro", "Assets/Test/SourceSansPro-Light.ttf", 24));
		fps = new Label("SourceSansPro", -15.5f, 7.8f, CONSOLE_COLOR_RED);
		layerUI->add(fps);

		Sound_Manager::add(new Sound("test", "Assets/Test/untitled.wav"));
	}

	void tick() override
	{
		unsigned int f = m_Fps;
		fps->setText(f, " fps");
		CORE_INFO("x= ", mask.x, " y= ", mask.y);
		CORE_INFO(getUPS(), " ups, ", getFPS(), " fps");
	}

	void update() override
	{
		float speed = 0.05f;
		if (C_Manager->isKeyPressed(GLFW_KEY_W))
			mask.y += speed;
		if (C_Manager->isKeyPressed(GLFW_KEY_S))
			mask.y -= speed;
		if (C_Manager->isKeyPressed(GLFW_KEY_A))
			mask.x -= speed;
		if (C_Manager->isKeyPressed(GLFW_KEY_D))
			mask.x += speed;

		static Maths::vec3 scale(1, 1, 1);
		if (C_Manager->isKeyPressed(GLFW_KEY_W))
		{
			scale.x += speed;
			scale.y += speed;
		}
		else if (C_Manager->isKeyPressed(GLFW_KEY_S))
		{
			scale.x -= speed;
			scale.y -= speed;
		}
		Sound_Manager::update();
		double x, y;
		C_Manager->getMousePosition(x, y);

		shader->enable();
		//shader->setUniform2f("light_pos", Maths::vec2((float)(x * 32.0f / window->getWidth() - 16.0f), (float)(9.0f - y * 18.0f / window->getHeight())));
		shader->setUniformMat4("mask_matrix", Maths::mat4::Translate(mask) * Maths::mat4::Scale(scale));
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
