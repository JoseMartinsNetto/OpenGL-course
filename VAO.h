#ifndef VAO_CLASS
#define VAO_CLASS

#include <glad/glad.h>
#include "VBO.h"

class VAO {
public:
	GLuint Id;

	VAO();

	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numOfComponents, GLenum type, GLsizei stride, void* offset);
	void Bind();
	void Unbind();
	void Delete();
};

#endif