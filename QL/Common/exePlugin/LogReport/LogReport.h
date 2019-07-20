
// LogReport.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "LogCommandLineInfo.h"


// CLogReportApp:
// �йش����ʵ�֣������ LogReport.cpp
//

class CLogReportApp : public CWinApp
{
public:
	CLogReportApp();


private:
   //�ź������
   HANDLE m_hSem;

private:


   //��ʵ��
   BOOL OnlyOneInstance(const CLogCommandLineInfo & cmdInfo);
   //�ӳ���·����ȡ���Ӧ�ľ��
   int GetAppPathFromHwnd(HWND hWnd, CString& AppPath);

   void CustomPraseCommandLine(CLogCommandLineInfo & cmdInfo);

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CLogReportApp theApp;