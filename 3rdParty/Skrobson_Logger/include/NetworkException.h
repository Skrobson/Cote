#pragma once
#include <string>
#include <exception>
class NetworkException:public std::exception
{
public:
	NetworkException();
	NetworkException(const std::string& what);
	NetworkException(int errCode);
	NetworkException(const std::string& what, int errCode);

	virtual ~NetworkException();
	
	virtual const char* what()const  override;

	const int getErrorCode()const { return errorCode; }

	protected:
		std::string problem{};
		int errorCode{ 0 };
};

