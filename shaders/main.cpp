#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "shader.hpp"

const char *redTrig_vertShader_source = "#version 330 core\n"
					"layout (location = 0) in vec3 aPos;\n"
					"out vec4 vertColor;\n"
					"void main()\n"
					"{ gl_Position = vec4(aPos, 1.0);\n"
					"vertColor = vec4(0.5, 0.0, 0.0, 1.0);\n }\n\0";

const char *redTrig_fragShader_source = "#version 330 core\n"
					"in vec4 vertColor;\n"
					"out vec4 fragColor;\n"
					"void main()\n"
					"{ fragColor = vertColor; }\n\0";

const char *uniTrig_fragShader_soruce ="#version 330 core\n"
				       "out vec4 fragColor;\n"
				       "uniform vec4 ourColor;\n"
				       "void main()\n"
				       "{ fragColor = ourColor;}\n\0";

const char *mulTrig_vertShader_source = "#version 330 core\n"
					"layout (location = 0) in vec3 aPos;\n"
					"layout (location = 1) in vec3 aColor;\n"
					"out vec3 ourColor;\n"
					"void main()\n"
					"{ gl_Position = vec4(aPos, 1.0);\n"
					"ourColor = aColor;\n }\n\0";

const char *mulTrig_fragShader_source = "#version 330 core\n"
					"in vec3 ourColor;\n"
					"out vec4 fragColor;\n"
					"void main()\n"
					"{ fragColor = vec4(ourColor, 1.0); }\n\0";

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
	/*int nAttr {};
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nAttr);
	std::cout<<"max vertex attributes is "<<nAttr;
	*/

	//start-compile red trig vertex shader
	unsigned int redTrigVertShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(redTrigVertShader, 1, &redTrig_vertShader_source, NULL);
	glCompileShader(redTrigVertShader);

	int success;
	char log[512];
	glGetShaderiv(redTrigVertShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(redTrigVertShader, 512, NULL, log);
		std::cout<<"ERROR::COMPILATION::VERTEX::SHADER\n"<<log;
	}
	//end-compile red trig vertex shader
	///////////////////////////////////////////////////////////////////////
	///start-compile red trig fragment shader
	unsigned int redTrigFragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(redTrigFragShader, 1, &redTrig_fragShader_source, NULL);
	glCompileShader(redTrigFragShader);

	glGetShaderiv(redTrigFragShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(redTrigFragShader, 512, NULL, log);
		std::cout<<"ERROR::COMPILATION::FRAGMENET::SHADER::RED\n"<<log;
	}
	//end-compile red trig frag shader
	//////////////////////////////////////////////////////////////////////
	///start compile uni trig frag shader
	unsigned int uniTrigFragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(uniTrigFragShader, 1, &uniTrig_fragShader_soruce, NULL);
	glCompileShader(uniTrigFragShader);

	glGetShaderiv(uniTrigFragShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(uniTrigFragShader, 512, NULL, log);
		std::cout<<"ERROR::COMPILATION::FRAGMENET::SHADER::UNIFORM\n"<<log;
	}
	///start-red trig shader prog
	unsigned int redTrigShaderProg = glCreateProgram();
	glAttachShader(redTrigShaderProg, redTrigVertShader);
	glAttachShader(redTrigShaderProg, redTrigFragShader);
	glLinkProgram(redTrigShaderProg);

	glGetProgramiv(redTrigShaderProg, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(redTrigShaderProg, 512, NULL, log);
		std::cout<<"ERROR::LINKING::SHADER::PROGRAM\n"<<log;
	}

	//end-red trig shader prog
	//////////////////////////////////////////////////////////////////////
	///start-uni trig shader prog
	unsigned int uniTrigShaderProg = glCreateProgram();
	glAttachShader(uniTrigShaderProg, redTrigVertShader);
	glAttachShader(uniTrigShaderProg, uniTrigFragShader);
	glLinkProgram(uniTrigShaderProg);


	glGetProgramiv(uniTrigShaderProg, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(uniTrigShaderProg, 512, NULL, log);
		std::cout<<"ERROR::LINKING::SHADER::PROGRAM\n"<<log;
	}

	//end-uni trig shader prog
	///////////////////////////////////////////////////////////////////////
	///start-mul trig vert shader
	unsigned int mulTrigVertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(mulTrigVertShader, 1, &mulTrig_vertShader_source, NULL);
	glCompileShader(mulTrigVertShader);

	glGetShaderiv(mulTrigVertShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(mulTrigVertShader, 512, NULL, log);
		std::cout<<"ERROR::COMPILING::SHADER::VERT::MUL\n"<<log;
	};
	//end-mul trig vert shader
	/////////////////////////////////////////////////////////////////////
	///start-mul trig frag shader
	unsigned int mulTrigFragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(mulTrigFragShader, 1, &mulTrig_fragShader_source, NULL);
	glCompileShader(mulTrigFragShader);


	glGetShaderiv(mulTrigFragShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(mulTrigFragShader, 512, NULL, log);
		std::cout<<"ERROR::COMPILING::SHADER::FRAG::MUL\n"<<log;
	};
	///end-mul trig frag shader
	/////////////////////////////////////////////////////////////////////
	///start-mul trig shader prog
	unsigned int mulTrigShaderProg = glCreateProgram();
	glAttachShader(mulTrigShaderProg, mulTrigVertShader);
	glAttachShader(mulTrigShaderProg, mulTrigFragShader);
	glLinkProgram(mulTrigShaderProg);

	glGetProgramiv(mulTrigShaderProg, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(redTrigShaderProg, 512, NULL, log);
		std::cout<<"ERROR::LINKING::SHADER::PROGRAM::MUL\n"<<log;
	}
	//end-mul trig shader prog
	////////////////////////////////////////////////////////////////////
	///start-trig drawing data
	float redTrigVertices [] {
		-0.5f, -0.5f, 0.0f,	1.0f, 0.0f, 0.0f,
		 0.0f,  0.5f, 0.0f,	0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,	0.0f, 0.0f, 1.0f
	};
	unsigned int redTrigVAO, redTrigVBO;
	glGenVertexArrays(1, &redTrigVAO);
	glGenBuffers(1, &redTrigVBO);

	glBindVertexArray(redTrigVAO);
	glBindBuffer(GL_ARRAY_BUFFER, redTrigVBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(redTrigVertices), redTrigVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//end-trig drawing data
	////////////////////////////////////////////////////////////////////

	shader ourShader { "../shadersSrc/vShader.vert", "../shadersSrc/fShader.frag"};

	// render loop
	while(!glfwWindowShouldClose(window))
	{
		//input
		processInput(window);
		

		//render
		glClearColor(0.3f, 0.4f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		ourShader.use();
		
		float timeValue = glfwGetTime();
		float redValue = std::sin(timeValue) / 2.0f;
		ourShader.setFloat("red", redValue);

		timeValue = glfwGetTime();
		float blueValue = std::sin(timeValue) / 2.0f;
		ourShader.setFloat("blue", blueValue);

		timeValue = glfwGetTime();
		float greenValue = std::sin(timeValue) / 2.0f;
		ourShader.setFloat("green", greenValue);

		ourShader.setFloat("move", greenValue);
		glBindVertexArray(redTrigVAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//swap buffers and poll io events
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
