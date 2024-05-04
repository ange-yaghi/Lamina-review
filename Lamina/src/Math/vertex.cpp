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
	if (object == nullptr) return;

	vertices.clear();
	normals.clear();
	textures.clear();

	//vertices.resize(object->faces.size());
	//normals.resize(object->faces.size());
	//textures.resize(object->faces.size());

	vec3u vertTemp;
	vec3u normTemp;
	vec3u textrTemp;

	std::array<GLTriangleVert, 3> vertBuf;
	std::array<GLTriangleNorm, 3> normBuf;
	std::array<GLTriangleTextr, 3> textrBuf;
	for (int i = 0; i < object->faces.size(); i++)
	{
		vertTemp.CreateVector({ 
			object->faces[i][0].vector[0], 
			object->faces[i][1].vector[0], 
			object->faces[i][2].vector[0] });

		textrTemp.CreateVector({
			object->faces[i][0].vector[1], 
			object->faces[i][1].vector[1], 
			object->faces[i][2].vector[1] });

		normTemp.CreateVector({
			object->faces[i][0].vector[2], 
			object->faces[i][1].vector[2], 
			object->faces[i][2].vector[2] });

		//load vertices
		vertBuf[0].CreateVector({
			(GLfloat)object->vertices[vertTemp.vector[0] - 1].vector[0],
			(GLfloat)object->vertices[vertTemp.vector[0] - 1].vector[1],
			(GLfloat)object->vertices[vertTemp.vector[0] - 1].vector[2], 0 });
		vertBuf[1].CreateVector({
			(GLfloat)object->vertices[vertTemp.vector[1] - 1].vector[0],
			(GLfloat)object->vertices[vertTemp.vector[1] - 1].vector[1],
			(GLfloat)object->vertices[vertTemp.vector[1] - 1].vector[2], 0 });
		vertBuf[2].CreateVector({
			(GLfloat)object->vertices[vertTemp.vector[2] - 1].vector[0],
			(GLfloat)object->vertices[vertTemp.vector[2] - 1].vector[1],
			(GLfloat)object->vertices[vertTemp.vector[2] - 1].vector[2], 0 });

		//load normals
		normBuf[0].CreateVector({
			(GLfloat)object->normals[normTemp.vector[0] - 1].vector[0],
			(GLfloat)object->normals[normTemp.vector[0] - 1].vector[1],
			(GLfloat)object->normals[normTemp.vector[0] - 1].vector[2] });
		normBuf[1].CreateVector({
			(GLfloat)object->normals[normTemp.vector[1] - 1].vector[0],
			(GLfloat)object->normals[normTemp.vector[1] - 1].vector[1],
			(GLfloat)object->normals[normTemp.vector[1] - 1].vector[2] });
		normBuf[2].CreateVector({
			(GLfloat)object->normals[normTemp.vector[2] - 1].vector[0],
			(GLfloat)object->normals[normTemp.vector[2] - 1].vector[1],
			(GLfloat)object->normals[normTemp.vector[2] - 1].vector[2] });

		//load textures
		textrBuf[0].CreateVector({
			(GLfloat)object->textureCoordinates[textrTemp.vector[0] - 1].vector[0],
			(GLfloat)object->textureCoordinates[textrTemp.vector[0] - 1].vector[1], });
		textrBuf[1].CreateVector({
			(GLfloat)object->textureCoordinates[textrTemp.vector[1] - 1].vector[0],
			(GLfloat)object->textureCoordinates[textrTemp.vector[1] - 1].vector[1], });
		textrBuf[2].CreateVector({
			(GLfloat)object->textureCoordinates[textrTemp.vector[2] - 1].vector[0],
			(GLfloat)object->textureCoordinates[textrTemp.vector[2] - 1].vector[1], });

		vertices.push_back(vertBuf);
		normals.push_back(normBuf);
		textures.push_back(textrBuf);
	}
}