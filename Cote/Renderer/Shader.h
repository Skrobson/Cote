#pragma once
#include <gl\glew.h>
#include <string>
#include <exception>
#include "GLerror.h"
#include <memory>

namespace cote
{
	namespace graphic
	{

		enum  ShaderType
		{
			VERTEX_SHADER = GL_VERTEX_SHADER,
			FRAGMENT_SHADER = GL_FRAGMENT_SHADER
		};




		class Shader
		{
		public:
			Shader();
			/**Loading from file*/
			Shader(const std::string& filename, ShaderType);

			/**Create shader from source*/
			static std::shared_ptr<Shader> createVertexShader(const std::string& source);

			/**Create shader from source*/
			static std::shared_ptr<Shader> createFragmentShader(const std::string& source);

			/**Create from source*/
			Shader(ShaderType ,const std::string& source);
	
			void createFromSource(const std::string & text, ShaderType type);
			

			//Wczytywanie z pliku mo¿nazrobiæ osobno
			void loadFromFile(const char* filename, ShaderType type);

			void loadFromFile(const std::string & filename, ShaderType type);



			inline unsigned getShaderID()const {
				return *shaderID;
			}

			inline ShaderType getType()const { return shaderType; }

			inline bool isCompiled()const { return compiled; }


		protected:

			bool compiled = false;

			ShaderType shaderType;

			std::shared_ptr<unsigned> shaderID;

		private:
			void makeHandler();
		};
	}
}

