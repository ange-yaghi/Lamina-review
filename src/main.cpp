#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../include/colors.hpp"
#include "../include/window.hpp"
#include "../include/vec2.hpp"

int main()
{
	if (!glfwInit()) return -1;
	lm::Window window(lm::vec2<int>(500, 500), "test window", NULL);
	//window.CreateWindow(lm::vec2<int>(500, 500), "test window", NULL);
	glfwMakeContextCurrent(window.window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) return -1;

	while (window.IsOpen())
	{
		glfwPollEvents();

		glClearColor(LM_COLOR_MDNTBLUE);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window.window);
	}
	glfwTerminate();
	return 0;
}