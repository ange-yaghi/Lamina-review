#pragma once
#include <iostream>
#include <vector>
#include <stdint.h>
#include "../Lamina/include/Math/matrix.hpp"

namespace lm
{
	template<typename t_vector, uint8_t t_vec_size>
	class Vector
	{
	public:
		Vector() : size(t_vec_size) { vector = std::vector<double>(size, 0); };
		void CreateVector(std::vector<t_vector> _vector)
		{
			if (_vector.size() == size) vector = _vector;
			else std::cout << "Unable to assign vector. Incompatible size" << std::endl;
		}

		Vector operator+ (const t_vector other)
		{
			Vector<t_vector, size> result;
			for (int i = 0; i < size; i++) result.vector[i] += other;
			return result;
		}
		Vector operator- (const t_vector other)
		{
			for (int i = 0; i < size; i++) vector[i] -= other;
			return *this;
		}
		Vector operator = (const Vector &other)
		{
			if (this == &other)
			{
				return *this;
			}

			this->size = other.size;
			this->vector = other.vector;
			return *this;
		}

		uint8_t size;
		std::vector<t_vector> vector;
	};

	typedef Vector<float, 2> vec2f;
	typedef Vector<float, 3> vec3f;
	typedef Vector<float, 4> vec4f;

	typedef Vector<double, 2> vec2d;
	typedef Vector<double, 3> vec3d;
	typedef Vector<double, 4> vec4d;

	vec4d TranslateVector(vec4d vector, double x, double y, double z);
	vec4d ScaleVector(vec4d vector, double x, double y, double z);
	vec4d RotateVector(vec4d vector, double angle, int plane);
}