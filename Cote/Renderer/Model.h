#pragma once
#include <vector>
#include "Mesh.h"
#include "Renderer.h"
#include "Transform.h"

namespace cote
{
	namespace graphic
	{
		using namespace cote::graphic;
		using namespace cote;

		class Model
		{
		public:
			Model();
			Model(std::vector<std::shared_ptr<Mesh>> meshes);

			void addMesh(std::shared_ptr<Mesh> mesh);

			void render(Renderer& renderer);

			Transform transform;
		protected:
			std::vector<std::shared_ptr<Mesh>> meshes;

			
		};

	}
}


