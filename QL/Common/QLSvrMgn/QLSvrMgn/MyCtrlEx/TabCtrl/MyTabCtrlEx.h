#pragma once


// CMyTabCtrlEx		

#define IDM_CLOSE_CURTAB                1000
#define IDM_CLOSE_OTHERTAB              1001
#define IDM_CLOSE_ALLTAB                1002

class CMyTabCtrlEx : public CMFCTabCtrl
{
	DECLARE_DYNAMIC(CMyTabCtrlEx)

private:
	BOOL m_bSameClick;

public:
	CMyTabCtrlEx();
	virtual ~CMyTabCtrlEx();

	/*******************************************************************
	 * @brief : ���õ�ǰ��ı�ǩҳ
	 * @author : zhangt
	 * @param : pDialog ��ǩҳʵ��
	 * @param : nIDD ��ǩҳID
	 * @param : strCaption ��ǩҳ����
	 * @param : nOperStyle �ñ�ǩִ�еĲ���
	 * @example : 
	 * @return : 
	 *******************************************************************/
	BOOL SetActiveTab(CWnd *pWnd,UINT nIDD,CString strCaption,WPARAM wpData=0);


	void SetTabsHeight();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
   afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnCloseCurTab();
	afx_msg void OnCloseOtherTab();
	afx_msg void OnCloseAllTab();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL SetActiveTab(int iTab);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};


