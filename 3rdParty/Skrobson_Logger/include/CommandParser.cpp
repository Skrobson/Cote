#include "stdafx.h"
#include "CommandParser.h"
#include <algorithm>
#include <cctype>
#include "ConsoleLogStream.h"
#include "BroadcastLogStream.h"
#include "FileLogStream.h"


CommandParser::CommandParser(int argc,const char * argv[])
{
	std::vector<std::string> options;
	for (auto i = 0; i < argc; ++i)
	{
		options.push_back(argv[i]);
	}
	parseOptions(options);
}

CommandParser::CommandParser(int argc, const wchar_t * argv[])
{
	std::vector<std::string> options;
	for (auto i = 0; i < argc; ++i)
	{
		std::wstring wArg = argv[i];
		std::string arg(wArg.begin(), wArg.end());
		options.push_back(arg);
	}
	parseOptions(options);
}

std::shared_ptr<Logger> CommandParser::createLogger()const
{
	auto logger = std::make_shared<Logger>();
	for (auto& opt : parsedOptions)
	{
		auto c = opt.first;
		
		if (c == OPT_CONSOLE)
		{
			logger->addLogStream(std::make_shared<ConsoleLogStream>());
		}
		else if (c == OPT_BROADCAST)
		{
			try 
			{
				auto port = std::stoi(opt.second);
				logger->addLogStream(std::make_shared<BroadcastLogStream>(port));
			}
			catch(std::exception& ex)
			{ 
				std::string error = "Wrong port parameter ";
				error += ex.what();
				logError( error);
			}
		}
		else if (c == OPT_FILE)
		{
			logger->addLogStream(std::make_shared<FileLogStream>(opt.second));
		}
		else if (c == OPT_LEVEL)
		{
			try
			{
				auto level = std::stoi(opt.second);
				logger->setMinimalLogLevel(static_cast<LogLevel>( level));
			}
			catch (std::exception& ex)
			{
				std::string error = "Wrong port parameter ";
				error += ex.what();
				logError(error);
			}
		}
		else
		{
			std::string error = "Unexcepted parameter: ";
			error += c;
			logError(error);
		}
	}
	return logger;
}


std::vector<std::string> CommandParser::chopParamString(const std::string& options)
{
	std::vector<std::string> chopedOptions;
		
	std::regex rgx("\\s+");
	std::sregex_token_iterator iter(options.begin(),
		options.end(),
		rgx,
		-1);
	std::sregex_token_iterator end;
	for (; iter != end; ++iter)
	{
		if (!std::regex_match(iter->str(), rgx))
			chopedOptions.push_back(iter->str());
	}
	
	return chopedOptions;
}

void CommandParser::parseOptions(std::vector<std::string>& options)
{
	for (auto & opt : options)
	{
		std::transform(opt.begin(), opt.end(), opt.begin(), std::toupper);
	}

	auto opt = std::find(options.begin(), options.end(), OPT_START);

	if((opt != options.end())&&(++opt!= options.end()))
	{ 
		auto chopedParams = chopParamString(*opt);
		opt = chopedParams.begin();
		auto nrOpt = 0;
		std::regex reg(REG);
		do
		{
			if (std::regex_match(*opt, reg))
			{
				
				auto option{(*opt)[opt->find_first_not_of(OPT_PREFIX)] };
				++opt;
				if ((opt != chopedParams.end()) && (!std::regex_match(*opt, reg)))
				{
					std::string value{ *(opt) };
					parsedOptions.insert( std::make_pair(option, value));
					++nrOpt;
				}
				else if(opt != chopedParams.end())
				{
					parsedOptions.insert( std::make_pair(option, std::string()));
					++nrOpt;
				}		
				else ++opt;
			}
			else ++opt;
			

		} while ((opt != chopedParams.end()) && (nrOpt < MAX_OPTIONS ));
	}
}

void CommandParser::logError(const std::string& msg)const
{
	Logger log;
	log.addLogStream(std::make_shared<ConsoleLogStream>());
	log.logWarning("",msg);
}
