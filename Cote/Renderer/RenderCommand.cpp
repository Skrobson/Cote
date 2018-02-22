#include "RenderCommand.h"

using namespace cote::graphic;

RenderCommand::RenderCommand()
{
}

void cote::graphic::RenderCommand::setMaterial(std::shared_ptr<Material> material)
{
	this->material = material;
}

void cote::graphic::RenderCommand::setVAO(std::shared_ptr<VertexArray> vao)
{
	this->vao = vao;
}

std::shared_ptr<ShaderProgram> cote::graphic::RenderCommand::getProgram()
{
	return material->getProgram();
}

void cote::graphic::RenderCommand::render()
{
	material->updateUniforms();
	material->bindTextures();

	vao->bind();
	vao->drawElements();
	vao->unbind();

	material->unbindTextures();
}





