#pragma once

#include <string>
#include <exception>


class InvalidAddressFormatException : public std::exception 
{
public:
	InvalidAddressFormatException(const std::string& address);

	const char* what()const override;
private:
	std::string address;
};


#ifdef _WIN32

#include<winsock2.h>
class InetAddress
{
public:
	InetAddress();
	InetAddress(const std::string& address, int port);
	InetAddress(int port);

	bool setAddress(const std::string& address);
	void setBroadcast();
	void setPort(int port);

	const sockaddr_in _getAddressStruct()const { return socketAddress; }
protected:
	sockaddr_in socketAddress;
};

#elif UNIX
class sockaddr_in
{

};

class InetAddress
{
public:
	InetAddress() { ; }
	InetAddress(const std::string& address, int port) { ; }
	InetAddress(int port) { ; }

	bool setAddress(const std::string& address) { ; }
	void setBroadcast() { ; }
	void setPort(int port) { ; }

	const sockaddr_in _getAddressStruct()const { return socketAddress; }
protected:
	sockaddr_in socketAddress;
};

#endif