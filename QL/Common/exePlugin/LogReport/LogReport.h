
// LogReport.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include "LogCommandLineInfo.h"


// CLogReportApp:
// 有关此类的实现，请参阅 LogReport.cpp
//

class CLogReportApp : public CWinApp
{
public:
	CLogReportApp();


private:
   //信号量句柄
   HANDLE m_hSem;

private:


   //单实例
   BOOL OnlyOneInstance(const CLogCommandLineInfo & cmdInfo);
   //从程序路径获取其对应的句柄
   int GetAppPathFromHwnd(HWND hWnd, CString& AppPath);

   void CustomPraseCommandLine(CLogCommandLineInfo & cmdInfo);

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CLogReportApp theApp;