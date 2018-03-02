#include "stdafx.h"
#include "BroadcastLogStream.h"



BroadcastLogStream::BroadcastLogStream(int port): UDPLogStream(port)
{

}

void BroadcastLogStream::putMessageIntoStream(const std::stringstream & msg)const
{
	UDPLogStream::putMessageIntoStream(msg);
}
