
// CFileTransClass_Demo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCFileTransClass_DemoApp:
// �йش����ʵ�֣������ CFileTransClass_Demo.cpp
//

class CCFileTransClass_DemoApp : public CWinApp
{
public:
	CCFileTransClass_DemoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCFileTransClass_DemoApp theApp;