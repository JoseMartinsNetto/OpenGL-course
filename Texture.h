#ifndef TEXTURE_CLASS
#define TEXTURE_CLASS

#include <glad/glad.h>
#include <stb/stb_image.h>
#include "Shader.h"

class Texture {
public:
	GLuint Id;
	GLenum type;

	Texture(const char* image, GLenum type, GLenum slot, GLenum format, GLenum pixelType);

	void TexUnit(Shader& shader, const char* uniform, GLuint unit);
	void Bind();
	void Unbind();
	void Delete();
};
#endif