#pragma once
#include <queue>
#include "Material.h"

namespace cote
{
	namespace graphic
	{
		using namespace cote::graphic;

		class Renderer
		{
		public:
			Renderer();

			//prototype
			void addCommandToQueue(std::shared_ptr<Material> material);
			virtual void render();

			virtual ~Renderer();

		protected:
			std::queue<std::shared_ptr<Material>> renderQueue;
		};


	}
}

