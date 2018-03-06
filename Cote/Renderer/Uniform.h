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
			virtual void updateValueForProgram(std::shared_ptr<ShaderProgram>  program)=0;
			
			std::string getName()const { return uniformName; }

			virtual void searchForUniformLocation(std::shared_ptr<const ShaderProgram> program);
		protected:
			std::map <std::shared_ptr<const ShaderProgram>, int, Comparator > uniformLocations;

			std::string uniformName;

		};

		template<typename T>
		class UniformT : public Uniform
		{
		public:
			UniformT(const std::string& name);

			UniformT(){}

			UniformT(T value,const std::string& name);

			void setValue(T newValue) { value = newValue; }
			
			T getValue()const { return value; }

			UniformT<T>& operator=(const T& t);
			
			operator T();

			/**Specify the value of a uniform variable for the current program object*/
			virtual void updateValueForProgram(std::shared_ptr<ShaderProgram>  program)override;

		protected:
			T value;

			
		};
		template<typename T>
		inline UniformT<T>::UniformT(const std::string& name): Uniform(name)
		{
		}

		template<typename T>
		inline UniformT<T>::UniformT(T value ,const std::string& name)
		{
			this->value = value;
		}

		template<typename T>
		inline UniformT<T> & UniformT<T>::operator=(const T & t)
		{
			this->value = t;
			return *(this);
		}

		template<typename T>
		inline UniformT<T>::operator T()
		{
			return value;
		}

		template<typename T>
		void UniformT<T>::updateValueForProgram(std::shared_ptr<ShaderProgram>  program)
		{
			//auto loc = uniformLocations.find(program);
			//if (loc != uniformLocations.end())
			//	program->setUniform(loc->second, value);
			//else
			//{
			//	searchForUniformLocation(program);
			//}

			program->setUniform<T>(uniformName, value);
		}
	}
}


