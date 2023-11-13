#include "Texture.h"

Texture::Texture(const char* image, GLenum textType, GLenum slot, GLenum format, GLenum pixelType)
{
	type = textType;

	int widht, height, numOfColorsCh;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(image, &widht, &height, &numOfColorsCh, 0);

	glGenTextures(1, &Id);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(textType, Id);

	glTexParameteri(textType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(textType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	glTexParameteri(textType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(textType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(textType, 0, GL_RGBA, widht, height, 0, format, pixelType, bytes);
	glGenerateMipmap(textType);

	stbi_image_free(bytes);
	glBindTexture(textType, 0);
}

void Texture::TexUnit(Shader& shader, const char* uniform, GLuint unit)
{
	GLuint textUni = glGetUniformLocation(shader.Id, uniform);
	shader.Activate();
	glUniform1i(textUni, 0);
}

void Texture::Bind()
{
	glBindTexture(type, Id);
}

void Texture::Unbind()
{
	glBindTexture(type, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &Id);
}