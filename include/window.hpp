#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include "../include/vec2.hpp"

namespace lm
{
	class Window
	{
	public:
		Window() : window(NULL) {};
		Window(lm::vec2u windowSize, std::string windowName) { CreateWindow(windowSize, windowName); }

		void CreateWindow(lm::vec2u windowSize, std::string windowName);

		lm::vec2u GetSize();
		void SetSize(lm::vec2u);

		lm::vec2u GetPosition();
		void SetPosition(lm::vec2u);
	private:
		GLFWwindow* window;
	};
}