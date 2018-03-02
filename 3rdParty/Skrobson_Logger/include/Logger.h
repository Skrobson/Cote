#pragma once
#include <memory>
#include <vector>

#include "LogStream.h"

#undef ERROR

enum class LogLevel : int
{
	INFO = 0,
	WARNING ,
	ERROR,
	FATAL_ERROR,
#ifdef _DEBUG
	DEBUG = 4
#endif // DEBUG
#ifndef _DEBUG
	DEBUG = -1
#endif // !DEBUG


};


class Logger
{
public:

	Logger();

	Logger(std::shared_ptr<LogStream> logStream, LogLevel minlogLevel);

	void setMinimalLogLevel(LogLevel min);

	void addLogStream(std::shared_ptr<LogStream> stream);

	template<typename... T>
	void logInfo(const std::string& file,T... t)const noexcept;

	template<typename... T>
	void logDebug(const std::string& file,T... t)const noexcept;

	template<typename... T>
	void logWarning(const std::string& file,T... t)const noexcept;

	template<typename... T>
	void logError(const std::string& file,T... t)const noexcept;

	template<typename... T>
	void logFatalError(const std::string& file,T... t)const noexcept;

	template<typename... T>
	void log(LogLevel level, const std::string& file, T... t)const noexcept;

private:

	LogLevel minLogLevel = LogLevel::INFO;

	std::vector<std::shared_ptr<LogStream>> logStreams;

	template<typename T>
	void logInternal(std::stringstream& logStream, T t)const noexcept;

	template<typename T, typename ... U>
	void logInternal(std::stringstream& logStream, T t, U... u)const noexcept;

	std::string getTime()const;

	std::string getFileNameFromPath(const std::string& file)const noexcept;

	const std::string& selectPrefix(LogLevel level)const noexcept;

	const std::string INFO = "[INFO]";
	const std::string DEBUG = "[DEBUG]";
	const std::string WARNING = "[WARNING]";
	const std::string ERROR = "[ERROR]";
	const std::string FATAL_ERROR = "[FATAL_ERROR]";
	const std::string SEPARATOR = " ";

};



template<typename... T>
inline void Logger::log(LogLevel logLevel, const std::string& file, T... t)const noexcept
{
	if (logLevel >= minLogLevel)
	{
		std::stringstream logMessage;
		logMessage << selectPrefix(logLevel);
		logMessage << getTime();
		logMessage << " (" << getFileNameFromPath(file) << ") ";
		logInternal(logMessage,t...);
		
		logMessage << "\n\n";
		
		for (auto & log : logStreams)
		{
			log->putMessageIntoStream(logMessage);
		}
	}
}


template<typename T, typename... U>
inline void Logger::logInternal(std::stringstream& logMessage, T t, U... u)const noexcept
{
	logInternal(logMessage, t);
	logInternal(logMessage, u...);
}

template<typename T>
inline void Logger::logInternal(std::stringstream& logMessage, T t)const noexcept
{
	logMessage << t;
	logMessage << SEPARATOR;
}

template<typename ...T>
inline void Logger::logInfo(const std::string& file, T... t)const noexcept
{
	log(LogLevel::INFO,file, t...);
}

template<typename ...T>
inline void Logger::logDebug(const std::string& file, T ...t)const noexcept
{
#ifdef _DEBUG
	log(LogLevel::DEBUG, file, t...);
#endif // _DEBUG

	

	
}

template<typename ...T>
inline void Logger::logWarning(const std::string& file, T ...t)const noexcept
{
	log(LogLevel::WARNING, file, t...);
}

template<typename ...T>
inline void Logger::logError(const std::string& file, T ...t)const noexcept
{
	log(LogLevel::ERROR, file, t...);
}

template<typename ...T>
inline void Logger::logFatalError(const std::string& file, T ...t)const noexcept
{
	log(LogLevel::FATAL_ERROR, file, t...);
}
