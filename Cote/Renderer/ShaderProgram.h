#pragma once

#include <GL\glew.h>
#include <detail/type_vec4.hpp>

#include <memory>
#include <initializer_list>
#include <map>
#include <memory>

#include "GLerror.h"
#include "Shader.h"

namespace cote
{
	namespace graphic
	{

//TODO: shadery moze nie musza byc przechowywane i wylaczane z programu w destruktorze
		class ShaderProgram
		{
		public:
			ShaderProgram();
			ShaderProgram(std::initializer_list<const Shader> list);
			

			bool attachShader(const Shader& shader);
			bool linkProgram();
			void bind()const;
			void unbind()const;
			inline unsigned getProgramID()const { return *mProgram; }

			inline bool isLinked()const { return mbLinked; }

		protected:

			std::shared_ptr<unsigned> mProgram;
			/**Na ta chwile mapa shaderow bedzie sie znajdowala w shader program, pozniej zostanie przeniesiona
			do fabryki programow*/
			std::map<ShaderType, unsigned> mShaders;

			bool mbLinked = false;

		private:
			void createProgram();
		};
	}
}

