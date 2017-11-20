#ifndef __TCP_H__
#define __TCP_H__

#include <WinSock2.h>
#include "IPPortPair.h"
#pragma  comment(lib, "WS2_32")

namespace LivLib
{

	/* Tcp���� */
	class Tcp
	{
	private:
		SOCKET _st; /* �����׽��� */
		sockaddr_in _addr; /* ���ص�ַ��Ϣ */
		bool _isBind;

		IPPortPair _currConnectAddr; /* ��ǰ���ӽ����ĵ�ַ��Ϣ */
		SOCKET _currConnectSocket; /* ��ǰ���ӽ������׽��� */

	public:

		Tcp(void);

		/////////////////////////////////�����
		/* �󶨱���IP���ַ */
		bool BindAddr(const char *IP, const unsigned int port);
		/* �������� */
		bool Accept();
		/* �õ�����socket */
		const SOCKET GetSocket();
		/* �õ����ѵĵ�ַ */
		const sockaddr_in GetAddr();
		/* �õ���ǰ���ӽ����ͻ��˵��׽��� */
		const SOCKET GetCurrConnectSocket();
		/* �õ���ǰ���ӽ����ͻ��˵ĵ�ַ��Ϣ */
		const IPPortPair GetCurrConnectAddr();

		/* ���յ�ǰ���ӽ����ͻ�����Ϣ */
		bool RecvCurrClientMsg(char *buffer, int readN);
		/* �������һ�������Ϸ������Ŀͻ��� */
		bool SendToClientMsg(char *buffer);


		//////////////////////////////////////////////�ͻ���
		bool Connect(const char *ip, unsigned int port);
		bool RecvServerMsg(char *buffer);
		/* ��������� */
		bool SendToServerMsg(char *buffer);

		////////////////////////////////�ͻ��˷����ͨ��
		bool SendToMsg(SOCKET targetSock, char *buffer, int sendN);	
		bool RecvMsg(SOCKET sock, char *buffer, int readN);

		~Tcp(void);
	private:
		inline sockaddr_in CreateAddr(const char *sendIP, const unsigned int sendPort);
	};
}

#endif
