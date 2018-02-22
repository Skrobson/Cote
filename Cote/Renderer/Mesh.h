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

			void setName(const std::string& name);
			std::string getName();

			std::shared_ptr<Material> getMaterial();		
			std::shared_ptr<VertexArray> getVAO();


		protected:
			std::shared_ptr<Material> material;
			std::shared_ptr<VertexArray> vao;

			std::string meshName;
		};
	}
}



