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

		void TranslateObject(float x, float y, float z);
		void ScaleObject(float x, float y, float z);
		void RotateObject(float angle, int plane);
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
		GLObject(WavefrontObject& _object) : object(&_object), vertices(_object.vertices), normals(_object.normals), textureCoordinates(_object.textureCoordinates) { ParseObject(); };

		void ParseObject();
		//void RuntimeParse();

		void TranslateObject(float x, float y, float z);
		void ScaleObject(float x, float y, float z);
		void RotateObject(float angle, int plane);

		//inline void TranslateGLObject(float x, float y, float z) { TranslateObject(x, y, z); ParseObject(); }
		//inline void ScaleGLObject(float x, float y, float z) { ScaleObject(x, y, z); ParseObject(); }
		//inline void RotateGLObject(float angle, int plane) { RotateObject(angle, plane); ParseObject(); }

		void ReloadObject()
		{
			vertices = object->vertices;
			normals = object->normals;
			textureCoordinates = object->textureCoordinates;
			ParseObject();
			//RuntimeParse();
		}

		void ChangeMesh(WavefrontObject& _object)
		{
			object = &_object;
			ReloadObject();
			ParseObject();
			//ReloadObject();
		}

		WavefrontObject* object;
		std::vector<GLuint> indeces;

		std::vector<vec4d> vertices;
		std::vector<vec3d> normals;
		std::vector<vec2d> textureCoordinates;

		std::vector<GLfloat> meshData;
	};
}