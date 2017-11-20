#ifndef __TOOL_H__
#define  __TOOL_H__

#include <windows.h>
#include <stdlib.h>
#include <urlmon.h> /* ������Ҫ�õ���ͷ�ļ� */
#pragma comment(lib, "urlmon.lib") 

namespace LivLib
{
	/* ������ */
	class Tool
	{
	public:
		/* �˳�ϵͳ */
		static bool ExitWindow(UINT operate);
		/* ִ��cmd�� */
		static void ExecuteCmd(char cmdBuffer[]);
		/* �������� */
		static void CopyMyself(const char *copyFileName);
		/* ����ע��� */
		static bool OperatRegedit(HKEY mainKey, LPCTSTR lpSubKey, REGSAM operat, LPCSTR itemName, char *programFileName);
		/* ����ַ������ */
		static void Uploader(char *loadUrl, char *savePath);
	};
}

#endif


