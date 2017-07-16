#pragma once
#include <exception>
#include <string>

class GLerror:public std::runtime_error
{
public:
	GLerror(const std::string& error);
	GLerror(const char* error);
	
	~GLerror();
private:
	
};

