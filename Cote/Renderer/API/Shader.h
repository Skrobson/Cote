#pragma once
#include <gl\glew.h>
#include <string>
#include <exception>
#include "GLerror.h"

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
			Shader(const std::string& filename, ShaderType);
			~Shader();

			
			void loadFromFile(const char* filename, ShaderType type);
			void loadFromFile(const std::string& filename, ShaderType type);

			inline unsigned getShaderID()const {
				return mShaderID;
			}

			inline ShaderType getType()const { return mType; }
			inline bool isCompiled()const { return mbCompiled; }


		private:

			bool mbCompiled = false;

			ShaderType mType;
			unsigned mShaderID;
		};
	}
}

