#include "shader.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <pthread.h>
#include <stb_image.h>
#include <iostream>

void updateView(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(800, 600, "revise", NULL, NULL);
	if(!window)
	{
		std::cout<<"failed to create window"<<std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout<<"failed to initialize GLAD"<<std::endl;
		return -1;
	}

	glfwSetFramebufferSizeCallback(window, updateView);
	stbi_set_flip_vertically_on_load(true);

	unsigned int skyTex;
	glGenTextures(1, &skyTex);
	glBindTexture(GL_TEXTURE_2D, skyTex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int skyWidth, skyHeight, skyChannels;
	unsigned char *skyData = stbi_load("../assets/sky.jpg", &skyWidth, &skyHeight, &skyChannels, 0);
	if (skyData)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, skyWidth, skyHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, skyData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
	{
		std::cout<<"failed to load sky"<<std::endl;
	}

	unsigned int moonTex;
	glGenTextures(1, &moonTex);
	glBindTexture(GL_TEXTURE_2D, moonTex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int moonWidth, moonHeight, moonChannels;
	unsigned char *moonData = stbi_load("../assets/moon.png", &moonWidth, &moonHeight, &moonChannels, 0);

	if (moonData)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, moonWidth, moonHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, moonData);
		glGenerateMipmap(GL_TEXTURE_2D);
				glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	stbi_image_free(moonData);

	float skyVertices[] = {  		//no color
		0.06f, 0.06f, 0.0f, 	3.0f, 3.0f,
		0.06f, -0.06f, 0.0f, 	2.0f, 2.0f,
		-0.06f, -0.06f, 0.0f, 	0.0f, 0.0f,
		-0.06f, 0.06f, 0.0f,	0.0f, 3.0f	
	};
	
	unsigned int skyIndeces[] = {
		2, 3, 0,
		0, 1, 3
	};

	unsigned int skyVAO, skyVBO, skyEBO;
	glGenVertexArrays(1, &skyVAO);
	glGenBuffers(1, &skyVBO);
	glGenBuffers(1, &skyEBO);

	glBindVertexArray(skyVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyEBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(skyVertices), skyVertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyIndeces), skyIndeces, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	shader skyShader {"../shaderSrc/skyVShader.vert", "../shaderSrc/skyFShader.frag"};

	while(!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.510f, 0.510f, 0.510f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		skyShader.use();
		skyShader.setInt("texture1", 0);
		skyShader.setInt("texture2", 1);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, skyTex);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, moonTex);

		glBindVertexArray(skyVAO);
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
