#pragma once
#include <map>
#include <memory>
#include <functional>
#include "ShaderProgram.h"
namespace cote
{
	namespace graphic
	{

		class Comparator
		{
		public:
			bool operator()(std::shared_ptr<const ShaderProgram> a, std::shared_ptr<const ShaderProgram> b) const; 
			
		};

		class Uniform
		{
		public:
			virtual void updateValueForProgram(const std::shared_ptr<ShaderProgram>  program)=0;
			
			virtual void searchForUniformLocation(std::shared_ptr<const ShaderProgram> program, const std::string& uniformName);
		protected:
			std::map <std::shared_ptr<const ShaderProgram>, int, Comparator > uniformLocations;

		};

		template<typename T>
		class UniformT : public Uniform
		{
		public:
		
			void setValue(T newValue) { value = newValue; }
			
			T getValue()const { return value; }

			/**Specify the value of a uniform variable for the current program object*/
			virtual void updateValueForProgram(const std::shared_ptr<ShaderProgram>  program)override;

		protected:
			T value;

			std::string name;
			
		};
		template<typename T>
		void UniformT<T>::updateValueForProgram(const std::shared_ptr<ShaderProgram>  program)
		{
			auto loc = uniformLocations.find(program);
			if(loc != uniformLocations.end())
				program->setUniform(loc->second, value);
		}


	
	}
}


