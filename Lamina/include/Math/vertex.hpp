#ifndef LM_VERTEX
#define LM_VERTEX

#include "../Lamina/include/Math/matrix.hpp"
#include "../Lamina/include/Math/vector.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <thread>
#include <future>

namespace lm
{
	struct ObjectData
	{
		std::vector<vec4d> vertices;
		std::vector<vec3d> normals;
		std::vector<vec2d> textureCoordinates;
		std::vector<std::array<vec3u, 3>> faces;

		//void Clear()
		//{
		//	vertices.clear();
		//	normals.clear();
		//	textureCoordinates.clear();
		//	faces.clear();
		//}
	};

	//class to load object from wavefront file
	class WavefrontObject
	{
	public:
		WavefrontObject() {};
		WavefrontObject(std::string path); //load from an .obj file

		lm::ObjectData data;
		std::string _path;

		std::atomic_bool isLoadDone;
		std::promise<ObjectData> _promisedData;
		std::future<ObjectData> _futureData;
		std::thread loadThread;

		void LoadFromOBJ(std::string path, std::promise<ObjectData> promisedData);
		bool WaitForLoad();
	};

	//gl compatible object
	class GLObject
	{
	public:
		GLObject() : object(nullptr) {};
		GLObject(WavefrontObject& _object) : object(&_object), vertices(_object.data.vertices), normals(_object.data.normals), textureCoordinates(_object.data.textureCoordinates) { ParseObject(); };

		void ParseObject();

		void ReloadObject()
		{
			vertices = object->data.vertices;
			normals = object->data.normals;
			textureCoordinates = object->data.textureCoordinates;
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