#include "StdAfx.h"
#include "DBP_Planning.h"

IMPLEMENT_SERIAL(CDBP_PlanningData,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBP_PlanningList,  CDataListMid, 1)

   CDBP_PlanningData::CDBP_PlanningData(void)
{
   ResetData();
}


CDBP_PlanningData::~CDBP_PlanningData(void)
{
}

void CDBP_PlanningData::ResetData()
{
   m_nID             =0     ;         //ID
   m_nYears          =0     ;         //年度
   m_strSeason       =_T("");         //季节
   m_strSubjectName  =_T("");         //主题名
   m_strBrand        =_T("");         //品牌
   m_strRemark       =_T("");         //主题备注
   m_bCheckState     =FALSE ;         //审核标识
   m_strCreateUserID =_T("");         //创建人
   m_strCreateTime   =_T("");         //创建时间
   m_strLastAcTime   =_T("");         //最后操作时间
   m_strCheckUserID  =_T("");         //审核人
   m_strCheckTime    =_T("");         //审核时间

   SetDataType(DAT_PLANNING);
}

void CDBP_PlanningData::Copy( CDBP_PlanningData *pData )
{
   ASSERT(pData != NULL);
   CDataMid::Copy(pData);
   
   m_nID             =pData->m_nID             ;
   m_nYears          =pData->m_nYears          ;
   m_strSeason       =pData->m_strSeason       ;
   m_strSubjectName  =pData->m_strSubjectName  ;
   m_strBrand        =pData->m_strBrand        ;
   m_strRemark       =pData->m_strRemark       ;
   m_bCheckState     =pData->m_bCheckState     ;
   m_strCreateUserID =pData->m_strCreateUserID ;
   m_strCreateTime   =pData->m_strCreateTime   ;
   m_strLastAcTime   =pData->m_strLastAcTime   ;
   m_strCheckUserID  =pData->m_strCheckUserID  ;
   m_strCheckTime    =pData->m_strCheckTime    ;
                                        ;
}

BOOL CDBP_PlanningData::GetAllDBInfo( CADOConn *pADOConn)
{
   ASSERT(pADOConn);
   if (pADOConn == nullptr)
   {
      return FALSE;
   }
      m_nID             =pADOConn->GetValueInt64(DBP_Planning_Key_ID           );
      m_nYears          =pADOConn->GetValueInt(DBP_Planning_Key_nYears       );
      m_strSeason       =pADOConn->GetValueString(DBP_Planning_Key_cSeason      );
      m_strSubjectName  =pADOConn->GetValueString(DBP_Planning_Key_cSubjectName );
      m_strBrand        =pADOConn->GetValueString(DBP_Planning_Key_cBrand       );
      m_strRemark       =pADOConn->GetValueString(DBP_Planning_Key_cRemark      );
      m_bCheckState     =_ttoi(pADOConn->GetValueString(DBP_Planning_Key_bCheckState  ));
      m_strCreateUserID =pADOConn->GetValueString(DBP_Planning_Key_cCreateUserID);
      m_strCreateTime   =pADOConn->GetValueString(DBP_Planning_Key_cCreateTime  );
      m_strLastAcTime   =pADOConn->GetValueString(DBP_Planning_Key_cLastActTime );
      m_strCheckUserID  =pADOConn->GetValueString(DBP_Planning_Key_cCheckUserID );
      m_strCheckTime    =pADOConn->GetValueString(DBP_Planning_Key_cCheckTime   );
   
   return TRUE;
}

BOOL CDBP_PlanningData::GetAllDBInfoByID(CADOConn *pADOConn)
{
   CString strSQL = _T("");
   ASSERT(pADOConn != nullptr);
   if (pADOConn == nullptr)
   {
      return FALSE;
   }
   strSQL.Format(_T("select * from %s where %s = %ld"),DB_TABLE_PLANNING,DBP_Planning_Key_ID,m_nID);
   pADOConn->GetRecordSet(strSQL);
   if(!pADOConn->adoEOF())
   {
      m_nID             =pADOConn->GetValueInt64(DBP_Planning_Key_ID           );
      m_nYears          =pADOConn->GetValueInt(DBP_Planning_Key_nYears       );
      m_strSeason       =pADOConn->GetValueString(DBP_Planning_Key_cSeason      );
      m_strSubjectName  =pADOConn->GetValueString(DBP_Planning_Key_cSubjectName );
      m_strBrand        =pADOConn->GetValueString(DBP_Planning_Key_cBrand       );
      m_strRemark       =pADOConn->GetValueString(DBP_Planning_Key_cRemark      );
      m_bCheckState     =_ttoi(pADOConn->GetValueString(DBP_Planning_Key_bCheckState  ));
      m_strCreateUserID =pADOConn->GetValueString(DBP_Planning_Key_cCreateUserID);
      m_strCreateTime   =pADOConn->GetValueString(DBP_Planning_Key_cCreateTime  );
      m_strLastAcTime   =pADOConn->GetValueString(DBP_Planning_Key_cLastActTime );
      m_strCheckUserID  =pADOConn->GetValueString(DBP_Planning_Key_cCheckUserID );
      m_strCheckTime    =pADOConn->GetValueString(DBP_Planning_Key_cCheckTime   );

   }
   return TRUE;
}
BOOL CDBP_PlanningData::InsertAllDBInfo( CADOConn *pADOConn )
{
   CString strSqlValue = _T("");
   CString strSqlKey = _T("");
   CString strSQL = _T("");

   strSqlKey.Format(_T("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s"),DBP_Planning_Key_nYears 
      ,DBP_Planning_Key_cSeason ,DBP_Planning_Key_cSubjectName ,DBP_Planning_Key_cBrand ,DBP_Planning_Key_cRemark ,DBP_Planning_Key_bCheckState 
      ,DBP_Planning_Key_cCreateUserID,DBP_Planning_Key_cCreateTime ,DBP_Planning_Key_cLastActTime ,DBP_Planning_Key_cCheckUserID ,DBP_Planning_Key_cCheckTime);

   strSqlValue.Format(_T("%d,'%s','%s','%s','%s',%d,'%s',%s,%s,'%s','%s'"),
   m_nYears,m_strSeason,m_strSubjectName,m_strBrand,
   m_strRemark,m_bCheckState,m_strCreateUserID ,DBS_GETDATESTR,DBS_GETDATESTR,
   m_strCheckUserID  ,m_strCheckTime
   );

   strSQL.Format(_T("insert into %s(%s) values(%s)"),DB_TABLE_PLANNING,strSqlKey,strSqlValue);

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

BOOL CDBP_PlanningData::UpdateAllDBInfoByID( CADOConn *pADOConn )
{
   CString strSQL = _T("");
   strSQL.Format(_T("Update %s set %s = %d,%s = '%s',%s = '%s',%s = '%s',%s = '%s',\
                    %s = %d, %s = '%s',%s = '%s',%s = '%s',%s = '%s',%s = '%s' where %s=%ld"),DB_TABLE_PLANNING
                    ,DBP_Planning_Key_nYears        ,m_nYears          
                    ,DBP_Planning_Key_cSeason       ,m_strSeason       
                    ,DBP_Planning_Key_cSubjectName  ,m_strSubjectName  
                    ,DBP_Planning_Key_cBrand        ,m_strBrand        
                    ,DBP_Planning_Key_cRemark       ,m_strRemark       
                    ,DBP_Planning_Key_bCheckState   ,m_bCheckState     
                    ,DBP_Planning_Key_cCreateUserID ,m_strCreateUserID 
                    ,DBP_Planning_Key_cCreateTime   ,m_strCreateTime   
                    ,DBP_Planning_Key_cLastActTime  ,m_strLastAcTime   
                    ,DBP_Planning_Key_cCheckUserID  ,m_strCheckUserID  
                    ,DBP_Planning_Key_cCheckTime    ,m_strCheckTime
                    ,DBP_Planning_Key_ID            ,m_nID             
                    );

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

BOOL CDBP_PlanningData::DelAllDBInfoByID( CADOConn *pADOConn )
{
   CString strSQL = _T("");
   strSQL.Format(_T("delete from %s where %s = %lld"),DB_TABLE_PLANNING,DBP_Planning_Key_ID,m_nID);
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

BOOL CDBP_PlanningData::GetIDByCondition( CADOConn *pADOConn )
{
   ASSERT(pADOConn != nullptr);
   CString strSQL;
   strSQL.Format(_T("select ID from %s \
                    where %s = '%s' and %s = %d and %s = '%s' and %s = '%s'"),
                    DB_TABLE_PLANNING,
                    DBP_Planning_Key_cSubjectName,m_strSubjectName,
                    DBP_Planning_Key_nYears,m_nYears,
                    DBP_Planning_Key_cSeason,m_strSeason,
                    DBP_Planning_Key_cBrand,m_strBrand
                    );
   pADOConn->GetRecordSet(strSQL);

  if (!pADOConn->adoEOF())
  {
     m_nID = pADOConn->GetValueInt64(DBP_Planning_Key_ID);
     return TRUE;
  }
 return FALSE;
}

CDBP_PlanningList::CDBP_PlanningList( void )
{

}

CDBP_PlanningList::~CDBP_PlanningList( void )
{

}

void CDBP_PlanningList::Copy( CDBP_PlanningList *pList )
{
   if (pList != NULL)
   {
      for (int nIndex = 0;nIndex < pList->GetCount();nIndex++)
      {
         CDBP_PlanningData *pPlanning =(CDBP_PlanningData *)pList->GetAt(pList->FindIndex(nIndex));
         if (pPlanning != NULL)
         {
            AddItem(pPlanning);
         }
      }
   }
}

void CDBP_PlanningList::AddItem( CDBP_PlanningData *pItem )
{
   ASSERT(pItem != NULL);
   CDBP_PlanningData *pPlanning = new CDBP_PlanningData;
   pPlanning->Copy(pItem);
   AddTail(pPlanning);
}

void CDBP_PlanningList::DeleteItemByIndex( int nIndex )
{
   if (nIndex != NULL)
   {

         CDBP_PlanningData *pPlanning =(CDBP_PlanningData *)GetAt(FindIndex(nIndex));
         if (pPlanning != NULL)
         {
            RemoveAt(FindIndex(nIndex));
         }
        
   }
}

#ifdef USING_GRIDCTRL_MARK
void CDBP_PlanningList::GetAllDBInfoByCondition( CADOConn *pADO,CString strSQL,MAP_GridCtrl_AllData &mapALLData )
{
   if (pADO == NULL || strSQL.IsEmpty())
   {
      return;
   }

   pADO->GetRecordSet(strSQL);

   int nRow = 0;
   while(!pADO->adoEOF())
   {
      MAP_GridCtrl_RowData map_row_data;
      CDBP_PlanningData DBPlanning;
      DBPlanning.GetAllDBInfo(pADO);

      //ID
      S_GridCtrl_FieldData map_Field_ID;
      CString strID;
      strID.Format(FORMAT_INT,DBPlanning.m_nID);
      map_Field_ID.strValue = strID;
      
      map_row_data.insert(make_pair(DBP_Planning_Key_ID	,map_Field_ID));

      //Years
      S_GridCtrl_FieldData map_Field_Years;
      CString strYears;
      strYears.Format(FORMAT_INT,DBPlanning.m_nYears);
      map_Field_Years.strValue = strYears;
      map_row_data.insert(make_pair(DBP_Planning_Key_nYears	,map_Field_Years));

      //CheckState
      S_GridCtrl_FieldData map_Field_CheckState;
      CString strCheckState;
      strCheckState.Format(FORMAT_INT,DBPlanning.m_bCheckState);
      map_Field_CheckState.strValue = strCheckState;
      map_row_data.insert(make_pair(DBP_Planning_Key_bCheckState	,map_Field_CheckState));

      //Brand
      S_GridCtrl_FieldData map_Field_Brand;
      map_Field_Brand.strValue = DBPlanning.m_strBrand;
      map_row_data.insert(make_pair(DBP_Planning_Key_cBrand	,map_Field_Brand));

      //SubjectName
      S_GridCtrl_FieldData map_Field_SubjectName;
      map_Field_SubjectName.strValue = DBPlanning.m_strSubjectName;
      map_row_data.insert(make_pair(DBP_Planning_Key_cSubjectName	,map_Field_SubjectName));

      //Searson
      S_GridCtrl_FieldData map_Field_Searson;
      map_Field_Searson.strValue = DBPlanning.m_strSeason;
      map_row_data.insert(make_pair(DBP_Planning_Key_cSeason	,map_Field_Searson));

      //Remark
      S_GridCtrl_FieldData map_Field_Remark;
      map_Field_Remark.strValue = DBPlanning.m_strRemark;
      map_row_data.insert(make_pair(DBP_Planning_Key_cRemark	,map_Field_Remark));

      //CheckTime
      S_GridCtrl_FieldData map_Field_CheckTime;
      map_Field_CheckTime.strValue = DBPlanning.m_strCheckTime;
      map_row_data.insert(make_pair(DBP_Planning_Key_cCheckTime	,map_Field_CheckTime));

      //CheckUserID
      S_GridCtrl_FieldData map_Field_CheckUserID;
      map_Field_CheckUserID.strValue = DBPlanning.m_strCheckUserID;
      map_row_data.insert(make_pair(DBP_Planning_Key_cCheckUserID	,map_Field_CheckUserID));

      //CreateTime
      S_GridCtrl_FieldData map_Field_CreateTime;
      map_Field_CreateTime.strValue = DBPlanning.m_strCreateTime;
      map_row_data.insert(make_pair(DBP_Planning_Key_cCreateTime	,map_Field_CreateTime));

      //CreateUserID
      S_GridCtrl_FieldData map_Field_CreateUserID;
      map_Field_CreateUserID.strValue = DBPlanning.m_strCreateUserID;
      map_row_data.insert(make_pair(DBP_Planning_Key_cCreateUserID	,map_Field_CreateUserID));

      //LastAcTime
      S_GridCtrl_FieldData map_Field_LastAcTime;
      map_Field_LastAcTime.strValue = DBPlanning.m_strLastAcTime;
      map_row_data.insert(make_pair(DBP_Planning_Key_cLastActTime	,map_Field_LastAcTime));

      mapALLData.insert(make_pair(nRow++,map_row_data));

      AddItem(&DBPlanning);
      pADO->MoveNext();
   }

}

#endif
