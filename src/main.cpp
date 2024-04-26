#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <../Lamina/include/colors.hpp>
#include <../Lamina/include/window.hpp>
#include <../Lamina/include/Math/vec2.hpp>

int main()
{
	if (!glfwInit()) return -1;
	lm::Window window(lm::vec2<int>(800, 500), "test window", LM_WINDOW_DEFAULT);

	while (window.IsOpen())
	{
		glfwPollEvents();

		window.Clear(lm::Color{ 12, 111, 243, 255 });

		window.Display();
	}
	glfwTerminate();
	return 0;
}