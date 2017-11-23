#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <GL\glew.h>



/**
GlError checks the OpenGl errors
Create object or use clear method before you call OpenGl function
*/
class GlError
{
public:
	GlError();

	std::vector<std::string> getErrors();
	
	/**Clear the buffer with errors
	Use it if you do not regularly test for errors */
	void clear();

	/**
	*Checks for OpenGl errors
	*@return true if error appears
	*/
	bool check();

private:
	std::vector<std::string> errors;

	void clearBuffer();

	void saveErrorString(GLenum errCode);
};

