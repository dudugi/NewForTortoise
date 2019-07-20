// CMFCDesktopAlertMid: 实现文件
//

#include "stdafx.h"
#include "CMFCDesktopAlertMid.h"


// CCloseMFCTabCtrl

IMPLEMENT_DYNAMIC(CMFCDesktopAlertMid, CMFCDesktopAlertWnd)

CMFCDesktopAlertMid::CMFCDesktopAlertMid()
{

}

CMFCDesktopAlertMid::~CMFCDesktopAlertMid()
{
}

CMFCDesktopAlertDialog *CMFCDesktopAlertMid::GetRuntimeDlg()
{
	ASSERT(m_pWndDlg != NULL);

	return m_pWndDlg;
}