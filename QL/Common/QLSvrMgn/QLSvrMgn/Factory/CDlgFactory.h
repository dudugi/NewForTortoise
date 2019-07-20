#pragma once
#include <map>


/*
   标签对话框工厂类 yangjr2017-5-23
*/

typedef struct tag_S_ONETABDIALOG
{
   CWnd* pWnd;
   int dlgID;
   CString dlgTitle;
   tag_S_ONETABDIALOG()
   {
      pWnd=nullptr;
      dlgID = 0;
      dlgTitle=_T("");
   }
}S_ONETABDIALOG;

class CDlgFactory
{
public:
   CDlgFactory(void);
   ~CDlgFactory(void);

   //通过对话框命令ID新建或获取对应对话框指针 
   //输入参数 nMenuID:对话框命令ID
   //输出参数 nDlgID:对话框资源ID,strDlgTitle:对话框标题
   //返回值：0时没有对话框，其他返回对应的对话框指针
   CWnd* factoryMethod(int nMenuID,int &nDlgID,CString &strDlgTitle);
private:
   typedef std::map<int, S_ONETABDIALOG> MAP_TABDIALOGS;
   MAP_TABDIALOGS m_Dialogs;
};

