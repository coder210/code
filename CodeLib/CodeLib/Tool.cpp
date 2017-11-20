/************************************************************************
 CopyRight(C): Izhuemng.win, liv, 2017-2018
 Version: 1.0  Author: liv		Date: 2017.9.29
 Description: ���߿�,�򵥷�װһЩ���õĲ���
 Function:
	ExitWindow: ϵͳ�ػ�����������ز���
	ExecuteCmd: ִ���ն˵�����
	CopyMyself: ����������Ƶ�ϵͳĿ¼��
	OperatRegedit: ��ע�����в���
	Uploader: ��һ����ַ�������ļ�

 Others:
************************************************************************/

#include "Tool.h"

namespace LivLib
{
	
	/************************************************************************
	 Description: ϵͳ�ػ�����������ز���
	 Parameter:
		 (in) operate: ָ���رղ���ϵͳ������
	 Return: bool
	************************************************************************/
	bool Tool::ExitWindow(UINT operate)
	{
		HANDLE hToken;
		TOKEN_PRIVILEGES tkp;

		/* ��Ȩ���� */
		if (! OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
		{
			return (FALSE);
		}

		LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);

		tkp.PrivilegeCount = 1;    
		tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 

		AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0); 
		if (GetLastError() != ERROR_SUCCESS) 
		{
			return FALSE; 
		}

		/* ����ִ���˳�ϵͳ�ĺ��� */
		if (!ExitWindowsEx(operate | EWX_FORCE, 
			SHTDN_REASON_MAJOR_OPERATINGSYSTEM |
			SHTDN_REASON_MINOR_UPGRADE |
			SHTDN_REASON_FLAG_PLANNED)) 
		{

			return FALSE; 
		}

		return TRUE;
	}

	/************************************************************************
	 Description: ִ���ն˵����� 
	 Parameter:
		 (in) cmd: �ն�������ַ��� 
	 Return: void
	************************************************************************/
	void Tool::ExecuteCmd(char cmdBuffer[])
	{
		system(cmdBuffer);
	}

	/************************************************************************
	 Description: ����������Ƶ�ϵͳĿ¼�� 
	 Parameter:
		 (in) copyFileName: ���ƺ�ĳ���������� 
	 Return: void
	************************************************************************/
	void Tool::CopyMyself(const char *copyFileName)
	{
		char myselfPath[MAX_PATH];
		char systemPath[MAX_PATH];

		/* �õ����ѵ�·�� */
		GetModuleFileNameA(NULL, myselfPath, MAX_PATH);
		GetSystemDirectoryA(systemPath, MAX_PATH);

		/* ·��Ҫ����\\ */
		strcat_s(systemPath, "\\");

		/* ���һ������·�� */
		strcat_s(systemPath, copyFileName);

		/* ������ļ����Ƶ����λ���� */
		CopyFileA(myselfPath, systemPath, false);
	}

	/************************************************************************
	 Description: ��ע�����в��� 
	 Parameter:
		mainKey: ע���ĸ���
		lpSubKey: ע�������µ��Ӽ�
		operat: Ҫ��ע�����в���
		itemName: ����
		programFileName: ���ӳ����·��
	 Return: ����true��ʾ�ɹ�,falseʧ��
	************************************************************************/
	bool Tool::OperatRegedit(HKEY mainKey, LPCTSTR lpSubKey, REGSAM operat, LPCSTR itemName, char *programFileName)
	{
		int opeatResult = 0;
		HKEY hKey = { 0 };

		/* ��ע��� */
		opeatResult = RegOpenKeyExA(mainKey, lpSubKey, 0, operat, &hKey);
		/* �޸�ע��� */
		opeatResult = RegSetValueExA(hKey, itemName , 0 ,
								REG_SZ, (BYTE*)programFileName,
								strlen(programFileName));
		/* �ر�ע��� */
		opeatResult = RegCloseKey(hKey);

		return opeatResult == 0;
	}


	/************************************************************************
	 Description: ��һ����ַ�������ļ� 
	 Parameter:
		 (in) loadUrl: ���ص�·��
		 (out) savePath: �����·��
	 Return: void
	************************************************************************/
	void Tool::Uploader(char *loadUrl, char *savePath)
	{
		URLDownloadToFile(nullptr, loadUrl, savePath, 0, nullptr);
	}
}

