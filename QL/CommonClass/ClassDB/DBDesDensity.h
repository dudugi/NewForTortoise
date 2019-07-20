#pragma once

#ifndef Des_IMAGE
#define Des_IMAGE	1
#endif

/*************************************************
// <文件>: DBDesDensity.h
// <说明>: 面子吗和密度信息表 主要用于与工艺对接
// <作者>: wangzl
// <日期>: 2019/01/30 10:32:14
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 

//2017/11/28 zhangt Create
#include "DataMid.h"

#if Des_IMAGE
#include "Dib.h"
#include "ViewCtrl.h"
#endif // Des_IMAGE

class CADOConn;

#define DBDesFaceCode_key_ID			   _T("ID")		      //自增ID
#define DBDesFaceCode_key_NAME			_T("cName")		   //名称 eg:面字码
#define DBDesFaceCode_key_LENOLD		   _T("fOldLen")	   //
#define DBDesFaceCode_key_TYPE			_T("cType")		   //类型 eg:支拉
#define DBDesFaceCode_key_LEN			   _T("fLen")		   //长度
#define DBDesFaceCode_key_UNIT			_T("cUnit")		   //单位 eg:里面
#define DBDesFaceCode_key_IDDENSITY		_T("IDDensity")	//密度关联字段自增ID


//面子码
class CDBFaceCode : public CDataMid
{
	DECLARE_SERIAL( CDBFaceCode)           //序列化（串行化）需要添加的声明

public:
	CDBFaceCode();
	~CDBFaceCode();
	void ResetData();

	BOOL GetAllDBInfo(CADOConn *pADOConn);	//获取【整条】信息
	void Copy(CDBFaceCode *pData);

                                          //获取插入语句的格式化
	CString GetSQLFormat();
                                          //获取插入数据的格式化
   CString GetValueFormat(
      const CString & strName,
      const CString & strOldLen,
      const CString & strType,
      const CString & strLen,
      const CString & strUnit,
      const __int64 nIDDensity
      );

	static CDBFaceCode * Instance();		   //获取（指针）实例

private:
	static std::shared_ptr<CDBFaceCode> sm_inst;

public:
	int		m_nID		;                    //自增ID
	CString m_strName	;                    //名称 eg:面字码
	CString	m_sOldLen;                    //
	CString m_strType	;                    //类型 eg:支拉
	CString	m_sLen	;                    //长度
	CString m_strUnit	;                    //单位 eg:里面

	__int64 m_nIDDensity;		            //密度关联字段自增ID
};

class CDBFaceCodeList : public CDataListMid
{
	DECLARE_SERIAL(CDBFaceCodeList)
public:
	CDBFaceCodeList();
	~CDBFaceCodeList();
	CDBFaceCode*  GetItem(int nIndex);
	void    AddItem(CDBFaceCode* pItem);
	void    DeleteItem(int nIndex);

	static CDBFaceCodeList * Instance();		//获取（指针）实例

private:
	static std::shared_ptr<CDBFaceCodeList> sm_inst;
};

//包含一个面子码链表的数据
class CDBDensityFaceCodeData : public CDataMid
{
	DECLARE_SERIAL(CDBDensityFaceCodeData)
public:
	CDBDensityFaceCodeData();
	virtual ~CDBDensityFaceCodeData();
public:
	CDBFaceCodeList m_lstFaceCode;
	__int64 m_nIDDensity;		//密度关联字段自增ID
public:
	void Copy(CDBDensityFaceCodeData * pData);
	void AddItem(CDBFaceCode * pData);
};

class CDBDensityFaceCodeList : public CDataListMid
{
	DECLARE_SERIAL(CDBDensityFaceCodeList)
public:
	CDBDensityFaceCodeList();
	virtual ~CDBDensityFaceCodeList();
public:
	CDBDensityFaceCodeData*  GetItem(int nIndex);
	CDBDensityFaceCodeData*  GetItemByIDDensity(int nID);
	void    AddItem(CDBDensityFaceCodeData* pItem);
	void    DeleteItem(int nIndex);
};


//密度表
#define DB_TABLE_DESDENSITY		      _T("DesDensity")
                                       
#define DBDesDensity_key_ID			   _T("ID")		                       //自增ID
#define DBDesDensity_key_Name	    	   _T("cName")		                    //名称
#define DBDesDensity_key_HorDesSrc	   _T("fHorDesSrc")                   //横密
#define DBDesDensity_key_VerDesSrc	   _T("fVerDesSrc")                   //直密
#define DBDesDensity_key_HorDesNew	   _T("fHorDesNew")                   //横密
#define DBDesDensity_key_VerDesNew	   _T("fVerDesNew")                   //直密
#define DBDesDensity_key_Structure	   _T("cStructure")                   //坯布结构
#define DBDesDensity_key_Material	   _T("cMaterial")	                 //毛料
#define DBDesDensity_key_Pull		      _T("fPull")		                    //拉力
#define DBDesDensity_key_PullUnit	   _T("cPullUnit")	                 //单位
#define DBDesDensity_key_PullType	   _T("iPullType")	                 //eg:全长拉 or 领下拉
#define DBDesDensity_key_Needle		   _T("cNeedle")	                    //针型
                                       
                                                                          //小片重量                             
#define DBDesDensity_key_PieceUnit	   _T("fPieceUnit")	                 //100克
#define DBDesDensity_key_PieceTurns	   _T("fPieceTurns")	                 //100转
#define DBDesDensity_key_PieceNeedle   _T("fPieceNeedle")	              //100针

                                                                          //起头空转
#define DBDesDensity_key_StartTurns		_T("fStartTurns")

                                                                          //罗文排列
#define DBDesDensity_key_RomanType		_T("cRomanType")

                                                                          //加丝转数
#define DBDesDensity_key_Wire		      _T("cWire")	                       //加丝
#define DBDesDensity_key_WireTurns	   _T("fWireTurns")	                 //转
#define DBDesDensity_key_WireType	   _T("iWireType")		              //是否全加丝

                                                                          //排针
#define DBDesDensity_key_ShowPZ        _T("iShowPZ")                      //是否显示排针
#define DBDesDensity_key_PZName		   _T("cPZName")                      //排针名称
#define DBDesDensity_key_PinBottom	   _T("cPinBottom")	                 //底
#define DBDesDensity_key_PinFace	      _T("cPinFace")		                 //面
#define DBDesDensity_key_PinType     	_T("iPinType")		                 //排针类型

#define DBDesDensity_key_Type		      _T("cType")			                 //密度自定义类型
#define DBDesDensity_key_BaseType	   _T("cBaseType")		              //大身密度 or 罗文密度

#define DBDesDensity_key_cSavedUserID  _T("cSavedUserID")                 //保存人
#define DBDesDensity_key_cSaveTime     _T("cSaveTime")                    //保存时间
#define DBDesDensity_key_cRemark       _T("cRemark")                      //密度说明
#define DBDesDensity_key_cOrderNo      _T("cOrderNo")                     //订单号 货号 

#define DBDesDensity_key_cPieceName    _T("cPieceName")                   //衣片名称
#define DBDesDensity_key_cMatName      _T("cMatName")                     //坯布名称 

#define DBDesDensity_key_cFlowerPatternPic    _T("cFlowerPatternPic")     //花样图片
//不在数据库
#define DBDesDensity_key_cSavedUserName _T("cSavedUserName")              //保存人姓名

class CDBDensity : public CDataMid
{
	DECLARE_SERIAL(CDBDensity)//序列化（串行化）需要添加的声明

public:
	CDBDensity();
	~CDBDensity();
	void ResetData();
   BOOL UpdateDBInfo(CADOConn * pADOConn);
	BOOL GetAllDBInfo(CADOConn *pADOConn);		//获取【整条】信息
	void Copy(CDBDensity *pData);

	//获取插入的SQL语句
	CString GetInsertSQL();
	static CDBDensity * Instance();//获取（指针）实例
   void SetFaceData(CDBFaceCode* data);
   BOOL UpdateAllDBInfoByID(CADOConn * pADOConn);
   BOOL InsertAllDBInfoByID(CADOConn * pADOConn);
#if Des_IMAGE
private:
   inline void ClearColorImage();
#endif // Des_IMAGE
private:
	static std::shared_ptr<CDBDensity> sm_inst;


public:
   CDBDensityFaceCodeData m_faceData         ;
	__int64		           m_nID              ;//自增ID
	CString                m_strName          ;//名称
	double	              m_fHorDesSrc       ;//横密
   double	              m_fVerDesSrc       ;//直密
   double	              m_fHorDesNew       ;//横密
   double	              m_fVerDesNew       ;//直密
	CString                m_strStructure     ;//坯布结构
	CString                m_strMaterial      ;//毛料

   double	              m_fPull            ;//拉力
	CString                m_strPullUnit      ;//单位
	int		              m_nPullType        ;//eg:全长拉 or 领下拉
	CString                m_strNeedle        ;//针型

	//小片重量
	double                 m_fPieceUnit		   ;//100克
	double                 m_fPieceTurns		;//100转
	double                 m_fPieceNeedle	   ;//100针

	//起头空转
   double                 m_fStartTurns		;

	//罗文排列
	CString                m_strRomanType	   ;

	//加丝转数
	CString                m_strWire		      ;//加丝
   double	              m_fWireTurns	      ;//转
	int		              m_nWireType		   ;//是否全加丝


	//排针
	BOOL	                 m_bShowPZ		      ;//是否显示排针
	CString                m_strPZName		   ;//排针名称
	CString                m_strPinBottom	   ;//底
	CString                m_strPinFace	      ;//面
	int		              m_nPinType		   ;//排针类型

	CString                m_strType		      ;//密度自定义类型
	CString                m_strBaseType	   ;//大身密度 or 罗文密度

   CString                m_strSavedUserID   ;//用户ID
   CString                m_strSaveTime      ;//保存时间
   CString                m_strRemark        ;//密度说明
   CString                m_strOrderNo       ;//订单号
   CString                m_strPieceName     ;//衣片名称
   CString                m_strMatName       ;//坯布名称


#if Des_IMAGE
   Gdiplus::Image*		  m_pFlowerPatternPic;//花样图
#endif

   //不在数据库
   CString m_strSavedUserName;//用户名
};

class CDBDensityList : public CDataListMid
{
	DECLARE_SERIAL(CDBDensityList)
public:
	CDBDensityList();
	~CDBDensityList();
	CDBDensity*  GetItem(int nIndex);
   CDBDensity*  GetItemByName(const CString & strName);
	void    AddItem(CDBDensity* pItem);
	void    DeleteItem(int nIndex);
   void    MatchData(CDBFaceCode* data);
   BOOL    DeleteUserByUserID(CADOConn * pADOConn, vector<CString> vecUserID);

   static CDBDensityList * Instance();		//获取（指针）实例
   
#ifdef USING_GRIDCTRL_MARK
   //生成表格数据
   MAP_GridCtrl_AllData CreateGridData(const CString & strUserDuty = _T(""));
#endif // USING_GRIDCTRL_MARK

private:
   CDBDensityFaceCodeData m_FaceData;
	static std::shared_ptr<CDBDensityList> sm_inst;
};