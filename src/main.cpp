#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../include/colors.hpp"

int main()
{
	GLFWwindow* window;
	if (!glfwInit()) return -1;
	window = glfwCreateWindow(500, 500, "name", NULL, NULL);
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) return -1;

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(LM_COLOR_MDNTBLUE);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}