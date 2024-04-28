#include "../Lamina/include/Math/vector.hpp"

lm::vec4d lm::TranslateVector(vec4d vector, double x, double y, double z)
{
	Matrix workingMatrix(4, 1);
	std::vector<std::vector<double>> values;
	values[0] = vector.vector;
	workingMatrix.CreateMatrix(values);
	TranslationMatrix translationMatrix(x, y, z);
	
	Matrix result = translationMatrix * workingMatrix;
	vec4d resultVec;
	resultVec.CreateVector(result.matrix[0]);
	return resultVec;
}

lm::vec4d lm::ScaleVector(vec4d vector, double x, double y, double z)
{
	Matrix workingMatrix(4, 1);
	std::vector<std::vector<double>> values;
	values[0] = vector.vector;
	workingMatrix.CreateMatrix(values);
	ScaleMatrix scaleMatrix(x, y, z);

	Matrix result = scaleMatrix * workingMatrix;
	vec4d resultVec;
	resultVec.CreateVector(result.matrix[0]);
	return resultVec;
}

lm::vec4d lm::RotateVector(vec4d vector, double angle, int plane)
{
	Matrix workingMatrix(4, 1);
	std::vector<std::vector<double>> values;
	values[0] = vector.vector;
	workingMatrix.CreateMatrix(values);
	RotationMatrix rotationMatrix(angle, plane);

	Matrix result = rotationMatrix * workingMatrix;
	vec4d resultVec;
	resultVec.CreateVector(result.matrix[0]);
	return resultVec;
}