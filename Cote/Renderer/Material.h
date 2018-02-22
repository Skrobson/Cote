#pragma once
#include <vector>
#include <memory>

#include "RenderState.h"
#include "Texture.h"
#include "ShaderProgram.h"
#include "Uniform.h"
#include "VertexArray.h"


namespace cote
{
	namespace graphic
	{
		using namespace cote::graphic;

		class Material
		{
		public:
			Material(std::shared_ptr<ShaderProgram> shader );

			void addUniform(std::shared_ptr<Uniform> uniform);

			void addTexture(std::shared_ptr<Texture> texture);

			void updateUniforms();

			void bindTextures();
			void unbindTextures();

			std::shared_ptr<ShaderProgram> getProgram();

			virtual ~Material();

		protected:
			std::shared_ptr<ShaderProgram> shader;

			RenderState renderState;

			std::vector < std::pair<std::shared_ptr<Texture>, UniformT<int>>> textures;

			std::vector<std::shared_ptr<Uniform>> uniforms;


			//not use
			void setTexturesUniforms();


		};
	}
}



