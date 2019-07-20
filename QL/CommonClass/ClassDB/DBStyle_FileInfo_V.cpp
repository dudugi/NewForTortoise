#include "StdAfx.h"
#include "DBKeyDef.h"
#include "DBStyle_FileInfo_V.h"
#include "DBKeyDef_V.h"

IMPLEMENT_SERIAL(CDBStyle_FileInfo_VData,  CDataMid, 1)

CDBStyle_FileInfo_VData::CDBStyle_FileInfo_VData(void)
{
   ResetData();
}


CDBStyle_FileInfo_VData::~CDBStyle_FileInfo_VData(void)
{
}

void CDBStyle_FileInfo_VData::ResetData()
{
   m_ID               = 0;
   m_nFileID          = 0;
   m_strStyleNo       = _T("");
   m_nFileType        = 0;
   m_strRelativePath  = _T("");
   m_strUploadUserID  = _T("");
   m_strUploadTime    = _T("");
   m_strFileMD5       = _T("");
   m_strFileName      = _T("");
   m_strFileExtension = _T("");
   m_nFileSize        = 0;
   m_strRemark        = _T("");
   m_nSort = 1;
   m_nParam_FileType = -1;
   m_nParam_WholeType= 0;
   m_strParam_Size   = _T("");


   SetDataType(DAT_STYLE_FILEINFO);
}

void CDBStyle_FileInfo_VData::Copy( CDBStyle_FileInfo_VData *pData )
{
   ASSERT(pData != NULL);
   CDataMid::Copy(pData);

   m_ID               = pData->m_ID               ;
   m_nFileID          = pData->m_nFileID          ;
   m_strStyleNo       = pData->m_strStyleNo       ;
   m_nFileType        = pData->m_nFileType        ;
   m_strRelativePath  = pData->m_strRelativePath  ;
   m_strUploadUserID  = pData->m_strUploadUserID  ;
   m_strUploadTime    = pData->m_strUploadTime    ;
   m_strFileMD5       = pData->m_strFileMD5       ;
   m_strFileName      = pData->m_strFileName      ;
   m_strFileExtension = pData->m_strFileExtension ;
   m_nFileSize        = pData->m_nFileSize        ;
   m_strRemark        = pData->m_strRemark        ;
   m_nSort            = pData->m_nSort            ;
   m_nParam_FileType  = pData->m_nParam_FileType  ;
   m_nParam_WholeType = pData->m_nParam_WholeType ;
   m_strParam_Size    = pData->m_strParam_Size    ;
}

BOOL CDBStyle_FileInfo_VData::GetAllDBInfo( CADOConn *pADOConn)
{
   ASSERT(pADOConn);

   m_ID              = pADOConn->GetValueInt64 (DBStyleFileInfo_V_key_ID             );
   m_nFileID         = pADOConn->GetValueInt64 (DBStyleFileInfo_V_key_nFileID        );
   m_strStyleNo      = pADOConn->GetValueString(DBStyleFileInfo_V_key_cStyleNo       );
   m_nFileType       = pADOConn->GetValueInt64 (DBStyleFileInfo_V_key_nFileType      );
   m_strRelativePath = pADOConn->GetValueString(DBStyleFileInfo_V_key_cRelativePath  );
   m_strRelativePath.MakeLower(); //ͳһСд by duchen
   m_strUploadUserID = pADOConn->GetValueString(DBStyleFileInfo_V_key_cUploadUserID  );
   m_strUploadTime   = pADOConn->GetValueString(DBStyleFileInfo_V_key_cUploadTime    );
   m_strFileMD5      = pADOConn->GetValueString(DBStyleFileInfo_V_key_cFileMD5       );
   m_strFileName     = pADOConn->GetValueString(DBStyleFileInfo_V_key_cFileName      );
   m_strFileExtension= pADOConn->GetValueString(DBStyleFileInfo_V_key_cFileExtension );
   m_nFileSize       = pADOConn->GetValueInt64 (DBStyleFileInfo_V_key_nFileSize      );
   m_strRemark       = pADOConn->GetValueString(DBStyleFileInfo_V_key_cRemark        );
   m_nSort           = pADOConn->GetValueInt   (DBStyleFileInfo_V_key_nSort          );
   m_nParam_FileType = pADOConn->GetValueInt   (DBStyleFileInfo_V_key_nParam_FileType );
   m_nParam_WholeType= pADOConn->GetValueInt   (DBStyleFileInfo_V_key_nParam_WholeType);
   m_strParam_Size   = pADOConn->GetValueString(DBStyleFileInfo_V_key_cParam_Size     );

   return TRUE;
}

void CDBStyle_FileInfo_VList::GetStyleFileInfo(CADOConn* pAdo,CString strStyleNo,vector<CDBStyle_FileInfo_VData*>& vecFileInfo)
{
  ASSERT(pAdo != nullptr);
  ASSERT(!strStyleNo.IsEmpty());
  vecFileInfo.clear();
  CString strSql;
  strSql.Format(_T("select * from V_StyleFileInfo where cStyleNo = '%s'"),strStyleNo);
  pAdo->GetRecordSet(strSql);
  while(!pAdo->adoEOF())
  {
     CDBStyle_FileInfo_VData* pData = new CDBStyle_FileInfo_VData;
     pData->GetAllDBInfo(pAdo);
     vecFileInfo.push_back(pData);
     pAdo->MoveNext();
  }
}
