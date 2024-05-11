#pragma once
#include "../Lamina/include/Math/vector.hpp"

namespace lm
{
	class Camera
	{
	public:
		//void SetPosition(float x, float y, float z) { position.x() = x; position.y() = y; position.z() = z; }
		//void SetDirection(float x, float y, float z) 
		//{
		//	target.CreateVector({x, y, z});
		//}
		static lm::mat4 LookAtMatrix(vec3f position, vec3f target, vec3f up)
		{
			vec3f direction = lm::normalize(position - target);
			vec3f right = lm::normalize(lm::CrossProduct(direction, up));
			mat4 first({
				{right.x(),		right.y(),		right.z(),		0},
				{up.x(),		up.y(),			up.z(),			0},
				{direction.x(),	direction.y(),	direction.z(),	0},
				{0,				0,				0,			1}
				});
			mat4 second({
				{1, 0, 0, -position.x()},
				{0, 1, 0, -position.y()},
				{0, 0, 1, -position.z()},
				{0, 0, 0, 1}
				});
			return first * second;
		}
	private:
		vec3f _position;
		vec3f _target;
	};
}