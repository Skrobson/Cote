#pragma once
#include <vector>
#include "Mesh.h"

namespace cote
{
	namespace graphic
	{
		using namespace cote::graphic;

		class Model
		{
		public:
			Model();
			Model(std::vector<std::shared_ptr<Mesh>> meshes);

			void addMesh(std::shared_ptr<Mesh> mesh);

			void render();
		protected:
			std::vector<std::shared_ptr<Mesh>> meshes;
		};

	}
}


