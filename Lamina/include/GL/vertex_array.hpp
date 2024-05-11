#pragma once

#include "../Lamina/include/GL/colors.hpp"
#include "../Lamina/include/GL/opengl.hpp"
#include "../Lamina/include/GL/texture.hpp"
#include "../Lamina/include/Math/constants.hpp"
#include "../Lamina/include/Math/matrix.hpp"
#include "../Lamina/include/Math/vertex.hpp"
#include "../Lamina/include/GL/window.hpp"
#include <iostream>

namespace lm
{
	class VertexArray
	{
	public:
		VertexArray() : window(nullptr), mesh(nullptr), vertexShaderPath("Shaders/VertexArrayVertexShader.vert"), fragmentShaderPath("Shaders/VertexArrayFragmentShader.frag"), texture(nullptr),
			color({255, 255, 255, 255})
		{
			program = lm::GLRenderer::CompileShader(vertexShaderPath, fragmentShaderPath);
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			position.CreateVector({ 0, 0, 0 });
			scale.CreateVector({ 1, 1, 1 });
			rotation.CreateVector({ 0, 0, 0 });
		};
		VertexArray(GLObject* object, lm::Window& _window) : window(&_window), mesh(object), vertexShaderPath("Shaders/VertexArrayVertexShader.vert"), fragmentShaderPath("Shaders/VertexArrayFragmentShader.frag"), 
			texture(nullptr), color({ 255, 255, 255, 255 })
		{
			program = lm::GLRenderer::CompileShader(vertexShaderPath, fragmentShaderPath);
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			position.CreateVector({ 0, 0, 0 });
			scale.CreateVector({ 1, 1, 1 });
			rotation.CreateVector({ 0, 0, 0 });
		};

		void initaiateArray(GLObject* object, lm::Window& _window)
		{
			window = &_window;
			mesh = object;
			vertexShaderPath = "Shaders/VertexArrayVertexShader.vert";
			fragmentShaderPath = "Shaders/VertexArrayFragmentShader.frag";
			texture = nullptr;
			color = { 255, 255, 255, 255 };
			program = lm::GLRenderer::CompileShader(vertexShaderPath, fragmentShaderPath);
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			position.CreateVector({ 0, 0, 0 });
			scale.CreateVector({ 1, 1, 1 });
			rotation.CreateVector({ 0, 0, 0 });
		}

		void DrawArray(/*lm::vec3f positionChange = lm::vec3f({ 0, 0, 0 }), lm::vec3f rotationChange = lm::vec3f({0, 0, 0}), lm::vec3f scaleChange = lm::vec3f({ 0, 0, 0 })*/);
		void SetScale(float x, float y, float z) { scale.CreateVector({ std::clamp(x, 0.f, (float) INT_MAX), std::clamp(y, 0.f, (float)INT_MAX), std::clamp(z, 0.f, (float)INT_MAX) }); }
		void SetRotation(float x, float y, float z);
		void SetPosition(float x, float y, float z);
		void SetTexture(Texture2D& _texture) { texture = &_texture; };
		void SetColor(lm::Color _color) { color = _color; }

		lm::vec3f GetRotation() { return rotation; }
		lm::vec3f GetPosition() { return position; }
		lm::vec3f GetScale() { return scale; }
 	private:
		GLObject* mesh;
		GLuint program;
		GLuint VAO; //vertex array object
		GLuint VBO; //vertex buffer object

		std::string vertexShaderPath;
		std::string fragmentShaderPath;

		lm::Color color;
		lm::Texture2D* texture;

		lm::vec3f position;
		lm::vec3f scale;
		lm::vec3f rotation;

		lm::WavefrontObject object;
		lm::GLObject _object;

		lm::Window* window;
	};
}