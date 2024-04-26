#pragma once

namespace lm
{
	template<typename Type>
	class vec2
	{
	public:
		Type x;
		Type y;

		vec2() : x(0), y(0) {};
		vec2(Type xArg, Type yArg) : x(xArg), y(yArg) {};

		vec2 operator+(vec2 other) { return vec2(x + other.x, y + other.y); }
		vec2 operator-(vec2 other) { return vec2(x - other.x, y - other.y); }
		vec2 operator*(vec2 other) { return vec2(x * other.x, y * other.y); }
		vec2 operator/(vec2 other) { return vec2(x / other.x, y / other.y); }

		vec2 operator+(Type scalar) { return vec2(x + scalar, y + scalar); }
		vec2 operator-(Type scalar) { return vec2(x - scalar, y - scalar); }
		vec2 operator*(Type scalar) { return vec2(x * scalar, y * scalar); }
		vec2 operator/(Type scalar) { return vec2(x / scalar, y / scalar); }

		Type GetDotProduct(vec2 other) { return (x * other.x) + (y * other.y); }
		Type GetFlatCrossProduct(vec2 other) {return (x * other.y) - (y * other.x); }
	};

	struct vertex
	{
		double x, y, z;
	};
}