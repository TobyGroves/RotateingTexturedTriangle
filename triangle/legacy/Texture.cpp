#include "Texture.h"
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <exception>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "stb_image.h"

#include <iostream>

Texture::Texture(std::string TextureLocation)
{

	textureLoc = TextureLocation.c_str();
	// image import 

	int w = 0;
	int h = 0;
	int channels = 0;

	unsigned char *data = stbi_load(textureLoc, &w, &h, &channels, 4);

	if (!data)
	{
		throw std::exception();
	}

	// create and bind texture

	textureId = 0;
	glGenTextures(1, &textureId);

	if (!textureId)
	{
		throw std::exception();
	}

	glBindTexture(GL_TEXTURE_2D, textureId);

	//upload the image data to the gpu texture unit
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	//free the loaded data as its on the gpu
	free(data);

	//generate mipmaps for correct mapping

	glGenerateMipmap(GL_TEXTURE_2D);

	//Unbind texture as finished operating
	glBindTexture(GL_TEXTURE_2D, 0);

	std::cout<< "bob" << std::endl;


}

GLuint Texture::getId()
{
	return textureId;
}