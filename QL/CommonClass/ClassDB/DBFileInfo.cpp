#include "StdAfx.h"
#include "DBFileInfo.h"
#include "DBKeyDef.h"

IMPLEMENT_SERIAL(CDBFileInfoData,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBFileInfoList,  CDataListMid, 1)

std::shared_ptr<CDBFileInfoList> CDBFileInfoList::sm_inst;


CDBFileInfoData::CDBFileInfoData()
{
	ResetData();
} 

CDBFileInfoData::~CDBFileInfoData()
{
}

void CDBFileInfoData::ResetData()
{
   m_nFileID           = 0;
   m_strRelativePath   = _T("");
   m_strUploadUserID   = _T("");
   m_strUploadTime     = _T("");
   m_strFileMD5        = _T("");
   m_strFileName       = _T("");
   m_strFileExtension  = _T("");
   m_nFileSize         = 0;
   m_strRemark         = _T("");
	m_nParam_FileType   = -1;
   m_nParam_WholeType  = 0;
   m_strParam_Size     = _T("");

	SetDataType(DAT_FILE);
}

__int64 CDBFileInfoData::InsertAllDBInfoByProcess(CADOConn * pADOConn)
{
   return InsertAllDBInfoByProcess(pADOConn,m_strRelativePath,m_strUploadUserID,m_strFileMD5,m_nFileSize,m_strRemark,m_nParam_FileType,m_strParam_Size,m_nParam_WholeType);
}

__int64 CDBFileInfoData::InsertAllDBInfoByProcess(CADOConn * pADOConn,
   const CString & strRelativePath,/*�ļ����·�� */ 
   const CString & strUploadUserID,/*�ϴ��� */ 
   const CString & strFileMD5,/*�ļ�MD5�� */ 
   const __int64 & nFileSize,/*�ļ���С */ 
   const CString & strRemark,/*�ļ�˵�� */
   const int & nFileType,/*�ϴ�����-�ļ�����*/
   const CString & strSize,/*�ϴ�����-����*/
   const int & nWholeType/*�ϴ�����-ȫ������*/
   )
{
   ENSURE(NULL != pADOConn);
   __int64 nRet = -1;

   CString strSQL = _T("");


   //                         1       2    3    4    5    6    7      8      9      10
   strSQL.Format(_T("DECLARE @ID int \
                    exec %s \
                    '%s','%s','%s','%lld','%s','%d','%d','%s',\
                    @ID = @ID OUTPUT SELECT	@ID as '%s'")
                    ,DB_PROCESS_SAVEFILEINFO
                    ,strRelativePath
                    ,strUploadUserID 
                    ,strFileMD5   
                    ,nFileSize      
                    ,strRemark     
                    ,nFileType
                    ,nWholeType
                    ,strSize
                    ,DBFileInfo_Key_ID
                    );

   if(pADOConn->GetRecordSet(strSQL))
   {
      nRet = pADOConn->GetValueInt64(DBFileInfo_Key_ID);
   }


   return nRet;
}

void CDBFileInfoData:: Copy(CDBFileInfoData *pData)
{
	ASSERT(pData != NULL);
	CDataMid::Copy(pData);
}


//CDBFileInfoList
CDBFileInfoList::CDBFileInfoList()
{

}
CDBFileInfoList::~CDBFileInfoList()
{

}

CDBFileInfoData*  CDBFileInfoList::GetItem(int nIndex)
{
	if (nIndex<0||nIndex>=GetCount())
		return NULL;
	return (CDBFileInfoData*)GetAt(FindIndex(nIndex));
}
void CDBFileInfoList::AddItem(CDBFileInfoData* pItem)
{
	CDBFileInfoData*pData=new CDBFileInfoData;
	pData->Copy(pItem);
	AddTail(pData);
}
void CDBFileInfoList::DeleteItem(int nIndex)
{
	if (nIndex<0||nIndex>GetCount())
		return;
	CDBFileInfoData *pObject=(CDBFileInfoData*)GetItem(nIndex);
	delete pObject;
	pObject=NULL;
	RemoveAt(FindIndex(nIndex));
}

CDBFileInfoList * CDBFileInfoList::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = shared_ptr<CDBFileInfoList>(new CDBFileInfoList);

	return sm_inst.get();
}