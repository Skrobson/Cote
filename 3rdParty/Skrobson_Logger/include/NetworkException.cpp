#include "stdafx.h"
#include "NetworkException.h"


NetworkException::NetworkException()
{
}

NetworkException::NetworkException(const std::string & what):problem(what)
{
}

NetworkException::NetworkException(int errCode):errorCode(errCode)
{
	if (errorCode != 0)
	{
		problem += " [error code]:" + std::to_string(errorCode);
	}
}

NetworkException::NetworkException(const std::string & what, int errCode):problem(what),errorCode(errCode)
{
	if (errorCode != 0)
	{
		problem += " [error code]:" + std::to_string(errorCode);
	}
}


NetworkException::~NetworkException()
{
}

const char * NetworkException::what() const
{


	return problem.c_str();
}
