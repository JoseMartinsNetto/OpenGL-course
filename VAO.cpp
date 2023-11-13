#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &Id);
}

void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numOfComponents, GLenum type, GLsizei stride, void* offset)
{
	VBO.Bind();

	glVertexAttribPointer(layout, numOfComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);

	VBO.Unbind();
}

void VAO::Bind()
{
	glBindVertexArray(Id);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &Id);
}
