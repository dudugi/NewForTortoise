#pragma once
#include <map>


/*
   ��ǩ�Ի��򹤳��� yangjr2017-5-23
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

   //ͨ���Ի�������ID�½����ȡ��Ӧ�Ի���ָ�� 
   //������� nMenuID:�Ի�������ID
   //������� nDlgID:�Ի�����ԴID,strDlgTitle:�Ի������
   //����ֵ��0ʱû�жԻ����������ض�Ӧ�ĶԻ���ָ��
   CWnd* factoryMethod(int nMenuID,int &nDlgID,CString &strDlgTitle);
private:
   typedef std::map<int, S_ONETABDIALOG> MAP_TABDIALOGS;
   MAP_TABDIALOGS m_Dialogs;
};

