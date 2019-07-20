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

// QLSvrMgnView.h : CQLSvrMgnView 类的接口
//

#pragma once

#include "resource.h"
#include "MyCtrlEx/TabCtrl/MyTabCtrlEx.h"
#include "DlgWelcome.h"
#include "Factory/CDlgFactory.h"
#include "QLSvrMgnDoc.h"


class CQLSvrMgnView : public CFormView
{
protected: // 仅从序列化创建
	CQLSvrMgnView();
	DECLARE_DYNCREATE(CQLSvrMgnView)
	void InitMyTabCtrl();

private:
	CMyTabCtrlEx m_ctrMyTabCtrl;
	CDlgFactory m_dlgFactory;

	//欢迎
	CDlgWelcome m_DlgWelcome;
public:
	enum{ IDD = IDD_QLSVRMGN_FORM };

// 特性
public:
	CQLSvrMgnDoc* GetDocument() const;	

// 操作
public:
	void OnActiveTabDlg(int nMenuID,WPARAM wpData);
   static UINT DealWork(LPVOID pParam);

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CQLSvrMgnView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // QLSvrMgnView.cpp 中的调试版本
inline CQLSvrMgnDoc* CQLSvrMgnView::GetDocument() const
   { return reinterpret_cast<CQLSvrMgnDoc*>(m_pDocument); }
#endif

