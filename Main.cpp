#include<iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"
#include "Texture.h"
#include "Camera.h"

#define WIDTH 800
#define HEIGHT 800

int main()
{
	// Initialize GLFW (OpenGl window manager)
	glfwInit();

	// Set the version of OpenGl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Telling to GLFW we were using the core profile (Modern Functions)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat pyramidVertices[] =
	{ //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
		-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
		-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
		 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
		 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side

		-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
		-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
		 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,     -0.8f, 0.5f,  0.0f, // Left Side

		-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
		 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
		 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f, -0.8f, // Non-facing side

		 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
		 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
		 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.8f, 0.5f,  0.0f, // Right side

		 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
		-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
		 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f,  0.8f  // Facing side
	};

	GLuint pyramidIndices[] =
	{
		0, 1, 2,	// Bottom side
		0, 2, 3,	// Bottom side
		4, 6, 5,	// Left side
		7, 9, 8,	// Non-facing side
		10, 12, 11, // Right side
		13, 15, 14  // Facing side
	};

	GLfloat lightVertices[] = 
	{
		-0.1f, -0.1f,  0.1f,
		-0.1f, -0.1f, -0.1f,
		 0.1f, -0.1f, -0.1f,
		 0.1f, -0.1f,  0.1f,
		-0.1f,  0.1f,  0.1f,
		-0.1f,  0.1f, -0.1f,
		 0.1f,  0.1f, -0.1f,
		 0.1f,  0.1f,  0.1f
	};

	GLuint lightIndices[] =
	{
		0, 1, 2,
		0, 2, 3,
		0, 4, 7,
		0, 7, 3,
		3, 7, 6,
		3, 6, 2,
		2, 6, 5,
		2, 5, 1,
		1, 5, 4,
		1, 4, 0,
		4, 5, 6,
		4, 6, 7
	};

	// Creating a GLFW window
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "YouTubeOpenGL", NULL,NULL);

	// Checking if window is created successfully
	if (window == NULL) 
	{
		std::cout << "Failed to create a GLFW Window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Making the context of GLFW window
	glfwMakeContextCurrent(window);

	// Loading glad to load modern OpenGL features
	gladLoadGL();

	// Set the viewoport for OpenGl
	glViewport(0, 0, WIDTH, HEIGHT);

	// Creating a shader program
	Shader defaultShader = Shader("default.vert", "default.frag");

	if (defaultShader.Id == 0)
	{
		glfwTerminate();
		return -1;
	}

	// Creating and Binding the buffer objects
	VAO pyramidVAO;
	pyramidVAO.Bind();

	VBO pyramidVBO = VBO(pyramidVertices, sizeof(pyramidVertices));
	EBO pyramidEBO = EBO(pyramidIndices, sizeof(pyramidIndices));

	pyramidVAO.LinkAttrib(pyramidVBO, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	pyramidVAO.LinkAttrib(pyramidVBO, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	pyramidVAO.LinkAttrib(pyramidVBO, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	pyramidVAO.LinkAttrib(pyramidVBO, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));

	pyramidVAO.Unbind();
	pyramidVBO.Unbind();
	pyramidEBO.Unbind();

	Shader lightShader = Shader("light.vert", "light.frag");

	if (lightShader.Id == 0)
	{
		glfwTerminate();
		return -1;
	}

	VAO lightVAO;
	lightVAO.Bind();

	VBO lightVBO = VBO(lightVertices, sizeof(lightVertices));
	EBO lightEBO = EBO(lightIndices, sizeof(lightIndices));

	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	glm::vec3 lightPos = glm::vec3(1.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.Id, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.Id, "lightColor"), lightColor.r, lightColor.g, lightColor.b, lightColor.a);

	defaultShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(defaultShader.Id, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	glUniform4f(glGetUniformLocation(defaultShader.Id, "lightColor"), lightColor.r, lightColor.g, lightColor.b, lightColor.a);
	glUniform3f(glGetUniformLocation(defaultShader.Id, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	// Texture loading
	Texture brickTexture("sonic.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	brickTexture.TexUnit(defaultShader, "tex0", 0);

	// Initialize Camera
	Camera camera = Camera(WIDTH, HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));

	glfwSwapInterval(1);
	glEnable(GL_DEPTH_TEST);

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		// Rendering a background color
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Inputs(window);
		camera.UpdateMatrix(45.0f, 0.1f, 100.0f);

		defaultShader.Activate();
		glUniform3f(glGetUniformLocation(defaultShader.Id, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(defaultShader, "camMatrix");
		brickTexture.Bind();
		pyramidVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(pyramidIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		lightShader.Activate();
		camera.Matrix(lightShader, "camMatrix");
		lightVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Terminating the program
	pyramidVAO.Delete();
	pyramidVBO.Delete();
	pyramidEBO.Delete();

	lightVAO.Delete();
	lightVBO.Delete();
	lightEBO.Delete();

	brickTexture.Delete();

	defaultShader.Delete();
	lightShader.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}