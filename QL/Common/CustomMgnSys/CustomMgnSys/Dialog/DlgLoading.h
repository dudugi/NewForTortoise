#pragma once
#include "PictureEx.h"

// CDlgLoading dialog

class CDlgLoading : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgLoading)

public:
	CDlgLoading(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgLoading();

// Dialog Data
	enum { IDD = IDD_DLG_LOADING };

private:
   CPictureEx	m_ctrLoadingGif;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
   virtual BOOL OnInitDialog();
   afx_msg void OnSize(UINT nType, int cx, int cy);
};
