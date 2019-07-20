#include "StdAfx.h"
#include "DBBindInfo.h"


IMPLEMENT_SERIAL(CDBP_BindInfoData,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBP_BindInfoList,  CDataListMid, 1)

CDBP_BindInfoData::CDBP_BindInfoData(void)
{
   ResetData();
}


CDBP_BindInfoData::~CDBP_BindInfoData(void)
{
}

void CDBP_BindInfoData::ResetData()
{
   m_nID = 0;
   m_strName = _T("");                 //名称
   m_oleBandStartTime = _T("");        //波段开始时间
   m_oleDesignEndTime  = _T("");        //设计完成时间
   m_olePatternEndTime  = _T("");       //纸样完成时间
   m_oleReviewEndTime  = _T("");        //内审会完成时间
   m_oleBandEndTime  = _T("");          //波段结束时间
   m_strStylish  = _T("");              //风格
   m_strColor  = _T("");                //色系
   m_bCheckState = FALSE;             //审核标识
   m_strRemark = _T("");               //备注
   m_nAssociatedProgrammingID = NULL;                 //所属商品规划的ID
   m_strSeriaNum = _T("");               //序号
   m_strDeliveryStartTime = _T("");    //货期起始时间
   m_strDeliveryEndTime = _T("");      //货期结束时间
   m_strShelvesTime = _T("");          //上货日
   m_strCheckUserID = _T("");          //审核人
   m_strCheckTime = _T("");            //审核时间
   m_strCreateUserID = _T("");         //创建人
   m_strCreateUserTime = _T("");       //创建时间
   SetDataType(DAT_BINDINFO);
}

void CDBP_BindInfoData::Copy( CDBP_BindInfoData *pData )
{
   ASSERT(pData != NULL);
   CDataMid::Copy(pData);
   m_nID = pData->m_nID;
   m_strName = pData->m_strName;                                  //名称
   m_oleBandStartTime = pData->m_oleBandStartTime;                //波段开始时间
   m_oleDesignEndTime  =pData->m_oleDesignEndTime;                //设计完成时间
   m_olePatternEndTime  = pData->m_olePatternEndTime;             //纸样完成时间
   m_oleReviewEndTime  = pData->m_oleReviewEndTime;               //内审会完成时间
   m_oleBandEndTime  = pData->m_oleBandEndTime;                   //波段结束时间
   m_strStylish  = pData->m_strStylish;                           //风格
   m_strColor  = pData->m_strColor;                               //色系
   m_bCheckState = pData->m_bCheckState;                          //审核标识
   m_strRemark = pData->m_strRemark;                              //备注
   m_nAssociatedProgrammingID = pData->m_nAssociatedProgrammingID;//所属商品规划的ID
   m_strSeriaNum = pData->m_strSeriaNum;                              //序号
   m_strDeliveryStartTime = pData->m_strDeliveryStartTime;        //货期起始时间
   m_strDeliveryEndTime = pData->m_strDeliveryEndTime;            //货期结束时间
   m_strShelvesTime = pData->m_strShelvesTime;                    //上货日
   m_strCheckUserID = pData->m_strCheckUserID;                    //审核人
   m_strCheckTime = pData->m_strCheckTime;                        //审核时间
   m_strCreateUserID= pData->m_strCreateUserID;         //创建人
   m_strCreateUserTime= pData->m_strCreateUserTime;       //创建时间
}

BOOL CDBP_BindInfoData::GetAllDBInfo( CADOConn *pADOConn )
{
   ASSERT(pADOConn);
   if (pADOConn == nullptr)
   {
      return FALSE;
   }
   if (!pADOConn->adoEOF())
   {
      m_nID = pADOConn->GetValueInt(DBP_BindInfo_Key_ID);
      m_strName =  pADOConn->GetValueString(DBP_BindInfo_Key_cName);                                  //名称
      m_oleBandStartTime = pADOConn->GetValueString(DBP_BandInfo_Key_cBindStartTime);                //波段开始时间
      m_oleDesignEndTime  =pADOConn->GetValueString(DBP_BindInfo_Key_cDesignEndTime);                //设计完成时间
      m_olePatternEndTime  = pADOConn->GetValueString(DBP_BindInfo_Key_cPatternEndTime);             //纸样完成时间
      m_oleReviewEndTime  = pADOConn->GetValueString(DBP_BindInfo_Key_cReviewEndTime);               //内审会完成时间
      m_oleBandEndTime  = pADOConn->GetValueString(DBP_BindInfo_Key_cBandEndTime);                   //波段结束时间
      m_strStylish  = pADOConn->GetValueString(DBP_BindInfo_Key_cStylish);                           //风格
      m_strColor  = pADOConn->GetValueString(DBP_BindInfo_Key_cColor);                               //色系
      m_bCheckState = pADOConn->GetValueInt(DBP_BindInfo_Key_bCheckState);                          //审核标识
      m_strRemark = pADOConn->GetValueString(DBP_BindInfo_Key_cRemark);                              //备注
      m_nAssociatedProgrammingID = pADOConn->GetValueInt64(DBP_BindInfo_Key_nAssociatedProgrammingID);//所属商品规划的ID
      m_strSeriaNum.Format(FORMAT_STRING,pADOConn->GetValueString(DBP_BindInfo_Key_cSeriaNum));                              //序号
      m_strDeliveryStartTime = pADOConn->GetValueString(DBP_BindInfo_Key_cDeliveryStartTime);        //货期起始时间
      m_strDeliveryEndTime = pADOConn->GetValueString(DBP_BindInfo_Key_cDeliveryEndTime);            //货期结束时间
      m_strShelvesTime = pADOConn->GetValueString(DBP_BindInfo_Key_cShelvesTime);                    //上货日
      m_strCheckUserID = pADOConn->GetValueString(DBP_BindInfo_Key_cCheckUserID);                    //审核人
      m_strCheckTime = pADOConn->GetValueString(DBP_BindInfo_Key_cCheckTime);                        //审核时间
      m_strCreateUserID = pADOConn->GetValueString(DBP_BindInfo_Key_cCreateUserID);;         //创建人
      m_strCreateUserTime = pADOConn->GetValueString(DBP_BindInfo_Key_cCreateUserTime);;       //创建时间
      return TRUE;
   }

   return FALSE;
}

BOOL CDBP_BindInfoData::InsertAllDBInfo( CADOConn *pADOConn )
{
    CString strSql = _T("");
    CString strSQL = _T("");
    CString strSeriaNum = _T("");
    strSQL.Format(_T("select ISNULL(MAX(CAST(%s as int)),0) as %s from %s"),DBP_BindInfo_Key_cSeriaNum,DBP_BindInfo_Key_cSeriaNum,DB_TABLE_BANDINFO);
    pADOConn->GetRecordSet(strSQL);
    while(!pADOConn->adoEOF())
    {
      m_strSeriaNum = pADOConn->GetValueString(DBP_BindInfo_Key_cSeriaNum);
       pADOConn->MoveNext();
    }

    if (m_strSeriaNum.IsEmpty())
    {

       m_strSeriaNum = _T("0");
    }
    else
    {
       __int64 nSeriaNum = _ttoi64(m_strSeriaNum);
       nSeriaNum++;
       m_strSeriaNum.Format(_T("%ld"),nSeriaNum);
    }

   CString strSQLKey;
   strSQLKey.Format(_T("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s")
      ,DBP_BindInfo_Key_cName                   ,DBP_BandInfo_Key_cBindStartTime          ,DBP_BindInfo_Key_cDesignEndTime    ,DBP_BindInfo_Key_cPatternEndTime        ,DBP_BindInfo_Key_cReviewEndTime 
      ,DBP_BindInfo_Key_cBandEndTime            ,DBP_BindInfo_Key_cStylish                ,DBP_BindInfo_Key_cColor            ,DBP_BindInfo_Key_bCheckState            ,DBP_BindInfo_Key_cRemark 
      ,DBP_BindInfo_Key_nAssociatedProgrammingID,DBP_BindInfo_Key_cSeriaNum               ,DBP_BindInfo_Key_cDeliveryStartTime,DBP_BindInfo_Key_cDeliveryEndTime       ,DBP_BindInfo_Key_cShelvesTime  
       ,DBP_BindInfo_Key_cCheckUserID            ,DBP_BindInfo_Key_cCheckTime              ,DBP_BindInfo_Key_cCreateUserTime   ,DBP_BindInfo_Key_cCreateUserID);

   CString strSQLValue;
   strSQLValue.Format(_T("'%s','%s','%s','%s','%s','%s','%s','%s',%d,'%s',%lld ,'%s','%s','%s','%s','%s','%s',%s,'%s'"),
      m_strName                                ,m_oleBandStartTime                       ,m_oleDesignEndTime                 ,m_olePatternEndTime                     ,m_oleReviewEndTime,
      m_oleBandEndTime                         ,m_strStylish                             ,m_strColor                         ,m_bCheckState                           ,m_strRemark,    
      m_nAssociatedProgrammingID               ,m_strSeriaNum                            ,m_strDeliveryStartTime             ,m_strDeliveryEndTime                    ,m_strShelvesTime,
      m_strCheckUserID                         ,m_strCheckTime                           ,DBS_GETDATESTR                ,m_strCreateUserID);

   strSql.Format(_T("insert into %s(%s)\
                    values(%s)"),DB_TABLE_BANDINFO,strSQLKey,strSQLValue);



   if (pADOConn != NULL)
   {
      BOOL bExecute = pADOConn->ExecuteSQL(strSql);
      if (bExecute)
      {
         return TRUE;
      }

      return FALSE;
   }
   return FALSE;
}

BOOL CDBP_BindInfoData::UpdateAllDBInfoByID( CADOConn *pADOConn )
{
   CString strSQL = _T("");
   strSQL.Format(_T("Update %s set %s = '%s',%s = '%s',%s = '%s',%s = '%s',\
                    %s = '%s',%s = '%s',%s = '%s',%s = '%s',%s =%d\
                    ,%s = '%s',%s = %lld,%s = '%s',%s = '%s',%s = '%s',\
                    %s = '%s',%s = '%s',%s = '%s' where %s=%d"),DB_TABLE_BANDINFO
                     ,DBP_BindInfo_Key_cName,m_strName,DBP_BandInfo_Key_cBindStartTime,m_oleBandStartTime,DBP_BindInfo_Key_cDesignEndTime,m_oleDesignEndTime,DBP_BindInfo_Key_cPatternEndTime,m_olePatternEndTime,DBP_BindInfo_Key_cReviewEndTime,m_oleReviewEndTime
                     ,DBP_BindInfo_Key_cBandEndTime,m_oleBandEndTime,DBP_BindInfo_Key_cStylish,m_strStylish,DBP_BindInfo_Key_cColor,m_strColor,DBP_BindInfo_Key_bCheckState,m_bCheckState,DBP_BindInfo_Key_cRemark,m_strRemark
                     ,DBP_BindInfo_Key_nAssociatedProgrammingID,m_nAssociatedProgrammingID,DBP_BindInfo_Key_cSeriaNum,m_strSeriaNum,DBP_BindInfo_Key_cDeliveryStartTime,m_strDeliveryStartTime,DBP_BindInfo_Key_cDeliveryEndTime,m_strDeliveryEndTime,DBP_BindInfo_Key_cShelvesTime,m_strShelvesTime
                     ,DBP_BindInfo_Key_cCheckUserID,m_strCheckUserID,DBP_BindInfo_Key_cCheckTime,m_strCheckTime,DBP_BindInfo_Key_ID,m_nID);
   if (pADOConn != NULL)
   {
      BOOL bExecute = pADOConn->ExecuteSQL(strSQL);
      if (bExecute)
      {
         return TRUE;
      }

      return FALSE;
   }
   return FALSE;

}

BOOL CDBP_BindInfoData::DelAllDBInfoByID( CADOConn *pADOConn)
{
    CString strSQL = _T("");
    strSQL.Format(_T("delete from %s where %s = %d"),DB_TABLE_BANDINFO,DBP_BindInfo_Key_ID,m_nID);
    if (pADOConn != NULL)
    {
       BOOL bExecute = pADOConn->ExecuteSQL(strSQL);
       if (bExecute)
       {
          return TRUE;
       }

       return FALSE;
    }
    return FALSE;
}

BOOL CDBP_BindInfoData::GetAllDBInfoByID( CADOConn *pADOConn )
{
   CString strSQL = _T("");
   strSQL.Format(_T("select *from %s where %s = %d"),DB_TABLE_BANDINFO,DBP_BindInfo_Key_ID,m_nID);
   if (pADOConn != NULL)
   {
      BOOL bExecute = pADOConn->GetRecordSet(strSQL);
      if (bExecute)
      {
         if(GetAllDBInfo(pADOConn))
         {
            return TRUE;
         }
      }

      return FALSE;
   }
   return FALSE;
}

BOOL CDBP_BindInfoData::UpdateCheckInfoByID( CADOConn *pADOConn )
{
   CString strSQL = _T("");
   strSQL.Format(_T("Update %s set %s = %d ,%s = '%s',%s = '%s' where %s = %d"),DB_TABLE_BANDINFO,DBP_BindInfo_Key_bCheckState,m_bCheckState,DBP_BindInfo_Key_cCheckUserID,m_strCheckUserID,DBP_BindInfo_Key_cCheckTime,m_strCheckTime,DBP_BindInfo_Key_ID,m_nID);
   if (pADOConn != NULL)
   {
      BOOL bExecute = pADOConn->ExecuteSQL(strSQL);
      if (bExecute)
      {
         return TRUE;
      }

      return FALSE;
   }
   return FALSE;
}

void CDBP_BindInfoList::Copy( CDBP_BindInfoList *pList )
{
   if (pList != NULL)
   {
      for (int nIndex = 0;nIndex < pList->GetCount();nIndex++)
      {
         CDBP_BindInfoData *pPlanning =(CDBP_BindInfoData *)pList->GetAt(pList->FindIndex(nIndex));
         if (pPlanning != NULL)
         {
            AddItem(pPlanning);
         }
      }
   }
}

void CDBP_BindInfoList::AddItem( CDBP_BindInfoData *pItem )
{
   ASSERT(pItem != NULL);
   CDBP_BindInfoData *pPlanning = new CDBP_BindInfoData;
   pPlanning->Copy(pItem);
   AddTail(pPlanning);
}

void CDBP_BindInfoList::DeleteItemByIndex( int nIndex )
{
   if (nIndex != NULL)
   {
      CDBP_BindInfoData *pPlanning =(CDBP_BindInfoData *)GetAt(FindIndex(nIndex));
      if (pPlanning != NULL)
      {
         RemoveAt(FindIndex(nIndex));
      }

   }
}

CDBP_BindInfoList::CDBP_BindInfoList( void )
{

}

CDBP_BindInfoList::~CDBP_BindInfoList( void )
{

}

#ifdef USING_GRIDCTRL_MARK
void CDBP_BindInfoList::GetAllDBInfoByProgrammingID( CADOConn *pADO,CString  strProgrammingID,MAP_GridCtrl_AllData &mapALLData )
{
   CString strSQL = _T("");
   if (pADO == NULL)
   {
      return;
   }
   if (strProgrammingID.IsEmpty())
   {
      strSQL.Format(_T("select * from %s where %s=0"),DB_TABLE_BANDINFO,DBP_BindInfo_Key_nAssociatedProgrammingID);
   } 
   else
   {
      strSQL.Format(_T("select *from %s where %s = '%s'"),DB_TABLE_BANDINFO,DBP_BindInfo_Key_nAssociatedProgrammingID,strProgrammingID);
   }
   pADO->GetRecordSet(strSQL);

   int nRow = 0;
   while(!pADO->adoEOF())
   {
      MAP_GridCtrl_RowData map_row_data;
      CDBP_BindInfoData DBPlanning;
      DBPlanning.GetAllDBInfo(pADO);
      //insertRowdata
      InsertRowData(DBP_BindInfo_Key_ID                       	              ,map_row_data,CB_enum_FieldData_Int,CB_enum_FieldCtrl_Text,FORMAT_INT	,DBPlanning.m_nID);
      InsertRowData(DBP_BindInfo_Key_cSeriaNum                               ,map_row_data,FORMAT_STRING,DBPlanning.m_strSeriaNum                );
      InsertRowData(DBP_BindInfo_Key_cName                                   ,map_row_data,FORMAT_STRING,DBPlanning.m_strName                    );
      InsertRowData(DBP_BandInfo_Key_cBindStartTime                          ,map_row_data,FORMAT_STRING,DBPlanning.m_oleBandStartTime           );
      InsertRowData(DBP_BindInfo_Key_cDesignEndTime                          ,map_row_data,FORMAT_STRING,DBPlanning.m_oleDesignEndTime           );
      InsertRowData(DBP_BindInfo_Key_cPatternEndTime                         ,map_row_data,FORMAT_STRING,DBPlanning.m_olePatternEndTime          );
      InsertRowData(DBP_BindInfo_Key_cReviewEndTime                          ,map_row_data,FORMAT_STRING,DBPlanning.m_oleReviewEndTime           );
      InsertRowData(DBP_BindInfo_Key_cBandEndTime                            ,map_row_data,FORMAT_STRING,DBPlanning.m_oleBandEndTime             );
      InsertRowData(DBP_BindInfo_Key_cDeliveryStartTime                      ,map_row_data,FORMAT_STRING,DBPlanning.m_strDeliveryStartTime       );
      InsertRowData(DBP_BindInfo_Key_cDeliveryEndTime                        ,map_row_data,FORMAT_STRING,DBPlanning.m_strDeliveryEndTime         );
      InsertRowData(DBP_BindInfo_Key_cShelvesTime                            ,map_row_data,FORMAT_STRING,DBPlanning.m_strShelvesTime             );
      InsertRowData(DBP_BindInfo_Key_cStylish                                ,map_row_data,FORMAT_STRING,DBPlanning.m_strStylish                 );
      InsertRowData(DBP_BindInfo_Key_cColor                                  ,map_row_data,FORMAT_STRING,DBPlanning.m_strColor                   );
      InsertRowData(DBP_BindInfo_Key_cCreateUserID                           ,map_row_data,FORMAT_STRING,DBPlanning.m_strCreateUserID            );
      InsertRowData(DBP_BindInfo_Key_cCreateUserTime                         ,map_row_data,FORMAT_STRING,DBPlanning.m_strCreateUserTime          );
      InsertRowData(DBP_BindInfo_Key_bCheckState                             ,map_row_data,FORMAT_INT,DBPlanning.m_bCheckState              );
      InsertRowData(DBP_BindInfo_Key_cCheckUserID                            ,map_row_data,FORMAT_STRING,DBPlanning.m_strCheckUserID             );
      InsertRowData(DBP_BindInfo_Key_cCheckTime                              ,map_row_data,FORMAT_STRING,DBPlanning.m_strCheckTime               );
      InsertRowData(DBP_BindInfo_Key_cRemark                                 ,map_row_data,FORMAT_STRING,DBPlanning.m_strRemark                  );
      InsertRowData(DBP_BindInfo_Key_nAssociatedProgrammingID                ,map_row_data,FORMAT_INT,DBPlanning.m_nAssociatedProgrammingID );

      mapALLData.insert(make_pair(nRow++,map_row_data));

      AddItem(&DBPlanning);
      pADO->MoveNext();
   }
}

BOOL CDBP_BindInfoList::InsertAllDBtoDB( CADOConn *pADO,__int64 nProgrammingID )
{
   ASSERT(pADO != nullptr);
   if (pADO == nullptr)
   {
       return FALSE;
   }
   for (int nIndex = 0;nIndex < GetCount();nIndex++)
   {
      CDBP_BindInfoData *DBBindInfo = (CDBP_BindInfoData *)GetAt(FindIndex(nIndex));
      if (DBBindInfo != nullptr)
      {
         DBBindInfo->m_nAssociatedProgrammingID = nProgrammingID;
         DBBindInfo->UpdateAllDBInfoByID(pADO);
      }
   }
   return TRUE;
}

#endif // USING_GRIDCTRL_MARK
