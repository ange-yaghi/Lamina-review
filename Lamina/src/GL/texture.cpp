#include "../Lamina/include/GL/texture.hpp"

lm::Texture2D::Texture2D(std::string path)
{
	textureData = stbi_load(&path[0], &height, &width, &channels, 0);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	if (textureData)
	{
		glTexImage2D(texture, 0, GL_RGB, width, height, 1, GL_RGB, GL_UNSIGNED_INT, textureData);
	}
	else std::cout << "Failed to load texture: " << path << std::endl;
	stbi_image_free(textureData);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

int lm::Texture2D::LoadFromFile(std::string path)
{
	textureData = stbi_load(&path[0], &height, &width, &channels, 0);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	if (textureData)
	{
		glTexImage2D(texture, 0, GL_RGB, width, height, 1, GL_RGB, GL_UNSIGNED_INT, textureData);
		return 1;
	}
	else
	{
		return 0;
		std::cout << "Failed to load texture: " << path << std::endl;
	}
	stbi_image_free(textureData);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}