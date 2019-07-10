#pragma once

#include "../../Graphics/RETexture.h"
#include "../../Graphics/VertArray.h"
#include <Utils/Maths/maths.h>
#include <Rendering/Renderer/Shader/Shader.h>

class Block 
{
public:
	static Block *air, * dirt, * stone;
	const static float SIZE;
protected:
	unsigned short ID;
	static VertArray* vao;
	Core::Rendering::Shader* shader;
	Maths::vec3 color;
	RETexture* texture;

public:
	Block(unsigned short ID);
	static void CREATE_ALL();
	static void DESTROY();

	virtual void update();
	virtual void render(const Maths::vec3& position);

private:
	void init();
};