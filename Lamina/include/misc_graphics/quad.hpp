#ifndef GL_QUAD
#define GL_QUAD

#include "../Lamina/include/GL/opengl.hpp"
#include "../Lamina/include/GL/texture.hpp"
#include "../Lamina/include/Math/vector.hpp"
#include "../Lamina/include/Math/constants.hpp"
#include "../Lamina/include/GL/colors.hpp"
#include "../Lamina/include/GL/window.hpp"
#include <vector>

namespace lm::quad
{
	inline std::array<GLfloat, 36> defaultQuad = {
//		x		y		z		w		r		t
		1.0,	1.0,	0.0,	1.0,	1.0,	0.0,
		-1.0,	-1.0,	0.0,	1.0,	0.0,	1.0,
		-1.0,	1.0,	0.0,	1.0,	0.0,	0.0,
		1.0,	1.0,	0.0,	1.0,	1.0,	0.0,
		1.0,	-1.0,	0.0,	1.0,	1.0,	1.0,
		-1.0,	-1.0,	0.0,	1.0,	0.0,	1.0
	};

	class GL2DProgram
	{
	public:
		explicit GL2DProgram(std::string vertShaderPath = "Shaders/quad_vert_shader.vert", std::string fragShaderPath = "Shaders/quad_frag_shader.frag")
		{
			program = lm::GLRenderer::CompileShader(vertShaderPath, fragShaderPath);
		};
		GLuint program;
	};

	class TexturedQuad
	{
	public:
		TexturedQuad() : position({ 0.f, 0.f }), origin({ 0.f, 0.f }), rotation(0.f), scale({ 1.f, 1.f }), window(nullptr), program(nullptr), color(lm::Color(255, 255, 255, 255)), quad(&defaultQuad) {
			if (!glfwInit()) throw;
			this->texture = lm::Texture2D();
			glGenBuffers(1, &VBO);
			glGenVertexArrays(1, &VAO);
		}
		TexturedQuad(std::string texturePath, GL2DProgram& _program, lm::Window& _window) : position({ 0.f, 0.f }), origin({ 0.f, 0.f }), scale({ 1.f, 1.f }), rotation(0.f), window(&_window) {
			if (!glfwInit()) throw;
			this->quad = &defaultQuad;
			this->texture = lm::Texture2D(texturePath);
			program = &_program;
			color = lm::Color( 255, 255, 255, 255 );
			try { if (InitiateGL() > 0) std::exception exception("Failed to iniate OpenGL for textured quad\n"); }
			catch (std::exception& exception) { std::cout << exception.what(); glfwTerminate(); throw; }
			catch (...) { glfwTerminate(); throw; }
		}

		void SetTexture(std::string path) { texture = lm::Texture2D(path); }

		void SetRotation(float angle) { rotation = lm::constants::DegToRad(angle); }
		void SetPosition(float x, float y) { position = lm::vec2f({ x, y }); }
		void SetOrigin(float x, float y) { origin = lm::vec2f({ x, y }); }
		void SetScale(float x, float y) { scale = lm::vec2f({ x, y }); }
		void SetColor(lm::Color _color) { color = _color; }

		float& GetRotation() { return rotation; }
		lm::vec2f& GetPosition() { return position; }
		lm::vec2f& GetOrigin() { return origin; }
		lm::vec2f& GetScale() { return scale; }
		lm::Color& GetColor() { return color; }

		void DrawQuad();

	protected:
		lm::Texture2D texture;
		std::array<GLfloat, 36>* quad;

		lm::vec2f position;
		lm::vec2f scale;
		lm::vec2f origin;
		float rotation;
		lm::Color color;

		lm::Window* window;

	private:
		GL2DProgram* program;
		GLuint VBO;
		GLuint VAO;
		int InitiateGL();
	};
}
#endif // !GL_QUAD