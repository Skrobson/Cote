#include "MapTest.h"
#include <HeightmapLoader.h>
//#include <GlobalLogger.h>



MapTest::MapTest()
{
	vS.loadFromFile("../../Data/shaders/light_map_model_vertex.glvs", cote::graphic::ShaderType::VERTEX_SHADER);
	fS.loadFromFile("../../Data/shaders/light_map_model_fragment.glfs", cote::graphic::ShaderType::FRAGMENT_SHADER);
	program = std::make_shared<cote::graphic::ShaderProgram>();
	program->attachShader(vS);
	program->attachShader(fS);
	program->linkProgram();

	Bitmap bitmap("../../Data/textures/heightmap-no-erosion.jpg");//terrain-heightmap-01.png
	HeightmapLoader mapLoader;
	mapLoader.convert(bitmap);

	std::vector<glm::vec2> uvs;
	for (auto y = 0; y < bitmap.getHeight(); ++y)
	{
		for (auto x = 0; x < bitmap.getWidth(); ++x)
		{
			uvs.push_back(glm::vec2(static_cast<float>(x)/10, static_cast<float>(y)/10));
			//uvs.push_back(glm::vec2(static_cast<float>(x) / (static_cast<float>(bitmap.getWidth())), static_cast<float>(y) / (static_cast<float>(bitmap.getHeight()))));
		}
	}


	auto pos = std::make_shared<VertexAttribute3f>(VertexAttributeIndex::POSITION,mapLoader.vertices);
	auto uv = std::make_shared<VertexAttribute2f>(VertexAttributeIndex::UV_0, uvs);
	auto norm = std::make_shared<VertexAttribute3f>(VertexAttributeIndex::NORMAL, mapLoader.normals);
	cote::graphic::VertexAttributeLayout vLayout;
	vLayout.pushVertexAttribute(pos);
	vLayout.pushVertexAttribute(uv);
	vLayout.pushVertexAttribute(norm);

	std::shared_ptr<VertexArray> vertexArray;
	try
	{

		vertexArray = std::make_shared<cote::graphic::VertexArray>(mapLoader.indicies, vLayout);
	}
	catch (GlException & ex)
	{
		std::cerr << ex.what();
		//FATAL_ERROR_LOG(ex.what());
	}
	Bitmap bitmap2("../../Data/textures/rock_blue.jpg");
	Bitmap bitmap3("../../Data/textures/ground_ao.png");
	auto material = std::make_shared<Material>(program);
	auto tex = std::make_shared<cote::graphic::Texture2d>(bitmap2, Texture::Repeat::MIRROR);
	auto tex2 = std::make_shared<cote::graphic::Texture2d>(bitmap3, Texture::Repeat::MIRROR);
	tex->setSamplerName("texture_diffuse1");
	tex2->setSamplerName("texture_specular1");
	material->addTexture(tex);
	material->addTexture(tex2);

	Mesh mapMesh = { material , vertexArray };
	Model mapModel ;
	mapModel.transform.setPos(glm::vec3(-450.0f, -150.0f, -25.0f));
	mapModel.addMesh(std::make_shared<Mesh>(mapMesh));
	models.push_back(std::make_shared<Model>(mapModel));

}

