// CMFCDesktopAlertMid: 实现文件
//

#include "stdafx.h"
#include "CMFCDesktopAlertMid.h"
#include "CustomMgnSys.h"


// CCloseMFCTabCtrl

IMPLEMENT_DYNAMIC(CMFCDesktopAlertMid, CBCGPPopupWindow)

CMFCDesktopAlertMid::CMFCDesktopAlertMid()
{

}

CMFCDesktopAlertMid::~CMFCDesktopAlertMid()
{
}

CBCGPPopupDlg *CMFCDesktopAlertMid::GetRuntimeDlg()
{
	//ASSERT(m_pWndDlg != NULL);

	//return m_pWndDlg;

	return GetDlg();
}