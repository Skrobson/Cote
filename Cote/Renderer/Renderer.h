#pragma once
#include <queue>
#include "RenderCommand.h"
#include "Camera.h"
#include "Light.h"
namespace cote
{
	namespace graphic
	{
		using namespace cote::graphic;

		class Renderer
		{
		public:
			Renderer();

			void setCamera(Camera& camera);
			void setView(glm::mat4 view);
			void setDirectionalLight(std::shared_ptr<Light> light);

			//prototype
			void addCommandToQueue(std::shared_ptr<RenderCommand> command);
			virtual void render();

			virtual ~Renderer();

		protected:
			//std::queue<std::shared_ptr<RenderCommand>> renderQueue;
			std::vector<std::shared_ptr<RenderCommand>> renderQueue;
			std::shared_ptr<ShaderProgram> actualProgram = nullptr;

			UniformT<glm::mat4> view;
			UniformT<glm::mat4> projection;
			UniformT<glm::vec3> viewPos;
			std::shared_ptr<Light> dirLight;

			void setUpLight();
		};

		
	}
}

