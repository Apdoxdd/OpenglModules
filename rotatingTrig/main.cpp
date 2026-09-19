#include "shader.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

void updateView(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(800, 600, "ROTATE", NULL, NULL);
	if(!window)
	{
		std::cout<<"Failed to create a window"<<std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout<<"Failed to load OpenGL functions"<<std::endl;
		return -1;
	}
	glfwSetFramebufferSizeCallback(window, updateView);

	float rotVertices [] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		 0.0f,  0.5f, 0.0f, 0.0f, 0.1f, 0.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};
	unsigned int rotVAO, rotVBO;
	glGenVertexArrays(1, &rotVAO);
	glGenBuffers(1, &rotVBO);

	glBindVertexArray(rotVAO);
	glBindBuffer(GL_ARRAY_BUFFER, rotVBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(rotVertices), rotVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	shader rotShader {"../shaderSrc/vShader.vert", "../shaderSrc/fShader.frag"};

	while(!glfwWindowShouldClose(window))
	{
		processInput(window);


		glClearColor(0.4f, 0.2f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		float time = glfwGetTime();
		float rotVal = time;
		rotShader.use();
		rotShader.setFloat("rot", rotVal);
		rotShader.setFloat("cenX", (0.0f));
		rotShader.setFloat("cenY", (-0.5f/3.0f));
		glBindVertexArray(rotVAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void updateView(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}







