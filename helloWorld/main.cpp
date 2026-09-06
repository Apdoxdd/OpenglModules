#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
void process_input( GLFWwindow *window )
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE ) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
void framebuffer_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}
int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL Example", NULL, NULL);
	if (window == NULL)
	{
		std::cout<<"failed to create GLFW window"<<std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if( !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout<<"Failed to initialze GLAD"<<std::endl;
		return -1;
	}
	glfwSetFramebufferSizeCallback(window, framebuffer_callback);

	float f1 = 0.2f, f2 =  0.3f, f3 = 0.3f, f4 = 1.0f;
	while(!glfwWindowShouldClose(window))
	{
		// input
		process_input(window);

		// rendering
		glClearColor(f1+=0.1, f2+=0.1, f3+=0.1, f4);
		glClear(GL_COLOR_BUFFER_BIT);

		// check and call and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}



	glfwTerminate();
	return 0;
}

