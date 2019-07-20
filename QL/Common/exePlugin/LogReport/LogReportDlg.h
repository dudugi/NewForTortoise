
// LogReportDlg.h : ͷ�ļ�
//

#pragma once


// CLogReportDlg �Ի���
class CLogReportDlg : public CDialogEx
{
// ����
public:
	CLogReportDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_LOGREPORT_DIALOG };

private:
   DWORD m_dwtick;

protected:
   //��ղ�������
   void ClearUp();

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
   afx_msg void OnClose();
protected:
   afx_msg LRESULT OnLogLocalSwap(WPARAM wParam, LPARAM lParam);
public:
   afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
   afx_msg void OnBnClickedBtnClear();
   afx_msg void OnClear();
};
