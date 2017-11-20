#ifndef __TCP_H__
#define __TCP_H__

#include <WinSock2.h>
#include "IPPortPair.h"
#pragma  comment(lib, "WS2_32")

namespace LivLib
{

	/* Tcp服务 */
	class Tcp
	{
	private:
		SOCKET _st; /* 本地套接字 */
		sockaddr_in _addr; /* 本地地址信息 */
		bool _isBind;

		IPPortPair _currConnectAddr; /* 当前连接进来的地址信息 */
		SOCKET _currConnectSocket; /* 当前连接进来的套接字 */

	public:

		Tcp(void);

		/////////////////////////////////服务端
		/* 绑定本地IP与地址 */
		bool BindAddr(const char *IP, const unsigned int port);
		/* 监听连接 */
		bool Accept();
		/* 得到对象socket */
		const SOCKET GetSocket();
		/* 得到自已的地址 */
		const sockaddr_in GetAddr();
		/* 得到当前连接进来客户端的套接字 */
		const SOCKET GetCurrConnectSocket();
		/* 得到当前连接进来客户端的地址信息 */
		const IPPortPair GetCurrConnectAddr();

		/* 接收当前连接进来客户端消息 */
		bool RecvCurrClientMsg(char *buffer, int readN);
		/* 发往最后一个连接上服务器的客户端 */
		bool SendToClientMsg(char *buffer);


		//////////////////////////////////////////////客户端
		bool Connect(const char *ip, unsigned int port);
		bool RecvServerMsg(char *buffer);
		/* 发往服务端 */
		bool SendToServerMsg(char *buffer);

		////////////////////////////////客户端服务端通用
		bool SendToMsg(SOCKET targetSock, char *buffer, int sendN);	
		bool RecvMsg(SOCKET sock, char *buffer, int readN);

		~Tcp(void);
	private:
		inline sockaddr_in CreateAddr(const char *sendIP, const unsigned int sendPort);
	};
}

#endif
