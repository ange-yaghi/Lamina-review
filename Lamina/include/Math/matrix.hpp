#pragma once
//#include "../Lamina/include/Math/vector.hpp"
#include <iostream>
#include <array>
#include <vector>
#include <stdint.h>


#define LM_ROTATE_X_PLANE 0b001
#define LM_ROTATE_Y_PLANE 0b010
#define LM_ROTATE_Z_PLANE 0b100

namespace lm
{
	class Matrix
	{
	public:
		Matrix() : rows(NULL), columns(NULL) {};
		Matrix(uint8_t _rows, uint8_t _columns) : rows(_rows), columns(_columns)
		{
			matrix = std::vector<std::vector<float>>(rows, std::vector<float>(columns, 0));
		}
		~Matrix() {};
		
		void CreateMatrix(const std::vector<std::vector<float>> &_matrix) 
		{
			bool matrixCompatible = true;
			if (_matrix.size() != rows) matrixCompatible = false;
			for (int i = 0; i < _matrix.size(); i++)
			{
				if (_matrix[i].size() != columns) matrixCompatible = false;
			}
			if (matrixCompatible) matrix = _matrix;
			else std::cout << "Unable to assign matix. Incompatible size" << std::endl;
		}
		void ChangeMatrixValue(uint8_t row, uint8_t column, float value) { matrix[row][column] = value; }

		Matrix operator+ (float &scalar)
		{
			Matrix result(rows, columns);
			result.CreateMatrix(matrix);
			for (int i = 0; i < matrix.size(); i++)
			{
				for (int j = 0; j < matrix[i].size(); j++)
				{
					result.matrix[i][j] += scalar;
				}
			}
			return result;
		}

		Matrix operator+ (Matrix &other)
		{
			Matrix result(rows, columns);
			result.CreateMatrix(matrix);
			for (int i = 0; i < matrix.size(); i++)
			{
				for (int j = 0; j < matrix[i].size(); j++)
				{
					result.matrix[i][j] += other.matrix[i][j];
				}
			}
			return result;
		}

		Matrix operator- (float &scalar)
		{
			Matrix result(rows, columns);
			result.CreateMatrix(matrix);
			for (int i = 0; i < matrix.size(); i++)
			{
				for (int j = 0; j < matrix[i].size(); j++)
				{
					result.matrix[i][j] -= scalar;
				}
			}
			return result;
		}

		Matrix operator- (Matrix &other)
		{
			Matrix result(rows, columns);
			result.CreateMatrix(matrix);
			for (int i = 0; i < matrix.size(); i++)
			{
				for (int j = 0; j < matrix[i].size(); j++)
				{
					result.matrix[i][j] -= other.matrix[i][j];
				}
			}
			return result;
		}

		Matrix operator* (Matrix &other)
		{
			if (columns == other.rows)
			{
				std::vector<std::vector<float>> result(rows, std::vector<float>(other.columns, 0));

				for (int i = 0; i < rows; i++)
				{
					for (int j = 0; j < other.columns; j++)
					{
						for (int k = 0; k < rows; k++)
						{
							result[i][j] += matrix[i][k] * other.matrix[k][j];
						}
					}
				}

				Matrix out(rows, other.columns);
				out.CreateMatrix(result);
				return out;
			}
			else 
			{
				std::cout << "Matrices can not be multiplied. Incompatible size." << std::endl;
				return Matrix();
			}
		}

		Matrix operator= (Matrix& other)
		{
			if (this == &other) return *this;

			this->rows = other.rows;
			this->columns = other.columns;
			this->matrix = other.matrix;
			return *this;
		}

		uint8_t rows;
		uint8_t columns;

//		rows ↓		columns ↓
		std::vector<std::vector<float>> matrix;
	};

	class TranslationMatrix
	{
	public:
		TranslationMatrix() : rows(4), columns(4) 
		{ 
			matrix = { {
				{1, 0, 0, 0},
				{0, 1, 0, 0},
				{0, 0, 1, 0},
				{0, 0, 0, 1}
			} };
		}

		TranslationMatrix(float x, float y, float z) : rows(4), columns(4)
		{
			matrix = { {
				{1, 0, 0, x},
				{0, 1, 0, y},
				{0, 0, 1, z},
				{0, 0, 0, 1}
			} };
		}

		~TranslationMatrix() {};

		void ChangeTranlationValues(float x, float y, float z)
		{
			matrix = { {
				{1, 0, 0, x},
				{0, 1, 0, y},
				{0, 0, 1, z},
				{0, 0, 0, 1}
			} };
		}

		Matrix operator* (Matrix other)
		{
			if (columns == other.rows)
			{
				std::vector<std::vector<float>> result(rows, std::vector<float>(other.columns, 0));

				for (int i = 0; i < rows; i++)
				{
					for (int j = 0; j < other.columns; j++)
					{
						for (int k = 0; k < rows; k++)
						{
							result[i][j] += matrix[i][k] * other.matrix[k][j];
						}
					}
				}

				Matrix out(rows, other.columns);
				out.CreateMatrix(result);
				return out;
			}
			else
			{
				std::cout << "Matrices can not be multiplied. Incompatible size." << std::endl;
				return Matrix();
			}
		}

		const uint8_t rows;
		const uint8_t columns;

//		rows ↓		columns ↓
		std::array<std::array<float, 4>, 4> matrix;
	};

	class ScaleMatrix
	{
	public:
		ScaleMatrix() : rows(4), columns(4)
		{
			matrix = { {
				{1, 0, 0, 0},
				{0, 1, 0, 0},
				{0, 0, 1, 0},
				{0, 0, 0, 1}
			} };
		}
		ScaleMatrix(float x, float y, float z) : rows(4), columns(4)
		{
			matrix = { {
				{x, 0, 0, 0},
				{0, y, 0, 0},
				{0, 0, z, 0},
				{0, 0, 0, 1}
			} };
		}

		~ScaleMatrix() {};

		void ChangeScaleValues(float x, float y, float z)
		{
			matrix = { {
				{x, 0, 0, 0},
				{0, y, 0, 0},
				{0, 0, z, 0},
				{0, 0, 0, 1}
			} };
		}

		Matrix operator* (Matrix other)
		{
			if (columns == other.rows)
			{
				std::vector<std::vector<float>> result(rows, std::vector<float>(other.columns, 0));

				for (int i = 0; i < rows; i++)
				{
					for (int j = 0; j < other.columns; j++)
					{
						for (int k = 0; k < rows; k++)
						{
							result[i][j] += matrix[i][k] * other.matrix[k][j];
						}
					}
				}

				Matrix out(rows, other.columns);
				out.CreateMatrix(result);
				return out;
			}
			else
			{
				std::cout << "Matrices can not be multiplied. Incompatible size." << std::endl;
				return Matrix();
			}
		}

		const uint8_t rows;
		const uint8_t columns;

//		rows ↓		columns ↓
		std::array<std::array<float, 4>, 4> matrix;
	};

	class RotationMatrix
	{
	public:
		RotationMatrix() : rows(4), columns(4)
		{
			matrix = { {
				{1, 0, 0, 0},
				{0, 1, 0, 0},
				{0, 0, 1, 0},
				{0, 0, 0, 1}
			} };
		}
		RotationMatrix(float angle, int plane) : rows(4), columns(4)
		{
			switch (plane)
			{
			case LM_ROTATE_X_PLANE:
				matrix = { {
					{1, 0, 0, 0},
					{0, std::cos(angle), -std::sin(angle), 0},
					{0, std::sin(angle), std::cos(angle), 0},
					{0, 0, 0, 1}
				} };
				break;
			case LM_ROTATE_Y_PLANE:
				matrix = { {
					{std::cos(angle), 0, std::sin(angle), 0},
					{0, 1, 0, 0},
					{-std::sin(angle), 0, std::cos(angle), 0},
					{0, 0, 0, 1}
				} };
				break;
			case LM_ROTATE_Z_PLANE:
				matrix = { {
					{std::cos(angle), -std::sin(angle), 0, 0},
					{std::sin(angle), std::cos(angle), 0, 0},
					{0, 0, 1, 0},
					{0, 0, 0, 1}
				} };
				break;
			default:
				matrix = { {
					{1, 0, 0, 0},
					{0, 1, 0, 0},
					{0, 0, 1, 0},
					{0, 0, 0, 1}
				} };
				break;
			}
		}

		~RotationMatrix() {};

		void ChangeRotationAngle(float angle, int plane)
		{
			switch (plane)
			{
			case LM_ROTATE_X_PLANE:
				matrix = { {
					{1, 0, 0, 0},
					{0, std::cos(angle), -std::sin(angle), 0},
					{0, std::sin(angle), std::cos(angle), 0},
					{0, 0, 0, 1}
				} };
				break;
			case LM_ROTATE_Y_PLANE:
				matrix = { {
					{std::cos(angle), 0, std::sin(angle), 0},
					{0, 1, 0, 0},
					{-std::sin(angle), 0, std::cos(angle), 0},
					{0, 0, 0, 1}
				} };
				break;
			case LM_ROTATE_Z_PLANE:
				matrix = { {
					{std::cos(angle), -std::sin(angle), 0, 0},
					{std::sin(angle), std::cos(angle), 0, 0},
					{0, 0, 1, 0},
					{0, 0, 0, 1}
				} };
				break;
			default:
				matrix = { {
					{1, 0, 0, 0},
					{0, 1, 0, 0},
					{0, 0, 1, 0},
					{0, 0, 0, 1}
				} };
				break;
			}
		}

		Matrix operator* (Matrix other)
		{
			if (!(columns == other.rows))
			{
				std::vector<std::vector<float>> result(rows, std::vector<float>(other.columns, 0));

				for (int i = 0; i < rows; i++)
				{
					for (int j = 0; j < other.columns; j++)
					{
						for (int k = 0; k < rows; k++)
						{
							result[i][j] += matrix[i][k] * other.matrix[k][j];
						}
					}
				}

				Matrix out(rows, other.columns);
				out.CreateMatrix(result);
				return out;
			}
			else
			{
				std::cout << "Matrices can not be multiplied. Incompatible size." << std::endl;
				return Matrix();
			}
		}

		const uint8_t rows;
		const uint8_t columns;

//		rows ↓		columns ↓
		std::array<std::array<float, 4>, 4> matrix;
	};
	class OrthographicProjectionMatrix
	{
	public:
		OrthographicProjectionMatrix() : rows(4), columns(4)
		{
			matrix = { {
				{1, 0, 0, 0},
				{0, 1, 0, 0},
				{0, 0, 1, 0},
				{0, 0, 0, 1}
			} };
		}

		OrthographicProjectionMatrix(float left, float right, float top, float bottom, float near, float far) : rows(4), columns(4)
		{
			matrix = { {
				{(2 / (right - left)),	0,						0,					((right + left) / (right - left))},
				{0,						(2 / (top - bottom)),	0,					((top + bottom) / (top - bottom))},
				{0,						0,						(2 / (far - near)),	((far + near) / (far - near))},
				{0,						0,						0,					1}
			} };
		}

		~OrthographicProjectionMatrix() {};

		void ChangeMatrix(float left, float right, float top, float bottom, float near, float far)
		{
			matrix = { {
				{(2 / (right - left)),	0,						0,					((right + left) / (right - left))},
				{0,						(2 / (top - bottom)),	0,					((top + bottom) / (top - bottom))},
				{0,						0,						(2 / (far - near)),	((far + near) / (far - near))},
				{0,						0,						0,					1}
			} };
		}

		const uint8_t rows;
		const uint8_t columns;

		//		rows ↓		columns ↓
		std::array<std::array<float, 4>, 4> matrix;
	};

	class PerspectiveProjectionMatrix
	{
	public:
		PerspectiveProjectionMatrix() : rows(4), columns(4)
		{
			matrix = { {
				{1, 0, 0, 0},
				{0, 1, 0, 0},
				{0, 0, 1, 0},
				{0, 0, 0, 1}
			} };
		}

		PerspectiveProjectionMatrix(float fov, float aspect, float near, float far) : rows(4), columns(4)
		{
			matrix = { {
				{(2 * near / (aspect * std::tan(fov / 2))),	0,			0,								0},
				{0,						(2 * near / std::tan(fov / 2)),	0,								0},
				{0,						0,								(-(far + near) / (far - near)),	(-(2 * far * near) / (far - near))},
				{0,						0,								-1,								0}
			} };
		}

		~PerspectiveProjectionMatrix() {};

		void ChangeMatrix(float fov, float aspect, float far, float near)
		{
			matrix = { {
				{(2 * near / (aspect * std::tan(fov / 2))),	0,			0,								0},
				{0,						(2 * near / std::tan(fov / 2)),	0,								0},
				{0,						0,								(-(far + near) / (far - near)),	(-(2 * far * near) / (far - near))},
				{0,						0,								-1,								0}
			} };
		}

		const uint8_t rows;
		const uint8_t columns;

		//		rows ↓		columns ↓
		std::array<std::array<float, 4>, 4> matrix;
	};
}
