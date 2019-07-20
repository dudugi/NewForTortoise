#include "StdAfx.h"
#include "../resource.h"
#include "../QLSvrMgn.h"
#include "CDlgFactory.h"
#include "../DlgPane1Item1.h"
#include "../DlgPane1Item2.h"
#include "../DlgPane1Item3.h"
#include "../DlgPane2Item1.h"
#include "../DlgPane2Item2.h"
#include "../DlgPane2Item3.h"
#include "../DlgCreateSqlScript.h"

CDlgFactory::CDlgFactory(void)
{
}


CDlgFactory::~CDlgFactory(void)
{
   MAP_TABDIALOGS::iterator iter = m_Dialogs.begin();
   for (;iter!=m_Dialogs.end();++iter)
   {
      delete iter->second.pWnd;
      iter->second.pWnd = nullptr;
   }
}

CWnd* CDlgFactory::factoryMethod(int nMenuID,int &nDlgID,CString &strDlgTitle)
{
	CString strTip = _T("");

   CWnd* pWnd = 0;
   MAP_TABDIALOGS::iterator iterFind = m_Dialogs.find(nMenuID);
   if (m_Dialogs.end() != iterFind) 
   {
      if (nullptr != iterFind->second.pWnd) 
      {
         pWnd = iterFind->second.pWnd;
         nDlgID = iterFind->second.dlgID;
         strDlgTitle = iterFind->second.dlgTitle;
		 //----------------------------------当对应的指针存在时直接返回 不再进行new ----------------------------------
		 if (NULL != pWnd)
		 {
			 return pWnd;
		 }
		 //----------------------------------当对应的指针存在时直接返回 不再进行new end----------------------------------
      }
   }

   switch(nMenuID)
   {	
		//by zhangyx 2017//11//29
   case IDD_DLG_PANE1_ITEM1:
	   {
		   pWnd = new CDlgPane1Item1;
		   nDlgID = CDlgPane1Item1::IDD;
		   strDlgTitle = _T("备份");
	   }
	   break;
   case IDD_DLG_PANE1_ITEM2:
	   {
		   pWnd = new CDlgPane1Item2;
		   nDlgID = CDlgPane1Item2::IDD;
		   strDlgTitle = _T("还原");
	   }
	   break;
   case IDD_DLG_PANE1_ITEM3:
	   {
		   pWnd = new CDlgPane1Item3;
		   nDlgID = CDlgPane1Item3::IDD;
		   strDlgTitle = _T("升级数据库");
	   }
	   break;
   case IDD_DLG_PANE2_ITEM1:
	   {
		   pWnd = new CDlgPane2Item1;
		   nDlgID = CDlgPane2Item1::IDD;
		   strDlgTitle = _T("安装数据库");
	   }
	   break;
   case IDD_DLG_PANE2_ITEM2:
	   {
		   pWnd = new CDlgPane2Item2;
		   nDlgID = CDlgPane2Item2::IDD;
		   strDlgTitle = _T("执行数据库脚本");
	   }
	   break;
   case IDD_DLG_PANE2_ITEM3:
	   {
		   pWnd = new CDlgPane2Item3;
		   nDlgID = CDlgPane2Item3::IDD;
		   strDlgTitle = _T("Pane2_Item3");
	   }
      break;
   case IDD_DIALOG_CREATE_SQL_SCRIPT:
      {
         pWnd = new CDlgCreateSqlScript;
         nDlgID = CDlgCreateSqlScript::IDD;
         strDlgTitle = _T("差异生成数据库脚本");
      }
	   break;
	   //by zhangyx 2017//11//29end
   default:
      break;
   }

   //----------------------------------若对应的节点存在 不再进行插入 直接对相关指针进行修改----------------------------------
   if (nullptr != pWnd) 
   {
	   if (m_Dialogs.end() != iterFind)
	   {
		   //前面非空直接返回  此处不进行非空相关处理
		   iterFind->second.pWnd = pWnd;
	   }
	   else
	   {
		   S_ONETABDIALOG oneDlg;
		   oneDlg.pWnd = pWnd;
		   oneDlg.dlgTitle = strDlgTitle;
		   oneDlg.dlgID = nDlgID;
		   m_Dialogs.insert(std::make_pair(nMenuID,oneDlg));
	   }
   }

   return pWnd;
}
     