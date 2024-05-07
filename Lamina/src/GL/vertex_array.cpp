#include "../Lamina/include/GL/vertex_array.hpp"

void lm::VertexArray::DrawArray()
{
	lm::TranslationMatrix tranlationMatrix ({ deltaPosition.x(), deltaPosition.y(), deltaPosition.z()});
	lm::ScaleMatrix scaleMatrix({ scale.x(), scale.y(), scale.z() });
	lm::RotationMatrix rotationMatrix_x(deltaRotation.x(), LM_ROTATE_X_PLANE);
	lm::RotationMatrix rotationMatrix_y(deltaRotation.y(), LM_ROTATE_Y_PLANE);
	lm::RotationMatrix rotationMatrix_z(deltaRotation.z(), LM_ROTATE_Z_PLANE);

	deltaPosition.CreateVector({ 0, 0, 0 });
	deltaRotation.CreateVector({ 0, 0, 0 });
	
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, mesh->meshData.size() * sizeof(GLfloat), &mesh->meshData[0], GL_STATIC_DRAW);
	glUseProgram(program);

	lm::ColorF glColor = lm::GetFloatColor(color);
	glUniform4f(glGetUniformLocation(program, "color"), color.r, color.g, color.b, color.a);

	glUniformMatrix4fv(glGetUniformLocation(program, "translationMatrix"), 1, GL_FALSE, &tranlationMatrix.matrix[0][0]);
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
		glUniform1i(glGetUniformLocation(program, "inTexture"), GL_TEXTURE0);
	}

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(4*sizeof(GLfloat)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glDrawArrays(GL_TRIANGLES, 0, mesh->meshData.size() / 9);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void lm::VertexArray::SetPosition(float x, float y, float z)
{
	position.CreateVector({ position.x() + x, position.y() + y, position.z() + z });
	deltaPosition.CreateVector({ x, y, z });
}

void lm::VertexArray::SetRotation(float x, float y, float z)
{
	rotation.CreateVector({ position.x() + x, position.y() + y, position.z() + z });
	deltaRotation.CreateVector({ x, y, z });
}