#include "../Lamina/include/Math/vertex.hpp"

lm::WavefrontObject::WavefrontObject(std::string path) : _path(path)
{
	_futureData = _promisedData.get_future();;
	loadThread = std::thread(std::bind(&lm::WavefrontObject::LoadFromOBJ, this, std::placeholders::_1, std::placeholders::_2), path, std::move(_promisedData));
	loadThread.detach();
}

bool lm::WavefrontObject::WaitForLoad()
{
	if (!isLoadDone) return false;
	data = _futureData.get();
	return true;
}

void lm::WavefrontObject::LoadFromOBJ(std::string path, std::promise<ObjectData> promisedData)
{
	lm::ObjectData returnObject;
	std::ifstream objectFile(path);
	std::string objContent;
	while (std::getline(objectFile, objContent))
	{
		std::string buffer;
		int pos = 0;
		while (!isspace(objContent[pos]) && pos < objContent.size())
		{
			buffer += objContent[pos];
			pos++;
		}
		pos++;

		if (buffer == "v")
		{
			buffer.clear();
			std::array<float, 3> coordinates;
			for (int i = 0; i < coordinates.size(); i++)
			{
				while (!isspace(objContent[pos]) && pos < objContent.size())
				{
					buffer += objContent[pos];
					pos++;
				}
				coordinates[i] = std::stof(buffer);
				buffer.clear();
				pos++;
			}

			vec4d vertex;
			vertex.CreateVector({ coordinates[0], coordinates[1], coordinates[2], 1 });
			returnObject.vertices.push_back(vertex);
		}
		else if (buffer == "vn")
		{
			buffer.clear();
			std::array<float, 3> coordinates;
			for (int i = 0; i < coordinates.size(); i++)
			{
				while (!isspace(objContent[pos]) && pos < objContent.size())
				{
					buffer += objContent[pos];
					pos++;
				}
				coordinates[i] = std::stof(buffer);
				buffer.clear();
				pos++;
			}

			vec3d normal;
			normal.CreateVector({ coordinates[0], coordinates[1], coordinates[2] });
			returnObject.normals.push_back(normal);
		}
		else if (buffer == "vt")
		{
			buffer.clear();
			std::array<float, 2> coordinates;
			for (int i = 0; i < coordinates.size(); i++)
			{
				while (!isspace(objContent[pos]) && pos < objContent.size())
				{
					buffer += objContent[pos];
					pos++;
				}
				coordinates[i] = std::stof(buffer);
				buffer.clear();
				pos++;
			}

			vec2d textureCoordinate;
			textureCoordinate.CreateVector({ coordinates[0], coordinates[1] });
			returnObject.textureCoordinates.push_back(textureCoordinate);
		}
		else if (buffer == "f")
		{
			buffer.clear();
			std::array<vec3u, 3> trv;
			for (int i = 0; i < trv.size(); i++)
			{
				while (!isspace(objContent[pos]) && pos < objContent.size())
				{
					buffer += objContent[pos];
					pos++;
				}

				buffer += '/';
				std::string trBuffer;
				int trNum = 0;
				for (int j = 0; j < buffer.size(); j++)
				{
					if (isdigit(buffer[j])) trBuffer += buffer[j];
					else
					{
						trv[i].data[trNum] = std::stoi(trBuffer);
						trBuffer.clear();
						trNum++;
					}
				}

				trNum = 0;
				buffer.clear();
				pos++;
			}
			//tr.CreateVector(trv);
			returnObject.faces.push_back(trv);
		}
		objContent.clear();
	}
	objectFile.close();
	promisedData.set_value(returnObject);
	isLoadDone = true;
}

//void lm::GLObject::ParseObject()
//{
//	meshData.clear();
//	if (object == nullptr) return;
//
//	for (int i = 0; i < object->data.faces.size(); i++)
//		for (int j = 0; j < object->data.faces[i].size(); j++)
//			for (int k = 0; k < object->data.faces[i][j].data.size(); k++) indeces.push_back(object->data.faces[i][j].data[k]);
//
//	unsigned int numberOfObjects = (unsigned int) indeces.size();
//	for (unsigned int i = 0; i < numberOfObjects; i += 3)
//	{
//		meshData.push_back((GLfloat)vertices[indeces[i] - 1].x());
//		meshData.push_back((GLfloat)vertices[indeces[i] - 1].y());
//		meshData.push_back((GLfloat)vertices[indeces[i] - 1].z());
//		meshData.push_back((GLfloat)vertices[indeces[i] - 1].w());
//
//		meshData.push_back((GLfloat)textureCoordinates[indeces[i + 1] - 1].x());
//		meshData.push_back((GLfloat)textureCoordinates[indeces[i + 1] - 1].y());
//
//		meshData.push_back((GLfloat)normals[indeces[i + 2] -1].x());
//		meshData.push_back((GLfloat)normals[indeces[i + 2] -1].y());
//		meshData.push_back((GLfloat)normals[indeces[i + 2] -1].z());
//	}
//}

void lm::WavefrontObject::ParseObject()
{
	meshData.clear();
	if (!data.IsDataValid()) return;

	std::vector<GLuint> indeces;

	for (int i = 0; i < data.faces.size(); i++)
		for (int j = 0; j < data.faces[i].size(); j++)
			for (int k = 0; k < data.faces[i][j].data.size(); k++) indeces.push_back(data.faces[i][j].data[k]);

	unsigned int numberOfObjects = (unsigned int)indeces.size();
	for (unsigned int i = 0; i < numberOfObjects; i += 3)
	{
		meshData.push_back((GLfloat)data.vertices[indeces[i] - 1].x());
		meshData.push_back((GLfloat)data.vertices[indeces[i] - 1].y());
		meshData.push_back((GLfloat)data.vertices[indeces[i] - 1].z());
		meshData.push_back((GLfloat)data.vertices[indeces[i] - 1].w());

		meshData.push_back((GLfloat)data.textureCoordinates[indeces[i + 1] - 1].x());
		meshData.push_back((GLfloat)data.textureCoordinates[indeces[i + 1] - 1].y());

		meshData.push_back((GLfloat)data.normals[indeces[i + 2] - 1].x());
		meshData.push_back((GLfloat)data.normals[indeces[i + 2] - 1].y());
		meshData.push_back((GLfloat)data.normals[indeces[i + 2] - 1].z());
	}
}