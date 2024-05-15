#include "../Lamina/include/user_interface/event.hpp"

bool lm::Event::ButtonPressed(lm::Window& window, int button)
{
	switch (button)
	{
	case LM_MOUSE_RIGHT:
		if (glfwGetMouseButton(window.window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) return true;
		else return false;
		break;
	case LM_MOUSE_LEFT:
		if (glfwGetMouseButton(window.window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) return true;
		else return false;
		break;
	case LM_MOUSE_MIDDLE:
		if (glfwGetMouseButton(window.window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) return true;
		else return false;
		break;
	case LM_MOUSE_XBUTTON1:
		if (glfwGetMouseButton(window.window, GLFW_MOUSE_BUTTON_4) == GLFW_PRESS) return true;
		else return false;
		break;
	case LM_MOUSE_XBUTTON2:
		if (glfwGetMouseButton(window.window, GLFW_MOUSE_BUTTON_5) == GLFW_PRESS) return true;
		else return false;
		break;
	default:
		return false;
		break;
	}
}

bool lm::Event::ButtonReleased(lm::Window& window, int button)
{
	switch (button)
	{
	case LM_MOUSE_RIGHT:
		if (glfwGetMouseButton(window.window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) return true;
		else return false;
		break;
	case LM_MOUSE_LEFT:
		if (glfwGetMouseButton(window.window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) return true;
		else return false;
		break;
	case LM_MOUSE_MIDDLE:
		if (glfwGetMouseButton(window.window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_RELEASE) return true;
		else return false;
		break;
	case LM_MOUSE_XBUTTON1:
		if (glfwGetMouseButton(window.window, GLFW_MOUSE_BUTTON_4) == GLFW_RELEASE) return true;
		else return false;
		break;
	case LM_MOUSE_XBUTTON2:
		if (glfwGetMouseButton(window.window, GLFW_MOUSE_BUTTON_5) == GLFW_RELEASE) return true;
		else return false;
		break;
	default:
		return false;
		break;
	}
}