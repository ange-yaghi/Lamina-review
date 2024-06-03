#include "../Lamina/include/GL/opengl.hpp"

GLuint lm::GLRenderer::CompileShader(std::string vertexShaderPath, std::string fragmentShaderPath)
{
	if (!glfwInit()) return GL_FALSE;
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertexShaderCode;
	std::string fragmentShaderCode;

	std::ifstream vertexCode(vertexShaderPath);
	std::ifstream fragmentCode(fragmentShaderPath);


	if (vertexCode.is_open())
	{
		std::stringstream readBuffer;
		readBuffer << vertexCode.rdbuf();
		vertexShaderCode = readBuffer.str();
		vertexCode.close();
	}
	else return GL_FALSE;

	if (fragmentCode.is_open())
	{
		std::stringstream readBuffer;
		readBuffer << fragmentCode.rdbuf();
		fragmentShaderCode = readBuffer.str();
		fragmentCode.close();
	}
	else return GL_FALSE;

	char const* sourcePtr = vertexShaderCode.c_str();
	glShaderSource(vertexShader, 1, &sourcePtr, NULL);
	glCompileShader(vertexShader);

	sourcePtr = fragmentShaderCode.c_str();
	glShaderSource(fragmentShader, 1, &sourcePtr, NULL);
	glCompileShader(fragmentShader);

	GLint glCompileStatus = GL_FALSE;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &glCompileStatus);
	if (glCompileStatus != GL_TRUE)
	{
		GLsizei log_length = 0;
		GLchar message[1024];
		glGetShaderInfoLog(vertexShader, 1024, &log_length, message);
		std::cout << "Failed to compile vertex shader: " << message << std::endl;
		return GL_FALSE;
	}

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &glCompileStatus);
	if (glCompileStatus != GL_TRUE)
	{
		GLsizei log_length = 0;
		GLchar message[1024];
		glGetShaderInfoLog(fragmentShader, 1024, &log_length, message);
		std::cout << "Failed to compile fragment shader: " << message << std::endl;
		return GL_FALSE;
	}

	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &glCompileStatus);
	if (glCompileStatus != GL_TRUE)
	{
		GLsizei log_length = 0;
		GLchar message[1024];
		glGetProgramInfoLog(program, 1024, &log_length, message);
		std::cout << "Program failed to link: " << message << std::endl;
		return GL_FALSE;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return program;
}