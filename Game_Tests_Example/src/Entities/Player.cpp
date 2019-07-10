#include "Player.h"
#include "../Levels/Level.h"

#include "../Game.h"

#include <Utils/Maths/maths.h>
#include "../Graphics/Shaders.h"

using namespace Maths;

Player::Player(const Maths::vec3& spawn)
	: C_Manager(*Game::ControleHandle), m_Wireframe(false), m_Window(*Game::WindowHandle),
	mouse_sensitivity(0.2f), dy(0.0f), JUMP_HEIGHT(1.5f), jumping(false), light(true), speed(0.7f)
{
	this->position = spawn;
	this->position.y = -this->position.y;
	shader = Shaders::BLOCK;

	const GLfloat TSIZE = 0.2f;
	GLfloat vertices[4 * 3] = {
		-TSIZE / 2.0f, -TSIZE / 2.0f, 0.0f,
		-TSIZE / 2.0f, TSIZE / 2.0f, 0.0f,
		TSIZE / 2.0f, TSIZE / 2.0f, 0.0f,
		TSIZE / 2.0f, -TSIZE / 2.0f, 0.0f
	};
	GLuint indices[6] = {
		0, 1, 2,
		2, 3, 0
	};

	target = new VertArray(vertices, indices, (GLfloat*)NULL, 4 * 3, 6);
	m_Window.setGrabMouse();
}

void Player::update()
{
	if (C_Manager.isKeyPressed(GLFW_KEY_W))
	{
		float xa = -Maths::sin(toRadians(rotation.y)) * speed;
		float za = Maths::cos(toRadians(rotation.y)) * speed;
		vec3 pos = vec3(position.x, position.y + 8.0f, position.z);
		vec3 rot = vec3(xa, 0.0f, za);
		//        if (level->raycast_block_id(position, rot, 32.0f) < 2 && level->raycast_block_id(pos, rot, 32.0f) < 2) {
		position.x += xa;
		position.z += za;
		//        }
	}
	if (C_Manager.isKeyPressed(GLFW_KEY_S))
	{
		float xa = Maths::sin(toRadians(rotation.y)) * speed;
		float za = -Maths::cos(toRadians(rotation.y)) * speed;
		//  if (level->raycast_collision(position, vec3(xa, za, 0.0f)) < 2) {
		position.x += xa;
		position.z += za;
		//  }
	}
	if (C_Manager.isKeyPressed(GLFW_KEY_A))
	{
		float xa = -Maths::sin(toRadians(rotation.y - 90.0f)) * speed;
		float za = Maths::cos(toRadians(rotation.y - 90.0f)) * speed;
		//  if (level->raycast_collision(position, vec3(xa, za, 0.0f)) < 2) {
		position.x += xa;
		position.z += za;
		//   }
	}
	if (C_Manager.isKeyPressed(GLFW_KEY_D))
	{
		float xa = -Maths::sin(toRadians(rotation.y + 90.0f)) * speed;
		float za = Maths::cos(toRadians(rotation.y + 90.0f)) * speed;
		// if (level->raycast_collision(position, vec3(xa, za, 0.0f)) < 2) {
		position.x += xa;
		position.z += za;
		//  }
	}
	vec3 gravity = vec3(0, -1, 0);
	bool block = level->raycast_block_id(position, gravity, 10.0f) > 1;
	if (!block || jumping)
		position.y -= dy;
	if (dy < -1.0f)
		dy = -1.0f;

	if (dy > 2.0f) dy = 2.0f;

	//    if (position.y > -48.0f) position.y = -48.0f;
	if (jumping)
		dy += 0.5f;
	if (dy > JUMP_HEIGHT)
		jumping = false;
	if (!jumping && dy > -JUMP_HEIGHT)
		dy -= 0.15f;

	if (C_Manager.isKeyPressed(GLFW_KEY_SPACE) && !jumping && block)
		jumping = true;
	if (C_Manager.isKeyPressed(GLFW_KEY_F))
		light = !light;
	// TODO: Sparky engine mouse grabbing
	if (m_Window.isMouseGrabbed())
	{
		vec2 mouse = m_Window.getMousePos();
		mouse.x = mouse.x;
		mouse.y = mouse.y;
		rotation.x += mouse.y * mouse_sensitivity;
		rotation.y += mouse.x * mouse_sensitivity;
	}
	if (C_Manager.isKeyPressed(GLFW_KEY_ESCAPE))
	{
		m_Window.setGrabMouse();
	}
	if (rotation.x < -90.0f) rotation.x = -90.0f;
	if (rotation.x > 90.0f) rotation.x = 90.0f;
	
	vec3 b = level->raycast_block(position, rotation);
	level->select_block(b);

	//if (m_Window.IsMouseButtonClicked(SP_MOUSE_LEFT))
	//{
	//	if (!m_Window.IsMouseGrabbed())
	//	{
	//		m_Window.SetMouseGrabbed(true);
	//		m_Window.SetMouseCursor(SP_NO_CURSOR);
	//	}
	//	else
	//	{
	//		unsigned short& rid = level->pick_block(position, rotation);
	//		if (rid != Level::NULL_BLOCK) rid = 1;
	//	}
	//}
	//else if (m_Window.IsMouseButtonPressed(SP_MOUSE_RIGHT))
	//{
	//	// Place block!
	//	unsigned short& bid = level->raycast_pre_block_id(position, rotation);
	//	if (bid == 1) bid = 2;
	//}
	if (C_Manager.isKeyPressed(GLFW_KEY_Q))
	{
		m_Wireframe = !m_Wireframe;
		if (m_Wireframe)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void Player::render()
{
	shader->enable();
	mat4 vw_matrix = mat4::Rotate(rotation.x, vec3(1.0f, 0.0f, 0.0f));
	vw_matrix *= mat4::Rotate(rotation.y, vec3(0.0f, 1.0f, 0.0f));
	CORE_INFO(rotation.y);
	mat4 Translation = mat4::Translate(position);
	vw_matrix *= mat4::Translate(position);
	shader->setUniformMat4("vw_matrix", vw_matrix);
	shader->setUniform3f("player_pos", vec3(-position.x, -position.y, -position.z));

	if (light)
		shader->setUniform1f("light_on", 1);
	else
		shader->setUniform1f("light_on", 0);

	shader->disable();
	Shaders::HUD->enable();
	target->render();
	Shaders::HUD->disable();
}
