#include "GLerror.h"






GlError::GlError()
{
	clearBuffer();
}

std::vector<std::string> GlError::getErrors()
{
	return errors;
}

void GlError::clear()
{
	clearBuffer();
	errors.clear();
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
		while ((errorCode = glGetError()) != GL_NO_ERROR)
		{
			saveErrorString(errorCode);
		}
		
		return true;
	}
}

void GlError::clearBuffer()
{
	while (glGetError != GL_NO_ERROR);
}

void GlError::saveErrorString(GLenum errCode)
{
	std::stringstream tmpErr;
	tmpErr << glewGetErrorString(errCode);

	errors.push_back(tmpErr.str());
}
