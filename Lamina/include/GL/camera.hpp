#pragma once
#include "../Lamina/include/Math/vector.hpp"
#include "../Lamina/include/GL/window.hpp"

namespace lm
{
	class Camera
	{
	public:
		Camera() : cameraPosition({ 0.f, 0.f, 3.f }), cameraFront({ 0.f, 0.f, -1.f }), cameraUp({ 0.f, 1.f, 0.f }), cameraSpeed(0.05f) {};

		static lm::mat4 LookAtMatrix(vec3f position, vec3f target, vec3f up)
		{
			lm::vec3f direction = lm::normalize(position - target);
			lm::vec3f right = lm::normalize(lm::CrossProduct(direction, up));
			lm::mat4 first({
				{right.x(),		right.y(),		right.z(),		0},
				{up.x(),		up.y(),			up.z(),			0},
				{direction.x(),	direction.y(),	direction.z(),	0},
				{0,				0,				0,			1}
				});
			lm::mat4 second({
				{1, 0, 0, -position.x()},
				{0, 1, 0, -position.y()},
				{0, 0, 1, -position.z()},
				{0, 0, 0, 1}
				});
			return first * second;
		}

		void GetInput(lm::Window& window)
		{
			if (glfwGetKey(window.window, GLFW_KEY_W) == GLFW_PRESS)
			{
				lm::vec3f multiplicationResult = cameraFront * cameraSpeed;
				cameraPosition += multiplicationResult;
			}
			if (glfwGetKey(window.window, GLFW_KEY_S) == GLFW_PRESS)
			{
				lm::vec3f multiplicationResult = cameraFront * cameraSpeed;
				cameraPosition -= multiplicationResult;
			}
			if (glfwGetKey(window.window, GLFW_KEY_D) == GLFW_PRESS)
			{
				lm::vec3f multiplicationResult = lm::normalize(lm::CrossProduct(cameraUp, cameraFront)) * cameraSpeed;
				cameraPosition += multiplicationResult;
			}
			if (glfwGetKey(window.window, GLFW_KEY_A) == GLFW_PRESS)
			{
				lm::vec3f multiplicationResult = lm::normalize(lm::CrossProduct(cameraUp, cameraFront)) * cameraSpeed;
				cameraPosition -= multiplicationResult;
			}
		}

		lm::mat4 GetViewMatrix()
		{
			return lm::Camera::LookAtMatrix(cameraPosition, cameraPosition + cameraFront, cameraUp);
		}
	private:
		lm::vec3f cameraPosition;	// position of the camera in 3d space
		lm::vec3f cameraFront;		// direction of the camera
		lm::vec3f cameraUp;			// direction of the up vector relative to the camera's coordinate system 

		float cameraSpeed;			// speed of the cameras translation
	};
}