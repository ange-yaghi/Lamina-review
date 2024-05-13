#pragma once
#include "../Lamina/include/Math/vector.hpp"
#include "../Lamina/include/GL/window.hpp"

namespace lm
{
	class PivotCamera
	{
	public:
	private:
		lm::vec3f target;
		lm::vec3f position;
	};

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
}