#include "BoxTest.h"



BoxTest::BoxTest()
{
	box = createBox();
	models.push_back(box);
}

void BoxTest::update()
{
	box->transform.rotate(glm::vec3(1.0f, 1.0f, 0.0f), 2);
}

std::shared_ptr<Model> BoxTest::createBox()
{
	std::vector<glm::vec3> vertexPos{
		// front
		{ -1.0, -1.0,  1.0 },
		{ 1.0, -1.0,  1.0 },
		{ 1.0,  1.0,  1.0 },
		{ -1.0,  1.0,  1.0 },
		// back			},
		{ -1.0, -1.0, -1.0 },
		{ 1.0, -1.0, -1.0 },
		{ 1.0,  1.0, -1.0 },
		{ -1.0,  1.0, -1.0 }

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
	auto boxVao = std::make_shared<cote::graphic::VertexArray>(indicies, vLayout);

	//auto vS = Shader::createVertexShader("../../Data/shaders/simple_model_vertex.glvs");
	//auto fS = Shader::createFragmentShader("../../Data/shaders/simple_model_vertex.glfs");
	cote::graphic::Shader vS;
	cote::graphic::Shader fS;

	vS.loadFromFile("../../Data/shaders/simple_model_vertex.glvs", cote::graphic::ShaderType::VERTEX_SHADER);
	fS.loadFromFile("../../Data/shaders/simple_model_fragment.glfs", cote::graphic::ShaderType::FRAGMENT_SHADER);
	
	auto program = std::make_shared<cote::graphic::ShaderProgram>();
	program->attachShader(vS);
	program->attachShader(fS);
	program->linkProgram();


	cote::graphic::Bitmap bitmap = cote::graphic::Bitmap("../../Data/textures/herb.png");

	auto tex = std::make_shared<cote::graphic::Texture2d>(bitmap);
	tex->setSamplerName("texture_diffuse1");

	auto material = std::make_shared<Material>(program);
	material->addTexture(tex);

	auto modelMat = std::make_shared<UniformT<glm::mat4>>();
	modelMat->setUniformName("model");

	Transform transform;
	transform.setPos(glm::vec3(0.0, 0.0, -4.0));
	glm::mat4 matModel = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.0));
	modelMat->setValue(glm::rotate(matModel, glm::radians(-10.0f), glm::vec3(1.0f, 0.0f, 0.0f)));

	Mesh mesh(material, boxVao);
	box = std::make_shared<Model>();
	box->addMesh(std::make_shared<Mesh>(mesh));
	return box;
}



