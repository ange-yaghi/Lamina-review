#pragma once

#include "../Lamina/include/Math/vec2.hpp"
#include <glad/glad.h>

namespace lm
{
	class Triangle
	{
	public:
		Triangle() : rotation(0) { size = lm::vec2<double>(100, 100); position = lm::vec2<double>(0, 0); }
		Triangle(lm::vec2<double> _size, lm::vec2<double> _position) : rotation(0) { size = _size; position = _position; }

		void SetSize(lm::vec2<double> _size) { size = _size; }
		lm::vec2<double> GetSize() { return size; }

		void SetPosition(lm::vec2<double> _position) { position = _position; }
		lm::vec2<double> GetPosition() { return position; }

		void SetRotation(double _rotation) { rotation = _rotation; }
		double GetRotation() { return rotation; }

	private:
		lm::vec2<double> size;
		lm::vec2<double> position;
		double rotation;
	};
}