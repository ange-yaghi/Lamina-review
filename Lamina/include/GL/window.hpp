#ifndef LM_WINDOW
#define LM_WINDOW

#include "../Lamina/include/GL/colors.hpp"
#include "../Lamina/include/Math/vertex.hpp"
#include <glad/glad.h>
#include <GLFW/include/GLFW/glfw3.h>
#include <iostream>
#include <string>

//define lamina window types
#define LM_WINDOW_RESIZABLE			0b00000001
#define LM_WINDOW_VISIBLE			0b00000010
#define LM_WINDOW_DECORATED			0b00000100
#define LM_WINDOW_FOCUSED			0b00001000
#define LM_WINDOW_MAXIMIZED			0b00010000
#define LM_WINDOW_DOUBLE_BUFFER		0b00100000
#define LM_WINDOW_FULLSCREEN		0b01000000
#define LM_WINDOW_SCALE_TO_MONITOR	0b10000000
#define LM_WINDOW_DEFAULT			0b00101111
#define LM_WINDOW_NON_RESIZABLE		0b00101110


namespace lm
{
	struct WindowSettings
	{
		int aliasingLevel = 0;
	};

	//main window class
	class Window
	{
	public:
		GLFWwindow* window;

		Window() : window(NULL) {};
		Window(lm::vec2i windowSize, std::string windowName, int windowHint, int multisamplingLevel = 0) { Create(windowSize, windowName, windowHint, multisamplingLevel); MakeContextCurrent(); }

		bool Create(lm::vec2i windowSize, std::string windowName, int windowHints, int multisamplingLevel = 0);

		lm::vec2i GetSize()
		{
			vec2i size;
			glfwGetWindowSize(window, &size.x(), &size.y());
			return size;
		}
		void SetSize(lm::vec2i size) { glfwSetWindowSize(window, size.x(), size.y()); }

		lm::vec2i GetPosition()
		{
			vec2i position;
			glfwGetWindowPos(window, &position.x(), &position.y());
			return position;
		}
		void SetPosition(lm::vec2i position) { glfwSetWindowPos(window, position.x(), position.y()); }

		bool IsOpen() { return !glfwWindowShouldClose(window); }
		void Close() { glfwSetWindowShouldClose(window, true); }

		void Clear(lm::Color color);
		void MakeContextCurrent()
		{
			glfwMakeContextCurrent(window);
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) std::cout << "Failed to load GLAD" << std::endl;
		}

		void Display() { glfwSwapBuffers(window); }
	};
}
#endif // !LM_WINDOW