#include "../Lamina/include/Math/vertex.hpp"

lm::Object::Object(std::string path)
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

void lm::Object::LoadFromOBJ(std::string objContent)
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
		std::vector<unsigned int> trv(9, NULL);
		for (int i = 0; i < trv.size(); i += 3)
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
					trv[i + trNum] = std::stoi(trBuffer);
					trBuffer.clear();
					trNum++;
				}
			}
			//trv[i + trNum] = std::stoi(trBuffer);
			trNum = 0;
			buffer.clear();
			pos++;
		}
		triangle tr;
		tr.CreateVector(trv);
		faces.push_back(tr);
	}
}

void lm::Object::TranslateArray(double x, double y, double z)
{
	for(int i = 0; i < vertices.size(); i++) vertices[i] = lm::TranslateVector(vertices[i], x, y, z);
}
void lm::Object::ScaleArray(double x, double y, double z)
{
	for (int i = 0; i < vertices.size(); i++) vertices[i] = lm::ScaleVector(vertices[i], x, y, z);
}
void lm::Object::RotateArray(double angle, int plane)
{
	for (int i = 0; i < vertices.size(); i++) vertices[i] = lm::RotateVector(vertices[i], angle, plane);
}