#ifndef __UDP_H__
#define __UDP_H__

#include <winsock2.h>
#include "IPPortPair.h"
#pragma comment(lib, "Ws2_32.lib")

namespace LivLib 
{
	/* udp�� */
	class Udp
	{
	private:
		SOCKET _st; /* �����׽��� */
		sockaddr_in _addr; /* ���ص�ַ��Ϣ */
		bool _isBind; /* �Ƿ�󶨵ı��ض˿� */

	public:
		/* ��ʼ��udp */
		Udp();
		/* �󶨱���IP���ַ */
		bool BindAddr(const char *IP, const unsigned int port);
		/* ������Ϣ,�ɹ����ط��ͳɹ����ֽ���,ʧ�ܷ���-1 */
	 	int SendToMsg(char *sendIP, const unsigned int sendPort, const char *buffer);
		/* ������Ϣ */
		bool RecvMsg(char *buffer);
		/* ������Ϣ,buffer��recvIp����������� */
		bool RecvMsg(char *buffer, IPPortPair *ipPort);
		/* �õ�����socket */
		const SOCKET GetSocket();
		/* �õ����ѵĵ�ַ */
		const sockaddr_in GetAddr();
		/* �ж��Ƿ�� */
		const bool GetBindState();

		/* �ͷ������Դ */
		~Udp();

	private:
		inline sockaddr_in CreateAddr(const char *sendIP, const unsigned int sendPort);

	};
}

#endif 

