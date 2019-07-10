
// BazierDrawDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CBazierDrawDlg �Ի���
class CBazierDrawDlg : public CDialogEx
{
// ����
public:
	CBazierDrawDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_BAZIERDRAW_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
   CPoint m_ptMiddlePoint;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
   void OnMouseMove(UINT nFlags, CPoint point);
public:
   CEdit m_editResult;
   CButton m_chkReduceFirst;

   afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
   afx_msg void OnBnClickedChkReduceFirst();
   CEdit m_editFZCount;
   CEdit m_editTotalNeedle;
   CEdit m_editTotalRevolution;
   CEdit m_editTolerance;
   CEdit m_editPixelPerSquare;
   CEdit m_editPixelPerY;
   // ��������
   CButton m_chkSegLimit;
   afx_msg void OnBnClickedChkSegLimit();
   CEdit m_editSegLimit;
   CEdit m_editFixX;
   CEdit m_editFixY;
   CButton m_chkFixPos;
   afx_msg void OnBnClickedChkFixPos();
};
