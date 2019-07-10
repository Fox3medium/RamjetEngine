#include "Entity.h"

Entity::Entity()
{
}

Entity::~Entity()
{
	delete model;
}

void Entity::init(Level* level)
{
	this->level = level;
}

Maths::vec3 Entity::get_position()
{
	return position;
}
