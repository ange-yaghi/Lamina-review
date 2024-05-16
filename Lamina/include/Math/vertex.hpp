#ifndef LM_VERTEX
#define LM_VERTEX

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

		std::vector<vec4d> vertices;
		std::vector<vec3d> normals;
		std::vector<vec2d> textureCoordinates;
		std::vector<std::array<vec3u, 3>> faces;

		void LoadStartPoint(std::string path);
		void LoadFromOBJ(std::string objContent);
	};

	class GLObject
	{
	public:
		GLObject() : object(nullptr) {};
		GLObject(WavefrontObject& _object) : object(&_object), vertices(_object.vertices), normals(_object.normals), textureCoordinates(_object.textureCoordinates) { ParseObject(); };

		void ParseObject();

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
		}

		WavefrontObject* object;
		std::vector<GLuint> indeces;

		std::vector<vec4d> vertices;
		std::vector<vec3d> normals;
		std::vector<vec2d> textureCoordinates;

		std::vector<GLfloat> meshData;
	};
}
#endif // !LM_VERTEX