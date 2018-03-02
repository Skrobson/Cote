#include "stdafx.h"

#include <iomanip>
#include <ctime>
#include <chrono>
#include "Logger.h"

Logger::Logger()
{
}

Logger::Logger(std::shared_ptr<LogStream> logStream, LogLevel minLogLevel)
{
	setMinimalLogLevel(minLogLevel);
	addLogStream(logStream);
}

void Logger::setMinimalLogLevel(LogLevel min)
{
	if (min < LogLevel::INFO)
		minLogLevel = LogLevel::INFO;
#ifndef  _DEBUG
	else if (min > LogLevel::FATAL_ERROR)
		minLogLevel = LogLevel::FATAL_ERROR;
#endif // ! _DEBUG
#ifdef _DEBUG

	else if (min > LogLevel::DEBUG)
		minLogLevel = LogLevel::DEBUG;
#endif
	else
		minLogLevel = min;
}

void Logger::addLogStream(std::shared_ptr<LogStream> stream)
{
	
	if ((std::find(logStreams.begin(), logStreams.end(), stream) == logStreams.end()))
	{
		logStreams.push_back(stream);
	}
	
}

std::string Logger::getTime() const
{
	auto now = std::chrono::system_clock::now();
	auto now_c = std::chrono::system_clock::to_time_t(now );
	
	std::string ts = std::ctime(&now_c);
	ts.resize(ts.size() - 1);
	return ts;
}

std::string Logger::getFileNameFromPath(const std::string & file)const noexcept
{
	auto i = file.find_last_of('\\');
	auto fileName = file.substr(++i);
	return fileName;
}

const std::string& Logger::selectPrefix(LogLevel level)const noexcept
{
	switch (level)
	{
	case LogLevel::INFO:
		return INFO;
		break;
	case LogLevel::DEBUG:
		return DEBUG;
		break;
	case LogLevel::WARNING:
		return WARNING;
		break;
	case LogLevel::ERROR:
		return ERROR;
		break;
	case LogLevel::FATAL_ERROR:
		return FATAL_ERROR;
		break;
	default: 
		return SEPARATOR;
		break;
	}

}



