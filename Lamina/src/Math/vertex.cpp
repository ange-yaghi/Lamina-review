#include "../Lamina/include/Math/vertex.hpp"

lm::WavefrontObject::WavefrontObject(std::string path)
{
	std::ifstream objectFile(path);
	std::string buffer;
	while (std::getline(objectFile, buffer))
	{
		LoadFromOBJ(buffer);
		buffer.clear();
	}
	objectFile.close();
}

void lm::WavefrontObject::LoadFromOBJ(std::string objContent)
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
		std::array<double, 3> coordinates;
		for(int i = 0; i < coordinates.size(); i++)
		{
			while (!isspace(objContent[pos]) && pos < objContent.size())
			{
				buffer += objContent[pos];
				pos++;
			}
			coordinates[i] = std::stod(buffer);
			buffer.clear();
			pos++;
		}
		
		vec4d vertex;
		vertex.CreateVector({ coordinates[0], coordinates[1], coordinates[2], 1});
		vertices.push_back(vertex);
	}
	else if (buffer == "vn")
	{
		buffer.clear();
		std::array<double, 3> coordinates;
		for (int i = 0; i < coordinates.size(); i++)
		{
			while (!isspace(objContent[pos]) && pos < objContent.size())
			{
				buffer += objContent[pos];
				pos++;
			}
			coordinates[i] = std::stod(buffer);
			buffer.clear();
			pos++;
		}

		vec3d normal;
		normal.CreateVector({ coordinates[0], coordinates[1], coordinates[2]});
		normals.push_back(normal);
	}
	else if (buffer == "vt")
	{
		buffer.clear();
		std::array<double, 2> coordinates;
		for (int i = 0; i < coordinates.size(); i++)
		{
			while (!isspace(objContent[pos]) && pos < objContent.size())
			{
				buffer += objContent[pos];
				pos++;
			}
			coordinates[i] = std::stod(buffer);
			buffer.clear();
			pos++;
		}

		vec2d textureCoordinate;
		textureCoordinate.CreateVector({ coordinates[0], coordinates[1]});
		textureCoordinates.push_back(textureCoordinate);
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
					trv[i].vector[trNum] = std::stoi(trBuffer);
					trBuffer.clear();
					trNum++;
				}
			}

			trNum = 0;
			buffer.clear();
			pos++;
		}
		//tr.CreateVector(trv);
		faces.push_back(trv);
	}
}

void lm::WavefrontObject::TranslateObject(double x, double y, double z)
{
	for(int i = 0; i < vertices.size(); i++) vertices[i] = lm::TranslateVector(vertices[i], x, y, z);
}
void lm::WavefrontObject::ScaleObject(double x, double y, double z)
{
	for (int i = 0; i < vertices.size(); i++) vertices[i] = lm::ScaleVector(vertices[i], x, y, z);
}
void lm::WavefrontObject::RotateObject(double angle, int plane)
{
	for (int i = 0; i < vertices.size(); i++) vertices[i] = lm::RotateVector(vertices[i], angle, plane);
}

void lm::GLObject::ParseObject()
{
	meshData.clear();
	if (object == nullptr) return;

	//std::array<GLuint, 3> vertexArrayBuffer;
	//std::array<GLuint, 3> normalArrayBuffer;
	//std::array<GLuint, 3> textureArrayBuffer;

	for (int i = 0; i < object->faces.size(); i++)
		for (int j = 0; j < object->faces[i].size(); j++)
			for (int k = 0; k < object->faces[i][j].vector.size(); k++) indeces.push_back(object->faces[i][j].vector[k]);

	unsigned int numberOfObjects = indeces.size();
	for (int i = 0; i < numberOfObjects; i += 3)
	{
		meshData.push_back(vertices[indeces[i] - 1].x());
		meshData.push_back(vertices[indeces[i] - 1].y());
		meshData.push_back(vertices[indeces[i] - 1].z());
		meshData.push_back(vertices[indeces[i] - 1].w());

		meshData.push_back(textureCoordinates[indeces[i + 1] - 1].x());
		meshData.push_back(textureCoordinates[indeces[i + 1] - 1].y());

		meshData.push_back(normals[indeces[i + 2] -1].x());
		meshData.push_back(normals[indeces[i + 2] -1].y());
		meshData.push_back(normals[indeces[i + 2] -1].z());
	}
}

//void lm::GLObject::RuntimeParse()
//{
//	unsigned int numberOfObjects = object->faces.size();
//	for (int i = 0; i < numberOfObjects; i += 9)
//	{
//		meshData.push_back(vertices[indeces[i] - 1].x());
//		meshData.push_back(vertices[indeces[i + 1] - 1].y());
//		meshData.push_back(vertices[indeces[i + 2] - 1].z());
//		meshData.push_back(vertices[indeces[i + 3] - 1].w());
//
//		meshData.push_back(vertices[indeces[i + 4] - 1].x());
//		meshData.push_back(vertices[indeces[i + 5] - 1].y());
//		meshData.push_back(vertices[indeces[i + 6] - 1].z());
//
//		meshData.push_back(vertices[indeces[i + 7] - 1].x());
//		meshData.push_back(vertices[indeces[i + 8] - 1].y());
//	}
//}

void lm::GLObject::TranslateObject(double x, double y, double z)
{
	for (int i = 0; i < vertices.size(); i++) vertices[i] = lm::TranslateVector(vertices[i], x, y, z);
	ParseObject();
}
void lm::GLObject::ScaleObject(double x, double y, double z)
{
	for (int i = 0; i < vertices.size(); i++) vertices[i] = lm::ScaleVector(vertices[i], x, y, z);
	ParseObject();
}
void lm::GLObject::RotateObject(double angle, int plane)
{
	for (int i = 0; i < vertices.size(); i++) vertices[i] = lm::RotateVector(vertices[i], angle, plane);
	ParseObject();
}