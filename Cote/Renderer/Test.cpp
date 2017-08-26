#include "Test.h"
#include <vector>


Test::Test()
{
	glfwInit();
	window = new Window(800, 600, "renderer");//w klasie window znajduje sie glfwWindowhint ktory musi zostac wywo³any przed glewInit

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "\nFAILED TO INITIALIZE GLEW";//debugLog
		glfwTerminate();

		return;
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
	//testy nowych klas
	cote::graphic::VertexAttributeLayout vLayout;
//	vLayout.pushVertexAttribute<glm::vec3>(cote::graphic::VertexAttributeIndex::POSITION);
//	vLayout.pushVertexAttribute<glm::vec2>(cote::graphic::VertexAttributeIndex::UV_0);



	vertexArray = std::make_unique<cote::graphic::VertexArray>();
	//vertexArray->bind();

	std::vector<float> vertexData{
		//pos					uv
		0.5f, 0.5f, 0.0f ,		1.0f, 1.0f ,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f,		0.0f, 1.0f
	};
	
	vertexArray->setAttributesValues(vertexData.size()*sizeof(float), &vertexData[0]);

	std::vector<unsigned> indicies = { 0,1,3 ,1,2,3 };
	vertexArray->copyElements(indicies.size(), &indicies[0]);

	vertexArray->setLayout(vLayout);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	//glBindVertexArray(NULL);
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



	


	
}

void Test::start()
{
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
}


Test::~Test()
{
	delete window;
}
