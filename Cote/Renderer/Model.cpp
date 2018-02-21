#include "Model.h"

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

void cote::graphic::Model::render()
{
}
