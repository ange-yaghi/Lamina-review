#include <../Lamina/include/Math/vertex.hpp>
#include <chrono>
#include <iostream>

int main()
{

	auto start = std::chrono::steady_clock::now();
	lm::WavefrontObject test("Objects/163k_triangulated_Mesh_Icosphere.obj");
	auto end = std::chrono::steady_clock::now();

	float avVertexLoad = test.vertices.size() / std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(std::chrono::duration_cast<std::chrono::milliseconds>(end - start)).count() * 1000;
	std::cout << "Loading object: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << "\tVertices per second: " << avVertexLoad << std::endl;

	//std::cout << "\nvertices:\n\nx\ty\tz\tw\n";
	//for (int i = 0; i < test.vertices.size(); i++) std::cout << test.vertices[i].vector[0] << "\t" << test.vertices[i].vector[1] << "\t" << test.vertices[i].vector[2] << "\t" << test.vertices[i].vector[3] << "\n";
	//std::cout << "\nnormals:\n\nx\ty\tz\n";
	//for (int i = 0; i < test.normals.size(); i++) std::cout << test.normals[i].vector[0] << "\t" << test.normals[i].vector[1] << "\t" << test.normals[i].vector[2] << "\n";
	//std::cout << "\ntexture coordinates:\n\nx\ty\n";
	//for (int i = 0; i < test.textureCoordinates.size(); i++) std::cout << test.textureCoordinates[i].vector[0] << "\t" << test.textureCoordinates[i].vector[1] << "\n";
	//std::cout << "\nfaces:\n\n";
	//for (int i = 0; i < test.faces.size(); i++)
	//	std::cout << test.faces[i][0].x() << "/"
	//	<< test.faces[i][0].y() << "/"
	//	<< test.faces[i][0].z() << "\t"
	//	<< test.faces[i][1].x() << "/"
	//	<< test.faces[i][1].y() << "/"
	//	<< test.faces[i][1].z() << "\t"
	//	<< test.faces[i][2].x() << "/"
	//	<< test.faces[i][2].y() << "/"
	//	<< test.faces[i][2].z() << "\n";

	auto startGL = std::chrono::steady_clock::now();
	lm::GLObject testObj(test);
	auto endGL = std::chrono::steady_clock::now();

	float avVertex = test.vertices.size() / std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(std::chrono::duration_cast<std::chrono::milliseconds>(endGL - startGL)).count() * 1000;
	std::cout << "\nInitial parsing: " << std::chrono::duration_cast<std::chrono::milliseconds>(endGL - startGL) << "\tvertices per second: " << avVertex << std::endl;

	startGL = std::chrono::steady_clock::now();
	testObj.ScaleObject(0.5, 0.5, 0.5);
	endGL = std::chrono::steady_clock::now();

	avVertex = test.vertices.size() / std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(std::chrono::duration_cast<std::chrono::milliseconds>(endGL - startGL)).count() * 1000;
	std::cout << "\nTranslation: " << std::chrono::duration_cast<std::chrono::milliseconds>(endGL - startGL) << "\tvertices per second: " << avVertex << std::endl;

	startGL = std::chrono::steady_clock::now();
	testObj.TranslateObject(0.2, 0.2, 0.2);
	endGL = std::chrono::steady_clock::now();

	avVertex = test.vertices.size() / std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(std::chrono::duration_cast<std::chrono::milliseconds>(endGL - startGL)).count() * 1000;
	std::cout << "\nScaling: " << std::chrono::duration_cast<std::chrono::milliseconds>(endGL - startGL) << "\t\tvertices per second: " << avVertex << std::endl;

	startGL = std::chrono::steady_clock::now();
	testObj.RotateObject(0.2, LM_ROTATE_X_PLANE);
	endGL = std::chrono::steady_clock::now();

	avVertex = test.vertices.size() / std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(std::chrono::duration_cast<std::chrono::milliseconds>(endGL - startGL)).count() * 1000;
	std::cout << "\nRotation x: " << std::chrono::duration_cast<std::chrono::milliseconds>(endGL - startGL) << "\tvertices per second: " << avVertex << std::endl;

	startGL = std::chrono::steady_clock::now();
	testObj.RotateObject(-0.2, LM_ROTATE_Y_PLANE);
	endGL = std::chrono::steady_clock::now();

	avVertex = test.vertices.size() / std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(std::chrono::duration_cast<std::chrono::milliseconds>(endGL - startGL)).count() * 1000;
	std::cout << "\nRotation y: " << std::chrono::duration_cast<std::chrono::milliseconds>(endGL - startGL) << "\tvertices per second: " << avVertex << std::endl;

	startGL = std::chrono::steady_clock::now();
	testObj.RotateObject(1, LM_ROTATE_Z_PLANE);
	endGL = std::chrono::steady_clock::now();

	avVertex = test.vertices.size() / std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(std::chrono::duration_cast<std::chrono::milliseconds>(endGL - startGL)).count() * 1000;
	std::cout << "\nRotation z: " << std::chrono::duration_cast<std::chrono::milliseconds>(endGL - startGL) << "\tvertices per second: " << avVertex << std::endl;

	//for (int i = 0; i < testObj.vertices.size(); i++) std::cout <<
	//	testObj.vertices[i][0].vector[0] << "\t" <<
	//	testObj.vertices[i][0].vector[1] << "\t" <<
	//	testObj.vertices[i][0].vector[2] << "\t|\t" <<
	//	testObj.vertices[i][1].vector[0] << "\t" <<
	//	testObj.vertices[i][1].vector[1] << "\t" <<
	//	testObj.vertices[i][1].vector[2] << "\t|\t" <<
	//	testObj.vertices[i][2].vector[0] << "\t" <<
	//	testObj.vertices[i][2].vector[1] << "\t" <<
	//	testObj.vertices[i][2].vector[2] << "\n";
	//std::cout << "\n\nTriangle normals:\n";
	//for (int i = 0; i < testObj.normals.size(); i++) std::cout <<
	//	testObj.normals[i][0].vector[0] << "\t" <<
	//	testObj.normals[i][0].vector[1] << "\t" <<
	//	testObj.normals[i][0].vector[2] << "\t|\t" <<
	//	testObj.normals[i][1].vector[0] << "\t" <<
	//	testObj.normals[i][1].vector[1] << "\t" <<
	//	testObj.normals[i][1].vector[2] << "\t|\t" <<
	//	testObj.normals[i][2].vector[0] << "\t" <<
	//	testObj.normals[i][2].vector[1] << "\t" <<
	//	testObj.normals[i][2].vector[2] << "\n";
	//std::cout << "\n\nTriangle texture coordinates:\n";
	//for (int i = 0; i < testObj.textures.size(); i++) std::cout <<
	//	testObj.textures[i][0].vector[0] << "\t" <<
	//	testObj.textures[i][0].vector[1] << "\t|\t" <<
	//	testObj.textures[i][1].vector[0] << "\t" <<
	//	testObj.textures[i][1].vector[1] << "\t|\t" <<
	//	testObj.textures[i][2].vector[0] << "\t" <<
	//	testObj.textures[i][2].vector[1] << "\n";

	std::string str;
	std::getline(std::cin, str);
}