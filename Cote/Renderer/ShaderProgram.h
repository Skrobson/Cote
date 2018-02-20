#pragma once

#include <GL\glew.h>
//#include <detail/type_vec4.hpp>

#include <memory>
#include <initializer_list>
#include <map>

#include  <glm.hpp>
#include "GLerror.h"
#include "Shader.h"

namespace cote
{
	namespace graphic
	{


		class ShaderProgram
		{
		public:
			ShaderProgram();
			ShaderProgram(std::initializer_list<const Shader> list);
			

			void attachShader(const Shader& shader);
			void linkProgram();
			void bind()const;
			void unbind()const;
			inline unsigned getProgramID()const { return *programID; }

			inline bool isLinked()const { return linked; }

			void setUniform(int location, int value);
			void setUniform(int location, unsigned value);
			void setUniform(int location, float value);
			void setUniform(int location, glm::vec2 value);
			void setUniform(int location, glm::vec3 value);
			void setUniform(int location, glm::vec4 value);
			void setUniform(int location, glm::mat3 value);
			void setUniform(int location, glm::mat4 value);

		protected:

			std::shared_ptr<unsigned> programID;
			/**Na ta chwile mapa shaderow bedzie sie znajdowala w shader program, pozniej zostanie przeniesiona
			do fabryki programow*/
			std::vector<unsigned> attachedShaders;

			bool linked = false;

		private:
			void createProgram();
		};
	}
}

