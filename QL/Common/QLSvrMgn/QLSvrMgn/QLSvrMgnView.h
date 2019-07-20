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

// QLSvrMgnView.h : CQLSvrMgnView ��Ľӿ�
//

#pragma once

#include "resource.h"
#include "MyCtrlEx/TabCtrl/MyTabCtrlEx.h"
#include "DlgWelcome.h"
#include "Factory/CDlgFactory.h"
#include "QLSvrMgnDoc.h"


class CQLSvrMgnView : public CFormView
{
protected: // �������л�����
	CQLSvrMgnView();
	DECLARE_DYNCREATE(CQLSvrMgnView)
	void InitMyTabCtrl();

private:
	CMyTabCtrlEx m_ctrMyTabCtrl;
	CDlgFactory m_dlgFactory;

	//��ӭ
	CDlgWelcome m_DlgWelcome;
public:
	enum{ IDD = IDD_QLSVRMGN_FORM };

// ����
public:
	CQLSvrMgnDoc* GetDocument() const;	

// ����
public:
	void OnActiveTabDlg(int nMenuID,WPARAM wpData);
   static UINT DealWork(LPVOID pParam);

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CQLSvrMgnView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnConfigure();
   afx_msg void OnUpdateAutoStart(CCmdUI *pCmdUI);
   afx_msg void OnUpdateAutoStartHide(CCmdUI *pCmdUI);
   afx_msg void OnAutoStart();
   afx_msg void OnAutoStartHide();
};

#ifndef _DEBUG  // QLSvrMgnView.cpp �еĵ��԰汾
inline CQLSvrMgnDoc* CQLSvrMgnView::GetDocument() const
   { return reinterpret_cast<CQLSvrMgnDoc*>(m_pDocument); }
#endif

