#pragma once

#include "Entity.h"

#include <Managers/Control_Manager.h>
#include <Init/Window.h>

class Player : public  Entity 
{
private:
	Maths::vec3 rotation;
	float mouse_sensitivity;
	float dy;
	const float JUMP_HEIGHT;
	bool jumping;
	bool light;
	float speed;
	VertArray* target;
	Core::Manager::Control_Manager& C_Manager;
	Core::Init::Window& m_Window;
	bool m_Wireframe;

public:
	Player(const Maths::vec3& spawn);
	void update();
	void render();
};