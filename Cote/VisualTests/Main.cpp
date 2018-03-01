
#include <vector>
#include <iostream>


#include "Window.h"
#include "TextureTest.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>

int main()
{

	Window* window;


	glfwInit();
	window = new Window(800, 600, "renderer");//w klasie window znajduje sie glfwWindowhint ktory musi zostac wywo�any przed glewInit

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


;

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


	glEnable(GL_DEPTH_TEST);
	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	//glCullFace(GL_FRONT_AND_BACK);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glEnable(GL_ALPHA);
	TextureTest test;
	
	while (glfwWindowShouldClose(*window) == false) {
		glfwPollEvents();

		//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//glActiveTexture(GL_TEXTURE0);
		//glUniform1i(glGetUniformLocation(program->getProgramID(), "texture_diffuse1"), 0);
		//glBindTexture(GL_TEXTURE_2D, tex->getTextureID());


		test.render();


		glfwSwapBuffers(*window);
	}


	delete window;

	return 0;
}