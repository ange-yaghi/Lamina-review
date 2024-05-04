#include <iostream>
#include <../Lamina/include/Math/matrix.hpp>
#include <../Lamina/include/Math/vector.hpp>
#include <windows.h>
#include <chrono>

void Test1()
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

	lm::vec4d vector;
	vector.CreateVector({ 1, 2, 3, 1 });

	lm::Matrix matrix((uint8_t)mat1.size(), (uint8_t)mat1[0].size());
	matrix.CreateMatrix(mat1);

	lm::Matrix other((uint8_t)mat2.size(), (uint8_t)mat2[0].size());
	other.CreateMatrix(mat2);

	//lm::Matrix result = matrix * other;

	//for (int i = 0; i < result.rows; i++)
	//{
	//	for (int j = 0; j < result.columns; j++)
	//	{
	//		std::cout << result.matrix[i][j] << "\t";
	//	}
	//	std::cout << std::endl;
	//}

	bool test = true;
	srand(time(NULL));
	const auto start = std::chrono::steady_clock::now();
	for (int t = 0; t < 100000; t++)
	{
		//std::cout << "\nTranslation matrix:\tVector\n\n";
		int rand1 = rand() % 10;
		int rand2 = rand() % 10;
		int rand3 = rand() % 10;
		lm::TranslationMatrix matt(t * rand1, t * rand2, t * rand3);
		lm::Matrix resultt = matt * other;

		lm::vec4d resVT = lm::TranslateVector(vector, t * rand1, t * rand2, t * rand3);

		for (int i = 0; i < resultt.rows; i++)
		{
			for (int j = 0; j < resultt.columns; j++)
			{
				//std::cout << resultt.matrix[i][j] << "\t\t\t" << resVT.vector[i];
				if (resultt.matrix[i][j] != resVT.vector[i]) test = false;
			}
			//std::cout << std::endl;
		}
		//std::cout << "\nScale matris:\t\tVector\n\n";

		lm::ScaleMatrix mats(t * rand1, t * rand2, t * rand3);
		lm::Matrix results = mats * other;

		lm::vec4d resVS = lm::ScaleVector(vector, t * rand1, t * rand2, t * rand3);
		for (int i = 0; i < results.rows; i++)
		{
			for (int j = 0; j < results.columns; j++)
			{
				//std::cout << results.matrix[i][j] << "\t\t\t" << resVS.vector[i];
				if (results.matrix[i][j] != resVS.vector[i]) test = false;
			}
			//std::cout << std::endl;
		}
		//std::cout << "\nRotation matrix:\tVector\n\n";

		lm::RotationMatrix matr(t * rand1, LM_ROTATE_Z_PLANE);
		lm::Matrix resultr = matr * other;

		lm::vec4d resVR = lm::RotateVector(vector, t * rand1, LM_ROTATE_Z_PLANE);
		for (int i = 0; i < resultr.rows; i++)
		{
			for (int j = 0; j < resultr.columns; j++)
			{
				//double round = resultr.matrix[i][j] * 10000;
				//double roundVec = resVR.vector[i] * 10000;
				//std::cout << std::round(round) / 10000 << "\t\t\t" << std::round(roundVec) / 10000;
				if (resultr.matrix[i][j] != resVR.vector[i]) test = false;
			}
			//std::cout << std::endl;
		}
	}
	const auto end = std::chrono::steady_clock::now();
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (test)
	{
		SetConsoleTextAttribute(hConsole, 10);
		std::cout << "\n[PASSED]";
		SetConsoleTextAttribute(hConsole, 7);
		std::cout << " Execution time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << std::endl;
	}
	else
	{
		SetConsoleTextAttribute(hConsole, 12);
		std::cout << "\n[FAILED]";
		SetConsoleTextAttribute(hConsole, 7);
		std::cout << " Execution time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << std::endl;
	}
}

void Test2()
{
	int numberOfTries = 5000;
	int numberOfTests = 10;

	std::chrono::milliseconds totalExecutionTimeTranslation(0);
	std::chrono::milliseconds totalExecutionTimeScaling(0);
	std::chrono::milliseconds totalExecutionTimeRotation(0);

	for(int i = 0; i < numberOfTests; i++)
	{
		lm::vec4d vectorT; vectorT.CreateVector({ 1, 2, 3, 1 });
		const auto startTranslateTest = std::chrono::steady_clock::now();
		for (int i = 0; i < numberOfTries; i++)
		{
			vectorT = lm::TranslateVector(vectorT, 1, 2, 3);
		}
		const auto endTranslateTest = std::chrono::steady_clock::now();
		totalExecutionTimeTranslation += std::chrono::duration_cast<std::chrono::milliseconds>(endTranslateTest - startTranslateTest);
		std::cout << "Execution time for vector translation: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTranslateTest - startTranslateTest) << std::endl;


		lm::vec4d vectorS; vectorS.CreateVector({ 1, 2, 3, 1 });
		const auto startScaleTest = std::chrono::steady_clock::now();
		for (int i = 0; i < numberOfTries; i++)
		{
			vectorS = lm::ScaleVector(vectorS, 1, 2, 3);
		}
		const auto endScaleTest = std::chrono::steady_clock::now();
		totalExecutionTimeScaling += std::chrono::duration_cast<std::chrono::milliseconds>(endScaleTest - startScaleTest);
		std::cout << "Execution time for vector scaling: " << std::chrono::duration_cast<std::chrono::milliseconds>(endScaleTest - startScaleTest) << std::endl;


		lm::vec4d vectorR; vectorR.CreateVector({ 1, 2, 3, 1 });
		const auto startRotateTest = std::chrono::steady_clock::now();
		for (int i = 0; i < numberOfTries; i++)
		{
			vectorR = lm::RotateVector(vectorR, 1, LM_ROTATE_X_PLANE);
		}
		const auto endRotateTest = std::chrono::steady_clock::now();
		totalExecutionTimeRotation += std::chrono::duration_cast<std::chrono::milliseconds>(endRotateTest - startRotateTest);
		std::cout << "Execution time for vector rotation: " << std::chrono::duration_cast<std::chrono::milliseconds>(endRotateTest - startRotateTest) 
			<< "\n\nTest number: " << i + 1 << "/" << numberOfTests << "\n" << std::endl;
	}

	float AvTranslate = std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(totalExecutionTimeTranslation).count() / numberOfTests;
	float AvScale = std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(totalExecutionTimeScaling).count() / numberOfTests;
	float AvRotate = std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(totalExecutionTimeRotation).count() / numberOfTests;

	std::cout << 
		"Average execution time translation: "	<< AvTranslate	<<	"\tOperations per second: "	<< (numberOfTries / AvTranslate) * 1000	<<
		"\nAverage execution time scaling: "	<< AvScale		<<	"\t\tOperations per second: "	<< (numberOfTries / AvScale) * 1000		<<
		"\nAverage execution time rotation: "	<< AvRotate		<<	"\t\tOperations per second: "	<< (numberOfTries / AvRotate) * 1000	<<
		std::endl;
}

int main()
{
	//Test2();
	Test1();

	return 0;
}