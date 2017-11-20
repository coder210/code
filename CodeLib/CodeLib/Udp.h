#ifndef __UDP_H__
#define __UDP_H__

#include <winsock2.h>
#include "IPPortPair.h"
#pragma comment(lib, "Ws2_32.lib")

namespace LivLib 
{
	/* udp类 */
	class Udp
	{
	private:
		SOCKET _st; /* 本地套接字 */
		sockaddr_in _addr; /* 本地地址信息 */
		bool _isBind; /* 是否绑定的本地端口 */

	public:
		/* 初始化udp */
		Udp();
		/* 绑定本地IP与地址 */
		bool BindAddr(const char *IP, const unsigned int port);
		/* 发送消息,成功返回发送成功的字节数,失败返回-1 */
	 	int SendToMsg(char *sendIP, const unsigned int sendPort, const char *buffer);
		/* 接收消息 */
		bool RecvMsg(char *buffer);
		/* 接收消息,buffer与recvIp都是输出参数 */
		bool RecvMsg(char *buffer, IPPortPair *ipPort);
		/* 得到对象socket */
		const SOCKET GetSocket();
		/* 得到自已的地址 */
		const sockaddr_in GetAddr();
		/* 判断是否绑定 */
		const bool GetBindState();

		/* 释放相关资源 */
		~Udp();

	private:
		inline sockaddr_in CreateAddr(const char *sendIP, const unsigned int sendPort);

	};
}

#endif 

