
// CFileTransClass_DemoDlg.h : ͷ�ļ�
//

#pragma once


// CCFileTransClass_DemoDlg �Ի���
class CCFileTransClass_DemoDlg : public CDialogEx
{
// ����
public:
	CCFileTransClass_DemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CFILETRANSCLASS_DEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
