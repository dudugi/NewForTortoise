//纱线索引表、纱线表

#pragma once
#ifndef YARN_IMAGE
#define YARN_IMAGE	1
#endif

#include <map>
#include "DataMid.h"
#include "DBKeyDef.h"
#define ALL_COLOR_GROUP _T("全部")
#define NO_COLOR_GROUP _T("无色组")

/*************************************************
// <文件>: DBYarnInfo.h
// <说明>: 纱线信息以及纱线索引表
// <作者>: wangzl
// <日期>: 2019/02/22
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 

class CADOConn;
class CDBYarnInfoData  : public CDataMid
{
	DECLARE_SERIAL( CDBYarnInfoData)//序列化（串行化）需要添加的声明
public:
	typedef enum En_YarnState
	{
		State_InValid = 0,//无效纱线
		State_Vilid ,
	};

	int				   m_nID;			 //自增ID
	COleDateTime	   m_oleData;		 //更新日期
	CString			   m_strCate;		 //类别   ->来自数据字典
	CString			   m_strYarnNo;		 //纱线号
	CString			   m_strYarnName;	 //纱线名称
	CString			   m_strIngredient;	 //纱线成分
	CString			   m_strThickNess;	 //支数
	CString			   m_strRemark;		 //备注
	double			   m_fWarning;		 //锁存数量
	COLORREF		   m_RGBValue;		 //颜色值(DWORD)数据库存储为bigint取后4个字节的数值即可
	CString			   m_strRGBName;	 //颜色名称
	int				   m_nKind;			 //种类(0==主料/1==辅料)
	int				   m_nState;		 //1==上  0==下架的标识
   double			      m_fKucunYujing;		 //库存预警数量
   CString           m_strColorGroup;//色组 huangym   2018/12/19
#if YARN_IMAGE
	Gdiplus::Image*				m_pYarnColorCard;//色卡
#endif

	CString			   m_strCurResv;	 //当前库存 纱线库存预警界面用到，和数据库无关联，add by lida 2017/06/15
   bool              m_bHaveDownPic;//图片是否已下载 yangjr 2017/1/30

public:
	CDBYarnInfoData();
	~CDBYarnInfoData();
	void ResetData();
	void Copy(CDBYarnInfoData *pData);
	void Serialize(CArchive& ar);
	BOOL GetAllDBInfo(CADOConn *pADOConn,bool bNeedColorCard=false);		//获取纱线【整条】信息

	BOOL DelAllDBInfoByID(CADOConn *pADOConn);		//根据ID删除【整条】记录
   BOOL DelAllDBInfoByYarnNoAndCate(CADOConn *pADOConn);		//根据色号跟类别删除【整条】记录

	BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);	//根据ID更新【整条】
   BOOL UpdateAllDBInfoByYarnNoAndCate(CADOConn *pADOConn);	//根据色号跟类别更新【整条】记录
	BOOL InsertAllDBInfoByYarnID(CADOConn *pADOConn);	//根据纱线号插入【整条】记录
   BOOL UpdateStateByYarnNoAndCate(CADOConn *pADOConn,CString strSehao,CString strYarnCate,int iState);	//根据纱线号更新上架状态记录 yangjr 2017-12-11
   BOOL GetStateByYarnNoAndCate(CADOConn *pADOConn,CString strSehao,CString strYarnCate,int &iState);	//根据纱线号获取上架状态记录 yangjr 2017-12-11
   BOOL GetPictureDataByYarnNoAndCate(CADOConn *pADOConn,CString strSehao,CString strYarnCate, Gdiplus::Image *&pYarnColorCard);	//根据纱线号获取色号图片 yangjr 2018/1/30
   //根据纱线号更新锁存值 yangjr 2018/1/9
   BOOL UpdateWarnValueByYarnNoAndCate(CADOConn *pADOConn,CString strSehao,CString strYarnCate,double fWarnValue);
   //根据纱线号更新库存预警值 yangjr 2018/4/24
   BOOL UpdateKucunYujingByYarnNoAndCate(CADOConn *pADOConn,CString strSehao,CString strYarnCate,double fKucunYujing);
   //比较修改前后数据，将修改了的数据保存起来
   CString SetDBEquals_Log(CDBYarnInfoData &pOldData);
   //BOOL GetYarnCateBySehao(CADOConn *pADOConn,CString strSehao,CString &strYarnCate);
	void Trim();
	static CDBYarnInfoData * Instance();//获取（指针）实例

#ifdef YARN_IMAGE
private:
	inline void ClearColorImage();
#endif // YARN_IMAGE
private:
	static std::shared_ptr<CDBYarnInfoData> sm_inst;
};

class CDBYarnInfoList : public CDataListMid
{
	DECLARE_SERIAL(CDBYarnInfoList)
public:
	CDBYarnInfoList();
	~CDBYarnInfoList();
	CDBYarnInfoData*  GetItem(int nIndex);
	void    AddItem(CDBYarnInfoData* pItem);
	void    DeleteItem(int nIndex);
   BOOL    DeleteItemByID(int ID);
	CDBYarnInfoData* GetItemByID(int nID);
   //获取对应色号所有的纱线数据 同色号的时候返回多条 yangjr 2019/03/01
   std::vector<CDBYarnInfoData*> GetItemsByYarnNo(CString strYarnNo);
   CDBYarnInfoData* GetItemByYarnNo_NoCase(CString strYarnNo); //忽略大小写
   //获取对应色号(不区分大小写)所有的纱线数据 同色号的时候返回多条 yangjr 2019/03/01
   std::vector<CDBYarnInfoData*> GetItemsByYarnNo_NoCase(CString strYarnNo);
	int GetIndexByID(int nID);
   CDBYarnInfoData* GetItemByYarnNoAndCate_NoCase(CString strYarnNo,CString strYarnCate); //忽略大小写
   void GetListFromDB(CADOConn *pADOConn, bool bNeedColorCard = false);//从数据库获取链表
	static CDBYarnInfoList * Instance();//获取（指针）实例

   void SetAllItemDownPic(bool bDownPic);//设置所有项的下载图片标志 yangjr 2018/1/30  
   void SetDownPicFlagByYarnNoAndCate(CString strYarnNo,CString strYarnCate,bool bDownPic); //设置对应色号的下载图片标志 yangjr 2018/1/30
   void SetPicDataByYarnNoAndCate(CString strYarnNo,CString strYarnCate, Gdiplus::Image* pYarnColorCard); //设置对应色号的图片数据 yangjr 2018/1/30

   void GetYarn_Cate_CF_Info(CADOConn *pADOConn,CString strYarnNo,CString& strYarnCate,CString& strCF);//读取纱线类别、成分信息

   void GetYarnCateCF(CADOConn *pADOConn,map<CString,CString>& mapData);

   BOOL GetYarnInfoBySehao(__in CADOConn *pADOConn,__in CString strSehao,__out CDBYarnInfoData* pObj);

   BOOL GetYarnColor(__in CADOConn *pADOConn,__in CString strSehao,__in CString strYarnCate,__out CString& strColor); //读取色号颜色 by lida 2018/07/26

   static BOOL CheckSeHaoIsExists(__in CADOConn *pADOConn,__in CString strSehao);    //检查色号是否存在
	//2017/6/9 8:57 wzl 生成表格相关数据
#ifdef USING_GRIDCTRL_MARK
	MAP_GridCtrl_AllData CreatrGridData();
   MAP_GridCtrl_AllData CreatrGridData_Sehao();

	//生成一条空的行数据		by WangZY 2017/08/24
	BOOL GetEmptyRowData(__out MAP_GridCtrl_RowData &mapEmptyRowData);

	//批量提交数据修改		by WangZY 2017/08/24
	BOOL SaveMultiModifyData(__in CADOConn *pADOConn, __in MAP_GridCtrl_AllData &mapAddData,
		__in MAP_GridCtrl_AllData &mapModifyData, __in MAP_GridCtrl_AllData &mapDeleteData,
		__in CString strMaker);

	//纱线预警提醒，获取下架、不显示的色号
	BOOL GetRssWarningSehao(__in CADOConn* pADOConn,__in CString strData,__out vector<CString>& vecSehao,__out CString& strCurDate);	
	
	//按品种信息初始化指定id的色号的成份信息		by WangZY 2018/05/07
	static BOOL InitChenfenInfo(__in CADOConn* pADOConn,__in CString strIDFilter);
#endif // USING_GRIDCTRL_MARK
	//生成表格相关数据 end wzl

private:
	static std::shared_ptr<CDBYarnInfoList> sm_inst;
};


typedef struct my_sehao_info
{
   my_sehao_info()
   {
      //m_nID = 0;
      //m_oleData = COleDateTime::GetCurrentTime();
      m_strCate = _T("");
      m_strYarnNo = _T("");
      m_strYarnName = _T("");
      m_strIngredient = _T("");
      m_strThickNess = _T("");
      m_strRemark = _T("");
      m_fWarning = -1;
      m_RGBValue = -1;
      m_strRGBName = _T("");
      m_nKind = -1;
      m_nState = -1;
      m_fKucunYujing = -1;		 //库存预警值
   };

   CString GetUpdateSql(BOOL bIgnoreNull = TRUE)     //忽略更新空字段？
   {
      if (m_strYarnNo.IsEmpty())
      {
         return _T("");
      }
      CString strSql = _T("");
      CString strText;

      //if (!m_strCate.IsEmpty() || !bIgnoreNull)
      //{
      //   strText.Format(_T("%s = '%s',"),DBColor_key_Cate,m_strCate);
      //   strSql += strText;
      //}

      if (!m_strYarnName.IsEmpty() || !bIgnoreNull)
      {
         strText.Format(_T("%s = '%s',"),DBColor_key_YarnName,m_strYarnName);
         strSql += strText;
      }

      if (!m_strIngredient.IsEmpty() || !bIgnoreNull)
      {
         strText.Format(_T("%s = '%s',"),DBColor_key_Ingredient,m_strIngredient);
         strSql += strText;
      }

      if (!m_strThickNess.IsEmpty() || !bIgnoreNull)
      {
         strText.Format(_T("%s = '%s',"),DBColor_key_ThickNess,m_strThickNess);
         strSql += strText;
      }

      if (!m_strRemark.IsEmpty() || !bIgnoreNull)
      {
         strText.Format(_T("%s = '%s',"),DBColor_key_Remark,m_strRemark);
         strSql += strText;
      }

      if (m_fWarning >0 || !bIgnoreNull)
      {
         strText.Format(_T("%s = '%lf',"),DBColor_key_Warning,m_fWarning);
         strSql += strText;
      }

      if (m_RGBValue!=-1 || !bIgnoreNull)
      {
         strText.Format(_T("%s = '%d',"),DBColor_key_RGBValue,m_RGBValue);
         strSql += strText;
      }

      if (!m_strRGBName.IsEmpty() || !bIgnoreNull)
      {
         strText.Format(_T("%s = '%s',"),DBColor_key_RGBName,m_strRGBName);
         strSql += strText;
      }

      if (m_nKind!=-1 || !bIgnoreNull)
      {
         strText.Format(_T("%s = '%d',"),DBColor_key_Kind,m_nKind);
         strSql += strText;
      }

      if (m_nState!=-1 || !bIgnoreNull)
      {
         strText.Format(_T("%s = '%d',"),DBColor_key_State,m_nState);
         strSql += strText;
      }

      if (m_fKucunYujing>0 || !bIgnoreNull)
      {
         strText.Format(_T("%s = '%lf',"),DBColor_key_fKucunYujing,m_fKucunYujing);
         strSql += strText;
      }

      //更新时间
      CString strGetDateStr = DBS_GETDATESTR;
      strText.Format(_T("%s = %s,"),DBColor_key_Date,strGetDateStr);
      strSql += strText;

      if (!strSql.IsEmpty())
      {
         strSql = strSql.Left(strSql.GetLength() - 1);// 取掉最后一个,
         CString strRetSql;  
         strRetSql.Format(_T("update %s set %s where %s = '%s' and %s = '%s'"),DB_TABLE_YARN,strSql,DBColor_key_YarnNo,m_strYarnNo,DBColor_key_Cate,m_strCate);
         return strRetSql;
      }
      return _T("");
   };

   CString GetInsertSql()
   {
      CString strFormat;
      strFormat.Format(_T("%s,%s,%s,%s,%s, %s,%s,%s,%s,%s, %s,%s,%s"),
         DBColor_key_Date,DBColor_key_Cate,DBColor_key_YarnNo,DBColor_key_YarnName,DBColor_key_Ingredient,	
         DBColor_key_ThickNess,DBColor_key_Remark,DBColor_key_Warning,DBColor_key_RGBValue,DBColor_key_RGBName,
         DBColor_key_Kind,DBColor_key_State,DBColor_key_fKucunYujing              
         );
      CString strFormat1;
      if (m_fWarning < 0) m_fWarning = 0;
      if (m_RGBValue < 0) m_RGBValue = 0;
      if (m_nKind < 0) m_nKind = 0;
      if (m_nState < 0) m_nState = 0;
      if (m_fKucunYujing < 0) m_fKucunYujing = 0;

      strFormat1.Format(_T("%s,'%s','%s','%s','%s', '%s','%s',%f,%d,'%s', %d,%d,%f"),
         DBS_GETDATESTR,m_strCate,m_strYarnNo,m_strYarnName,m_strIngredient,
         m_strThickNess,m_strRemark,m_fWarning,m_RGBValue,m_strRGBName,
         m_nKind,m_nState,m_fKucunYujing);

      CString strSql;
      strSql.Format(_T("insert into %s (%s) values (%s);"),DB_TABLE_YARN,strFormat,strFormat1);
      return strSql;
   };

   //int				   m_nID;			 //自增ID
   //COleDateTime	   m_oleData;		 //更新日期
   CString			   m_strCate;		 //类别   ->来自数据字典
   CString			   m_strYarnNo;		 //纱线号
   CString			   m_strYarnName;	 //纱线名称
   CString			   m_strIngredient;	 //纱线成分
   CString			   m_strThickNess;	 //支数
   CString			   m_strRemark;		 //备注
   double			      m_fWarning;		 //锁存数量
   COLORREF		      m_RGBValue;		 //颜色值(DWORD)数据库存储为bigint取后4个字节的数值即可
   CString			   m_strRGBName;	 //颜色名称
   int				      m_nKind;			 //种类(0==主料/1==辅料)
   int				      m_nState;		 //1==上  0==下架的标识
   double			      m_fKucunYujing;		 //库存预警数量
}s_my_sehao_info;