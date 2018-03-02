#include "stdafx.h"
#include "UDPSocket.h"

#ifdef _WIN32
//std::shared_ptr<WSADATA> UDPSocket::wsaData = std::shared_ptr<WSADATA>(nullptr);

UDPSocket::UDPSocket()
{
	init();
	auto tmpSock = socket(AF_INET, SOCK_DGRAM, 0);
	if (tmpSock == INVALID_SOCKET)
	{ 
		NetworkException ex{ "Could not create socket. ",  WSAGetLastError() };
		throw(ex);
	}

	socketHandler = std::shared_ptr<SOCKET>(new SOCKET( tmpSock), [](SOCKET* sock) {
		closesocket(*sock);
		delete sock;
	});

	//set on broadcasting
	auto iOptVal = 1;
	auto iOptLen = sizeof(int);
	setsockopt(*socketHandler, SOL_SOCKET, SO_BROADCAST, (char*)&iOptVal, iOptLen);

}

void UDPSocket::writeDatagram(const std::string & datagram, const InetAddress & address) const
{
	if (sendto(*socketHandler, datagram.c_str(), datagram.length(), 0, (struct sockaddr *) &address._getAddressStruct(), sizeof(address._getAddressStruct())) == SOCKET_ERROR)
	{
		NetworkException ex{ "Could not send datagram through socket.",  WSAGetLastError() };
		throw(ex);
	}
}

void UDPSocket::init()
{
	//if (wsaData == nullptr) 
	//{
		WSADATA wsa;
		auto code = WSAStartup(MAKEWORD(WINSOCK_MAJOR_VERSION, WINSOCK_MINOR_VERSION), &wsa);
		if (code != 0)
		{
			NetworkException ex{ "Could not open Windows connection. " ,code };
			throw(ex);
		}
		wsaData = std::shared_ptr<WSAData>(new WSAData(wsa), [](WSAData * wsa) {
			WSACleanup();
			delete wsa;
		});
	//}
}
#endif