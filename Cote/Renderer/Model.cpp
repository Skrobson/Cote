#include "Model.h"
#include <iostream>
using namespace cote::graphic;

Model::Model()
{
}

cote::graphic::Model::Model(std::vector<std::shared_ptr<Mesh>> meshes): meshes(meshes)
{
}

void cote::graphic::Model::addMesh(std::shared_ptr<Mesh> mesh)
{
	meshes.push_back(mesh);
}

void cote::graphic::Model::render(Renderer& renderer)
{
	for (auto mesh : meshes)
	{
		auto model = std::make_shared<UniformT<glm::mat4>>("model");
		*model = transform.getModel();
		//RenderCommand command(mesh->getMaterial(), mesh->getVAO(), model);
		renderer.addCommandToQueue(std::make_shared<RenderCommand>(mesh->getMaterial(), mesh->getVAO(), model));
	}

}
