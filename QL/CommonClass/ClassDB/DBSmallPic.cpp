#include "StdAfx.h"
#include "DBSmallPic.h"
#include "DBKeyDef.h"
#include "ADOConn/DBImage.h"
#include <afx.h>


/////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CDBSmallPic, CDataMid, 1)
std::shared_ptr<CDBSmallPic> CDBSmallPic::sm_inst;
CDBSmallPic::CDBSmallPic()
{
#if Des_IMAGE
   m_pSmallDetailPic = NULL;
#endif // Des_IMAGE
   ResetData();
}


CDBSmallPic::~CDBSmallPic()
{
#if Des_IMAGE
   ClearColorImage();
#endif // Des_IMAGE
}

void CDBSmallPic::ResetData()
{
   m_nID            = -1;
   m_strName        = _T("");
   m_nWidth         = 0;
   m_nHeight        = 0;
   m_bLoop          = false;
   m_bKeepLine      = false;
   m_strContact     = _T("");
   m_strType        = _T("");
   m_strSavedUserID = _T("");
   m_strSaveTime    = _T("");
   m_strRemark      = _T("");
#if Des_IMAGE
   ClearColorImage();
#endif // Des_IMAGE
}

BOOL CDBSmallPic::UpdateDBInfo(CADOConn *pADOConn)
{
   pADOConn->GetValueString(DBSmallPic_key_Name) = m_strName;			//名称
   return TRUE;
}

BOOL CDBSmallPic::GetAllDBInfo(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);

   BOOL bRet = TRUE;
   if (NULL == pADOConn)
   {
      bRet = FALSE;
   }
   else
   {
      m_nID            = pADOConn->GetValueInt    (DBSmallPic_key_ID);
      m_nWidth         = pADOConn->GetValueInt    (DBSmallPic_key_iWidth);
      m_nHeight        = pADOConn->GetValueInt    (DBSmallPic_key_iHeight);
      m_strName        = pADOConn->GetValueString (DBSmallPic_key_Name);
      m_strType        = pADOConn->GetValueString (DBSmallPic_key_Type);
      m_strSavedUserID = pADOConn->GetValueString (DBSmallPic_key_cSavedUserID);
      m_strSaveTime    = pADOConn->GetValueString (DBSmallPic_key_cSaveTime);
      m_strRemark      = pADOConn->GetValueString (DBSmallPic_key_cRemark);
      m_bLoop          = (pADOConn->GetValueInt   (DBSmallPic_key_bLoop) == 1) ? true : false;
      m_bKeepLine      = (pADOConn->GetValueInt   (DBSmallPic_key_bKeepLine) == 1) ? true : false;
      m_strContact     = pADOConn->GetValueString (DBSmallPic_key_cContact);

#if Des_IMAGE
      ClearColorImage();
      CDBImage oImage;
      m_pSmallDetailPic = oImage.NewImageFromDB(DBSmallPic_key_cSmallDetailPic, pADOConn->GetRecoPtr());
#endif 
   }
   return bRet;
}

void CDBSmallPic::Copy(CDBSmallPic *pData)
{
   m_nID               = pData->m_nID;
   m_strName           = pData->m_strName;
   m_nWidth            = pData->m_nWidth;
   m_nHeight           = pData->m_nHeight;
   m_strType           = pData->m_strType;
   m_strSavedUserID    = pData->m_strSavedUserID;
   m_strSaveTime       = pData->m_strSaveTime;
   m_strRemark         = pData->m_strRemark;
   m_bLoop             = pData->m_bLoop;
   m_bKeepLine         = pData->m_bKeepLine;
   m_strContact        = pData->m_strContact;
#if Des_IMAGE
      ClearColorImage();
   if (pData->m_pSmallDetailPic)
   {
      m_pSmallDetailPic = pData->m_pSmallDetailPic->Clone();
   }
#endif
}

CString CDBSmallPic::GetInsertSQL()
{
   CString strRet = _T(""), strFormat = _T(""), strValue = _T("");
   strFormat.Format(_T("%s,%d,%d,%s,%s,%s,%s,%d,%d,%s"),
      DBSmallPic_key_Name,
      DBSmallPic_key_iWidth,
      DBSmallPic_key_iHeight,
      DBSmallPic_key_Type,
      DBSmallPic_key_cSavedUserID,
      DBSmallPic_key_cSaveTime,
      DBSmallPic_key_cRemark,
      DBSmallPic_key_bLoop,
      DBSmallPic_key_bKeepLine,
      DBSmallPic_key_cContact
   );
   CString strSaveTime = _T("");
   if (m_strSaveTime.IsEmpty())
   {
      strSaveTime = DBS_GETDATESTR;
   }
   else
   {
      strSaveTime.Format(_T("'%s'"), m_strSaveTime);
   }
   strValue.Format(_T("'%s','%d','%d','%s','%s',%s,'%s','%d','%d','%s'"),
      m_strName,
      m_nWidth,
      m_nHeight,
      m_strType,
      m_strSavedUserID,
      strSaveTime,
      m_strRemark,
      m_bLoop,
      m_bKeepLine,
      m_strContact);
   strRet.Format(_T("insert into %s(%s) values(%s)"), DB_TABLE_SMALLPIC, strFormat, strValue);

   return strRet;
};

CDBSmallPic * CDBSmallPic::Instance()
{
   if (sm_inst.get() == 0)
      sm_inst = shared_ptr<CDBSmallPic>(new CDBSmallPic);

   return sm_inst.get();
}

BOOL CDBSmallPic::UpdateAllDBInfoByID(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);
   BOOL bRet = TRUE;
   CString strSQL = _T("");
   pADOConn->BeginTrans(); 
   strSQL.Format(_T("update %s set \
      %s='%s',%s='%d',%s='%d',%s='%s',%s='%s',%s=%s,%s='%s',\
      %s='%d',%s='%d',%s='%s'\
      where %s='%lld'"), DB_TABLE_SMALLPIC,
      DBSmallPic_key_Name,         m_strName,
      DBSmallPic_key_iWidth,       m_nWidth,
      DBSmallPic_key_iHeight,      m_nHeight,
      DBSmallPic_key_Type,         m_strType,
      DBSmallPic_key_cSavedUserID, m_strSavedUserID,
      DBSmallPic_key_cSaveTime, DBS_GETDATESTR,
      DBSmallPic_key_cRemark,      m_strRemark,
      DBSmallPic_key_bLoop,        m_bLoop,
      DBSmallPic_key_bKeepLine,    m_bKeepLine,
      DBSmallPic_key_cContact,     m_strContact,
      DBSmallPic_key_ID,           m_nID);


   if (!pADOConn->ExecuteSQL(strSQL))
   {
      pADOConn->RollbackTrans();
      return FALSE;
   }

   if (pADOConn->CommitTrans())
   {
      bRet = TRUE;
   }
   else
   {
      bRet = FALSE;
   }

   return bRet;
}

BOOL CDBSmallPic::InsertAllDBInfoByID(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);

   BOOL bRet = TRUE;

   CString strSQL = _T("");
   CString strLabel = _T("");
   CString strSaveTime = _T("");
   if (m_strSaveTime.IsEmpty())
   {
      strSaveTime = DBS_GETDATESTR;
   }
   else
   {
      strSaveTime.Format(_T("'%s'"), m_strSaveTime);
   }
                                //0   1   2   3  4  5  6  7 8 9  10 
   strSQL.Format(_T("insert into %s (%s, %s,%s,%s,%s,%s,%s,%s,%s,%s)\
					 values('%s','%d','%d','%s','%s',%s,'%s','%d','%d','%s')"), DB_TABLE_SMALLPIC, \
      DBSmallPic_key_Name,                  //1
      DBSmallPic_key_iWidth,                //2
      DBSmallPic_key_iHeight,               //3
      DBSmallPic_key_Type,                  //4
      DBSmallPic_key_cSavedUserID,          //5
      DBSmallPic_key_cSaveTime,             //6
      DBSmallPic_key_cRemark,               //7
      DBSmallPic_key_bLoop,                 //8
      DBSmallPic_key_bKeepLine,             //9
      DBSmallPic_key_cContact,              //10
      m_strName,                            //1
      m_nWidth,                             //2
      m_nHeight,                            //3
      m_strType,                            //4
      m_strSavedUserID,                     //5
      strSaveTime,                          //6
      m_strRemark,                          //7
      m_bLoop,                              //8
      m_bKeepLine,                          //9
      m_strContact                          //10
   );

   if (!pADOConn->ExecuteSQL(strSQL))
   {
      return FALSE;
   }
   return TRUE;
}

#if Des_IMAGE
void CDBSmallPic::ClearColorImage()
{
   if (NULL != m_pSmallDetailPic)
   {
      delete m_pSmallDetailPic;
      m_pSmallDetailPic = NULL;
   }
}
#endif


IMPLEMENT_SERIAL(CDBSmallPicList, CDataListMid, 1)
std::shared_ptr<CDBSmallPicList> CDBSmallPicList::sm_inst;

CDBSmallPicList::CDBSmallPicList()
{

}

CDBSmallPicList::~CDBSmallPicList()
{

}

CDBSmallPic*  CDBSmallPicList::GetItem(int nIndex)
{
   if (nIndex < 0 || nIndex >= GetCount())
      return NULL;

   return (CDBSmallPic*)GetAt(FindIndex(nIndex));
}

void CDBSmallPicList::AddItem(CDBSmallPic* pItem)
{
   CDBSmallPic*pData = new CDBSmallPic;
   pData->Copy(pItem);
   AddTail(pData);
}

void CDBSmallPicList::DeleteItem(int nIndex)
{
   if (nIndex<0 || nIndex>GetCount())
      return;

   CDBSmallPic *pObject = (CDBSmallPic*)GetItem(nIndex);
   delete pObject;
   pObject = NULL;

   RemoveAt(FindIndex(nIndex));
}

BOOL CDBSmallPicList::DeleteUserByUserID(CADOConn* pADOConn, vector<CString>vecUserID)
{
   ASSERT(pADOConn != NULL);
   if (vecUserID.size() <= 0)
      return FALSE;

   CString strUserID;
   for (int i = 0; i < (int)vecUserID.size(); ++i)
   {
      strUserID += _T("'") + vecUserID[i] + _T("',");
   }
   strUserID.TrimRight(_T(","));
   CString strSql;
   strSql.Format(_T("delete from %s where %s in (%s)"), _T("SmallPic"), DBSmallPic_key_ID, strUserID);
   return pADOConn->ExecuteSQL(strSql);
}

CDBSmallPicList* CDBSmallPicList::Instance()		//获取（指针）实例
{
   if (sm_inst.get() == 0)
      sm_inst = shared_ptr<CDBSmallPicList>(new CDBSmallPicList);

   return sm_inst.get();
}

#ifdef USING_GRIDCTRL_MARK
MAP_GridCtrl_AllData CDBSmallPicList::CreateGridData(const CString & strUserDuty/*=_T("")*/)
{
   MAP_GridCtrl_AllData map_all_data;

   int nIndex = 0, nCount = GetCount();
   int nValidCount = 1;
   for (nIndex = 0; nIndex < nCount; nIndex++)
   {
      CDBSmallPic * pData = GetItem(nIndex);
      if (NULL != pData)
      {
         MAP_GridCtrl_RowData map_row_data;
         pData->InsertRowData(DBSmallPic_key_ID,           map_row_data, CB_enum_FieldData_Int, CB_enum_FieldCtrl_Text,FORMAT_INT64, pData->m_nID);             //ID
         pData->InsertRowData(DBSmallPic_key_Name,         map_row_data, FORMAT_STRING,   pData->m_strName);         //名称
         pData->InsertRowData(DBSmallPic_key_Type,         map_row_data, FORMAT_STRING,   pData->m_strType);         //种类
         pData->InsertRowData(DBSmallPic_key_cSavedUserID, map_row_data, FORMAT_STRING,   pData->m_strSavedUserID);  //用户ID
         pData->InsertRowData(DBSmallPic_key_cSaveTime,    map_row_data, CB_enum_FieldData_Time, CB_enum_FieldCtrl_DateTime,FORMAT_STRING,   pData->m_strSaveTime);     //保存时间
         pData->InsertRowData(DBSmallPic_key_cRemark,      map_row_data, FORMAT_STRING,   pData->m_strRemark);       //说明
         map_all_data.insert(make_pair(nValidCount, map_row_data));
         //行数据插入所有数据中

         nValidCount++;
      }
   }

   return map_all_data;
}
#endif

