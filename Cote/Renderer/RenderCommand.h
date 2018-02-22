#pragma once
#include <vector>

#include "Material.h"
#include "ShaderProgram.h"
#include "VertexArray.h"
#include "Uniform.h"

namespace cote
{
	namespace graphic
	{
		using  namespace cote::graphic;

		class RenderCommand
		{
		public:
			RenderCommand(std::shared_ptr<Material> material , std::shared_ptr<VertexArray> vao, std::shared_ptr<UniformT<glm::mat4>> modelTransform);
			
			
			std::shared_ptr<ShaderProgram> getProgram();

			void render();

		protected:
			std::shared_ptr<ShaderProgram>  program ;

			std::shared_ptr<Material> material;

			std::shared_ptr<VertexArray> vao;

			std::shared_ptr<UniformT<glm::mat4>> modelTransform;

		};

	}
}


