#pragma once
#include "BCGPPopupWindow.h"
// CMFCDesktopAlertMid
/************************************************************************
 * �������ڣ�2017/04/19     ���ߣ�zhangtao
 * CMFCDesktopAlertWnd�м���
 * ���ࣺCMFCDesktopAlertWnd
 * Ŀ�ģ����Խ����ౣ���ĳ�Ա�����������ӿ��ṩ�ⲿ����
 ************************************************************************/

class CMFCDesktopAlertMid: public CBCGPPopupWindow
{
	DECLARE_DYNAMIC(CMFCDesktopAlertMid)
public:
	CMFCDesktopAlertMid();
	~CMFCDesktopAlertMid();

	/*
	 * @sample
		pPopup->Create(pWndParent, IDD_DLG_DESKTOP, NULL, 
			ptShowPos, RUNTIME_CLASS(CDesktopDlg));
		CDesktopDlg��CMFCDesktopAlertDialog������
	*/
	CBCGPPopupDlg *GetRuntimeDlg();//���ʸ��ౣ���ĳ�Ա���� ����RUNTIME_CLASS����ָ��
};


