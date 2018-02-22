#include "TextureTest.h"
#include <iostream>
#include <GLerror.h>
#include <common.hpp>

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


	vS.loadFromFile("../../Data/shaders/tex_vertex.glvs", cote::graphic::ShaderType::VERTEX_SHADER);
	//vS.loadFromFile("../../Data/shaders/simple_model_vertex.glvs", cote::graphic::ShaderType::VERTEX_SHADER);
	fS.loadFromFile("../../Data/shaders/tex_fragment.glfs", cote::graphic::ShaderType::FRAGMENT_SHADER);
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
	UniformT<glm::mat4> preUniform;
	preUniform.setUniformName("model");
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	preUniform.setValue(model);
	auto uptr = std::make_shared<UniformT<glm::mat4>>(preUniform);

	material->addUniform(uptr);

	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection = glm::perspective(glm::radians(45.0f), float(800 / 600), 0.1f, 100.0f);

	auto uptrView = std::make_shared<UniformT<glm::mat4>>();
	auto uptrProjection = std::make_shared<UniformT<glm::mat4>>();
	uptrView->setValue(view);
	uptrView->setUniformName("view");
	
	uptrProjection->setValue(projection);
	uptrProjection->setUniformName("projection");

	material->addUniform(uptrProjection);
	material->addUniform(uptrView);
	
}


TextureTest::~TextureTest()
{

}

void TextureTest::render()
{
	
	RenderCommand command;
	command.setMaterial(material);
	command.setVAO(vertexArray);

	renderer.addCommandToQueue(std::make_shared<RenderCommand>(command));
	renderer.render();
}
