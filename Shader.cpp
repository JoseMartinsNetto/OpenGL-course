#include "Shader.h"

std::string GetFileContents(const char* fileName)
{
	std::ifstream in(fileName, std::ios::binary);
	if(in) 
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return (contents);
	}throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	std::string vertexCode = GetFileContents(vertexFile);
	std::string fragmentCode = GetFileContents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	GLuint vertexShader = Compile(vertexSource, GL_VERTEX_SHADER);
	GLuint fragmentShader = Compile(fragmentSource, GL_FRAGMENT_SHADER);

	if (vertexShader == 0 || fragmentShader == 0)
	{
		Id = 0;
		return;
	}

	Id = glCreateProgram();
	glAttachShader(Id, vertexShader);
	glAttachShader(Id, fragmentShader);
	glLinkProgram(Id);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

GLuint Shader::Compile(const char* source, GLuint type)
{
	GLuint id = glCreateShader(type);
	glShaderSource(id, 1, &source, NULL);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		int lenght;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);
		char* message = (char*)alloca(lenght * sizeof(char));
		glGetShaderInfoLog(id, lenght, &lenght, message);

		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

void Shader::Activate()
{
	if (Id == 0) return;

	glUseProgram(Id);
}

void Shader::Delete()
{
	if (Id == 0) return;

	glDeleteProgram(Id);
}