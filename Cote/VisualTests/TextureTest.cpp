#include "TextureTest.h"
#include <iostream>
#include <GLerror.h>
#include <common.hpp>
#include <AssetManager.h>

TextureTest::TextureTest()
{
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

	vertexArray = std::make_shared<cote::graphic::VertexArray>(indicies, vLayout);


	//vS.loadFromFile("../../Data/shaders/tex_vertex.glvs", cote::graphic::ShaderType::VERTEX_SHADER);
	vS.loadFromFile("../../Data/shaders/simple_model_vertex.glvs", cote::graphic::ShaderType::VERTEX_SHADER);
	fS.loadFromFile("../../Data/shaders/simple_model_fragment.glfs", cote::graphic::ShaderType::FRAGMENT_SHADER);
	//fS.loadFromFile("../../Data/shaders/tex_fragment.glfs", cote::graphic::ShaderType::FRAGMENT_SHADER);
	program = std::make_shared<cote::graphic::ShaderProgram>();
	program->attachShader(vS);
	program->attachShader(fS);
	program->linkProgram();


	cote::graphic::Bitmap bitmap = cote::graphic::Bitmap("../../Data/textures/herb.png");


	tex = std::make_shared<cote::graphic::Texture2d>(bitmap);
	tex->setSamplerName("texture_diffuse1");
	GlError error;
	if (error.check())
		std::cout << error.getError() << std::endl;


	material = std::make_shared<Material>(program);
	material->addTexture(tex);


	//intro to 3d
	modelMat = std::make_shared<UniformT<glm::mat4>>();
	modelMat->setUniformName("model");

	transform.setPos(glm::vec3(0.0, 0.0, -4.0));
	//glm::mat4 matModel  = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.0));
	//model->setValue( glm::rotate(matModel, glm::radians(-10.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
	box = createBox();

	cote::AssetManager manager;

	model = manager.loadModel("../../Data/models/nanosuit.obj", program);
	
	model->transform.setPos(glm::vec3(0.0, 0.0, -4.0));
}


TextureTest::~TextureTest()
{

}

void TextureTest::render()
{
	//glm::mat4 matPos = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -4.0));
	model->transform.rotate(glm::vec3(0.0f, 0.0f, 1.0f), -1.0f);
	//*modelMat = transform.rotate(glm::vec3(0.0f, 0.0f, 1.0f),  -1.0f);
	//(glm::rotate(matPos,  glm::radians((float)glfwGetTime() *-35.0f), glm::vec3(1.0f, 0.0f, -1.0f)));//transform.getModel();
	//RenderCommand command(material, box, modelMat);
	//renderer.addCommandToQueue(std::make_shared<RenderCommand>(command));
	model->render(renderer);

	renderer.render();
}

std::shared_ptr<cote::graphic::VertexArray> TextureTest::createBox()
{
	std::vector<glm::vec3> vertexPos{
		// front
		{-1.0, -1.0,  1.0},
		{1.0, -1.0,  1.0},
		{1.0,  1.0,  1.0},
		{-1.0,  1.0,  1.0},
		// back			},
		{-1.0, -1.0, -1.0},
		{1.0, -1.0, -1.0},
		{1.0,  1.0, -1.0},
		{-1.0,  1.0, -1.0}

	};


	std::vector<glm::vec2> vertexUv{
		{ 1.0f, 1.0f },
		{ 1.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 1.0f },
		{ 1.0f, 1.0f },
		{ 1.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 1.0f }
	};

	std::vector<unsigned> indicies = {		
		// front
		0, 1, 2,
		2, 3, 0,
		// top
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// bottom
		4, 0, 3,
		3, 7, 4,
		// left
		4, 5, 1,
		1, 0, 4,
		// right
		3, 2, 6,
		6, 7, 3, };

	std::shared_ptr<cote::graphic::VertexAttribute> pos = std::make_shared<cote::graphic::VertexAttribute3f>(cote::graphic::VertexAttributeIndex::POSITION, vertexPos);

	std::shared_ptr<cote::graphic::VertexAttribute> uv = std::make_shared<cote::graphic::VertexAttribute2f>(cote::graphic::VertexAttributeIndex::UV_0, vertexUv);

	cote::graphic::VertexAttributeLayout vLayout;
	vLayout.pushVertexAttribute(pos);
	vLayout.pushVertexAttribute(uv);

	auto box = std::make_shared<cote::graphic::VertexArray>(indicies, vLayout);

	return box;
}
