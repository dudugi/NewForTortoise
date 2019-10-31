
// CreateThumbFile.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "CreateThumbFile.h"
#include "CreateThumbFileDlg.h"
#include <GdiplusInit.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace Gdiplus;


// CCreateThumbFileApp

BEGIN_MESSAGE_MAP(CCreateThumbFileApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CCreateThumbFileApp ����

CCreateThumbFileApp::CCreateThumbFileApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
   m_nGdiplusToken = 0;
}


// Ψһ��һ�� CCreateThumbFileApp ����

CCreateThumbFileApp theApp;


// CCreateThumbFileApp ��ʼ��

BOOL CCreateThumbFileApp::InitInstance()
{
	CWinApp::InitInstance();

   // GDI+ϵͳ��Դ��ʼ��
   //loading �Ի�����ҪGDI+
   GdiplusStartupInput nGdiplusStartupInput;
   GdiplusStartup(&m_nGdiplusToken, &nGdiplusStartupInput, NULL);


	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CCreateThumbFileDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

