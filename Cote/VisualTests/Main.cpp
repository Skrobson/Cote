
#include <vector>
#include <iostream>
#include <memory>

#include "Window.h"
#include "Textureold.h"
#include "ShaderProgram.h"
#include "VertexArray.h"
#include <GL/glew.h>
#include <GLFW\glfw3.h>

int main()
{
	cote::graphic::Shader vS;
	cote::graphic::Shader fS;
	std::unique_ptr<cote::graphic::ShaderProgram> program;
	Window* window;
	Texture* tex;
	std::unique_ptr< cote::graphic::VertexArray> vertexArray;


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


	std::vector<unsigned> indicies = { 0,1,3 ,1,2,3 };


	//vertexArray->bind();

	std::vector<glm::vec3> vertexPos{
		//pos					
		{ 0.5f, 0.5f, 0.0f },
	{ 0.5f, -0.5f, 0.0f }	,
	{ -0.5f, -0.5f, 0.0f }	,
	{ -0.5f,  0.5f, 0.0f }
	};
	std::shared_ptr<cote::graphic::VertexAttribute> pos = std::make_shared<cote::graphic::VertexAttribute3f>(cote::graphic::VertexAttributeIndex::POSITION, vertexPos);

	std::vector<glm::vec2> vertexUv{
		{ 1.0f, 1.0f },
	{ 1.0f, 0.0f },
	{ 0.0f, 0.0f },
	{ 0.0f, 1.0f }
	};

	std::shared_ptr<cote::graphic::VertexAttribute> uv = std::make_shared<cote::graphic::VertexAttribute2f>(cote::graphic::VertexAttributeIndex::UV_0, vertexUv);

	cote::graphic::VertexAttributeLayout vLayout;
	vLayout.pushVertexAttribute(pos);
	vLayout.pushVertexAttribute(uv);

	vertexArray = std::make_unique<cote::graphic::VertexArray>(indicies, vLayout);
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cerr << "after vertexArray" << glewGetErrorString(error);
	}

	tex = new Texture("../../Data/textures/wall.jpg", TEX_DIFFUSE);

	vS.loadFromFile("../../Data/shaders/tex_vertex.glvs", cote::graphic::ShaderType::VERTEX_SHADER);
	fS.loadFromFile("../../Data/shaders/tex_fragment.glfs", cote::graphic::ShaderType::FRAGMENT_SHADER);
	program = std::make_unique<cote::graphic::ShaderProgram>();
	program->attachShader(vS);
	program->attachShader(fS);
	program->linkProgram();

	//przykladowy vertex
	//Vertex vertices1[] = {
	//	{ glm::vec3(0.5f, 0.5f, 0.0f),glm::vec2(1.0f, 1.0f) },
	//	{ glm::vec3(0.5f, -0.5f, 0.0f),glm::vec2(1.0f, 0.0f) },
	//	{ glm::vec3(-0.5f, -0.5f, 0.0f),glm::vec2(0.0f, 0.0f) },
	//	{ glm::vec3(-0.5f,  0.5f, 0.0f),glm::vec2(0.0f, 1.0f) }

	//};
	//GLuint indecies1[] = { 0,1,3 ,1,2,3 };

	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cerr << glewGetErrorString(error);
	}




	while (glfwWindowShouldClose(*window) == false) {
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		program->bind();
		tex->use(0);
		//glActiveTexture(GL_TEXTURE0);
		//glUniform1i(glGetUniformLocation(program->getProgramID(), "texture_diffuse1"), 0);
		//glBindTexture(GL_TEXTURE_2D, tex->getTextureID());



		vertexArray->drawElements();


		glfwSwapBuffers(*window);
	}


	delete window;

	return 0;
}