
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
   m_strName                   =_T("")       ;//����
   m_oleBandStartTime          =_T("")       ;//���ο�ʼʱ��
   m_oleDesignEndTime          =_T("")       ;//������ʱ��
   m_olePatternEndTime         =_T("")       ;//ֽ�����ʱ��
   m_oleReviewEndTime          =_T("")       ;//��������ʱ��
   m_oleBandEndTime            =_T("")       ;//���ν���ʱ��
   m_strStylish                =_T("")       ;//���
   m_strColor                  =_T("")       ;//ɫϵ
   m_bCheckState               =FALSE        ;//��˱�ʶ
   m_strRemark                 =_T("")       ;//��ע
   m_nAssociatedProgrammingID  =0            ;//������Ʒ�滮��I
   m_strSeriaNum               =_T("")       ;//���
   m_strDeliveryStartTime      =_T("")       ;//������ʼʱ��
   m_strDeliveryEndTime        =_T("")       ;//���ڽ���ʱ��
   m_strShelvesTime            =_T("")       ;//�ϻ���
   m_strCheckUserID            =_T("")       ;//�����
   m_strCheckTime              =_T("")       ;//���ʱ��
   m_strCreateUserID           =_T("")       ;
   m_strCreateUserTime         =_T("");
   m_nProgrammingID            =0           ;// 
   m_strBrand                  =_T("")      ;//Ʒ��
   m_nYears                    =0           ;//���
   m_strSeason                 =_T("")      ;//����
   m_strTradeFairTime          =_T("")      ;//������
   m_strArea                   =_T("")      ;//����
   m_nAssociatedPlanningID     = 0          ;//����������ID
   m_strProgrammingCreateUserID=_T("")      ;//������
   


   SetDataType(DAT_BANKPROGRAMMING);
}

void CDBViewBandProgrammingInfoData::Copy( CDBViewBandProgrammingInfoData * pData )
{
   ASSERT(pData != NULL);
   CDataMid::Copy(pData);
   m_nID                       =pData->m_nID                     ;//ID
   m_strName                   =pData->m_strName                 ;//����
   m_oleBandStartTime          =pData->m_oleBandStartTime        ;//���ο�ʼʱ��
   m_oleDesignEndTime          =pData->m_oleDesignEndTime        ;//������ʱ��
   m_olePatternEndTime         =pData->m_olePatternEndTime       ;//ֽ�����ʱ��
   m_oleReviewEndTime          =pData->m_oleReviewEndTime        ;//��������ʱ��
   m_oleBandEndTime            =pData->m_oleBandEndTime          ;//���ν���ʱ��
   m_strStylish                =pData->m_strStylish              ;//���
   m_strColor                  =pData->m_strColor                ;//ɫϵ
   m_bCheckState               =pData->m_bCheckState             ;//��˱�ʶ
   m_strRemark                 =pData->m_strRemark               ;//��ע
   m_nAssociatedProgrammingID  =pData->m_nAssociatedProgrammingID;//������Ʒ�滮��
   m_strSeriaNum               =pData->m_strSeriaNum             ;//���
   m_strDeliveryStartTime      =pData->m_strDeliveryStartTime    ;//������ʼʱ��
   m_strDeliveryEndTime        =pData->m_strDeliveryEndTime      ;//���ڽ���ʱ��
   m_strShelvesTime            =pData->m_strShelvesTime          ;//�ϻ���
   m_strCheckUserID            =pData->m_strCheckUserID          ;//�����
   m_strCheckTime              =pData->m_strCheckTime            ;//���ʱ��
   m_strCreateUserID           =pData->m_strCreateUserID         ;
   m_strCreateUserTime         =pData->m_strCreateUserTime       ;
   m_nProgrammingID            =pData->m_nProgrammingID          ;// ProgrammingID
   m_strBrand                  =pData->m_strBrand                ;//Ʒ��
   m_nYears                    =pData->m_nYears                  ;//���
   m_strSeason                 =pData->m_strSeason               ;//����
   m_strTradeFairTime          =pData->m_strTradeFairTime        ;//������
   m_strArea                   =pData->m_strArea                 ;//����
   m_nAssociatedPlanningID     =pData->m_nAssociatedPlanningID   ;//����������ID
   m_strProgrammingCreateUserID=pData->m_strProgrammingCreateUserID         ;//������



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
