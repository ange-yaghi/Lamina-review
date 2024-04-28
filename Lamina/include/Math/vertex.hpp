#pragma once
#include "../Lamina/include/Math/vector.hpp"
#include "../Lamina/include/Math/matrix.hpp"
#include <iostream>
#include <vector>
#include <string>


namespace lm
{
	class VertexArray
	{
	public:
		VertexArray() { vertices.resize(0); };
		VertexArray(std::vector<vec4d> _vertices) { vertices = _vertices; }
	private:
		std::vector<vec4d> vertices;
	};
}