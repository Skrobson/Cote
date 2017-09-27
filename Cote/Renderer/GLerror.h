#pragma once
#include <exception>
#include <string>
#include <sstream>
#include <vector>
#include <GL\glew.h>




class GlError
{
public:
	
	std::vector<std::string> getErrors();
	
	bool checkForError();

private:
	std::vector<std::string> errors;

	void saveErrorString(GLenum errCode);
};

