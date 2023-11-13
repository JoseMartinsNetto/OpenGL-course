#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string GetFileContents(const char* fileName);

class Shader {
public:
	GLuint Id;
	Shader(const char* vertexFile, const char* fragmentFile);

	void Activate();
	void Delete();


private:
	GLuint Compile(const char* source, GLuint type);
};

#endif // !SHADER_CLASS_H
