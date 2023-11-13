#ifndef EBO_CLASS
#define EBO_CLASS

#include<glad/glad.h>

class EBO {
public:
	GLuint Id;

	EBO(GLuint* indices, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();
};

#endif
