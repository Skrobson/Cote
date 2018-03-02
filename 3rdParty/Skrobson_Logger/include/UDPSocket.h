#pragma once
#include<winsock2.h>
#include <memory>
#include "NetworkException.h"
#include "InetAddress.h"

#ifdef _WIN32

#pragma comment(lib,"ws2_32.lib") //Winsock Library
#define WINSOCK_MAJOR_VERSION 2
#define WINSOCK_MINOR_VERSION 2


class UDPSocket
{
public:
	UDPSocket();
	void writeDatagram(const std::string& datagram, const InetAddress& address)const;
	SOCKET getSockethandler()const { return *socketHandler; }
private:
	std::shared_ptr<SOCKET> socketHandler;

	std::shared_ptr<WSADATA> wsaData; //static 

	void init(); //static

};


#elif UNIX
class UDPSocket
{
public:
	UDPSocket() { throw NetworkException("sokcets not supportet yet"); }
	void writeDatagram(const std::string& datagram, const InetAddress& address)const { throw NetworkException("sokcets not supportet yet"); }

};


	
#endif // _WIN32
