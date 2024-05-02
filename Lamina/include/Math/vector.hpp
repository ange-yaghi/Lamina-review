#pragma once
#include "../Lamina/include/Math/matrix.hpp"
#include <glad/glad.h>
#include <iostream>
#include <stdint.h>
#include <vector>

namespace lm
{
	template<typename t_vector, uint8_t t_vec_size>
	class Vector
	{
	public:
		Vector() : vector{} {};
		void CreateVector(const std::vector<t_vector>& _vector)
		{
			if (_vector.size() == vector.size()) std::copy_n(_vector.begin(), t_vec_size, vector.begin());
			else std::cout << "Unable to assign vector. Incompatible size" << std::endl;
		}

		Vector operator+ (const t_vector other)
		{
			Vector<t_vector, vector.size()> result;
			for (int i = 0; i < vector.size(); i++) result.vector[i] += other;
			return result;
		}
		Vector operator- (const t_vector other)
		{
			for (int i = 0; i < vector.size(); i++) vector[i] -= other;
			return *this;
		}
		Vector operator = (const Vector &other)
		{
			if (this == &other)
			{
				return *this;
			}

			this->vector = other.vector;
			return *this;
		}

		std::array<t_vector, t_vec_size> vector;

		inline t_vector& x() { return vector[0]; }
		inline t_vector& y() { return vector[1]; }
		inline t_vector& z() { return vector[2]; }
		inline t_vector& w() { return vector[3]; }
	};

	typedef Vector<unsigned int, 2> vec2u;
	typedef Vector<unsigned int, 3> vec3u;
	typedef Vector<unsigned int, 4> vec4u;

	typedef Vector<int, 2> vec2i;
	typedef Vector<int, 3> vec3i;
	typedef Vector<int, 4> vec4i;

	typedef Vector<float, 2> vec2f;
	typedef Vector<float, 3> vec3f;
	typedef Vector<float, 4> vec4f;

	typedef Vector<double, 2> vec2d;
	typedef Vector<double, 3> vec3d;
	typedef Vector<double, 4> vec4d;

	//vert1: xyz, vert2: xyz, vert3: xyz
	typedef Vector<GLfloat, 4> GLTriangleVert;
	typedef Vector<GLfloat, 3> GLTriangleNorm;
	typedef Vector<GLfloat, 2> GLTriangleTextr;

	vec4d TranslateVector(vec4d vector, double x, double y, double z);
	vec4d ScaleVector(vec4d vector, double x, double y, double z);
	vec4d RotateVector(vec4d vector, double angle, int plane);
}