#include "../Lamina/include/misc_graphics/quad.hpp"

int lm::quad::TexturedQuad::InitiateGL()
{
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	if (sizeof(this->quad) == 0) return -1;
	glBufferData(GL_ARRAY_BUFFER, this->quad->size() * sizeof(GLfloat), quad->data(), GL_STATIC_DRAW);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	return 1;
}

void lm::quad::TexturedQuad::DrawQuad()
{
	try
	{
		if (window == nullptr) std::exception exception("Window is nullptr\n");
		if (program == nullptr) std::exception exception("Program is nullptr\n");
	}
	catch (std::exception& exception)
	{
		std::cout << exception.what();
		throw;
		return;
	}
	catch (...) { throw; return; }

	lm::vec2i windowSize = window->GetSize();
	lm::mat4 translationMatrix = lm::CreateTranslationMatrix((((position.x() - origin.x()) / windowSize.x()) * 2.f) - 1.f, (((-position.y() + origin.y()) / windowSize.y()) * 2.f) + 1.f, 0.f);
	lm::mat4 rotationMatrix = lm::CreateRotationMatrix(0.f, 0.f, rotation);
	lm::mat4 scaleMatrix = lm::CreateScaleMatrix(scale.x() / windowSize.x(), scale.y() / windowSize.y(), 1.f);

	window->MakeContextCurrent();
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.texture);
	glClear(GL_DEPTH_BUFFER_BIT);
	//set program and pass uniform data to it
	if(program != nullptr) 
	{
		glUseProgram(program->program);
		glUniformMatrix4fv(glGetUniformLocation(program->program, "translationMatrix"), 1, GL_TRUE, &translationMatrix.data[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(program->program, "rotationMatrix"), 1, GL_TRUE, &rotationMatrix.data[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(program->program, "scaleMatrix"), 1, GL_TRUE, &scaleMatrix.data[0][0]);
		lm::ColorF colorF = lm::GetFloatColor(color);
		glUniform4f(glGetUniformLocation(program->program, "colorToFrag"), colorF.r, colorF.g, colorF.b, colorF.a);
		glUniform1i(glGetUniformLocation(program->program, "textureData"), 0);
	}

	//generate attrib pointer arrays
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(4 * sizeof(GLfloat)));

	//draw triangles to screen
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}