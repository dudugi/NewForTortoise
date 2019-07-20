//客户信息
#pragma once

#include <map>
#include <memory>
#ifdef USING_GRIDCTRL_MARK
#include "ClassData\CDataTableDlgDefine.h"
#endif // USING_GRIDCTRL_MARK

class CADOConn;
class CLDK;
//客户基础数据表
class CDBCustomBaseData :public CObject
{
   DECLARE_SERIAL( CDBCustomBaseData)//序列化（串行化）需要添加的声明
public:
   int				m_nID;	
   CString			m_strCusCode;	//客户编号
   CString			m_strCusName;	//客户名称
   CString			m_strCusAddress;	//客户地址
   CString			m_strCusPhone;	//电话
   CString			m_strCusContacts;	//联系人
   CString			m_strcPDMVersion;	//PDM版本
   CString			m_strProvince;	//客户地址
   int            m_isLocalDB;		//数据库是否部署在本地
   CString        m_strServerPerson;//服务人员
   int            m_iClientNum;//客户端数量
   CString        m_strMemo;//备注
public:
   CDBCustomBaseData();
   ~CDBCustomBaseData();
   void operator = (CDBCustomBaseData *pData);
   void ResetData();
   void Copy(CDBCustomBaseData *pData);	
   BOOL GetAllDBInfo(CADOConn *pADOConn);				//获取【整条】信息
   BOOL InsertAllDBInfo(CADOConn *pADOConn);	//插入【整条】新记录
   BOOL UpdateAllDBInfoByCusCode(CADOConn *pADOConn);	//根据客户编号更新【整条】记录
   BOOL DelAllDBInfoByCusCode(CADOConn *pADOConn);		//根据客户编号删除【整条】记录
   BOOL GetAllDBInfoByCusCode(CADOConn *pADOConn);		//根据客户编号获取【整条】信息 

   static CDBCustomBaseData * Instance();				//获取（指针）实例

private:
   static std::shared_ptr<CDBCustomBaseData> sm_inst;
};

//客户数据库设置表
class CDBCustomDbData :public CObject
{
   DECLARE_SERIAL( CDBCustomDbData)//序列化（串行化）需要添加的声明
public:  
   CString			m_strCusCode;	   //客户编号
   CString			m_cDbServerName;	//数据库名称
   CString			m_cDbServerIP;	//数据库IP
   int			   m_iDbServerPort;	//数据库端口
   CString			m_cDbAccount;	//登录账户
   CString			m_cDbPassword;	//登录密码
 
public:
   CDBCustomDbData();
   ~CDBCustomDbData();
   void operator = (CDBCustomDbData *pData);
   void ResetData();
   void Copy(CDBCustomDbData *pData);	
   BOOL GetAllDBInfo(CADOConn *pADOConn);				//获取【整条】信息
   BOOL InsertAllDBInfo(CADOConn *pADOConn);	//插入【整条】新记录
   BOOL UpdateAllDBInfoByCusCode(CADOConn *pADOConn);	//根据客户编号更新【整条】记录
   BOOL DelAllDBInfoByCusCode(CADOConn *pADOConn);		//根据客户编号删除【整条】记录
   BOOL GetAllDBInfoByCusCode(CADOConn *pADOConn);		//根据客户编号获取【整条】信息 

   static CDBCustomDbData * Instance();				//获取（指针）实例

private:
   static std::shared_ptr<CDBCustomDbData> sm_inst;
};

//客户加密数据表
class CDBCustomEncryptData :public CObject
{
   DECLARE_SERIAL( CDBCustomEncryptData)//序列化（串行化）需要添加的声明
public:  
   CString			m_strCusCode;	//客户编号
   CString			m_cData1;	//加密数据1
   CString			m_cData2;	//加密数据2
   CString			m_cData3;	//加密数据3
   CString			m_cData4;	//加密数据4
public:
   CDBCustomEncryptData();
   ~CDBCustomEncryptData();
   void operator = (CDBCustomEncryptData *pData);
   void ResetData();
   void Copy(CDBCustomEncryptData *pData);	
   BOOL GetAllDBInfo(CADOConn *pADOConn);				//获取【整条】信息
   BOOL InsertAllDBInfo(CADOConn *pADOConn);	//插入【整条】新记录
   BOOL UpdateAllDBInfoByCusCode(CADOConn *pADOConn);	//根据客户编号更新【整条】记录
   BOOL DelAllDBInfoByCusCode(CADOConn *pADOConn);		//根据客户编号删除【整条】记录
   BOOL GetAllDBInfoByCusCode(CADOConn *pADOConn);		//根据客户编号获取【整条】信息 

   static CDBCustomEncryptData * Instance();				//获取（指针）实例

private:
   static std::shared_ptr<CDBCustomEncryptData> sm_inst;
};

class CDBVCustomerInfoData :public CObject
{
	DECLARE_SERIAL( CDBVCustomerInfoData)//序列化（串行化）需要添加的声明
public:
   int				   m_nID;	
   CString			m_strCusCode;	//客户编号
   CString			m_strCusName;	//客户名称
   CString			m_strCusAddress;	//客户地址
   CString			m_strCusPhone;	//电话
   CString			m_strCusContacts;	//联系人
   CString			m_strcPDMVersion;	//PDM版本
   CString			m_strProvince;	//客户地址
   int            m_isLocalDB;		//数据库是否部署在本地
   CString        m_strServerPerson;//服务人员   
   CString        m_strMemo;//备注

   CString			m_cDbServerName;	//数据库名称
   CString			m_cDbServerIP;	//数据库IP
   int			   m_iDbServerPort;	//数据库端口
   CString			m_cDbAccount;	//登录账户
   CString			m_cDbPassword;	//登录密码

   CString			m_cData1;	//加密数据1
   CString			m_cData2;	//加密数据2
   CString			m_cData3;	//加密数据3
   CString			m_cData4;	//加密数据4 

   //不在数据库的数据 yangjr 2018/8/30
   CString			m_cBeginTime;	//开始时间
   CString			m_cTime;	//到期时间
   CString			m_cPerson;	//身份信息
   CString			m_cModeData;	//功能模块 
   int            m_iClientNum;//客户端数量

   double         m_fChongZhiJE;//本次充值金额
public:
	CDBVCustomerInfoData();
	~CDBVCustomerInfoData();
	void operator = (CDBVCustomerInfoData *pData);
	void ResetData();
	void Copy(CDBVCustomerInfoData *pData);	
	BOOL GetAllDBInfo(CADOConn *pADOConn);				//获取【整条】信息	
	BOOL GetAllDBInfoByCusCode(CADOConn *pADOConn);		//根据客户获取【整条】信息 

   CString GetInsertSql();
   CString GetUpdateSql();

   BOOL EncryptString(__in CLDK *pLdk);
   BOOL DecryptString(__in CLDK *pLdk);
	static CDBVCustomerInfoData * Instance();				//获取（指针）实例

private:
	static std::shared_ptr<CDBVCustomerInfoData> sm_inst;
};


class CDBVCustomerInfoList  : public CObList //CDataListMid
{
	DECLARE_SERIAL(CDBVCustomerInfoList)
public:
	CDBVCustomerInfoList();
	~CDBVCustomerInfoList();
	CDBVCustomerInfoData* GetItem(int nIndex);					//根据索引获取Item
	CDBVCustomerInfoData* GetItemByCusCode(CString strCusCode);	//根据客户编码获取Item
	int GetIndexByCusCode(CString strCusCode);				//根据客户编码获取索引
	void AddItem(CDBVCustomerInfoData* pItem);					//添加Item
	void DeleteItem(int nIndex);							//删除固定索引Item

	void GetListFromDB(CADOConn *pADOConn);					//从数据库获取链表
	static CDBVCustomerInfoList * Instance();					//获取（指针）实例

   BOOL GetAllCustomerGridData(__in CADOConn* pADOConn,__in CLDK *pLdk,__out MAP_GridCtrl_AllData& map_data);

   BOOL GetExpiringCustomerGridData(__in CADOConn* pADOConn,__in int iDays,__in CLDK *pLdk,__out MAP_GridCtrl_AllData& map_data); //即将过期

   BOOL GetExpiredCustomerGridData(__in CADOConn* pADOConn,__in CLDK *pLdk,__out MAP_GridCtrl_AllData& map_data);  //已过期

   void ConvertDataToMap(const CDBVCustomerInfoData &oData,MAP_GridCtrl_RowData &row_data);

   BOOL GetCustomerDataByID(__in CADOConn* pADOConn,__in int iID,__in CLDK *pLdk,__out CDBVCustomerInfoData* pData);

   CString GetDelSql_CustomerDataByCusCode(__in vector<CString> vecCusCode);

   BOOL CheckCusCodeExists(__in CADOConn* pADOConn,__in CString strCusCode);

protected:
   inline void Empty()
   {
      for (int j=(GetCount()-1);j>=0;j--)
      {
         CObject *pData =(CObject *)GetAt(FindIndex(j));
         if (pData)
         {
            delete pData;
            pData = NULL;
         }
      }

      RemoveAll();
   }

private:
	static std::shared_ptr<CDBVCustomerInfoList> sm_inst;

};