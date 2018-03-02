#pragma once
#include <vector>

#include "LogStream.h"
#include "UDPSocket.h"

class UDPLogStream: public LogStream
{
public:
	UDPLogStream(const InetAddress& address);

	virtual void putMessageIntoStream(const std::stringstream& msg)const override;

private:

	bool connectionEstablishment = false;

	std::shared_ptr<UDPSocket > socket;
	
	InetAddress  address;

	void handleException(const std::exception& ex)const;
};

