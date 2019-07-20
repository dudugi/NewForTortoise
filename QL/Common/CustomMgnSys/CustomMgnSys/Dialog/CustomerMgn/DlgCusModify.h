#pragma once
#include "BCGPDialog.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "Base64Code.h"
#include "ClassEx/EditEx/EditDoubleNum.h"
// CDlgCusModify 客户信息修改对话框 add by lida 2018/08/22
class CDBVCustomerInfoData;
class CDlgBCGGrid;
class CDlgCusModify : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgCusModify)

public:  //公共接口
    void SetCusData(CDBVCustomerInfoData* pCusData);
    BOOL DoSave(CDBVCustomerInfoData* pCusData);   

public:
	CDlgCusModify(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgCusModify();

// 对话框数据
	enum { IDD = IDD_DLG_CUS_MODIFY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
   virtual BOOL OnInitDialog();
   virtual void OnOK();
   virtual void OnCancel();

   void InitDateTimePicker();
   void Cstring2Ip(__in CString strIp,__out BYTE& Field0,__out BYTE& Field1,__out BYTE& Field2,__out BYTE& Field3);
   void Ip2Cstring(__in BYTE Field0,__in BYTE Field1,__in BYTE Field2,__in BYTE Field3,__out CString& strIp);

	DECLARE_MESSAGE_MAP()

   void CopyData2Win(CDBVCustomerInfoData* pCusData);
   BOOL GetDataFromWin(CDBVCustomerInfoData* pCusData);
   void InitComGridDlg();//初始化表格
private:
   CBase64Code       m_base64;

   CBCGPEdit m_edit_CusCode;
   CBCGPEdit m_edit_CusName;
   CBCGPEdit m_edit_Province;
   CBCGPEdit m_edit_Addr;
   CBCGPEdit m_edit_CusContacts;
   CBCGPEdit m_edit_Phone;
   CBCGPEdit m_edit_DBName;
   CBCGPEdit m_edit_DBAccount;
   CBCGPEdit m_edit_DBPwd;
   CEditDoubleNum m_edit_DBPort;
   CBCGPEdit m_edit_PDMVersion;
   CBCGPEdit m_edit_Certification;
   CBCGPEdit m_edit_ModeData;
   CBCGPButton m_check_IsLocalDB;
   CIPAddressCtrl m_ipAddressCtrl;
   CBCGPDateTimeCtrl m_datetimepicker;
   CEditDoubleNum m_Edit_ClientNum;
   CEditDoubleNum m_Edit_ChongZhiJE;
   CBCGPEdit m_Edit_Memo;
   CBCGPEdit m_Edit_ServicePerson;
   CBCGPDateTimeCtrl m_Datetime_Begin;
   CBCGPEdit m_edit_day;

   CDlgBCGGrid*			m_pDlgComGrid;				//新表格控件

   COleDateTime   m_ole_beg;
   COleDateTime   m_ole_end;
public:
   afx_msg void OnSize(UINT nType, int cx, int cy);
   afx_msg void OnBnClickedDatetime();
   virtual BOOL PreTranslateMessage(MSG* pMsg);
};
