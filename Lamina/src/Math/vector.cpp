#include "../Lamina/include/Math/vector.hpp"

lm::vec4d lm::TranslateVector(vec4d &vector, double x, double y, double z)
{
	TranslationMatrix translationMatrix(x, y, z);
	vec4d result = vector * translationMatrix;
	return result;
}

lm::vec4d lm::ScaleVector(vec4d &vector, double x, double y, double z)
{
	ScaleMatrix scaleMatrix(x, y, z);
	vec4d result = vector * scaleMatrix;
	return result;
}

lm::vec4d lm::RotateVector(vec4d &vector, double angle, int plane)
{
	RotationMatrix rotationMatrix(angle, plane);
	vec4d result = vector * rotationMatrix;
	return result;
}