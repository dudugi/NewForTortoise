#pragma once

#include "resource.h"
// CDesktopDlg �Ի���

#define WM_DESKTOP_DBCLICK			WM_USER + 0x101	//˫����Ϣ������Ϣ

class CDlgDesktop : CMFCDesktopAlertDialog
{
	DECLARE_DYNCREATE(CDlgDesktop)

public:
	COLORREF m_clrText;
	COLORREF m_clrTitle;	//������ɫ
	CFont m_Font;
	CString m_strText;
	//CDesktopDlg(CWnd* pParent = NULL);   // ��׼���캯��
	WPARAM wParam;
	LPARAM lParam;
	CWnd *pOwerWnd;
	CDlgDesktop(); 
	virtual ~CDlgDesktop();

// �Ի�������
	enum { IDD = IDD_DLG_DESKTOP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnDraw (CDC* pDC);
	virtual BOOL OnInitDialog();


	CMFCToolBarImages	m_imgLogo;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
