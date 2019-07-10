#pragma once

#include <Rendering/Renderer/Shader/Shader.h>

class Shaders 
{
public:
	static Core::Rendering::Shader* BLOCK;
	static Core::Rendering::Shader* HUD;
public:
	static void Init();
};