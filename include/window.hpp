#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include "../include/vec2.hpp"
#include "../include/colors.hpp"
#include "../include/Primitives/triangle.hpp"
#include "../include/Primitives/rectangle.hpp"

//define lamina window types
#define LM_RESIZABLE_WINDOW			0x0
#define LM_NON_RESIZABLE_WINDOW		0x1
#define LM_FULL_SCREEN_WINDOW		0x2
#define LM_BORDERLESS_WINDOW		0x3

namespace lm
{
	//main window class
	class Window
	{
	public:
		GLFWwindow* window;

		Window() : window(NULL) {};
		Window(lm::vec2<int> windowSize, std::string windowName, int windowHint) { CreateWindow(windowSize, windowName, windowHint); }

		bool CreateWindow(lm::vec2<int> windowSize, std::string windowName, int windowHints);

		lm::vec2<int> GetSize()
		{
			vec2<int> size;
			glfwGetWindowSize(window, &size.x, &size.y);
			return size;
		}
		void SetSize(lm::vec2<int> size) { glfwSetWindowSize(window, size.x, size.y); }

		lm::vec2<int> GetPosition()
		{
			vec2<int> position;
			glfwGetWindowPos(window, &position.x, &position.y);
			return position;
		}
		void SetPosition(lm::vec2<int> position) { glfwSetWindowPos(window, position.x, position.y); }

		bool IsOpen() { return !glfwWindowShouldClose(window); }
		void Close() { glfwSetWindowShouldClose(window, true); }

		void Clear(lm::Color color);

		template<typename T>
		void Draw(T target);

		void Display() { glfwSwapBuffers(window); }
	};
}