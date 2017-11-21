#pragma once
//#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>

namespace cote
{
	class Logger
	{
	public:
		Logger();

		static void log(const std::string& message) noexcept
		{
			std::stringstream logMessage;

			auto time = std::chrono::system_clock::now();
			auto time_c = std::chrono::system_clock::to_time_t(time);
			
			//logMessage << std::put_time(std::localtime(&time_c), "%d-%m-%Y %H-%M-%S");
			logMessage << message << "\n";
			
			std::cerr << logMessage.str();
		}
		

	};
}

