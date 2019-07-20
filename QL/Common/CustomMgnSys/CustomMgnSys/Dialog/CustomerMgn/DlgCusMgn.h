#pragma once
#include "BCGPDialog.h"
#include "QLBCG/DlgBCGGrid.h"
#include "afxwin.h"
#include "DB/DBCustomer.h"
// CDlgCusMgn �ͻ�����Ի��� add by lida 2018/08/22

class CDlgCusModify;


class CDlgCusMgn : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgCusMgn)

public:
	CDlgCusMgn(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgCusMgn();

// �Ի�������
	enum { IDD = IDD_DLG_CUS_MGN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
   virtual BOOL OnInitDialog();

   void InitGridCtrl();
   void ShowCusModifyDlg(BOOL bShow,CDBVCustomerInfoData* pCusData);
   void ShowDlgMode(int iFlag);
   void DoRefreshData();
   BOOL CheckDBConnectState();

   DECLARE_MESSAGE_MAP()

private:
   CDlgCusModify*    m_pDlgCusModify;  //�ͻ���Ϣ�޸�
   CDlgBCGGrid*		  m_pDlgComGrid;				//�±��ؼ�

   CDBVCustomerInfoData m_oData;    //��ǰ�༭�Ŀͻ�����

   CString           m_strTitle;
   int               m_iShowMode;
   BOOL              m_bDoFreshing; //����ˢ������

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
   afx_msg void OnBnClickedBtnExpiration();     //�ͻ��������
   afx_msg LRESULT OnLClickedComGridMsg(WPARAM wParam, LPARAM lParam);	//��Ӧ����ؼ���������������Ϣ
   afx_msg LRESULT OnLDBClickedComGridMsg(WPARAM wParam, LPARAM lParam);	
   afx_msg LRESULT OnRClickedComGridMsg(WPARAM wParam, LPARAM lParam);	
   afx_msg void OnBnClickedBtnExpiring();
   afx_msg void OnBnClickedBtnExpired();
};
