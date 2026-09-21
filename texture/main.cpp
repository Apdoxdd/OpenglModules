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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(800, 600, "Shader", NULL, NULL);

	if (!window)
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

	//start-create container texture
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	int width, height, nrChannels;
	unsigned char *data = stbi_load("../assets/container.jpg", &width, &height, &nrChannels, 0);

	if (data)
	{	
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
	{
		std::cout<<"Failed to load texture"<<std::endl;
	}
	stbi_image_free(data);
	///end-create container texture
	///////////////////////////////////////////////////////////////////////////////////////////
	
	//start-container wall data
	float contVert [] = {
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};
	unsigned int contIndec [] = {
		0, 1, 2,
		2, 3, 0
	};

	unsigned int contVAO, contVBO, contEBO;
	glGenVertexArrays(1, &contVAO);
	glGenBuffers(1, &contVBO);
	glGenBuffers(1, &contEBO);

	glBindVertexArray(contVAO);
	glBindBuffer(GL_ARRAY_BUFFER, contVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, contEBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(contVert), contVert, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(contIndec), contIndec, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	shader contShader {"../shaderSrc/contVShader.vert", "../shaderSrc/contFShader.frag"};
	while(!glfwWindowShouldClose(window))
	{
		//input
		processInput(window);

		glClearColor(0.3f, 0.4f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glBindVertexArray(contVAO);

		contShader.use();
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(contVAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
