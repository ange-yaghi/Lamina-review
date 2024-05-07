#include <../Lamina/include/colors.hpp>
#include <../Lamina/include/GL/opengl.hpp>
#include <../Lamina/include/Math/matrix.hpp>
#include <../Lamina/include/Math/vec2.hpp>
#include <../Lamina/include/window.hpp>
#include <../Lamina/include/GL/vertex_array.hpp>
#include <../Lamina/include/GL/imageLoader.h>
#include <chrono>
#include <iostream>

int main()
{
	if (!glfwInit()) return -1;
	lm::Window window(lm::vec2<int>(800, 800), "test window", LM_WINDOW_DEFAULT, 8);
	auto epoch = std::chrono::steady_clock::now();
	window.MakeContextCurrent();
	int time = 0;

	lm::WavefrontObject object("Objects/testmesh.obj");
	lm::GLObject _object(object);
	lm::VertexArray array(&_object);
	array.SetScale(0.5, 0.5, 0.5);
	array.SetRotation( 0.f, 3.1415f, 0.f);
	array.SetPosition(0, 0, 0);
	lm::Texture2D texture("Textures/test_texture.png", LM_RGB);
	array.SetTexture(texture);

	while (window.IsOpen())
	{
		glfwPollEvents();

		int state_w = glfwGetKey(window.window, GLFW_KEY_W);
		int state_a = glfwGetKey(window.window, GLFW_KEY_A);
		int state_s = glfwGetKey(window.window, GLFW_KEY_S);
		int state_d = glfwGetKey(window.window, GLFW_KEY_D);

		int state_i = glfwGetKey(window.window, GLFW_KEY_I);
		int state_k = glfwGetKey(window.window, GLFW_KEY_K);
		int state_j = glfwGetKey(window.window, GLFW_KEY_J);
		int state_l = glfwGetKey(window.window, GLFW_KEY_L);
		int state_t = glfwGetKey(window.window, GLFW_KEY_T);
		int state_g = glfwGetKey(window.window, GLFW_KEY_G);

		if (state_w == GLFW_PRESS) array.SetRotation(array.GetRotation().x() + 0.05f, array.GetRotation().y(), array.GetRotation().z());
		if (state_s == GLFW_PRESS) array.SetRotation(array.GetRotation().x() - 0.05f, array.GetRotation().y(), array.GetRotation().z());
		if (state_a == GLFW_PRESS) array.SetRotation(array.GetRotation().x(), array.GetRotation().y() - 0.05f, array.GetRotation().z());
		if (state_d == GLFW_PRESS) array.SetRotation(array.GetRotation().x(), array.GetRotation().y() + 0.05f, array.GetRotation().z());

		if (state_i == GLFW_PRESS) array.SetPosition(array.GetPosition().x(), array.GetPosition().y() + 0.01f, array.GetPosition().z());
		if (state_k == GLFW_PRESS) array.SetPosition(array.GetPosition().x(), array.GetPosition().y() - 0.01f, array.GetPosition().z());
		if (state_j == GLFW_PRESS) array.SetPosition(array.GetPosition().x() - 0.01f, array.GetPosition().y(), array.GetPosition().z());
		if (state_l == GLFW_PRESS) array.SetPosition(array.GetPosition().x() + 0.01f, array.GetPosition().y(), array.GetPosition().z());
		if (state_t == GLFW_PRESS) array.SetScale(array.GetScale().x() - 0.01f, array.GetScale().y() - 0.01f, array.GetScale().z() - 0.01f);
		if (state_g == GLFW_PRESS) array.SetScale(array.GetScale().x() + 0.01f, array.GetScale().y() + 0.01f, array.GetScale().z() + 0.01f);

		window.Clear(lm::Color{ 50, 50, 50, 255 });
		/*float time = std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - epoch)).count();*/
		time++;
		lm::ColorF color = { 0.0f, 1.0f, 1.0f, 1.0f };
		array.SetColor(lm::Get8BitColor(color));
		array.DrawArray();
		window.Display();
	}

//
//	std::vector<GLfloat> vertices = {
///*0*/	0.5f, 0.5f, 0.0f,		1.f, 0.f,
///*1*/	0.5f, -0.5f, 0.0f,		1.f, 1.f,
///*2*/	-0.5f, -0.5f, 0.0f,		0.f, 1.f,
///*3*/	-0.5f, 0.5f, 0.0f,		0.f, 0.f,
//	};
//
//	std::vector<GLuint> indices =
//	{
//		0, 1, 2,
//		0, 2, 3
//	};
//
//	int width, height, channels;
//	unsigned char* data = stbi_load("Textures/test_texture.png", &width, &height, &channels, 0);
//	GLuint texture;
//	glActiveTexture(GL_TEXTURE0);
//	glGenTextures(1, &texture);
//	glBindTexture(GL_TEXTURE_2D, texture);
//	if (data)
//	{
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//	}
//	else std::cout << "Failed to load texture" << std::endl;
//	stbi_image_free(data);
//	
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//
//	int width2, height2, channels2;
//	unsigned char* data2 = stbi_load("Textures/RGBA_test_texture.png", &width2, &height2, &channels2, 0);
//	GLuint texture2;
//	glActiveTexture(GL_TEXTURE1);
//	glGenTextures(1, &texture2);
//	glBindTexture(GL_TEXTURE_2D, texture2);
//	if (data2)
//	{
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width2, height2, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
//	}
//	else std::cout << "Failed to load texture" << std::endl;
//	stbi_image_free(data2);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//
//	while (window.IsOpen())
//	{
//		glfwPollEvents();
//
////		float time = std::chrono::duration_cast<std::chrono::duration<float>>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - epoch)).count();
//
//
//		window.Clear(lm::Color{ 50, 50, 50, 255 });
//
//		//glfwMakeContextCurrent(window.window);
//		//if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) std::cout << "Failed to load GLAD" << std::endl;
//
//		GLuint EBO;
//		glGenBuffers(1, &EBO);
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
//
//		GLuint vertexArray;
//		glGenVertexArrays(1, &vertexArray);
//
//		//compile promgram
//		GLuint program = lm::GLRenderer::CompileShader("Shaders/basicVertexShader.vert", "Shaders/basicFragShader.frag");
//		glUseProgram(program);
//
//		//set color
//		GLint colorVar = glGetUniformLocation(program, "passedColor");
//		lm::Color color(255, 255, 255, 255);
//		lm::ColorF floatColor = lm::GetFloatColor(color);
//		glUniform4f(colorVar, floatColor.r, floatColor.g, floatColor.b, floatColor.a);
//
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, texture);
//		glUniform1i(glGetUniformLocation(program, "inTexture"), 0);
//		glActiveTexture(GL_TEXTURE1);
//		glBindTexture(GL_TEXTURE_2D, texture2);
//		glUniform1i(glGetUniformLocation(program, "inTexture2"), 1);
//
//		//draw 
//		glBindVertexArray(vertexArray);
//		
//		GLuint vertexBuffer;
//		glGenBuffers(1, &vertexBuffer);
//		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
//		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
//
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
//		glEnableVertexAttribArray(0);
//
//		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
//		glEnableVertexAttribArray(1);
//
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
//
//		glDisableVertexAttribArray(0);
//		glDisableVertexAttribArray(1);
//		//glDisableVertexAttribArray(1);
//
//		window.Display();
//	}
	glfwTerminate();
	return 0;
}