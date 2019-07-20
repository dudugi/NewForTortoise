#include "StdAfx.h"
#include "DBP_ProductStructurePlanning.h"
#include "DBKeyDef.h"

///////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CDBP_ProductStructurePlanningData,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBP_ProductStructurePlanningList,  CDataListMid, 1)

std::shared_ptr<CDBP_ProductStructurePlanningList> CDBP_ProductStructurePlanningList::sm_inst;

CDBP_ProductStructurePlanningData::CDBP_ProductStructurePlanningData()
{
   ResetData(); 
} 

CDBP_ProductStructurePlanningData::~CDBP_ProductStructurePlanningData()
{
}

void CDBP_ProductStructurePlanningData::ResetData()
{
   m_nID                          = 0;
   m_strClassification            = _T("");
   m_strCategory                  = _T("");
   m_strPieceNum                  = _T("");
   m_strColor                     = _T("");
   m_strSize                      = _T("");
   m_strFabric                    = _T("");
   m_strFashion                   = _T("");
   m_strContour                   = _T("");
   m_fPrice_Ceiling               = 0.00  ;
   m_fPrice_Floor                 = 0.00;
   m_fPrice_Tag                   = 0.00;
   m_strRemark                    = _T("");
   m_strBand_Name                 = _T("");
   m_strBand_BandStartTime        = _T("");
   m_strBand_DesignEndTime        = _T("");
   m_strBand_PatternEndTime       = _T("");
   m_strBand_ReviewEndTime        = _T("");
   m_strBand_BandEndTime          = _T("");
   m_strBand_DeliveryStartTime    = _T("");
   m_strBand_DeliveryEndTime      = _T("");
   m_strBand_ShelvesTime          = _T("");
   m_strBand_Stylish              = _T("");
   m_strBand_Color                = _T("");
   m_strCreateUserID              = _T("");
   m_strCreateTime                = _T("");
   m_nCreateFlag                  = 0;
   m_strProgramming_Brand         = _T("");
   m_strProgramming_Years         = _T("");
   m_strProgramming_Season        = _T("");
   m_strProgramming_TradeFairTime = _T("");
   m_strProgramming_Area          = _T("");
   m_strPlanning_SubjectName      = _T("");
   m_bSubmitState                 = FALSE;
   m_strSubmitUserID              = _T("");
   m_strSubmitTime                = _T("");
   m_strCheckUserID               = _T("");
   m_strCheckTime                 = _T("");
   m_bCheckState                  = FALSE;
   m_nCurProSort                  = 0;
   m_bRevision                    = FALSE;
   m_strRevisionReason            = _T("");

   SetDataType(DAT_PRODUCTSTRUCTUREPLANNINGDATA);
}

void CDBP_ProductStructurePlanningData:: Copy(CDBP_ProductStructurePlanningData *pData)
{
   ASSERT(pData != NULL);
   CDataMid::Copy(pData);

   m_nID                          = pData->m_nID                         ;
   m_strClassification            = pData->m_strClassification           ;
   m_strCategory                  = pData->m_strCategory                 ;
   m_strPieceNum                  = pData->m_strPieceNum                 ;
   m_strColor                     = pData->m_strColor                    ;
   m_strSize                      = pData->m_strSize                     ;
   m_strFabric                    = pData->m_strFabric                   ;
   m_strFashion                   = pData->m_strFashion                  ;
   m_strContour                   = pData->m_strContour                  ;
   m_fPrice_Ceiling               = pData->m_fPrice_Ceiling              ;
   m_fPrice_Floor                 = pData->m_fPrice_Floor                ;
   m_fPrice_Tag                   = pData->m_fPrice_Tag                  ;
   m_strRemark                    = pData->m_strRemark                   ;
   m_strBand_Name                 = pData->m_strBand_Name                ;
   m_strBand_BandStartTime        = pData->m_strBand_BandStartTime       ;
   m_strBand_DesignEndTime        = pData->m_strBand_DesignEndTime       ;
   m_strBand_PatternEndTime       = pData->m_strBand_PatternEndTime      ;
   m_strBand_ReviewEndTime        = pData->m_strBand_ReviewEndTime       ;
   m_strBand_BandEndTime          = pData->m_strBand_BandEndTime         ;
   m_strBand_DeliveryStartTime    = pData->m_strBand_DeliveryStartTime   ;
   m_strBand_DeliveryEndTime      = pData->m_strBand_DeliveryEndTime     ;
   m_strBand_ShelvesTime          = pData->m_strBand_ShelvesTime         ;
   m_strBand_Stylish              = pData->m_strBand_Stylish             ;
   m_strBand_Color                = pData->m_strBand_Color               ;
   m_strCreateUserID              = pData->m_strCreateUserID             ;
   m_strCreateTime                = pData->m_strCreateTime               ;
   m_nCreateFlag                  = pData->m_nCreateFlag                 ;
   m_strProgramming_Brand         = pData->m_strProgramming_Brand        ;
   m_strProgramming_Years         = pData->m_strProgramming_Years        ;
   m_strProgramming_Season        = pData->m_strProgramming_Season       ;
   m_strProgramming_TradeFairTime = pData->m_strProgramming_TradeFairTime;
   m_strProgramming_Area          = pData->m_strProgramming_Area         ;
   m_strPlanning_SubjectName      = pData->m_strPlanning_SubjectName     ;
   m_bSubmitState                 = pData->m_bSubmitState                ;
   m_strSubmitUserID              = pData->m_strSubmitUserID             ;
   m_strSubmitTime                = pData->m_strSubmitTime               ;
   m_strCheckUserID               = pData->m_strCheckUserID              ;
   m_strCheckTime                 = pData->m_strCheckTime                ;
   m_bCheckState                  = pData->m_bCheckState                 ;
   m_nCurProSort                  = pData->m_nCurProSort                 ;
   m_bRevision                    = pData->m_bRevision                   ;
   m_strRevisionReason            = pData->m_strRevisionReason           ;
}

BOOL CDBP_ProductStructurePlanningData::GetAllDBInfo(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);

   BOOL bRet = FALSE;
   if (NULL != pADOConn)
   {
      m_nID                          = pADOConn->GetValueInt64(DBP_ProductStructurePlanning_Key_ID                        );
      m_strClassification            = pADOConn->GetValueString(DBP_ProductStructurePlanning_Key_cClassification           );
      m_strCategory                  = pADOConn->GetValueString(DBP_ProductStructurePlanning_Key_cCategory                 );
      m_strPieceNum                  = pADOConn->GetValueString(DBP_ProductStructurePlanning_Key_nPieceNum                 );
      m_strColor                     = pADOConn->GetValueString(DBP_ProductStructurePlanning_Key_cColor                    );
      m_strSize                      = pADOConn->GetValueString(DBP_ProductStructurePlanning_Key_cSize                     );
      m_strFabric                    = pADOConn->GetValueString(DBP_ProductStructurePlanning_Key_cFabric                   );
      m_strFashion                   = pADOConn->GetValueString(DBP_ProductStructurePlanning_Key_cFashion                  );
      m_strContour                   = pADOConn->GetValueString(DBP_ProductStructurePlanning_Key_cContour                  );
      m_fPrice_Ceiling               = pADOConn->GetValueDouble(DBP_ProductStructurePlanning_Key_fPrice_Ceiling            );
      m_fPrice_Floor                 = pADOConn->GetValueDouble(DBP_ProductStructurePlanning_Key_fPrice_Floor              );
      m_fPrice_Tag                   = pADOConn->GetValueDouble(DBP_ProductStructurePlanning_Key_fPrice_Tag                );
      m_strRemark                    = pADOConn->GetValueString(DBP_ProductStructurePlanning_Key_cRemark                   );
      m_strBand_Name                 = pADOConn->GetValueString(DBP_ProductStructurePlanning_Key_cBand_Name                );
      m_strBand_BandStartTime        = pADOConn->GetValueString(DBP_ProductStructurePlanning_Key_cBand_BandStartTime       );
      m_strBand_DesignEndTime        = pADOConn->GetValueString(DBP_ProductStructurePlanning_Key_cBand_DesignEndTime       );
      m_strBand_PatternEndTime       = pADOConn->GetValueString(DBP_ProductStructurePlanning_Key_cBand_PatternEndTime      );
      m_strBand_ReviewEndTime        = pADOConn->GetValueString(DBP_ProductStructurePlanning_Key_cBand_ReviewEndTime       );
      m_strBand_BandEndTime          = pADOConn->GetValueString(DBP_ProductStructurePlanning_Key_cBand_BandEndTime         );
      m_strBand_DeliveryStartTime    = pADOConn->GetValueString(DBP_ProductStructurePlanning_Key_cBand_DeliveryStartTime   );
      m_strBand_DeliveryEndTime      = pADOConn->GetValueString(DBP_ProductStructurePlanning_Key_cBand_DeliveryEndTime     );
      m_strBand_ShelvesTime          = pADOConn->GetValueString(DBP_ProductStructurePlanning_Key_cBand_ShelvesTime         );
      m_strBand_Stylish              = pADOConn->GetValueString(DBP_ProductStructurePlanning_Key_cBand_Stylish             );
      m_strBand_Color                = pADOConn->GetValueString(DBP_ProductStructurePlanning_Key_cBand_Color               );
      m_strCreateUserID              = pADOConn->GetValueString(DBP_ProductStructurePlanning_Key_cCreateUserID             );
      m_strCreateTime                = pADOConn->GetValueString(DBP_ProductStructurePlanning_Key_cCreateTime               );
      m_nCreateFlag                  = pADOConn->GetValueInt(DBP_ProductStructurePlanning_Key_nCreateFlag                  );
      m_strProgramming_Brand         = pADOConn->GetValueString(DBP_ProductStructurePlanning_Key_cProgramming_Brand        );
      m_strProgramming_Years         = pADOConn->GetValueString(DBP_ProductStructurePlanning_Key_cProgramming_Years        );
      m_strProgramming_Season        = pADOConn->GetValueString(DBP_ProductStructurePlanning_Key_cProgramming_Season       );
      m_strProgramming_TradeFairTime = pADOConn->GetValueString(DBP_ProductStructurePlanning_Key_cProgramming_TradeFairTime);
      m_strProgramming_Area          = pADOConn->GetValueString(DBP_ProductStructurePlanning_Key_cProgramming_Area         );
      m_strPlanning_SubjectName      = pADOConn->GetValueString(DBP_ProductStructurePlanning_Key_cPlanning_SubjectName     );
      m_bSubmitState                 = pADOConn->GetValueInt   (DBP_ProductStructurePlanning_Key_bSubmitState              );
      m_strSubmitUserID              = pADOConn->GetValueString(DBP_ProductStructurePlanning_Key_cSubmitUserID             );
      m_strSubmitTime                = pADOConn->GetValueString(DBP_ProductStructurePlanning_Key_cSubmitTime               );
      m_strCheckUserID               = pADOConn->GetValueString(DBP_ProductStructurePlanning_Key_cCheckUserID              );
      m_strCheckTime                 = pADOConn->GetValueString(DBP_ProductStructurePlanning_Key_cCheckTime                );
      m_bCheckState                  = pADOConn->GetValueInt(DBP_ProductStructurePlanning_Key_bCheckState                  );

      m_nCurProSort                  = pADOConn->GetValueInt(DBP_ProductStructurePlanning_Key_nCurProSort                  );

      m_bRevision                    = pADOConn->GetValueInt(DBP_ProductStructurePlanning_Key_bRevision                    );
      m_strRevisionReason            = pADOConn->GetValueString(DBP_ProductStructurePlanning_Key_cRevisionReason           );

      bRet = TRUE;
   }

   return bRet;
}

BOOL CDBP_ProductStructurePlanningData::DelAllDBInfoByID(CADOConn *pADOConn)
{
   ASSERT(NULL != pADOConn);
   CString strSQL = _T("");
   strSQL.Format(_T("delete from %s where %s = '%lld';"),DB_TABLE_PRODUCTSP,DBP_ProductStructurePlanning_Key_ID,m_nID);

   return pADOConn->ExecuteSQL(strSQL);
}

BOOL CDBP_ProductStructurePlanningData::UpdateAllDBInfoByID( CADOConn *pADOConn )
{
   ASSERT(NULL != pADOConn);
   CString strSQL = _T(""),strKeyValue = _T("");
   //关联企划ID 和 创建人 禁止修改

   strKeyValue.Format(_T("%s = '%s',%s = '%s',%s = '%s',%s = '%s',%s = '%s',\
                         %s = '%s',%s = '%s',%s = '%s',%s = '%.2f',%s = '%.2f',\
                         %s = '%.2f',%s = '%s',%s = '%s',%s = '%s',%s = '%s',\
                         %s = '%s',%s = '%s',%s = '%s',%s = '%s',%s = '%s',\
                         %s = '%s',%s = '%s',%s = '%s',%s = '%s',%s = '%s',\
                         %s = '%d',%s = '%s',%s = '%s',%s = '%s',%s = '%s',\
                         %s = '%s',%s = '%s',%s = '%d',%s = '%s',%s = '%s',\
                         %s = '%s',%s = '%s',%s = '%d',%s = '%d',%s = '%d',\
                         %s = '%s'"),
                         DBP_ProductStructurePlanning_Key_cClassification           ,m_strClassification           ,
                         DBP_ProductStructurePlanning_Key_cCategory                 ,m_strCategory                 ,
                         DBP_ProductStructurePlanning_Key_nPieceNum                 ,m_strPieceNum                 ,
                         DBP_ProductStructurePlanning_Key_cColor                    ,m_strColor                    ,
                         DBP_ProductStructurePlanning_Key_cSize                     ,m_strSize                     ,//5
                         DBP_ProductStructurePlanning_Key_cFabric                   ,m_strFabric                   ,
                         DBP_ProductStructurePlanning_Key_cFashion                  ,m_strFashion                  ,
                         DBP_ProductStructurePlanning_Key_cContour                  ,m_strContour                  ,
                         DBP_ProductStructurePlanning_Key_fPrice_Ceiling            ,m_fPrice_Ceiling              ,
                         DBP_ProductStructurePlanning_Key_fPrice_Floor              ,m_fPrice_Floor                ,//10
                         DBP_ProductStructurePlanning_Key_fPrice_Tag                ,m_fPrice_Tag                  ,
                         DBP_ProductStructurePlanning_Key_cRemark                   ,m_strRemark                   ,
                         DBP_ProductStructurePlanning_Key_cBand_Name                ,m_strBand_Name                ,
                         DBP_ProductStructurePlanning_Key_cBand_BandStartTime       ,m_strBand_BandStartTime       ,
                         DBP_ProductStructurePlanning_Key_cBand_DesignEndTime       ,m_strBand_DesignEndTime       ,//15
                         DBP_ProductStructurePlanning_Key_cBand_PatternEndTime      ,m_strBand_PatternEndTime      ,
                         DBP_ProductStructurePlanning_Key_cBand_ReviewEndTime       ,m_strBand_ReviewEndTime       ,
                         DBP_ProductStructurePlanning_Key_cBand_BandEndTime         ,m_strBand_BandEndTime         ,
                         DBP_ProductStructurePlanning_Key_cBand_DeliveryStartTime   ,m_strBand_DeliveryStartTime   ,
                         DBP_ProductStructurePlanning_Key_cBand_DeliveryEndTime     ,m_strBand_DeliveryEndTime     ,//20
                         DBP_ProductStructurePlanning_Key_cBand_ShelvesTime         ,m_strBand_ShelvesTime         ,
                         DBP_ProductStructurePlanning_Key_cBand_Stylish             ,m_strBand_Stylish             ,
                         DBP_ProductStructurePlanning_Key_cBand_Color               ,m_strBand_Color               ,
                         DBP_ProductStructurePlanning_Key_cCreateUserID             ,m_strCreateUserID             ,
                         DBP_ProductStructurePlanning_Key_cCreateTime               ,m_strCreateTime               ,//25
                         DBP_ProductStructurePlanning_Key_nCreateFlag               ,m_nCreateFlag                 ,
                         DBP_ProductStructurePlanning_Key_cProgramming_Brand        ,m_strProgramming_Brand        ,
                         DBP_ProductStructurePlanning_Key_cProgramming_Years        ,m_strProgramming_Years        ,
                         DBP_ProductStructurePlanning_Key_cProgramming_Season       ,m_strProgramming_Season       ,
                         DBP_ProductStructurePlanning_Key_cProgramming_TradeFairTime,m_strProgramming_TradeFairTime,//30
                         DBP_ProductStructurePlanning_Key_cProgramming_Area         ,m_strProgramming_Area         ,
                         DBP_ProductStructurePlanning_Key_cPlanning_SubjectName     ,m_strPlanning_SubjectName     ,
                         DBP_ProductStructurePlanning_Key_bSubmitState              ,m_bSubmitState                ,
                         DBP_ProductStructurePlanning_Key_cSubmitUserID             ,m_strSubmitUserID             ,
                         DBP_ProductStructurePlanning_Key_cSubmitTime               ,m_strSubmitTime               ,//40
                         DBP_ProductStructurePlanning_Key_cCheckUserID              ,m_strCheckUserID              ,
                         DBP_ProductStructurePlanning_Key_cCheckTime                ,m_strCheckTime                ,
                         DBP_ProductStructurePlanning_Key_bCheckState               ,m_bCheckState                 ,
                         DBP_ProductStructurePlanning_Key_nCurProSort               ,m_nCurProSort                 ,
                         DBP_ProductStructurePlanning_Key_bRevision                 ,m_bRevision                   ,//50
                         DBP_ProductStructurePlanning_Key_cRevisionReason           ,m_strRevisionReason           
                         );

   //更新时不需要更新其它的关联信息  
   strSQL.Format(_T("update %s set %s where %s = '%lld';"),DB_TABLE_PRODUCTSP,
      strKeyValue,DBP_ProductStructurePlanning_Key_ID,m_nID);

   return pADOConn->ExecuteSQL(strSQL);
}

BOOL CDBP_ProductStructurePlanningData::InsertAllDBInfo( CADOConn *pADOConn )
{
   ASSERT(NULL != pADOConn);
   CString strSQL = _T(""),strParam = _T(""),strValue = _T("");

   //                   1  2  3  4  5  6  7  8  9 10
   strParam.Format(_T("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,\
                       %s,%s,%s,%s,%s,%s,%s,%s,%s,%s,\
                       %s,%s,%s,%s,%s,%s,%s,%s,%s,%s,\
                       %s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s"),
                       DBP_ProductStructurePlanning_Key_cClassification ,DBP_ProductStructurePlanning_Key_cCategory ,
                       DBP_ProductStructurePlanning_Key_nPieceNum ,DBP_ProductStructurePlanning_Key_cColor ,
                       DBP_ProductStructurePlanning_Key_cSize ,DBP_ProductStructurePlanning_Key_cFabric ,
                       DBP_ProductStructurePlanning_Key_cFashion ,DBP_ProductStructurePlanning_Key_cContour ,
                       DBP_ProductStructurePlanning_Key_fPrice_Ceiling ,DBP_ProductStructurePlanning_Key_fPrice_Floor ,//10
                       DBP_ProductStructurePlanning_Key_fPrice_Tag ,DBP_ProductStructurePlanning_Key_cRemark ,
                       DBP_ProductStructurePlanning_Key_cBand_Name ,DBP_ProductStructurePlanning_Key_cBand_BandStartTime ,
                       DBP_ProductStructurePlanning_Key_cBand_DesignEndTime ,DBP_ProductStructurePlanning_Key_cBand_PatternEndTime ,
                       DBP_ProductStructurePlanning_Key_cBand_ReviewEndTime ,DBP_ProductStructurePlanning_Key_cBand_BandEndTime ,
                       DBP_ProductStructurePlanning_Key_cBand_DeliveryStartTime ,DBP_ProductStructurePlanning_Key_cBand_DeliveryEndTime ,//20
                       DBP_ProductStructurePlanning_Key_cBand_ShelvesTime ,DBP_ProductStructurePlanning_Key_cBand_Stylish ,
                       DBP_ProductStructurePlanning_Key_cBand_Color ,DBP_ProductStructurePlanning_Key_cCreateUserID ,
                       DBP_ProductStructurePlanning_Key_cCreateTime ,DBP_ProductStructurePlanning_Key_nCreateFlag ,
                       DBP_ProductStructurePlanning_Key_cProgramming_Brand ,DBP_ProductStructurePlanning_Key_cProgramming_Years ,
                       DBP_ProductStructurePlanning_Key_cProgramming_Season ,DBP_ProductStructurePlanning_Key_cProgramming_TradeFairTime ,//30
                       DBP_ProductStructurePlanning_Key_cProgramming_Area ,DBP_ProductStructurePlanning_Key_cPlanning_SubjectName,
                       DBP_ProductStructurePlanning_Key_bSubmitState ,DBP_ProductStructurePlanning_Key_cSubmitUserID,
                       DBP_ProductStructurePlanning_Key_cSubmitTime  ,
                       DBP_ProductStructurePlanning_Key_cCheckUserID,DBP_ProductStructurePlanning_Key_cCheckTime  ,
                       DBP_ProductStructurePlanning_Key_bCheckState ,DBP_ProductStructurePlanning_Key_nCurProSort,
                       DBP_ProductStructurePlanning_Key_bRevision,DBP_ProductStructurePlanning_Key_cRevisionReason
                       );
   //                    1    2    3    4    5    6    7    8     9     10
   strValue.Format(_T("'%s','%s','%s','%s','%s','%s','%s','%s','%.2f','%.2f',\
                      '%.2f','%s','%s','%s','%s','%s','%s','%s','%s','%s',\
                      '%s','%s','%s','%s',%s,'%d','%s','%s','%s','%s',\
                      '%s','%s','%d','%s','%s','%s','%s','%d','%d','%d','%s'"),
      m_strClassification ,m_strCategory ,
      m_strPieceNum ,m_strColor ,
      m_strSize ,m_strFabric ,
      m_strFashion ,m_strContour ,
      m_fPrice_Ceiling ,m_fPrice_Floor ,//10
      m_fPrice_Tag ,m_strRemark ,
      m_strBand_Name ,m_strBand_BandStartTime ,
      m_strBand_DesignEndTime ,m_strBand_PatternEndTime ,
      m_strBand_ReviewEndTime ,m_strBand_BandEndTime ,
      m_strBand_DeliveryStartTime ,m_strBand_DeliveryEndTime ,//20
      m_strBand_ShelvesTime ,m_strBand_Stylish ,
      m_strBand_Color ,m_strCreateUserID ,
      DBS_GETDATESTR ,m_nCreateFlag ,
      m_strProgramming_Brand ,m_strProgramming_Years ,
      m_strProgramming_Season ,m_strProgramming_TradeFairTime,//30
      m_strProgramming_Area ,m_strPlanning_SubjectName,
      m_bSubmitState   ,m_strSubmitUserID,
      m_strSubmitTime  ,
      m_strCheckUserID,m_strCheckTime  ,
      m_bCheckState ,m_nCurProSort,
      m_bRevision,m_strRevisionReason
      );


   strSQL.Format(_T("insert into %s (%s) values(%s);"),
      DB_TABLE_PRODUCTSP,strParam,strValue);

   return pADOConn->ExecuteSQL(strSQL);
}

void CDBP_ProductStructurePlanningData::Trim()
{
   m_strClassification .Trim();
   m_strCategory .Trim();
   m_strPieceNum .Trim();
   m_strColor .Trim();
   m_strSize .Trim();
   m_strFabric .Trim();
   m_strFashion .Trim();
   m_strContour .Trim();
   m_strRemark .Trim();
   m_strBand_Name .Trim();
   m_strBand_BandStartTime .Trim();
   m_strBand_DesignEndTime .Trim();
   m_strBand_PatternEndTime .Trim();
   m_strBand_ReviewEndTime .Trim();
   m_strBand_BandEndTime .Trim();
   m_strBand_DeliveryStartTime .Trim();
   m_strBand_DeliveryEndTime .Trim();
   m_strBand_ShelvesTime .Trim();
   m_strBand_Stylish .Trim();
   m_strCreateUserID .Trim();
   m_strCreateTime .Trim();
   m_strProgramming_Brand .Trim();
   m_strProgramming_Season .Trim();
   m_strProgramming_TradeFairTime.Trim();
   m_strProgramming_Area .Trim();
   m_strPlanning_SubjectName .Trim();
   m_strProgramming_Years.Trim();
   m_strCheckUserID.Trim();
   m_strCheckTime.Trim();
   m_strRevisionReason.Trim();
   m_strSubmitUserID.Trim();
   m_strSubmitTime  .Trim();
}

BOOL CDBP_ProductStructurePlanningData::CopyToDBProgrammingAndBindPlanningID( CDBP_ProgrammingData *pProgrammingData ,__int64 nID)
{
   //工作未完成，等待其他功能完善。。。
   ASSERT(pProgrammingData != NULL);
   if (pProgrammingData != NULL)
   {
      pProgrammingData->m_strBrand        =  m_strProgramming_Brand        ;//品牌
      pProgrammingData->m_nYears          =  _ttoi(m_strProgramming_Years)        ;//年度
      pProgrammingData->m_strSeason       =  m_strProgramming_Season       ;//季节
      pProgrammingData->m_strTradeFairTime=  m_strProgramming_TradeFairTime;//订货会时间
      pProgrammingData->m_strArea         =  m_strProgramming_Area         ;//区域
      //pProgrammingData->m_strSubjectName     =  m_strPlanning_SubjectName     ;//主题名
      pProgrammingData->m_strCreateUserID             =  m_strCreateUserID             ;//创建人
      pProgrammingData->m_nAssociatedPlanningID = nID;
   }

   return TRUE;
}

BOOL CDBP_ProductStructurePlanningData::CopyToDBBandAndBindProgrammingID( CDBP_BindInfoData *pDBBandInfo,__int64 nID )
{
   ASSERT(pDBBandInfo != NULL);
   if (pDBBandInfo != NULL)
   {
      pDBBandInfo->m_strName                = m_strBand_Name               ;//名称
      pDBBandInfo->m_oleBandStartTime       = m_strBand_BandStartTime      ;//波段开始时间
      pDBBandInfo->m_oleDesignEndTime       = m_strBand_DesignEndTime      ;//设计完成时间
      pDBBandInfo->m_olePatternEndTime      = m_strBand_PatternEndTime     ;//纸样完成时间
      pDBBandInfo->m_oleReviewEndTime       = m_strBand_ReviewEndTime      ;//内审会完成时间
      pDBBandInfo->m_oleBandEndTime         = m_strBand_BandEndTime        ;//波段结束时间
      pDBBandInfo->m_strDeliveryStartTime   = m_strBand_DeliveryStartTime  ;//货期起始时间
      pDBBandInfo->m_strDeliveryEndTime     = m_strBand_DeliveryEndTime    ;//货期结束时间
      pDBBandInfo->m_strShelvesTime         = m_strBand_ShelvesTime        ;//上货日
      pDBBandInfo->m_strStylish             = m_strBand_Stylish            ;//风格
      pDBBandInfo->m_strColor               = m_strBand_Color              ;//色系
      pDBBandInfo->m_strCreateUserID             = m_strCreateUserID            ;//创建人
      pDBBandInfo->m_strCreateUserTime               = m_strCreateTime              ;//创建时间
      pDBBandInfo->m_strCheckUserID              = m_strCheckUserID             ;//审核人
      pDBBandInfo->m_strCheckTime                = m_strCheckTime               ;//审核时间
      pDBBandInfo->m_bCheckState                 = m_bCheckState                ;//审核状态
      pDBBandInfo->m_nAssociatedProgrammingID    = nID;
   }
   return TRUE;
}

BOOL CDBP_ProductStructurePlanningData::CopyToDBPlanning( CDBP_PlanningData *pDBPlanningInfo )
{
   ASSERT(pDBPlanningInfo != NULL);
   if (pDBPlanningInfo != NULL)
   {
      pDBPlanningInfo->m_strBrand        =  m_strProgramming_Brand        ;//品牌
      pDBPlanningInfo->m_nYears          =  _ttoi(m_strProgramming_Years)        ;//年度
      pDBPlanningInfo->m_strSeason       =  m_strProgramming_Season       ;//季节
      pDBPlanningInfo->m_strSubjectName     =  m_strPlanning_SubjectName     ;//主题名
      pDBPlanningInfo->m_strCreateUserID             =  m_strCreateUserID             ;//创建人
      pDBPlanningInfo->m_strCreateTime      =  m_strCreateTime;
   }
   return TRUE; 
}

CDBP_ProductStructurePlanningList::CDBP_ProductStructurePlanningList()
{

}
CDBP_ProductStructurePlanningList::~CDBP_ProductStructurePlanningList()
{

}

CDBP_ProductStructurePlanningData* CDBP_ProductStructurePlanningList::GetItem(int nIndex)
{
   if (nIndex<0||nIndex>=GetCount())
      return NULL;
   return (CDBP_ProductStructurePlanningData*)GetAt(FindIndex(nIndex));
}

CDBP_ProductStructurePlanningData* CDBP_ProductStructurePlanningList::GetItemByID(__int64 nID)
{
   CDBP_ProductStructurePlanningData* pRet = NULL;

   int nCount = GetCount();

   for (int nIndex = 0;nIndex < nCount;++nIndex)
   {
      auto pData = GetItem(nIndex);
      if (NULL != pData && pData->m_nID == nID)
      {
         pRet = pData;
         break;
      }
   }
   return pRet;
}

void CDBP_ProductStructurePlanningList::AddItem(CDBP_ProductStructurePlanningData* pItem)
{
   CDBP_ProductStructurePlanningData*pData=new CDBP_ProductStructurePlanningData;
   pData->Copy(pItem);
   AddTail(pData);
}

void CDBP_ProductStructurePlanningList::DeleteItem(int nIndex)
{
   if (nIndex<0||nIndex>GetCount())
      return;
   CDBP_ProductStructurePlanningData *pObject=(CDBP_ProductStructurePlanningData*)GetItem(nIndex);
   delete pObject;
   pObject=NULL;
   RemoveAt(FindIndex(nIndex));
}

CDBP_ProductStructurePlanningList * CDBP_ProductStructurePlanningList::Instance()
{
   if(sm_inst.get() == 0)
      sm_inst = shared_ptr<CDBP_ProductStructurePlanningList>(new CDBP_ProductStructurePlanningList);

   return sm_inst.get();
}
