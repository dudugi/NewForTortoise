#pragma once
#include <vector>

using namespace std;


class CADOConn;

//pdm ��־������ add by lida 2018/03/07

#define Log_Type_Num		12		//�������� ����
#define Log_Cate_Num		150	//����	����
#define TABLE_NAME_MAX_LEN	50

typedef enum Em_WorkLog_Type		//��������
{   
   enLog_Type_Del = 0,		//ɾ��		0
   enLog_Type_Upadate,		//����		1
   enLog_Type_Add,			//���		2
   enLog_Type_Login,		//����		3
   enLog_Type_Logout,		//�˳�		4
   enLog_Type_UpLoad,		//�ϴ�		5
   enLog_Type_DownLoad,	//����		6
   enLog_Type_Search,		//��ѯ		7
   enLog_Type_View,		//�鿴		8
   enLog_Type_Print,		//��ӡ		9
   enLog_Type_Export,		//����		10
   enLog_Type_Inport		//����		11
};

static TCHAR g_LogType[Log_Type_Num][TABLE_NAME_MAX_LEN] = {
   {_T("ɾ��")},
   {_T("����")},
   {_T("���")},
   {_T("����")},
   {_T("�˳�")},
   {_T("�ϴ�")},
   {_T("����")}, 
   {_T("��ѯ")},
   {_T("�鿴")},
   {_T("��ӡ")},
   {_T("����")},
   {_T("����")},
};

typedef enum Em_WorkLog_Cate		//����
{
   enLog_Cate_TableName_Null = 0,
   enLog_Cate_SQL_Transaction = 1,           //���ݿ�����							
   enLog_Cate_TableName_Userinfo,				//	Ա����										
   enLog_Cate_TableName_Customer,				//	�ͻ�����										 									
   enLog_Cate_TableName_WorkLog,					//	������־	
   enLog_Cate_TableName_CheckConfig,         //  ��֤��Ϣ
};

static TCHAR g_TableID[Log_Cate_Num][TABLE_NAME_MAX_LEN] = {
   {_T("")},					//0
   {_T("SQL����")},					//0
   {_T("Userinfo")},
   {_T("Customer")},
   {_T("WorkLog")},
   {_T("CheckConfig")},
};


class CDBWorkLogOperator
{
public: 
   static CDBWorkLogOperator* GetInstance()
   {
      if (p_Instance == NULL)
      {
         p_Instance = new CDBWorkLogOperator;
      }
      return p_Instance;
   };

   //nCate����nType: �������ͣ�strMaker:������Ա�� strCode:����, strInterfaceID: ���棬strCode�����ţ�strLogInfo����־
   BOOL InsertWorkLog(CADOConn *pADOConn,Em_WorkLog_Cate nCate,Em_WorkLog_Type nType,CString strMaker ,
      CString strInterfaceID= _T(""),CString strCode= _T(""),CString strLogInfo= _T(""));

   BOOL InsertMultiWorkLog(CADOConn *pADOConn,Em_WorkLog_Cate nCate,Em_WorkLog_Type nType,CString strMaker ,
      CString strInterfaceID= _T(""),vector<CString> vecCode = vector<CString>(),CString strLogInfo= _T(""));

   CString Get_InsertWorkLog_Sql(CADOConn *pADOConn,Em_WorkLog_Cate nCate,Em_WorkLog_Type nType,CString strMaker ,
      CString strInterfaceID= _T(""),CString strCode= _T(""),CString strLogInfo= _T(""));

private:
   CDBWorkLogOperator(void);
   ~CDBWorkLogOperator(void);

private:
   static CDBWorkLogOperator* p_Instance;
};

