#include "StdAfx.h"
#include "DBProductProcess_V.h"
#include "DBKeyDef_V.h"

///////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CDBProductProcess_VData,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBProductProcess_VList,  CDataListMid, 1)

std::shared_ptr<CDBProductProcess_VList> CDBProductProcess_VList::sm_inst;

CDBProductProcess_VData::CDBProductProcess_VData()
{
   ResetData(); 
} 

CDBProductProcess_VData::~CDBProductProcess_VData()
{
}

void CDBProductProcess_VData::ResetData()
{
   m_ProductSPData.ResetData();
   m_ProcessRecordsData.ResetData();

   m_strAssignUserID = _T("");
   m_nPersonType     = 0;
}

void CDBProductProcess_VData:: Copy(CDBProductProcess_VData *pData)
{
   ASSERT(pData != NULL);
   CDataMid::Copy(pData);

   m_ProductSPData.Copy(&(pData->m_ProductSPData));
   m_ProcessRecordsData.Copy(&(pData->m_ProcessRecordsData));

   m_strAssignUserID  =  pData->m_strAssignUserID;
   m_nPersonType      =  pData->m_nPersonType    ;

}

BOOL CDBProductProcess_VData::GetAllDBInfo(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);

   BOOL bRet = FALSE;
   if (NULL != pADOConn)
   {
      m_ProductSPData.m_nID                          = pADOConn->GetValueInt64( DBV_ProductProcess_Key_ID                        );
      m_ProductSPData.m_strClassification            = pADOConn->GetValueString(DBV_ProductProcess_Key_cClassification           );
      m_ProductSPData.m_strCategory                  = pADOConn->GetValueString(DBV_ProductProcess_Key_cCategory                 );
      m_ProductSPData.m_strPieceNum                  = pADOConn->GetValueString(DBV_ProductProcess_Key_nPieceNum                 );
      m_ProductSPData.m_strColor                     = pADOConn->GetValueString(DBV_ProductProcess_Key_cColor                    );
      m_ProductSPData.m_strSize                      = pADOConn->GetValueString(DBV_ProductProcess_Key_cSize                     );
      m_ProductSPData.m_strFabric                    = pADOConn->GetValueString(DBV_ProductProcess_Key_cFabric                   );
      m_ProductSPData.m_strFashion                   = pADOConn->GetValueString(DBV_ProductProcess_Key_cFashion                  );
      m_ProductSPData.m_strContour                   = pADOConn->GetValueString(DBV_ProductProcess_Key_cContour                  );
      m_ProductSPData.m_fPrice_Ceiling               = pADOConn->GetValueDouble(DBV_ProductProcess_Key_fPrice_Ceiling            );
      m_ProductSPData.m_fPrice_Floor                 = pADOConn->GetValueDouble(DBV_ProductProcess_Key_fPrice_Floor              );
      m_ProductSPData.m_fPrice_Tag                   = pADOConn->GetValueDouble(DBV_ProductProcess_Key_fPrice_Tag                );
      m_ProductSPData.m_strRemark                    = pADOConn->GetValueString(DBV_ProductProcess_Key_cRemark                   );
      m_ProductSPData.m_strBand_Name                 = pADOConn->GetValueString(DBV_ProductProcess_Key_cBand_Name                );
      m_ProductSPData.m_strBand_BandStartTime        = pADOConn->GetValueString(DBV_ProductProcess_Key_cBand_BandStartTime       );
      m_ProductSPData.m_strBand_DesignEndTime        = pADOConn->GetValueString(DBV_ProductProcess_Key_cBand_DesignEndTime       );
      m_ProductSPData.m_strBand_PatternEndTime       = pADOConn->GetValueString(DBV_ProductProcess_Key_cBand_PatternEndTime      );
      m_ProductSPData.m_strBand_ReviewEndTime        = pADOConn->GetValueString(DBV_ProductProcess_Key_cBand_ReviewEndTime       );
      m_ProductSPData.m_strBand_BandEndTime          = pADOConn->GetValueString(DBV_ProductProcess_Key_cBand_BandEndTime         );
      m_ProductSPData.m_strBand_DeliveryStartTime    = pADOConn->GetValueString(DBV_ProductProcess_Key_cBand_DeliveryStartTime   );
      m_ProductSPData.m_strBand_DeliveryEndTime      = pADOConn->GetValueString(DBV_ProductProcess_Key_cBand_DeliveryEndTime     );
      m_ProductSPData.m_strBand_ShelvesTime          = pADOConn->GetValueString(DBV_ProductProcess_Key_cBand_ShelvesTime         );
      m_ProductSPData.m_strBand_Stylish              = pADOConn->GetValueString(DBV_ProductProcess_Key_cBand_Stylish             );
      m_ProductSPData.m_strBand_Color                = pADOConn->GetValueString(DBV_ProductProcess_Key_cBand_Color               );
      m_ProductSPData.m_strCreateUserID              = pADOConn->GetValueString(DBV_ProductProcess_Key_cCreateUserID             );
      m_ProductSPData.m_strCreateTime                = pADOConn->GetValueString(DBV_ProductProcess_Key_cCreateTime               );
      m_ProductSPData.m_nCreateFlag                  = pADOConn->GetValueInt   (DBV_ProductProcess_Key_nCreateFlag               );
      m_ProductSPData.m_strProgramming_Brand         = pADOConn->GetValueString(DBV_ProductProcess_Key_cProgramming_Brand        );
      m_ProductSPData.m_strProgramming_Years         = pADOConn->GetValueString(DBV_ProductProcess_Key_cProgramming_Years        );
      m_ProductSPData.m_strProgramming_Season        = pADOConn->GetValueString(DBV_ProductProcess_Key_cProgramming_Season       );
      m_ProductSPData.m_strProgramming_TradeFairTime = pADOConn->GetValueString(DBV_ProductProcess_Key_cProgramming_TradeFairTime);
      m_ProductSPData.m_strProgramming_Area          = pADOConn->GetValueString(DBV_ProductProcess_Key_cProgramming_Area         );
      m_ProductSPData.m_strPlanning_SubjectName      = pADOConn->GetValueString(DBV_ProductProcess_Key_cPlanning_SubjectName     );
      m_ProductSPData.m_strCheckUserID               = pADOConn->GetValueString(DBV_ProductProcess_Key_cCheckUserID              );
      m_ProductSPData.m_strCheckTime                 = pADOConn->GetValueString(DBV_ProductProcess_Key_cCheckTime                );
      m_ProductSPData.m_bCheckState                  = pADOConn->GetValueInt   (DBV_ProductProcess_Key_bCheckState               );
      m_strAssignUserID                              = pADOConn->GetValueString(DBV_ProductProcess_Key_cAssignUserID             );
      m_nPersonType                                  = pADOConn->GetValueInt   (DBV_ProductProcess_Key_nPersonType               );
      m_ProcessRecordsData.m_nID                     = pADOConn->GetValueInt64 (DBV_ProductProcess_Key_ProcessID                 );
      m_ProcessRecordsData.m_nAssociatedProductID    = pADOConn->GetValueInt64 (DBV_ProductProcess_Key_nAssociatedProductID      );
      m_ProcessRecordsData.m_strReceiveUserID        = pADOConn->GetValueString(DBV_ProductProcess_Key_cReceiveUserID            );
      m_ProcessRecordsData.m_strSponsorID            = pADOConn->GetValueString(DBV_ProductProcess_Key_cSponsorID                );
      m_ProcessRecordsData.m_nProcessType            = pADOConn->GetValueInt   (DBV_ProductProcess_Key_nProcessType              );
      m_ProcessRecordsData.m_strInitiateTime         = pADOConn->GetValueString(DBV_ProductProcess_Key_cInitiateTime             );
      m_ProcessRecordsData.m_strRealStartTime        = pADOConn->GetValueString(DBV_ProductProcess_Key_cRealStartTime            );
      m_ProcessRecordsData.m_strFinishTime           = pADOConn->GetValueString(DBV_ProductProcess_Key_cFinishTime               );
      m_ProcessRecordsData.m_nState                  = pADOConn->GetValueInt   (DBV_ProductProcess_Key_nState                    );
      m_ProcessRecordsData.m_bCheckState             = pADOConn->GetValueInt   (DBV_ProductProcess_Key_nCheckState               );


      bRet = TRUE;
   }

   return bRet;
}


void CDBProductProcess_VData::Trim()
{
   m_ProductSPData.Trim();
   m_ProcessRecordsData.Trim();
   m_strAssignUserID.Trim();
}

#ifdef USING_GRIDCTRL_MARK
MAP_GridCtrl_RowData CDBProductProcess_VData::CreateGridRowData(CADOConn * pADOConn)
{
   MAP_GridCtrl_RowData rowData;
   CDataMid::InsertRowData(DBV_ProductProcess_Key_ID                        ,pADOConn->GetValueString(DBV_ProductProcess_Key_ID                        ),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_cClassification           ,pADOConn->GetValueString(DBV_ProductProcess_Key_cClassification           ),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_cCategory                 ,pADOConn->GetValueString(DBV_ProductProcess_Key_cCategory                 ),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_nPieceNum                 ,pADOConn->GetValueString(DBV_ProductProcess_Key_nPieceNum                 ),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_cColor                    ,pADOConn->GetValueString(DBV_ProductProcess_Key_cColor                    ),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_cSize                     ,pADOConn->GetValueString(DBV_ProductProcess_Key_cSize                     ),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_cFabric                   ,pADOConn->GetValueString(DBV_ProductProcess_Key_cFabric                   ),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_cFashion                  ,pADOConn->GetValueString(DBV_ProductProcess_Key_cFashion                  ),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_cContour                  ,pADOConn->GetValueString(DBV_ProductProcess_Key_cContour                  ),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_fPrice_Ceiling            ,pADOConn->GetValueString(DBV_ProductProcess_Key_fPrice_Ceiling            ),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_fPrice_Floor              ,pADOConn->GetValueString(DBV_ProductProcess_Key_fPrice_Floor              ),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_fPrice_Tag                ,pADOConn->GetValueString(DBV_ProductProcess_Key_fPrice_Tag                ),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_cRemark                   ,pADOConn->GetValueString(DBV_ProductProcess_Key_cRemark                   ),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_cBand_Name                ,pADOConn->GetValueString(DBV_ProductProcess_Key_cBand_Name                ),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_cBand_BandStartTime       ,pADOConn->GetValueString(DBV_ProductProcess_Key_cBand_BandStartTime       ),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_cBand_DesignEndTime       ,pADOConn->GetValueString(DBV_ProductProcess_Key_cBand_DesignEndTime       ),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_cBand_PatternEndTime      ,pADOConn->GetValueString(DBV_ProductProcess_Key_cBand_PatternEndTime      ),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_cBand_ReviewEndTime       ,pADOConn->GetValueString(DBV_ProductProcess_Key_cBand_ReviewEndTime       ),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_cBand_BandEndTime         ,pADOConn->GetValueString(DBV_ProductProcess_Key_cBand_BandEndTime         ),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_cBand_DeliveryStartTime   ,pADOConn->GetValueString(DBV_ProductProcess_Key_cBand_DeliveryStartTime   ),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_cBand_DeliveryEndTime     ,pADOConn->GetValueString(DBV_ProductProcess_Key_cBand_DeliveryEndTime     ),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_cBand_ShelvesTime         ,pADOConn->GetValueString(DBV_ProductProcess_Key_cBand_ShelvesTime         ),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_cBand_Stylish             ,pADOConn->GetValueString(DBV_ProductProcess_Key_cBand_Stylish             ),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_cBand_Color               ,pADOConn->GetValueString(DBV_ProductProcess_Key_cBand_Color               ),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_cCreateUserID             ,pADOConn->GetValueString(DBV_ProductProcess_Key_cCreateUserID             ),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_cCreateTime               ,pADOConn->GetValueString(DBV_ProductProcess_Key_cCreateTime               ),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_nCreateFlag               ,pADOConn->GetValueString(DBV_ProductProcess_Key_nCreateFlag               ),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_cProgramming_Brand        ,pADOConn->GetValueString(DBV_ProductProcess_Key_cProgramming_Brand        ),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_cProgramming_Years        ,pADOConn->GetValueString(DBV_ProductProcess_Key_cProgramming_Years        ),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_cProgramming_Season       ,pADOConn->GetValueString(DBV_ProductProcess_Key_cProgramming_Season       ),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_cProgramming_TradeFairTime,pADOConn->GetValueString(DBV_ProductProcess_Key_cProgramming_TradeFairTime),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_cProgramming_Area         ,pADOConn->GetValueString(DBV_ProductProcess_Key_cProgramming_Area         ),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_cPlanning_SubjectName     ,pADOConn->GetValueString(DBV_ProductProcess_Key_cPlanning_SubjectName     ),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_cCheckUserID              ,pADOConn->GetValueString(DBV_ProductProcess_Key_cCheckUserID              ),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_cCheckTime                ,pADOConn->GetValueString(DBV_ProductProcess_Key_cCheckTime                ),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_bCheckState               ,pADOConn->GetValueString(DBV_ProductProcess_Key_bCheckState               ),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_cAssignUserID             ,pADOConn->GetValueString(DBV_ProductProcess_Key_cAssignUserID             ),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_nPersonType               ,pADOConn->GetValueString(DBV_ProductProcess_Key_nPersonType               ),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_ProcessID                 ,pADOConn->GetValueString(DBV_ProductProcess_Key_ProcessID                 ),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_nAssociatedProductID      ,pADOConn->GetValueString(DBV_ProductProcess_Key_nAssociatedProductID      ),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_cReceiveUserID            ,pADOConn->GetValueString(DBV_ProductProcess_Key_cReceiveUserID            ),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_cSponsorID                ,pADOConn->GetValueString(DBV_ProductProcess_Key_cSponsorID                ),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_nProcessType              ,pADOConn->GetValueString(DBV_ProductProcess_Key_nProcessType              ),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_cInitiateTime             ,pADOConn->GetValueString(DBV_ProductProcess_Key_cInitiateTime             ),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_cRealStartTime            ,pADOConn->GetValueString(DBV_ProductProcess_Key_cRealStartTime            ),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_cFinishTime               ,pADOConn->GetValueString(DBV_ProductProcess_Key_cFinishTime               ),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_nState                    ,pADOConn->GetValueString(DBV_ProductProcess_Key_nState                    ),rowData);
   CDataMid::InsertRowData(DBV_ProductProcess_Key_nCheckState               ,pADOConn->GetValueString(DBV_ProductProcess_Key_nCheckState               ),rowData);

   return rowData;
}
#endif // USING_GRIDCTRL_MARK

CDBProductProcess_VList::CDBProductProcess_VList()
{

}
CDBProductProcess_VList::~CDBProductProcess_VList()
{

}

CDBProductProcess_VData* CDBProductProcess_VList::GetItem(int nIndex)
{
   if (nIndex<0||nIndex>=GetCount())
      return NULL;
   return (CDBProductProcess_VData*)GetAt(FindIndex(nIndex));
}

void CDBProductProcess_VList::AddItem(CDBProductProcess_VData* pItem)
{
   CDBProductProcess_VData*pData=new CDBProductProcess_VData;
   pData->Copy(pItem);
   AddTail(pData);
}

void CDBProductProcess_VList::DeleteItem(int nIndex)
{
   if (nIndex<0||nIndex>GetCount())
      return;
   CDBProductProcess_VData *pObject=(CDBProductProcess_VData*)GetItem(nIndex);
   delete pObject;
   pObject=NULL;
   RemoveAt(FindIndex(nIndex));
}

CDBProductProcess_VList * CDBProductProcess_VList::Instance()
{
   if(sm_inst.get() == 0)
      sm_inst = shared_ptr<CDBProductProcess_VList>(new CDBProductProcess_VList);

   return sm_inst.get();
}
