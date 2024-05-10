#pragma once

#include <glad/glad.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

namespace lm
{
	class GLRenderer
	{
	public:
		static GLuint CompileShader(std::string vertexShaderPath, std::string fragmentShaderPath);
	};
}