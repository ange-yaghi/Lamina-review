#pragma once
#include "../Lamina/include/Math/matrix.hpp"
#include "../Lamina/include/Math/vector.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace lm
{
	class WavefrontObject
	{
	public:
		WavefrontObject() {};
		WavefrontObject(std::string _name, std::vector<vec4d> _vertices, std::vector<vec3d> _normals, std::vector<vec2d> _textureCoordinates, std::vector<vec3u[3]> _faces) :
			vertices(_vertices), normals(_normals), textureCoordinates(_textureCoordinates) {};
		WavefrontObject(std::string path); //load from an .obj file

		void TranslateObject(double x, double y, double z);
		void ScaleObject(double x, double y, double z);
		void RotateObject(double angle, int plane);
	//private:
		std::vector<vec4d> vertices;
		std::vector<vec3d> normals;
		std::vector<vec2d> textureCoordinates;
		std::vector<std::array<vec3u, 3>> faces;

		void LoadFromOBJ(std::string objContent);
	};

	class GLObject
	{
	public:
		GLObject() : object(nullptr) {};
		GLObject(WavefrontObject* _object) : object(_object) {};

		void ParseObject();

		WavefrontObject* object;
		std::vector<std::array<GLTriangleVert, 3>> vertices;
		std::vector< std::array<GLTriangleNorm, 3>> normals;
		std::vector< std::array<GLTriangleTextr, 3>> textures;
	};
}