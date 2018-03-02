#pragma once
#include "UDPLogStream.h"
class BroadcastLogStream :
	public UDPLogStream
{
public:
	BroadcastLogStream(int port);

	virtual void putMessageIntoStream(const std::stringstream& msg)const override;

};

