
// TestDragFileFromClipboardDlg.h : ͷ�ļ�
//

#pragma once


// CTestDragFileFromClipboardDlg �Ի���
class CTestDragFileFromClipboardDlg : public CDialogEx
{
// ����
public:
	CTestDragFileFromClipboardDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TESTDRAGFILEFROMCLIPBOARD_DIALOG };

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
   afx_msg void OnBnClickedButton1();
};