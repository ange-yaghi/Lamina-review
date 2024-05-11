#pragma once
#include "../Lamina/include/Math/vector.hpp"

namespace lm
{
	class Camera
	{
	public:
		void SetPosition(float x, float y, float z) { position.x() = x; position.y() = y; position.z() = z; }
		void SetDirection(float x, float y, float z) 
		{
			target.CreateVector({x, y, z});
			direction = lm::normalize(position - target);
		}
		void SetRightDirection(float x, float y, float z)
		{
			right = lm::normalize(lm::CrossProduct(vec3f({ x, y, z }), direction));
		}
		void SetUpDirection(float x, float y, float z)
		{
			right = lm::CrossProduct(direction, right);
		}
	private:
		vec3f position;
		vec3f target;
		vec3f direction;
		vec3f right;
		vec3f up;
	};
}