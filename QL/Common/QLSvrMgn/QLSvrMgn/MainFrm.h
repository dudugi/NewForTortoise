// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://msdn.microsoft.com/officeui��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// MainFrm.h : CMainFrame ��Ľӿ�
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
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:
     BOOL SetStatusBarPane(int nIndex,CString strText);
// ����
public:
	
// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
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
	NOTIFYICONDATA m_nid;  //����

// ���ɵ���Ϣӳ�亯��
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


