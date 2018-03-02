#include "stdafx.h"
#include "GlobalLogger.h"

#include "CommandParser.h"
#include "ConsoleLogStream.h"
#include "FileLogStream.h"
#include "BroadcastLogStream.h"
# ifdef _WIN32
#include <windows.h>
# endif // _WIN32
bool GlobalLogger::initialized = false;

std::shared_ptr<Logger> GlobalLogger::logger = nullptr;

GlobalLogger::GlobalLogger()
{
}

void GlobalLogger::init(int argc,const char * argv[])
{
	if (!initialized)
	{
		CommandParser parser(argc, argv);
		logger = parser.createLogger();
		initialized = true;
	}
	
}

void GlobalLogger::init(int argc, const wchar_t * argv[])
{
	if (!initialized)
	{
		CommandParser parser(argc, argv);
		logger = parser.createLogger();
		initialized = true;
	}
}



const std::shared_ptr<const Logger> GlobalLogger::getLogger()
{
	if (logger == nullptr)
	{
		logger = std::make_shared<Logger>();
		auto stream = std::make_shared<ConsoleLogStream>();
		logger->addLogStream(stream);

		std::string fileName;
# ifdef _WIN32

		constexpr auto lenght = 1024;
		wchar_t exePath[lenght];
		GetModuleFileName(NULL, exePath, lenght * sizeof(WCHAR));
		std::wstring wFileName(exePath);
		fileName.assign(wFileName.begin(), wFileName.end());
		auto i = fileName.find_last_of('\\');
		fileName = fileName.substr(++i);

# endif // _WIN32		
		fileName += "_LOG.txt";
		auto fileStream = std::make_shared<FileLogStream>(fileName);
		logger->addLogStream(fileStream);

	}
	return logger;
}

void GlobalLogger::implicitFileLogInit()
{
	if (!initialized)
	{
		std::string fileName;

# ifdef _WIN32

		constexpr auto lenght = 1024;
		wchar_t exePath[lenght];
		GetModuleFileName(NULL, exePath, lenght * sizeof(WCHAR));
		std::wstring wFileName(exePath);
		fileName.assign(wFileName.begin(), wFileName.end());
		auto i = fileName.find_last_of('\\');
		fileName = fileName.substr(++i);
# endif // _WIN32		

		fileName += "_LOG.txt";

		logger = std::make_shared<Logger>();
		logger->addLogStream(std::make_shared<ConsoleLogStream>());
		logger->addLogStream(std::make_shared<FileLogStream>(fileName));

		initialized = true;


	}
		
}

void GlobalLogger::implicitBroadcastLogInit(int port)
{
	if (!initialized)
	{
		logger = std::make_shared<Logger>();
		logger->addLogStream(std::make_shared<ConsoleLogStream>());
		logger->addLogStream(std::make_shared<BroadcastLogStream>(port));

		initialized = true;
	}
}
