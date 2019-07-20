#pragma once
#include <vector>

using namespace std;


class CADOConn;

//pdm 日志操作类 add by lida 2018/03/07

#define Log_Type_Num		12		//操作类型 数量
#define Log_Cate_Num		150	//表名	数量
#define TABLE_NAME_MAX_LEN	50

typedef enum Em_WorkLog_Type		//操作类型
{   
   enLog_Type_Del = 0,		//删除		0
   enLog_Type_Upadate,		//更新		1
   enLog_Type_Add,			//添加		2
   enLog_Type_Login,		//登入		3
   enLog_Type_Logout,		//退出		4
   enLog_Type_UpLoad,		//上传		5
   enLog_Type_DownLoad,	//下载		6
   enLog_Type_Search,		//查询		7
   enLog_Type_View,		//查看		8
   enLog_Type_Print,		//打印		9
   enLog_Type_Export,		//导出		10
   enLog_Type_Inport		//导入		11
};

static TCHAR g_LogType[Log_Type_Num][TABLE_NAME_MAX_LEN] = {
   {_T("删除")},
   {_T("更新")},
   {_T("添加")},
   {_T("登入")},
   {_T("退出")},
   {_T("上传")},
   {_T("下载")}, 
   {_T("查询")},
   {_T("查看")},
   {_T("打印")},
   {_T("导出")},
   {_T("导入")},
};

typedef enum Em_WorkLog_Cate		//表名
{
   enLog_Cate_TableName_Null = 0,
   enLog_Cate_SQL_Transaction = 1,           //数据库事物							
   enLog_Cate_TableName_Userinfo,				//	员管理										
   enLog_Cate_TableName_Customer,				//	客户管理										 									
   enLog_Cate_TableName_WorkLog,					//	操作日志	
   enLog_Cate_TableName_CheckConfig,         //  认证信息
};

static TCHAR g_TableID[Log_Cate_Num][TABLE_NAME_MAX_LEN] = {
   {_T("")},					//0
   {_T("SQL事务")},					//0
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

   //nCate：表，nType: 操作类型，strMaker:登入人员， strCode:单号, strInterfaceID: 界面，strCode：单号，strLogInfo：日志
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

