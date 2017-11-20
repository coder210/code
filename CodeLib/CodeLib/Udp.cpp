#include "Udp.h"
#include<string.h>
#include <iostream>

namespace LivLib
{
	/* init udp */
	Udp::Udp()
	{
		WSADATA wsaData;
		WSAStartup(MAKEWORD(2, 2), &wsaData);
		this->_st = socket(AF_INET, SOCK_DGRAM, 0);
		this->_isBind = false;
	}

	bool Udp::BindAddr(const char *IP, const unsigned int port)
	{
		memset(&this->_addr, 0, sizeof(this->_addr));
		this->_addr = CreateAddr(IP, port);
		int res = bind(_st, (sockaddr *)&this->_addr, sizeof(this->_addr));
		this->_isBind = (res == 0);
		return this->_isBind;
	}

	inline sockaddr_in Udp::CreateAddr(const char *IP, const unsigned int port)
	{
		sockaddr_in addr;
		memset(&addr, 0, sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		addr.sin_addr.S_un.S_addr = inet_addr(IP);
		return addr;
	}


	int Udp::SendToMsg(char *sendIP, const unsigned int sendPort, const char *buffer)
	{
		sockaddr_in sendAddr = CreateAddr(sendIP, sendPort);
		return sendto(this->_st, buffer, strlen(buffer), 0, (SOCKADDR *)&sendAddr, sizeof(sendAddr));
	}

	bool Udp::RecvMsg(char *buffer)
	{
		return this->RecvMsg(buffer, NULL);
	}

	bool Udp::RecvMsg(char *buffer, IPPortPair *ipPort)
	{
		sockaddr_in sendAddr = {0};
		int len = sizeof(sendAddr);
		char tmpBuffer[1024] = {0};
		/* recv msg */
		int recvLen = recvfrom(this->_st, tmpBuffer, sizeof(tmpBuffer), 0, (SOCKADDR *)&sendAddr, &len);
		if(recvLen == -1)
		{
			return false;
		}
		else 
		{
			tmpBuffer[recvLen] = '\0';
			strcpy_s(buffer, strlen(tmpBuffer) + 1, tmpBuffer);

			/* 不为NULL就不接收 */
			if (ipPort != NULL)
			{
				ipPort->_ip = inet_ntoa(sendAddr.sin_addr);
				ipPort->_port = htons(sendAddr.sin_port);
			}
			return true;
		}
	}

	const SOCKET Udp::GetSocket()
	{
		return this->_st;
	}

	const sockaddr_in Udp::GetAddr()
	{
		return this->_addr;
	}

	const bool Udp::GetBindState()
	{
		return this->_isBind;
	}

	/* release init */
	Udp::~Udp()
	{
		if (this->_st != INVALID_SOCKET)
		{
			closesocket(this->_st);
		}
		WSACleanup();
	}
}
