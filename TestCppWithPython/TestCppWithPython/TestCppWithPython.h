
// TestCppWithPython.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTestCppWithPythonApp:
// �йش����ʵ�֣������ TestCppWithPython.cpp
//

class CTestCppWithPythonApp : public CWinApp
{
public:
	CTestCppWithPythonApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTestCppWithPythonApp theApp;