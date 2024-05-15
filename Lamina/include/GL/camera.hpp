#ifndef LM_CAMERA
#define LM_CAMERA

#include "../Lamina/include/Math/vector.hpp"
#include "../Lamina/include/GL/window.hpp"
#include "../Lamina/include/Math/constants.hpp"
#include "../Lamina/include/user_interface/event.hpp"

namespace lm
{
	static lm::mat4 LookAtMatrix(vec3f position, vec3f target, vec3f up)
	{
		lm::vec3f direction = lm::normalize(position - target);
		lm::vec3f right = lm::normalize(lm::CrossProduct(direction, up));
		lm::mat4 first({
			{right.x(),		right.y(),		right.z(),		0},
			{up.x(),		up.y(),			up.z(),			0},
			{direction.x(),	direction.y(),	direction.z(),	0},
			{0,				0,				0,				1}
			});
		lm::mat4 second({
			{1, 0, 0, -position.x()},
			{0, 1, 0, -position.y()},
			{0, 0, 1, -position.z()},
			{0, 0, 0, 1}
			});
		return first * second;
	}

	class PivotCamera
	{
	public:
		PivotCamera() : target(lm::vec3f({ 0, 0, 0 })), position(lm::vec3f({ 0, 0, 0 })), radius(5), pitch(0), yaw(0), window(nullptr), pitchClamp(89.f), radiusClamp(lm::vec2f({5, 50})), firstMouseMovement(true) {};
		PivotCamera(lm::vec3f initialPosition, lm::vec3f initialTarget, float initialRadius, lm::Window& _window) :
			target(initialTarget), position(initialPosition), radius(initialRadius), window(&_window), pitch(0), yaw(0), pitchClamp(89.f), radiusClamp(lm::vec2f({ 5.f, 50.f })),
		firstMouseMovement(true)
		{
			glfwSetWindowUserPointer(this->window->window, this);
			glfwSetScrollCallback(this->window->window, lm::PivotCamera::ScrollCallback);
			glfwSetCursorPosCallback(this->window->window, lm::PivotCamera::CursorPosCallback);
			UpdateCamera();
		};
		PivotCamera(lm::vec3f initialPosition, lm::vec3f initialTarget, float initialRadius, float _pitchClamp, lm::vec2f _radiusClamp, lm::Window& _window) : 
			target(initialTarget), position(initialPosition), radius(initialRadius), window(&_window), pitch(0), yaw(0), firstMouseMovement(true) 
		{
			glfwSetWindowUserPointer(this->window->window, this);
			glfwSetScrollCallback(this->window->window, lm::PivotCamera::ScrollCallback);
			glfwSetCursorPosCallback(this->window->window, lm::PivotCamera::CursorPosCallback);
			if (_radiusClamp.x() > 0.f && _radiusClamp.x() < _radiusClamp.y()) radiusClamp = _radiusClamp;
			else radiusClamp = lm::vec2f({ 5.f, 50.f });
			if (_pitchClamp > 0.f && _pitchClamp <= 90.f) pitchClamp = _pitchClamp;
			else pitchClamp = 89.f;
			UpdateCamera();
		};

		lm::mat4 GetCameraLookAtMatrix(){
			lm::vec3f up = lm::normalize(lm::CrossProduct(lm::normalize(lm::CrossProduct(position, lm::vec3f({ 0, 1, 0 }))) , position));
			return LookAtMatrix(position, target, up);
		}
		void UpdateCamera()
		{
			this->position.x() = std::cos(lm::constants::DegToRad(yaw)) * std::cos(lm::constants::DegToRad(pitch)) * radius;
			this->position.y() = std::sin(lm::constants::DegToRad(pitch)) * radius;
			this->position.z() = std::sin(lm::constants::DegToRad(yaw)) * std::cos(lm::constants::DegToRad(pitch)) * radius;
		}
		void GetScrollInput(int scroll)
		{
			if (scroll > 0 && this->radius >= this->radiusClamp.x()) this->radius -= 1.f;
			if (scroll < 0 && this->radius <= this->radiusClamp.y()) this->radius += 1.f;
			UpdateCamera();
		}
		void GetMousePosInput(lm::vec2d cursorPos)
		{
			std::cout << cursorPos.x() << " " << cursorPos.y() << "\n";
			if (firstMouseMovement) 
			{
				lastMousePosition = cursorPos;
				firstMouseMovement = false;
				return;
			}
			if (lastMousePosition.x() - cursorPos.x() > 0) 
				yaw += (lastMousePosition.x() - cursorPos.x());
			if (lastMousePosition.x() - cursorPos.x() < 0) 
				yaw += (lastMousePosition.x() - cursorPos.x());
			if (lastMousePosition.y() - cursorPos.y() > 0) 
				pitch += -(lastMousePosition.y() - cursorPos.y());
			if (lastMousePosition.y() - cursorPos.y() < 0) 
				pitch += -(lastMousePosition.y() - cursorPos.y());
			lastMousePosition = cursorPos;
			if (pitch >= pitchClamp) pitch = pitchClamp;
			if (pitch <= -pitchClamp) pitch = -pitchClamp;
			UpdateCamera();
		}

		void SetRadiusClamp(lm::vec2f _radiusClamp) { if (_radiusClamp.x() > 0 && _radiusClamp.x() < _radiusClamp.y()) radiusClamp = _radiusClamp; }
		void SetPitchClamp(float _pitchClamp) { if(_pitchClamp > 0 && _pitchClamp <= 90) pitchClamp = _pitchClamp; }
	private:
		lm::vec3f target;
		lm::vec3f position;
		float radius;
		float yaw;
		float pitch;

		lm::vec2f radiusClamp;
		float pitchClamp;

		lm::Window* window;

		//working variables
		lm::vec2d lastMousePosition;
		bool firstMouseMovement;

		static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
		{
			lm::PivotCamera* thisCamera = static_cast<lm::PivotCamera*>(glfwGetWindowUserPointer(window));
			if (thisCamera != nullptr)
			{
				thisCamera->GetScrollInput(yoffset);
			}
			/*if(yoffset > 0) */
		}

		static void CursorPosCallback(GLFWwindow* window, double xpos, double ypos)
		{
			lm::PivotCamera* thisCamera = static_cast<lm::PivotCamera*>(glfwGetWindowUserPointer(window));
			if (thisCamera != nullptr && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
			{
				thisCamera->GetMousePosInput(lm::vec2d({ xpos, ypos }));
			}
		}
	};
}
#endif // !LM_CAMERA
