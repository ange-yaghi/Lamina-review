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

		bool IsDataValid()
		{
			if (vertices.size() <= 0) return false;
			else if (normals.size() <= 0) return false;
			else if (textureCoordinates.size() <= 0) return false;
			else if (faces.size() <= 0) return false;
			else return true;
		}

		void Delete()
		{
			vertices.clear();
			normals.clear();
			textureCoordinates.clear();
			faces.clear();
			vertices.shrink_to_fit();
			normals.shrink_to_fit();
			textureCoordinates.shrink_to_fit();
			faces.shrink_to_fit();
		}
	};

	//class to load object from wavefront file
	class WavefrontObject
	{
	public:
		WavefrontObject() {};
		WavefrontObject(std::string path); //load from an .obj file

		std::string _path;

		std::atomic_bool isLoadDone;
		std::promise<ObjectData> _promisedData;
		std::future<ObjectData> _futureData;
		std::thread loadThread;
		
		lm::ObjectData data;
		std::vector<GLfloat> meshData;

		void LoadFromOBJ(std::string path, std::promise<ObjectData> promisedData);
		bool WaitForLoad();

		void ParseObject();
		void DeleteUnprocessedData() { data.Delete(); }
	};

	//gl compatible object
	//class GLObject
	//{
	//public:
	//	GLObject() : object(nullptr) {};
	//	GLObject(WavefrontObject& _object) : object(&_object), vertices(_object.data.vertices), normals(_object.data.normals), textureCoordinates(_object.data.textureCoordinates) { ParseObject(); };

	//	void ParseObject();

	//	WavefrontObject* object;

	//	std::vector<GLuint> indeces;
	//	std::vector<vec4d> vertices;
	//	std::vector<vec3d> normals;
	//	std::vector<vec2d> textureCoordinates;

	//	std::vector<GLfloat> meshData;
	//};
}
#endif // !LM_VERTEX