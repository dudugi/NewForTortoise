#include "StdAfx.h"
#include "DBCloudModuleInfo_V_Data.h"
#include "DBKeyDef_V.h"


IMPLEMENT_SERIAL(CDBCloudModuleInfo_V_Data,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBCloudModuleInfo_V_List,  CDataListMid, 1)



CDBCloudModuleInfo_V_Data::CDBCloudModuleInfo_V_Data(void)
{
   ResetData();
}


CDBCloudModuleInfo_V_Data::~CDBCloudModuleInfo_V_Data(void)
{
}

//************************************
// <����>:   ResetData
// <˵��>:   
// <����>:   Wangzy
// <����>:   2019/06/04
// <Access>:public 
// <Return>:void��
//************************************
void CDBCloudModuleInfo_V_Data::ResetData()
{
   m_nID                = -1;                   //ģ���ļ�ID
   m_strOldFileName     = _T("");               //ģ���ļ���
   m_strFileSavePath    = _T("");               //ģ���ļ�·��
   m_nFileType          = 0;                    //ģ���ļ�����:(Ŀǰ�Ǽ�¼ģ���Ƿ���ѣ�0Ϊ���ܣ�1Ϊ��ѣ�
   m_nUploadSuccess     = 0;                    //ģ���ļ��Ƿ��ϴ����
   m_nState             = 0;                    //ģ���ļ�״̬
   m_strDescription     = _T("");               //ģ���ļ�����
   m_strVerifyComment   = _T("");               //ģ���ļ����������
   m_strCheckCode       = _T("");               //ģ���ļ�У����(MD5ֵ)
   m_strModType         = _T("");               //ģ������(����)
   m_strProvider        = _T("");               //ģ���ļ��Ĺ�Ӧ��
   m_strTelPhone        = _T("");               //ģ���ļ���ϵ�绰
   m_nDownLoadNum       = 0;                    //ģ���ļ����ش���
   m_strUserID          = _T("");               //�ϴ���ID
   m_strUserName        = _T("");               //�ϴ�������
   m_strUserPower       = _T("");               //�ϴ���Ȩ��
   m_strRegeditTime     = _T("");               //�ϴ���ע��ʱ��
   m_nUserState         = 0;                    //�ϴ���״̬
   m_strWechat          = _T("");               //�ϴ���΢��
   m_strQQ              = _T("");               //�ϴ���QQ
   m_strRemark          = _T("");               //�ϴ��߱�ע
   m_strSignature       = _T("");               //�ϴ����޸�ǩ��
   m_strPhoneNum        = _T("");               //�ϴ��ߵ绰����
}

//************************************
// <����>:   Copy
// <˵��>:   
// <����>:   Wangzy
// <����>:   2019/06/04
// <Access>:public 
// <Return>:void��
// <����>:   CDBCloudModuleInfo_V_Data * pData
//************************************
void CDBCloudModuleInfo_V_Data::Copy(CDBCloudModuleInfo_V_Data *pData)
{
   ASSERT(pData != NULL);
   CDataMid::Copy(pData);
   m_nID                = pData->m_nID                ;               //ģ���ļ�ID
   m_strOldFileName     = pData->m_strOldFileName     ;               //ģ���ļ���
   m_strFileSavePath    = pData->m_strFileSavePath    ;               //ģ���ļ�·��
   m_nFileType          = pData->m_nFileType          ;               //ģ���ļ�����:(Ŀǰ�Ǽ�¼ģ���Ƿ���ѣ�0Ϊ���ܣ�1Ϊ��ѣ�
   m_nUploadSuccess     = pData->m_nUploadSuccess     ;               //ģ���ļ��Ƿ��ϴ����
   m_nState             = pData->m_nState             ;               //ģ���ļ�״̬��0Ϊδ��ˣ�1Ϊ�����
   m_strDescription     = pData->m_strDescription     ;               //ģ���ļ�����
   m_strVerifyComment   = pData->m_strVerifyComment   ;               //ģ���ļ����������
   m_strCheckCode       = pData->m_strCheckCode       ;               //ģ���ļ�У����(MD5ֵ)
   m_strModType         = pData->m_strModType         ;               //ģ������(����)
   m_strProvider        = pData->m_strProvider        ;               //ģ���ļ��Ĺ�Ӧ��
   m_strTelPhone        = pData->m_strTelPhone        ;               //ģ���ļ���ϵ�绰
   m_nDownLoadNum       = pData->m_nDownLoadNum       ;               //ģ���ļ����ش���
   m_strUserID          = pData->m_strUserID          ;               //�ϴ���ID
   m_strUserName        = pData->m_strUserName        ;               //�ϴ�������
   m_strUserPower       = pData->m_strUserPower       ;               //�ϴ���Ȩ��
   m_strRegeditTime     = pData->m_strRegeditTime     ;               //�ϴ���ע��ʱ��
   m_nUserState         = pData->m_nUserState         ;               //�ϴ���״̬
   m_strWechat          = pData->m_strWechat          ;               //�ϴ���΢��
   m_strQQ              = pData->m_strQQ              ;               //�ϴ���QQ
   m_strRemark          = pData->m_strRemark          ;               //�ϴ��߱�ע
   m_strSignature       = pData->m_strSignature       ;               //�ϴ����޸�ǩ��
   m_strPhoneNum        = pData->m_strPhoneNum        ;               //�ϴ��ߵ绰����
}

//************************************
// <����>:   GetAllDBInfo
// <˵��>:   
// <����>:   Wangzy
// <����>:   2019/06/04
// <Access>:public 
// <Return>:BOOL��
// <����>:   CADOConn * pADOConn
//************************************
BOOL CDBCloudModuleInfo_V_Data::GetAllDBInfo(CADOConn *pADOConn)
{
   ASSERT(pADOConn);
   m_nID                = pADOConn->GetValueInt(   DBCloudModuleInfo_V_Key_ID);
   m_strOldFileName     = pADOConn->GetValueString(DBCloudModuleInfo_V_Key_cOldFileName);
   m_strFileSavePath    = pADOConn->GetValueString(DBCloudModuleInfo_V_Key_cFileSavePath    );
   m_nFileType          = pADOConn->GetValueInt(   DBCloudModuleInfo_V_Key_nFileType        );
   m_nUploadSuccess     = pADOConn->GetValueInt(   DBCloudModuleInfo_V_Key_bUploadSuccess   );
   m_nState             = pADOConn->GetValueInt(   DBCloudModuleInfo_V_Key_dwState          );
   m_strDescription     = pADOConn->GetValueString(DBCloudModuleInfo_V_Key_cDescription     );
   m_strVerifyComment   = pADOConn->GetValueString(DBCloudModuleInfo_V_Key_cVerifyComment   );
   m_strCheckCode       = pADOConn->GetValueString(DBCloudModuleInfo_V_Key_cCheckCode       );
   m_strModType         = pADOConn->GetValueString(DBCloudModuleInfo_V_Key_cModType         );
   m_strProvider        = pADOConn->GetValueString(DBCloudModuleInfo_V_Key_cProvider        );
   m_strTelPhone        = pADOConn->GetValueString(DBCloudModuleInfo_V_Key_cTelPhone        );
   m_nDownLoadNum       = pADOConn->GetValueInt(   DBCloudModuleInfo_V_Key_nDownLoadNum     );
   m_strUserID          = pADOConn->GetValueString(DBCloudModuleInfo_V_Key_cUserID          );
   m_strUserName        = pADOConn->GetValueString(DBCloudModuleInfo_V_Key_cUserName        );
   m_strUserPower       = pADOConn->GetValueString(DBCloudModuleInfo_V_Key_cUserPower       );
   m_strRegeditTime     = pADOConn->GetValueString(DBCloudModuleInfo_V_Key_dtRegeditTime    );
   m_nUserState         = pADOConn->GetValueInt(   DBCloudModuleInfo_V_Key_dwUserState      );
   m_strWechat          = pADOConn->GetValueString(DBCloudModuleInfo_V_Key_cWechat          );
   m_strQQ              = pADOConn->GetValueString(DBCloudModuleInfo_V_Key_cQQ              );
   m_strRemark          = pADOConn->GetValueString(DBCloudModuleInfo_V_Key_cRemark          );
   m_strSignature       = pADOConn->GetValueString(DBCloudModuleInfo_V_Key_cSignature       );
   m_strPhoneNum        = pADOConn->GetValueString(DBCloudModuleInfo_V_Key_cPhoneNum        );

   return TRUE;
}



//************************************
// <����>:   GetUpdateCheckModuleInfoSQL
// <˵��>:   ��ȡģ�������˵�SQL��䣬����Ĭ��ֵΪ-1������˱�ʶ���ɣ����򰴴���Ĳ�������
// <����>:   Wangzy
// <����>:   2019/06/04
// <Access>:public 
// <Return>:CString��
// <����>:   int nCheck
//************************************
CString CDBCloudModuleInfo_V_Data::GetUpdateCheckModuleInfoSQL(int nCheck/*=-1*/)
{
   CString strSQL;

   strSQL.Format(_T("Update %s set %s=%d where %s=%d ;"),
      
      DB_VIEW_CLOUD_MODULE_INFO,
      
      DBCloudModuleInfo_V_Key_dwState,
      nCheck==-1?m_nState:nCheck,
      
      DBCloudModuleInfo_V_Key_ID,
      m_nID);

   return strSQL;
}



//************************************
// <����>:   GetUpdateModuleInfoDeleteFlagSQL
// <˵��>:   ��ȡģ�����ɾ����־��SQL��䣬����Ĭ��ֵΪ-1�����ϴ��ı�ʶ���ɣ����򰴴���Ĳ�������;
// <����>:   Wangzy
// <����>:   2019/06/04
// <Access>:public 
// <Return>:CString��
// <����>:   int nDeleteFlag
//************************************
CString CDBCloudModuleInfo_V_Data::GetUpdateModuleInfoDeleteFlagSQL(int nDeleteFlag /*=-1*/)
{
   CString strSQL;

   strSQL.Format(_T("Update %s set %s=%d where %s=%d ;"),

      DB_VIEW_CLOUD_MODULE_INFO,

      DBCloudModuleInfo_V_Key_bUploadSuccess,
      nDeleteFlag==-1?m_nUploadSuccess:nDeleteFlag,

      DBCloudModuleInfo_V_Key_ID,
      m_nID);

   return strSQL;
}

#ifdef USING_GRIDCTRL_MARK

//************************************
// <����>:   ConvertDataToMapData
// <˵��>:   
// <����>:   Wangzy
// <����>:   2019/06/04
// <Access>:public static 
// <Return>:BOOL��
// <����>:   __out MAP_GridCtrl_RowData & mapData
// <����>:   __in CDBCloudModuleInfo_V_Data * pData
//************************************
BOOL CDBCloudModuleInfo_V_Data::ConvertDataToMapData(__out MAP_GridCtrl_RowData &mapData, __in CDBCloudModuleInfo_V_Data *pData)
{
   if (nullptr==pData)
   {
      return FALSE;
   }
   CString strCheck = _T("δ���");
   switch(pData->m_nState)
   {
   case 0:
      {
         strCheck = _T("δ���");
      }
      break;
   case 1:
      {
         strCheck = _T("�����");
      }
      break;
   case 2:
      {
         strCheck = _T("���ʧ��");
      }
   default:
      break;
   }

   CDataMid::InsertRowData(DBCloudModuleInfo_V_Key_ID                ,mapData    ,_T("%d")        ,pData->m_nID            );                            //ģ���ļ�ID
   CDataMid::InsertRowData(DBCloudModuleInfo_V_Key_nFileType         ,mapData    ,_T("%s")        ,pData->m_nFileType==0?_T("����"):_T("���"));          //ģ���ļ�����:(Ŀǰ�Ǽ�¼ģ���Ƿ���ѣ�0Ϊ���ܣ�1Ϊ��ѣ�
   CDataMid::InsertRowData(DBCloudModuleInfo_V_Key_bUploadSuccess    ,mapData    ,_T("%s")        ,pData->m_nUploadSuccess==1?_T("���ϴ�"):_T("δ�ϴ�") ); //ģ���ļ��Ƿ��ϴ����
   CDataMid::InsertRowData(DBCloudModuleInfo_V_Key_dwState           ,mapData    ,_T("%s")        ,strCheck);                                            //ģ���ļ�״̬   
   CDataMid::InsertRowData(DBCloudModuleInfo_V_Key_nDownLoadNum      ,mapData    ,_T("%d")        ,pData->m_nDownLoadNum   );                            //ģ���ļ����ش���
   CDataMid::InsertRowData(DBCloudModuleInfo_V_Key_dwUserState       ,mapData    ,_T("%d")        ,pData->m_nUserState     );                            //�ϴ���״̬

   CDataMid::InsertRowData(DBCloudModuleInfo_V_Key_cOldFileName      ,pData->m_strOldFileName     ,mapData);                        //ģ���ļ���
   CDataMid::InsertRowData(DBCloudModuleInfo_V_Key_cFileSavePath     ,pData->m_strFileSavePath    ,mapData);                        //ģ���ļ�·��
   CDataMid::InsertRowData(DBCloudModuleInfo_V_Key_cDescription      ,pData->m_strDescription     ,mapData);                        //ģ���ļ�����
   CDataMid::InsertRowData(DBCloudModuleInfo_V_Key_cVerifyComment    ,pData->m_strVerifyComment   ,mapData);                        //ģ���ļ����������
   CDataMid::InsertRowData(DBCloudModuleInfo_V_Key_cCheckCode        ,pData->m_strCheckCode       ,mapData);                        //ģ���ļ�У����(MD5ֵ)
   CDataMid::InsertRowData(DBCloudModuleInfo_V_Key_cModType          ,pData->m_strModType         ,mapData);                        //ģ������(����)
   CDataMid::InsertRowData(DBCloudModuleInfo_V_Key_cProvider         ,pData->m_strProvider        ,mapData);                        //ģ���ļ��Ĺ�Ӧ��
   CDataMid::InsertRowData(DBCloudModuleInfo_V_Key_cTelPhone         ,pData->m_strTelPhone        ,mapData);                        //ģ���ļ���ϵ�绰
   CDataMid::InsertRowData(DBCloudModuleInfo_V_Key_cUserID           ,pData->m_strUserID          ,mapData);                        //�ϴ���ID
   CDataMid::InsertRowData(DBCloudModuleInfo_V_Key_cUserName         ,pData->m_strUserName        ,mapData);                        //�ϴ�������
   CDataMid::InsertRowData(DBCloudModuleInfo_V_Key_cUserPower        ,pData->m_strUserPower       ,mapData);                        //�ϴ���Ȩ��
   CDataMid::InsertRowData(DBCloudModuleInfo_V_Key_dtRegeditTime     ,pData->m_strRegeditTime     ,mapData);                        //�ϴ���ע��ʱ��
   CDataMid::InsertRowData(DBCloudModuleInfo_V_Key_cWechat           ,pData->m_strWechat          ,mapData);                        //�ϴ���΢��
   CDataMid::InsertRowData(DBCloudModuleInfo_V_Key_cQQ               ,pData->m_strQQ              ,mapData);                        //�ϴ���QQ
   CDataMid::InsertRowData(DBCloudModuleInfo_V_Key_cRemark           ,pData->m_strRemark          ,mapData);                        //�ϴ��߱�ע
   CDataMid::InsertRowData(DBCloudModuleInfo_V_Key_cSignature        ,pData->m_strSignature       ,mapData);                        //�ϴ����޸�ǩ��
   CDataMid::InsertRowData(DBCloudModuleInfo_V_Key_cPhoneNum         ,pData->m_strPhoneNum        ,mapData);                        //�ϴ��ߵ绰����

   return TRUE;
}

#endif   //USING_GRIDCTRL_MARK


//************************************
// <����>:   CDBCloudModuleInfo_V_List
// <˵��>:   
// <����>:   Wangzy
// <����>:   2019/06/04
// <Access>:public 
// <Return>:��
// <����>:   void
//************************************
CDBCloudModuleInfo_V_List::CDBCloudModuleInfo_V_List(void)
{

}

//************************************
// <����>:   ~CDBCloudModuleInfo_V_List
// <˵��>:   
// <����>:   Wangzy
// <����>:   2019/06/04
// <Access>:public 
// <Return>:��
// <����>:   void
//************************************
CDBCloudModuleInfo_V_List::~CDBCloudModuleInfo_V_List(void)
{

}

//************************************
// <����>:   Copy
// <˵��>:   
// <����>:   Wangzy
// <����>:   2019/06/04
// <Access>:public 
// <Return>:void��
// <����>:   CDBCloudModuleInfo_V_List * pList
//************************************
void CDBCloudModuleInfo_V_List::Copy(CDBCloudModuleInfo_V_List *pList)
{
   Empty();
   if (pList != NULL)
   {
      for (int nIndex = 0;nIndex < pList->GetCount();nIndex++)
      {
         CDBCloudModuleInfo_V_Data *pData = (CDBCloudModuleInfo_V_Data *)pList->GetAt(pList->FindIndex(nIndex));
         if (pData != NULL)
         {
            AddItem(pData);
         }
      }
   }
}

//************************************
// <����>:   GetItem
// <˵��>:   
// <����>:   Wangzy
// <����>:   2019/06/04
// <Access>:public 
// <Return>:CDBCloudModuleInfo_V_Data*��
// <����>:   int nIndex
//************************************
CDBCloudModuleInfo_V_Data* CDBCloudModuleInfo_V_List::GetItem(int nIndex)
{
   if (nIndex<0
      ||nIndex>=GetCount())
   {
      return nullptr;
   }

   return (CDBCloudModuleInfo_V_Data*)GetAt(FindIndex(nIndex));  
}

//************************************
// <����>:   GetItemByID
// <˵��>:   
// <����>:   Wangzy
// <����>:   2019/06/04
// <Access>:public 
// <Return>:CDBCloudModuleInfo_V_Data*��
// <����>:   const CString & strID
//************************************
CDBCloudModuleInfo_V_Data* CDBCloudModuleInfo_V_List::GetItemByID(const CString & strID)
{
   CDBCloudModuleInfo_V_Data * pItem = NULL;
   if (!strID.IsEmpty())
   {
      int nID = _ttoi(strID);
      int count = GetCount();
      for(int i=0;i< count;++i)
      {
         CDBCloudModuleInfo_V_Data * pObject = GetItem(i);
         if(NULL != pObject 
            && pObject->m_nID == nID)
         {
            pItem = pObject;
            break;
         }
      }
   }

   return pItem;
}

//************************************
// <����>:   GetItemByID
// <˵��>:   
// <����>:   Wangzy
// <����>:   2019/06/04
// <Access>:public 
// <Return>:CDBCloudModuleInfo_V_Data*��
// <����>:   const int & nID
//************************************
CDBCloudModuleInfo_V_Data* CDBCloudModuleInfo_V_List::GetItemByID(const int & nID)
{
   CDBCloudModuleInfo_V_Data * pItem = NULL;
   if (-1!=nID)
   {
      int count = GetCount();
      for(int i=0;i< count;++i)
      {
         CDBCloudModuleInfo_V_Data * pObject = GetItem(i);
         if(NULL != pObject 
            && pObject->m_nID == nID)
         {
            pItem = pObject;
            break;
         }
      }
   }

   return pItem;
}

//************************************
// <����>:   GetIndexByID
// <˵��>:   
// <����>:   Wangzy
// <����>:   2019/06/04
// <Access>:public 
// <Return>:int��
// <����>:   const CString & strID
//************************************
int CDBCloudModuleInfo_V_List::GetIndexByID(const CString & strID)
{
   int nRet = -1;
   if (!strID.IsEmpty())
   {
      int nID = _ttoi(strID);
      int count = GetCount();
      for(int i=0;i< count;++i)
      {
         CDBCloudModuleInfo_V_Data * pObject = GetItem(i);
         if(NULL != pObject 
            && pObject->m_nID == nID)
         {
            nRet = i;
            break;
         }
      }
   }

   return nRet;
}

//************************************
// <����>:   GetIndexByID
// <˵��>:   
// <����>:   Wangzy
// <����>:   2019/06/04
// <Access>:public 
// <Return>:int��
// <����>:   const int & nID
//************************************
int CDBCloudModuleInfo_V_List::GetIndexByID(const int & nID)
{
   int nRet = -1;
   if (-1!=nID)
   {
      int count = GetCount();
      for(int i=0;i< count;++i)
      {
         CDBCloudModuleInfo_V_Data * pObject = GetItem(i);
         if(NULL != pObject 
            && pObject->m_nID == nID)
         {
            nRet = i;
            break;
         }
      }
   }

   return nRet;
}

//************************************
// <����>:   AddItem
// <˵��>:   
// <����>:   Wangzy
// <����>:   2019/06/04
// <Access>:public 
// <Return>:void��
// <����>:   CDBCloudModuleInfo_V_Data * pItem
//************************************
void CDBCloudModuleInfo_V_List::AddItem(CDBCloudModuleInfo_V_Data *pItem)
{
   ASSERT(pItem != NULL);
   CDBCloudModuleInfo_V_Data *pData= new CDBCloudModuleInfo_V_Data;
   pData->Copy(pItem);
   AddTail(pData);
}

//************************************
// <����>:   DeleteItemByIndex
// <˵��>:   
// <����>:   Wangzy
// <����>:   2019/06/04
// <Access>:public 
// <Return>:void��
// <����>:   int nIndex
//************************************
void CDBCloudModuleInfo_V_List::DeleteItemByIndex(int nIndex)
{
   if ((nIndex>=0
      &&nIndex<GetCount()))
   {
      CDBCloudModuleInfo_V_Data *pData =(CDBCloudModuleInfo_V_Data *)GetAt(FindIndex(nIndex));
      if (pData != nullptr)
      {
         RemoveAt(FindIndex(nIndex));
         delete pData;
         pData = nullptr;
      }
   }
}

//************************************
// <����>:   DeleteItemByID
// <˵��>:   
// <����>:   Wangzy
// <����>:   2019/06/04
// <Access>:public 
// <Return>:void��
// <����>:   CString strID
//************************************
void CDBCloudModuleInfo_V_List::DeleteItemByID(CString strID)
{
   int nIndex = GetIndexByID(strID);
   if (nIndex != -1)
   {
      DeleteItemByIndex(nIndex);
   }
}

//************************************
// <����>:   DeleteItemByID
// <˵��>:   
// <����>:   Wangzy
// <����>:   2019/06/04
// <Access>:public 
// <Return>:void��
// <����>:   int nID
//************************************
void CDBCloudModuleInfo_V_List::DeleteItemByID(int nID)
{
   int nIndex = GetIndexByID(nID);
   if (nIndex != -1)
   {
      DeleteItemByIndex(nIndex);
   }
}


//************************************
// <����>:   GetCloudModuleInfo
// <˵��>:   �����ݿ��ȡ��ģ����Ϣ
// <����>:   Wangzy
// <����>:   2019/06/04
// <Access>:public 
// <Return>:int����������
// <����>:   CADOConn * pADOConn
// <����>:   const CString & strFilter
//************************************
int CDBCloudModuleInfo_V_List::GetCloudModuleInfo(CADOConn *pADOConn, const CString &strFilter)
{
   ASSERT(pADOConn != NULL);
   
   CString strSQL;

   strSQL.Format(_T("select * from %s %s ;"),
      DB_VIEW_CLOUD_MODULE_INFO,
       strFilter);

   pADOConn->GetRecordSet(strSQL);
   while (!pADOConn->adoEOF())
   {
      CDBCloudModuleInfo_V_Data data;
      data.GetAllDBInfo(pADOConn);
      AddItem(&data);
      pADOConn->MoveNext();
   }
   int nRet = GetCount();

   return nRet;
}

#ifdef USING_GRIDCTRL_MARK

//************************************
// <����>:   ConvertListToGridMap
// <˵��>:   List�б�ת��ΪMap�б�
// <����>:   Wangzy
// <����>:   2019/06/04
// <Access>:public static 
// <Return>:BOOL��
// <����>:   __out MAP_GridCtrl_AllData & mapData
// <����>:   __in CDBCloudModuleInfo_V_List & listData
//************************************
BOOL CDBCloudModuleInfo_V_List::ConvertListToGridMap(__out MAP_GridCtrl_AllData &mapData,__in CDBCloudModuleInfo_V_List &listData)
{
   mapData.clear();
   int nCount = listData.GetCount();
   for (int nIndex=0; nIndex<nCount; ++nIndex)
   {
      auto pData = listData.GetItem(nIndex);
      if (nullptr == pData)
      {
         continue;
      }
      MAP_GridCtrl_RowData mapRowData;
      BOOL bSuc = CDBCloudModuleInfo_V_Data::ConvertDataToMapData(mapRowData,pData);
      if (bSuc)
      {
         mapData.insert(make_pair(nIndex,mapRowData));
      }
   }

   return TRUE;
}

#endif   //USING_GRIDCTRL_MARK
