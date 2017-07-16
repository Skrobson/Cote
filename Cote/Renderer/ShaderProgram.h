#pragma once

#include <GL\glew.h>
#include <detail/type_vec4.hpp>

#include <memory>
#include <initializer_list>
#include <map>

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
			~ShaderProgram();

			bool attachShader(const Shader& shader);
			bool linkProgram();
			void bind()const;
			void unbind()const;
			inline unsigned getProgramID()const { return mProgram; }

			inline bool isLinked()const { return mbLinked; }

		private:

			unsigned mProgram;

			std::map<ShaderType, unsigned> mShaders;

			bool mbLinked = false;
		};
	}
}

