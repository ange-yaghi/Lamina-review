#include <../Lamina/include/GL/colors.hpp>
#include <../Lamina/include/GL/opengl.hpp>
#include <../Lamina/include/Math/matrix.hpp>
#include <../Lamina/include/GL/window.hpp>
#include <../Lamina/include/GL/vertex_array.hpp>
#include <../Lamina/include/Math/constants.hpp>
#include <../Lamina/include/Math/timer.hpp>
#include <../Lamina/include/misc_graphics/quad.hpp>
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

void Test1(lm::VertexArray& array)
{
	array.SetPosition(0, 0, 0);
	array.DrawArray();
	array.SetPosition(0, 0, 2);
	array.DrawArray();
	array.SetPosition(0, 0, -2);
	array.DrawArray();
	array.SetPosition(0, 2, 0);
	array.DrawArray();
	array.SetPosition(0, -2, 0);
	array.DrawArray();
	array.SetPosition(2, 0, 0);
	array.DrawArray();
	array.SetPosition(-2, 0, 0);
	array.DrawArray();

	array.SetPosition(0, 2, 2);
	array.DrawArray();
	array.SetPosition(0, 2, -2);
	array.DrawArray();
	array.SetPosition(0, -2, 2);
	array.DrawArray();
	array.SetPosition(0, -2, -2);
	array.DrawArray();
	array.SetPosition(2, 2, 0);
	array.DrawArray();
	array.SetPosition(2, -2, 0);
	array.DrawArray();
	array.SetPosition(-2, 2, 0);
	array.DrawArray();
	array.SetPosition(-2, -2, 0);
	array.DrawArray();
	array.SetPosition(2, 0, 2);
	array.DrawArray();
	array.SetPosition(2, 0, -2);
	array.DrawArray();
	array.SetPosition(-2, 0, 2);
	array.DrawArray();
	array.SetPosition(-2, 0, -2);
	array.DrawArray();

	array.SetPosition(2, 2, 2);
	array.DrawArray();
	array.SetPosition(2, 2, -2);
	array.DrawArray();
	array.SetPosition(2, -2, 2);
	array.DrawArray();
	array.SetPosition(-2, 2, 2);
	array.DrawArray();
	array.SetPosition(-2, -2, 2);
	array.DrawArray();
	array.SetPosition(2, -2, -2);
	array.DrawArray();
	array.SetPosition(-2, 2, -2);
	array.DrawArray();
	array.SetPosition(-2, -2, -2);
	array.DrawArray();

	array.SetPosition(4, 4, 4);
	array.DrawArray();
	array.SetPosition(4, 4, -4);
	array.DrawArray();
	array.SetPosition(4, -4, 4);
	array.DrawArray();
	array.SetPosition(-4, 4, 4);
	array.DrawArray();
	array.SetPosition(-4, -4, 4);
	array.DrawArray();
	array.SetPosition(4, -4, -4);
	array.DrawArray();
	array.SetPosition(-4, 4, -4);
	array.DrawArray();
	array.SetPosition(-4, -4, -4);
	array.DrawArray();
}

int main()
{
	if (!glfwInit()) return -1;
	lm::Window window(lm::vec2i({800, 800}), "Lamina draw demo", LM_WINDOW_DEFAULT, 8);
	window.MakeContextCurrent();
	int frameCounter = 0;
	glfwSwapInterval(1);
	lm::Timer timer;

	lm::WavefrontObject object("Objects/sphere_test_obj.obj");
	lm::Texture2D texture("Textures/test_texture.png");
	lm::GLObject _object(object);
	std::cout << "Loading time: " << timer.GetTime(LM_SECONDS) << "s" << std::endl;
	timer.Restart();

	lm::PivotCamera cam(lm::vec3f({ 0, 0, 0 }), lm::vec3f({ 0, 0, 0 }), 10, window);
	cam.SetRadiusClamp(lm::vec2f({ 2, 50 }));
	lm::VertexArray array(&_object, window, cam);
	lm::VertexArray array2(&_object, window, cam);
	//lm::VertexArray arrays[100];
	array.SetScale(1, 1, 1);
	array.SetRotation(lm::constants::DegToRad(0.f), lm::constants::DegToRad(0.f), lm::constants::DegToRad(0.f));
	array.SetTexture(texture);
	lm::vec3f rotation = array.GetRotation();

	lm::quad::GL2DProgram program;
	lm::quad::TexturedQuad quad("Textures/RGBA_test_texture.png", program, window);

	float averateFrameTime = 0;
	float lowestFrameTime = INT_MAX;
	float highestFrameTime = 0;
	std::cout << "Initialisation time: " << timer.GetTime(LM_MILISECONDS) << "ms" << std::endl;
	timer.Restart();
	while (window.IsOpen())
	{
		timer.Restart();
		glfwPollEvents();

		window.Clear(lm::Color{ 50, 50, 50, 255 });
		lm::vec2i winSize = window.GetSize();
		quad.SetPosition(0, 0);
		array.SetColor(lm::Color{ 255, 255, 255, 255 });
		quad.SetScale((float)winSize.x() / 4, (float)winSize.x() / 4);
		quad.SetOrigin(-quad.GetScale().x() / 2, -quad.GetScale().y() / 2);
		Test1(array);
		quad.DrawQuad();
		//array.DrawArray();
		window.Display();
		
		averateFrameTime += timer.GetTime(LM_MILISECONDS);

		if(frameCounter >= 10)
		{
			if (glfwGetKey(window.window, GLFW_KEY_R) == GLFW_PRESS) {
				highestFrameTime = 0; lowestFrameTime = INT_MAX;
			}
			set_cursor(0, 3);
			std::cout << "Frame rate: " << 1000 / (averateFrameTime / frameCounter) << " FPS      ";
			set_cursor(0, 4);
			std::cout << "Average frame time: " << averateFrameTime / frameCounter << "ms     ";
			if (averateFrameTime > highestFrameTime)
			{
				set_cursor(0, 5);
				highestFrameTime = averateFrameTime;
				std::cout << "Highest frame time: " << highestFrameTime / frameCounter << "       ";
			}
			if (averateFrameTime < lowestFrameTime)
			{
				set_cursor(0, 6);
				lowestFrameTime = averateFrameTime;
				std::cout << "Lowest frame time: " << lowestFrameTime / frameCounter << "       ";
			}
			averateFrameTime = 0;
			frameCounter = 0;
		}
		frameCounter++;
	}
	glfwTerminate();
	return 0;
}