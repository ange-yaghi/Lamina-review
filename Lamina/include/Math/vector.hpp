#ifndef LM_VECTOR
#define LM_VECTOR

#include "../Lamina/include/Math/matrix.hpp"
#include <glad/glad.h>
#include <iostream>
#include <stdint.h>
#include <vector>

namespace lm
{
	//Main classs definition
	template<typename t_vector, uint8_t t_vec_size>
	class Vector
	{
	public:
		Vector() : data{} {};
		Vector(const std::vector<t_vector>& _vector) { CreateVector(_vector); }
		void CreateVector(const std::array<t_vector, t_vec_size>& _vector)
		{
			if (_vector.size() == data.size()) std::copy_n(_vector.begin(), t_vec_size, data.begin());
			else std::cout << "Unable to assign vector. Incompatible size" << std::endl;
		}

		Vector operator+ (const t_vector &other)
		{
			lm::Vector<t_vector, 2> result(this->data);
			for (int i = 0; i < this->data.size(); i++) result.data[i] += other;
			return result;
		}

		Vector operator+ (Vector& other)
		{
			if (this->data.size() == other.data.size())
			{
				lm::Vector<t_vector, 2> result(this->data);
				for (int i = 0; i < this->data.size(); i++) result.data[i] += other.data[i];
				return result;
			}
			else std::cout << "Incompatible vector size for addition\n";
		}

		Vector operator+= (Vector& other)
		{
			if (this->data.size() != other.data.size())
			{
				std::cout << "Incompatible vector size for addition\n";
				return *this;
			}
			for (int i = 0; i < this->data.size(); i++)
			{
				this->data[i] += other.data[i];
			}
			return *this;
		}

		Vector operator- (const t_vector &other)
		{
			for (int i = 0; i < data.size(); i++) data[i] -= other;
			return *this;
		}
		Vector operator-= (Vector& other)
		{
			if (other.data.size() == 3)
			{
				for (int i = 0; i < this->data.size(); i++) this->data[i] -= other.data[i];
				return *this;
			}
			else std::cout << "Incompatible vector size for addition\n";
		}
		Vector operator- (const Vector& other)
		{
			if (other.data.size() == 3)
			{
				lm::Vector<t_vector, 3> result(this->data);
				for (int i = 0; i < this->data.size(); i++) result.data[i] -= other.data[i];
				return result;
			}
			else std::cout << "Incompatible vector size for addition\n";
		}

		Vector operator*(const t_vector& scalar)
		{
			for (int i = 0; i < data.size(); i++)
			{
				data[i] *= scalar;
			}
			return *this;
		}

		Vector operator = (const Vector &other)
		{
			if (this == &other)
			{
				return *this;
			}

			this->data = other.data;
			return *this;
		}

		std::array<t_vector, t_vec_size> data;
	};

	//specialization for 2d vector
	template<typename t_vector>
	class Vector<t_vector, 2>
	{
	public:
		Vector() : data{} {};
		Vector(const std::array<t_vector, 2>& _vector) { CreateVector(_vector); }
		void CreateVector(const std::array<t_vector, 2>& _vector)
		{
			if (_vector.size() == data.size()) std::copy_n(_vector.begin(), 2, data.begin());
			else std::cout << "Unable to assign vector. Incompatible size" << std::endl;
		}

		Vector operator+ (const t_vector other)
		{
			lm::Vector<t_vector, 2> result(this->data);
			for (int i = 0; i < this->data.size(); i++) result.data[i] += other;
			return result;
		}
		Vector operator+ (Vector& other)
		{
			if (other.data.size() == 2)
			{
				lm::Vector<t_vector, 2> result(this->data);
				for (int i = 0; i < this->data.size(); i++) result.data[i] += other.data[i];
				return result;
			}
			else std::cout << "Incompatible vector size for addition\n";
		}
		Vector operator+= (Vector& other)
		{
			if (this->data.size() != other.data.size())
			{
				std::cout << "Incompatible vector size for addition\n";
				return *this;
			}
			for (int i = 0; i < this->data.size(); i++)
			{
				this->data[i] += other.data[i];
			}
			return *this;
		}
		Vector operator- (const t_vector other)
		{
			for (int i = 0; i < data.size(); i++) data[i] -= other;
			return *this;
		}
		Vector operator-= (Vector& other)
		{
			if (other.data.size() == 3)
			{
				for (int i = 0; i < this->data.size(); i++) this->data[i] -= other.data[i];
				return *this;
			}
			else std::cout << "Incompatible vector size for addition\n";
		}
		Vector operator- (const Vector& other)
		{
			if (other.data.size() == 3)
			{
				lm::Vector<t_vector, 3> result(this->data);
				for (int i = 0; i < this->data.size(); i++) result.data[i] -= other.data[i];
				return result;
			}
			else std::cout << "Incompatible vector size for addition\n";
		}

		Vector operator* (const t_vector& scalar) {
			return lm::Vector<t_vector, 2>({
				this->data[0] * scalar,
				this->data[1] * scalar,
				});
		}

		Vector operator = (const Vector& other)
		{
			if (this == &other)
			{
				return *this;
			}

			this->data = other.data;
			return *this;
		}

		std::array<t_vector, 2> data;

		inline t_vector& x() { return data[0]; }
		inline t_vector& y() { return data[1]; }
	};

	//specialization for 3d vector
	template<typename t_vector>
	class Vector<t_vector, 3>
	{
	public:
		Vector() : data{} {};
		Vector(const std::array<t_vector, 3>& _vector) { CreateVector(_vector); }
		void CreateVector(const std::array<t_vector, 3>& _vector)
		{
			if (_vector.size() == data.size()) std::copy_n(_vector.begin(), 3, data.begin());
			else std::cout << "Unable to assign vector. Incompatible size" << std::endl;
		}

		Vector operator+ (const t_vector other)
		{
			lm::Vector<t_vector, 3> result(this->data);
			for (int i = 0; i < this->data.size(); i++) result.data[i] += other;
			return result;
		}
		Vector operator+ (Vector& other)
		{
			if (other.data.size() == 3)
			{
				lm::Vector<t_vector, 3> result(this->data);
				for (int i = 0; i < this->data.size(); i++) result.data[i] += other.data[i];
				return result;
			}
			else std::cout << "Incompatible vector size for addition\n";
		}
		Vector operator+= (Vector& other)
		{
			if (this->data.size() != other.data.size())
			{
				std::cout << "Incompatible vector size for addition\n";
				return *this;
			}
			for (int i = 0; i < this->data.size(); i++)
			{
				this->data[i] += other.data[i];
			}
			return *this;
		}
		Vector operator- (const t_vector other)
		{
			for (int i = 0; i < data.size(); i++) data[i] -= other;
			return *this;
		}
		Vector operator-= (Vector& other)
		{
			if (other.data.size() == 3)
			{
				for (int i = 0; i < this->data.size(); i++) this->data[i] -= other.data[i];
				return *this;
			}
			else std::cout << "Incompatible vector size for addition\n";
		}
		Vector operator- (const Vector& other)
		{
			if (other.data.size() == 3)
			{
				lm::Vector<t_vector, 3> result(this->data);
				for (int i = 0; i < this->data.size(); i++) result.data[i] -= other.data[i];
				return result;
			}
			else std::cout << "Incompatible vector size for addition\n";
			return *this;
		}

		Vector operator* (const t_vector& scalar) {
			return lm::Vector<t_vector, 3>({
				this->data[0] * scalar,
				this->data[1] * scalar,
				this->data[2] * scalar
				});
		}

		Vector operator = (const Vector& other)
		{
			if (this == &other)
			{
				return *this;
			}

			this->data = other.data;
			return *this;
		}

		std::array<t_vector, 3> data;

		inline t_vector& x() { return data[0]; }
		inline t_vector& y() { return data[1]; }
		inline t_vector& z() { return data[2]; }
	};

	//specialization for 4d vector
	template<typename t_vector>
	class Vector<t_vector, 4>
	{
	public:
		Vector() : data{} {};
		Vector(const std::array<t_vector, 4>& _vector) { CreateVector(_vector); }
		void CreateVector(const std::array<t_vector, 4>& _vector)
		{
			if (_vector.size() == data.size()) std::copy_n(_vector.begin(), 4, data.begin());
			else std::cout << "Unable to assign vector. Incompatible size" << std::endl;
		}

		Vector operator+ (const t_vector other)
		{
			lm::Vector<t_vector, 4> result(this->data);
			for (int i = 0; i < this->data.size(); i++) result.data[i] += other;
			return result;
		}
		Vector operator+ (Vector& other)
		{
			if (other.data.size() == 4)
			{
				lm::Vector<t_vector, 4> result(this->data);
				for (int i = 0; i < this->data.size(); i++) result.data[i] += other.data[i];
				return result;
			}
			else std::cout << "Incompatible vector size for addition\n";
		}
		Vector operator+= (Vector& other)
		{
			if (this->data.size() != other.data.size())
			{
				std::cout << "Incompatible vector size for addition\n";
				return *this;
			}
			for (int i = 0; i < this->data.size(); i++)
			{
				this->data[i] += other.data[i];
			}
			return *this;
		}
		Vector operator- (const t_vector& other)
		{
			for (int i = 0; i < data.size(); i++) data[i] -= other;
			return *this;
		}
		Vector operator-= (Vector& other)
		{
			if (other.data.size() == 3)
			{
				for (int i = 0; i < this->data.size(); i++) this->data[i] -= other.data[i];
				return *this;
			}
			else std::cout << "Incompatible vector size for addition\n";
		}
		Vector operator- (const Vector& other)
		{
			if (other.data.size() == 3)
			{
				lm::Vector<t_vector, 3> result(this->data);
				for (int i = 0; i < this->data.size(); i++) result.data[i] -= other.data[i];
				return result;
			}
			else std::cout << "Incompatible vector size for addition\n";
		}

		Vector operator* (const t_vector& scalar)
		{
			return lm::Vector<t_vector, 4>({
				this->data[0] * scalar,
				this->data[1] * scalar,
				this->data[2] * scalar,
				this->data[3] * scalar
				});
		}

		Vector operator = (const Vector& other)
		{
			if (this == &other)
			{
				return *this;
			}

			this->data = other.data;
			return *this;
		}

		std::array<t_vector, 4> data;

		inline t_vector& x() { return data[0]; }
		inline t_vector& y() { return data[1]; }
		inline t_vector& z() { return data[2]; }
		inline t_vector& w() { return data[3]; }
	};

	//definitions for common types of vector
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

	typedef Vector<GLfloat, 4> GLTriangleVert;
	typedef Vector<GLfloat, 3> GLTriangleNorm;
	typedef Vector<GLfloat, 2> GLTriangleTextr;

	inline vec3f normalize(vec3f vec)
	{
		float length = std::sqrt((vec.x() * vec.x()) + (vec.y() * vec.y()) + (vec.z() * vec.z()));
		if (length == 0.f) return vec3f({ 0.f, 0.f, 0.f });
		return vec3f({ vec.x() / length, vec.y() / length, vec.z() / length });
	}
	inline vec3f CrossProduct(vec3f vec1, vec3f vec2)
	{
		return vec3f({ 
			vec1.y() * vec2.z() - vec1.z() * vec2.y(), 
			vec1.z() * vec2.x() - vec1.x() * vec2.z(), 
			vec1.x() * vec2.y() - vec1.y() * vec2.x() });
	}
	inline float DotProcuct(vec3f vec1, vec3f vec2)
	{
		return vec1.x() * vec2.x() + vec1.y() * vec2.y() + vec1.z() * vec2.z();
	}
	
	inline lm::vec2f Mat2xVec2(lm::mat2& matrix, lm::vec2f& vector)
	{
		return lm::vec2f({
			matrix.data[0][0] * vector.x() + matrix.data[0][1] * vector.y(),
			matrix.data[1][0] * vector.x() + matrix.data[1][1] * vector.y()
			});
	}
	inline lm::vec3f Mat3xVec3(lm::mat3& matrix, lm::vec3f& vector)
	{
		return lm::vec3f({
			matrix.data[0][0] * vector.x() + matrix.data[0][1] * vector.y() + matrix.data[0][2] * vector.z(),
			matrix.data[1][0] * vector.x() + matrix.data[1][1] * vector.y() + matrix.data[1][2] * vector.z(),
			matrix.data[2][0] * vector.x() + matrix.data[2][1] * vector.y() + matrix.data[2][2] * vector.z(),
			});
	}
	inline lm::vec4f Mat4xVec4(lm::mat4& matrix, lm::vec4f& vector)
	{
		return lm::vec4f({
			matrix.data[0][0] * vector.x() + matrix.data[0][1] * vector.y() + matrix.data[0][2] * vector.z() + matrix.data[0][3] * vector.w(),
			matrix.data[1][0] * vector.x() + matrix.data[1][1] * vector.y() + matrix.data[1][2] * vector.z() + matrix.data[1][3] * vector.w(),
			matrix.data[2][0] * vector.x() + matrix.data[2][1] * vector.y() + matrix.data[2][2] * vector.z() + matrix.data[2][3] * vector.w(),
			matrix.data[3][0] * vector.x() + matrix.data[3][1] * vector.y() + matrix.data[3][2] * vector.z() + matrix.data[3][3] * vector.w()
			});
	}
}
#endif // !LM_VECTOR