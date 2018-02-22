#include "Mesh.h"
using namespace cote::graphic;

cote::graphic::Mesh::Mesh(std::shared_ptr<Material> material, std::shared_ptr<VertexArray> vao): material(material), vao(vao)
{
}

void cote::graphic::Mesh::setName(const std::string & name)
{
	meshName = name;
}

std::string cote::graphic::Mesh::getName()
{
	return meshName;
}

std::shared_ptr<Material> cote::graphic::Mesh::getMaterial()
{
	return material;
}

std::shared_ptr<VertexArray> cote::graphic::Mesh::getVAO()
{
	return vao;
}

