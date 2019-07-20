/*************************************************
// <文件>: DBTableStyleGlobalSetInfo.h
// <说明>: 数据库操作类-表格样式全局设置表
// <作者>: yangjr
// <日期>: 2019/02/20 16:35:46
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#pragma once

#include <vector>
#include "DataMid.h"

class CADOConn;
class DBTableStyleAttrSetLst;

class DBTableStyleGlobalSetInfo :public CDataMid
{
	DECLARE_SERIAL( DBTableStyleGlobalSetInfo)//序列化（串行化）需要添加的声明
public:
	int				m_nID;			   //自增ID
   CString        m_cXmlFileName;   //xml文件名
   CString        m_cXmlDesc;       //xml说明
   CString        m_cInitSettingXml;//出厂设置XML内容
   CString        m_cRealTimeXml;   //实时的xml内容
   CString        m_cUpdateTime;    //实时更新时间

   void ResetData();
   
   void Copy(DBTableStyleGlobalSetInfo *pData);

   BOOL GetAllDBInfo(CADOConn *pADOConn);

   BOOL InsertAllDBInfo( CADOConn *pADOConn );

   CString GetInsertSQL();

   BOOL DeleteInfoByID(CADOConn *pADOConn);
      
   BOOL UpdateInfoByID(CADOConn *pADOConn);

public:
	DBTableStyleGlobalSetInfo();
   ~DBTableStyleGlobalSetInfo();
};

class DBTableStyleGlobalSetInfoList  : public CDataListMid
{
	DECLARE_SERIAL(DBTableStyleGlobalSetInfoList)
public:
	DBTableStyleGlobalSetInfoList();
	~DBTableStyleGlobalSetInfoList();
	DBTableStyleGlobalSetInfo* GetItem(int nIndex);			//根据索引获取Item
	void AddItem(DBTableStyleGlobalSetInfo* pItem);			//添加Item
	void DeleteItem(int nIndex);					            //删除固定索引Item
	static DBTableStyleGlobalSetInfoList * Instance();		//获取（指针）实例


   //************************************
   // Method:    用本地数据 更新实时XML数据  
   // Author:    wuZhiHua
   // Date : 	  2018/04/17
   // Access:    public 
   // Returns:   BOOL
   // Parameter: CString fileName
   //************************************
   BOOL UpdateCurrentTimeXmlDataFromLocalData(CADOConn *pADOConn,CString fileName , CString strTime);


   //************************************
   // Method:    用初始化数据 更新实时XML数据 
   // Author:    wuZhiHua
   // Date : 	  2018/04/17
   // Access:    public 
   // Returns:   BOOL
   // Parameter: CString fileName
   //************************************
   BOOL UpdateCurrentTimeXmlDataFromInitData(CADOConn *pADOConn,CString fileName, CString strTime , CString &updateXmlstr);


   //************************************
   // Method:    更新出厂设置 会覆盖实时数据
   // Author:    wuZhiHua
   // Date : 	  2018/04/17
   // Access:    public 
   // Returns:   BOOL
   // Parameter: CString fileName
   //************************************
   BOOL UpdateInitSetXmlData(CADOConn *pADOConn,CString fileName, CString strTime);

   
   //************************************
   // Method:    合并代码数据  到实时XML内容  恢复出厂设置内容
   // Author:    wuZhiHua
   // Date : 	  2018/04/18
   // Access:    public 
   // Returns:   BOOL
   // Parameter: CADOConn * pADOConn
   // Parameter: CString fileName
   // Parameter: CString strTime
   //************************************
   BOOL CombineDefaultTableAtrri(CADOConn *pADOConn,CString fileName, CString strTime);


   ////************************************
   //// Method:    更新数据列  还有属性设置
   //// Author:    wuZhiHua
   //// Date : 	  2018/04/18
   //// Access:    public 
   //// Returns:   BOOL
   //// Parameter: CADOConn * pADOConn
   //// Parameter: CString strTime
   ////************************************
   //BOOL UpdateColSetAndStyleAttrSet(CADOConn *pADOConn , CString strTime);



   ////************************************
   //// Method:    更新数据列  还有属性设置 单个数据
   //// Author:    wuZhiHua
   //// Date : 	  2018/04/18
   //// Access:    public 
   //// Returns:   void
   //// Parameter: S_GridCtrl_TableAtrri & tableAtrri
   ////************************************
   //void UpdateColSetAndStyleAttrSet(CADOConn *pADOConn, DBTableStyleAttrSetLst *pStyleAttrSet , S_GridCtrl_TableAtrri& tableAtrri);

   //************************************
   // Method:    数据库XML字符串转 表格样式属性结构体
   // Author:    wuZhiHua
   // Date : 	  2018/04/17
   // Access:    private 
   // Returns:   S_GridCtrl_TableAtrri
   // Parameter: CString attriStr
   //************************************
   S_GridCtrl_TableAtrri AttriStrToAttriStruct(CString attriStr);


   //************************************
   // Method:    表格样式属性结构体 转数据库XML字符串
   // Author:    wuZhiHua
   // Date : 	  2018/04/18
   // Access:    public 
   // Returns:   CString
   // Parameter: S_GridCtrl_TableAtrri attri
   //************************************
   CString AttriStructToAttriStr(S_GridCtrl_TableAtrri tableAtrri);

   //************************************
   // Method:    根据文件名获取 数据库表格样式实时数据
   // Author:    wuZhiHua
   // Date : 	  2018/04/18
   // Access:    public 
   // Returns:   CString
   // Parameter: CADOConn * pADOConn
   // Parameter: CString fileName
   //************************************
   CString GetStyleInfoByFileName(CADOConn *pADOConn, CString fileName  , CString &updateTime);

#ifdef USING_GRIDCTRL_MARK
   //************************************
   // Method:    获取表格
   // Author:    wuZhiHua
   // Date : 	  2018/04/16
   // Access:    private 
   // Returns:   void
   // Parameter: MAP_GridCtrl_AllData & allData
   //************************************
   void GetGridData(CADOConn *pADOConn, __out MAP_GridCtrl_AllData& mapAllData);

   //************************************
   // Method:    插入或更新实时XML数据
   // Author:    yangjr
   // Date : 	  2018/05/29
   // Access:    public 
   // Returns:   BOOL
   // Parameter: CString fileName xml文件名， S_GridCtrl_TableAtrri &tableAtrri 表格样式
   BOOL InsertOrUpdateStyle(CADOConn *pADOConn,CString fileName,const S_GridCtrl_TableAtrri &tableAtrri);

   //************************************
   // Method:    获取服务器的XML数据
   // Author:    yangjr
   // Date : 	  2018/05/29
   // Access:    public 
   // Returns:   BOOL，S_GridCtrl_TableAtrri &tableAtrri 表格样式
   // Parameter: CString fileName xml文件名
   BOOL GetServerStyle(CADOConn *pADOConn,CString fileName,S_GridCtrl_TableAtrri &tableAtrri);
#endif

private:
	static std::shared_ptr<DBTableStyleGlobalSetInfoList> sm_inst;
};
