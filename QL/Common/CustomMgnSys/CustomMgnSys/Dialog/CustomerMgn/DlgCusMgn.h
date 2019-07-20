#pragma once
#include "BCGPDialog.h"
#include "QLBCG/DlgBCGGrid.h"
#include "afxwin.h"
#include "DB/DBCustomer.h"
// CDlgCusMgn 客户管理对话框 add by lida 2018/08/22

class CDlgCusModify;


class CDlgCusMgn : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgCusMgn)

public:
	CDlgCusMgn(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgCusMgn();

// 对话框数据
	enum { IDD = IDD_DLG_CUS_MGN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
   virtual BOOL OnInitDialog();

   void InitGridCtrl();
   void ShowCusModifyDlg(BOOL bShow,CDBVCustomerInfoData* pCusData);
   void ShowDlgMode(int iFlag);
   void DoRefreshData();
   BOOL CheckDBConnectState();

   DECLARE_MESSAGE_MAP()

private:
   CDlgCusModify*    m_pDlgCusModify;  //客户信息修改
   CDlgBCGGrid*		  m_pDlgComGrid;				//新表格控件

   CDBVCustomerInfoData m_oData;    //当前编辑的客户数据

   CString           m_strTitle;
   int               m_iShowMode;
   BOOL              m_bDoFreshing; //正在刷新数据

   CBCGPButton m_btn_add;
   CBCGPButton m_btn_del;
   CBCGPButton m_btn_modify;
   CBCGPButton m_btn_refresh;
   CBCGPButton m_btn_cancel;
   CBCGPButton m_btn_save;
   CBCGPButton m_btn_expiring;
   CBCGPButton m_btn_expired;
   CBCGPEdit m_edit_days;

   enum {
      en_view = 0,
      en_modify,
   };

public:
   afx_msg void OnSize(UINT nType, int cx, int cy);
   afx_msg void OnBnClickedBtnAdd();
   afx_msg void OnBnClickedBtnDel();
   afx_msg void OnBnClickedBtnModify();
   afx_msg void OnBnClickedBtnRefresh();
   afx_msg void OnBnClickedBtnSave();
   afx_msg void OnBnClickedBtnCancel();
   afx_msg void OnBnClickedBtnExpiration();     //客户到期情况
   afx_msg LRESULT OnLClickedComGridMsg(WPARAM wParam, LPARAM lParam);	//响应网格控件鼠标左键单击的消息
   afx_msg LRESULT OnLDBClickedComGridMsg(WPARAM wParam, LPARAM lParam);	
   afx_msg LRESULT OnRClickedComGridMsg(WPARAM wParam, LPARAM lParam);	
   afx_msg void OnBnClickedBtnExpiring();
   afx_msg void OnBnClickedBtnExpired();
};
