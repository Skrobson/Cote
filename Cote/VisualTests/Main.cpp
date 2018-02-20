
#include <vector>
#include <iostream>


#include "Window.h"
#include "TextureTest.h"
#include <GL/glew.h>
#include <GLFW\glfw3.h>

int main()
{

	Window* window;


	glfwInit();
	window = new Window(800, 600, "renderer");//w klasie window znajduje sie glfwWindowhint ktory musi zostac wywo³any przed glewInit

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "\nFAILED TO INITIALIZE GLEW";//debugLog
		glfwTerminate();

		return 1;
	}
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cerr << glewGetErrorString(error);
	}


	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	//pobieranie rozmiaru okna
	int frameX, frameY;
	glfwGetFramebufferSize(*window, &frameX, &frameY);

	//ustawianie miejsca do ryowania
	glViewport(0, 0, frameX, frameY);
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cerr << "after viewport & framebuffer" << glewGetErrorString(error);
	}






	//przykladowy vertex
	//Vertex vertices1[] = {
	//	{ glm::vec3(0.5f, 0.5f, 0.0f),glm::vec2(1.0f, 1.0f) },
	//	{ glm::vec3(0.5f, -0.5f, 0.0f),glm::vec2(1.0f, 0.0f) },
	//	{ glm::vec3(-0.5f, -0.5f, 0.0f),glm::vec2(0.0f, 0.0f) },
	//	{ glm::vec3(-0.5f,  0.5f, 0.0f),glm::vec2(0.0f, 1.0f) }

	//};
	//GLuint indecies1[] = { 0,1,3 ,1,2,3 };

	TextureTest test;
	glEnable(GL_ALPHA);
	while (glfwWindowShouldClose(*window) == false) {
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		//glActiveTexture(GL_TEXTURE0);
		//glUniform1i(glGetUniformLocation(program->getProgramID(), "texture_diffuse1"), 0);
		//glBindTexture(GL_TEXTURE_2D, tex->getTextureID());


		test.bind();


		glfwSwapBuffers(*window);
	}


	delete window;

	return 0;
}