#include "stdafx.h"
#include "FileLogStream.h"


FileLogStream::FileLogStream(std::string fileName):fileName(fileName)
{
	file = std::shared_ptr<std::fstream>(new std::fstream(fileName, std::fstream::out | std::fstream::app),
		[](std::fstream* f) {
		if (f->is_open())
		f->close();
	});
}


void FileLogStream::putMessageIntoStream(const std::stringstream & msg)const
{
	if (file->is_open())
	{
		(*file) << msg.str();
		file->flush();
	}
}



