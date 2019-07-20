// DlgCusModify.cpp : 实现文件
//

#include "stdafx.h"
#include "CustomMgnSys.h"
#include "DlgCusModify.h"

#include "DBCustomer.h"
#include "QLBCG/DlgBCGGrid.h"
#include "CGridCtrlTableAttributeOp.h"
#include "DlgGridCtrlTableStyle.h"
#include "DBCusOpRecords.h"
#include "rnstring.h"

// CDlgCusModify 对话框

IMPLEMENT_DYNAMIC(CDlgCusModify, CBCGPDialog)

CDlgCusModify::CDlgCusModify(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CDlgCusModify::IDD, pParent)
{
   m_pDlgComGrid = nullptr;
}

CDlgCusModify::~CDlgCusModify()
{
   if (m_pDlgComGrid)
   {
      delete m_pDlgComGrid;
      m_pDlgComGrid = nullptr;
   }
}

void CDlgCusModify::DoDataExchange(CDataExchange* pDX)
{
   CBCGPDialog::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_EDIT_CusCode, m_edit_CusCode);
   DDX_Control(pDX, IDC_EDIT_NAME, m_edit_CusName);
   DDX_Control(pDX, IDC_EDIT_Province, m_edit_Province);
   DDX_Control(pDX, IDC_EDIT_Addr, m_edit_Addr);
   DDX_Control(pDX, IDC_EDIT_Contacts, m_edit_CusContacts);
   DDX_Control(pDX, IDC_EDIT_Phone, m_edit_Phone);
   DDX_Control(pDX, IDC_EDIT_DbServerName, m_edit_DBName);
   DDX_Control(pDX, IDC_EDIT_DbAccount, m_edit_DBAccount);
   DDX_Control(pDX, IDC_EDIT_DbPassword, m_edit_DBPwd);
   DDX_Control(pDX, IDC_EDIT_DbServerPort, m_edit_DBPort);
   DDX_Control(pDX, IDC_EDIT_PDMVersion, m_edit_PDMVersion);
   DDX_Control(pDX, IDC_EDIT_Person, m_edit_Certification);
   DDX_Control(pDX, IDC_EDIT_ModeData, m_edit_ModeData);
   DDX_Control(pDX, IDC_CHECK_IsLocalDB, m_check_IsLocalDB);
   DDX_Control(pDX, IDC_IPADDRESS1, m_ipAddressCtrl);
   DDX_Control(pDX, IDC_DATETIME_PICKER, m_datetimepicker);
   DDX_Control(pDX, IDC_EDIT_CLIENTNUM, m_Edit_ClientNum);
   DDX_Control(pDX, IDC_EDIT_JINE, m_Edit_ChongZhiJE);
   DDX_Control(pDX, IDC_EDIT_MEMO, m_Edit_Memo);
   DDX_Control(pDX, IDC_EDIT_ServicePerson, m_Edit_ServicePerson);
   DDX_Control(pDX, IDC_DATETIME_BEGIN, m_Datetime_Begin);
   DDX_Control(pDX, IDC_EDIT_DAY, m_edit_day);
}

BOOL CDlgCusModify::OnInitDialog()
{
   CBCGPDialog::OnInitDialog();

   m_edit_DBPort.SetEditDoubleNum(18,0);
   m_Edit_ClientNum.SetEditDoubleNum(18,0);
   m_Edit_ChongZhiJE.SetEditDoubleNum(18,2);

   InitDateTimePicker();
   InitComGridDlg();//初始化表格
   return TRUE; 
}

void CDlgCusModify::InitDateTimePicker()
{
   UINT stateFlags = 0;
   stateFlags |= CBCGPDateTimeCtrl::DTM_DROPCALENDAR;
   stateFlags |= CBCGPDateTimeCtrl::DTM_DATE;
   stateFlags |= CBCGPDateTimeCtrl::DTM_TIME24HBYLOCALE;
   stateFlags |= CBCGPDateTimeCtrl::DTM_SPIN;
   const UINT stateMask = 
      CBCGPDateTimeCtrl::DTM_SPIN |
      CBCGPDateTimeCtrl::DTM_DROPCALENDAR | 
      CBCGPDateTimeCtrl::DTM_DATE |
      CBCGPDateTimeCtrl::DTM_TIME24H |
      CBCGPDateTimeCtrl::DTM_CHECKBOX |
      CBCGPDateTimeCtrl::DTM_TIME | 
      CBCGPDateTimeCtrl::DTM_TIME24HBYLOCALE |
      CBCGPDateTimeCtrl::DTM_SECONDS;
   m_datetimepicker.m_monthFormat = 2;
   m_datetimepicker.SetState (stateFlags, stateMask);
   m_Datetime_Begin.m_monthFormat = 2;
   m_Datetime_Begin.SetState (stateFlags, stateMask);
}

void CDlgCusModify::OnOK()
{
   //CBCGPDialog::OnOK();
}

void CDlgCusModify::OnCancel()
{
   //CBCGPDialog::OnCancel();
}

void CDlgCusModify::SetCusData(CDBVCustomerInfoData* pCusData)
{
   CopyData2Win(pCusData);
   if (m_pDlgComGrid)
   {
      MAP_GridCtrl_AllData map_data;
      if (pCusData->m_nID>0)
      {
         CDBCusOpRecordsList DBList;
         DBList.GetGridDataByCusCode(theApp.m_pADOConn,pCusData->m_strCusCode,map_data);
      }
      m_pDlgComGrid->SetGridDataInfo(map_data);
      m_pDlgComGrid->RefreshGridCtrlInfo();
   } 
}

BOOL CDlgCusModify::DoSave(CDBVCustomerInfoData* pCusData)
{
   return GetDataFromWin(pCusData);
}

BEGIN_MESSAGE_MAP(CDlgCusModify, CBCGPDialog)
   ON_WM_SIZE()
   //ON_BN_CLICKED(IDC_DATETIME_BEGIN, &CDlgCusModify::OnBnClickedDatetime)
   //ON_BN_CLICKED(IDC_DATETIME_PICKER, &CDlgCusModify::OnBnClickedDatetime)
END_MESSAGE_MAP()

void CDlgCusModify::CopyData2Win(CDBVCustomerInfoData* pCusData)
{
   CString strText = _T("");
   if (pCusData)
   {
      if(pCusData->m_nID >0)
      {
         m_edit_CusCode.EnableWindow(FALSE);        
      }
      else
      {
         m_edit_CusCode.EnableWindow(TRUE);        
      }
      m_edit_CusCode.SetWindowText(pCusData->m_strCusCode);
      m_edit_CusName.SetWindowText(pCusData->m_strCusName);
      m_edit_Province.SetWindowText(pCusData->m_strProvince);
      m_edit_Addr.SetWindowText(pCusData->m_strCusAddress);
      m_edit_CusContacts.SetWindowText(pCusData->m_strCusContacts);
      m_edit_Phone.SetWindowText(pCusData->m_strCusPhone);
      m_edit_DBName.SetWindowText(pCusData->m_cDbServerName);
      BYTE Field0,Field1,Field2,Field3;
      Cstring2Ip(pCusData->m_cDbServerIP,Field0,Field1,Field2,Field3);
      m_ipAddressCtrl.SetAddress(Field0,Field1,Field2,Field3);
      m_edit_DBAccount.SetWindowText(pCusData->m_cDbAccount);
      pCusData->m_cDbPassword = m_base64.base64Decode(pCusData->m_cDbPassword);
      m_edit_DBPwd.SetWindowText(pCusData->m_cDbPassword);
      CString strPort;
      strPort.Format(_T("%d"),pCusData->m_iDbServerPort);
      m_edit_DBPort.SetWindowText(strPort);
      m_edit_PDMVersion.SetWindowText(pCusData->m_strcPDMVersion);      
      m_check_IsLocalDB.SetCheck(pCusData->m_isLocalDB==1?TRUE:FALSE);
           
      m_Edit_ChongZhiJE.SetWindowText(_T("0"));//本次充值金额；
      m_Edit_ServicePerson.SetWindowText(pCusData->m_strServerPerson);//服务人员
      m_Edit_Memo.SetWindowText(pCusData->m_strMemo);//备注  

      //加密数据
      CString strBeginTime,strcTime;
      int iyear, imonth, iday;
      strBeginTime = pCusData->m_cBeginTime;
      if (!strBeginTime.IsEmpty())
      {
         CStringA strBeginTimeCSA = RnString::WChar2Char(strBeginTime.GetBuffer());      
         sscanf(strBeginTimeCSA.GetBuffer(),"%d-%d-%d", &iyear, &imonth, &iday);
         COleDateTime beginDate(iyear,imonth,iday,0,0,0);
         m_ole_beg = beginDate;
         m_Datetime_Begin.SetDate(beginDate);
      }

      strcTime = pCusData->m_cTime; 
      if (!strcTime.IsEmpty())
      {
         CStringA strTimeCSA = RnString::WChar2Char(strcTime.GetBuffer());      
         sscanf(strTimeCSA.GetBuffer(),"%d-%d-%d", &iyear, &imonth, &iday);
         COleDateTime date(iyear,imonth,iday,0,0,0);
         m_ole_end = date;
         m_datetimepicker.SetDate(date);
      }   

      m_edit_ModeData.SetWindowText(pCusData->m_cModeData);  
      m_edit_Certification.SetWindowText(pCusData->m_cPerson);

      CString strNum;
      strNum.Format(_T("%d"),pCusData->m_iClientNum);
      m_Edit_ClientNum.SetWindowText(strNum);//客户端数量
   }
   else
   {
      m_edit_CusCode.EnableWindow(TRUE);      
      m_edit_CusCode.SetWindowText(strText);
      m_edit_CusName.SetWindowText(strText);
      m_edit_Province.SetWindowText(strText);
      m_edit_Addr.SetWindowText(strText);
      m_edit_CusContacts.SetWindowText(strText);
      m_edit_Phone.SetWindowText(strText);
      m_edit_DBName.SetWindowText(strText);
      m_ipAddressCtrl.ClearAddress();
      m_edit_DBAccount.SetWindowText(strText);
      m_edit_DBPwd.SetWindowText(strText);
      m_edit_DBPort.SetWindowText(strText);
      m_edit_PDMVersion.SetWindowText(strText);
      
      m_check_IsLocalDB.SetCheck(FALSE);      
      m_Edit_ChongZhiJE.SetWindowText(_T("0"));     
      m_Edit_Memo.SetWindowText(strText);
      m_Edit_ServicePerson.SetWindowText(strText);

      m_datetimepicker.SetWindowText(strText);
      m_edit_Certification.SetWindowText(strText);
      m_edit_ModeData.SetWindowText(strText);
      m_Datetime_Begin.SetWindowText(strText);
      m_Edit_ClientNum.SetWindowText(strText);
   }
}

BOOL CDlgCusModify::GetDataFromWin(CDBVCustomerInfoData* pCusData)
{
   if (pCusData)
   {
      m_edit_CusCode.GetWindowText(pCusData->m_strCusCode);
      m_edit_CusName.GetWindowText(pCusData->m_strCusName);
      m_edit_Province.GetWindowText(pCusData->m_strProvince);
      m_edit_Addr.GetWindowText(pCusData->m_strCusAddress);
      m_edit_CusContacts.GetWindowText(pCusData->m_strCusContacts);
      m_edit_Phone.GetWindowText(pCusData->m_strCusPhone);
      m_edit_DBName.GetWindowText(pCusData->m_cDbServerName);
      BYTE Field0,Field1,Field2,Field3;
      m_ipAddressCtrl.GetAddress(Field0,Field1,Field2,Field3);
      Ip2Cstring(Field0,Field1,Field2,Field3,pCusData->m_cDbServerIP);
      m_edit_DBAccount.GetWindowText(pCusData->m_cDbAccount);
      m_edit_DBPwd.GetWindowText(pCusData->m_cDbPassword);
      pCusData->m_cDbPassword = m_base64.base64Encode(pCusData->m_cDbPassword);
      CString strPort;
      m_edit_DBPort.GetWindowText(strPort);
      pCusData->m_iDbServerPort = _ttoi(strPort);
      m_edit_PDMVersion.GetWindowText(pCusData->m_strcPDMVersion);
      pCusData->m_isLocalDB = m_check_IsLocalDB.GetCheck();          
     

      //服务人员
      m_Edit_ServicePerson.GetWindowText(pCusData->m_strServerPerson);
      //备注
      m_Edit_Memo.GetWindowText(pCusData->m_strMemo);      

      //本次充值金额
      CString strfJE;
      m_Edit_ChongZhiJE.GetWindowText(strfJE);
      pCusData->m_fChongZhiJE = _ttof(strfJE);

      CString strBeginTime=_T(""),strcTime=_T("");
      strBeginTime = m_Datetime_Begin.ToString();
      strBeginTime.Replace(_T("/"),_T("-"));
      pCusData->m_cBeginTime = strBeginTime;
      strcTime = m_datetimepicker.ToString();
      strcTime.Replace(_T("/"),_T("-"));
      pCusData->m_cTime = strcTime;
      m_edit_Certification.GetWindowText(pCusData->m_cPerson);
      m_edit_ModeData.GetWindowText(pCusData->m_cModeData); 
      //客户端数量
      CString strClientNum;
      m_Edit_ClientNum.GetWindowText(strClientNum);
      pCusData->m_iClientNum = _ttoi(strClientNum);
      //加密操作yangjr 2018/8/30
      if(!pCusData->EncryptString(&theApp.m_LDK))
      {         
          return FALSE;
      }   
   }
   return TRUE;
}

void CDlgCusModify::Cstring2Ip(__in CString strIp,__out BYTE& Field0,__out BYTE& Field1,__out BYTE& Field2,__out BYTE& Field3)
{ 
   char str[1024];
   wsprintfA(str,"%ls",strIp); 
   DWORD dwIp;
   dwIp = inet_addr(str);
   unsigned char* pIP = (unsigned char*)&dwIp;
   Field0 = *pIP;
   Field1 = *(pIP+1);
   Field2 = *(pIP+2);
   Field3 = *(pIP+3);
}

void CDlgCusModify::Ip2Cstring(__in BYTE Field0,__in BYTE Field1,__in BYTE Field2,__in BYTE Field3,__out CString& strIp)
{
   strIp.Format(_T("%u.%u.%u.%u"),Field0,Field1,Field2,Field3);
}


// CDlgCusModify 消息处理程序

void CDlgCusModify::OnSize(UINT nType, int cx, int cy)
{
   CBCGPDialog::OnSize(nType, cx, cy);
  
   auto pPic = GetDlgItem(IDC_STATIC_RECORDS);
   if (!pPic || !IsWindow(pPic->GetSafeHwnd()))
   {
      return;
   }
   CRect dlgRect;
   GetClientRect(dlgRect);
   CRect rt;
   pPic->GetWindowRect(rt); 
   ScreenToClient(&rt);
   int iTop = rt.bottom +5;
   if (m_pDlgComGrid)
   {
      m_pDlgComGrid->SetWindowPos(NULL ,rt.left,iTop , dlgRect.right-5, dlgRect.Height()-iTop, SWP_SHOWWINDOW); 
   }    
}

void CDlgCusModify::InitComGridDlg()//初始化表格
{
   S_GridCtrl_TableAttri attri;
   if(!CGridCtrlTableAttributeOp::Instance()->ReadTableAttri(TABLE_CUSMGN_OPRECORDS,attri))
   {
      TRACE(_T("CDlgCusModify:Failed\n"));
   }	
   //新表格控件，封装的数据
   MAP_GridCtrl_AllData data ;
   if (NULL != m_pDlgComGrid)
   {
      delete m_pDlgComGrid;
      m_pDlgComGrid = NULL;
   }
   m_pDlgComGrid = new CDlgBCGGrid;

   if (!IsWindow(m_pDlgComGrid->GetSafeHwnd()))
   {
      m_pDlgComGrid->Create(CDlgBCGGrid::IDD,this);
   }

   //设置初始化数据
   m_pDlgComGrid->SetGridAttriAndDatas(attri,data);
   m_pDlgComGrid->RefreshGridCtrlInfo();

   //设置打印导出title
   m_pDlgComGrid->SetWindowText(_T("客户信息操作日志"));
   //设置表格样式xml文件名
   m_pDlgComGrid->SetTableStyleFileName(TABLE_CUSMGN_OPRECORDS);
}

void CDlgCusModify::OnBnClickedDatetime()
{
   DATE date_beg = m_Datetime_Begin.GetDate();
   DATE date_end = m_datetimepicker.GetDate();
   
   COleDateTime ole_beg(date_beg);
   COleDateTime ole_end(date_end);
   COleDateTimeSpan ole_span = ole_end-ole_beg;
   CString strDays;
   strDays.Format(_T("%d"),ole_span.GetDays());
   //m_edit_day.SetWindowText(strDays);
}


BOOL CDlgCusModify::PreTranslateMessage(MSG* pMsg)
{
   if (pMsg->message == WM_KEYDOWN)
   {
      if (pMsg->wParam==VK_RETURN)
      {
         if (pMsg->hwnd == m_edit_day.GetSafeHwnd())
         {
            CString strDays;
            m_edit_day.GetWindowText(strDays);
            int iDays = _ttoi(strDays);
            COleDateTime ole_end(m_ole_end);
            ole_end += COleDateTimeSpan(iDays,0,0,0);
            m_datetimepicker.SetDate(ole_end);
         }
      }
   }
   return CBCGPDialog::PreTranslateMessage(pMsg);
}
