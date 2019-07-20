//客户信息
#pragma once

#include <map>
#include <memory>
#ifdef USING_GRIDCTRL_MARK
#include "ClassData\CDataTableDlgDefine.h"
#endif // USING_GRIDCTRL_MARK

class CADOConn;
class CLDK;
class CDBVCustomerInfoData;
class CDBCusOpRecordsData :public CObject
{
	DECLARE_SERIAL( CDBCusOpRecordsData)//序列化（串行化）需要添加的声明
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
   int            m_iClientNum;//客户端数量
   CString        m_strMemo;//备注

   CString			m_cDbServerName;	//数据库名称
   CString			m_cDbServerIP;	//数据库IP
   int			   m_iDbServerPort;	//数据库端口
   CString			m_cDbAccount;	//登录账户
   CString			m_cDbPassword;	//登录密码

   CString			m_cBeginTime;	//开始时间
   CString			m_cTime;	//到期时间
   CString			m_cPerson;	//身份信息
   CString			m_cModeData;	//功能模块 
   double         m_fChongZhiJE;//本次充值金额
   CString        m_cOpType;//操作类型 
public:
	CDBCusOpRecordsData();
	~CDBCusOpRecordsData();
	void operator = (CDBCusOpRecordsData *pData);
	void ResetData();
	void Copy(CDBCusOpRecordsData *pData);	
   void Copy(CDBVCustomerInfoData *pData);	
	BOOL GetAllDBInfo(CADOConn *pADOConn);				//获取【整条】信息	
	BOOL GetAllDBInfoByID(CADOConn *pADOConn);		//根据ID获取【整条】信息 
   BOOL InsertDBInfo(CADOConn *pADOConn);
	static CDBCusOpRecordsData * Instance();				//获取（指针）实例

private:
	static std::shared_ptr<CDBCusOpRecordsData> sm_inst;
};


class CDBCusOpRecordsList  : public CObList //CDataListMid
{
	DECLARE_SERIAL(CDBCusOpRecordsList)
public:
	CDBCusOpRecordsList();
	~CDBCusOpRecordsList();
	CDBCusOpRecordsData* GetItem(int nIndex);					//根据索引获取Item
	CDBCusOpRecordsData* GetItemByID(int nID);	//根据ID获取Item
	int GetIndexByID(int nID);				//根据ID获取索引
	void AddItem(CDBCusOpRecordsData* pItem);					//添加Item
	void DeleteItem(int nIndex);							//删除固定索引Item

	void GetListFromDB(CADOConn *pADOConn);					//从数据库获取链表
	static CDBCusOpRecordsList * Instance();					//获取（指针）实例

  BOOL GetGridDataByCusCode(__in CADOConn* pADOConn,__in CString strCusCode,__out MAP_GridCtrl_AllData& map_data);
  void ConvertDataToMap(const CDBCusOpRecordsData &oData,MAP_GridCtrl_RowData &row_data);

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
	static std::shared_ptr<CDBCusOpRecordsList> sm_inst;

};