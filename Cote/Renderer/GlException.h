#pragma once
#include <string>
#include <exception>
namespace cote
{	
	namespace graphic
	{

		class GlException : public std::runtime_error
		{
		public:
			GlException(const std::string& error);
			GlException(const char* error);
		};
	}

}

