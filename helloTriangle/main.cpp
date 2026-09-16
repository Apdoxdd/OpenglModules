#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


const char *vertShaderSource = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"void main()\n"
			"{ gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); }\0";

void updateView(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
int main()
{
	//start-initialize
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	

	GLFWwindow *window = glfwCreateWindow(800, 600, "HelloTriangle", NULL, NULL);
	if ( window == NULL )
	{
		std::cout<<"error making a window";
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
	// end-initialize
	

	//start-vertex shader compiling
	unsigned int vertShader;
	vertShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertShader, 1, &vertShaderSource, NULL);
	glCompileShader(vertShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{

		glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
		std::cout<<"ERROR::SHADER::VERTEX::COMPILATION::ERROR\n"<<infoLog;
	}


	//end-vertex shader compiling


	//start-fragment shader compiling
	const char *fragShaderSource = "#version 330 core\n"
				       "out vec4 fragColor;\n"
				       "void main()\n"
				       "{ fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); }; \0";
	unsigned int fragShader;
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragShader, 1, &fragShaderSource, NULL);
	glCompileShader(fragShader);

	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{

		glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
		std::cout<<"ERROR::SHADER::FRAG::COMPILATION::ERROR\n"<<infoLog;
	}

	//end-fragment shader compilation
	
	//start-program shader
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();


	glAttachShader(shaderProgram, vertShader);
	glAttachShader(shaderProgram, fragShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout<<"ERROR::LINKING::PROGRAM::ERROR\n"<<infoLog;
	}
	
	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

	//end-program shader
	
	//start-triangle setup
	
	float trigVert[] {
		0.2f, 0.2f, 0.0f,
		0.2f, 0.8f, 0.0f,
		0.8f, 0.2f, 0.0f
	};
	unsigned int trigVAO, trigVBO;
	glGenVertexArrays(1, &trigVAO);
	glGenBuffers(1, &trigVBO);

	glBindVertexArray(trigVAO);
	glBindBuffer(GL_ARRAY_BUFFER, trigVBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(trigVert), trigVert, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//end-triangle setup
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//start-rectangle setup 
	
	float recVert[] {
		-0.2f, 0.2f, 0.0f, // top right corner
		-0.8f, 0.2f, 0.0f, // top lef corner
		-0.8f, -0.2f, 0.0f, // bottom left corner
		-0.2f, -0.2f, 0.0f // bottom right corner
	};

	unsigned int recIndec []{
		0, 1, 2,
		2, 3, 0
	};

	unsigned int recVAO, recVBO, recEBO;
	glGenVertexArrays(1, &recVAO);
	glGenBuffers(1, &recVBO);
	glGenBuffers(1, &recEBO);

	glBindVertexArray(recVAO);
	glBindBuffer(GL_ARRAY_BUFFER, recVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, recEBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(recVert), recVert, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(recIndec), recIndec, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	//end-rectangle setup

	while(!glfwWindowShouldClose(window))
	{
		glfwSetFramebufferSizeCallback(window, updateView);
		//input

		processInput(window);


		//render commands
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);

		//start render trig
		glBindVertexArray(trigVAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//end render trig
		///////////////////////////////
		///start render rec
		glBindVertexArray(recVAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//end render rec
		//swap buffers and pull events

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}
