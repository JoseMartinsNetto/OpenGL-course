#ifndef VBO_CLASS
#define VBO_CLASS

#include<glad/glad.h>

class VBO {
public:
	GLuint Id;

	VBO(GLfloat* vertices, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();
};

#endif
