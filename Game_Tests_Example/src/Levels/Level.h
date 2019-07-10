#pragma once

#include <vector>
#include <Utils/Maths/maths.h>
#include <Rendering/Renderer/Shader/Shader.h>

#include "Models/Block.h"
#include "../Graphics/VertArray.h"
#include "../Entities/Entity.h"
#include "../Entities/Player.h"

class Level 
{
public:
	static unsigned short NULL_BLOCK;
	static Maths::vec3 NULL_COORD;

private:
	VertArray* floor;
	unsigned short*** blocks;
	Maths::mat4 floor_pos, floor_rot;
	std::vector<Entity*> entities;

	const int WIDTH =	16;
	const int DEPTH =	16;
	const int HEIGHT =	16;

	Maths::vec3 selected_block;

public:
	Level();
	~Level();

	void add(Entity* entity);
	void update();
	void select_block(const Maths::vec3& block);
	unsigned short& get_intersection_block(Entity* entity);
	unsigned short& get_block(const Maths::vec3& position);
	unsigned short& pick_block(const Maths::vec3& position, const Maths::vec3& rotation);
	unsigned short& raycast_collision(const Maths::vec3& position, const Maths::vec3& rotation);
	unsigned short& raycast_block_id(const Maths::vec3& position, const Maths::vec3& rotation);
	unsigned short& raycast_block_id(const Maths::vec3& position, const Maths::vec3& rotation, float distance);
	unsigned short& raycast_pre_block_id(const Maths::vec3& position, const Maths::vec3& rotation);
	Maths::vec3 raycast_block(const Maths::vec3& position, const Maths::vec3& rotation);
	void render();

};