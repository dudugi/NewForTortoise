
// BazierDraw.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CBazierDrawApp:
// �йش����ʵ�֣������ BazierDraw.cpp
//

class CBazierDrawApp : public CWinApp
{
public:
	CBazierDrawApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CBazierDrawApp theApp;