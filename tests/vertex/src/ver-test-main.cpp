#include <../Lamina/include/Math/vertex.hpp>
#include <chrono>
#include <iostream>

int main()
{
	auto start = std::chrono::steady_clock::now();
	lm::WavefrontObject test("C:/Users/borbg/Documents/CPP Projects/Lamina/Objects/testobj.obj");
	auto end = std::chrono::steady_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	std::cout << "\nvertices:\n\nx\ty\tz\tw\n";
	for (int i = 0; i < test.vertices.size(); i++) std::cout << test.vertices[i].vector[0] << "\t" << test.vertices[i].vector[1] << "\t" << test.vertices[i].vector[2] << "\t" << test.vertices[i].vector[3] << "\n";
	std::cout << "\nnormals:\n\nx\ty\tz\n";
	for (int i = 0; i < test.normals.size(); i++) std::cout << test.normals[i].vector[0] << "\t" << test.normals[i].vector[1] << "\t" << test.normals[i].vector[2] << "\n";
	std::cout << "\ntexture coordinates:\n\nx\ty\n";
	for (int i = 0; i < test.textureCoordinates.size(); i++) std::cout << test.textureCoordinates[i].vector[0] << "\t" << test.textureCoordinates[i].vector[1] << "\n";
	std::cout << "\nfaces:\n\n";
	for (int i = 0; i < test.faces.size(); i++)
		std::cout << test.faces[i][0].x() << "/"
		<< test.faces[i][0].y() << "/"
		<< test.faces[i][0].z() << "\t"
		<< test.faces[i][1].x() << "/"
		<< test.faces[i][1].y() << "/"
		<< test.faces[i][1].z() << "\t"
		<< test.faces[i][2].x() << "/"
		<< test.faces[i][2].y() << "/"
		<< test.faces[i][2].z() << "\n";

	auto startGL = std::chrono::steady_clock::now();
	lm::GLObject testObj(&test);
	testObj.ParseObject();
	auto endGL = std::chrono::steady_clock::now();

	std::cout << "\n" << std::chrono::duration_cast<std::chrono::microseconds>(endGL - startGL) << "\n\nTriangle coordinates:\n" << std::endl;

	for (int i = 0; i < testObj.vertices.size(); i++) std::cout <<
		testObj.vertices[i][0].vector[0] << "\t" <<
		testObj.vertices[i][0].vector[1] << "\t" <<
		testObj.vertices[i][0].vector[2] << "\t|\t" <<
		testObj.vertices[i][1].vector[0] << "\t" <<
		testObj.vertices[i][1].vector[1] << "\t" <<
		testObj.vertices[i][1].vector[2] << "\t|\t" <<
		testObj.vertices[i][2].vector[0] << "\t" <<
		testObj.vertices[i][2].vector[1] << "\t" <<
		testObj.vertices[i][2].vector[2] << "\n";
	std::cout << "\n\nTriangle normals:\n";
	for (int i = 0; i < testObj.normals.size(); i++) std::cout <<
		testObj.normals[i][0].vector[0] << "\t" <<
		testObj.normals[i][0].vector[1] << "\t" <<
		testObj.normals[i][0].vector[2] << "\t|\t" <<
		testObj.normals[i][1].vector[0] << "\t" <<
		testObj.normals[i][1].vector[1] << "\t" <<
		testObj.normals[i][1].vector[2] << "\t|\t" <<
		testObj.normals[i][2].vector[0] << "\t" <<
		testObj.normals[i][2].vector[1] << "\t" <<
		testObj.normals[i][2].vector[2] << "\n";
	std::cout << "\n\nTriangle texture coordinates:\n";
	for (int i = 0; i < testObj.textures.size(); i++) std::cout <<
		testObj.textures[i][0].vector[0] << "\t" <<
		testObj.textures[i][0].vector[1] << "\t|\t" <<
		testObj.textures[i][1].vector[0] << "\t" <<
		testObj.textures[i][1].vector[1] << "\t|\t" <<
		testObj.textures[i][2].vector[0] << "\t" <<
		testObj.textures[i][2].vector[1] << "\n";
}