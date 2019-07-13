#include <RamjetCore.h>

#include "Layer/TestLayer.h"
#include "Layer/Test3D.h"

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
	Layer2D* layer;
	Layer2D* layerUI;
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
		
		//pushLayer(new TestLayer());
		pushLayer(new Test3D());
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
