#pragma once

#include <App/Application.h>
#include "Levels/Level.h"

class Game : public App::Application
{
public:
	static Core::Manager::Control_Manager* ControleHandle;
	static Core::Init::Window* WindowHandle;
private:
	Level* m_Level;
public:
	Game();
	~Game();

	void init() override;
	void update() override;
	void render() override;
};