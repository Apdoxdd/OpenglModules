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

	unsigned int wallTex;
	glGenTextures(1, &wallTex);
	glBindTexture(GL_TEXTURE_2D, wallTex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



	int wallWidth, wallHeight, nrChannels;
	unsigned char *wallData = stbi_load("../assets/wall.jpg", &wallWidth, &wallHeight, &nrChannels, 0);
	if (wallData)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, wallWidth, wallHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, wallData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
	{
		std::cout<<"Failed to load container image"<<std::endl;
	}
	stbi_image_free(wallData);

	
	unsigned int smTex;
	glGenTextures(1, &smTex);
	glBindTexture(GL_TEXTURE_2D, smTex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



	int smWidth, smHeight, nrChannels2;
	unsigned char *smData = stbi_load("../assets/awesomeface.png", &smWidth, &smHeight, &nrChannels2, 0);
	if(smData)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, smWidth, smHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, smData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout<<"Failed to load smiley image"<<std::endl;
	}
	stbi_image_free(smData);



	float wallVertices [] = {
		
     		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   3.0f, 3.0f,   
     		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   3.0f, 0.0f,   
    		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   
    		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    
	};

	unsigned int wallIndeces[] = {
		2, 3, 0,
		0, 1, 2
	};
	unsigned int wallVAO, wallVBO, wallEBO;
	glGenVertexArrays(1, &wallVAO);
	glGenBuffers(1, &wallVBO);
	glGenBuffers(1, &wallEBO);

	glBindVertexArray(wallVAO);
	glBindBuffer(GL_ARRAY_BUFFER, wallVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, wallEBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(wallVertices), wallVertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(wallIndeces), wallIndeces, GL_STATIC_DRAW);

	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	

	while(!glfwWindowShouldClose(window))
	{
		//input
		processInput(window);

		glClearColor(0.3f, 0.4f, 0.4f, 1.0f);
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
