
// MyEqual.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMyEqualApp:
// �йش����ʵ�֣������ MyEqual.cpp
//

class CMyEqualApp : public CWinApp
{
public:
	CMyEqualApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMyEqualApp theApp;