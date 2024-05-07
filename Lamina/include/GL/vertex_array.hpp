#pragma once

#include "../Lamina/include/Math/vertex.hpp"
#include "../Lamina/include/colors.hpp"
#include "../Lamina/include/GL/stb_image.h"
#include "../Lamina/include/GL/opengl.hpp"
#include "../Lamina/include/GL/texture.hpp"
#include "../Lamina/include/Math/matrix.hpp"
#include <iostream>

namespace lm
{
	class VertexArray
	{
	public:
		VertexArray() : mesh(nullptr), vertexShaderPath("Shaders/VertexArrayVertexShader.vert"), fragmentShaderPath("Shaders/VertexArrayFragmentShader.frag"), texture(nullptr),
			color({255, 255, 255, 255})
		{
			program = lm::GLRenderer::CompileShader(vertexShaderPath, fragmentShaderPath);
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			position.CreateVector({ 0, 0, 0 });
			scale.CreateVector({ 1, 1, 1 });
			rotation.CreateVector({ 0, 0, 0 });
			deltaPosition.CreateVector({ 0, 0, 0 });
			deltaRotation.CreateVector({ 0, 0, 0 });
		};
		VertexArray(GLObject* object) : mesh(object), vertexShaderPath("Shaders/VertexArrayVertexShader.vert"), fragmentShaderPath("Shaders/VertexArrayFragmentShader.frag"), 
			texture(nullptr), color({ 255, 255, 255, 255 })
		{
			program = lm::GLRenderer::CompileShader(vertexShaderPath, fragmentShaderPath);
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			position.CreateVector({ 0, 0, 0 });
			scale.CreateVector({ 1, 1, 1 });
			rotation.CreateVector({ 0, 0, 0 });
			deltaPosition.CreateVector({ 0, 0, 0 });
			deltaRotation.CreateVector({ 0, 0, 0 });
		};

		void DrawArray(/*lm::vec3f positionChange = lm::vec3f({ 0, 0, 0 }), lm::vec3f rotationChange = lm::vec3f({0, 0, 0}), lm::vec3f scaleChange = lm::vec3f({ 0, 0, 0 })*/);
		void SetScale(float x, float y, float z) { scale.CreateVector({ x, y, z }); }
		void SetRotation(float x, float y, float z);
		void SetPosition(float x, float y, float z);
		void SetTexture(Texture2D& _texture) { texture = &_texture; };
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

		lm::vec3f deltaPosition;
		lm::vec3f deltaRotation;

		lm::WavefrontObject object;
		lm::GLObject _object;
	};
}