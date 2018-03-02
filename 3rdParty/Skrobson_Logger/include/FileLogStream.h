#pragma once
#include <fstream>
#include <memory>
#include "LogStream.h"
class FileLogStream: public LogStream
{
public:
	FileLogStream(std::string fileName);

	virtual void putMessageIntoStream(const std::stringstream& msg)const override;

private:
	std::shared_ptr<std::fstream> file;

	std::string fileName;

};

