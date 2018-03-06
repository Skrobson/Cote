#include "Renderer.h"
#include <gtc\matrix_transform.hpp>

using namespace cote::graphic;

Renderer::Renderer()
{
	view.setUniformName("view");
	//view.setValue(glm::lookAt(glm::vec3(0.0, 2.0, 0.0), glm::vec3(0.0, 0.0, -4.0), glm::vec3(0.0, 1.0, 0.0)));

	projection.setUniformName("projection");

	viewPos.setUniformName("viewPos");
	//projection.setValue(glm::perspective(glm::radians(45.0f), float(800 / 600), 0.1f, 100.0f));

}

void cote::graphic::Renderer::setCamera(Camera& camera)
{
	view = camera.getView();
	projection = camera.getProjection();
	viewPos = camera.getPosition();
}

void cote::graphic::Renderer::setView(glm::mat4 view)
{
}

void cote::graphic::Renderer::setDirectionalLight(std::shared_ptr<Light> light)
{
	dirLight = light;
}


void cote::graphic::Renderer::addCommandToQueue(std::shared_ptr<RenderCommand> material)
{
	renderQueue.push_back(material);

}

void cote::graphic::Renderer::render()
{
	for (auto command : renderQueue)
	{
		if (actualProgram != command->getProgram())
				{
					//actualProgram->unbind();
					actualProgram = command->getProgram();
					actualProgram->bind();
					view.updateValueForProgram(actualProgram);
					projection.updateValueForProgram(actualProgram);
					viewPos.updateValueForProgram(actualProgram);
					setUpLight();
				}
				command->render(actualProgram);
	}

	renderQueue.clear();
	actualProgram->unbind();

	actualProgram = nullptr;
}

Renderer::~Renderer()
{
}

void cote::graphic::Renderer::setUpLight()
{
	if (dirLight)
	{
		dirLight->ambient.updateValueForProgram(actualProgram);
		dirLight->diffuse.updateValueForProgram(actualProgram);
		dirLight->direction.updateValueForProgram(actualProgram);
		dirLight->specular.updateValueForProgram(actualProgram);

	}

}
