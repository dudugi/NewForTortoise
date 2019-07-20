#pragma once

#include "resource.h"
// CDesktopDlg 对话框

#define WM_DESKTOP_DBCLICK			WM_USER + 0x101	//双击消息框发送消息

class CDlgDesktop : CMFCDesktopAlertDialog
{
	DECLARE_DYNCREATE(CDlgDesktop)

public:
	COLORREF m_clrText;
	COLORREF m_clrTitle;	//标题颜色
	CFont m_Font;
	CString m_strText;
	//CDesktopDlg(CWnd* pParent = NULL);   // 标准构造函数
	WPARAM wParam;
	LPARAM lParam;
	CWnd *pOwerWnd;
	CDlgDesktop(); 
	virtual ~CDlgDesktop();

// 对话框数据
	enum { IDD = IDD_DLG_DESKTOP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnDraw (CDC* pDC);
	virtual BOOL OnInitDialog();


	CMFCToolBarImages	m_imgLogo;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
