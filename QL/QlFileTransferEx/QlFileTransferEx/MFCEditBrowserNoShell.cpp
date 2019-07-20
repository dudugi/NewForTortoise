// MFCEditBrowserNoShell.cpp : 实现文件
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
	bi.ulFlags = BIF_NEWDIALOGSTYLE;    //窗口可以调整大小，有新建文件夹按钮
	bi.lpszTitle = _T("请选择文件夹");  
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



// CMFCEditBrowserNoShell 消息处理程序


