
// TestChinesePinYinSearch.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTestChinesePinYinSearchApp:
// �йش����ʵ�֣������ TestChinesePinYinSearch.cpp
//

class CTestChinesePinYinSearchApp : public CWinApp
{
public:
	CTestChinesePinYinSearchApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTestChinesePinYinSearchApp theApp;