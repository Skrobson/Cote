#pragma once
#include "VertexArray.h"
#include "Material.h"
#include "Texture.h"

namespace cote
{
	namespace graphic
	{
		using namespace cote::graphic;

		class Mesh
		{

		public:

			Mesh(std::shared_ptr<Material> material, std::shared_ptr<VertexArray> vao);

			std::shared_ptr<Material> getMaterial();		
			std::shared_ptr<VertexArray> getVAO();

			~Mesh();

		protected:
			std::shared_ptr<Material> material;
			std::shared_ptr<VertexArray> vao;
		};
	}
}



