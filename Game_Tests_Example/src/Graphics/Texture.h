#pragma once

#include <iostream>
#include <string>
#include <Utils/Log.h>
#include <GLEW/glew.h>

class RETexture 
{
public:
	static RETexture*dirt, *stone;

public:
	RETexture(const std::string& file);
	static void destroy();
	static void load();
	void enable();
	void disable();

private:
	GLuint texture;
	GLuint loadFile(const std::string& filepath);

};