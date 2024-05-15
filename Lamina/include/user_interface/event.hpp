#ifndef LM_MOUSE
#define LM_MOUSE

#include "../Lamina/include/GL/opengl.hpp"
#include "../Lamina/include/GL/window.hpp"

#define LM_MOUSE_RIGHT		0
#define LM_MOUSE_LEFT		1
#define LM_MOUSE_MIDDLE		2
#define LM_MOUSE_XBUTTON1	3
#define LM_MOUSE_XBUTTON2	4

#define LM_SCROLL_UP		1
#define LM_SCROLL_NONE		0
#define LM_SCROLL_DOWN		-1

namespace lm {
	class Event
	{
	public:
		Event() : _window(nullptr), _xoffset(0.f), _yoffset(0.f), prevScrollXOffset(_xoffset), prevScrollYOffset(_yoffset) {};
		Event(lm::Window& window) : _window(&window), _xoffset(0.f), _yoffset(0.f)
		{
			glfwSetWindowUserPointer(_window->window, this);
			glfwSetScrollCallback(_window->window, ScrollCallback);
			prevScrollXOffset = getScrollX();
			prevScrollYOffset = getScrollY();
		}
		~Event() {};

		void LinkWindow(lm::Window& window)
		{
			_window = &window;
			glfwSetWindowUserPointer(_window->window, this);
			glfwSetScrollCallback(_window->window, ScrollCallback);
			prevScrollXOffset = getScrollX();
			prevScrollYOffset = getScrollY();
		}

		bool ButtonPressed(lm::Window& window, int button);
		bool ButtonReleased(lm::Window& window, int button);

		double getScrollX() { return _xoffset; }
		double getScrollY() { return _yoffset; }

		int ScrolledX() {
			if (prevScrollXOffset - getScrollX() < 0) 
			{
				prevScrollXOffset = getScrollX();
				return LM_SCROLL_DOWN;
			}
			if (prevScrollXOffset - getScrollX() > 0)
			{
				prevScrollXOffset = getScrollX();
				return LM_SCROLL_UP;
			}
			prevScrollXOffset = getScrollX();
			return LM_SCROLL_NONE;
		}

		int ScrolledY() {
			if (prevScrollYOffset - getScrollY() < 0)
			{
				prevScrollYOffset = getScrollY();
				return LM_SCROLL_DOWN;
			}
			if (prevScrollYOffset - getScrollY() > 0)
			{
				prevScrollYOffset = getScrollY();
				return LM_SCROLL_UP;
			}
			prevScrollYOffset = getScrollY();
			return LM_SCROLL_NONE;
		}

	private:
		double _xoffset;
		double _yoffset;
		lm::Window* _window;

		double prevScrollXOffset;
		double prevScrollYOffset;

		static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
		{
			Event* handler = static_cast<Event*>(glfwGetWindowUserPointer(window));
			if (handler != nullptr)
			{
				handler->_xoffset = xoffset;
				handler->_yoffset = yoffset;
			}
		}
	};
}
#endif // !LM_MOUSE