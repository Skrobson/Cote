#pragma once
#include <queue>
#include "RenderCommand.h"

namespace cote
{
	namespace graphic
	{
		using namespace cote::graphic;

		class Renderer
		{
		public:
			Renderer();
			void setView(glm::mat4 view);
			
			//prototype
			void addCommandToQueue(std::shared_ptr<RenderCommand> command);
			virtual void render();

			virtual ~Renderer();

		protected:
			std::queue<std::shared_ptr<RenderCommand>> renderQueue;

			std::shared_ptr<ShaderProgram> actualProgram = nullptr;

			UniformT<glm::mat4> view;
			UniformT<glm::mat4> projection;
		};


	}
}

