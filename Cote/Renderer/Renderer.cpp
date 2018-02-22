#include "Renderer.h"

using namespace cote::graphic;

Renderer::Renderer()
{
}


void cote::graphic::Renderer::addCommandToQueue(std::shared_ptr<RenderCommand> material)
{
	renderQueue.push(material);
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
		}
		command->render();
		renderQueue.pop();
	}
	actualProgram->unbind();

	actualProgram = nullptr;
}

Renderer::~Renderer()
{
}
