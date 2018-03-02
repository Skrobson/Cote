#pragma once
#include <sstream>
class LogStream
{
public:
	
	virtual void putMessageIntoStream(const std::stringstream& msg)const = 0;

	virtual ~LogStream();

};


