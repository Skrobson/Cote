#include "ModelTest.h"



ModelTest::ModelTest()
{
	//vS.loadFromFile("../../Data/shaders/tex_vertex.glvs", cote::graphic::ShaderType::VERTEX_SHADER);
	vS.loadFromFile("../../Data/shaders/simple_model_vertex.glvs", cote::graphic::ShaderType::VERTEX_SHADER);
	fS.loadFromFile("../../Data/shaders/simple_model_fragment.glfs", cote::graphic::ShaderType::FRAGMENT_SHADER);
	//fS.loadFromFile("../../Data/shaders/tex_fragment.glfs", cote::graphic::ShaderType::FRAGMENT_SHADER);
	program = std::make_shared<cote::graphic::ShaderProgram>();
	program->attachShader(vS);
	program->attachShader(fS);
	program->linkProgram();

	testModel = manager.loadModel("../../Data/models/nanosuit.obj", program);

	testModel->transform.setPos(glm::vec3(0.0, -5.0, -8.0));
	testModel->transform.setScale(glm::vec3(0.4, 0.4, 0.4));

	models.push_back(testModel);
}

void ModelTest::update()
{
	testModel->transform.rotate(glm::vec3(0.0f, 1.0f, 0.0f), -1.0f);
}


ModelTest::~ModelTest()
{
}
