#ifndef LM_OPENGL
#define LM_OPENGL

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
#endif // !LM_OPENGL
