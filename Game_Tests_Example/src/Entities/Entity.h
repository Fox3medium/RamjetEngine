#pragma once

#include "../Graphics/VertArray.h"

#include <Rendering/Renderer/Shader/Shader.h>

class Level;

class Entity 
{
protected:
	VertArray* model;
	Core::Rendering::Shader* shader; 
	Maths::vec3 position;
	Level* level;

public:
	Entity();
	virtual ~Entity();

	void init(Level* level);
	Maths::vec3 get_position();
	virtual void update() = 0;
	virtual void render() = 0;
};