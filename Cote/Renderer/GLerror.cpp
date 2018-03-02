#include "GlError.h"






GlError::GlError()
{
	clearBuffer();
}

std::string GlError::getError()
{
	return error;
}

void GlError::clear()
{
	clearBuffer();
	error.clear();
}


bool GlError::check()
{
	GLenum errorCode = glGetError();
	if (errorCode == GL_NO_ERROR)
	{
		return false;
	}
	else 
	{
		saveErrorString(errorCode);

		return true;
	}
}

void GlError::clearBuffer()
{
	while (glGetError() != GL_NO_ERROR);
}

void GlError::saveErrorString(GLenum errCode)
{
	std::stringstream tmpErr;
	tmpErr << glewGetErrorString(errCode);

	error = tmpErr.str();
}
