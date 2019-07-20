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
// <函数>:   ResetData
// <说明>:   
// <作者>:   Wangzy
// <日期>:   2019/06/04
// <Access>:public 
// <Return>:void：
//************************************
void CDBCloudModuleInfo_V_Data::ResetData()
{
   m_nID                = -1;                   //模块文件ID
   m_strOldFileName     = _T("");               //模块文件名
   m_strFileSavePath    = _T("");               //模块文件路径
   m_nFileType          = 0;                    //模块文件类型:(目前是记录模块是否免费，0为加密，1为免费）
   m_nUploadSuccess     = 0;                    //模块文件是否上传完成
   m_nState             = 0;                    //模块文件状态
   m_strDescription     = _T("");               //模块文件描述
   m_strVerifyComment   = _T("");               //模块文件审核人评语
   m_strCheckCode       = _T("");               //模块文件校验码(MD5值)
   m_strModType         = _T("");               //模块类型(分类)
   m_strProvider        = _T("");               //模块文件的供应商
   m_strTelPhone        = _T("");               //模块文件联系电话
   m_nDownLoadNum       = 0;                    //模块文件下载次数
   m_strUserID          = _T("");               //上传者ID
   m_strUserName        = _T("");               //上传者名称
   m_strUserPower       = _T("");               //上传者权限
   m_strRegeditTime     = _T("");               //上传者注册时间
   m_nUserState         = 0;                    //上传者状态
   m_strWechat          = _T("");               //上传者微信
   m_strQQ              = _T("");               //上传者QQ
   m_strRemark          = _T("");               //上传者备注
   m_strSignature       = _T("");               //上传者修改签名
   m_strPhoneNum        = _T("");               //上传者电话号码
}

//************************************
// <函数>:   Copy
// <说明>:   
// <作者>:   Wangzy
// <日期>:   2019/06/04
// <Access>:public 
// <Return>:void：
// <参数>:   CDBCloudModuleInfo_V_Data * pData
//************************************
void CDBCloudModuleInfo_V_Data::Copy(CDBCloudModuleInfo_V_Data *pData)
{
   ASSERT(pData != NULL);
   CDataMid::Copy(pData);
   m_nID                = pData->m_nID                ;               //模块文件ID
   m_strOldFileName     = pData->m_strOldFileName     ;               //模块文件名
   m_strFileSavePath    = pData->m_strFileSavePath    ;               //模块文件路径
   m_nFileType          = pData->m_nFileType          ;               //模块文件类型:(目前是记录模块是否免费，0为加密，1为免费）
   m_nUploadSuccess     = pData->m_nUploadSuccess     ;               //模块文件是否上传完成
   m_nState             = pData->m_nState             ;               //模块文件状态：0为未审核，1为已审核
   m_strDescription     = pData->m_strDescription     ;               //模块文件描述
   m_strVerifyComment   = pData->m_strVerifyComment   ;               //模块文件审核人评语
   m_strCheckCode       = pData->m_strCheckCode       ;               //模块文件校验码(MD5值)
   m_strModType         = pData->m_strModType         ;               //模块类型(分类)
   m_strProvider        = pData->m_strProvider        ;               //模块文件的供应商
   m_strTelPhone        = pData->m_strTelPhone        ;               //模块文件联系电话
   m_nDownLoadNum       = pData->m_nDownLoadNum       ;               //模块文件下载次数
   m_strUserID          = pData->m_strUserID          ;               //上传者ID
   m_strUserName        = pData->m_strUserName        ;               //上传者名称
   m_strUserPower       = pData->m_strUserPower       ;               //上传者权限
   m_strRegeditTime     = pData->m_strRegeditTime     ;               //上传者注册时间
   m_nUserState         = pData->m_nUserState         ;               //上传者状态
   m_strWechat          = pData->m_strWechat          ;               //上传者微信
   m_strQQ              = pData->m_strQQ              ;               //上传者QQ
   m_strRemark          = pData->m_strRemark          ;               //上传者备注
   m_strSignature       = pData->m_strSignature       ;               //上传者修改签名
   m_strPhoneNum        = pData->m_strPhoneNum        ;               //上传者电话号码
}

//************************************
// <函数>:   GetAllDBInfo
// <说明>:   
// <作者>:   Wangzy
// <日期>:   2019/06/04
// <Access>:public 
// <Return>:BOOL：
// <参数>:   CADOConn * pADOConn
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
// <函数>:   GetUpdateCheckModuleInfoSQL
// <说明>:   获取模块更新审核的SQL语句，参数默认值为-1即按审核标识生成，否则按传输的参数生成
// <作者>:   Wangzy
// <日期>:   2019/06/04
// <Access>:public 
// <Return>:CString：
// <参数>:   int nCheck
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
// <函数>:   GetUpdateModuleInfoDeleteFlagSQL
// <说明>:   获取模块更新删除标志的SQL语句，参数默认值为-1即按上传的标识生成，否则按传输的参数生成;
// <作者>:   Wangzy
// <日期>:   2019/06/04
// <Access>:public 
// <Return>:CString：
// <参数>:   int nDeleteFlag
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
// <函数>:   ConvertDataToMapData
// <说明>:   
// <作者>:   Wangzy
// <日期>:   2019/06/04
// <Access>:public static 
// <Return>:BOOL：
// <参数>:   __out MAP_GridCtrl_RowData & mapData
// <参数>:   __in CDBCloudModuleInfo_V_Data * pData
//************************************
BOOL CDBCloudModuleInfo_V_Data::ConvertDataToMapData(__out MAP_GridCtrl_RowData &mapData, __in CDBCloudModuleInfo_V_Data *pData)
{
   if (nullptr==pData)
   {
      return FALSE;
   }
   CString strCheck = _T("未审核");
   switch(pData->m_nState)
   {
   case 0:
      {
         strCheck = _T("未审核");
      }
      break;
   case 1:
      {
         strCheck = _T("已审核");
      }
      break;
   case 2:
      {
         strCheck = _T("审核失败");
      }
   default:
      break;
   }

   CDataMid::InsertRowData(DBCloudModuleInfo_V_Key_ID                ,mapData    ,_T("%d")        ,pData->m_nID            );                            //模块文件ID
   CDataMid::InsertRowData(DBCloudModuleInfo_V_Key_nFileType         ,mapData    ,_T("%s")        ,pData->m_nFileType==0?_T("加密"):_T("免费"));          //模块文件类型:(目前是记录模块是否免费，0为加密，1为免费）
   CDataMid::InsertRowData(DBCloudModuleInfo_V_Key_bUploadSuccess    ,mapData    ,_T("%s")        ,pData->m_nUploadSuccess==1?_T("已上传"):_T("未上传") ); //模块文件是否上传完成
   CDataMid::InsertRowData(DBCloudModuleInfo_V_Key_dwState           ,mapData    ,_T("%s")        ,strCheck);                                            //模块文件状态   
   CDataMid::InsertRowData(DBCloudModuleInfo_V_Key_nDownLoadNum      ,mapData    ,_T("%d")        ,pData->m_nDownLoadNum   );                            //模块文件下载次数
   CDataMid::InsertRowData(DBCloudModuleInfo_V_Key_dwUserState       ,mapData    ,_T("%d")        ,pData->m_nUserState     );                            //上传者状态

   CDataMid::InsertRowData(DBCloudModuleInfo_V_Key_cOldFileName      ,pData->m_strOldFileName     ,mapData);                        //模块文件名
   CDataMid::InsertRowData(DBCloudModuleInfo_V_Key_cFileSavePath     ,pData->m_strFileSavePath    ,mapData);                        //模块文件路径
   CDataMid::InsertRowData(DBCloudModuleInfo_V_Key_cDescription      ,pData->m_strDescription     ,mapData);                        //模块文件描述
   CDataMid::InsertRowData(DBCloudModuleInfo_V_Key_cVerifyComment    ,pData->m_strVerifyComment   ,mapData);                        //模块文件审核人评语
   CDataMid::InsertRowData(DBCloudModuleInfo_V_Key_cCheckCode        ,pData->m_strCheckCode       ,mapData);                        //模块文件校验码(MD5值)
   CDataMid::InsertRowData(DBCloudModuleInfo_V_Key_cModType          ,pData->m_strModType         ,mapData);                        //模块类型(分类)
   CDataMid::InsertRowData(DBCloudModuleInfo_V_Key_cProvider         ,pData->m_strProvider        ,mapData);                        //模块文件的供应商
   CDataMid::InsertRowData(DBCloudModuleInfo_V_Key_cTelPhone         ,pData->m_strTelPhone        ,mapData);                        //模块文件联系电话
   CDataMid::InsertRowData(DBCloudModuleInfo_V_Key_cUserID           ,pData->m_strUserID          ,mapData);                        //上传者ID
   CDataMid::InsertRowData(DBCloudModuleInfo_V_Key_cUserName         ,pData->m_strUserName        ,mapData);                        //上传者名称
   CDataMid::InsertRowData(DBCloudModuleInfo_V_Key_cUserPower        ,pData->m_strUserPower       ,mapData);                        //上传者权限
   CDataMid::InsertRowData(DBCloudModuleInfo_V_Key_dtRegeditTime     ,pData->m_strRegeditTime     ,mapData);                        //上传者注册时间
   CDataMid::InsertRowData(DBCloudModuleInfo_V_Key_cWechat           ,pData->m_strWechat          ,mapData);                        //上传者微信
   CDataMid::InsertRowData(DBCloudModuleInfo_V_Key_cQQ               ,pData->m_strQQ              ,mapData);                        //上传者QQ
   CDataMid::InsertRowData(DBCloudModuleInfo_V_Key_cRemark           ,pData->m_strRemark          ,mapData);                        //上传者备注
   CDataMid::InsertRowData(DBCloudModuleInfo_V_Key_cSignature        ,pData->m_strSignature       ,mapData);                        //上传者修改签名
   CDataMid::InsertRowData(DBCloudModuleInfo_V_Key_cPhoneNum         ,pData->m_strPhoneNum        ,mapData);                        //上传者电话号码

   return TRUE;
}

#endif   //USING_GRIDCTRL_MARK


//************************************
// <函数>:   CDBCloudModuleInfo_V_List
// <说明>:   
// <作者>:   Wangzy
// <日期>:   2019/06/04
// <Access>:public 
// <Return>:：
// <参数>:   void
//************************************
CDBCloudModuleInfo_V_List::CDBCloudModuleInfo_V_List(void)
{

}

//************************************
// <函数>:   ~CDBCloudModuleInfo_V_List
// <说明>:   
// <作者>:   Wangzy
// <日期>:   2019/06/04
// <Access>:public 
// <Return>:：
// <参数>:   void
//************************************
CDBCloudModuleInfo_V_List::~CDBCloudModuleInfo_V_List(void)
{

}

//************************************
// <函数>:   Copy
// <说明>:   
// <作者>:   Wangzy
// <日期>:   2019/06/04
// <Access>:public 
// <Return>:void：
// <参数>:   CDBCloudModuleInfo_V_List * pList
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
// <函数>:   GetItem
// <说明>:   
// <作者>:   Wangzy
// <日期>:   2019/06/04
// <Access>:public 
// <Return>:CDBCloudModuleInfo_V_Data*：
// <参数>:   int nIndex
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
// <函数>:   GetItemByID
// <说明>:   
// <作者>:   Wangzy
// <日期>:   2019/06/04
// <Access>:public 
// <Return>:CDBCloudModuleInfo_V_Data*：
// <参数>:   const CString & strID
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
// <函数>:   GetItemByID
// <说明>:   
// <作者>:   Wangzy
// <日期>:   2019/06/04
// <Access>:public 
// <Return>:CDBCloudModuleInfo_V_Data*：
// <参数>:   const int & nID
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
// <函数>:   GetIndexByID
// <说明>:   
// <作者>:   Wangzy
// <日期>:   2019/06/04
// <Access>:public 
// <Return>:int：
// <参数>:   const CString & strID
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
// <函数>:   GetIndexByID
// <说明>:   
// <作者>:   Wangzy
// <日期>:   2019/06/04
// <Access>:public 
// <Return>:int：
// <参数>:   const int & nID
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
// <函数>:   AddItem
// <说明>:   
// <作者>:   Wangzy
// <日期>:   2019/06/04
// <Access>:public 
// <Return>:void：
// <参数>:   CDBCloudModuleInfo_V_Data * pItem
//************************************
void CDBCloudModuleInfo_V_List::AddItem(CDBCloudModuleInfo_V_Data *pItem)
{
   ASSERT(pItem != NULL);
   CDBCloudModuleInfo_V_Data *pData= new CDBCloudModuleInfo_V_Data;
   pData->Copy(pItem);
   AddTail(pData);
}

//************************************
// <函数>:   DeleteItemByIndex
// <说明>:   
// <作者>:   Wangzy
// <日期>:   2019/06/04
// <Access>:public 
// <Return>:void：
// <参数>:   int nIndex
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
// <函数>:   DeleteItemByID
// <说明>:   
// <作者>:   Wangzy
// <日期>:   2019/06/04
// <Access>:public 
// <Return>:void：
// <参数>:   CString strID
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
// <函数>:   DeleteItemByID
// <说明>:   
// <作者>:   Wangzy
// <日期>:   2019/06/04
// <Access>:public 
// <Return>:void：
// <参数>:   int nID
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
// <函数>:   GetCloudModuleInfo
// <说明>:   从数据库获取云模块信息
// <作者>:   Wangzy
// <日期>:   2019/06/04
// <Access>:public 
// <Return>:int：返回数量
// <参数>:   CADOConn * pADOConn
// <参数>:   const CString & strFilter
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
// <函数>:   ConvertListToGridMap
// <说明>:   List列表转换为Map列表
// <作者>:   Wangzy
// <日期>:   2019/06/04
// <Access>:public static 
// <Return>:BOOL：
// <参数>:   __out MAP_GridCtrl_AllData & mapData
// <参数>:   __in CDBCloudModuleInfo_V_List & listData
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
