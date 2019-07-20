#include "StdAfx.h"
#include "DBDesignDataLib.h"
#include "DBKeyDef.h"
#include <afx.h>


/////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CDBDesignDataLib, CDataMid, 1)
std::shared_ptr<CDBDesignDataLib> CDBDesignDataLib::sm_inst;
CDBDesignDataLib::CDBDesignDataLib()
{
   ResetData();
}


CDBDesignDataLib::~CDBDesignDataLib()
{
}

void CDBDesignDataLib::ResetData()
{
   m_nID               = -1;
   m_strName           = _T("");
   m_strSavedUserID    = _T("");
   m_strSaveTime       = _T("");
   m_strData           = _T("");
   m_strLibType        = _T("");
   m_strPosition       = _T("");
   m_bSymmetricByHor   = false;
   m_bSymmetricByPer   = false;
   m_bUseExpre         = false;
   m_bUseLine          = false;
   m_bMark             = false;
   m_bMatchPiece       = false;
   m_nLength           = 0;
   m_nBust             = 0;
   m_nShoulderWidth    = 0;
   m_nCollarWidth      = 0;
   m_nCollarHeight     = 0;
   m_nFront            = 0;
   m_nBehind           = 0;
   m_nMidWidth         = 0;
   m_nMidHeight        = 0;
   m_nBellowWidth      = 0;
   m_nBellowHeight     = 0;
   m_nShoulderSlanting = 0;
   m_nShoulder         = 0;
   m_nShoulderHeight   = 0;
   m_nShoudlerHor      = 0;
   m_nFrontDeep        = 0;
   m_nBehindDeep       = 0;
   m_nSleeveLength     = 0;
   m_nSleeveWidth      = 0;
   m_strTomid          =  _T("");
   m_strToTop          =  _T("");
   m_strWidth1         =  _T("");
   m_strWidth2         =  _T("");
   m_strHeight1        =  _T("");
   m_strHeight2        =  _T("");
   m_strTotalHeight    =  _T("");
   m_strTotalWidth     =  _T("");
}

BOOL CDBDesignDataLib::UpdateDBInfo(CADOConn *pADOConn)
{
   pADOConn->GetValueString(DBDesignDataLib_key_Name) = m_strName;			//名称
   return TRUE;
}

BOOL CDBDesignDataLib::GetAllDBInfo(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);

   BOOL bRet = TRUE;
   if (NULL == pADOConn)
   {
      bRet = FALSE;
   }
   else
   {
      m_nID               = pADOConn->GetValueInt   (DBDesignDataLib_key_ID               );
      m_strName           = pADOConn->GetValueString(DBDesignDataLib_key_Name             );
      m_strSavedUserID    = pADOConn->GetValueString(DBDesignDataLib_key_cSavedUserID     );
      m_strSaveTime       = pADOConn->GetValueString(DBDesignDataLib_key_cSaveTime);
      m_strData           = pADOConn->GetValueString(DBDesignDataLib_key_cData);
      m_strLibType        = pADOConn->GetValueString(DBDesignDataLib_key_cLibType         );
      m_strPosition       = pADOConn->GetValueString(DBDesignDataLib_key_cPosition        );
      m_bSymmetricByHor   = pADOConn->GetValueInt   (DBDesignDataLib_key_bSymmetricByHor  )==0?false:true;
      m_bSymmetricByPer   = pADOConn->GetValueInt   (DBDesignDataLib_key_bSymmetricByPer  )==0?false:true;
      m_bUseExpre         = pADOConn->GetValueInt   (DBDesignDataLib_key_bUseExpre        )==0?false:true;
      m_bUseLine          = pADOConn->GetValueInt   (DBDesignDataLib_key_bUseLine         )==0?false:true;
      m_bMark             = pADOConn->GetValueInt   (DBDesignDataLib_key_bMark            )==0?false:true;
      m_bMatchPiece       = pADOConn->GetValueInt   (DBDesignDataLib_key_bMatchPiece      )==0?false:true;
      m_nLength           = pADOConn->GetValueInt   (DBDesignDataLib_key_nLength          );
      m_nBust             = pADOConn->GetValueInt   (DBDesignDataLib_key_nBust            );
      m_nShoulderWidth    = pADOConn->GetValueInt   (DBDesignDataLib_key_nShoulderWidth   );
      m_nCollarWidth      = pADOConn->GetValueInt   (DBDesignDataLib_key_nCollarWidth     );
      m_nCollarHeight     = pADOConn->GetValueInt   (DBDesignDataLib_key_nCollarHeight    );
      m_nFront            = pADOConn->GetValueInt   (DBDesignDataLib_key_nFront           );
      m_nBehind           = pADOConn->GetValueInt   (DBDesignDataLib_key_nBehind          );
      m_nMidWidth         = pADOConn->GetValueInt   (DBDesignDataLib_key_nMidWidth        );
      m_nMidHeight        = pADOConn->GetValueInt   (DBDesignDataLib_key_nMidHeight       );
      m_nBellowWidth      = pADOConn->GetValueInt   (DBDesignDataLib_key_nBellowWidth     );
      m_nBellowHeight     = pADOConn->GetValueInt   (DBDesignDataLib_key_nBellowHeight    );
      m_nShoulderSlanting = pADOConn->GetValueInt   (DBDesignDataLib_key_nShoulderSlanting);
      m_nShoulder         = pADOConn->GetValueInt   (DBDesignDataLib_key_nShoulder        );
      m_nShoulderHeight   = pADOConn->GetValueInt   (DBDesignDataLib_key_nShoulderHeight  );
      m_nShoudlerHor      = pADOConn->GetValueInt   (DBDesignDataLib_key_nShoudlerHor     );
      m_nFrontDeep        = pADOConn->GetValueInt   (DBDesignDataLib_key_nFrontDeep       );
      m_nBehindDeep       = pADOConn->GetValueInt   (DBDesignDataLib_key_nBehindDeep      );
      m_nSleeveLength     = pADOConn->GetValueInt   (DBDesignDataLib_key_nSleeveLength    );
      m_nSleeveWidth      = pADOConn->GetValueInt   (DBDesignDataLib_key_nSleeveWidth     );
      m_strTomid          = pADOConn->GetValueString(DBDesignDataLib_key_cTomid           );
      m_strToTop          = pADOConn->GetValueString(DBDesignDataLib_key_cToTop           );
      m_strWidth1         = pADOConn->GetValueString(DBDesignDataLib_key_cWidth1          );
      m_strWidth2         = pADOConn->GetValueString(DBDesignDataLib_key_cWidth2          );
      m_strHeight1        = pADOConn->GetValueString(DBDesignDataLib_key_cHeight1         );
      m_strHeight2        = pADOConn->GetValueString(DBDesignDataLib_key_cHeight2         );
      m_strTotalHeight    = pADOConn->GetValueString(DBDesignDataLib_key_cTotalHeight     );
      m_strTotalWidth     = pADOConn->GetValueString(DBDesignDataLib_key_cTotalWidth      );
   }                                                                     
   return bRet;
}

void CDBDesignDataLib::Copy(CDBDesignDataLib *pData)
{
   m_nID               = pData->m_nID;
   m_strName           = pData->m_strName;
   m_strSavedUserID    = pData->m_strSavedUserID;
   m_strSaveTime       = pData->m_strSaveTime;
   m_strData           = pData->m_strData;

   m_strLibType        = pData->m_strLibType;
   m_strPosition       = pData->m_strPosition;
   m_bSymmetricByHor   = pData->m_bSymmetricByHor;
   m_bSymmetricByPer   = pData->m_bSymmetricByPer;
   m_bUseExpre         = pData->m_bUseExpre;
   m_bUseLine          = pData->m_bUseLine;
   m_bMark             = pData->m_bMark;
   m_bMatchPiece       = pData->m_bMatchPiece;
   m_nLength           = pData->m_nLength;
   m_nBust             = pData->m_nBust;
   m_nShoulderWidth    = pData->m_nShoulderWidth;
   m_nCollarWidth      = pData->m_nCollarWidth;
   m_nCollarHeight     = pData->m_nCollarHeight;
   m_nFront            = pData->m_nFront;
   m_nBehind           = pData->m_nBehind;
   m_nMidWidth         = pData->m_nMidWidth;
   m_nMidHeight        = pData->m_nMidHeight;
   m_nBellowWidth      = pData->m_nBellowWidth;
   m_nBellowHeight     = pData->m_nBellowHeight;
   m_nShoulderSlanting = pData->m_nShoulderSlanting;
   m_nShoulder         = pData->m_nShoulder;
   m_nShoulderHeight   = pData->m_nShoulderHeight;
   m_nShoudlerHor      = pData->m_nShoudlerHor;
   m_nFrontDeep        = pData->m_nFrontDeep;
   m_nBehindDeep       = pData->m_nBehindDeep;
   m_nSleeveLength     = pData->m_nSleeveLength;
   m_nSleeveWidth      = pData->m_nSleeveWidth;
   m_strTomid          = pData->m_strTomid;
   m_strToTop          = pData->m_strToTop;
   m_strWidth1         = pData->m_strWidth1;
   m_strWidth2         = pData->m_strWidth2;
   m_strHeight1        = pData->m_strHeight1;
   m_strHeight2        = pData->m_strHeight2;
   m_strTotalHeight    = pData->m_strTotalHeight;
   m_strTotalWidth     = pData->m_strTotalWidth;
}

CString CDBDesignDataLib::GetInsertSQL()
{
   CString strRet = _T("");
   return strRet;
};

CDBDesignDataLib * CDBDesignDataLib::Instance()
{
   if (sm_inst.get() == 0)
      sm_inst = shared_ptr<CDBDesignDataLib>(new CDBDesignDataLib);

   return sm_inst.get();
}

BOOL CDBDesignDataLib::UpdateAllDBInfoByID(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);
   BOOL bRet = TRUE;
   return bRet;
}

BOOL CDBDesignDataLib::InsertAllDBInfoByID(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);

   BOOL bRet = TRUE;

   return TRUE;
}

IMPLEMENT_SERIAL(CDBDesignDataLibList, CDataListMid, 1)
std::shared_ptr<CDBDesignDataLibList> CDBDesignDataLibList::sm_inst;

CDBDesignDataLibList::CDBDesignDataLibList()
{

}

CDBDesignDataLibList::~CDBDesignDataLibList()
{

}

CDBDesignDataLib*  CDBDesignDataLibList::GetItem(int nIndex)
{
   if (nIndex < 0 || nIndex >= GetCount())
      return NULL;

   return (CDBDesignDataLib*)GetAt(FindIndex(nIndex));
}

void CDBDesignDataLibList::AddItem(CDBDesignDataLib* pItem)
{
   CDBDesignDataLib*pData = new CDBDesignDataLib;
   pData->Copy(pItem);
   AddTail(pData);
}

void CDBDesignDataLibList::DeleteItem(int nIndex)
{
   if (nIndex<0 || nIndex>GetCount())
      return;

   CDBDesignDataLib *pObject = (CDBDesignDataLib*)GetItem(nIndex);
   delete pObject;
   pObject = NULL;

   RemoveAt(FindIndex(nIndex));
}

BOOL CDBDesignDataLibList::DeleteUserByUserID(CADOConn* pADOConn, vector<CString>vecUserID)
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
   strSql.Format(_T("delete from %s where %s in (%s)"), _T("DesignData_Lib"), DBDesignDataLib_key_ID, strUserID);
   return pADOConn->ExecuteSQL(strSql);
}

CDBDesignDataLibList* CDBDesignDataLibList::Instance()		//获取（指针）实例
{
   if (sm_inst.get() == 0)
      sm_inst = shared_ptr<CDBDesignDataLibList>(new CDBDesignDataLibList);

   return sm_inst.get();
}

#ifdef USING_GRIDCTRL_MARK
MAP_GridCtrl_AllData CDBDesignDataLibList::CreateGridData(const CString & strUserDuty/*=_T("")*/)
{
   MAP_GridCtrl_AllData map_all_data;

   int nIndex = 0, nCount = GetCount();
   int nValidCount = 1;
   for (nIndex = 0; nIndex < nCount; nIndex++)
   {
      CDBDesignDataLib * pData = GetItem(nIndex);
      if (NULL != pData)
      {
         MAP_GridCtrl_RowData                                   map_row_data;
         pData->InsertRowData(DBDesignDataLib_key_ID,           map_row_data, CB_enum_FieldData_Int, CB_enum_FieldCtrl_Text, _T("%lld"), pData->m_nID);           //ID
         pData->InsertRowData(DBDesignDataLib_key_Name,         map_row_data, FORMAT_STRING, pData->m_strName);         //名称
         pData->InsertRowData(DBDesignDataLib_key_cData,        map_row_data, FORMAT_STRING, pData->m_strData);     //数据  
         pData->InsertRowData(DBDesignDataLib_key_cSavedUserID, map_row_data, FORMAT_STRING, pData->m_strSavedUserID);  //用户ID
         pData->InsertRowData(DBDesignDataLib_key_cSaveTime,    map_row_data, FORMAT_STRING, CB_enum_FieldData_Time, CB_enum_FieldCtrl_DateTime, pData->m_strSaveTime);     //保存时间
         map_all_data.insert(make_pair(nValidCount, map_row_data));
         //行数据插入所有数据中

         nValidCount++;
      }
   }

   return map_all_data;
}
#endif

