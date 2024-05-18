#include "../Lamina/include/GL/texture.hpp"

lm::Texture2D::Texture2D(std::string path)
{
	LoadFromFile(&path[0]);
}

int lm::Texture2D::LoadFromFile(const char* path)
{
	textureData = stbi_load(path, &width, &height, &channels, 0);
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	if (textureData)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (channels == STBI_grey) glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, textureData);
		else if (channels == STBI_grey_alpha) glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, width, height, 0, GL_RG, GL_UNSIGNED_BYTE, textureData);
		else if(channels == STBI_rgb) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
		else if (channels == STBI_rgb_alpha) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
		else return 0;
		stbi_image_free(textureData);

		return 1;
	}
	else
	{
		return 0;
		std::cout << "Failed to load texture: " << path << std::endl;
	}
}

int lm::Texture2D::LoadFromData(unsigned char* data, int _height, int _width, int _channels)
{
	height = _height;
	width = _width;
	channels = _channels;
	textureData = data;
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	if (textureData)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (channels == STBI_grey) glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, _width, _height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
		else if (channels == STBI_grey_alpha) glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, _width, _height, 0, GL_RG, GL_UNSIGNED_BYTE, data);
		else if (channels == STBI_rgb) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		else if (channels == STBI_rgb_alpha) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		else return 0;
		stbi_image_free(textureData);

		return 1;
	}
	else
	{
		return 0;
		std::cout << "Failed to load texture" << std::endl;
	}
}