#include "GLerror.h"






std::vector<std::string> GlError::getErrors()
{
	return errors;
}

bool GlError::checkForError()
{
	GLenum errorCode = glGetError();
	if (errorCode != GL_NO_ERROR)
	{
		saveErrorString(errorCode);
		return true;
	}
	else
		return false;
}

void GlError::saveErrorString(GLenum errCode)
{
	std::stringstream tmpErr;
	tmpErr << glewGetErrorString(errCode);

	errors.push_back(tmpErr.str());
}
