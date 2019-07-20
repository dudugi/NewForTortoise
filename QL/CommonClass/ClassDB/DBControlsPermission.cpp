#include "StdAfx.h"
#include "DBControlsPermission.h"
#include "DBKeyDef.h"

IMPLEMENT_SERIAL(CDBControlsPermissionData,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBControlsPermissionList,  CDataListMid, 1)

std::shared_ptr<CDBControlsPermissionList> CDBControlsPermissionList::sm_inst;

CDBControlsPermissionData::CDBControlsPermissionData()
{
   ResetData();
}

CDBControlsPermissionData::~CDBControlsPermissionData()
{

}

void CDBControlsPermissionData::ResetData()
{
   m_nID          = 0;
   m_nDlgID       = 0;
   m_nDlgFlag     = 0;
   m_nControlID   = 0;
   m_nControlType = 0;

   SetDataType(DAT_CONTROLSPERMISSION);
}

void CDBControlsPermissionData::Copy(CDBControlsPermissionData *pData)
{
   ASSERT(pData != NULL);

   CDataMid::Copy(pData);
   m_nID          = pData->m_nID          ;
   m_nDlgID       = pData->m_nDlgID       ;
   m_nDlgFlag     = pData->m_nDlgFlag     ;
   m_nControlID   = pData->m_nControlID   ;
   m_nControlType = pData->m_nControlType ;
   m_strDescription = pData->m_strDescription;
}

BOOL CDBControlsPermissionData::GetAllDBInfo(CADOConn *pADOConn )
{
   ASSERT(pADOConn != NULL);

   BOOL bRet = TRUE;

   if (NULL == pADOConn)
   {
      bRet = FALSE;
   }
   else
   {
      m_nID          = pADOConn->GetValueInt64(DBControlsPermission_Key_ID        );
      m_nDlgID       = pADOConn->GetValueInt(DBControlsPermission_Key_nDlgID      );
      m_nDlgFlag     = pADOConn->GetValueInt(DBControlsPermission_Key_nDlgFlag    );
      m_nControlID   = pADOConn->GetValueInt(DBControlsPermission_Key_nControlID  );
      m_nControlType = pADOConn->GetValueInt(DBControlsPermission_Key_nControlType);
      m_strDescription = pADOConn->GetValueString(DBControlsPermission_Key_cDescription);

      bRet = TRUE;
   }

   return bRet;
}

BOOL CDBControlsPermissionData::DelAllDBInfo( CADOConn *pADOConn )
{
   ASSERT(pADOConn != NULL);
   BOOL bRet = FALSE;
   if (NULL != pADOConn)
   {
      CString strSQL = _T("");
      strSQL.Format(_T("delete from %s where %s = '%lld'"),DB_TABLE_CONTROLSPERMISSION,DBControlsPermission_Key_ID,m_nID);
      bRet = pADOConn->ExecuteSQL(strSQL);
   }

   return bRet;
}

BOOL CDBControlsPermissionData::InsertAllDBIno( CADOConn *pADOConn )
{
   ASSERT(pADOConn != NULL);
   BOOL bRet = FALSE;
   CString strSQL = GetInsertSQL();
   if (NULL != pADOConn)
   {
      bRet = pADOConn->ExecuteSQL(strSQL);
   }

   return bRet;
}

CString CDBControlsPermissionData::GetInsertSQL() const
{
   ASSERT(0 != m_nDlgID && 0 != m_nControlID);//对话框ID与控件ID不能为0
   CString strSQL = _T("");
   strSQL.Format(_T("insert into %s(%s,%s,%s,%s,%s) \
                    values('%d','%d','%d','%d','%s')"),DB_TABLE_CONTROLSPERMISSION,
                    DBControlsPermission_Key_nDlgID,DBControlsPermission_Key_nDlgFlag,
                    DBControlsPermission_Key_nControlID,DBControlsPermission_Key_nControlType,DBControlsPermission_Key_cDescription,
                    m_nDlgID,m_nDlgFlag,m_nControlID,m_nControlType,m_strDescription);
   return strSQL;
}

/*不需要更新操作
BOOL CDBControlsPermission::UpdateAllDBInfo( CADOConn *pADOConn )
{
   ASSERT(pADOConn != NULL);
   ASSERT(m_nDlgID != 0);

   BOOL bRet = TRUE;

   CString strSQL = _T("");
   strSQL.Format(_T("Update %s set %s='%d',%s='%d',%s='%d',%s='%d' where %s='%lld'"),DB_TABLE_CONTROLSPERMISSION
      ,DBControlsPermission_Key_nDlgID,m_nDlgID
      ,DBControlsPermission_Key_nDlgFlag,m_nDlgFlag
      ,DBControlsPermission_Key_nControlID,m_nControlID
      ,DBControlsPermission_Key_nControlType,m_nControlType
      ,DBControlsPermission_Key_ID,m_nID
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
}*/


CDBControlsPermissionList::CDBControlsPermissionList()
{

}

CDBControlsPermissionList::~CDBControlsPermissionList()
{

}

CDBControlsPermissionData* CDBControlsPermissionList::GetItem(int nIndex)
{
   if (nIndex<0||nIndex>=GetCount())
      return NULL;
   return (CDBControlsPermissionData*)GetAt(FindIndex(nIndex));
}

void CDBControlsPermissionList::AddItem(CDBControlsPermissionData* pItem)
{
   CDBControlsPermissionData*pData=new CDBControlsPermissionData;
   pData->Copy(pItem);
   AddTail(pData);
}

void CDBControlsPermissionList::DeleteItem(int nIndex)
{
   if (nIndex<0||nIndex>GetCount())
      return;
   CDBControlsPermissionData *pObject=(CDBControlsPermissionData*)GetItem(nIndex);
   delete pObject;
   pObject=NULL;
   RemoveAt(FindIndex(nIndex));
}

void CDBControlsPermissionList::GetListFromDB(CADOConn *pADOConn,const CString & strUserPermission)
{
   ASSERT(pADOConn != NULL);

   Empty();
   CString strSQL = _T("");
   strSQL.Format(_T("select * from %s  order by %s"),
      DB_TABLE_CONTROLSPERMISSION,DBControlsPermission_Key_ID);
   pADOConn->GetRecordSet(strSQL);
   
   int nIndex = 0,nCount = strUserPermission.GetLength();
   while (!pADOConn->adoEOF() )
   {
      if (nIndex >= nCount || '0' == strUserPermission.GetAt(nIndex))
      {
         CDBControlsPermissionData* pNewData = new CDBControlsPermissionData;
         if(pNewData->GetAllDBInfo(pADOConn))
         {
            AddTail(pNewData);
         }
         else
         {
            delete pNewData;
         }
      }

      ++nIndex;
      pADOConn->MoveNext();
   }
}

void CDBControlsPermissionList::GetListFromDB(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);

   Empty();
   CString strSQL = _T("");
   strSQL.Format(_T("select * from %s  order by %s"),
      DB_TABLE_CONTROLSPERMISSION,DBControlsPermission_Key_ID);
   pADOConn->GetRecordSet(strSQL);

   while (!pADOConn->adoEOF() )
   {
      CDBControlsPermissionData* pNewData = new CDBControlsPermissionData;
      if(pNewData->GetAllDBInfo(pADOConn))
      {
         AddTail(pNewData);
      }
      else
      {
         delete pNewData;
      }

      pADOConn->MoveNext();
   }
}

void CDBControlsPermissionList::HandleWindowNormalControlPermission(CWnd * pWnd,UINT nIDTemplete,int nDlgFlag)
{//如果要提升效率的话 可以更改为stl容器 如map hash等
   int nIndex = 0,nCount = GetCount();
   for (nIndex = 0;nIndex < nCount;++nIndex)
   {
      auto pData = GetItem(nIndex);
      if (NULL != pData && pData->m_nDlgID == nIDTemplete && pData->m_nDlgFlag == nDlgFlag 
         && pData->m_nControlType == CDBControlsPermissionData::en_Control_Normal)
      {
         auto pChildWnd = pWnd->GetDlgItem(pData->m_nControlID);
         if (NULL != pChildWnd && IsWindow(pChildWnd->GetSafeHwnd()))//此处应该做权限检测
         {
            pChildWnd->EnableWindow(FALSE);
         }
      }
   }
}


void CDBControlsPermissionList::HandleWindowMenuControlPermission(CMenu* pPopup,UINT nIDTemplete,int nDlgFlag)
{
   int nIndex = 0,nCount = GetCount();
   for (nIndex = 0;nIndex < nCount;++nIndex)
   {
      auto pData = GetItem(nIndex);
      if (NULL != pData && pData->m_nDlgID == nIDTemplete && pData->m_nDlgFlag == nDlgFlag 
         && pData->m_nControlType == CDBControlsPermissionData::en_Control_Menu)
      {
         pPopup->RemoveMenu(pData->m_nControlID,MF_BYCOMMAND|MF_GRAYED);
      }
   }
}

BOOL CDBControlsPermissionList::HasItemInControlPermission(UINT nIDTemplete,int nDlgFlag,UINT nControlID,CDBControlsPermissionData::EM_CONTROL_TYPE nControlType)
{
   int nIndex  = 0,nCount = GetCount();
   for (nIndex = 0;nIndex < nCount;++nIndex)
   {
      auto * pData = GetItem(nIndex);
      if (NULL != pData)
      {
         if (pData->m_nDlgID == nIDTemplete && pData->m_nDlgFlag == nDlgFlag 
            && pData->m_nControlType == nControlType && pData->m_nControlID == nControlID )
         {
            return TRUE;
         }
      }
   }
   return FALSE;
}

BOOL CDBControlsPermissionList::InitDBControlPermission(CADOConn * pADOConn)
{
   ASSERT(NULL != pADOConn);

   vector<CString> vecExecSQL;
   CString strSQL;
   strSQL.Format(_T("delete from %s"),DB_TABLE_CONTROLSPERMISSION);
   vecExecSQL.push_back(strSQL);

   int nCount = GetCount();
   for (int nIndex = 0;nIndex < nCount;++nIndex)
   {
      auto pData = GetItem(nIndex);
      if (NULL != pData)
      {
         strSQL = pData->GetInsertSQL();
         vecExecSQL.push_back(strSQL);
      }
   }

   return pADOConn->ExecuteSQLByTransaction(vecExecSQL);
}

CDBControlsPermissionList * CDBControlsPermissionList::Instance()
{
   if(sm_inst.get() == 0)
      sm_inst = shared_ptr<CDBControlsPermissionList>(new CDBControlsPermissionList);

   return sm_inst.get();
}
