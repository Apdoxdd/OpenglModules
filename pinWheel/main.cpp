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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(800, 600, "PIN WHEEL", NULL, NULL);
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

	float whVertices[] = {
		0.0f,  0.0f, 0.0f, 0.690f, 0.145f, 0.467f, 0.0f,
		0.0f, -0.4f, 0.0f, 0.341f, 0.157f, 0.227f, 0.0f,
		0.3f,  -0.4f, 0.0f, 0.102f, 0.286f, 0.286f, 0.0f,

		0.0f, -0.4f, 0.0f, 0.341f, 0.157f, 0.227f, 1.0f,
		0.3f, -0.4f, 0.0f, 0.102f, 0.286f, 0.286f, 1.0f,
		
		0.0f, -0.4f, 0.0f, 0.341f, 0.157f, 0.227f, 2.0f,
		0.3f, -0.4f, 0.0f, 0.102f, 0.286f, 0.286f, 2.0f,


		0.0f, -0.4f, 0.0f, 0.341f, 0.157f, 0.227f, 3.0f,
		0.3f, -0.4f, 0.0f, 0.102f, 0.286f, 0.286f, 3.0f,

		0.0f, -0.4f, 0.0f, 0.341f, 0.157f, 0.227f, 4.0f,
		0.3f, -0.4f, 0.0f, 0.102f, 0.286f, 0.286f, 4.0f,
	}; 

	unsigned int whIndeces[] = {
		0, 1, 2,
		0, 3, 4,
		0, 5, 6,
		0, 7, 8,
		0, 9, 10

	};

	unsigned int whVAO, whVBO, whEBO;
	glCreateVertexArrays(1, &whVAO);
	glCreateBuffers(1, &whVBO);
	glCreateBuffers(1, &whEBO);

	glBindVertexArray(whVAO);
	glBindBuffer(GL_ARRAY_BUFFER, whVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, whEBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(whVertices), whVertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(whIndeces), whIndeces, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(6 * sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	/////////////////////////////////////////////////////////////////////////////////////////////////
	
	float poVertices [] = {
		0.01f, 0.0f, 0.0f,	0.675f, 0.576f, 0.384f,
	       -0.01f, 0.0f, 0.0f,	0.675f, 0.576f, 0.384f,
	        0.01f, -1.0f, 0.0f,	0.675f, 0.576f, 0.384f,
	       -0.01f, -1.0f, 0.0f,	0.675f, 0.576f, 0.384f
	};
	unsigned int poIndeces [] = {
		0, 2, 3,
		3, 1, 0
	};

	unsigned int poVAO, poVBO, poEBO;
	glCreateVertexArrays(1, &poVAO);
	glCreateBuffers(1, &poVBO);
	glCreateBuffers(1, &poEBO);

	glBindVertexArray(poVAO);
	glBindBuffer(GL_ARRAY_BUFFER, poVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, poEBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(poVertices), poVertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(poIndeces), poIndeces, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	float airVertices[] = {
	// streak 1
	0.20f, 0.50f, 0.0f,
	0.40f, 0.55f, 0.0f,

	0.14f, 0.65f, 0.0f,
	0.34f, 0.70f, 0.0f,

	0.08f, 0.80f, 0.0f,
	0.28f, 0.85f, 0.0f,
};

	unsigned int airVAO, airVBO;

	glCreateVertexArrays(1, &airVAO);
	glCreateBuffers(1, &airVBO);

	glBindVertexArray(airVAO);
	glBindBuffer(GL_ARRAY_BUFFER, airVBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(airVertices), airVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

glEnableVertexAttribArray(0);

	shader ourShader { "../shaderSrc/vShader.vert", "../shaderSrc/fShader.frag"};
	shader ourShader2 { "../shaderSrc/poVShader.vert", "../shaderSrc/poFShader.frag"};

	shader airShader {"../shaderSrc/airVShader.vert", "../shaderSrc/airFShader.frag"};
	shader flipShader {"../shaderSrc/flipVShader.vert", "../shaderSrc/fShader.frag"};
	
	while(!glfwWindowShouldClose(window))
	{
		processInput(window);


		glClearColor(1.0f, 1.0f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		float time = glfwGetTime();
		ourShader.use();
		ourShader.setFloat("angle", time);


		glBindVertexArray(whVAO);
		glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_INT, 0);

		glBindVertexArray(poVAO);
		ourShader2.use();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		float air = std::sin(time);
		airShader.use();
		airShader.setFloat("air", time);
		glBindVertexArray(airVAO);

		glLineWidth(5.0f);


		glDrawArrays(GL_LINES, 0, 6); // 3 lines × 2 verts each
		glBindVertexArray(whVAO);
		flipShader.use();
		flipShader.setFloat("air", time);
		glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_INT, 0);

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
