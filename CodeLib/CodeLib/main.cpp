#include <iostream>
#include "Udp.h"
#include "Tcp.h"
using namespace LivLib;

int main()
{

	/* ���������� */
	Udp udp;
	udp.BindAddr("127.0.0.1", 7575);

	/* ���ݵ����� */
	IPPortPair ipPort = { 0 };
	char buff[512];
	memset(buff, 0, sizeof(buff));


	while(true)
	{
		if (udp.RecvMsg(buff))
		{
			std::cout << "\n" << buff << std::endl;
		}

	}

	system("pause");
	return 0;
}