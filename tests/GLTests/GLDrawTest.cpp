#include <../Lamina/include/GL/colors.hpp>
#include <../Lamina/include/GL/opengl.hpp>
#include <../Lamina/include/Math/matrix.hpp>
#include <../Lamina/include/GL/window.hpp>
#include <../Lamina/include/GL/vertex_array.hpp>
#include <../Lamina/include/Math/constants.hpp>
#include <../Lamina/include/Math/timer.hpp>
#include <chrono>
#include <iostream>
#include <Windows.h>

void set_cursor(int x = 0, int y = 0)
{
	HANDLE handle;
	COORD coordinates;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	coordinates.X = x;
	coordinates.Y = y;
	SetConsoleCursorPosition(handle, coordinates);
}

int main()
{
	if (!glfwInit()) return -1;
	lm::Window window(lm::vec2i({800, 800}), "Lamina draw demo", LM_WINDOW_DEFAULT, 8);
	window.MakeContextCurrent();
	int frameCounter = 0;
	glfwSwapInterval(1);
	lm::Timer timer;

	lm::WavefrontObject object("Objects/testobj.obj");
	lm::GLObject _object(object);
	lm::PivotCamera cam(lm::vec3f({ 0, 0, 0 }), lm::vec3f({ 0, 0, 0 }), 10, window);
	lm::VertexArray array(&_object, window, cam);
	lm::VertexArray array2(&_object, window, cam);
	//lm::VertexArray arrays[100];
	array.SetScale(1, 1, 1);
	array.SetRotation(lm::constants::DegToRad(0.f), lm::constants::DegToRad(0.f), lm::constants::DegToRad(0.f));
	array.SetPosition(0, 0, 2);
	array2.SetPosition(0, 0, -2);
	lm::Texture2D texture("Textures/test_texture.png");
	array.SetTexture(texture);
	array2.SetTexture(texture);
	lm::vec3f rotation = array.GetRotation();
	//srand((unsigned int)time(NULL));
	//for (int i = 0; i < 100; i++)
	//{
	//	arrays[i].initaiateArray(&_object, window);
	//	int posx = rand() % 10;
	//	int posy = rand() % 10;
	//	int posz = rand() % 50;
	//	arrays[i].SetPosition((float) posx, (float) posy, (float) - posz);
	//	int rotx = rand() % 360;
	//	int roty = rand() % 360;
	//	int rotz = rand() % 360;
	//	arrays[i].SetRotation(lm::constants::DegToRad((float)rotx), lm::constants::DegToRad((float)roty), lm::constants::DegToRad((float)rotz));
	//	arrays[i].SetTexture(texture);
	//}
	//SetCursorPos(1, 0);

	//float averateFrameTime = 0;

	while (window.IsOpen())
	{
		//cam.GetInput();
		timer.Restart();
		glfwPollEvents();
		//int state_w = glfwGetKey(window.window, GLFW_KEY_W);
		//int state_a = glfwGetKey(window.window, GLFW_KEY_A);
		//int state_s = glfwGetKey(window.window, GLFW_KEY_S);
		//int state_d = glfwGetKey(window.window, GLFW_KEY_D);
		//int state_q = glfwGetKey(window.window, GLFW_KEY_Q);
		//int state_e = glfwGetKey(window.window, GLFW_KEY_E);

		//int state_i = glfwGetKey(window.window, GLFW_KEY_I);
		//int state_k = glfwGetKey(window.window, GLFW_KEY_K);
		//int state_j = glfwGetKey(window.window, GLFW_KEY_J);
		//int state_l = glfwGetKey(window.window, GLFW_KEY_L);
		//int state_t = glfwGetKey(window.window, GLFW_KEY_T);
		//int state_g = glfwGetKey(window.window, GLFW_KEY_G);

		//if (state_w == GLFW_PRESS) array.SetRotation(array.GetRotation().x() + 0.05f, array.GetRotation().y(), array.GetRotation().z());
		//if (state_s == GLFW_PRESS) array.SetRotation(array.GetRotation().x() - 0.05f, array.GetRotation().y(), array.GetRotation().z());
		//if (state_a == GLFW_PRESS) array.SetRotation(array.GetRotation().x(), array.GetRotation().y() - 0.05f, array.GetRotation().z());
		//if (state_d == GLFW_PRESS) array.SetRotation(array.GetRotation().x(), array.GetRotation().y() + 0.05f, array.GetRotation().z());
		//if (state_q == GLFW_PRESS) array.SetRotation(array.GetRotation().x(), array.GetRotation().y(), array.GetRotation().z() - 0.05f);
		//if (state_e == GLFW_PRESS) array.SetRotation(array.GetRotation().x(), array.GetRotation().y(), array.GetRotation().z() + 0.05f);

		//if (state_i == GLFW_PRESS) array.SetPosition(array.GetPosition().x(), array.GetPosition().y() + 0.01f, array.GetPosition().z());
		//if (state_k == GLFW_PRESS) array.SetPosition(array.GetPosition().x(), array.GetPosition().y() - 0.01f, array.GetPosition().z());
		//if (state_j == GLFW_PRESS) array.SetPosition(array.GetPosition().x() - 0.01f, array.GetPosition().y(), array.GetPosition().z());
		//if (state_l == GLFW_PRESS) array.SetPosition(array.GetPosition().x() + 0.01f, array.GetPosition().y(), array.GetPosition().z());
		//if (state_t == GLFW_PRESS) array.SetPosition(array.GetPosition().x(), array.GetPosition().y(), array.GetPosition().z() - 0.01f);
		//if (state_g == GLFW_PRESS) array.SetPosition(array.GetPosition().x(), array.GetPosition().y(), array.GetPosition().z() + 0.01f);

		window.Clear(lm::Color{ 50, 50, 50, 255 });
		array.SetColor(lm::Color{ 255, 100, 100, 255 });
		array.DrawArray();
		array2.DrawArray();
		//for (int i = 0; i < 100; i++)
		//{
		//	arrays[i].DrawArray();
		//}
		window.Display();

		//averateFrameTime += timer.GetTime(LM_MILISECONDS);

		//if(frameCounter >= 10)
		//{
		//	set_cursor(0, 0);
		//	std::cout << averateFrameTime / frameCounter << " ms " << 1000 / (averateFrameTime / frameCounter) << " FPS " << "      " << std::endl;
		//	averateFrameTime = 0;
		//	frameCounter = 0;
		//}
		//frameCounter++;
	}
	glfwTerminate();
	return 0;
}
