#include "StdAfx.h"
#include "DBStyle_DesFaceCode.h"
#include "DBKeyDef.h"

IMPLEMENT_SERIAL(CDBStyle_DesFaceCodeData,CDataMid,1)

CDBStyle_DesFaceCodeData::CDBStyle_DesFaceCodeData()
{
   ResetData();
}

CDBStyle_DesFaceCodeData::~CDBStyle_DesFaceCodeData()
{
}

void CDBStyle_DesFaceCodeData::ResetData()   
{
   m_nID          = -1     ;//自增ID
   m_strName      = _T("") ;//名称 eg:面字码
   m_sOldLen      = _T("") ;//
   m_strType      = _T("") ;//类型 eg:支拉
   m_sLen         = _T("") ;//长度
   m_strUnit      = _T("") ;//单位 eg:里面
   m_nIDDensity   = -1     ;//密度关联字段自增ID

   SetDataType(DAT_STYLE_DESFACECODE);
}

void CDBStyle_DesFaceCodeData::Copy( CDBStyle_DesFaceCodeData *pData )
{
   ASSERT(pData!=NULL);
   CDataMid::Copy(pData);
   m_nID        = pData->m_nID        ;
   m_strName    = pData->m_strName    ;
   m_sOldLen    = pData->m_sOldLen    ;
   m_strType    = pData->m_strType    ;
   m_sLen       = pData->m_sLen       ;
   m_strUnit    = pData->m_strUnit    ;
   m_nIDDensity = pData->m_nIDDensity ;
}

BOOL CDBStyle_DesFaceCodeData::GetAllDBInfo( CADOConn *pADOConn )
{
   ASSERT(pADOConn != NULL);
   m_nID        = pADOConn->GetValueInt64 (DBStyle_DesFaceCode_Key_ID       );
   m_strName    = pADOConn->GetValueString(DBStyle_DesFaceCode_Key_cName    );
   m_sOldLen    = pADOConn->GetValueString(DBStyle_DesFaceCode_Key_fOldLen  );
   m_strType    = pADOConn->GetValueString(DBStyle_DesFaceCode_Key_cType    );
   m_sLen       = pADOConn->GetValueString(DBStyle_DesFaceCode_Key_fLen     );
   m_strUnit    = pADOConn->GetValueString(DBStyle_DesFaceCode_Key_cUnit    );
   m_nIDDensity = pADOConn->GetValueInt64 (DBStyle_DesFaceCode_Key_IDDensity);

   return TRUE;
}

CString CDBStyle_DesFaceCodeData::GetSQLFormat()
{
   CString strRet = _T("");
   //
   strRet.Format(_T("%s,%s,%s,%s,%s,%s"),
      DBStyle_DesFaceCode_Key_cName    ,
      DBStyle_DesFaceCode_Key_fOldLen  ,
      DBStyle_DesFaceCode_Key_cType    ,
      DBStyle_DesFaceCode_Key_fLen     ,
      DBStyle_DesFaceCode_Key_cUnit    ,
      DBStyle_DesFaceCode_Key_IDDensity
      );

   return strRet;
}

CString CDBStyle_DesFaceCodeData::GetValueFormat(const CString & strName, const CString & strOldLen, const CString & strType, const CString & strLen, const CString & strUnit, const __int64 nIDDensity)
{
   CString strRet = _T("");
   strRet.Format(_T("('%s','%s','%s','%s','%s','%lld')"),
      strName, strOldLen,  strType,strLen, strUnit, nIDDensity);
   return strRet;
}

CDBStyle_DesFaceCodeList::CDBStyle_DesFaceCodeList()
{

}

CDBStyle_DesFaceCodeList::~CDBStyle_DesFaceCodeList()
{

}


