#ifndef LM_CAMERA
#define LM_CAMERA

#include "../Lamina/include/Math/vector.hpp"
#include "../Lamina/include/GL/window.hpp"
#include "../Lamina/include/Math/constants.hpp"

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
		PivotCamera() : target(lm::vec3f({ 0, 0, 0 })), position(lm::vec3f({ 0, 0, 0 })), radius(5), pitch(0), yaw(0), window(nullptr), pitchClamp(89.f), radiusClamp(lm::vec2f({5, 50})) {};
		PivotCamera(lm::vec3f initialPosition, lm::vec3f initialTarget, float initialRadius, lm::Window& _window) :
			target(initialTarget), position(initialPosition), radius(initialRadius), window(&_window), pitch(0), yaw(0), pitchClamp(89.f), radiusClamp(lm::vec2f({ 5, 50 })) {};
		PivotCamera(lm::vec3f initialPosition, lm::vec3f initialTarget, float initialRadius, float _pitchClamp, lm::vec2f _radiusClamp, lm::Window& _window) : 
			target(initialTarget), position(initialPosition), radius(initialRadius), window(&_window), pitch(0), yaw(0) 
		{
			if (_radiusClamp.x() > 0 && _radiusClamp.x() < _radiusClamp.y()) radiusClamp = _radiusClamp;
 			if (_pitchClamp > 0 && _pitchClamp <= 90) pitchClamp = _pitchClamp;
		};

		lm::mat4 GetCameraLookAtMatrix(){
			lm::vec3f up = lm::normalize(lm::CrossProduct(lm::normalize(lm::CrossProduct(position, lm::vec3f({ 0, 1, 0 }))) , position));
			return LookAtMatrix(position, target, up);
		}
		void UpdateCamera()
		{
			position.x() = std::cos(lm::constants::DegToRad(yaw)) * std::cos(lm::constants::DegToRad(pitch)) * radius;
			position.y() = std::sin(lm::constants::DegToRad(pitch)) * radius;
			position.z() = std::sin(lm::constants::DegToRad(yaw)) * std::cos(lm::constants::DegToRad(pitch)) * radius;
		}
		void GetInput()
		{
			if(window != nullptr)
			{
				if (glfwGetKey(window->window, GLFW_KEY_W) == GLFW_PRESS) {
					if (pitch >= pitchClamp) pitch = pitchClamp;
					else pitch += 1.f;
				}
				if (glfwGetKey(window->window, GLFW_KEY_S) == GLFW_PRESS) {
					if (pitch <= -pitchClamp) pitch = -pitchClamp;
					else pitch -= 1.f;
				}
				if (glfwGetKey(window->window, GLFW_KEY_A) == GLFW_PRESS) 
					yaw -= 1.f;
				if (glfwGetKey(window->window, GLFW_KEY_D) == GLFW_PRESS) 
					yaw += 1.f;

				if (glfwGetKey(window->window, GLFW_KEY_R) == GLFW_PRESS)
					if (radius <= radiusClamp.x()) radius = radiusClamp.x();
					else radius -= 0.1f;
				if (glfwGetKey(window->window, GLFW_KEY_F) == GLFW_PRESS)
					if (radius >= radiusClamp.y()) radius = radiusClamp.y();
					else radius += 0.1f;
				UpdateCamera();
			}
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
	};
}
#endif // !LM_CAMERA
