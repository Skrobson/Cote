#include "stdafx.h"
#include "UDPLogStream.h"
#include "Logger.h"
#include "ConsoleLogStream.h"

UDPLogStream::UDPLogStream(const InetAddress & address) : address(address)
{
	try
	{
		socket = std::make_shared<UDPSocket>();
		connectionEstablishment = true;
	}
	catch (const NetworkException& ex)
	{
		handleException(ex);
	}
	
	
}


void UDPLogStream::putMessageIntoStream(const std::stringstream & msg)const
{
	if (connectionEstablishment)
	{
		try
		{
			socket->writeDatagram(msg.str(), address);
		}
		catch (const NetworkException& ex)
		{
			handleException(ex);
		}
	}
	
}

void UDPLogStream::handleException(const std::exception & ex)const
{
	Logger logger;
	auto console = std::make_shared<ConsoleLogStream>();
	logger.addLogStream(console);
	logger.logError(__FILE__, ex.what());
}
