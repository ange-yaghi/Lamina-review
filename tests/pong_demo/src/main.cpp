#include <../Lamina/include/misc_graphics/quad.hpp>
#include <../Lamina/include/Math/timer.hpp>
#include <time.h>

class Ball
{
public:
	Ball(lm::quad::GL2DProgram& program, lm::Window& _window, lm::quad::TexturedQuad& _leftPlayer, lm::quad::TexturedQuad& _rightPlayer, float _velocity)
	{
		if (!glfwInit()) return;
		ballObject = lm::quad::TexturedQuad("Textures/pong_demo_textures/white_circle.png", program, _window);
		ballObject.SetScale(10, 10);
		ballObject.SetPosition((float)_window.GetSize().x() / 2, (float)_window.GetSize().y() / 2);
		ballObject.SetColor(lm::Color({ 255, 0, 0, 255 }));
		leftPlayer = &_leftPlayer;
		rightPlayer = &_rightPlayer;
		velocity = _velocity;
		window = &_window;
		direction = lm::vec2f({ 1, 0 });
		time.Restart();
	}

	float GetDeltaTime()
	{
		float deltaTime = time.GetTime(LM_SECONDS);
		time.Restart();
		return deltaTime;
	}

	void MoveBall()
	{
		ballObject.SetPosition(ballObject.GetPosition().x() + (velocity * direction.x()), ballObject.GetPosition().y() + (velocity * direction.y()));

		if (ballObject.GetPosition().y() <= rightPlayer->GetPosition().y() + rightPlayer->GetScale().y() && ballObject.GetPosition().y() >= rightPlayer->GetPosition().y() - rightPlayer->GetScale().y())
		{
			if (ballObject.GetPosition().x() + ballObject.GetScale().x() >= rightPlayer->GetPosition().x()) 
			{
				direction.x() = -direction.x();
				int yDirRandomness = rand() % 100;
				bool positive = rand();
				if (!positive) yDirRandomness = -yDirRandomness;
				direction.y() = (-direction.y() + (float)yDirRandomness / 100);
				if (direction.y() >= 1) direction.y() = 1;
				if (direction.y() <= -1) direction.y() = -1;
			}
		}
		if (ballObject.GetPosition().y() <= leftPlayer->GetPosition().y() + leftPlayer->GetScale().y() && ballObject.GetPosition().y() >= leftPlayer->GetPosition().y() - leftPlayer->GetScale().y())
		{
			if (ballObject.GetPosition().x() - ballObject.GetScale().x() <= leftPlayer->GetPosition().x())
			{
				direction.x() = -direction.x();
				int yDirRandomness = rand() % 100;
				bool positive = rand();
				if (!positive) yDirRandomness = -yDirRandomness;
				direction.y() = (-direction.y() + (float)yDirRandomness / 100);
				if (direction.y() >= 1) direction.y() = 1;
				if (direction.y() <= -1) direction.y() = -1;
			}
		}

		if (ballObject.GetPosition().y() <= 0) direction.y() = -direction.y();
		if (ballObject.GetPosition().y() >= window->GetSize().y()) direction.y() = -direction.y();
	}

	lm::quad::TexturedQuad ballObject;
	lm::Timer time;
	lm::vec2f direction;
	lm::Window* window;
	float velocity;

	lm::quad::TexturedQuad* leftPlayer;
	lm::quad::TexturedQuad* rightPlayer;
};

int WinMain()
{
	glfwInit();
	srand((unsigned int)time(0));
	lm::Window window(lm::vec2i({ 800, 400 }), "Pong Demo", LM_WINDOW_NON_RESIZABLE, 8);
	lm::quad::GL2DProgram program;

	lm::quad::TexturedQuad leftPlayer("Textures/pong_demo_textures/white_rect.png", program, window);
	lm::quad::TexturedQuad rightPlayer("Textures/pong_demo_textures/white_rect.png", program, window);

	lm::quad::TexturedQuad divider("Textures/pong_demo_textures/white_rect.png", program, window);
	Ball ball(program, window, leftPlayer, rightPlayer, 2);

	window.MakeContextCurrent();
	leftPlayer.SetScale((float)window.GetSize().x() / 50, (float)window.GetSize().y() / 4);
	leftPlayer.SetPosition(0, (float)window.GetSize().y() / 2);
	rightPlayer.SetScale((float)window.GetSize().x() / 50, (float)window.GetSize().y() / 4);
	rightPlayer.SetPosition((float)window.GetSize().x(), (float)window.GetSize().y() / 2);
	divider.SetScale((float)window.GetSize().x() / 100, (float)window.GetSize().y());
	divider.SetPosition((float)window.GetSize().x() / 2, (float)window.GetSize().y() / 2);

	while (window.IsOpen())
	{
		glfwPollEvents();

		if (glfwGetKey(window.window, GLFW_KEY_W) == GLFW_PRESS) leftPlayer.SetPosition(leftPlayer.GetPosition().x(), leftPlayer.GetPosition().y() - 3);
		if (glfwGetKey(window.window, GLFW_KEY_S) == GLFW_PRESS) leftPlayer.SetPosition(leftPlayer.GetPosition().x(), leftPlayer.GetPosition().y() + 3);
		if (glfwGetKey(window.window, GLFW_KEY_UP) == GLFW_PRESS) rightPlayer.SetPosition(rightPlayer.GetPosition().x(), rightPlayer.GetPosition().y() - 3);
		if (glfwGetKey(window.window, GLFW_KEY_DOWN) == GLFW_PRESS) rightPlayer.SetPosition(rightPlayer.GetPosition().x(), rightPlayer.GetPosition().y() + 3);
		if (glfwGetKey(window.window, GLFW_KEY_R) == GLFW_PRESS) ball = Ball(program, window, leftPlayer, rightPlayer, 2);

		if (leftPlayer.GetPosition().y() - leftPlayer.GetScale().y() / 2 <= 0) leftPlayer.SetPosition(leftPlayer.GetPosition().x(), 0 + leftPlayer.GetScale().y() / 2);
		if (leftPlayer.GetPosition().y() + leftPlayer.GetScale().y() / 2 >= (float)window.GetSize().y()) leftPlayer.SetPosition(leftPlayer.GetPosition().x(), (float)window.GetSize().y() - leftPlayer.GetScale().y() / 2);

		if (rightPlayer.GetPosition().y() - rightPlayer.GetScale().y() / 2 <= 0) rightPlayer.SetPosition(rightPlayer.GetPosition().x(), 0 + rightPlayer.GetScale().y() / 2);
		if (rightPlayer.GetPosition().y() + rightPlayer.GetScale().y() / 2 >= (float)window.GetSize().y()) rightPlayer.SetPosition(rightPlayer.GetPosition().x(), (float)window.GetSize().y() - rightPlayer.GetScale().y() / 2);

		ball.MoveBall();

		window.Clear(lm::Color({ 0, 0, 0, 255 }));
		leftPlayer.DrawQuad();
		rightPlayer.DrawQuad();
		divider.DrawQuad();
		ball.ballObject.DrawQuad();
		window.Display();
	}
}