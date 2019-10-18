
// TestDragFileFromClipboardDlg.h : ͷ�ļ�
//

#pragma once
#include <list>


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
   BOOL HasClipFile();
   BOOL GetClipFilePaths(std::list<CString> *pListPaths);
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
   afx_msg void OnBnClickedButton1();
   afx_msg void OnBnClickedBtnTesthasclipfile();
   afx_msg void OnDropFiles(HDROP hDropInfo);

   BOOL GetDropFilePaths(HDROP hDropInfo, std::list<CString> *pListPaths);
};
