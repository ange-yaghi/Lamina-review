#include <iostream>
#include <../Lamina/include/colors.hpp>
#include <../Lamina/include/window.hpp>
#include <../Lamina/include/Math/vec2.hpp>
#include <../Lamina/include/Math/matrix.hpp>
#include <../Lamina/include/GL/opengl.hpp>
#include <chrono>

int main()
{
	if (!glfwInit()) return -1;
	lm::Window window(lm::vec2<int>(800, 600), "test window", LM_WINDOW_DEFAULT, 8);
	auto epoch = std::chrono::steady_clock::now();

	while (window.IsOpen())
	{
		glfwPollEvents();

		float time = std::chrono::duration_cast<std::chrono::duration<float>>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - epoch)).count();


		window.Clear(lm::Color{ 100, 102, 237, 255 });

		const GLfloat vertices[] = {
			0.5, -0.5, 0.0,
			-0.5, -0.5, 0.0,
			-0.5, 0.5, 0.0,
			0.5, 0.5, 0.0
		};

		const GLuint indices[] =
		{
			0, 1, 2,
			2, 3, 0
		};

		const GLfloat colors[] = {
			1, 0, 0.2, 1,
			0, 1, 0.2, 1,
			0, 1, 0.2, 1,
			1, 0, 0.2, 1
		};

		glfwMakeContextCurrent(window.window);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) std::cout << "Failed to load GLAD" << std::endl;

		GLuint EBO;
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		GLuint vertexArray;
		glGenVertexArrays(1, &vertexArray);

		GLuint program = lm::GLRenderer::CompileShader("Shaders/basicVertexShader.vert", "Shaders/basicFragShader.frag");
		glUseProgram(program);
		GLint uniformTime = glGetUniformLocation(program, "currentTime");
		glUniform1f(uniformTime, time);

		glBindVertexArray(vertexArray);
		
		GLuint vertexBuffer;
		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(0);

		GLuint colorBuffer;
		glGenBuffers(1, &colorBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(1);
		//glEnableVertexAttribArray(1);
		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		//glDisableVertexAttribArray(1);

		window.Display();
	}
	glfwTerminate();
	return 0;
}