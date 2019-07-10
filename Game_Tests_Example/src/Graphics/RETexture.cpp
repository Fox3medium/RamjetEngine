#include "RETexture.h"
#include <Rendering/Renderer/Texture/Texture.h>

RETexture* RETexture::dirt = (RETexture*)NULL;
RETexture* RETexture::stone = (RETexture*)NULL;

RETexture::RETexture(const std::string& file)
{
	texture = loadFile(file);
}

void RETexture::destroy()
{
	delete dirt;
	delete stone;
}

GLuint RETexture::loadFile(const std::string& filepath)
{
	Core::Rendering::Texture::setFilter(Core::Rendering::TextureFilter::NEAREST);
	Core::Rendering::Texture* texture = new Core::Rendering::Texture(filepath, filepath);
	return texture->getID();
}

void RETexture::load()
{
	glActiveTexture(GL_TEXTURE0);
	dirt = new RETexture("Assets/Tex/wall.jpg");
	stone = new RETexture("Assets/Tex/747.png");
}

void RETexture::enable()
{
	glBindTexture(GL_TEXTURE_2D, texture);
}

void RETexture::disable()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}