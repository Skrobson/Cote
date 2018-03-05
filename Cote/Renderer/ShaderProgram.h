#pragma once

#include <GL\glew.h>
//#include <detail/type_vec4.hpp>

#include <memory>
#include <initializer_list>
#include <map>
#include <string.>

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

			template<typename  T>
			void setUniform(const std::string& name, T value);

			//void setUniform(const std::string& name, int value);
			//void setUniform(const std::string& name, unsigned value);
			//void setUniform(const std::string& name, float value);
			//void setUniform(const std::string& name, glm::vec2 value);
			//void setUniform(const std::string& name, glm::vec3 value);
			//void setUniform(const std::string& name, glm::vec4 value);
			//void setUniform(const std::string& name, glm::mat3 value);
			//void setUniform(const std::string& name, glm::mat4 value);

			void setUniform(int location, int value);
			void setUniform(int location, unsigned value);
			void setUniform(int location, float value);
			void setUniform(int location, glm::vec2 value);
			void setUniform(int location, glm::vec3 value);
			void setUniform(int location, glm::vec4 value);
			void setUniform(int location, glm::mat3 value);
			void setUniform(int location, glm::mat4 value);

		protected:

			std::map<std::string, int > uniformLocations;

			std::shared_ptr<unsigned> programID;

			std::vector<unsigned> attachedShaders;

			bool linked = false;

			void setUpUniformLocations();
			virtual void searchForUniformLocation(std::string uniformName);

		private:
			void createProgram();
		};
		template<typename T>
		inline void ShaderProgram::setUniform(const std::string & name, T value)
		{
			auto location = uniformLocations.find(name);
			if (location != uniformLocations.end())
				setUniform(location->second, value);
		//	else
			//	searchForUniformLocation(name);
		}
	}
}

