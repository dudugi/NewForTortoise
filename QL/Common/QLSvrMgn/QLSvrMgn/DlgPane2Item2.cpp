// DlgPane2Item2.cpp : 实现文件
//

#include "stdafx.h"
#include "QLSvrMgn.h"
#include "DlgPane2Item2.h"


// CDlgPane2Item2 对话框

IMPLEMENT_DYNAMIC(CDlgPane2Item2, CTabDialog)

CDlgPane2Item2::CDlgPane2Item2(CWnd* pParent /*=NULL*/)
	: CTabDialog(CDlgPane2Item2::IDD, pParent)
{

}

CDlgPane2Item2::~CDlgPane2Item2()
{
}

void CDlgPane2Item2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgPane2Item2, CTabDialog)
   ON_BN_CLICKED(IDC_CARRY_DATABASE_BUTTON, &CDlgPane2Item2::OnBnClickedCarryDatabaseButton)
   ON_BN_CLICKED(IDC_BTN_CARRY, &CDlgPane2Item2::OnBnClickedBtnCarry)
END_MESSAGE_MAP()


// CDlgPane2Item2 消息处理程序


void CDlgPane2Item2::OnBnClickedCarryDatabaseButton()
{
   // TODO: 在此添加控件通知处理程序代码
   // TODO: 在此添加控件通知处理程序代码
   CString strDefPath = _T("");
   GetDlgItemText(IDC_UPDATE_FUNCTION_EDIT,strDefPath);

   CString strFilter = _T("文件(*.sql)|*.sql||");
   CString strNewPath =_T("");
   COleDateTime CurrentTime=COleDateTime::GetCurrentTime();
   CString strFile = _T("");

   if (m_CDirectroy.OpenDirFile(strNewPath,strDefPath,strFile,strFilter,TRUE))
   {
      SetDlgItemText(IDC__CARRY_DATABASE_EDIT , strNewPath);
      theApp.OnWriteIni(_T("CarryDataSqlPath"), _T("CarryDataSql"), strNewPath,INI_SQLSVR);
   }

}



void CDlgPane2Item2::OnBnClickedBtnCarry()
{
   // TODO: 在此添加控件通知处理程序代码
   CString strFilePath = _T("");
   GetDlgItemText(IDC__CARRY_DATABASE_EDIT,strFilePath);
   if(strFilePath.IsEmpty() || (!PathFileExists(strFilePath)))
   {
      theApp.OnShowDesktopAlert(_T("请选择有效路径!"),COLOR_TIP_WARN,2,AfxGetMainWnd());
   }
   else
   {
      if (!theApp.GetStateConnectDB())
      {
         theApp.OnShowDesktopAlert(_T("无法连接到数据库"),COLOR_TIP_WARN,2,AfxGetMainWnd());
         return;
      }

      //
      //读取数据库脚本，进行数据库名比对
      CString strDataName,strTip;
      BOOL bUpdate = TRUE;
      strDataName = CompareDataName(strFilePath);
      if (strDataName.IsEmpty())
      {
         bUpdate = FALSE;
         CString strDatabase = _T("");
         theApp.OnReadIni(_T("ConfigureInfo"), _T("DatabaseName"), strDataName,INI_SQLSVR);//获取数据库名称
      }

      if (bUpdate)
      {
         strTip.Format(_T("%s数据库和当前连接数据库不一致,确定执行脚本文件吗？"),strDataName);
         if(IDCANCEL == MessageBox(strTip,_T("提示"),MB_OKCANCEL|MB_ICONQUESTION))
         {
            return;
         }
         theApp.OnShowDesktopAlert(_T("执行失败"),COLOR_TIP_WARN,2);
         return;
      }

      CString strDatabase = _T("");
      theApp.OnReadIni(_T("ConfigureInfo"), _T("DatabaseName"), strDatabase,INI_SQLSVR);
      theApp.ShowLoading();
      BOOL bRet = TRUE;
      bRet = m_FileTxt.ReadFile(strFilePath);
      if (m_FileTxt.ReadFile(strFilePath))
      {
         CString strSQL = _T("");
         auto it = m_FileTxt.m_vecCString.begin();
         while(it != m_FileTxt.m_vecCString.end())
         {
            CString strStr,strStrItr,strStrGo;
            strStrItr= *it;
            strStrItr.MakeUpper();
            strStrItr.Replace(_T(" "), _T(""));
            strStr.Format(_T("USE[%s]"),strDataName);
            strStrGo.Format(_T("GO"));
            if(strStrItr== strStr || *it==strStrGo)
            {
               it++;
               continue;
            }
            strSQL += *(it) + _T("\r\n");
            it++;
         }

         bRet = theApp.m_pADOConn->ExecuteSQL(strSQL);
         if(bRet)
         {
            theApp.OnShowDesktopAlert(_T("执行成功!"),COLOR_TIP_SUC,2,AfxGetMainWnd());
         }
         else
         {
            theApp.OnShowDesktopAlert(_T("执行失败!"),COLOR_TIP_FAIL,2,AfxGetMainWnd());
         }		
      }
      else
      {
         theApp.OnShowDesktopAlert(_T("执行失败!"),COLOR_TIP_FAIL,2,AfxGetMainWnd());
      }
      theApp.CloseLoading();
   }
}

CString CDlgPane2Item2::CompareDataName(CString strPath)
{
   //读取数据库脚本，进行数据库名比对
   CStdioFile file;
   CString str;
   if(file.Open(strPath,CFile::modeRead))
   {
      file.ReadString(str);
      str.Trim();

      int pos =  str.ReverseFind('[');
      CString text =str.Right(str.GetLength()-pos);
      CString strDatabase = _T("");
      theApp.OnReadIni(_T("ConfigureInfo"), _T("DatabaseName"), strDatabase,INI_SQLSVR);//获取数据库名称
      strDatabase= _T("[")+strDatabase+_T("]");
      if (strDatabase != text)
      {
         return text;
      }
      else
      {
         text = _T("");
         return text;
      }

   }
   else
   {
      return FALSE;
   }
}
