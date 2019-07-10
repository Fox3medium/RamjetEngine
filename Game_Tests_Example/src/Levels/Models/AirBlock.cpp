#include "AirBlock.h"
#pragma once

AirBlock::AirBlock(unsigned short ID)
	: Block(ID)
{
	texture = RETexture::dirt;
}

void AirBlock::render(const Maths::vec3& position)
{
}
