#include "TextureTest.h"
#include <iostream>
#include <GLerror.h>

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

	vertexArray = std::make_unique<cote::graphic::VertexArray>(indicies, vLayout);



	vS.loadFromFile("../../Data/shaders/tex_vertex.glvs", cote::graphic::ShaderType::VERTEX_SHADER);
	fS.loadFromFile("../../Data/shaders/tex_fragment.glfs", cote::graphic::ShaderType::FRAGMENT_SHADER);
	program = std::make_unique<cote::graphic::ShaderProgram>();
	program->attachShader(vS);
	program->attachShader(fS);
	program->linkProgram();


	cote::graphic::Bitmap bitmap = cote::graphic::Bitmap("../../Data/textures/herb.png");


	tex = std::make_unique<cote::graphic::Texture2d>(bitmap);

	std::cout << tex->getTextureID() << std::endl;
	std::cout << bitmap.getHeight()<<" "<<bitmap.getWidth() << std::endl;
	GlError error;
	if (error.check())
		std::cout << error.getError() << std::endl;

}


TextureTest::~TextureTest()
{

}

void TextureTest::bind()
{
	program->bind();
	tex->bind(0);
	//oldTex->use(0);
	glUniform1i(glGetUniformLocation(program->getProgramID(), "texture_diffuse1"), 0);
	

	vertexArray->drawElements();
}
