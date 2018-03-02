#pragma once
#include <iostream>
#include "LogStream.h"
class ConsoleLogStream : public LogStream
{
public: 
	ConsoleLogStream();

	virtual void putMessageIntoStream(const std::stringstream& msg)const override;

private:
	std::ostream & console = std::cout;

};

