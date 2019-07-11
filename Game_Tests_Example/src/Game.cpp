#include "Game.h"
#include "Graphics/Shaders.h"
#include <Managers/Managers.h>

Core::Init::Window* Game::WindowHandle = nullptr;
Core::Manager::Control_Manager* Game::ControleHandle = nullptr;

Game::Game()
	: Application("CraftTest", 1280, 720)
{
}

Game::~Game()
{
	delete m_Level;
}

void Game::init()
{	
	Application::init();

	Core::Sound_Manager::add(new Core::Audio::Sound("test", "Assets/Test/untitled.wav"));

	ControleHandle = C_Manager;
	WindowHandle = window;
	WindowHandle->setControl(ControleHandle);
	Shaders::Init();
	RETexture::load();
	m_Level = new Level();
}
