#pragma once

// CMFCDesktopAlertMid
/************************************************************************
 * 创建日期：2017/04/19     作者：zhangtao
 * CMFCDesktopAlertWnd中间类
 * 基类：CMFCDesktopAlertWnd
 * 目的：可以将父类保护的成员及函数作出接口提供外部访问
 ************************************************************************/

class CMFCDesktopAlertMid: public CMFCDesktopAlertWnd
{
	DECLARE_DYNAMIC(CMFCDesktopAlertMid)
public:
	CMFCDesktopAlertMid();
	~CMFCDesktopAlertMid();

	/*
	 * @sample
		pPopup->Create(pWndParent, IDD_DLG_DESKTOP, NULL, 
			ptShowPos, RUNTIME_CLASS(CDesktopDlg));
		CDesktopDlg是CMFCDesktopAlertDialog派生类
	*/
	CMFCDesktopAlertDialog *GetRuntimeDlg();//访问父类保护的成员变量 返回RUNTIME_CLASS类中指针
};


