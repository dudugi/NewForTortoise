
#include "StdAfx.h"
#include "DBGlobalSet.h"
#include "DBBandProgramming_V.h"

IMPLEMENT_SERIAL(CDBViewBandProgrammingInfoData,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBViewBandProgrammingInfoList,  CDataListMid, 1)

std::shared_ptr<CDBViewBandProgrammingInfoList> CDBViewBandProgrammingInfoList::sm_inst;

CDBViewBandProgrammingInfoData::CDBViewBandProgrammingInfoData( void )
{
   ResetData(); 
}

CDBViewBandProgrammingInfoData::~CDBViewBandProgrammingInfoData( void )
{

}

void CDBViewBandProgrammingInfoData::ResetData()
{
   m_nID                       =0            ;
   m_strName                   =_T("")       ;//名称
   m_oleBandStartTime          =_T("")       ;//波段开始时间
   m_oleDesignEndTime          =_T("")       ;//设计完成时间
   m_olePatternEndTime         =_T("")       ;//纸样完成时间
   m_oleReviewEndTime          =_T("")       ;//内审会完成时间
   m_oleBandEndTime            =_T("")       ;//波段结束时间
   m_strStylish                =_T("")       ;//风格
   m_strColor                  =_T("")       ;//色系
   m_bCheckState               =FALSE        ;//审核标识
   m_strRemark                 =_T("")       ;//备注
   m_nAssociatedProgrammingID  =0            ;//所属商品规划的I
   m_strSeriaNum               =_T("")       ;//序号
   m_strDeliveryStartTime      =_T("")       ;//货期起始时间
   m_strDeliveryEndTime        =_T("")       ;//货期结束时间
   m_strShelvesTime            =_T("")       ;//上货日
   m_strCheckUserID            =_T("")       ;//审核人
   m_strCheckTime              =_T("")       ;//审核时间
   m_strCreateUserID           =_T("")       ;
   m_strCreateUserTime         =_T("");
   m_nProgrammingID            =0           ;// 
   m_strBrand                  =_T("")      ;//品牌
   m_nYears                    =0           ;//年份
   m_strSeason                 =_T("")      ;//季节
   m_strTradeFairTime          =_T("")      ;//订货会
   m_strArea                   =_T("")      ;//区域
   m_nAssociatedPlanningID     = 0          ;//关联的主题ID
   m_strProgrammingCreateUserID=_T("")      ;//创建人
   


   SetDataType(DAT_BANKPROGRAMMING);
}

void CDBViewBandProgrammingInfoData::Copy( CDBViewBandProgrammingInfoData * pData )
{
   ASSERT(pData != NULL);
   CDataMid::Copy(pData);
   m_nID                       =pData->m_nID                     ;//ID
   m_strName                   =pData->m_strName                 ;//名称
   m_oleBandStartTime          =pData->m_oleBandStartTime        ;//波段开始时间
   m_oleDesignEndTime          =pData->m_oleDesignEndTime        ;//设计完成时间
   m_olePatternEndTime         =pData->m_olePatternEndTime       ;//纸样完成时间
   m_oleReviewEndTime          =pData->m_oleReviewEndTime        ;//内审会完成时间
   m_oleBandEndTime            =pData->m_oleBandEndTime          ;//波段结束时间
   m_strStylish                =pData->m_strStylish              ;//风格
   m_strColor                  =pData->m_strColor                ;//色系
   m_bCheckState               =pData->m_bCheckState             ;//审核标识
   m_strRemark                 =pData->m_strRemark               ;//备注
   m_nAssociatedProgrammingID  =pData->m_nAssociatedProgrammingID;//所属商品规划的
   m_strSeriaNum               =pData->m_strSeriaNum             ;//序号
   m_strDeliveryStartTime      =pData->m_strDeliveryStartTime    ;//货期起始时间
   m_strDeliveryEndTime        =pData->m_strDeliveryEndTime      ;//货期结束时间
   m_strShelvesTime            =pData->m_strShelvesTime          ;//上货日
   m_strCheckUserID            =pData->m_strCheckUserID          ;//审核人
   m_strCheckTime              =pData->m_strCheckTime            ;//审核时间
   m_strCreateUserID           =pData->m_strCreateUserID         ;
   m_strCreateUserTime         =pData->m_strCreateUserTime       ;
   m_nProgrammingID            =pData->m_nProgrammingID          ;// ProgrammingID
   m_strBrand                  =pData->m_strBrand                ;//品牌
   m_nYears                    =pData->m_nYears                  ;//年份
   m_strSeason                 =pData->m_strSeason               ;//季节
   m_strTradeFairTime          =pData->m_strTradeFairTime        ;//订货会
   m_strArea                   =pData->m_strArea                 ;//区域
   m_nAssociatedPlanningID     =pData->m_nAssociatedPlanningID   ;//关联的主题ID
   m_strProgrammingCreateUserID=pData->m_strProgrammingCreateUserID         ;//创建人



}

BOOL CDBViewBandProgrammingInfoData::GetAllDBInfo( CADOConn *pADOConn )
{
   ASSERT(pADOConn);
   if (pADOConn == nullptr)
   {
      return FALSE;
   }
   m_nID                       = pADOConn->GetValueInt64(DBV_BANDPROGRAMMING_Key_ID);
   m_strName                   =pADOConn->GetValueString(DBV_BANDPROGRAMMING_Key_cName);
   m_oleBandStartTime          =pADOConn->GetValueString(DBV_BANDPROGRAMMING_Key_cBindStartTime);
   m_oleDesignEndTime          =pADOConn->GetValueString(DBV_BANDPROGRAMMING_Key_cDesignEndTime);
   m_olePatternEndTime         =pADOConn->GetValueString(DBV_BANDPROGRAMMING_Key_cPatternEndTime);
   m_oleReviewEndTime          =pADOConn->GetValueString(DBV_BANDPROGRAMMING_Key_cReviewEndTime);
   m_oleBandEndTime            =pADOConn->GetValueString(DBV_BANDPROGRAMMING_Key_cBandEndTime);
   m_strStylish                =pADOConn->GetValueString(DBV_BANDPROGRAMMING_Key_cStylish);
   m_strColor                  =pADOConn->GetValueString(DBV_BANDPROGRAMMING_Key_cColor);
   m_bCheckState               =_ttoi(pADOConn->GetValueString(DBV_BANDPROGRAMMING_Key_bCheckState));
   m_strRemark                 =pADOConn->GetValueString(DBV_BANDPROGRAMMING_Key_cRemark);
   m_nAssociatedProgrammingID  = pADOConn->GetValueInt64(DBV_BANDPROGRAMMING_Key_nAssociatedProgrammingID);
   m_strSeriaNum               =pADOConn->GetValueString(DBV_BANDPROGRAMMING_Key_cSeriaNum);
   m_strDeliveryStartTime      =pADOConn->GetValueString(DBV_BANDPROGRAMMING_Key_cDeliveryStartTime);
   m_strDeliveryEndTime        =pADOConn->GetValueString(DBV_BANDPROGRAMMING_Key_cDeliveryEndTime);
   m_strShelvesTime            =pADOConn->GetValueString(DBV_BANDPROGRAMMING_Key_cShelvesTime);
   m_strCheckUserID            =pADOConn->GetValueString(DBV_BANDPROGRAMMING_Key_cCheckUserID);
   m_strCheckTime              =pADOConn->GetValueString(DBV_BANDPROGRAMMING_Key_cCheckTime);
   m_strCreateUserID           =pADOConn->GetValueString(DBV_BANDPROGRAMMING_Key_cCreateUserID);
   m_strCreateUserTime         =pADOConn->GetValueString(DBV_BANDPROGRAMMING_Key_cCreateUserTime);
   m_nProgrammingID            = pADOConn->GetValueInt64(DBV_BANDPROGRAMMING_Key_ProgrammingID);
   m_strBrand                  =pADOConn->GetValueString(DBV_BANDPROGRAMMING_Key_cBrand);
   m_nYears                    =   pADOConn->GetValueInt(DBV_BANDPROGRAMMING_Key_nYears);
   m_strSeason                 =pADOConn->GetValueString(DBV_BANDPROGRAMMING_Key_cSeason);
   m_strTradeFairTime          =pADOConn->GetValueString(DBV_BANDPROGRAMMING_Key_cTradeFairTime);
   m_strArea                   =pADOConn->GetValueString(DBV_BANDPROGRAMMING_Key_cArea);
   m_nAssociatedPlanningID     = pADOConn->GetValueInt64(DBV_BANDPROGRAMMING_Key_nAssociatedPlanningID);
   m_strProgrammingCreateUserID=pADOConn->GetValueString(DBV_BANDPROGRAMMING_Key_cProgrammingCreateUserID);

   return TRUE;
}


CDBViewBandProgrammingInfoList::CDBViewBandProgrammingInfoList()
{

}

CDBViewBandProgrammingInfoList::~CDBViewBandProgrammingInfoList()
{

}

void CDBViewBandProgrammingInfoList::Copy( CDBViewBandProgrammingInfoList *pList )
{
   if (pList != NULL)
   {
      for (int nIndex = 0;nIndex < pList->GetCount();nIndex++)
      {
         CDBViewBandProgrammingInfoData *pPlanning =(CDBViewBandProgrammingInfoData *)pList->GetAt(pList->FindIndex(nIndex));
         if (pPlanning != NULL)
         {
            AddItem(pPlanning);
         }
      }
   }
}

void CDBViewBandProgrammingInfoList::AddItem( CDBViewBandProgrammingInfoData *pItem )
{
   ASSERT(pItem != NULL);
   CDBViewBandProgrammingInfoData *pPlanning = new CDBViewBandProgrammingInfoData;
   pPlanning->Copy(pItem);
   AddTail(pPlanning);
}

void CDBViewBandProgrammingInfoList::DeleteItemByIndex( int nIndex )
{
   if (nIndex != NULL)
   {

      CDBViewBandProgrammingInfoData *pPlanning =(CDBViewBandProgrammingInfoData *)GetAt(FindIndex(nIndex));
      if (pPlanning != NULL)
      {
         RemoveAt(FindIndex(nIndex));
      }

   }
}

#ifdef USING_GRIDCTRL_MARK
void CDBViewBandProgrammingInfoList::GetAllDBInfoByCondition( CADOConn *pADO,CString strSQL,MAP_GridCtrl_AllData &mapALLData )
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
      CDBViewBandProgrammingInfoData DBPlanning;
      DBPlanning.GetAllDBInfo(pADO);
      InsertRowData(DBV_BANDPROGRAMMING_Key_ID				            ,map_row_data,CB_enum_FieldData_Int,CB_enum_FieldCtrl_Text,FORMAT_INT	,DBPlanning.m_nID);
      InsertRowData(DBV_BANDPROGRAMMING_Key_cSeriaNum                ,map_row_data,FORMAT_STRING,DBPlanning.m_strSeriaNum);
      InsertRowData(DBV_BANDPROGRAMMING_Key_cName                    ,map_row_data,FORMAT_STRING,DBPlanning.m_strName    );
      InsertRowData(DBV_BANDPROGRAMMING_Key_cBindStartTime           ,map_row_data,FORMAT_STRING,DBPlanning.m_oleBandStartTime);
      InsertRowData(DBV_BANDPROGRAMMING_Key_cDesignEndTime           ,map_row_data,FORMAT_STRING,DBPlanning.m_oleDesignEndTime);
      InsertRowData(DBV_BANDPROGRAMMING_Key_cPatternEndTime          ,map_row_data,FORMAT_STRING,DBPlanning.m_olePatternEndTime          );
      InsertRowData(DBV_BANDPROGRAMMING_Key_cReviewEndTime           ,map_row_data,FORMAT_STRING,DBPlanning.m_oleReviewEndTime           );
      InsertRowData(DBV_BANDPROGRAMMING_Key_cBandEndTime             ,map_row_data,FORMAT_STRING,DBPlanning.m_oleBandEndTime             );
      InsertRowData(DBV_BANDPROGRAMMING_Key_cDeliveryStartTime       ,map_row_data,FORMAT_STRING,DBPlanning.m_strDeliveryStartTime       );
      InsertRowData(DBV_BANDPROGRAMMING_Key_cDeliveryEndTime         ,map_row_data,FORMAT_STRING,DBPlanning.m_strDeliveryEndTime         );
      InsertRowData(DBV_BANDPROGRAMMING_Key_cShelvesTime             ,map_row_data,FORMAT_STRING,DBPlanning.m_strShelvesTime               );
      InsertRowData(DBV_BANDPROGRAMMING_Key_cStylish                 ,map_row_data,FORMAT_STRING,DBPlanning.m_strStylish                 );
      InsertRowData(DBV_BANDPROGRAMMING_Key_cColor                   ,map_row_data,FORMAT_STRING,DBPlanning.m_strColor                   );
      InsertRowData(DBV_BANDPROGRAMMING_Key_cCreateUserID            ,map_row_data,FORMAT_STRING,DBPlanning.m_strCreateUserID            );
      InsertRowData(DBV_BANDPROGRAMMING_Key_cCreateUserTime          ,map_row_data,FORMAT_STRING,DBPlanning.m_strCreateUserTime          );
      InsertRowData(DBV_BANDPROGRAMMING_Key_bCheckState              ,map_row_data,FORMAT_INT,DBPlanning.m_bCheckState              );
      InsertRowData(DBV_BANDPROGRAMMING_Key_cCheckUserID             ,map_row_data,FORMAT_STRING,DBPlanning.m_strCheckUserID             );
      InsertRowData(DBV_BANDPROGRAMMING_Key_cCheckTime               ,map_row_data,FORMAT_STRING,DBPlanning.m_strCheckTime               );
      InsertRowData(DBV_BANDPROGRAMMING_Key_cRemark                  ,map_row_data,FORMAT_STRING,DBPlanning.m_strRemark                  );
      InsertRowData(DBV_BANDPROGRAMMING_Key_nAssociatedProgrammingID ,map_row_data,FORMAT_INT,DBPlanning.m_nAssociatedProgrammingID );
      InsertRowData(DBV_BANDPROGRAMMING_Key_ProgrammingID            ,map_row_data,FORMAT_INT,DBPlanning.m_nProgrammingID            );
      InsertRowData(DBV_BANDPROGRAMMING_Key_cBrand                   ,map_row_data,FORMAT_STRING,DBPlanning.m_strBrand                   );
      InsertRowData(DBV_BANDPROGRAMMING_Key_nYears                   ,map_row_data,FORMAT_INT,DBPlanning.m_nYears                   );
      InsertRowData(DBV_BANDPROGRAMMING_Key_cSeason                  ,map_row_data,FORMAT_STRING,DBPlanning.m_strSeason                  );
      InsertRowData(DBV_BANDPROGRAMMING_Key_cTradeFairTime           ,map_row_data,FORMAT_STRING,DBPlanning.m_strTradeFairTime           );
      InsertRowData(DBV_BANDPROGRAMMING_Key_cArea                    ,map_row_data,FORMAT_STRING,DBPlanning.m_strArea                    );
      InsertRowData(DBV_BANDPROGRAMMING_Key_nAssociatedPlanningID    ,map_row_data,FORMAT_INT,DBPlanning.m_nAssociatedPlanningID    );
      InsertRowData(DBV_BANDPROGRAMMING_Key_cProgrammingCreateUserID ,map_row_data,FORMAT_STRING,DBPlanning.m_strProgrammingCreateUserID );
      mapALLData.insert(make_pair(nRow++,map_row_data));

      AddItem(&DBPlanning);
      pADO->MoveNext();
   }
}
#endif // USING_GRIDCTRL_MARK

CDBViewBandProgrammingInfoList * CDBViewBandProgrammingInfoList::Instance()
{
   if(sm_inst.get() == 0)
      sm_inst = shared_ptr<CDBViewBandProgrammingInfoList>(new CDBViewBandProgrammingInfoList);

   return sm_inst.get();
}
