
// CreateThumbFile.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCreateThumbFileApp:
// �йش����ʵ�֣������ CreateThumbFile.cpp
//

class CCreateThumbFileApp : public CWinApp
{
public:
	CCreateThumbFileApp();
   ULONG_PTR m_nGdiplusToken;			//GDI+
// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCreateThumbFileApp theApp;