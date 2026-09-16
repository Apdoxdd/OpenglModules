#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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
		std::cout<<"ERROR::COMPILATION::FRAGMENET::SHADER\n"<<log;
	}
	//end-compile red trig frag shader
	//////////////////////////////////////////////////////////////////////
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
	glDeleteShader(redTrigVertShader);
	glDeleteShader(redTrigFragShader);

	//end-red trig shader prog
	//////////////////////////////////////////////////////////////////////
	///start-trig drawing data
	float redTrigVertices [] {
		-0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f
	};
	unsigned int redTrigVAO, redTrigVBO;
	glGenVertexArrays(1, &redTrigVAO);
	glGenBuffers(1, &redTrigVBO);

	glBindVertexArray(redTrigVAO);
	glBindBuffer(GL_ARRAY_BUFFER, redTrigVBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(redTrigVertices), redTrigVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//end-trig drawing data
	////////////////////////////////////////////////////////////////////



	// render loop
	while(!glfwWindowShouldClose(window))
	{
		//input
		processInput(window);
		

		//render
		glClearColor(0.3f, 0.4f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(redTrigShaderProg);

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
