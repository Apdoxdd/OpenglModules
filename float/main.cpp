#include "shader.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <cmath>
#include <iostream>


void updateView(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(800, 600, "SMILEY WALL", NULL, NULL);
	if(!window)
	{
		std::cout<<"failed to create a window"<<std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout<<"failed to initialize GLAD";
		return -1;
	}

	glfwSetFramebufferSizeCallback(window, updateView);
	stbi_set_flip_vertically_on_load(true);

	unsigned int pooTex;
	glGenTextures(1, &pooTex);
	glBindTexture(GL_TEXTURE_2D, pooTex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int pooWidth, pooHeight, pooChannels;
	unsigned char *pooData = stbi_load("../assets/poo.png", &pooWidth, &pooHeight, &pooChannels, 0);
	if(pooData)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pooWidth, pooHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pooData);
	}
	else
	{
		std::cout<<"Failed to load poo pic\n";
	}
	stbi_image_free(pooData);

	while(!glfwWindowShouldClose(window))
	{
		processInput(window);


		glClearColor(0.0f, 0.2314f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

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
