// MFCEditBrowserNoShell.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QlFileTransferEx.h"
#include "MFCEditBrowserNoShell.h"


// CMFCEditBrowserNoShell

IMPLEMENT_DYNAMIC(CMFCEditBrowserNoShell, CMFCEditBrowseCtrl)

CMFCEditBrowserNoShell::CMFCEditBrowserNoShell()
{

}

CMFCEditBrowserNoShell::~CMFCEditBrowserNoShell()
{
}


void CMFCEditBrowserNoShell::OnBrowse()
{
	switch (m_Mode)
	{
	case BrowseMode_Folder:
	case BrowseMode_File:
		{
			CMFCEditBrowseCtrl::OnBrowse();
			return;
		}
		break;
	}

	BROWSEINFO bi; 
	ZeroMemory(&bi,sizeof(BROWSEINFO));
	bi.ulFlags = BIF_BROWSEINCLUDEFILES; 
	bi.ulFlags = BIF_NEWDIALOGSTYLE;
	bi.ulFlags = BIF_RETURNONLYFSDIRS;
	bi.ulFlags = BIF_NEWDIALOGSTYLE;    //���ڿ��Ե�����С�����½��ļ��а�ť
	bi.lpszTitle = _T("��ѡ���ļ���");  
	bi.hwndOwner = GetSafeHwnd();
	LPITEMIDLIST pidl = SHBrowseForFolder(&bi); 
	TCHAR * path = new TCHAR[MAX_PATH];  
	if(pidl != NULL)  
	{  
		SHGetPathFromIDList(pidl,path);
		CString strPath = path;
		if(NULL != path)
		{
			delete path;
			path = NULL;
		}
		if (!strPath.IsEmpty())
		{
			SetWindowText(strPath);
			return;
		}
	}
	else
	{
		if(NULL != path)
		{
			delete path;
			path = NULL;
		}
		return ;
	}

}

BEGIN_MESSAGE_MAP(CMFCEditBrowserNoShell, CMFCEditBrowseCtrl)
END_MESSAGE_MAP()



// CMFCEditBrowserNoShell ��Ϣ�������


