#include <../Lamina/include/Math/vertex.hpp>
#include <iostream>
#include <chrono>

int main()
{
	auto start = std::chrono::steady_clock::now();
	lm::Object test("C:/Users/borbg/Documents/CPP Projects/Lamina/Objects/testobj.obj");
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
		std::cout << test.faces[i].vector[0] << "/"
		<< test.faces[i].vector[1] << "/"
		<< test.faces[i].vector[2] << "\t"
		<< test.faces[i].vector[3] << "/"
		<< test.faces[i].vector[4] << "/"
		<< test.faces[i].vector[5] << "\t"
		<< test.faces[i].vector[6] << "/"
		<< test.faces[i].vector[7] << "/"
		<< test.faces[i].vector[8] << "\n";
}