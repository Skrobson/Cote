#include "stdafx.h"
#include "InetAddress.h"

#ifdef _WIN32

#include <Ws2tcpip.h>


InetAddress::InetAddress()
{
	memset((void *)&socketAddress, '\0', sizeof(struct sockaddr_in));
	socketAddress.sin_family = AF_INET;
}

InetAddress::InetAddress(const std::string & address, int port):InetAddress()
{

	setPort(port);
	if (!setAddress(address))
	{
		InvalidAddressFormatException ex{ address };
		throw ex;
	}
}

InetAddress::InetAddress(int port) : InetAddress()
{
	setPort(port);
	setBroadcast();
}



bool InetAddress::setAddress(const std::string & address)
{
	if ((inet_pton(AF_INET, address.c_str(), &socketAddress.sin_addr)) != 1)
	{
		return false;
	}
	return true;
}

void InetAddress::setBroadcast()
{
	socketAddress.sin_addr.S_un.S_addr = INADDR_BROADCAST;
}

void InetAddress::setPort(int port)
{
	socketAddress.sin_port = htons(port);
}

#endif


InvalidAddressFormatException::InvalidAddressFormatException(const std::string & address): address(address)
{
}

const char * InvalidAddressFormatException::what() const
{
	auto error = address;
	error += " is invalid address \n";
	return error.c_str();
}
