#include <iostream>
#include <../Lamina/include/colors.hpp>
#include <../Lamina/include/window.hpp>
#include <../Lamina/include/Math/vec2.hpp>
#include <../Lamina/include/Math/matrix.hpp>
#include <../Lamina/include/GL/opengl.hpp>

int main()
{
	if (!glfwInit()) return -1;
	lm::Window window(lm::vec2<int>(800, 500), "test window", LM_WINDOW_DEFAULT, 8);

	while (window.IsOpen())
	{
		glfwPollEvents();

		window.Clear(lm::Color{ 100, 102, 237, 255 });

		const GLfloat vertices[] = {
			-0.5, -0.5, 0.0,
			0.5, -0.5, 0.0,
			0.0, 0.5, 0.0
		};

		glfwMakeContextCurrent(window.window);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) std::cout << "Failed to load GLAD" << std::endl;

		GLuint vertexArray;
		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);

		GLuint vertexBuffer;
		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		GLuint program = lm::GLRenderer::CompileShader("Shaders/basicVertexShader.vert", "Shaders/basicFragShader.frag");
		glUseProgram(program);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);

		window.Display();
	}
	glfwTerminate();
	return 0;
}