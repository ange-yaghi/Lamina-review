#include <iostream>
#include <../Lamina/include/Math/matrix.hpp>

int main()
{
	std::vector<std::vector<double>> mat1 = {
		{4, 12, 2, 2},
		{2, 1, 0, 2},
		{7, 1, 1, 1},
		{0, 2, 5, 4}
	};
	std::vector<std::vector<double>> mat2 = {
		{1},
		{2},
		{3},
		{1}
	};

	lm::Matrix matrix((uint8_t)mat1.size(), (uint8_t)mat1[0].size());
	matrix.CreateMatrix(mat1);
	
	lm::Matrix other((uint8_t)mat2.size(), (uint8_t)mat2[0].size());
	other.CreateMatrix(mat2);

	lm::Matrix result = matrix * other;

	for (int i = 0; i < result.rows; i++)
	{
		for (int j = 0; j < result.columns; j++)
		{
			std::cout << result.matrix[i][j] << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << "\nTranslation matrix:\n\n";

	lm::TranslationMatrix matt(1, 1, 1);
	lm::Matrix resultt = matt * other;
	for (int i = 0; i < resultt.rows; i++)
	{
		for (int j = 0; j < resultt.columns; j++)
		{
			std::cout << resultt.matrix[i][j] << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << "\nScale matris:\n\n";

	lm::ScaleMatrix mats(2, 4, 8);
	lm::Matrix results = mats * other;
	for (int i = 0; i < results.rows; i++)
	{
		for (int j = 0; j < results.columns; j++)
		{
			std::cout << results.matrix[i][j] << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << "\nRotation matrix:\n\n";

	lm::RotationMatrix matr(20, LM_ROTATE_Z_PLANE);
	lm::Matrix resultr = matr * other;
	for (int i = 0; i < resultr.rows; i++)
	{
		for (int j = 0; j < resultr.columns; j++)
		{
			std::cout << resultr.matrix[i][j] << "\t";
		}
		std::cout << std::endl;
	}

	return 0;
}