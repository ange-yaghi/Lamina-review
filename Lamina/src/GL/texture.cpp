#include "../Lamina/include/GL/texture.hpp"

lm::Texture2D::Texture2D(std::string path, GLint format)
{
	LoadFromFile(&path[0], format);
}

int lm::Texture2D::LoadFromFile(const char* path, GLint format)
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

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, textureData);
		stbi_image_free(textureData);

		return 1;
	}
	else
	{
		return 0;
		std::cout << "Failed to load texture: " << path << std::endl;
	}
}