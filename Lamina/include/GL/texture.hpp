#pragma once

#include "../Lamina/include/GL/imageLoader.h"
#include "glad/glad.h"
#include <iostream>
#include <string>

#define LM_TEXTURE_REPEAT			GL_REPEAT
#define LM_TEXTURE_MIRROR_REPEAT	GL_MIRRORED_REPEAT
#define LM_TEXTURE_CLAMP_TO_EDGE	GL_CLAMP_TO_EDGE
#define LM_TEXTURE_CLAMP_TO_BORDER	GL_CLAMP_TO_BORDER
#define LM_LINEAR_INTERPOLATION		GL_LINEAR
#define LM_NEAREST_INTERPOLATION	GL_NEAREST
#define LM_NEAREST_MIPMAP			GL_NEAREST_MIPMAP_NEAREST
#define LM_LINEAR_MIPMAP			GL_LINEAR_MIPMAP_LINEAR
#define LM_LINEAR_NEAREST_MIPMAP	GL_LINEAR_MIPMAP_NEAREST
#define LM_NEAREST_LINEAR_MIPMAP	GL_NEAREST_MIPMAP_LINEAR
//#define LM_RGB						GL_RGB
//#define LM_RGBA						GL_RGBA

namespace lm
{
	class Texture2D
	{
	public:
		Texture2D() : height(0), width(0), channels(0), texture(0), textureData(nullptr) {};
		Texture2D(std::string path);

		int LoadFromFile(const char* path);

		void SetWrappingMethod(GLint method)
		{
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, method);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, method);
		}

		void SetInterpolationMethod(GLint far, GLint near)
		{
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, far);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, near);
		}

		unsigned char* textureData;
		int height, width, channels;

		GLuint texture;
	};
}