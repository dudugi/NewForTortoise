#pragma once
#include "MyCtrlEx\Static\PictureEx.h"


// CDlgLoading �Ի���

class CDlgLoading : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgLoading)

public:
	CDlgLoading(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgLoading();

	CPictureEx	m_ctrLoadingGif;
	BOOL		m_bInitModal;	//����DoModal

// �Ի�������
	enum { IDD = IDD_DLG_LOADING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual INT_PTR DoModal();
};
