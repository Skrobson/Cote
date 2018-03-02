#pragma once
#include <memory>
#include "Logger.h"


#define DEBUG_LOG(...) GlobalLogger::getLogger()->logDebug(__FILE__, __VA_ARGS__)
#define INFO_LOG(...)  GlobalLogger::getLogger()->logInfo(__FILE__, __VA_ARGS__)
#define ERROR_LOG(...) GlobalLogger::getLogger()->logError(__FILE__, __VA_ARGS__)
#define FATAL_ERROR_LOG(...) GlobalLogger::getLogger()->logFatalError(__FILE__, __VA_ARGS__)
#define WARNING_LOG(...) GlobalLogger::getLogger()->logWarning(__FILE__, __VA_ARGS__)

#define LOG_IMPLICIT_FILE_STREAM() GlobalLogger::implicitFileLogInit();	
#define LOG_IMPLICIT_BROADCAST_STREAM() GlobalLogger::implicitBroadcastLogInit()

class GlobalLogger
{
public:
	
	/**Inicjacja globalnego obiektu
	*--log + parametry jako jeden string oddzielone spacja 
	*-c konsola
	*-b [port] broadcast na podanym porcie
	*-f [filename] zapis logow do pliku
	*-l [level] poziom logowania jako int
	*		1 info
	*		2 warning
	*		3 error
	*		4 fatal error
	*		5 debug
	*/
	static void init(int argc,const char* argv[]);


	/**Inicjacja globalnego obiektu
		*--log + parametry jako jeden string oddzielone spacja 
		*-c konsola
		*-b [port] broadcast na podanym porcie
		*-f [filename] zapis logow do pliku
		*-l [level] poziom logowania jako int
		*		1 info
		*		2 warning
		*		3 error
		*		4 fatal error
		*		5 debug		
	*/
	static void init(int argc, const wchar_t* argv[]);

	static const std::shared_ptr<const Logger> getLogger();

	static void implicitFileLogInit();

	static void implicitBroadcastLogInit(int port = 8080);

protected:

	GlobalLogger();

	static std::shared_ptr<Logger> logger;

	static bool initialized ;
};


	


