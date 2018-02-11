#pragma once
#include <map>
#include <memory>
#include <functional>
#include "ShaderProgram.h"
namespace cote 
{
	namespace graphic 
	{

		template<typename T>
		class Uniform
		{
		public:
		
			void setValue(T newValue) { value = newValue; }
			
			T getValue()const { return value; }

			/**Specify the value of a uniform variable for the current program object*/
			void updateValueForProgram(const ShaderProgram& program)const =0;

			void searchForUniformLocation(std::shared_ptr<const ShaderProgram> program, const std::string& uniformName);
		protected:
			T value;

			static const auto comparator = []( std::shared_ptr<const ShaderProgram> a,const std::shared_ptr<ShaderProgram> b) {
				return a->getProgramID() > b->getProgramID();
			};

			std::map <std::shared_ptr<const ShaderProgram>, int, decltype( comparator)> uniformLocations ;

			std::string name;
			
		};
		template<typename T>
		inline void Uniform<T>::searchForUniformLocation(std::shared_ptr<const ShaderProgram> program, const std::string & uniformName)
		{
			auto location = glGetUniformLocation(program->getProgramID(), uniformName.c_str());
			uniformLocations.insert_or_assign(program, location);
		}
	}
}


