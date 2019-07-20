#pragma once
#include "MyCtrlEx\Static\PictureEx.h"


// CDlgLoading 对话框

class CDlgLoading : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgLoading)

public:
	CDlgLoading(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgLoading();

	CPictureEx	m_ctrLoadingGif;
	BOOL		m_bInitModal;	//进入DoModal

// 对话框数据
	enum { IDD = IDD_DLG_LOADING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual INT_PTR DoModal();
};
