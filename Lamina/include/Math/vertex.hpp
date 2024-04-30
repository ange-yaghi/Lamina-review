#pragma once
#include "../Lamina/include/Math/vector.hpp"
#include "../Lamina/include/Math/matrix.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

namespace lm
{
	class Object
	{
	public:
		Object() {};
		Object(std::string _name, std::vector<vec4d> _vertices, std::vector<vec3d> _normals, std::vector<vec2d> _textureCoordinates, std::vector<vec3u[3]> _faces) :
			vertices(_vertices), normals(_normals), textureCoordinates(_textureCoordinates) {};
		Object(std::string path); //load from an .obj file

		void TranslateArray(double x, double y, double z);
		void ScaleArray(double x, double y, double z);
		void RotateArray(double angle, int plane);
	//private:
		std::vector<vec4d> vertices;
		std::vector<vec3d> normals;
		std::vector<vec2d> textureCoordinates;
		std::vector<triangle> faces;

		void LoadFromOBJ(std::string objContent);
	};
}