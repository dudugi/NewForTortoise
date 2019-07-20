#include "StdAfx.h"
#include "DBYarnInfo.h"
#include "DBKeyDef.h"

#if YARN_IMAGE
#include "..\ClassEx\ADOConn\DBImage.h"
#endif

using namespace Gdiplus;

///////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CDBYarnInfoData,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBYarnInfoList,  CDataListMid, 1)

std::shared_ptr<CDBYarnInfoData> CDBYarnInfoData::sm_inst;
std::shared_ptr<CDBYarnInfoList> CDBYarnInfoList::sm_inst;

CDBYarnInfoData::CDBYarnInfoData()
{
#if YARN_IMAGE
	m_pYarnColorCard = NULL;
#endif // YARN_IMAGE
	ResetData(); 
} 

CDBYarnInfoData::~CDBYarnInfoData()
{
#if YARN_IMAGE
	ClearColorImage();
#endif // YARN_IMAGE
}

void CDBYarnInfoData::ResetData()
{
	m_nID = 0;
	m_oleData = COleDateTime::GetCurrentTime();
	m_strCate = _T("");
	m_strYarnNo = _T("");
	m_strYarnName = _T("");
	m_strIngredient = _T("");
	m_strThickNess = _T("");
	m_strRemark = _T("");
	m_fWarning = 0;
	m_RGBValue = 0;
	m_strRGBName = _T("");
	m_nKind = 0;
   m_strCurResv = _T("");
   m_strColorGroup = _T("");
	m_nState = State_Vilid;
   m_fKucunYujing = 0;		 //库存预警值
#if YARN_IMAGE
	ClearColorImage();
#endif // YARN_IMAGE
   m_bHaveDownPic = false;//图片是否已下载 yangjr 2017/1/30
	SetDataType(DAT_YARN);
}

void CDBYarnInfoData:: Copy(CDBYarnInfoData *pData)
{
	ASSERT(pData != NULL);
	CDataMid::Copy(pData);

	m_nID			=	pData->m_nID;
	m_oleData		=	pData->m_oleData;
	m_strCate		=	pData->m_strCate;
	m_strYarnNo		=	pData->m_strYarnNo;
	m_strYarnName	=	pData->m_strYarnName;
	m_strIngredient	=	pData->m_strIngredient;
	m_strThickNess	=	pData->m_strThickNess;
	m_strRemark		=	pData->m_strRemark;
	m_fWarning		=	pData->m_fWarning;
	m_RGBValue		=	pData->m_RGBValue;
	m_strRGBName	=	pData->m_strRGBName;
	m_nKind			=	pData->m_nKind;
	m_nState		=	pData->m_nState;
   m_fKucunYujing = pData->m_fKucunYujing;
   m_strColorGroup = pData->m_strColorGroup;
#if YARN_IMAGE
	ClearColorImage();
	if (pData->m_pYarnColorCard)
	{
		m_pYarnColorCard = pData->m_pYarnColorCard->Clone();
	}
   m_bHaveDownPic = pData->m_bHaveDownPic;//图片是否已下载 yangjr 2017/1/30
#endif
}

void CDBYarnInfoData::Serialize(CArchive& ar)
{
	CDataMid::Serialize(ar);//父类函数

	int nTagSize = 0;
	CString strName;
	int nNameSize;

	ar.Flush();
	if (ar.IsStoring())
	{
		MySerial.SaveDataInt(ar,_T("THYARNID"),m_nID);
		MySerial.SaveColeDateTime(ar,_T("YARNDATE"),m_oleData);
		MySerial.SaveDataStr(ar,_T("YARNCATE"),m_strCate);
		MySerial.SaveDataStr(ar,_T("THYARNNO"),m_strYarnNo);
		MySerial.SaveDataStr(ar,_T("YARNNAME"),m_strYarnName);
		MySerial.SaveDataStr(ar,_T("YARNINGR"),m_strIngredient);
		MySerial.SaveDataStr(ar,_T("THICKNES"),m_strThickNess);
		MySerial.SaveDataStr(ar,_T("THREMARK"),m_strRemark);
		MySerial.SaveDataFloat(ar,_T("YARNWARN"),m_fWarning);
		MySerial.SaveDataInt64(ar,_T("RGBVALUE"),m_RGBValue);
		MySerial.SaveDataStr(ar,_T("TRGBNAME"),m_strRGBName);
      MySerial.SaveDataInt(ar, _T("THEKINDS"), m_nKind);
      MySerial.SaveDataStr(ar, _T("GROUP"), m_strColorGroup);

		nNameSize = 8;
		strName = _T("DENDDEND");
		ar << nNameSize;
		ar << strName;
	}
	else
	{
		int nNumber = 0;
		ar >> nNameSize;
		ar >> strName;

		if(strName.GetLength()!=nNameSize)
			return;

		while(strName != _T("DENDDEND"))
		{
			if(nNumber > 200)
			{
				return;
			}
			else if (strName == _T("THYARNID"))
			{
				ar >> nTagSize >> m_nID;
			}
			else if (strName == _T("YARNDATE"))
			{
				ar >> nTagSize >> m_oleData;
			}
			else if (strName == _T("YARNCATE"))
			{
				ar >> nTagSize >> m_strCate;
			}
			else if (strName == _T("THYARNNO"))
			{
				ar >> nTagSize >> m_strYarnNo;
			}
			else if (strName == _T("YARNNAME"))
			{
				ar >> nTagSize >> m_strYarnName;
			}
			else if (strName == _T("YARNINGR"))
			{
				ar >> nTagSize >> m_strIngredient;
			}
			else if (strName == _T("THICKNES"))
			{
				ar >> nTagSize >> m_strThickNess;
			}
			else if (strName == _T("THREMARK"))
			{
				ar >> nTagSize >> m_strRemark;
			}
			else if (strName == _T("YARNWARN"))
			{
				ar >> nTagSize >> m_fWarning;
			}
			else if (strName == _T("RGBVALUE"))
			{
				ar >> nTagSize >> m_RGBValue;
			}
			else if (strName == _T("TRGBNAME"))
			{
				ar >> nTagSize >> m_strRGBName;
         }
         else if (strName == _T("THEKINDS"))
         {
            ar >> nTagSize >> m_nKind;
         }
         else if (strName == _T("GROUP"))
         {
            ar >> nTagSize >> m_strColorGroup;
         }
			else
			{
				ar >> nTagSize;
				ar.Flush();
				ar.GetFile()->Seek(nTagSize, CFile::current);
			}
			/////////////////////////////////////////////
			strName = _T("");
			ar >> nNameSize;
			ar >> strName;
			if(strName.GetLength() != nNameSize)
				return;
			nNumber++;
		}
	}
}

CDBYarnInfoData * CDBYarnInfoData::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = shared_ptr<CDBYarnInfoData>(new CDBYarnInfoData);

	return sm_inst.get();
}

BOOL CDBYarnInfoData::GetAllDBInfo(CADOConn *pADOConn,bool bNeedColorCard)
{
	ASSERT(pADOConn != NULL);

	BOOL bRet = TRUE;

	if (NULL == pADOConn)
	{
		bRet = FALSE;
	}
	else
	{
		m_nID			= pADOConn->GetValueInt(DBColor_key_ID);
		m_oleData		= pADOConn->GetValueDate(DBColor_key_Date);
		m_strCate		= pADOConn->GetValueString(DBColor_key_Cate);
		m_strYarnNo		= pADOConn->GetValueString(DBColor_key_YarnNo);
		m_strYarnName	= pADOConn->GetValueString(DBColor_key_YarnName);
		m_strIngredient	= pADOConn->GetValueString(DBColor_key_Ingredient);
		m_strThickNess	= pADOConn->GetValueString(DBColor_key_ThickNess);
		m_strRemark		= pADOConn->GetValueString(DBColor_key_Remark);
		m_fWarning		= pADOConn->GetValueDouble(DBColor_key_Warning);
		m_RGBValue		= pADOConn->GetValueInt64(DBColor_key_RGBValue);
      m_strRGBName = pADOConn->GetValueString(DBColor_key_RGBName);
      m_strColorGroup = pADOConn->GetValueString(DBColor_key_cGroup);
		m_nKind			= pADOConn->GetValueInt(DBColor_key_Kind);
		m_nState		= pADOConn->GetValueInt(DBColor_key_State);
      m_fKucunYujing = pADOConn->GetValueDouble(DBColor_key_fKucunYujing);
#if YARN_IMAGE
		ClearColorImage();
 		CDBImage oImage;
 		m_pYarnColorCard = oImage.NewImageFromDB(DBColor_key_ColorCard,pADOConn->GetRecoPtr());
// 		CString strPath = _T("");
// 		strPath.Format(_T("F:\\Photo\\%s.jpg"),m_strYarnNo);
// 		oImage.SaveImagePathFromDB(DBColor_key_ColorCard,strPath,pADOConn->GetRecoPtr());
#endif // YARN_IMAGE
      if (bNeedColorCard)
      {
         m_bHaveDownPic = true;
      }else
      {
         m_bHaveDownPic = false;
      }
		bRet = TRUE;
	}

	return bRet;
}
//BOOL CDBYarnInfoData::GetYarnCateBySehao(CADOConn *pADOConn,CString strSehao,CString &strYarnCate)
//{
//   ASSERT(pADOConn != NULL);
//   CString strSQL = _T("");
//   strSQL.Format(_T("select %s from %s where %s='%s'"),DBColor_key_Cate,DB_TABLE_YARN,DBColor_key_YarnNo,strSehao);
//   pADOConn->GetRecordSet(strSQL);
//   while (!pADOConn->adoEOF())   
//   {
//      strYarnCate = pADOConn->GetValueString(DBColor_key_Cate);
//      return TRUE;
//
//   }
//   return FALSE;
//}
//根据纱线号获取上架状态记录 yangjr 2017-12-11
BOOL CDBYarnInfoData::GetStateByYarnNoAndCate(CADOConn *pADOConn,CString strSehao,CString strYarnCate,int &iState)
{
   ASSERT(pADOConn != NULL);
   CString strSQL = _T("");
   strSQL.Format(_T("select %s from %s where %s='%s' and %s='%s'"),DBColor_key_State,DB_TABLE_YARN
      ,DBColor_key_YarnNo,strSehao
      ,DBColor_key_Cate,strYarnCate);
   pADOConn->GetRecordSet(strSQL);
   while (!pADOConn->adoEOF())   
   {
      iState = pADOConn->GetValueInt(DBColor_key_State);
      return TRUE;

   }
   return FALSE;
}

//获取对应色号所有的纱线数据 同色号的时候返回多条 yangjr 2019/03/01
std::vector<CDBYarnInfoData*> CDBYarnInfoList::GetItemsByYarnNo(CString strYarnNo)
{
   std::vector<CDBYarnInfoData*> vecYarnInfo;
   strYarnNo.Trim();
   if (!strYarnNo.IsEmpty())
   {
      for(int i=0;i< GetCount();i++)
      {
         CDBYarnInfoData * pObject = GetItem(i);
         if(strYarnNo==pObject->m_strYarnNo)
         {
            vecYarnInfo.push_back(pObject);
         }
      }
   }

   return vecYarnInfo;
}

//获取对应色号(不区分大小写)所有的纱线数据 同色号的时候返回多条 yangjr 2019/03/01
std::vector<CDBYarnInfoData*> CDBYarnInfoList::GetItemsByYarnNo_NoCase(CString strYarnNo)
{
   std::vector<CDBYarnInfoData*> vecYarnInfo;
   strYarnNo.Trim();
   if (!strYarnNo.IsEmpty())
   {
      for(int i=0;i< GetCount();i++)
      {
         CDBYarnInfoData * pObject = GetItem(i);
         if(strYarnNo.CompareNoCase(pObject->m_strYarnNo)==0)
         {
            vecYarnInfo.push_back(pObject);
         }
      }
   }
   return vecYarnInfo;
}

CDBYarnInfoData* CDBYarnInfoList::GetItemByID(int nID)
{
	CDBYarnInfoData * pItem = NULL;
   for(int i=0;i< GetCount();i++)
   {
      CDBYarnInfoData * pObject = GetItem(i);
      if(nID==pObject->m_nID)
      {
         pItem = pObject;
         break;
      }
   }

	return pItem;
}

CDBYarnInfoData* CDBYarnInfoList::GetItemByYarnNo_NoCase(CString strYarnNo)
{
   CDBYarnInfoData * pItem = NULL;
   strYarnNo.Trim();
   if (!strYarnNo.IsEmpty())
   {
      for(int i=0;i< GetCount();i++)
      {
         CDBYarnInfoData * pObject = GetItem(i);
         if(strYarnNo.CompareNoCase(pObject->m_strYarnNo)==0)
         {
            pItem = pObject;
            break;
         }
      }
   }

   return pItem;
}

//忽略大小写
CDBYarnInfoData* CDBYarnInfoList::GetItemByYarnNoAndCate_NoCase(CString strYarnNo,CString strYarnCate)
{
   CDBYarnInfoData * pItem = NULL;
   strYarnNo.Trim();
   if (!strYarnNo.IsEmpty())
   {
      for(int i=0;i< GetCount();i++)
      {
         CDBYarnInfoData * pObject = GetItem(i);
         if(strYarnNo.CompareNoCase(pObject->m_strYarnNo)==0 && strYarnCate == pObject->m_strCate)
         {
            pItem = pObject;
            break;
         }
      }
   }

   return pItem;
}


//CDBYarnInfoList
BOOL CDBYarnInfoData::DelAllDBInfoByID(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);	
	BOOL bRet = TRUE;

	CString strSQL = _T("");
	strSQL.Format(_T("delete from %s where %s='%d'"),DB_TABLE_YARN,DBColor_key_ID,m_nID);

	if (pADOConn->ExecuteSQL(strSQL))
	{
		bRet = TRUE;
	}
	else
	{
		bRet = FALSE;
	}

	return bRet;
}
//根据色号跟类别删除【整条】记录
BOOL CDBYarnInfoData::DelAllDBInfoByYarnNoAndCate(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);	
   BOOL bRet = TRUE;

   CString strSQL = _T("");
   strSQL.Format(_T("delete from %s where %s='%s' and  %s='%s'"),DB_TABLE_YARN
      ,DBColor_key_YarnNo,m_strYarnNo
      ,DBColor_key_Cate,m_strCate);

   if (pADOConn->ExecuteSQL(strSQL))
   {
      bRet = TRUE;
   }
   else
   {
      bRet = FALSE;
   }

   return bRet;
}

BOOL CDBYarnInfoData::UpdateAllDBInfoByID( CADOConn *pADOConn )
{
	ASSERT(pADOConn != NULL);
	m_strYarnNo.Trim();
	ASSERT(!m_strYarnNo.IsEmpty());

	BOOL bRet = TRUE;
	CString strSQL = _T("");
	//								 1         2         3       4         5
	strSQL.Format(_T("update %s set  %s = %s  ,%s = '%s',%s = %d,%s = '%s',%s = '%s' \
									,%s = '%s',%s = '%s',%s = %f,%s = %lu ,%s = '%s',%s = '%s' \
									,%s = %d ,%s = %f \
									where %s = '%d'"),
									DB_TABLE_YARN,
									DBColor_key_Date		,DBS_GETDATESTR,		//1
									DBColor_key_Cate		,m_strCate,				//2
									DBColor_key_Kind		,m_nKind,				//3
									DBColor_key_YarnName	,m_strYarnName,			//4
									DBColor_key_Ingredient	,m_strIngredient,		//5
									DBColor_key_ThickNess	,m_strThickNess,		//6
									DBColor_key_Remark		,m_strRemark,			//7
									DBColor_key_Warning		,m_fWarning,			//8
									DBColor_key_RGBValue	,m_RGBValue,			//9
                           DBColor_key_RGBName, m_strRGBName,			//10
                           DBColor_key_cGroup, m_strColorGroup,			//11
									DBColor_key_State		,m_nState,				//12
                           DBColor_key_fKucunYujing,m_fKucunYujing,//13
									DBColor_key_ID		,m_nID			//14
                           
									);

	if (pADOConn->ExecuteSQL(strSQL))
	{
		bRet = TRUE;
	}
	else
	{
		bRet = FALSE;
	}

	return bRet;
}
//根据色号跟类别更新【整条】记录
BOOL CDBYarnInfoData::UpdateAllDBInfoByYarnNoAndCate(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);
   m_strYarnNo.Trim();
   ASSERT(!m_strYarnNo.IsEmpty());

   BOOL bRet = TRUE;
   CString strSQL = _T("");
   //								 1         2         3       4         5
   strSQL.Format(_T("update %s set  %s = %s,%s = %d,%s = '%s',%s = '%s' \
                    ,%s = '%s',%s = '%s',%s = %f,%s = %lu ,%s = '%s',%s = '%s' \
                    ,%s = %d ,%s = %f \
                    where %s = '%s' and %s = '%s'"),
                    DB_TABLE_YARN,
                    DBColor_key_Date		,DBS_GETDATESTR,		//1                    
                    DBColor_key_Kind		,m_nKind,				//3
                    DBColor_key_YarnName	,m_strYarnName,			//4
                    DBColor_key_Ingredient	,m_strIngredient,		//5
                    DBColor_key_ThickNess	,m_strThickNess,		//6
                    DBColor_key_Remark		,m_strRemark,			//7
                    DBColor_key_Warning		,m_fWarning,			//8
                    DBColor_key_RGBValue	,m_RGBValue,			//9
                    DBColor_key_RGBName, m_strRGBName,			//10
                    DBColor_key_cGroup, m_strColorGroup,			//11
                    DBColor_key_State		,m_nState,				//12
                    DBColor_key_fKucunYujing,m_fKucunYujing,//13
                    DBColor_key_YarnNo		,m_strYarnNo,			//14
                    DBColor_key_Cate		,m_strCate			//15
                    );

   if (pADOConn->ExecuteSQL(strSQL))
   {
      bRet = TRUE;
   }
   else
   {
      bRet = FALSE;
   }

   return bRet;
}
//根据纱线号跟纱线类别更新上架状态记录 yangjr 2017-12-11
BOOL CDBYarnInfoData::UpdateStateByYarnNoAndCate(CADOConn *pADOConn,CString strSehao,CString strYarnCate,int iState)
{
   ASSERT(pADOConn != NULL); 

   BOOL bRet = TRUE;
   CString strSQL = _T("");  
   strSQL.Format(_T("update %s set %s = '%d',%s = %s where %s = '%s' and %s = '%s'"),
                    DB_TABLE_YARN,                   
                    DBColor_key_State		,iState,				//11
                    DBColor_key_Date      ,DBS_GETDATESTR,
                    DBColor_key_YarnNo		,strSehao			//11
                    ,DBColor_key_Cate,strYarnCate
                    );

   if (pADOConn->ExecuteSQL(strSQL))
   {
      bRet = TRUE;
   }
   else
   {
      bRet = FALSE;
   }

   return bRet;
}
//根据纱线号获取色号图片 yangjr 2018/1/30
BOOL CDBYarnInfoData::GetPictureDataByYarnNoAndCate(CADOConn *pADOConn,CString strSehao,CString strYarnCate, Image *&pYarnColorCard)
{
   ASSERT(pADOConn != NULL);
   CString strSQL = _T("");
   strSQL.Format(_T("select %s from %s where %s='%s' and %s='%s'"),DBColor_key_ColorCard,DB_TABLE_YARN
      ,DBColor_key_YarnNo,strSehao
      ,DBColor_key_Cate,strYarnCate);
   pADOConn->GetRecordSet(strSQL);
   while (!pADOConn->adoEOF())   
   {
      CDBImage oImage;
      pYarnColorCard = oImage.NewImageFromDB(DBColor_key_ColorCard,pADOConn->GetRecoPtr());
      return TRUE;

   }
   return FALSE;
}

//根据纱线号更新锁存值 yangjr 2018/1/9
BOOL CDBYarnInfoData::UpdateWarnValueByYarnNoAndCate(CADOConn *pADOConn,CString strSehao,CString strYarnCate,double fWarnValue)
{
   ASSERT(pADOConn != NULL); 

   BOOL bRet = TRUE;
   CString strSQL = _T("");  
   strSQL.Format(_T("update %s set %s = %f,%s = %s where %s = '%s' and %s = '%s'"),
      DB_TABLE_YARN,                   
      DBColor_key_Warning		,fWarnValue,				//11
      DBColor_key_Date      ,DBS_GETDATESTR,
      DBColor_key_YarnNo		,strSehao			//11
      ,DBColor_key_Cate,strYarnCate
      );

   if (pADOConn->ExecuteSQL(strSQL))
   {
      bRet = TRUE;
   }
   else
   {
      bRet = FALSE;
   }

   return bRet;
}

//根据纱线号更新库存预警值 yangjr 2018/4/24
BOOL CDBYarnInfoData::UpdateKucunYujingByYarnNoAndCate(CADOConn *pADOConn,CString strSehao,CString strYarnCate,double fKucunYujing)
{
   ASSERT(pADOConn != NULL); 

   BOOL bRet = TRUE;
   CString strSQL = _T("");  
   strSQL.Format(_T("update %s set %s = %f,%s = %s where %s = '%s' and %s = '%s'"),
      DB_TABLE_YARN,                   
      DBColor_key_fKucunYujing		,fKucunYujing,				//11
      DBColor_key_Date      ,DBS_GETDATESTR,
      DBColor_key_YarnNo		,strSehao			//11
      ,DBColor_key_Cate,strYarnCate
      );

   if (pADOConn->ExecuteSQL(strSQL))
   {
      bRet = TRUE;
   }
   else
   {
      bRet = FALSE;
   }

   return bRet;
}
CString CDBYarnInfoData::SetDBEquals_Log(CDBYarnInfoData &pOldData)
{
   CString strActLog = _T("");
   if (m_strCate != pOldData.m_strCate)
   {
      CString strCate;
      if (m_strCate.IsEmpty())
      {
         strCate = _T("空值");
      }
      strCate = m_strCate;
      strActLog += _T("类别:") + strCate + _T(",");
   }
   if (m_strYarnNo != pOldData.m_strYarnNo)
   {
      CString strYarnNo;
      if (m_strYarnNo.IsEmpty())
      {
         strYarnNo = _T("空值");
      }
      strYarnNo = m_strYarnNo;
      strActLog += _T("纱线号:") + strYarnNo + _T(",");
   }
   if (m_strYarnName != pOldData.m_strYarnName)
   {
      CString strYarnName;
      if (m_strYarnName.IsEmpty())
      {
         strYarnName = _T("空值");
      }
      strYarnName = m_strYarnName;
      strActLog += _T("纱线名称:") + strYarnName + _T(",");
   }
   if ( m_strIngredient  != pOldData.m_strIngredient )
   {
      CString strIngredient;
      if ( m_strIngredient.IsEmpty())
      {
         strIngredient = _T("空值");
      }
      strIngredient =  m_strIngredient;
      strActLog += _T("纱线成分:") + strIngredient + _T(",");
   }
   if (m_strThickNess != pOldData.m_strThickNess)
   {
      CString strThickNess;
      if (m_strThickNess.IsEmpty())
      {
         strThickNess = _T("空值");
      }
      strThickNess = m_strThickNess;
      strActLog += _T("支数:") + strThickNess + _T(",");
   }
   if (m_strRemark != pOldData.m_strRemark)
   {
      CString strRemark;
      if (m_strRemark.IsEmpty())
      {
         strRemark = _T("空值");
      }
      strRemark = m_strRemark;
      strActLog += _T("备注:") + strRemark + _T(",");
   }
   if (m_fWarning != pOldData.m_fWarning)
   {
      CString str_Warning;
      str_Warning.Format(FORMAT_WEIGHT,m_fWarning);
      if (str_Warning.IsEmpty())
      {
         str_Warning = _T("空值");
      }
      strActLog += _T("锁存数量:") + str_Warning + _T(",");
   }
   if (m_strRGBName != pOldData.m_strRGBName)
   {
      CString strRGBName;
      if (m_strRGBName.IsEmpty())
      {
         strRGBName = _T("空值");
      }
      strRGBName = m_strRGBName;
      strActLog += _T("颜色名称:") + strRGBName + _T(",");
   }
   if (m_nKind  != pOldData.m_nKind )
   {
      CString str_Kind;
      str_Kind.Format(FORMAT_INT,m_nKind);
      if(m_nKind == 0)
      {
         str_Kind = _T("主料");
      }
      else
      {
         str_Kind = _T("辅料");
      }
      strActLog += _T("种类:") + str_Kind + _T(",");
   }
   if (m_nState != pOldData.m_nState)
   {
      CString str_State;
      if (m_nState == 1)
      {
         str_State = _T("上架");
      }
      else
      {
         str_State = _T("下架");
      }
      strActLog += _T("下架标识:") + str_State + _T(",");
   }
   if (m_fKucunYujing != pOldData.m_fKucunYujing)
   {
      CString str_KucunYujing;
      str_KucunYujing.Format(FORMAT_WEIGHT, m_fKucunYujing);
      if (str_KucunYujing.IsEmpty())
      {
         str_KucunYujing = _T("空值");
      }
      strActLog += _T("库存预警数量:") + str_KucunYujing + _T(",");
   }
   if (m_strColorGroup != pOldData.m_strColorGroup)
   {
      CString str_strColor;
      str_strColor.Format(FORMAT_WEIGHT, m_strColorGroup);
      if (str_strColor.IsEmpty())
      {
         str_strColor = _T("空值");
      }
      strActLog += _T("库存预警数量:") + str_strColor + _T(",");
   }
   return strActLog;
}

BOOL CDBYarnInfoData::InsertAllDBInfoByYarnID( CADOConn *pADOConn )
{
	ASSERT(pADOConn != NULL);
	m_strYarnNo.Trim();
	ASSERT(!m_strYarnNo.IsEmpty());

	BOOL bRet = TRUE;

	CString strSQL = _T(""),strFormat = _T(""),strValue = _T("");
	strFormat.Format(_T("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s"),
		DBColor_key_Date		,//1
		DBColor_key_Cate		,//2
		DBColor_key_YarnNo		,//3
		DBColor_key_YarnName	,//4
		DBColor_key_Ingredient	,//5
		DBColor_key_ThickNess	,//6
		DBColor_key_Remark		,//7
		DBColor_key_Warning		,//8
		DBColor_key_RGBValue	,//9
		DBColor_key_RGBName		,//10
		DBColor_key_Kind		,//11
		DBColor_key_State		, //12
      DBColor_key_fKucunYujing,		 //13
      DBColor_key_cGroup		 //14
		);
	//					1 ,2   ,3   ,4   ,5   ,6   ,7   ,8  ,9  ,10  ,11
	strValue.Format(_T("%s,'%s','%s','%s','%s','%s','%s',%f,%lu,'%s',%d,%d,%f,'%s'"),
		DBS_GETDATESTR		,   //1
		m_strCate			,   //2
		m_strYarnNo			,   //3
		m_strYarnName		,   //4
		m_strIngredient		,//5
		m_strThickNess		,   //6
		m_strRemark			,   //7
		m_fWarning			,   //8  ----
		m_RGBValue			,   //9  xxxx
      m_strRGBName,         //10
		m_nKind				,   //11  ----
		m_nState,			    //12
      m_fKucunYujing,       //13
      m_strColorGroup      //14
		);

	strSQL.Format(_T("insert into %s (%s) values(%s)"),DB_TABLE_YARN,strFormat,strValue);

	if (pADOConn->ExecuteSQL(strSQL))
	{
      strSQL.Format(_T("select top 1 ID from %s where %s = '%s'order by ID desc;"),DB_TABLE_YARN,DBColor_key_YarnNo,m_strYarnNo);
      pADOConn->GetRecordSet(strSQL);
      if (!pADOConn->adoEOF())
      {
         m_nID = pADOConn->GetValueInt(_T("ID"));
      }
		bRet = TRUE;
	}
	else
	{
		bRet = FALSE;
	}

	return bRet;
}

void CDBYarnInfoData::Trim()
{
	m_strCate.Trim();
	m_strYarnNo.Trim();
	m_strYarnName.Trim();
	m_strIngredient.Trim();
	m_strThickNess.Trim();
	m_strRemark.Trim();
   m_strRGBName.Trim();
   m_strColorGroup.Trim();
}

#if YARN_IMAGE
void CDBYarnInfoData::ClearColorImage()
{
	if (NULL != m_pYarnColorCard)
	{
		delete m_pYarnColorCard;
		m_pYarnColorCard = NULL;
	}
}
#endif // YARN_IMAGE

CDBYarnInfoList::CDBYarnInfoList()
{

}
CDBYarnInfoList::~CDBYarnInfoList()
{

}

CDBYarnInfoData*  CDBYarnInfoList::GetItem(int nIndex)
{
	if (nIndex<0||nIndex>=GetCount())
		return NULL;
	return (CDBYarnInfoData*)GetAt(FindIndex(nIndex));
}

void CDBYarnInfoList::AddItem(CDBYarnInfoData* pItem)
{
	CDBYarnInfoData*pData=new CDBYarnInfoData;
	pData->Copy(pItem);
	AddTail(pData);
}

void CDBYarnInfoList::DeleteItem(int nIndex)
{
	if (nIndex<0||nIndex>GetCount())
		return;
	CDBYarnInfoData *pObject=(CDBYarnInfoData*)GetItem(nIndex);
	delete pObject;
	pObject=NULL;
	RemoveAt(FindIndex(nIndex));
}

BOOL CDBYarnInfoList::DeleteItemByID(int ID)
{
   for (int i=0; i<GetCount(); ++i)
   {
      auto pItem = (CDBYarnInfoData*)GetItem(i);
      if (pItem && pItem->m_nID == ID)
      {
         delete pItem;
         pItem=NULL;
         RemoveAt(FindIndex(i));
         return TRUE;
      }
   }
   return FALSE;
}

int CDBYarnInfoList::GetIndexByID(int nID)
{
   int nSel = -1;
   for(int i=0;i< GetCount();i++)
   {
      CDBYarnInfoData * pObject = GetItem(i);
      if(nID==pObject->m_nID)
      {
         nSel = i;
         break;
      }
   }

   return nSel;
}
//设置所有项的下载图片标志 yangjr 2018/1/30
void CDBYarnInfoList::SetAllItemDownPic(bool bDownPic)
{
   for(int i=0;i<GetCount();++i)
   {
      CDBYarnInfoData * pObject = GetItem(i);
      pObject->m_bHaveDownPic = bDownPic;
   }
}

//设置对应色号的下载图片标志 yangjr 2018/1/30
void CDBYarnInfoList::SetDownPicFlagByYarnNoAndCate(CString strYarnNo,CString strYarnCate,bool bDownPic)
{
   int nSel = -1;
   strYarnNo.Trim();
   if (!strYarnNo.IsEmpty())
   {
      for(int i=0;i< GetCount();++i)
      {
         CDBYarnInfoData * pObject = GetItem(i);
         if(strYarnNo==pObject->m_strYarnNo && strYarnCate==pObject->m_strCate)
         {
            pObject->m_bHaveDownPic = bDownPic;
            break;
         }
      }
   }
}

//设置对应色号的图片数据 yangjr 2018/1/30
void CDBYarnInfoList::SetPicDataByYarnNoAndCate(CString strYarnNo,CString strYarnCate,Image* pYarnColorCard)
{
   int nSel = -1;
   strYarnNo.Trim();
   if (!pYarnColorCard)
   {
      return;
   }
   if (!strYarnNo.IsEmpty())
   {
      for(int i=0;i< GetCount();++i)
      {
         CDBYarnInfoData * pObject = GetItem(i);
         if(strYarnNo==pObject->m_strYarnNo && strYarnCate==pObject->m_strCate)
         {
#if YARN_IMAGE
            if (NULL != pObject->m_pYarnColorCard)
            {
               delete pObject->m_pYarnColorCard;
               pObject->m_pYarnColorCard = NULL;
            }
            if (pYarnColorCard)
            {
               pObject->m_pYarnColorCard = pYarnColorCard->Clone();
            }
#endif
            break;
         }
      }
   }
}

void CDBYarnInfoList::GetListFromDB(CADOConn *pADOConn, bool bNeedColorCard)
{
   ASSERT(pADOConn != NULL);

   Empty();
   CString strSQL = _T("");
   if (bNeedColorCard)
   {
      strSQL.Format(_T("select * from %s"), DB_TABLE_YARN);
   }
   else
   {
      strSQL.Format(_T("select ID,dDate,cCate,cSehao,cSeming,\
         cChenfen,cShazhi,cMemo,iYujing,cRGBValue,cRGBName,iKind,iState,'' as cColorCard,fKucunYujing,cGroup from %s"), DB_TABLE_YARN);
   }
   pADOConn->GetRecordSet(strSQL);

   while (!pADOConn->adoEOF())
   {
      CDBYarnInfoData oData;
      oData.GetAllDBInfo(pADOConn, bNeedColorCard);
      AddItem(&oData);
      pADOConn->MoveNext();
   }
}

BOOL CDBYarnInfoList::GetYarnColor(__in CADOConn *pADOConn,__in CString strSehao,__in CString strYarnCate,__out CString& strColor)
{
   ASSERT(pADOConn != NULL);
   strColor = _T("");
   CString strSQL = _T("");
   strSQL.Format(_T("select cSehao,cRGBName from Color where cSehao = '%s' and cCate = '%s';"),strSehao,strColor);
   pADOConn->GetRecordSet(strSQL);
   if (!pADOConn->adoEOF())
   {
      strColor = pADOConn->GetValueString(_T("cRGBName"));
      return TRUE;
   }
   return FALSE;
}

CDBYarnInfoList * CDBYarnInfoList::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = shared_ptr<CDBYarnInfoList>(new CDBYarnInfoList);

	return sm_inst.get();
}

#ifdef USING_GRIDCTRL_MARK
/*******************************************************************
 * @brief : 生成表格相关数据
 * @author : wzl
 * @date : 2017/6/9
 * @param : 
 * @example : 
 * @return : 返回生成的表格所需数据
 *******************************************************************/
MAP_GridCtrl_AllData CDBYarnInfoList::CreatrGridData()
{
	MAP_GridCtrl_AllData  map_all_data;

	int nIndex = 0,nCount = GetCount();
	int nValidCount = 1;
	for (nIndex = 0;nIndex < nCount;nIndex++)
	{
		CDBYarnInfoData * pData = GetItem(nIndex);
		if (NULL != pData)
		{
			MAP_GridCtrl_RowData map_row_data;

			pData->InsertRowData(DBColor_key_ID				,map_row_data, CB_enum_FieldData_Int, CB_enum_FieldCtrl_Text,FORMAT_INT	,pData->m_nID					);
			pData->InsertRowData(DBColor_key_Date			,map_row_data,CB_enum_FieldData_Time,CB_enum_FieldCtrl_DateTime,FORMAT_STRING	,pData->m_oleData.Format(_T("%Y-%m-%d %H:%M:%S"))	);//时间
			pData->InsertRowData(DBColor_key_Cate			,map_row_data,FORMAT_STRING	,pData->m_strCate				);
			
			//2017/12/29 zhangt 设置上架背景颜色
			vector<int> vecClr;
			//if (CDBYarnInfoData::State_Vilid == pData->m_nState)//上架 设置背景色
			//{
				vecClr.clear();
				vecClr.push_back(pData->m_RGBValue);
				pData->InsertRowData(DBColor_key_YarnNo		,pData->m_strYarnNo,map_row_data,CB_enum_FieldData_CString,CB_enum_FieldCtrl_Text,vecClr);
			//}
			//else 
			//{
			//	pData->InsertRowData(DBColor_key_YarnNo			,map_row_data,FORMAT_STRING	,pData->m_strYarnNo				);
			//}//2017/12/29_end

			pData->InsertRowData(DBColor_key_YarnName		,map_row_data,FORMAT_STRING	,pData->m_strYarnName			);
			pData->InsertRowData(DBColor_key_Ingredient		,map_row_data,FORMAT_STRING	,pData->m_strIngredient			);
			pData->InsertRowData(DBColor_key_ThickNess		,map_row_data,FORMAT_STRING	,pData->m_strThickNess			);
			pData->InsertRowData(DBColor_key_Remark			,map_row_data,FORMAT_STRING	,pData->m_strRemark				);
			pData->InsertRowData(DBColor_key_Warning		,map_row_data,CB_enum_FieldData_Double4Point,CB_enum_FieldCtrl_Text,FORMAT_WEIGHT	,pData->m_fWarning				);
			pData->InsertRowData(DBColor_key_RGBValue		,map_row_data,_T("%u"),pData->m_RGBValue				);
			pData->InsertRowData(DBColor_key_RGBName		,map_row_data,FORMAT_STRING	,pData->m_strRGBName			);
			pData->InsertRowData(DBColor_key_State			,map_row_data,FORMAT_INT	,pData->m_nState				);
			switch(pData->m_nKind)
			{
			case 0:
				pData->InsertRowData(DBColor_key_Kind			,map_row_data,_T("主料")	/*,pData->m_nKind					*/);
				break;
			case 1:
				pData->InsertRowData(DBColor_key_Kind			,map_row_data,_T("辅料")	/*,pData->m_nKind					*/);
				break;
			}
         pData->InsertRowData(DBColor_key_fKucunYujing, map_row_data, CB_enum_FieldData_Double4Point, CB_enum_FieldCtrl_Text, FORMAT_WEIGHT, pData->m_fKucunYujing);
         pData->InsertRowData(DBColor_key_cGroup, map_row_data, FORMAT_STRING,pData->m_strColorGroup);//色组 by huangym 2018/12/19
			//写入行数据

			map_all_data.insert(make_pair(nValidCount,map_row_data));
			//行数据插入所有数据中

			nValidCount++;
		}
	}
	return map_all_data;
}

MAP_GridCtrl_AllData CDBYarnInfoList::CreatrGridData_Sehao()
{
   MAP_GridCtrl_AllData  map_all_data;

   int nIndex = 0,nCount = GetCount();
   int nValidCount = 1;
   for (nIndex = 0;nIndex < nCount;nIndex++)
   {
      CDBYarnInfoData * pData = GetItem(nIndex);
      if (NULL != pData)
      {
         MAP_GridCtrl_RowData map_row_data;

         pData->InsertRowData(DBColor_key_YarnNo			,map_row_data,FORMAT_STRING	,pData->m_strYarnNo				);//色号
         pData->InsertRowData(DBColor_key_Cate			,map_row_data,FORMAT_STRING	,pData->m_strCate				); //纱线类别
         map_all_data.insert(make_pair(nValidCount,map_row_data));
         //行数据插入所有数据中
         nValidCount++;
      }
   }
   return map_all_data;
}

//生成一条空的行数据			by WangZY 2017/08/24
BOOL CDBYarnInfoList::GetEmptyRowData(__out MAP_GridCtrl_RowData &mapEmptyRowData)
{
	mapEmptyRowData.clear();

	InsertRowData(DBColor_key_ID			,_T(""), mapEmptyRowData, CB_enum_FieldData_Int, CB_enum_FieldCtrl_Text);
	InsertRowData(DBColor_key_Date		,_T(""), mapEmptyRowData,CB_enum_FieldData_Time,CB_enum_FieldCtrl_DateTime);//时间
	InsertRowData(DBColor_key_Cate		,_T(""), mapEmptyRowData);
	InsertRowData(DBColor_key_YarnNo		,_T(""), mapEmptyRowData);
	InsertRowData(DBColor_key_YarnName	,_T(""), mapEmptyRowData);
	InsertRowData(DBColor_key_Ingredient,_T(""), mapEmptyRowData);
	InsertRowData(DBColor_key_ThickNess	,_T(""), mapEmptyRowData);
	InsertRowData(DBColor_key_Remark		,_T(""), mapEmptyRowData);
	InsertRowData(DBColor_key_Warning	,_T(""), mapEmptyRowData,CB_enum_FieldData_Double2Point,CB_enum_FieldCtrl_Text);
	InsertRowData(DBColor_key_RGBValue	,_T(""), mapEmptyRowData);
	InsertRowData(DBColor_key_RGBName	,_T(""), mapEmptyRowData);
	InsertRowData(DBColor_key_Kind		,_T(""), mapEmptyRowData);
	InsertRowData(DBColor_key_State		,_T(""), mapEmptyRowData);
	InsertRowData(DBColor_key_fKucunYujing		,_T(""), mapEmptyRowData);
	return TRUE;

}

//批量提交数据修改		by WangZY 2017/08/24
BOOL CDBYarnInfoList::SaveMultiModifyData(__in CADOConn *pADOConn, 
										__in MAP_GridCtrl_AllData &mapAddData, 
										__in MAP_GridCtrl_AllData &mapModifyData, 
										__in MAP_GridCtrl_AllData &mapDeleteData, 
										__in CString strMaker)
{
	ASSERT(pADOConn != NULL);

	//需要写提交代码		by WangZY 2017/08/27
	CString strSQL = _T("");

	//执行删除
	for (auto it=mapDeleteData.begin(); it!=mapDeleteData.end(); ++it)
	{
#pragma region 色号批量删除
		CString strID; 
		auto itData = it->second.find(DBColor_key_ID);
		if (itData == it->second.end())
		{
			return FALSE;
		}
		strID = itData->second.strValue;

		strSQL.Format(_T("Delete FROM %s where %s='%s'"),
			DB_TABLE_YARN,DBColor_key_ID,strID);
		
		pADOConn->AppendBatchSQL(strSQL);
#pragma endregion 色号批量删除

//#pragma region 删除日志
//
//	
//		CString strCate;
//		CString strYarnNo;
//		CString strYarnName;
//		CString strDate;
//	
//		//类别
//		itData = it->second.find(DBColor_key_Cate);
//		if (itData != it->second.end())
//		{
//			strCate = itData->second.strValue;
//		}
//
//		//纱号
//		itData = it->second.find(DBColor_key_YarnNo);
//		if (itData != it->second.end())
//		{
//			strYarnNo = itData->second.strValue;
//		}
//
//		//纱名
//		itData = it->second.find(DBColor_key_YarnName);
//		if (itData != it->second.end())
//		{
//			strYarnName = itData->second.strValue;
//		}
//
//		//日期
//		itData = it->second.find(DBColor_key_Date);
//		if (itData != it->second.end())
//		{
//			strDate = itData->second.strValue;
//		}
//		
//		//操作日志sql
//		CString strSQLLog;
//
//		strSQLLog.Format(_T("insert into WorkLog(cCate,cType,cCode,cMaker,cMemo) \
//								  values('色号','色号批量删除','%s','%s',\
//								  '%s,%s,%s,%s,%s,%s')"),
//								  strID,strMaker,strID, strCate, strYarnNo,
//								  strYarnName,strDate,strMaker);
//
//		pADOConn->AppendBatchSQL(strSQLLog);
//#pragma endregion 删除日志
	}


	//BOOL bBegin = pADOConn->BeginTrans();
	//if (!bBegin)
	//{
	//return FALSE;
	//}
	
	BOOL bExec = pADOConn->ExecuteBatchSQL();
	if (!bExec)
	{
		//BOOL bRollback = pADOConn->RollbackTrans();

		return FALSE;
	}

	//执行修改
	BOOL bUpdateSuccess = TRUE;
	for (auto it=mapModifyData.begin(); it!=mapModifyData.end(); ++it)
	{
#pragma region 色号批量修改
		CString strID; 
		auto itData = it->second.find(DBColor_key_ID);
		if (itData == it->second.end())
		{
			bUpdateSuccess = FALSE;
			
			break;
		}
		strID = itData->second.strValue;

		CString strCate;		
		CString strKind;			
		CString strYarnName;	
		CString strIngredient;
		CString strThickNess;	
		CString strRemark;		
		CString strWarning;		
		CString strRGBValue;		
		CString strRGBName;	
		CString strYarnNo;		
		CString strDate;
		CString strState;
      CString strKucunYujing;
		itData = it->second.find(DBColor_key_Cate);
		if (itData != it->second.end())
		{
			strCate = itData->second.strValue;
		}

		itData = it->second.find(DBColor_key_Kind);
		if (itData != it->second.end())
		{
			strKind = itData->second.strValue;
			if (strKind == _T("主料"))
			{
				strKind.Format(FORMAT_INT,0);
			}
			else
			{
				strKind = _T("1");
			}
		}

		itData = it->second.find(DBColor_key_YarnName);
		if (itData != it->second.end())
		{
			strYarnName = itData->second.strValue;
		}

		itData = it->second.find(DBColor_key_YarnNo);
		if (itData != it->second.end())
		{
			strYarnNo = itData->second.strValue;
		}

		itData = it->second.find(DBColor_key_RGBName);
		if (itData != it->second.end())
		{
			strRGBName = itData->second.strValue;
		}

		itData = it->second.find(DBColor_key_RGBValue);
		if (itData != it->second.end())
		{
			strRGBValue = itData->second.strValue;
		}

		itData = it->second.find(DBColor_key_Ingredient);
		if (itData != it->second.end())
		{
			strIngredient = itData->second.strValue;
		}

		itData = it->second.find(DBColor_key_ThickNess);
		if (itData != it->second.end())
		{
			strThickNess = itData->second.strValue;
		}

		itData = it->second.find(DBColor_key_Remark);
		if (itData != it->second.end())
		{
			strRemark = itData->second.strValue;
		}

		itData = it->second.find(DBColor_key_Warning);
		if (itData != it->second.end())
		{
			strWarning = itData->second.strValue;
		}

		//日期
		itData = it->second.find(DBColor_key_Date);
		if (itData != it->second.end())
		{
			strDate = itData->second.strValue;
		}

		itData = it->second.find(DBColor_key_State);
		if (itData != it->second.end())
		{
			strState = itData->second.strValue;
		}
      itData = it->second.find(DBColor_key_fKucunYujing);
      if (itData != it->second.end())
      {
         strKucunYujing = itData->second.strValue;
      }

		strSQL.Format(_T("update %s set  %s = '%s'  ,%s = '%s',%s = '%s',%s = '%s', \
							  %s = '%s',%s = '%s',%s = '%s',%s = '%s',%s = '%s' , \
							  %s = '%s',%s = '%s',%s = '%s',%s = '%s' \
							  where %s = '%s'"),
							  DB_TABLE_YARN,
							  DBColor_key_Date		,strDate,			//1
							  DBColor_key_Cate		,strCate,			//2
							  DBColor_key_Kind		,strKind,			//3
							  DBColor_key_YarnName	,strYarnName,		//4
							  DBColor_key_Ingredient,strIngredient,	//5
							  DBColor_key_ThickNess	,strThickNess,		//6
							  DBColor_key_Remark		,strRemark,			//7
							  DBColor_key_Warning	,strWarning,		//8
							  DBColor_key_RGBValue	,strRGBValue,		//9
							  DBColor_key_RGBName	,strRGBName,		//10
							  DBColor_key_YarnNo		,strYarnNo,			//11
							  DBColor_key_State		,strState,
                       DBColor_key_fKucunYujing		,strKucunYujing,
							  DBColor_key_ID			,strID				//12
							  );

		pADOConn->ExecuteSQL(strSQL);
#pragma endregion 色号批量修改

//#pragma region 批量修改日志
//		//操作日志sql
//		CString strSQLLog;
//
//		strSQLLog.Format(_T("insert into WorkLog(cCate,cType,cCode,cMaker,cMemo) \
//								  values('色号','色号批量修改','%s','%s',\
//								  '%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s')"),
//								  strID,strMaker,
//								  strID,strCate,strKind,strYarnName,	
//								  strIngredient,strThickNess,strRemark,strWarning,
//								  strRGBValue,strRGBName,strYarnNo,strMaker,strState);
//		
//		pADOConn->ExecuteSQL(strSQLLog);
//
//#pragma endregion 批量修改日志
	}
	
	if (!bUpdateSuccess)
	{
		//BOOL bRollback = pADOConn->RollbackTrans();

		return FALSE;
	}

	//执行新增
	BOOL bAddSuccess = TRUE;
	for (auto it=mapAddData.begin(); it!=mapAddData.end(); ++it)
	{
#pragma region 色号批量新增

		CString strCate;		
		CString strKind;			
		CString strYarnName;	
		CString strIngredient;
		CString strThickNess;	
		CString strRemark;		
		CString strWarning;		
		CString strRGBValue;		
		CString strRGBName;	
		CString strYarnNo;		
		CString strDate;
		CString strState;
      CString strKucunYujing;
		auto itData = it->second.find(DBColor_key_Cate);
		if (itData != it->second.end())
		{
			strCate = itData->second.strValue;
		}

		itData = it->second.find(DBColor_key_Kind);
		if (itData != it->second.end())
		{
			strKind = itData->second.strValue;
		}

		itData = it->second.find(DBColor_key_YarnName);
		if (itData != it->second.end())
		{
			strYarnName = itData->second.strValue;
		}

		itData = it->second.find(DBColor_key_YarnNo);
		if (itData != it->second.end())
		{
			strYarnNo = itData->second.strValue;
		}

		itData = it->second.find(DBColor_key_RGBName);
		if (itData != it->second.end())
		{
			strRGBName = itData->second.strValue;
		}

		itData = it->second.find(DBColor_key_RGBValue);
		if (itData != it->second.end())
		{
			strRGBValue = itData->second.strValue;
		}

		itData = it->second.find(DBColor_key_Ingredient);
		if (itData != it->second.end())
		{
			strIngredient = itData->second.strValue;
		}

		itData = it->second.find(DBColor_key_ThickNess);
		if (itData != it->second.end())
		{
			strThickNess = itData->second.strValue;
		}

		itData = it->second.find(DBColor_key_Remark);
		if (itData != it->second.end())
		{
			strRemark = itData->second.strValue;
		}

		itData = it->second.find(DBColor_key_Warning);
		if (itData != it->second.end())
		{
			strWarning = itData->second.strValue;
		}

		//日期
		itData = it->second.find(DBColor_key_Date);
		if (itData != it->second.end())
		{
			strDate = itData->second.strValue;
		}

		itData = it->second.find(DBColor_key_State);
		if (itData != it->second.end())
		{
			strState = itData->second.strValue;
		}
      itData = it->second.find(DBColor_key_fKucunYujing);
      if (itData != it->second.end())
      {
         strKucunYujing = itData->second.strValue;
      }

		strSQL.Format(_T("insert into %s(%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s)\
			values('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s')"),
							  DB_TABLE_YARN,
							  DBColor_key_Date		,
							  DBColor_key_Cate		,
							  DBColor_key_Kind		,
							  DBColor_key_YarnName	,
							  DBColor_key_Ingredient,
							  DBColor_key_ThickNess	,
							  DBColor_key_Remark		,
							  DBColor_key_Warning	,
							  DBColor_key_RGBValue	,
							  DBColor_key_RGBName	,
							  DBColor_key_YarnNo		,
							  DBColor_key_State		,
                       DBColor_key_fKucunYujing		,
							  strDate,		
							  strCate,		
							  strKind,		
							  strYarnName,	
							  strIngredient,
							  strThickNess,	
							  strRemark,		
							  strWarning,	
							  strRGBValue,	
							  strRGBName,	
							  strYarnNo,
							  strState,
                       strKucunYujing
							  );

		BOOL bExec = pADOConn->ExecuteSQL(strSQL);
		if (!bExec)
		{
			bAddSuccess = FALSE;

			break;
		}

#pragma endregion 色号批量新增

#pragma region 批量新增日志

		//操作日志sql
		CString strSQLLog;
		CString strID;
		strSQLLog.Format(_T("insert into WorkLog(cCate,cType,cCode,cMaker,cMemo) \
								  values('色号','色号批量新增','%s','%s',\
								  '%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s')"),
								  strYarnNo,strMaker,
								  strYarnNo,strCate,strKind,strYarnName,	
								  strIngredient,strThickNess,strRemark,strWarning,
								  strRGBValue,strRGBName,strMaker,strState,strKucunYujing);

		pADOConn->ExecuteSQL(strSQLLog);
#pragma endregion 批量新增日志

	}

	if (!bAddSuccess)
	{
		//BOOL bRollback = pADOConn->RollbackTrans();

		return FALSE;
	}
	
	
	//BOOL bCommit = pADOConn->CommitTrans();
	//if (!bCommit)
	//{
	//	return FALSE;
	//}

	return TRUE;
}

BOOL CDBYarnInfoList::GetRssWarningSehao(__in CADOConn* pADOConn,__in CString strData,__out vector<CString>& vecSehao,__out CString& strCurDate)
{
	ASSERT(pADOConn != NULL);
	vecSehao.clear();
	CString strSQL = _T("");
	if (!strCurDate.IsEmpty())
	{
		
		strSQL.Format(_T("select cSehao, CONVERT(VARCHAR(10),dDate,120) as dDate from Color where iState <> 1 and CONVERT(VARCHAR(10),dDate,120) < '%s'"),strData);
		pADOConn->GetRecordSet(strSQL);
		while(!pADOConn->adoEOF())
		{
			CString strSehao = pADOConn->GetValueString(_T("cSehao"));
			vecSehao.push_back(strSehao);
			pADOConn->MoveNext();
		}
	}
	strSQL = _T("select CONVERT(VARCHAR(10),GETDATE(),120) as dDate;");
	pADOConn->GetRecordSet(strSQL);
	if (!pADOConn->adoEOF())
	{
		strCurDate = pADOConn->GetValueString(_T("dDate"));
	}
	return TRUE;
}

//按品种信息初始化指定id的色号的成份信息		by WangZY 2018/05/07
BOOL CDBYarnInfoList::InitChenfenInfo(__in CADOConn* pADOConn,__in CString strIDFilter)
{
	ASSERT(pADOConn != NULL);

	CString strSQL = _T("");

	strSQL.Format(_T("update Color \
		set cChenfen=(select top 1 cChenfen from PinZhongSetting P \
		where p.cCate=Color.cCate) \
		%s "),
		strIDFilter);
	BOOL bRet = pADOConn->ExecuteSQL(strSQL);
	
	return bRet;
}

void CDBYarnInfoList::GetYarn_Cate_CF_Info(CADOConn *pADOConn,CString strYarnNo,CString& strYarnCate,CString& strCF)
{
   strYarnCate = _T("");
   strCF = _T("");
   if (strYarnNo.IsEmpty())
      return;

   ASSERT(pADOConn != NULL);
   CString strSQL = _T("");
   strSQL.Format(_T("select %s,%s from %s where %s = '%s';"),DBColor_key_Cate,DBColor_key_Ingredient,DB_TABLE_YARN,DBColor_key_YarnNo,strYarnNo);
   pADOConn->GetRecordSet(strSQL);
   if (!pADOConn->adoEOF())
   {
      strYarnCate = pADOConn->GetValueString(DBColor_key_Cate);
      strCF = pADOConn->GetValueString(DBColor_key_Ingredient);
   }
}

void CDBYarnInfoList::GetYarnCateCF(CADOConn *pADOConn,map<CString,CString>& mapData)
{
   mapData.clear();
   ASSERT(pADOConn != NULL);
   CString strSQL = _T("");
   strSQL.Format(_T("select cCate,cChenfen from Color where cChenfen <> '' group by cCate,cChenfen"));
   pADOConn->GetRecordSet(strSQL);
   while (!pADOConn->adoEOF())
   {
      mapData.insert(make_pair(pADOConn->GetValueString(DBColor_key_Cate),pADOConn->GetValueString(DBColor_key_Ingredient)));
      pADOConn->MoveNext();
   }
}

BOOL CDBYarnInfoList::GetYarnInfoBySehao(__in CADOConn *pADOConn,__in CString strSehao,__out CDBYarnInfoData* pObj)
{
   if (pObj == NULL)
   {
      ASSERT(pObj != NULL);
      return FALSE;
   }
   ASSERT(pADOConn != NULL);
   CString strSQL = _T("");
   strSQL.Format(_T("select top 1 * from Color where cSehao = '%s'"),strSehao);
   pADOConn->GetRecordSet(strSQL);
   if (!pADOConn->adoEOF())
   {
      pObj->GetAllDBInfo(pADOConn);
      return TRUE;
   }
   return FALSE;
}

#endif // USING_GRIDCTRL_MARK

BOOL CDBYarnInfoList::CheckSeHaoIsExists(__in CADOConn *pADOConn,__in CString strSehao)
{
   ASSERT(pADOConn != NULL);
   CString strSQL = _T("");
   strSQL.Format(_T("select count(*) as num from Color where cSehao = '%s'"),strSehao);
   pADOConn->GetRecordSet(strSQL);
   if (!pADOConn->adoEOF())
   {
      int iNum = pADOConn->GetValueInt(_T("num"));
      if (iNum >0)
         return TRUE;
   }
   return FALSE;
}






