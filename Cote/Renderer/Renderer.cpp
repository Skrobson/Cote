#include "Renderer.h"

using namespace cote::graphic;

Renderer::Renderer()
{
}


void cote::graphic::Renderer::addCommandToQueue(std::shared_ptr<Material> material)
{
	renderQueue.push(material);
}

void cote::graphic::Renderer::render()
{
	while (renderQueue.empty() == false)
	{
		auto command = renderQueue.front();
		command->render();
		renderQueue.pop();
	}
}

Renderer::~Renderer()
{
}
