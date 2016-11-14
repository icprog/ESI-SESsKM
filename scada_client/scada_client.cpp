// scada_client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "../TCPDriver/TCPDriver.h"
int main()
{
	SOCKET cs = INVALID_SOCKET, as = INVALID_SOCKET;
	TCPDriver *tcp = new TCPDriver();
	tcp->connectt(&as, &cs, "127.0.0.1", 27016, 1);
    return 0;
}

