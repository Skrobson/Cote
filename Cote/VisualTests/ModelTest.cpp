#include "ModelTest.h"




ModelTest::ModelTest()
{
	vS.loadFromFile("../../Data/shaders/light_model_vertex.glvs", cote::graphic::ShaderType::VERTEX_SHADER);
	fS.loadFromFile("../../Data/shaders/light_model_fragment.glfs", cote::graphic::ShaderType::FRAGMENT_SHADER);
	program = std::make_shared<cote::graphic::ShaderProgram>();
	program->attachShader(vS);
	program->attachShader(fS);
	program->linkProgram();

	testModel = manager.loadModel("../../Data/models/nanosuit.obj", program);// witch / witch.obj", program);

	testModel->transform.setPos(glm::vec3(0.0, -5.0, -8.0));
	testModel->transform.setScale(glm::vec3(0.4, 0.4, 0.4));

	models.push_back(testModel);

	/////
	program->bind();
	std::cout << glGetUniformLocation(program->getProgramID(), "viewPos");
	std::cout << glGetUniformLocation(program->getProgramID(), "light.direction");

	dirLight = std::make_shared<Light>();
	dirLight->ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	dirLight->diffuse = glm::vec3(0.3f, 0.3f, 0.3f);
	dirLight->specular = glm::vec3(1.0f, 1.0f, 1.0f);
	dirLight->direction = glm::vec3(0.0f, 7.0f, 7.0f);
	//program->searchForUniformLocation(dirLight->ambient.getName());
	//program->searchForUniformLocation(dirLight->diffuse.getName());
	//program->searchForUniformLocation(dirLight->specular.getName());
	//program->searchForUniformLocation(dirLight->direction.getName());
	ATest::renderer.setDirectionalLight(dirLight);
	
}

void ModelTest::update()
{
	testModel->transform.rotate(glm::vec3(0.0f, 1.0f, 0.0f), -1.0f);
}


ModelTest::~ModelTest()
{
}
