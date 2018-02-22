#include "Renderer.h"
#include <gtc\matrix_transform.hpp>

using namespace cote::graphic;

Renderer::Renderer()
{
	view.setUniformName("view");
	view.setValue(glm::lookAt(glm::vec3(0.0, 2.0, 0.0), glm::vec3(0.0, 0.0, -4.0), glm::vec3(0.0, 1.0, 0.0)));

	projection.setUniformName("projection");
	projection.setValue(glm::perspective(glm::radians(45.0f), float(800 / 600), 0.1f, 100.0f));

}

void cote::graphic::Renderer::setView(glm::mat4 view)
{
}


void cote::graphic::Renderer::addCommandToQueue(std::shared_ptr<RenderCommand> material)
{
	renderQueue.push(material);
	view.searchForUniformLocation(material->getProgram());
	projection.searchForUniformLocation(material->getProgram());
}

void cote::graphic::Renderer::render()
{
	while (renderQueue.empty() == false)
	{
		auto command = renderQueue.front();
		if (actualProgram != command->getProgram())
		{
			actualProgram->unbind();
			actualProgram = command->getProgram();
			actualProgram->bind();
			view.updateValueForProgram(actualProgram);
			projection.updateValueForProgram(actualProgram);
		}
		command->render();
		renderQueue.pop();
	}
	//actualProgram->unbind();

	//actualProgram = nullptr;
}

Renderer::~Renderer()
{
}
