#pragma once
#include <gl\glew.h>
#include <string>
#include <memory>
#include "GlError.h"
#include "GlException.h"

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

			/**Loading from file
			* @throws GlException
			* @throws std::exception
			*/
			Shader(const std::string& filename, ShaderType);

			/**Create shader from source
			* @throws GlException
			*/
			static std::shared_ptr<Shader> createVertexShader(const std::string& source);

			/**Create shader from source
			* @throws GlException
			*/
			static std::shared_ptr<Shader> createFragmentShader(const std::string& source);

			/**Create from source
			* @throws GlException
			*/
			Shader(ShaderType ,const std::string& source);
			
			/**Create from source
			* @throws GlException
			*/
			void createFromSource(const std::string & text, ShaderType type);
			

			/**Loading from file
			* @throws GlException
			* @throws std::exception
			*/
			void loadFromFile(const char* filename, ShaderType type);

			/**Loading from file
			* @throws GlException
			* @throws std::exception
			*/
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

