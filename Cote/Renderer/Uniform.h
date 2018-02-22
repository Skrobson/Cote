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
			Uniform(std::string name);
			Uniform() {}

			void setUniformName(const std::string& name) { uniformName = name; }
			virtual void updateValueForProgram(const std::shared_ptr<ShaderProgram>  program)=0;
			
			virtual void searchForUniformLocation(std::shared_ptr<const ShaderProgram> program);
		protected:
			std::map <std::shared_ptr<const ShaderProgram>, int, Comparator > uniformLocations;

			std::string uniformName;

		};

		template<typename T>
		class UniformT : public Uniform
		{
		public:
			UniformT(std::string name);
			UniformT(){}
			void setValue(T newValue) { value = newValue; }
			
			T getValue()const { return value; }

			/**Specify the value of a uniform variable for the current program object*/
			virtual void updateValueForProgram(const std::shared_ptr<ShaderProgram>  program)override;

		protected:
			T value;

			std::string name;
			
		};
		template<typename T>
		inline UniformT<T>::UniformT(std::string name): Uniform(name)
		{
		}
		template<typename T>
		void UniformT<T>::updateValueForProgram(const std::shared_ptr<ShaderProgram>  program)
		{
			auto loc = uniformLocations.find(program);
			if(loc != uniformLocations.end())
				program->setUniform(loc->second, value);
		}


	
	}
}


