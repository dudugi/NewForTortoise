
// TestCppWithPythonDlg.h : ͷ�ļ�
//

#pragma once


// CTestCppWithPythonDlg �Ի���
class CTestCppWithPythonDlg : public CDialogEx
{
// ����
public:
	CTestCppWithPythonDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TESTCPPWITHPYTHON_DIALOG };

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
};
