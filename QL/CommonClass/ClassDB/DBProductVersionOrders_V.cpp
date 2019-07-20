#include "StdAfx.h"
#include "DBProductVersionOrders_V.h"
#include "DBKeyDef_V.h"

///////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CDBProductVersionOrders_VData,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBProductVersionOrders_VList,  CDataListMid, 1)

std::shared_ptr<CDBProductVersionOrders_VList> CDBProductVersionOrders_VList::sm_inst;

CDBProductVersionOrders_VData::CDBProductVersionOrders_VData()
{
   ResetData(); 
} 

CDBProductVersionOrders_VData::~CDBProductVersionOrders_VData()
{
}

void CDBProductVersionOrders_VData::ResetData()
{
   m_ProductSPData.ResetData();

   m_nVersionID      = 0;
   m_strVersion      = _T("");
   m_nRdRecordsID    = 0;
   m_strCate         = _T("");
   m_strCode         = _T("");
   m_strDate         = _T("");
   m_strMaker        = _T("");
   m_strInvSehao     = _T("");
   m_strInvPeise     = _T("");
   m_strInvKuanhao   = _T("");
   m_strInvUnitCost  = _T("");
   m_strLastPerson   = _T("");
   m_strLastTime     = _T("");
   m_strInvState2    = _T("");
   m_strTrueTime     = _T("");
   m_nOrdCreateFlag  = 0;
   m_strJianshu      = _T("");
   m_strInvMemo      = _T("");
   m_strInvState     = _T("");
   m_strZuoFeiMemo   = _T("");

}

void CDBProductVersionOrders_VData:: Copy(CDBProductVersionOrders_VData *pData)
{
   ASSERT(pData != NULL);
   CDataMid::Copy(pData);

   m_ProductSPData.Copy(&(pData->m_ProductSPData));

   m_nVersionID      = pData->m_nVersionID    ;
   m_strVersion      = pData->m_strVersion    ;
   m_nRdRecordsID    = pData->m_nRdRecordsID  ;
   m_strCate         = pData->m_strCate       ;
   m_strCode         = pData->m_strCode       ;
   m_strDate         = pData->m_strDate       ;
   m_strMaker        = pData->m_strMaker      ;
   m_strInvSehao     = pData->m_strInvSehao   ;
   m_strInvPeise     = pData->m_strInvPeise   ;
   m_strInvKuanhao   = pData->m_strInvKuanhao ;
   m_strInvUnitCost  = pData->m_strInvUnitCost;
   m_strLastPerson   = pData->m_strLastPerson ;
   m_strLastTime     = pData->m_strLastTime   ;
   m_strInvState2    = pData->m_strInvState2  ;
   m_strTrueTime     = pData->m_strTrueTime   ;
   m_nOrdCreateFlag  = pData->m_nOrdCreateFlag;
   m_strJianshu      = pData->m_strJianshu    ;
   m_strInvMemo      = pData->m_strInvMemo    ;
   m_strInvState     = pData->m_strInvState   ;
   m_strZuoFeiMemo   = pData->m_strZuoFeiMemo ;


}

BOOL CDBProductVersionOrders_VData::GetAllDBInfo(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);

   BOOL bRet = FALSE;
   if (NULL != pADOConn)
   {
      m_ProductSPData.m_nID                          = pADOConn->GetValueInt64(DBV_ProductVersionOrders_Key_ID                        );
      m_ProductSPData.m_strClassification            = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cClassification           );
      m_ProductSPData.m_strCategory                  = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cCategory                 );
      m_ProductSPData.m_strPieceNum                  = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_nPieceNum                 );
      m_ProductSPData.m_strColor                     = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cColor                    );
      m_ProductSPData.m_strSize                      = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cSize                     );
      m_ProductSPData.m_strFabric                    = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cFabric                   );
      m_ProductSPData.m_strFashion                   = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cFashion                  );
      m_ProductSPData.m_strContour                   = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cContour                  );
      m_ProductSPData.m_fPrice_Ceiling               = pADOConn->GetValueDouble(DBV_ProductVersionOrders_Key_fPrice_Ceiling            );
      m_ProductSPData.m_fPrice_Floor                 = pADOConn->GetValueDouble(DBV_ProductVersionOrders_Key_fPrice_Floor              );
      m_ProductSPData.m_fPrice_Tag                   = pADOConn->GetValueDouble(DBV_ProductVersionOrders_Key_fPrice_Tag                );
      m_ProductSPData.m_strRemark                    = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cRemark                   );
      m_ProductSPData.m_strBand_Name                 = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cBand_Name                );
      m_ProductSPData.m_strBand_BandStartTime        = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cBand_BandStartTime       );
      m_ProductSPData.m_strBand_DesignEndTime        = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cBand_DesignEndTime       );
      m_ProductSPData.m_strBand_PatternEndTime       = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cBand_PatternEndTime      );
      m_ProductSPData.m_strBand_ReviewEndTime        = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cBand_ReviewEndTime       );
      m_ProductSPData.m_strBand_BandEndTime          = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cBand_BandEndTime         );
      m_ProductSPData.m_strBand_DeliveryStartTime    = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cBand_DeliveryStartTime   );
      m_ProductSPData.m_strBand_DeliveryEndTime      = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cBand_DeliveryEndTime     );
      m_ProductSPData.m_strBand_ShelvesTime          = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cBand_ShelvesTime         );
      m_ProductSPData.m_strBand_Stylish              = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cBand_Stylish             );
      m_ProductSPData.m_strBand_Color                = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cBand_Color               );
      m_ProductSPData.m_strCreateUserID              = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cCreateUserID             );
      m_ProductSPData.m_strCreateTime                = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cCreateTime               );
      m_ProductSPData.m_nCreateFlag                  = pADOConn->GetValueInt   (DBV_ProductVersionOrders_Key_nCreateFlag               );
      m_ProductSPData.m_strProgramming_Brand         = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cProgramming_Brand        );
      m_ProductSPData.m_strProgramming_Years         = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cProgramming_Years        );
      m_ProductSPData.m_strProgramming_Season        = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cProgramming_Season       );
      m_ProductSPData.m_strProgramming_TradeFairTime = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cProgramming_TradeFairTime);
      m_ProductSPData.m_strProgramming_Area          = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cProgramming_Area         );
      m_ProductSPData.m_strPlanning_SubjectName      = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cPlanning_SubjectName     );
      m_ProductSPData.m_strCheckUserID               = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cCheckUserID              );
      m_ProductSPData.m_strCheckTime                 = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cCheckTime                );
      m_ProductSPData.m_bCheckState                  = pADOConn->GetValueInt   (DBV_ProductVersionOrders_Key_bCheckState               );
      m_ProductSPData.m_nCurProSort                  = pADOConn->GetValueInt   (DBV_ProductVersionOrders_Key_nCurProSort               );
      m_ProductSPData.m_bRevision                    = pADOConn->GetValueInt   (DBV_ProductVersionOrders_Key_bRevision                 );
      m_ProductSPData.m_strRevisionReason            = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cRevisionReason           );
      m_nVersionID                                   = pADOConn->GetValueInt64 (DBV_ProductVersionOrders_Key_VersionID                 );
      m_strVersion                                   = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cVersion                  );
      m_nRdRecordsID                                 = pADOConn->GetValueInt64 (DBV_ProductVersionOrders_Key_RdRecordsID               );
      m_strCate                                      = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cCate                     );
      m_strCode                                      = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cCode                     );
      m_strDate                                      = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_dDate                     );
      m_strMaker                                     = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cMaker                    );
      m_strInvSehao                                  = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cInvSehao                 );
      m_strInvPeise                                  = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cInvPeise                 );
      m_strInvKuanhao                                = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cInvKuanhao               );
      m_strInvUnitCost                               = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cInvUnitCost              );
      m_strLastPerson                                = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cLastPerson               );
      m_strLastTime                                  = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_dLastTime                 );
      m_strInvState2                                 = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cInvState2                );
      m_strTrueTime                                  = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_dTrueTime                 );
      m_nOrdCreateFlag                               = pADOConn->GetValueInt   (DBV_ProductVersionOrders_Key_iOrdCreateFlag            );
      m_strJianshu                                   = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cJianshu                  );
      m_strInvMemo                                   = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cInvMemo                  );
      m_strInvState                                  = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cInvState                 );
      m_strZuoFeiMemo                                = pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cZuoFeiMemo               );


      bRet = TRUE;
   }

   return bRet;
}

#ifdef USING_GRIDCTRL_MARK
MAP_GridCtrl_RowData CDBProductVersionOrders_VData::CreateGridRowData(CADOConn * pADOConn)
{
   ASSERT(NULL != pADOConn);
   MAP_GridCtrl_RowData map_row_data;

   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_ID                        ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_ID                        ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_cClassification           ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cClassification           ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_cCategory                 ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cCategory                 ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_nPieceNum                 ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_nPieceNum                 ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_cColor                    ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cColor                    ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_cSize                     ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cSize                     ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_cFabric                   ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cFabric                   ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_cFashion                  ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cFashion                  ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_cContour                  ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cContour                  ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_fPrice_Ceiling            ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_fPrice_Ceiling            ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_fPrice_Floor              ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_fPrice_Floor              ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_fPrice_Tag                ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_fPrice_Tag                ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_cRemark                   ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cRemark                   ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_cBand_Name                ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cBand_Name                ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_cBand_BandStartTime       ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cBand_BandStartTime       ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_cBand_DesignEndTime       ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cBand_DesignEndTime       ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_cBand_PatternEndTime      ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cBand_PatternEndTime      ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_cBand_ReviewEndTime       ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cBand_ReviewEndTime       ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_cBand_BandEndTime         ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cBand_BandEndTime         ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_cBand_DeliveryStartTime   ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cBand_DeliveryStartTime   ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_cBand_DeliveryEndTime     ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cBand_DeliveryEndTime     ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_cBand_ShelvesTime         ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cBand_ShelvesTime         ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_cBand_Stylish             ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cBand_Stylish             ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_cBand_Color               ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cBand_Color               ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_cCreateUserID             ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cCreateUserID             ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_cCreateTime               ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cCreateTime               ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_nCreateFlag               ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_nCreateFlag               ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_cProgramming_Brand        ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cProgramming_Brand        ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_cProgramming_Years        ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cProgramming_Years        ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_cProgramming_Season       ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cProgramming_Season       ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_cProgramming_TradeFairTime,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cProgramming_TradeFairTime),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_cProgramming_Area         ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cProgramming_Area         ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_cPlanning_SubjectName     ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cPlanning_SubjectName     ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_cCheckUserID              ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cCheckUserID              ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_cCheckTime                ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cCheckTime                ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_bCheckState               ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_bCheckState               ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_nCurProSort               ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_nCurProSort               ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_bRevision                 ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_bRevision                 ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_cRevisionReason           ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cRevisionReason           ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_VersionID                 ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_VersionID                 ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_cVersion                  ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cVersion                  ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_RdRecordsID               ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_RdRecordsID               ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_cCate                     ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cCate                     ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_cCode                     ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cCode                     ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_dDate                     ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_dDate                     ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_cMaker                    ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cMaker                    ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_cInvSehao                 ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cInvSehao                 ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_cInvPeise                 ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cInvPeise                 ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_cInvKuanhao               ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cInvKuanhao               ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_cInvUnitCost              ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cInvUnitCost              ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_cLastPerson               ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cLastPerson               ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_dLastTime                 ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_dLastTime                 ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_cInvState2                ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cInvState2                ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_dTrueTime                 ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_dTrueTime                 ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_iOrdCreateFlag            ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_iOrdCreateFlag            ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_cJianshu                  ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cJianshu                  ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_cInvMemo                  ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cInvMemo                  ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_cInvState                 ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cInvState                 ),map_row_data);
   CDataMid::InsertRowData(DBV_ProductVersionOrders_Key_cZuoFeiMemo               ,pADOConn->GetValueString(DBV_ProductVersionOrders_Key_cZuoFeiMemo               ),map_row_data);

   return map_row_data;
}
#endif // USING_GRIDCTRL_MARK

void CDBProductVersionOrders_VData::Trim()
{
   m_ProductSPData.Trim();

   m_strVersion .Trim();
   m_strCate .Trim();
   m_strCode .Trim();
   m_strDate .Trim();
   m_strMaker .Trim();
   m_strInvSehao .Trim();
   m_strInvPeise .Trim();
   m_strInvKuanhao .Trim();
   m_strInvUnitCost.Trim();
   m_strLastPerson .Trim();
   m_strLastTime .Trim();
   m_strInvState2 .Trim();
   m_strTrueTime .Trim();
   m_strJianshu .Trim();
   m_strInvMemo .Trim();
   m_strInvState .Trim();
   m_strZuoFeiMemo .Trim();
}

CDBProductVersionOrders_VList::CDBProductVersionOrders_VList()
{

}
CDBProductVersionOrders_VList::~CDBProductVersionOrders_VList()
{

}

CDBProductVersionOrders_VData* CDBProductVersionOrders_VList::GetItem(int nIndex)
{
   if (nIndex<0||nIndex>=GetCount())
      return NULL;
   return (CDBProductVersionOrders_VData*)GetAt(FindIndex(nIndex));
}

void CDBProductVersionOrders_VList::AddItem(CDBProductVersionOrders_VData* pItem)
{
   CDBProductVersionOrders_VData*pData=new CDBProductVersionOrders_VData;
   pData->Copy(pItem);
   AddTail(pData);
}

void CDBProductVersionOrders_VList::DeleteItem(int nIndex)
{
   if (nIndex<0||nIndex>GetCount())
      return;
   CDBProductVersionOrders_VData *pObject=(CDBProductVersionOrders_VData*)GetItem(nIndex);
   delete pObject;
   pObject=NULL;
   RemoveAt(FindIndex(nIndex));
}

CDBProductVersionOrders_VList * CDBProductVersionOrders_VList::Instance()
{
   if(sm_inst.get() == 0)
      sm_inst = shared_ptr<CDBProductVersionOrders_VList>(new CDBProductVersionOrders_VList);

   return sm_inst.get();
}

#ifdef USING_GRIDCTRL_MARK
MAP_GridCtrl_AllData CDBProductVersionOrders_VList::GetAllDBInfotoList( CADOConn *pADOConn,MAP_GridCtrl_AllData mapAllData )
{
   CString strSQL = _T("");
   BOOL bRet = FALSE;
   int nRow = 0;
   strSQL.Format(_T("select * from %s"),DB_VIEW_PRODUCTVERSIONORDERS);
  
   if (pADOConn != nullptr)
   {
      pADOConn->GetRecordSet(strSQL);
      while(!pADOConn->adoEOF())
      {
         CDBProductVersionOrders_VData DBProductVersion;
         MAP_GridCtrl_RowData map_row_data = DBProductVersion.CreateGridRowData(pADOConn);
         BOOL bExcu = DBProductVersion.GetAllDBInfo(pADOConn);
         pADOConn->MoveNext();
         if (!bExcu)
         {
            continue;
         }
         AddItem(&DBProductVersion);
         mapAllData.insert(make_pair(nRow++,map_row_data));
         bRet = TRUE;
      }
   }
   return mapAllData;
}
#endif // USING_GRIDCTRL_MARK
