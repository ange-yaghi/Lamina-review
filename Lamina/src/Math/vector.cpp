#include "../Lamina/include/Math/vector.hpp"

lm::vec4d lm::TranslateVector(vec4d &vector, double x, double y, double z)
{
	Matrix workingMatrix(4, 1);
	workingMatrix.CreateMatrix({ {vector.vector[0]}, {vector.vector[1]}, {vector.vector[2]}, {vector.vector[3]} });
	TranslationMatrix translationMatrix(x, y, z);
	
	Matrix result = translationMatrix * workingMatrix;
	vec4d resultVec({ result.matrix[0][0], result.matrix[1][0], result.matrix[2][0], result.matrix[3][0] });
	return resultVec;
}

lm::vec4d lm::ScaleVector(vec4d &vector, double x, double y, double z)
{
	Matrix workingMatrix(4, 1);
	workingMatrix.CreateMatrix({ {vector.vector[0]}, {vector.vector[1]}, {vector.vector[2]}, {vector.vector[3]} });
	ScaleMatrix scaleMatrix(x, y, z);

	Matrix result = scaleMatrix * workingMatrix;
	vec4d resultVec({ result.matrix[0][0], result.matrix[1][0], result.matrix[2][0], result.matrix[3][0] });
	return resultVec;
}

lm::vec4d lm::RotateVector(vec4d &vector, double angle, int plane)
{
	Matrix workingMatrix(4, 1);
	workingMatrix.CreateMatrix({ {vector.vector[0]}, {vector.vector[1]}, {vector.vector[2]}, {vector.vector[3]} });
	RotationMatrix rotationMatrix(angle, plane);

	Matrix result = rotationMatrix * workingMatrix;
	vec4d resultVec({ result.matrix[0][0], result.matrix[1][0], result.matrix[2][0], result.matrix[3][0] });
	return resultVec;
}