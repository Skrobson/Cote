#pragma once
#pragma once
#include <vector>
#include <map>
#include <regex>
#include <memory>
#include "Logger.h"
class CommandParser
{
public:
	CommandParser(int argc , const char* argv[]);

	CommandParser(int argc, const wchar_t* argv[]);

	std::shared_ptr<Logger> createLogger()const;
	std::vector<std::string> chopParamString(const std::string& options);

	const std::map<char, std::string> getOpts() const { return parsedOptions; }
private:
	

	void parseOptions(std::vector<std::string>& options);
	
	std::map<char, std::string>  parsedOptions;

	void logError(const std::string& msg)const;

	const std::string OPT_START = "--LOG";

	const char OPT_CONSOLE = 'C';
	const char OPT_BROADCAST = 'B';
	const char OPT_FILE = 'F';
	const char OPT_LEVEL = 'L';
	const char OPT_PREFIX = '-';

	const std::string REG ="^-[A-Z]$";

	const int MAX_OPTIONS = 4;
};

