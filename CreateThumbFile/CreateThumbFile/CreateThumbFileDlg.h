
// CreateThumbFileDlg.h : ͷ�ļ�
//

#pragma once


// CCreateThumbFileDlg �Ի���
class CCreateThumbFileDlg : public CDialogEx
{
// ����
public:
	CCreateThumbFileDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CREATETHUMBFILE_DIALOG };

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
