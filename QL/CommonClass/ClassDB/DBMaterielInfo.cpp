#include "StdAfx.h"
#include "DBMaterielInfo.h"
#include "DBKeyDef.h"

#if MATERIEL_IMAGE
#include "..\ClassEx\ADOConn\DBImage.h"
#endif

using namespace Gdiplus;


///////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CDBMaterielInfoData,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBMaterielInfoList,  CDataListMid, 1)

std::shared_ptr<CDBMaterielInfoData> CDBMaterielInfoData::sm_inst;
std::shared_ptr<CDBMaterielInfoList> CDBMaterielInfoList::sm_inst;

CDBMaterielInfoData::CDBMaterielInfoData()
{
#if MATERIEL_IMAGE
	m_pMaterielPic = nullptr;
#endif // YARN_IMAGE
	ResetData(); 
} 

CDBMaterielInfoData::~CDBMaterielInfoData()
{
#if MATERIEL_IMAGE
	ClearColorImage();
#endif // YARN_IMAGE
}

void CDBMaterielInfoData::ResetData()
{
   m_strID         = _T("");	//物料编号
   m_strName       = _T("");	//物料名称
   m_strLevel1Type = _T("");	//一级类别
   m_strLevel2Type = _T("");	//二级类别 
   m_strLevel3Type = _T("");	//三级类别 
   m_strLevel4Type = _T("");	//四级类别 
   m_strLevel5Type = _T("");	//五级类别 
   m_strUnit       = _T("");	//物料单位
   m_strChengfen   = _T("");	//物料材质(成份)
   m_strMemo       = _T("");	//物料说明
   m_nPrice        = 0.00;	      //物料单价
   m_strBrand      = _T("");	//物料品牌
   m_strSupplier   = _T("");    //供应商

   m_strActLog     = _T("");  //操作日志
#if MATERIEL_IMAGE
	ClearColorImage();
#endif // YARN_IMAGE
   m_bHaveDownPic = false;//图片是否已下载 yangjr 2017/1/30
	SetDataType(DAT_YARN);
}

void CDBMaterielInfoData:: Copy(CDBMaterielInfoData *pData)
{
	ASSERT(pData != NULL);
	CDataMid::Copy(pData);

   m_strID			 = pData->m_strID;			   //物料编号
   m_strName		 = pData->m_strName;		      //物料名称
   m_strLevel1Type = pData->m_strLevel1Type;	   //一级类别
   m_strLevel2Type = pData->m_strLevel2Type;	   //二级类别 
   m_strLevel3Type = pData->m_strLevel3Type;	   //三级类别 
   m_strLevel4Type = pData->m_strLevel4Type;	   //四级类别 
   m_strLevel5Type = pData->m_strLevel5Type;	   //五级类别 
   m_strUnit		 = pData->m_strUnit;		      //物料单位
   m_strChengfen	 = pData->m_strChengfen;	   //物料材质(成份)
   m_strMemo       = pData->m_strMemo;	         //物料说明
   m_nPrice        = pData->m_nPrice;	         //物料单价
   m_strBrand      = pData->m_strBrand;	      //物料品牌
   m_strSupplier   = pData->m_strSupplier;      //供应商

#if MATERIEL_IMAGE
	ClearColorImage();
	if (pData->m_pMaterielPic)
	{
		m_pMaterielPic = pData->m_pMaterielPic->Clone();
	}
   m_bHaveDownPic = pData->m_bHaveDownPic;//图片是否已下载 yangjr 2017/1/30
#endif
}

void CDBMaterielInfoData::Serialize(CArchive& ar)
{
	CDataMid::Serialize(ar);//父类函数

	int nTagSize = 0;
	CString strName;
	int nNameSize;

	ar.Flush();
	if (ar.IsStoring())
	{
      MySerial.SaveDataStr(ar,_T("ID"),         m_strID			);
      MySerial.SaveDataStr(ar,_T("Name"),       m_strName		);
      MySerial.SaveDataStr(ar,_T("Level1Type"), m_strLevel1Type);
      MySerial.SaveDataStr(ar,_T("Level2Type"), m_strLevel2Type);
      MySerial.SaveDataStr(ar,_T("Level3Type"), m_strLevel3Type);
      MySerial.SaveDataStr(ar,_T("Level4Type"), m_strLevel4Type);
      MySerial.SaveDataStr(ar,_T("Level5Type"), m_strLevel5Type);
      MySerial.SaveDataStr(ar,_T("Unit"),       m_strUnit		);
      MySerial.SaveDataStr(ar,_T("Chengfen"),   m_strChengfen	);
      MySerial.SaveDataStr(ar, _T("Memo"), m_strMemo);
      CString strPrice = _T("");
      strPrice.Format(_T("%.2lf"), m_nPrice);
      MySerial.SaveDataStr(ar, _T("Price"), strPrice);
      MySerial.SaveDataStr(ar, _T("Brand"), m_strBrand);

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
		{
         return;
      }

		while(strName != _T("DENDDEND"))
		{
			if(nNumber > 200)
			{
				return;
			}
         else if (strName == _T("ID"))
         {         
            ar >> nTagSize >>m_strID;   
         }   
         else if (strName == _T("Name"))      
         {         
            ar >> nTagSize >>m_strName;   
         }   
         else if (strName == _T("Level1Type"))      
         {         
            ar >> nTagSize >>m_strLevel1Type;   
         }   
         else if (strName == _T("Level2Type"))      
         {         
            ar >> nTagSize >>m_strLevel2Type;   
         }   
         else if (strName == _T("Level3Type"))      
         {         
            ar >> nTagSize >>m_strLevel3Type;   
         }   
         else if (strName == _T("Level4Type"))      
         {         
            ar >> nTagSize >>m_strLevel4Type;   
         }   
         else if (strName == _T("Level5Type"))      
         {         
            ar >> nTagSize >>m_strLevel5Type;   
         }   
         else if (strName == _T("Unit"))      
         {         
            ar >> nTagSize >>m_strUnit;   
         }   
         else if (strName == _T("Chengfen"))      
         {         
            ar >> nTagSize >>m_strChengfen;   
         }
         else if (strName == _T("Memo"))
         {
            ar >> nTagSize >> m_strMemo;
         }
         else if (strName == _T("Price"))
         {
            CString strPrice = _T("");
            strPrice.Format(_T("%.2lf"), m_nPrice);
            ar >> nTagSize >> strPrice;
         }
         else if (strName == _T("Brand"))
         {
            ar >> nTagSize >> m_strBrand;
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
			{
            return;
         }
			nNumber++;
		}
	}
}

CDBMaterielInfoData * CDBMaterielInfoData::Instance()
{
	if(sm_inst.get() == 0)
	{
      sm_inst = shared_ptr<CDBMaterielInfoData>(new CDBMaterielInfoData);
   }

	return sm_inst.get();
}

BOOL CDBMaterielInfoData::GetAllDBInfo(CADOConn *pADOConn,bool bNeedPic)
{
	ASSERT(pADOConn != NULL);

	BOOL bRet = TRUE;

	if (NULL == pADOConn)
	{
		bRet = FALSE;
	}
	else
	{
      m_strID  		 = pADOConn->GetValueString(DBMateriel_Key_ID         );
      m_strName		 = pADOConn->GetValueString(DBMateriel_Key_cName      );
      m_strLevel1Type = pADOConn->GetValueString(DBMateriel_Key_cLevel1Type);
      m_strLevel2Type = pADOConn->GetValueString(DBMateriel_Key_cLevel2Type);
      m_strLevel3Type = pADOConn->GetValueString(DBMateriel_Key_cLevel3Type);
      m_strLevel4Type = pADOConn->GetValueString(DBMateriel_Key_cLevel4Type);
      m_strLevel5Type = pADOConn->GetValueString(DBMateriel_Key_cLevel5Type);
      m_strUnit		 = pADOConn->GetValueString(DBMateriel_Key_cUnit      );
      m_strChengfen	 = pADOConn->GetValueString(DBMateriel_Key_cChengFen  );
      m_strMemo       = pADOConn->GetValueString(DBMateriel_Key_cMemo      );
      m_nPrice        = pADOConn->GetValueDouble(DBMateriel_Key_cPrice        );
      m_strBrand      = pADOConn->GetValueString(DBMateriel_Key_cBrand     );
      m_strSupplier   = pADOConn->GetValueString(DBMateriel_Key_cSupplier  );

      if (bNeedPic)
      {
#if MATERIEL_IMAGE
         ClearColorImage();
         CDBImage oImage;
         m_pMaterielPic = oImage.NewImageFromDB(DBMateriel_Key_cPic,
            pADOConn->GetRecoPtr());

#endif // YARN_IMAGE

         m_bHaveDownPic = true;
      }else
      {
         m_bHaveDownPic = false;
      }
		bRet = TRUE;
	}

	return bRet;
}




BOOL CDBMaterielInfoData::DelAllDBInfoByID(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);
	m_strID.Trim();
	ASSERT(!m_strID.IsEmpty());

	BOOL bRet = TRUE;

	CString strSQL = _T("");
	strSQL.Format(_T("delete from %s where %s='%s'"),
      DB_TABLE_MATERIEL_INFO,
      DBMateriel_Key_ID,m_strID);

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

BOOL CDBMaterielInfoData::UpdateAllDBInfoByID( CADOConn *pADOConn )
{
	ASSERT(pADOConn != NULL);
	m_strID.Trim();
	ASSERT(!m_strID.IsEmpty());

	BOOL bRet = TRUE;
	CString strSQL = _T("");
	//								 1         2         3       4         5
	strSQL.Format(_T("update %s set \
                    %s='%s', %s='%s', %s ='%s', %s = '%s', %s = '%s',\
                    %s='%s', %s='%s', %s ='%s', %s = '%s',%s = %.2lf,\
                    %s = '%s', %s='%s' \
						  where %s = '%s'"),
						DB_TABLE_MATERIEL_INFO,

                  DBMateriel_Key_cName      ,   m_strName,		      //物料名称	//2
                  DBMateriel_Key_cLevel1Type,   m_strLevel1Type,	   //一级类别	//3
                  DBMateriel_Key_cLevel2Type,   m_strLevel2Type,	   //二级类别 	//4
                  DBMateriel_Key_cLevel3Type,   m_strLevel3Type,	   //三级类别 	//5
                  DBMateriel_Key_cLevel4Type,   m_strLevel4Type,	   //四级类别 	//6
                  DBMateriel_Key_cLevel5Type,   m_strLevel5Type,	   //五级类别 	//7
                  DBMateriel_Key_cUnit      ,   m_strUnit,		      //物料单位	//8
                  DBMateriel_Key_cChengFen  ,   m_strChengfen,	      //物料材质(成份)	//9
                  DBMateriel_Key_cMemo      ,   m_strMemo,	         //物料说明	//10
                  DBMateriel_Key_cPrice     ,   m_nPrice,	         //物料单价	//11
                  DBMateriel_Key_cBrand     ,   m_strBrand,	         //物料品牌	//12
                  DBMateriel_Key_cSupplier  ,   m_strSupplier,       //供应商  //13
						
                  DBMateriel_Key_ID         ,   m_strID			   //物料编号	//1
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

//根据ID获取图片
BOOL CDBMaterielInfoData::GetPictureDataByID(CADOConn *pADOConn,
   CString strID, Image *&pPic)
{
   ASSERT(pADOConn != NULL);
   CString strSQL = _T("");
   strSQL.Format(_T("select %s from %s where %s='%s'"),
      DBMateriel_Key_cPic,
      DB_TABLE_MATERIEL_INFO,
      DBMateriel_Key_ID,
      strID);

   pADOConn->GetRecordSet(strSQL);
   while (!pADOConn->adoEOF())   
   {
      CDBImage oImage;
      pPic = oImage.NewImageFromDB(DBMateriel_Key_cPic,pADOConn->GetRecoPtr());
      return TRUE;

   }

   return FALSE;
}



BOOL CDBMaterielInfoData::InsertAllDBInfoByID( CADOConn *pADOConn )
{
	ASSERT(pADOConn != NULL);
	m_strID.Trim();
	ASSERT(!m_strID.IsEmpty());

	BOOL bRet = TRUE;

	CString strSQL = _T(""),strFormat = _T(""),strValue = _T("");
	strFormat.Format(_T("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s"),

      DBMateriel_Key_ID		      ,//1
      DBMateriel_Key_cName       ,//2
      DBMateriel_Key_cLevel1Type ,//3
      DBMateriel_Key_cLevel2Type ,//4
      DBMateriel_Key_cLevel3Type ,//5

      DBMateriel_Key_cLevel4Type ,//6
      DBMateriel_Key_cLevel5Type ,//7
      DBMateriel_Key_cUnit       ,//8
      DBMateriel_Key_cChengFen   ,//9
      DBMateriel_Key_cMemo       ,//10
      DBMateriel_Key_cPrice      ,//11
      DBMateriel_Key_cBrand      ,//12
      DBMateriel_Key_cSupplier    //13
		);
	//					1 ,2   ,3   ,4   ,5   ,6   ,7   ,8  ,9  ,10  ,11
	strValue.Format(_T("'%s','%s','%s','%s','%s','%s','%s','%s','%s','%s',%.2lf,'%s','%s'"),
		
      m_strID,			      //物料编号
      m_strName,		      //物料名称	
      m_strLevel1Type,	   //一级类别	
      m_strLevel2Type,	   //二级类别
      m_strLevel3Type,	   //三级类别

      m_strLevel4Type,	   //四级类别
      m_strLevel5Type,	   //五级类别
      m_strUnit,		      //物料单位	
      m_strChengfen,	      //物料材质
      m_strMemo,	         //物料说明	
      m_nPrice	,           //物料单价	
      m_strBrand,	         //物料品牌	
      m_strSupplier        //供应商
		
		);

	strSQL.Format(_T("insert into %s (%s) values(%s)"),
      DB_TABLE_MATERIEL_INFO,
      strFormat,
      strValue);

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

void CDBMaterielInfoData::Trim()
{
	m_strName.Trim();
	m_strLevel1Type.Trim();
   m_strLevel2Type.Trim();
   m_strLevel3Type.Trim();
   m_strLevel4Type.Trim();
   m_strLevel5Type.Trim();
	m_strUnit.Trim();
   m_strChengfen.Trim();
   m_strMemo.Trim();
   m_strBrand.Trim();
   m_strSupplier.Trim();
	
}

#if MATERIEL_IMAGE
void CDBMaterielInfoData::ClearColorImage()
{
	if (nullptr != m_pMaterielPic)
	{
		delete m_pMaterielPic;
		m_pMaterielPic = nullptr;
	}
}
#endif // YARN_IMAGE

CDBMaterielInfoList::CDBMaterielInfoList()
{

}
CDBMaterielInfoList::~CDBMaterielInfoList()
{

}

CDBMaterielInfoData*  CDBMaterielInfoList::GetItem(int nIndex)
{
	if (nIndex<0
      ||nIndex>=GetCount())
	{	
      return nullptr;
   }
	return (CDBMaterielInfoData*)GetAt(FindIndex(nIndex));
}

CDBMaterielInfoData* CDBMaterielInfoList::GetItemByMaterielId(CString strId)
{
   CDBMaterielInfoData * pItem = nullptr;
   strId.Trim();
   if (!strId.IsEmpty())
   {
      for(int i=0;i< GetCount();i++)
      {
         CDBMaterielInfoData * pObject = GetItem(i);
         if(strId==pObject->m_strID)
         {
            pItem = pObject;
            break;
         }
      }
   }

   return pItem;
}
//CDBYarnInfoList
void CDBMaterielInfoList::AddItem(CDBMaterielInfoData* pItem)
{
	CDBMaterielInfoData*pData=new CDBMaterielInfoData;
	pData->Copy(pItem);
	AddTail(pData);
}

void CDBMaterielInfoList::DeleteItem(int nIndex)
{
	if (nIndex<0||nIndex>GetCount())
	{
      return;
   }
	CDBMaterielInfoData *pObject=(CDBMaterielInfoData*)GetItem(nIndex);
	delete pObject;
	pObject=nullptr;
	RemoveAt(FindIndex(nIndex));
}

int CDBMaterielInfoList::GetIndexByMaterielId(CString strId)
{
	int nSel = -1;
	strId.Trim();
	if (!strId.IsEmpty())
	{
		for(int i=0;i< GetCount();i++)
		{
			CDBMaterielInfoData * pObject = GetItem(i);
			if(strId==pObject->m_strID)
			{
				nSel = i;
				break;
			}
		}
	}

	return nSel;
}

void CDBMaterielInfoList::SetAllItemDownPic(bool bDownPic)
{
   for(int i=0;i<GetCount();++i)
   {
      CDBMaterielInfoData * pObject = GetItem(i);
      pObject->m_bHaveDownPic = bDownPic;
   }
}

//设置下载图片标志 
void CDBMaterielInfoList::SetDownPicFlagById(CString strID,bool bDownPic)
{
   int nSel = -1;
   strID.Trim();
   if (!strID.IsEmpty())
   {
      for(int i=0;i< GetCount();++i)
      {
         CDBMaterielInfoData * pObject = GetItem(i);
         if(strID==pObject->m_strID)
         {
            pObject->m_bHaveDownPic = bDownPic;
            break;
         }
      }
   }
}

//设置图片数据 
void CDBMaterielInfoList::SetPicDataById(CString strID, Gdiplus::Image* pPic)
{
   int nSel = -1;
   strID.Trim();
   if (!pPic)
   {
      return;
   }

   if (!strID.IsEmpty())
   {
      for(int i=0;i< GetCount();++i)
      {
         CDBMaterielInfoData * pObject = GetItem(i);
         if(strID==pObject->m_strID)
         {
#if MATERIEL_IMAGE
            if (nullptr != pObject->m_pMaterielPic)
            {
               delete pObject->m_pMaterielPic;
               pObject->m_pMaterielPic = nullptr;
            }
            if (nullptr != pPic)
            {
               pObject->m_pMaterielPic = pPic->Clone();
            }
#endif
            break;
         }
      }
   }
}

void CDBMaterielInfoList::GetListFromDB(CADOConn *pADOConn,bool bNeedPic)
{
	ASSERT(pADOConn != NULL);
	
	Empty();
	CString strSQL = _T("");
   if (bNeedPic)
   {
      strSQL.Format(_T("select * from %s"),
         DB_TABLE_MATERIEL_INFO);
   }
   else
   {
      strSQL.Format(_T("select %s,%s,%s,%s,%s,\
         %s,%s,%s,%s,%s,\
         %s,%s,%s\
         from %s"),
         
         DBMateriel_Key_ID		      ,//1
         DBMateriel_Key_cName       ,//2
         DBMateriel_Key_cLevel1Type ,//3
         DBMateriel_Key_cLevel2Type ,//4
         DBMateriel_Key_cLevel3Type ,//5

         DBMateriel_Key_cLevel4Type ,//6
         DBMateriel_Key_cLevel5Type ,//7
         DBMateriel_Key_cUnit       ,//8
         DBMateriel_Key_cChengFen   ,//9
         DBMateriel_Key_cMemo       ,//10

         DBMateriel_Key_cPrice      ,//11
         DBMateriel_Key_cBrand      ,//12
         DBMateriel_Key_cSupplier   ,//13
         DB_TABLE_MATERIEL_INFO);
   }	
	pADOConn->GetRecordSet(strSQL);

	while (!pADOConn->adoEOF())
	{
		CDBMaterielInfoData oData;
		oData.GetAllDBInfo(pADOConn,bNeedPic);
		AddItem(&oData);
		pADOConn->MoveNext();
	}
}


CDBMaterielInfoList * CDBMaterielInfoList::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = shared_ptr<CDBMaterielInfoList>(new CDBMaterielInfoList);

	return sm_inst.get();
}


//获取五层级别分类的信息			by WangZY 2018/08/07
BOOL CDBMaterielInfoList::GetLevelTypeInfo(__in CADOConn *pADOConn, 
   __out CMateriel5LevelInfo &info)
{
   ASSERT(pADOConn != NULL);

   
   info.Clear();

   //一，二级类别处理		by WangZY 2018/08/07
   CString strSQL = _T("");
   strSQL.Format(_T("select %s,%s \
      from %s \
      group by %s,%s;"),
      DBMateriel_Key_cLevel1Type,
      DBMateriel_Key_cLevel2Type,

      DB_TABLE_MATERIEL_INFO,

      DBMateriel_Key_cLevel1Type,
      DBMateriel_Key_cLevel2Type);


   pADOConn->GetRecordSet(strSQL);
   while (!pADOConn->adoEOF())
   {
      CString strLevel1 = pADOConn->GetValueString(DBMateriel_Key_cLevel1Type);
      CString strLevel2 = pADOConn->GetValueString(DBMateriel_Key_cLevel2Type);
      info.m_infoLevel1_2.AddItem(strLevel1,&strLevel2);
     
      pADOConn->MoveNext();
   }


   //二、三级类别处理		by WangZY 2018/08/07
   strSQL.Format(_T("select %s,%s \
                    from %s \
                    group by %s,%s;"),
                    DBMateriel_Key_cLevel2Type,
                    DBMateriel_Key_cLevel3Type,

                    DB_TABLE_MATERIEL_INFO,

                    DBMateriel_Key_cLevel2Type,
                    DBMateriel_Key_cLevel3Type);


   pADOConn->GetRecordSet(strSQL);
   while (!pADOConn->adoEOF())
   {
      CString strLevel2 = pADOConn->GetValueString(DBMateriel_Key_cLevel2Type);
      CString strLevel3 = pADOConn->GetValueString(DBMateriel_Key_cLevel3Type);
      
      info.m_infoLevel2_3.AddItem(strLevel2,&strLevel3);

      pADOConn->MoveNext();
   }

   //三、四级类别处理		by WangZY 2018/08/07
   strSQL.Format(_T("select %s,%s \
                    from %s \
                    group by %s,%s;"),
                    DBMateriel_Key_cLevel3Type,
                    DBMateriel_Key_cLevel4Type,

                    DB_TABLE_MATERIEL_INFO,

                    DBMateriel_Key_cLevel3Type,
                    DBMateriel_Key_cLevel4Type);


   pADOConn->GetRecordSet(strSQL);
   while (!pADOConn->adoEOF())
   {
      CString strLevel3 = pADOConn->GetValueString(DBMateriel_Key_cLevel3Type);
      CString strLevel4 = pADOConn->GetValueString(DBMateriel_Key_cLevel4Type);

      info.m_infoLevel3_4.AddItem(strLevel3,&strLevel4);

      pADOConn->MoveNext();
   }

   //四、五级类别处理		by WangZY 2018/08/07
   strSQL.Format(_T("select %s,%s \
                    from %s \
                    group by %s,%s;"),
                    DBMateriel_Key_cLevel4Type,
                    DBMateriel_Key_cLevel5Type,

                    DB_TABLE_MATERIEL_INFO,

                    DBMateriel_Key_cLevel4Type,
                    DBMateriel_Key_cLevel5Type);


   pADOConn->GetRecordSet(strSQL);
   while (!pADOConn->adoEOF())
   {
      CString strLevel4 = pADOConn->GetValueString(DBMateriel_Key_cLevel4Type);
      CString strLevel5 = pADOConn->GetValueString(DBMateriel_Key_cLevel5Type);

      info.m_infoLevel4_5.AddItem(strLevel4,&strLevel5);

      pADOConn->MoveNext();
   }

   return TRUE;
}

//获取三层级别分类的信息		by WangZY 2018/08/07
BOOL CDBMaterielInfoList::Get3LevelTypeInfo(__in CADOConn *pADOConn, 
   __out CMateriel5LevelInfo &info)
{
   ASSERT(pADOConn != NULL);


   info.Clear();

   //一，二级类别处理		by WangZY 2018/08/07
   CString strSQL = _T("");
   strSQL.Format(_T("select %s,%s \
                    from %s \
                    group by %s,%s;"),
                    DBMateriel_Key_cLevel1Type,
                    DBMateriel_Key_cLevel2Type,

                    DB_TABLE_MATERIEL_INFO,

                    DBMateriel_Key_cLevel1Type,
                    DBMateriel_Key_cLevel2Type);


   pADOConn->GetRecordSet(strSQL);
   while (!pADOConn->adoEOF())
   {
      CString strLevel1 = pADOConn->GetValueString(DBMateriel_Key_cLevel1Type);
      CString strLevel2 = pADOConn->GetValueString(DBMateriel_Key_cLevel2Type);
      info.m_infoLevel1_2.AddItem(strLevel1,&strLevel2);

      pADOConn->MoveNext();
   }


   //二、三级类别处理		by WangZY 2018/08/07
   strSQL.Format(_T("select %s,%s \
                    from %s \
                    group by %s,%s;"),
                    DBMateriel_Key_cLevel2Type,
                    DBMateriel_Key_cLevel3Type,

                    DB_TABLE_MATERIEL_INFO,

                    DBMateriel_Key_cLevel2Type,
                    DBMateriel_Key_cLevel3Type);


   pADOConn->GetRecordSet(strSQL);
   while (!pADOConn->adoEOF())
   {
      CString strLevel2 = pADOConn->GetValueString(DBMateriel_Key_cLevel2Type);
      CString strLevel3 = pADOConn->GetValueString(DBMateriel_Key_cLevel3Type);

      info.m_infoLevel2_3.AddItem(strLevel2,&strLevel3);

      pADOConn->MoveNext();
   }

   return TRUE;
}


#ifdef USING_GRIDCTRL_MARK
MAP_GridCtrl_AllData CDBMaterielInfoList::CreatrGridData()
{
	MAP_GridCtrl_AllData  map_all_data;

	int nIndex = 0,nCount = GetCount();
	int nValidCount = 1;
	for (nIndex = 0;nIndex < nCount;nIndex++)
	{
		CDBMaterielInfoData * pData = GetItem(nIndex);
		if (nullptr != pData)
		{
			MAP_GridCtrl_RowData map_row_data;
            
         pData->InsertRowData(DBMateriel_Key_ID		      , map_row_data, pData->m_strID    		);   //物料编号
         pData->InsertRowData(DBMateriel_Key_cName       , map_row_data, pData->m_strName		   );   //物料名称
         pData->InsertRowData(DBMateriel_Key_cLevel1Type , map_row_data, pData->m_strLevel1Type  );   //一级类别
         pData->InsertRowData(DBMateriel_Key_cLevel2Type , map_row_data, pData->m_strLevel2Type  );   //二级类别
         pData->InsertRowData(DBMateriel_Key_cLevel3Type , map_row_data, pData->m_strLevel3Type  );   //三级类别
                                                                                      
         pData->InsertRowData(DBMateriel_Key_cLevel4Type , map_row_data, pData->m_strLevel4Type  );   //四级类别
         pData->InsertRowData(DBMateriel_Key_cLevel5Type , map_row_data, pData->m_strLevel5Type  );   //五级类别
         pData->InsertRowData(DBMateriel_Key_cUnit       , map_row_data, pData->m_strUnit        );   //物料单位
         pData->InsertRowData(DBMateriel_Key_cChengFen   , map_row_data, pData->m_strChengfen    );   //物料材质
         pData->InsertRowData(DBMateriel_Key_cMemo       , map_row_data, pData->m_strMemo);   //物料说明
         pData->InsertRowData(DBMateriel_Key_cPrice      , map_row_data, _T("%.2lf"), pData->m_nPrice);   //物料单价
         pData->InsertRowData(DBMateriel_Key_cBrand      , map_row_data, pData->m_strBrand);   //物料品牌
          pData->InsertRowData(DBMateriel_Key_cSupplier  , map_row_data, pData->m_strSupplier);   //供应商


			//写入行数据
			map_all_data.insert(make_pair(nValidCount,map_row_data));
			//行数据插入所有数据中

			nValidCount++;
		}
	}

	return map_all_data;
}

//生成一条空的行数据			by WangZY 2017/08/24
BOOL CDBMaterielInfoList::GetEmptyRowData(
   __out MAP_GridCtrl_RowData &mapEmptyRowData)
{
	mapEmptyRowData.clear();

   InsertRowData(DBMateriel_Key_ID		       ,_T(""), mapEmptyRowData);
   InsertRowData(DBMateriel_Key_cName         ,_T(""), mapEmptyRowData);
   InsertRowData(DBMateriel_Key_cLevel1Type   ,_T(""), mapEmptyRowData);
   InsertRowData(DBMateriel_Key_cLevel2Type   ,_T(""), mapEmptyRowData);
   InsertRowData(DBMateriel_Key_cLevel3Type   ,_T(""), mapEmptyRowData);
   
   InsertRowData(DBMateriel_Key_cLevel4Type   ,_T(""), mapEmptyRowData);
   InsertRowData(DBMateriel_Key_cLevel5Type   ,_T(""), mapEmptyRowData);
   InsertRowData(DBMateriel_Key_cUnit         ,_T(""), mapEmptyRowData);
   InsertRowData(DBMateriel_Key_cChengFen     ,_T(""), mapEmptyRowData);
   InsertRowData(DBMateriel_Key_cMemo         ,_T(""), mapEmptyRowData);
   InsertRowData(DBMateriel_Key_cPrice        ,_T(""), mapEmptyRowData);
   InsertRowData(DBMateriel_Key_cBrand        ,_T(""), mapEmptyRowData);
   InsertRowData(DBMateriel_Key_cSupplier     ,_T(""), mapEmptyRowData);
   
	return TRUE;

}


BOOL CDBMaterielInfoList::GetInfoByMaterielId(__in CADOConn *pADOConn,
   __in CString strId,__out CDBMaterielInfoData* pObj)
{
   if (pObj == nullptr)
   {
      ASSERT(pObj != nullptr);
      return FALSE;
   }
   ASSERT(pADOConn != NULL);
   CString strSQL = _T("");

   strSQL.Format(_T("select * from %s where %s = '%s'"),
      DB_TABLE_MATERIEL_INFO,
      DBMateriel_Key_ID,
      strId);

   pADOConn->GetRecordSet(strSQL);
   if (!pADOConn->adoEOF())
   {
      pObj->GetAllDBInfo(pADOConn,true);
      
      return TRUE;
   }

   return FALSE;
}
CString CDBMaterielInfoData::SetDBEquals_Log(CDBMaterielInfoData &pOldData)
{
   CString strActLog = _T("");
   if (m_strID != pOldData.m_strID)//物料编号
   {
      CString strID = m_strID;
      if (strID.IsEmpty())
      {
         strID = _T("空值");
      }
      strActLog += _T("物料编号:") + strID + _T(",");
   }
   if (m_strName != pOldData.m_strName)//物料名称
   {
      CString strName = m_strName;
      if (strName.IsEmpty())
      {
         strName = _T("空值");
      }
      strActLog += _T("物料名称:") + strName + _T(",");
   }
   if (m_strLevel1Type != pOldData.m_strLevel1Type)//一级类别
   {
      CString strLevel1Type = m_strLevel1Type;
      if (m_strLevel1Type.IsEmpty())
      {
         strLevel1Type = _T("空值");
      }
      strActLog += _T("一级类别:") + strLevel1Type + _T(",");
   }
   if (m_strLevel2Type != pOldData.m_strLevel2Type)//二级类别
   {
      CString strLevel2Type = m_strLevel2Type;
      if (strLevel2Type.IsEmpty())
      {
         strLevel2Type = _T("空值");
      }
      strActLog += _T("二级类别:") + strLevel2Type + _T(",");
   }
   if (m_strLevel3Type != pOldData.m_strLevel3Type)//三级类别
   {
      CString strLevel3Type = m_strLevel3Type;
      if (strLevel3Type.IsEmpty())
      {
         strLevel3Type = _T("空值");
      }
      strActLog += _T("三级类别:") + strLevel3Type + _T(",");
   }
   if (m_strLevel4Type != pOldData.m_strLevel4Type)//四级类别
   {
      CString strLevel4Type = m_strLevel4Type;

      if (strLevel4Type.IsEmpty())
      {
         strLevel4Type = _T("空值");
      }
      strActLog += _T("四级类别:") + strLevel4Type + _T(",");
   }
   if (m_strLevel5Type != pOldData.m_strLevel5Type)//五级类别
   {
      CString strLevel5Type = m_strLevel5Type;
      if (strLevel5Type.IsEmpty())
      {
         strLevel5Type = _T("空值");
      }
      strActLog += _T("五级类别:") + strLevel5Type + _T(",");
   }
   if (m_strUnit != pOldData.m_strUnit)//物料单位
   {
      CString strUnit = m_strUnit;

      if (strUnit.IsEmpty())
      {
         strUnit = _T("空值");
      }
      strActLog += _T("物料单位:") + strUnit + _T(",");
   }
   if (m_strChengfen != pOldData.m_strChengfen)//物料材质(成份)
   {
      CString strChengfen = m_strChengfen;

      if (strChengfen.IsEmpty())
      {
         strChengfen = _T("空值");
      }
      strActLog += _T("物料材质:") + strChengfen + _T(",");
   }
   if (m_strMemo != pOldData.m_strMemo)//物料说明
   {
      CString strMemo = m_strMemo;

      if (strMemo.IsEmpty())
      {
         strMemo = _T("空值");
      }
      strActLog += _T("物料说明:") + strMemo + _T(",");
   }
   if (m_nPrice != pOldData.m_nPrice)//物料单价
   {
      CString strPrice = _T("");
      strPrice.Format(_T("%.2lf"),m_nPrice);

      strActLog += _T("物料单价:") + strPrice + _T(",");
   }
   if (m_strBrand != pOldData.m_strBrand)//物料品牌
   {
      CString strBrand = m_strBrand;

      if (strBrand.IsEmpty())
      {
         strBrand = _T("空值");
      }
      strActLog += _T("物料品牌:") + strBrand + _T(",");
   }
   return strActLog;
}

BOOL CDBMaterielInfoData::GetAllDBInfoByID( CADOConn *pADOConn,bool bNeedColorCard/*=false*/ )
{
   ASSERT(pADOConn != NULL);

   BOOL bRet = TRUE;

   CString strSQL = _T("");
   strSQL.Format(_T("select * from %s where %s = '%s'"),DB_TABLE_MATERIEL_INFO,DBMateriel_Key_ID,m_strID);
   if (NULL == pADOConn)
   {
      bRet = FALSE;
   }
   else
   {
      pADOConn->GetRecordSet(strSQL);
      if (!pADOConn->adoEOF())
      {
         m_strID  		 = pADOConn->GetValueString(DBMateriel_Key_ID         );
         m_strName		 = pADOConn->GetValueString(DBMateriel_Key_cName      );
         m_strLevel1Type = pADOConn->GetValueString(DBMateriel_Key_cLevel1Type);
         m_strLevel2Type = pADOConn->GetValueString(DBMateriel_Key_cLevel2Type);
         m_strLevel3Type = pADOConn->GetValueString(DBMateriel_Key_cLevel3Type);
         m_strLevel4Type = pADOConn->GetValueString(DBMateriel_Key_cLevel4Type);
         m_strLevel5Type = pADOConn->GetValueString(DBMateriel_Key_cLevel5Type);
         m_strUnit		 = pADOConn->GetValueString(DBMateriel_Key_cUnit      );
         m_strChengfen	 = pADOConn->GetValueString(DBMateriel_Key_cChengFen  );
         m_strMemo       = pADOConn->GetValueString(DBMateriel_Key_cMemo);
         m_nPrice        = pADOConn->GetValueDouble(DBMateriel_Key_cPrice);
         m_strBrand      = pADOConn->GetValueString(DBMateriel_Key_cBrand);
         m_strSupplier   = pADOConn->GetValueString(DBMateriel_Key_cSupplier);

         if (bNeedColorCard)
         {
#if MATERIEL_IMAGE
            ClearColorImage();
            CDBImage oImage;
            m_pMaterielPic = oImage.NewImageFromDB(DBMateriel_Key_cPic,
               pADOConn->GetRecoPtr());

#endif // YARN_IMAGE

            m_bHaveDownPic = true;
         }else
         {
            m_bHaveDownPic = false;
         }
         bRet = TRUE;
      }
      }
   return bRet;
}
BOOL CDBMaterielInfoList::operator= (CDBMaterielInfoList &pData)
{
   for (int i = 0;i<pData.GetCount();i++)
   {
      CDBMaterielInfoData *pMate = (CDBMaterielInfoData *) pData.GetAt(pData.FindIndex(i));
      if (NULL != pMate)
      {
         if(GetIndexByMaterielId(pMate->m_strID) == -1)
         {
            AddItem(pMate);
         }
      }
   }

   return TRUE;
}
#endif // USING_GRIDCTRL_MARK
