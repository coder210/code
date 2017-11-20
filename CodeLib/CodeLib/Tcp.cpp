#include "Tcp.h"
#include <iostream>

namespace LivLib
{
	Tcp::Tcp(void)
	{
		WSADATA wsaData;
		WSAStartup(MAKEWORD(2, 2), &wsaData);
		this->_st = socket(AF_INET, SOCK_STREAM, 0);
		this->_isBind = false;
	}

	bool Tcp::BindAddr(const char *IP, const unsigned int port)
	{
		sockaddr_in sockAddr = CreateAddr(IP, port);
		int result = bind(this->_st, (sockaddr*)&sockAddr, sizeof(sockAddr));
		if (result == -1)
		{
			return false;
		}

		result = listen(this->_st, 4);
		if (result == 0)
		{
			this->_addr = sockAddr;
			/* 绑定成功 */
			return (this->_isBind = true);
		}
		else
		{
			return false;
		}
	}

	bool Tcp::Accept()
	{
		if (!this->_isBind)
		{
			return false;
		}

		/* 连接到服务器的的地址信息 */
		sockaddr_in connectAddr;
		int len = sizeof(connectAddr);
		SOCKET connectSocket = accept(this->_st, (sockaddr*)&connectAddr, &len);
		if (connectSocket == INVALID_SOCKET)
		{
			return false;
		}

		/* 记录当前连接进来客户端信息 */
		this->_currConnectAddr._ip = inet_ntoa(connectAddr.sin_addr);
		this->_currConnectAddr._port = htons(connectAddr.sin_port);
		this->_currConnectSocket = connectSocket;

		return true;
	}

	/* 得到自已的套接字 */
	const SOCKET Tcp::GetSocket()
	{
		return this->_st;
	}

	/* 得到自已的地址信息 */
	const sockaddr_in Tcp::GetAddr()
	{
		return this->_addr;
	}

	/* 得到当前连接进来客户端的套接字 */
	const SOCKET Tcp::GetCurrConnectSocket()
	{
		
		return this->_currConnectSocket;
	}

	/* 得到当前连接进来客户端的地址信息 */
	const IPPortPair Tcp::GetCurrConnectAddr()
	{
		return this->_currConnectAddr;
	}

	inline sockaddr_in Tcp::CreateAddr(const char *IP, const unsigned int port)
	{
		sockaddr_in addr;
		memset(&addr, 0, sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		addr.sin_addr.S_un.S_addr = inet_addr(IP);
		return addr;
	}

	bool Tcp::Connect(const char *ip, unsigned int port)
	{
		sockaddr_in sockAddr = CreateAddr(ip, port);
		return (connect(this->_st, (sockaddr*)&sockAddr, sizeof(sockAddr)) == 0);
	}
	bool Tcp::RecvCurrClientMsg(char *buffer, int readN)
	{
		return this->RecvMsg(this->_currConnectSocket, buffer, readN);
	}
	bool Tcp::SendToClientMsg(char *buffer)
	{

		return this->SendToMsg(this->_currConnectSocket, buffer, strlen(buffer));
	}


	bool Tcp::RecvServerMsg(char *buffer)
	{

		return this->RecvMsg(this->_st, buffer, strlen(buffer));
	}
	bool Tcp::SendToServerMsg(char *buffer)
	{
		
		return this->SendToMsg(this->_st, buffer, strlen(buffer));
	}


	bool Tcp::SendToMsg(SOCKET targetSock, char *buffer, int sendN)
	{
		return send(targetSock, buffer, sendN, 0) != -1;
	}
	bool Tcp::RecvMsg(SOCKET sock, char *buffer, int readN)
	{
		int n = recv(sock, buffer, readN - 1, 0);
		if (n > 0)
		{
			buffer[n] = 0;
			return true;
		}
		else 
		{
			return false;
		}
	}

	Tcp::~Tcp(void)
	{
		if (this->_st != INVALID_SOCKET)
		{
			closesocket(this->_st);
		}
		WSACleanup();
	}
}

