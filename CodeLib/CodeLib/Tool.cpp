/************************************************************************
 CopyRight(C): Izhuemng.win, liv, 2017-2018
 Version: 1.0  Author: liv		Date: 2017.9.29
 Description: 工具库,简单封装一些常用的操作
 Function:
	ExitWindow: 系统关机或重启等相关操作
	ExecuteCmd: 执行终端的命令
	CopyMyself: 将本体程序复制到系统目录下
	OperatRegedit: 对注册表进行操作
	Uploader: 从一个网址上下载文件

 Others:
************************************************************************/

#include "Tool.h"

namespace LivLib
{
	
	/************************************************************************
	 Description: 系统关机或重启等相关操作
	 Parameter:
		 (in) operate: 指定关闭操作系统的类型
	 Return: bool
	************************************************************************/
	bool Tool::ExitWindow(UINT operate)
	{
		HANDLE hToken;
		TOKEN_PRIVILEGES tkp;

		/* 提权操作 */
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

		/* 真正执行退出系统的函数 */
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
	 Description: 执行终端的命令 
	 Parameter:
		 (in) cmd: 终端命令的字符串 
	 Return: void
	************************************************************************/
	void Tool::ExecuteCmd(char cmdBuffer[])
	{
		system(cmdBuffer);
	}

	/************************************************************************
	 Description: 将本体程序复制到系统目录下 
	 Parameter:
		 (in) copyFileName: 复制后的程序的新名字 
	 Return: void
	************************************************************************/
	void Tool::CopyMyself(const char *copyFileName)
	{
		char myselfPath[MAX_PATH];
		char systemPath[MAX_PATH];

		/* 得到自已的路径 */
		GetModuleFileNameA(NULL, myselfPath, MAX_PATH);
		GetSystemDirectoryA(systemPath, MAX_PATH);

		/* 路径要加上\\ */
		strcat_s(systemPath, "\\");

		/* 组成一个绝对路径 */
		strcat_s(systemPath, copyFileName);

		/* 将这个文件复制到这个位置上 */
		CopyFileA(myselfPath, systemPath, false);
	}

	/************************************************************************
	 Description: 对注册表进行操作 
	 Parameter:
		mainKey: 注册表的根键
		lpSubKey: 注册表根键下的子键
		operat: 要对注册表进行操作
		itemName: 项名
		programFileName: 链接程序的路径
	 Return: 返回true表示成功,false失败
	************************************************************************/
	bool Tool::OperatRegedit(HKEY mainKey, LPCTSTR lpSubKey, REGSAM operat, LPCSTR itemName, char *programFileName)
	{
		int opeatResult = 0;
		HKEY hKey = { 0 };

		/* 打开注册表 */
		opeatResult = RegOpenKeyExA(mainKey, lpSubKey, 0, operat, &hKey);
		/* 修改注册表 */
		opeatResult = RegSetValueExA(hKey, itemName , 0 ,
								REG_SZ, (BYTE*)programFileName,
								strlen(programFileName));
		/* 关闭注册表 */
		opeatResult = RegCloseKey(hKey);

		return opeatResult == 0;
	}


	/************************************************************************
	 Description: 从一个网址上下载文件 
	 Parameter:
		 (in) loadUrl: 下载的路径
		 (out) savePath: 保存的路径
	 Return: void
	************************************************************************/
	void Tool::Uploader(char *loadUrl, char *savePath)
	{
		URLDownloadToFile(nullptr, loadUrl, savePath, 0, nullptr);
	}
}

