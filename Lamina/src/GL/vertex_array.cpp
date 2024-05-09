#include "../Lamina/include/GL/vertex_array.hpp"

void lm::VertexArray::DrawArray()
{
	//lm::TranslationMatrix tranlationMatrix ({ position.x(), position.y(), position.z()});
	lm::ScaleMatrix scaleMatrix({ scale.x(), scale.y(), scale.z() });
	lm::RotationMatrix rotationMatrix_x(rotation.x(), LM_ROTATE_X_PLANE);
	lm::RotationMatrix rotationMatrix_y(rotation.y(), LM_ROTATE_Y_PLANE);
	lm::RotationMatrix rotationMatrix_z(rotation.z(), LM_ROTATE_Z_PLANE);
	
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, mesh->meshData.size() * sizeof(GLfloat), &mesh->meshData[0], GL_STATIC_DRAW);
	glUseProgram(program);

	lm::ColorF glColor = lm::GetFloatColor(color);
	glUniform4f(glGetUniformLocation(program, "color"), glColor.r, glColor.g, glColor.b, glColor.a);

	glUniform3f(glGetUniformLocation(program, "deltaTranslationVector"), position.x(), position.y(), position.z());
	glUniformMatrix4fv(glGetUniformLocation(program, "scaleMatrix"), 1, GL_FALSE, &scaleMatrix.matrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "rotationMatrix_x"), 1, GL_FALSE, &rotationMatrix_x.matrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "rotationMatrix_y"), 1, GL_FALSE, &rotationMatrix_y.matrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "rotationMatrix_z"), 1, GL_FALSE, &rotationMatrix_z.matrix[0][0]);
	glUniform1i(glGetUniformLocation(program, "textured"), GL_FALSE);
	if (texture != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->texture);
		glUniform1i(glGetUniformLocation(program, "textured"), GL_TRUE);
		glUniform1i(glGetUniformLocation(program, "inTexture"), 0);
	}

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(4*sizeof(GLfloat)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

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
	//rotation.x() = (float)((int)rotation.x() % 360);
	//rotation.y() = (float)((int)rotation.y() % 360);
	//rotation.z() = (float)((int)rotation.z() % 360);
	if (rotation.x() > 2 * PI) rotation.x() -= 2 * (float)PI;
	if (rotation.y() > 2 * PI) rotation.y() -= 2 * (float)PI;
	if (rotation.z() > 2 * PI) rotation.z() -= 2 * (float)PI;
	if (rotation.x() < 0) rotation.x() += 2 * (float)PI;
	if (rotation.y() < 0) rotation.y() += 2 * (float)PI;
	if (rotation.z() < 0) rotation.z() += 2 * (float)PI;
}