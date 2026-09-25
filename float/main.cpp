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

	GLFWwindow *window = glfwCreateWindow(800, 600, "MATRIX POO", NULL, NULL);
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
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pooWidth, pooHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pooData);
		glGenerateMipmap(GL_TEXTURE_2D);
		// incoming is needed to blend transparent images
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else
	{
		std::cout<<"Failed to load poo pic\n";
	}
	stbi_image_free(pooData);

	unsigned int matTex;
	glGenTextures(1, &matTex);
	glBindTexture(GL_TEXTURE_2D, matTex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	int matWidth, matHeight, matChannels;
	unsigned char *matData = stbi_load("../assets/matrix.jpg", &matWidth, &matHeight, &matChannels, 0);
	std::cout << "matrix channels: " << matChannels << std::endl;
	if(matData)
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //to fix the black color bug
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, matWidth, matHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, matData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout<<"Failed to load matrix\n";
	}
	stbi_image_free(matData);

	float matVertices [] {
		-1.0f, -1.0f, 0.0f,     0.0f, 0.0f, //bottom left
		-1.0f,  1.0f, 0.0f, 	0.0f, 1.0f, //top left
		 1.0f,  1.0f, 0.0f,	1.0f, 1.0f, //top right
		 1.0f, -1.0f, 0.0f, 	1.0f, 0.0f  //bottom right
	};
	unsigned int matIndeces [] {
		0, 1, 2,
		2, 3, 0
	};
	
	unsigned int matVAO, matVBO, matEBO;
	glGenVertexArrays(1, &matVAO);
	glGenBuffers(1, &matVBO);
	glGenBuffers(1, &matEBO);

	glBindVertexArray(matVAO);
	glBindBuffer(GL_ARRAY_BUFFER, matVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, matEBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(matVertices), matVertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(matIndeces), matIndeces, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	float pooVertices [] {
		-0.225f, -0.3f, 0.0f,     0.0f, 0.0f, // bottom left
		-0.225f,  0.3f, 0.0f,     0.0f, 1.0f, // top left 
		 0.225f,  0.3f, 0.0f,     1.0f, 1.0f, // top right	
		 0.225f, -0.3f, 0.0f,     1.0f, 0.0f  // bottom right
	};
	unsigned int pooIndeces [] {
		0, 1, 2,
		2, 3, 0
	};

	unsigned int pooVAO, pooVBO, pooEBO;
	glGenVertexArrays(1, &pooVAO);
	glGenBuffers(1, &pooVBO);
	glGenBuffers(1, &pooEBO);

	glBindVertexArray(pooVAO);
	glBindBuffer(GL_ARRAY_BUFFER, pooVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pooEBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(pooVertices), pooVertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(pooIndeces), pooIndeces, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	
	shader pooShader {"../shaderSrc/pooVShader.vert", "../shaderSrc/pooFShader.frag"};
	shader matShader {"../shaderSrc/matVShader.vert", "../shaderSrc/matFShader.frag"};

	float xOff {0.0f}, yOff {0.0f}; //the offset that would be added to our texture
	float xVel {0.6f}, yVel {0.45f}; //constant for our velocity

	const float halfW {0.225f}, halfH {0.3f}; // half the width of the poo quad ( the square thats outlined around poo but we have invisibile)

	float lastFrame {0.0f}; //start of time
	

	while(!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT); // just to clear the screen before rendering the next frame doesnt matter color
		//calculate current frame to know the time passed to get the new position ( pos = velocity * time )
		float currentFrame = glfwGetTime();
		float deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		xOff += xVel * deltaTime;
		yOff += yVel * deltaTime;
		//xOff += xVel;
		//yOff += yVel;

		if (xOff + halfW >=  1.0f) {xOff =  1.0f - halfW; xVel = -xVel;}
		if (xOff - halfW <= -1.0f) {xOff = -1.0f + halfW; xVel = -xVel;};
		if (yOff + halfH >=  1.0f) {yOff =  1.0f - halfH; yVel = -yVel;}
		if (yOff - halfH <= -1.0f) {yOff = -1.0f + halfH; yVel = -yVel;};

		
		matShader.use();
		matShader.setInt("texture1", 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, matTex);
		glBindVertexArray(matVAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		float time = glfwGetTime();
		

		pooShader.use();
		pooShader.setInt("texture1", 0);
		pooShader.setFloat("xOffSet", xOff);
		pooShader.setFloat("yOffSet", yOff);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, pooTex);
		
		glBindVertexArray(pooVAO);
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
