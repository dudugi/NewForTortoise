// TestPythonConsole.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "TestPythonConsole.h"
#include "C:\Users\duchen\AppData\Local\Programs\Python\Python37\include\python.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// 初始化 MFC 并在失败时显示错误
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: 更改错误代码以符合您的需要
			_tprintf(_T("错误: MFC 初始化失败\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: 在此处为应用程序的行为编写代码。

         Py_SetProgramName((const wchar_t *)argv[0]);
         Py_Initialize();
         PyRun_SimpleString("print ('Hello Python!')\n");//此接口可执行字符串形式的代码
         Py_Finalize();
         system("pause");
		}
	}
	else
	{
		// TODO: 更改错误代码以符合您的需要
		_tprintf(_T("错误: GetModuleHandle 失败\n"));
		nRetCode = 1;
	}

	return nRetCode;
}
