#pragma once

// CMFCDesktopAlertMid
/************************************************************************
 * �������ڣ�2017/04/19     ���ߣ�zhangtao
 * CMFCDesktopAlertWnd�м���
 * ���ࣺCMFCDesktopAlertWnd
 * Ŀ�ģ����Խ����ౣ���ĳ�Ա�����������ӿ��ṩ�ⲿ����
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
		CDesktopDlg��CMFCDesktopAlertDialog������
	*/
	CMFCDesktopAlertDialog *GetRuntimeDlg();//���ʸ��ౣ���ĳ�Ա���� ����RUNTIME_CLASS����ָ��
};


