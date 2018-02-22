#include "RenderCommand.h"

using namespace cote::graphic;


cote::graphic::RenderCommand::RenderCommand(std::shared_ptr<Material> material, std::shared_ptr<VertexArray> vao, std::shared_ptr<UniformT<glm::mat4>> transform)
{
	this->material = material;
	program = material->getProgram();

	this->vao = vao;
	modelTransform = transform;
	modelTransform->setUniformName("model");
	modelTransform->searchForUniformLocation(program);
}



std::shared_ptr<ShaderProgram> cote::graphic::RenderCommand::getProgram()
{
	return material->getProgram();
}

void cote::graphic::RenderCommand::render()
{
	modelTransform->updateValueForProgram(program);
	material->updateUniforms();
	material->bindTextures();

	
	vao->bind();
	vao->drawElements();
	vao->unbind();

	material->unbindTextures();
}






