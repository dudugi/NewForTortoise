// DlgCreateSqlScript.cpp : 实现文件
//

#include "stdafx.h"
#include "QLSvrMgn.h"
#include "DlgCreateSqlScript.h"
#include "afxdialogex.h"


// CDlgCreateSqlScript 对话框

IMPLEMENT_DYNAMIC(CDlgCreateSqlScript, CTabDialog)

CDlgCreateSqlScript::CDlgCreateSqlScript(CWnd* pParent /*=NULL*/)
	: CTabDialog(CDlgCreateSqlScript::IDD, pParent)
{

}

CDlgCreateSqlScript::~CDlgCreateSqlScript()
{
}

void CDlgCreateSqlScript::DoDataExchange(CDataExchange* pDX)
{
   CTabDialog::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_IPADDRESS1, m_IpAddress);
   DDX_Control(pDX, IDC_IPADDRESS2, m_IpAddress2);
   DDX_Control(pDX, IDC_EDIT_PORT, m_edit_port);
   DDX_Control(pDX, IDC_EDIT_PORT2, m_edit_port2);
   DDX_Control(pDX, IDC_EDIT_DBNAME, m_edit_dbname);
   DDX_Control(pDX, IDC_EDIT_DBNAME2, m_edit_dbname2);
   DDX_Control(pDX, IDC_EDIT_ACCOUNT, m_edit_dbaccount);
   DDX_Control(pDX, IDC_EDIT_ACCOUNT2, m_edit_dbaccount2);
   DDX_Control(pDX, IDC_EDIT_PWD, m_edit_dbpwd);
   DDX_Control(pDX, IDC_EDIT_PWD2, m_edit_dbpwd2);
   DDX_Control(pDX, IDC_EDIT_FILE_PATH, m_edit_file_path);
}


BEGIN_MESSAGE_MAP(CDlgCreateSqlScript, CTabDialog)
   ON_BN_CLICKED(IDC_BUTTON_FILE, &CDlgCreateSqlScript::OnBnClickedButtonFile)
   ON_BN_CLICKED(IDC_BUTTON_CREATE_SCRIPT, &CDlgCreateSqlScript::OnBnClickedButtonCreateScript)
   ON_BN_CLICKED(IDC_BTN_TEST_CONNECT, &CDlgCreateSqlScript::OnBnClickedBtnTestConnect)
END_MESSAGE_MAP()


// CDlgCreateSqlScript 消息处理程序

void CDlgCreateSqlScript::OnBnClickedButtonFile()
{
   CString strDefPath = _T("");
   GetDlgItemText(IDC_SAVE_DATABASE_EDIT,strDefPath);

   CString strFilter = _T("文件(*.sql)|*.sql||");
   CString strNewPath =_T("");
   COleDateTime CurrentTime=COleDateTime::GetCurrentTime();
   CString strFile = _T("");
   strFile.Format(_T("%d_%d_%d_%d时%d分_diff.sql") ,CurrentTime.GetYear(), CurrentTime.GetMonth(),CurrentTime.GetDay(), CurrentTime.GetHour(), CurrentTime.GetMinute());  

   if (m_CDirectroy.OpenDirFile(strNewPath,strDefPath,strFile,strFilter,FALSE))
   {
      SetDlgItemText(IDC_EDIT_FILE_PATH, strNewPath);
   }
}

void CDlgCreateSqlScript::OnBnClickedButtonCreateScript()
{
   CString strFilePath;
   GetDlgItemText(IDC_EDIT_FILE_PATH,strFilePath);
   if (strFilePath.IsEmpty())
   {
      AfxMessageBox(_T("请选择文件"));
      return;
   }


   GetDlgItem(IDC_BTN_TEST_CONNECT)->EnableWindow(FALSE);
   GetDlgItem(IDC_BUTTON_CREATE_SCRIPT)->EnableWindow(FALSE);

   m_map_db_attri_dst.clear();
   m_map_db_attri_src.clear();

   BOOL bRet1 = bConnectDB_src();
   if (bRet1)
   {
      m_ado_src.GetRecordSet(SQL_SELECT);
      while (!m_ado_src.adoEOF())
      {
         tag_db_attri o_data;
         GetAllValue(&m_ado_src,o_data);
         Add2MapAttri(m_map_db_attri_src,o_data);
         m_ado_src.MoveNext();
      }
      //m_ado_src.CloseConnect();
   }
   else
   {
      m_map_db_attri_dst.clear();
      m_map_db_attri_src.clear();
      return;
   }
   BOOL bRet2 = bConnectDB_dst();
   if (bRet2)
   {
      m_ado_dst.GetRecordSet(SQL_SELECT);
      while (!m_ado_dst.adoEOF())
      {
         tag_db_attri o_data;
         GetAllValue(&m_ado_dst,o_data);
         Add2MapAttri(m_map_db_attri_dst,o_data);
         m_ado_dst.MoveNext();
      }
      //m_ado_dst.CloseConnect();
   }
   else
   {
      m_map_db_attri_dst.clear();
      m_map_db_attri_src.clear();
      return;
   }
   CString strDBName2;
   m_edit_dbname2.GetWindowText(strDBName2);
   CreateSqlScript(strDBName2,m_map_db_attri_src,m_map_db_attri_dst,m_map_sql_script);
   WriteSql2File(strFilePath,m_map_sql_script);
   AfxMessageBox(_T("生成脚本成功！"));

   GetDlgItem(IDC_BTN_TEST_CONNECT)->EnableWindow(TRUE);
   GetDlgItem(IDC_BUTTON_CREATE_SCRIPT)->EnableWindow(TRUE);
}

void CDlgCreateSqlScript::OnBnClickedBtnTestConnect()
{
   BOOL bRet1 = bConnectDB_src();
   BOOL bRet2 = bConnectDB_dst();
   if (bRet1 && bRet2)
   {
      AfxMessageBox(_T("连接成功"));
   }
}

BOOL CDlgCreateSqlScript::bConnectDB_src()
{
   m_db_info_src;
   m_IpAddress.GetWindowText(m_db_info_src.strIp);
   m_edit_dbname.GetWindowText(m_db_info_src.strDbName);
   m_edit_dbaccount.GetWindowText(m_db_info_src.strDbAccount);
   m_edit_dbpwd.GetWindowText(m_db_info_src.strDbPassword);
   m_edit_port.GetWindowText(m_db_info_src.strPort);
   CString strConnectInfo = m_ado_src.CreateConncetSqlStrByDecodeParam(m_db_info_src.strIp+_T(",")+m_db_info_src.strPort,
      m_db_info_src.strDbName,m_db_info_src.strDbAccount,m_db_info_src.strDbPassword);
   m_ado_src.SetConnectSqlStr(strConnectInfo);
   BOOL bRet = m_ado_src.InitConnect();
   if (bRet == FALSE)
   {
      AfxMessageBox(_T("（源）数据库配置错误"),MB_OK);
   }
   return bRet;
}

BOOL CDlgCreateSqlScript::bConnectDB_dst()
{
   m_db_info_dst;
   m_IpAddress2.GetWindowText(m_db_info_dst.strIp);
   m_edit_dbname2.GetWindowText(m_db_info_dst.strDbName);
   m_edit_dbaccount2.GetWindowText(m_db_info_dst.strDbAccount);
   m_edit_dbpwd2.GetWindowText(m_db_info_dst.strDbPassword);
   m_edit_port2.GetWindowText(m_db_info_dst.strPort);
   CString strConnectInfo = m_ado_dst.CreateConncetSqlStrByDecodeParam(m_db_info_dst.strIp+_T(",")+m_db_info_dst.strPort,
      m_db_info_dst.strDbName,m_db_info_dst.strDbAccount,m_db_info_dst.strDbPassword);
   m_ado_dst.SetConnectSqlStr(strConnectInfo);
   BOOL bRet = m_ado_dst.InitConnect();
   if (bRet == FALSE)
   {
      AfxMessageBox(_T("（目标）数据库2配置错误"),MB_OK);
   }
   return bRet;
}

void CDlgCreateSqlScript::GetAllValue(CMyADOConnEx* pAdo,tag_db_attri& oData)
{
   if (pAdo)
   {       
      oData.strTableName = pAdo->GetValueString(FIELD_TABLE_NAME);      
      oData.strTableDesc = pAdo->GetValueString(FIELD_TABLE_DESC);   
      oData.iColOrder = pAdo->GetValueInt(FIELD_COL_ORDER);     
      oData.strColName =pAdo->GetValueString(FIELD_COL_NAME);    
      oData.iIdentity = pAdo->GetValueInt(FIELD_IDENTITY);     
      oData.iPrimaryKey = pAdo->GetValueInt(FIELD_PRI_KEY);    
      oData.strColType = pAdo->GetValueString(FIELD_COL_TYPE);     
      oData.iBytes = pAdo->GetValueInt(FIELD_COL_BYTES);        
      oData.iLen = pAdo->GetValueInt(FIELD_COL_LENGTH);          
      oData.iScale = pAdo->GetValueInt(FIELD_COL_SACLE);        
      oData.bIsNullable = pAdo->GetValueInt(FIELD_COL_NULLABLE);    
      oData.strDefaultValue = pAdo->GetValueString(FIELD_DEFAULT_VALUE);
      if (oData.strDefaultValue.Find(_T("(N'"))>=0)
      {
         oData.strDefaultValue.Replace(_T("(N'"),_T(""));
      }
      else
      {
         oData.strDefaultValue.Replace(_T("('"),_T(""));
      }
      oData.strIndexName = pAdo->GetValueString(FIELD_INDEX_NAME);
      oData.strDefaultValue.Replace(_T("')"),_T(""));
      oData.strColDesc = pAdo->GetValueString(FIELD_COL_DESC);    
      oData.bFullNumberColName = db_attri::ColNameFullNumber(oData.strColName);
   }
}

void CDlgCreateSqlScript::Add2MapAttri(map_db_attri& map_attri,tag_db_attri& oData)
{
   auto itr_table_name = map_attri.find(oData.strTableName);
   if (itr_table_name == map_attri.end())
   {
      map_attri.insert(make_pair(oData.strTableName,vec_db_attri()));
      Add2MapAttri(map_attri,oData);
   }
   else
   {
      itr_table_name->second.push_back(oData);
   }
}


BOOL CDlgCreateSqlScript::OnInitDialog()
{
   CTabDialog::OnInitDialog();

   m_IpAddress.SetWindowText(_T("139.196.243.169"));
   m_edit_port.SetWindowText(_T("1433"));
   m_edit_dbname.SetWindowText(_T("BKPDM"));
   m_edit_dbaccount.SetWindowText(_T("QlFl20170104123QL"));
   m_edit_dbpwd.SetWindowText(_T("QlFl20170104123456QL"));

   //m_IpAddress2.SetWindowText(_T("139.196.243.169"));
   //m_edit_port2.SetWindowText(_T("1433"));
   //m_edit_dbname2.SetWindowText(_T("SQR"));
   //m_edit_dbaccount2.SetWindowText(_T("QlFl20170104123QL"));
   //m_edit_dbpwd2.SetWindowText(_T("QlFl20170104123456QL"));

   //m_IpAddress.SetWindowText(_T("127.0.0.1"));
   //m_edit_port.SetWindowText(_T("1433"));
   //m_edit_dbname.SetWindowText(_T("myPDM"));
   //m_edit_dbaccount.SetWindowText(_T("sa"));
   //m_edit_dbpwd.SetWindowText(_T("123"));

   m_IpAddress2.SetWindowText(_T("127.0.0.1")); 
   m_edit_port2.SetWindowText(_T("1433"));
   m_edit_dbname2.SetWindowText(_T("myBKPDM"));
   m_edit_dbaccount2.SetWindowText(_T("sa"));
   m_edit_dbpwd2.SetWindowText(_T("123"));


   return TRUE; 
}
