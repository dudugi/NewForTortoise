// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// MainFrm.h : CMainFrame 类的接口
//

#pragma once
#include "CalendarBar.h"
#include "Resource.h"
#include "MyCtrlEx/RibbonBar/MyRibbonBar.h"
#include "MyCtrlEx/Outlook/MyOutlookBar.h"
#include "MyCtrlEx/CaptionBar/MyCaptionBar.h"
#include "MyCtrlEx/RibbonApplicationButton/MyRibbonApplicationButton.h"
#include "MyCtrlEx/StatusBar/MyStatusBar.h"

//#define USING_RIB_CAPTION

#define  WM_BACKUP_D WM_USER+1

class CMainFrame : public CFrameWndEx
{
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:
     BOOL SetStatusBarPane(int nIndex,CString strText);
// 操作
public:
	
// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
#ifdef USING_RIB_CAPTION
	CMyRibbonBar		m_wndRibbonBar;
	CMyRibbonStatusBar  m_wndStatusBar;
#else
	CMFCMenuBar			m_wndMenuBar;
	CMyStatusBar		m_wndStatusBar;
#endif 
	CMyOutlookBar       m_wndNavigationBar;
	CMyCaptionBar		m_wndCaptionBar;
	CMyRibbonApplicationButton m_MainButton;
	CMyOutlookBarPane	m_wndRibbonBarPane1;
	CMyOutlookBarPane	m_wndRibbonBarPane2;

	CMFCToolBarImages m_PanelImages;
	CMFCShellTreeCtrl m_wndTree;
	CCalendarBar      m_wndCalendar;
	NOTIFYICONDATA m_nid;  //托盘

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	afx_msg void OnViewCaptionBar();
	afx_msg void OnUpdateViewCaptionBar(CCmdUI* pCmdUI);
	afx_msg void OnOptions();

	afx_msg void OnComdPaneItem();

	

	DECLARE_MESSAGE_MAP()

	BOOL CreateOutlookBar(CMyOutlookBar& bar, UINT uiID, CMyOutlookBarPane *pOutlookBarPane1,CMyOutlookBarPane *pOutlookBarPane2,int nInitialWidth);
	//BOOL CreateOutlookBar(CMyOutlookBar& bar, UINT uiID, CMFCShellTreeCtrl& tree, CCalendarBar& calendar, int nInitialWidth);
	BOOL CreateCaptionBar();

	int FindFocusedOutlookWnd(CMFCOutlookBarTabCtrl** ppOutlookWnd);

	CMFCOutlookBarTabCtrl* FindOutlookParent(CWnd* pWnd);
	CMFCOutlookBarTabCtrl* m_pCurrOutlookWnd;
	CMFCOutlookBarPane*    m_pCurrOutlookPage;
	virtual void OnUpdateFrameTitle(BOOL bAddToTitle);
	virtual void OnUpdateFrameMenu(HMENU hMenuAlt);
   void InitTray();
public:
	afx_msg void OnClose();
protected:
   afx_msg LRESULT OnAdoconnMsg(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnTrayMsg(WPARAM wParam, LPARAM lParam);
   afx_msg void OnExit();
};


