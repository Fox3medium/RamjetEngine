#pragma once

#include "StoneBlock.h"

StoneBlock::StoneBlock(unsigned short ID) 
	: Block(ID)
{
	texture = RETexture::stone;
}