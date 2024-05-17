#include "../Lamina/include/GL/vertex_array.hpp"

void lm::VertexArray::DrawArray()
{
	try {
		if (window == nullptr) std::runtime_error error("Window not assigned to vertex array\n");
		if (camera == nullptr) std::runtime_error error("Camera not assigned to vertex array\n");
	}
	catch (std::runtime_error& exception)
	{
		std::cout << exception.what() << std::endl;
		throw;
		return;
	}
	catch (...) { throw; return; }

	lm::ColorF glColor = lm::GetFloatColor(color);
	lm::mat4 translationMatrix = lm::CreateTranslationMatrix(position.x(), position.y(), position.z());
	lm::mat4 scaleMatrix = lm::CreateScaleMatrix(scale.x(), scale.y(), scale.z());
	lm::mat4 rotationMatrix = lm::CreateRotationMatrix(rotation.x(), rotation.y(), rotation.z());
	lm::mat4 perspectiveMatrix = lm::CreatePerspectiveProjectionMatrix(lm::constants::RadToDeg(70.f), (float)window->GetSize().x() / (float)window->GetSize().y(), 1, 10000);
	lm::mat4 view = camera->GetCameraLookAtMatrix();

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glActiveTexture(GL_TEXTURE0);
	glUseProgram(program);

	glUniform4f(glGetUniformLocation(program, "color"), glColor.r, glColor.g, glColor.b, glColor.a);
	glUniformMatrix4fv(glGetUniformLocation(program, "translationMatrix"), 1, GL_TRUE, &translationMatrix.data[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "scaleMatrix"), 1, GL_TRUE, &scaleMatrix.data[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "rotationMatrix"), 1, GL_TRUE, &rotationMatrix.data[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "viewMatrix"), 1, GL_TRUE, &view.data[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "projectionMatrix"), 1, GL_TRUE, &perspectiveMatrix.data[0][0]);
	if (texture != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->texture);
		glUniform1i(glGetUniformLocation(program, "textured"), GL_TRUE);
		glUniform1i(glGetUniformLocation(program, "inTexture"), 0);
	}
	else glUniform1i(glGetUniformLocation(program, "textured"), GL_FALSE);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(4 * sizeof(GLfloat)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)mesh->meshData.size() / 9);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void lm::VertexArray::SetPosition(float x, float y, float z)
{
	position.CreateVector({ x, y, z });
}

void lm::VertexArray::SetRotation(float x, float y, float z)
{
	rotation.CreateVector({ x, y, z });
	if (rotation.x() > (float)TAU) rotation.x() -= (float)TAU;
	if (rotation.y() > (float)TAU) rotation.y() -= (float)TAU;
	if (rotation.z() > (float)TAU) rotation.z() -= (float)TAU;
	if (rotation.x() < 0) rotation.x() += (float)TAU;
	if (rotation.y() < 0) rotation.y() += (float)TAU;
	if (rotation.z() < 0) rotation.z() += (float)TAU;
}