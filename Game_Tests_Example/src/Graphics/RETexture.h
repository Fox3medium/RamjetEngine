#pragma once

#include <iostream>
#include <string>
#include <Core_OpenGL.h>

class RETexture 
{
public:
	static RETexture*dirt, *stone;

private:
	GLuint texture;

public:
	RETexture(const std::string& file);
	static void destroy();
	static void load();
	void enable();
	void disable();

private:
	GLuint loadFile(const std::string& filepath);

};