#include "StdAfx.h"
#include "DBStyle_DesDenisity.h"
#include "DBKeyDef.h"
#include "DBImage.h"


IMPLEMENT_SERIAL(CDBStyle_DesDenisityData,CDataMid,1)

CDBStyle_DesDenisityData::CDBStyle_DesDenisityData()
{
   ResetData();
}

CDBStyle_DesDenisityData::~CDBStyle_DesDenisityData()
{
}

void CDBStyle_DesDenisityData::ResetData()   
{
   m_faceData.ResetData();
   m_nID = -1;//自增ID
   m_nStyleID = 0;
   m_strName = _T("");//名称
   m_fHorDesSrc = 0  ;//横密
   m_fVerDesSrc = 0  ;//直密
   m_fHorDesNew = 0  ;//横密
   m_fVerDesNew = 0  ;//直密
   m_strStructure = _T("");//坯布结构
   m_strMaterial = _T("");//毛料

   m_fPull = 0;//拉力
   m_strPullUnit = _T("");//单位
   m_nPullType = 0;//eg:全长拉 or 领下拉
   m_strNeedle = _T("");//针型

   //小片重量
   m_fPieceUnit = 0;//克
   m_fPieceTurns = 0;//转
   m_fPieceNeedle = 0;//针

   //起头空转
   m_fStartTurns = 0;

   //罗文排列
   m_strRomanType = _T("");

   //加丝转数
   m_strWire = _T("");//加丝
   m_fWireTurns = 0;//转
   m_nWireType = 0;//是否全加丝


   //排针
   m_bShowPZ = FALSE;
   m_strPZName = _T("");//排针名称
   m_strPinBottom = _T("");//底
   m_strPinFace = _T("");//面
   m_nPinType = 0;//排针类型

   m_strType = _T("");//密度类型
   m_strBaseType = _T("");

   m_strSavedUserID = _T("");
   m_strSaveTime    = _T("");
   m_strRemark      = _T("");

   m_strPieceName   = _T("");
   m_strMatName     = _T("");

   SetDataType(DAT_STYLE_DESDENISITY);
}

void CDBStyle_DesDenisityData::Copy( CDBStyle_DesDenisityData *pData )
{
   ASSERT(pData!=NULL);
   CDataMid::Copy(pData);

   m_nID             = pData->m_nID             ;
   m_nStyleID        = pData->m_nStyleID        ;
   m_strName         = pData->m_strName         ;
   m_fHorDesSrc      = pData->m_fHorDesSrc      ;
   m_fVerDesSrc      = pData->m_fVerDesSrc      ;
   m_fHorDesNew      = pData->m_fHorDesNew      ;
   m_fVerDesNew      = pData->m_fVerDesNew      ;
   m_strStructure    = pData->m_strStructure    ;
   m_strMaterial     = pData->m_strMaterial     ;
   m_fPull           = pData->m_fPull           ;
   m_strPullUnit     = pData->m_strPullUnit     ;
   m_nPullType       = pData->m_nPullType       ;
   m_strNeedle       = pData->m_strNeedle       ;
   m_fPieceUnit      = pData->m_fPieceUnit      ;
   m_fPieceTurns     = pData->m_fPieceTurns     ;
   m_fPieceNeedle    = pData->m_fPieceNeedle    ;
   m_fStartTurns     = pData->m_fStartTurns     ;
   m_strRomanType    = pData->m_strRomanType    ;
   m_strWire         = pData->m_strWire         ;
   m_fWireTurns      = pData->m_fWireTurns      ;
   m_nWireType       = pData->m_nWireType       ;
   m_bShowPZ         = pData->m_bShowPZ         ;
   m_strPZName       = pData->m_strPZName       ;
   m_strPinBottom    = pData->m_strPinBottom    ;
   m_strPinFace      = pData->m_strPinFace      ;
   m_nPinType        = pData->m_nPinType        ;
   m_strType         = pData->m_strType         ;
   m_strBaseType     = pData->m_strBaseType     ;
   m_strSavedUserID  = pData->m_strSavedUserID  ;
   m_strSaveTime     = pData->m_strSaveTime     ;
   m_strRemark       = pData->m_strRemark       ;
   m_strPieceName    = pData->m_strPieceName    ;
   m_strMatName      = pData->m_strMatName      ;

   m_faceData.Copy(&pData->m_faceData);
}

BOOL CDBStyle_DesDenisityData::GetAllDBInfo( CADOConn *pADOConn )
{
   ASSERT(pADOConn != NULL);

   BOOL bRet = TRUE;

   if (NULL == pADOConn)
   {
      bRet = FALSE;
   }
   else
   {
      m_nID             = pADOConn->GetValueInt64 (DBStyle_DesDenisity_Key_ID           );//自增ID
      m_nStyleID        = pADOConn->GetValueInt   (DBStyle_DesDenisity_Key_nStyleID     );
      m_strName         = pADOConn->GetValueString(DBStyle_DesDenisity_Key_cName        );//名称
      m_fHorDesSrc      = pADOConn->GetValueDouble(DBStyle_DesDenisity_Key_fHorDesSrc   );//横密
      m_fVerDesSrc      = pADOConn->GetValueDouble(DBStyle_DesDenisity_Key_fVerDesSrc   );//直密
      m_fHorDesNew      = pADOConn->GetValueDouble(DBStyle_DesDenisity_Key_fHorDesNew   );//横密
      m_fVerDesNew      = pADOConn->GetValueDouble(DBStyle_DesDenisity_Key_fVerDesNew   );//直密
      m_strStructure    = pADOConn->GetValueString(DBStyle_DesDenisity_Key_cStructure   );//坯布结构
      m_strMaterial     = pADOConn->GetValueString(DBStyle_DesDenisity_Key_cMaterial    );//毛料
      m_fPull           = pADOConn->GetValueDouble(DBStyle_DesDenisity_Key_fPull        );//拉力
      m_strPullUnit     = pADOConn->GetValueString(DBStyle_DesDenisity_Key_cPullUnit    );//单位
      m_nPullType       = pADOConn->GetValueInt   (DBStyle_DesDenisity_Key_iPullType    );//eg:全长拉 or 领下拉
      m_strNeedle       = pADOConn->GetValueString(DBStyle_DesDenisity_Key_cNeedle      );//针型

      //小片重量
      m_fPieceUnit      = pADOConn->GetValueDouble(DBStyle_DesDenisity_Key_fPieceUnit   );//克
      m_fPieceTurns     = pADOConn->GetValueDouble(DBStyle_DesDenisity_Key_fPieceTurns  );//转
      m_fPieceNeedle    = pADOConn->GetValueDouble(DBStyle_DesDenisity_Key_fPieceNeedle );//针

      //起头空转
      m_fStartTurns     = pADOConn->GetValueDouble(DBStyle_DesDenisity_Key_fStartTurns);

      //罗文排列
      m_strRomanType    = pADOConn->GetValueString(DBStyle_DesDenisity_Key_cRomanType);

      //加丝转数
      m_strWire         = pADOConn->GetValueString (DBStyle_DesDenisity_Key_cWire      );//加丝
      m_fWireTurns      = pADOConn->GetValueDouble (DBStyle_DesDenisity_Key_fWireTurns );//转
      m_nWireType       = pADOConn->GetValueInt    (DBStyle_DesDenisity_Key_iWireType  );//是否全加丝

      //排针
      m_bShowPZ         = pADOConn->GetValueInt    (DBStyle_DesDenisity_Key_iShowPZ   );
      m_strPZName       = pADOConn->GetValueString (DBStyle_DesDenisity_Key_cPZName   );
      m_strPinBottom    = pADOConn->GetValueString (DBStyle_DesDenisity_Key_cPinBottom);//底
      m_strPinFace      = pADOConn->GetValueString (DBStyle_DesDenisity_Key_cPinFace  );//面
      m_nPinType        = pADOConn->GetValueInt    (DBStyle_DesDenisity_Key_iPinType  );//排针类型

      m_strType         = pADOConn->GetValueString(DBStyle_DesDenisity_Key_cType       );//密度类型
      m_strBaseType     = pADOConn->GetValueString(DBStyle_DesDenisity_Key_cBaseType   );

      m_strSavedUserID  = pADOConn->GetValueString(DBStyle_DesDenisity_Key_cSavedUserID);
      m_strSaveTime     = pADOConn->GetValueString(DBStyle_DesDenisity_Key_cSaveTime   );
      m_strRemark       = pADOConn->GetValueString(DBStyle_DesDenisity_Key_cRemark     );

      m_strPieceName    = pADOConn->GetValueString(DBStyle_DesDenisity_Key_cPieceName);
      m_strMatName      = pADOConn->GetValueString(DBStyle_DesDenisity_Key_cMatName  );
   }


   return bRet;
}

void CDBStyle_DesDenisityData::SetFaceData(CDBStyle_DesFaceCodeData* data)
{
   if (data->m_nIDDensity == m_nID)
   {
      m_faceData.AddItem(data);
      m_faceData.m_nIDDensity = m_nID;
   }
}

BOOL CDBStyle_DesDenisityData::InsertAllDBInfoByID(CADOConn * pADOConn)
{
   ASSERT(pADOConn != NULL);

   BOOL bRet = TRUE;

   CString strSQL = _T("");
   strSQL.Format(_T("insert into %s (%s,%s,%s,%s,%s, %s,%s,%s,%s,%s,\
 %s,%s,%s,%s,%s, %s,%s,%s,%s,%s,\
 %s,%s,%s,%s,%s, %s,%s,%s,%s,%s ,%s,%s)\
 values('%d','%s','%.2f','%.2f','%.2f',  '%.2f','%s','%s','%.2f','%s',\
 '%d','%s','%.4f','%.2f','%.2f',  '%.2f','%s','%s','%.2f','%d',\
 '%s','%s','%s','%d','%s',  '%d','%s','%s',%s,'%s' ,'%s','%s')"), 
                    DB_TABLE_STYLE_DESDENISITY,
                    DBStyle_DesDenisity_Key_nStyleID    ,DBStyle_DesDenisity_Key_cName       ,
                    DBStyle_DesDenisity_Key_fHorDesSrc  ,DBStyle_DesDenisity_Key_fVerDesSrc  ,
                    DBStyle_DesDenisity_Key_fHorDesNew  ,DBStyle_DesDenisity_Key_fVerDesNew  ,
                    DBStyle_DesDenisity_Key_cStructure  ,DBStyle_DesDenisity_Key_cMaterial   ,
                    DBStyle_DesDenisity_Key_fPull       ,DBStyle_DesDenisity_Key_cPullUnit   ,

                    DBStyle_DesDenisity_Key_iPullType   ,DBStyle_DesDenisity_Key_cNeedle     ,
                    DBStyle_DesDenisity_Key_fPieceUnit  ,DBStyle_DesDenisity_Key_fPieceTurns ,
                    DBStyle_DesDenisity_Key_fPieceNeedle,DBStyle_DesDenisity_Key_fStartTurns ,
                    DBStyle_DesDenisity_Key_cRomanType  ,DBStyle_DesDenisity_Key_cWire       ,
                    DBStyle_DesDenisity_Key_fWireTurns  ,DBStyle_DesDenisity_Key_iWireType   ,

                    DBStyle_DesDenisity_Key_cPinBottom  ,DBStyle_DesDenisity_Key_cPinFace    ,
                    DBStyle_DesDenisity_Key_iPinType    ,DBStyle_DesDenisity_Key_cType       ,
                    DBStyle_DesDenisity_Key_cBaseType   ,DBStyle_DesDenisity_Key_iShowPZ     ,
                    DBStyle_DesDenisity_Key_cPZName     ,DBStyle_DesDenisity_Key_cSavedUserID,
                    DBStyle_DesDenisity_Key_cSaveTime   ,DBStyle_DesDenisity_Key_cRemark     ,

                    DBStyle_DesDenisity_Key_cPieceName  ,DBStyle_DesDenisity_Key_cMatName    ,

                    m_nStyleID      ,m_strName       ,
                    m_fHorDesSrc    ,m_fVerDesSrc    ,
                    m_fHorDesNew    ,m_fVerDesNew    ,
                    m_strStructure  ,m_strMaterial   ,
                    m_fPull         ,m_strPullUnit   ,

                    m_nPullType     ,m_strNeedle     ,
                    m_fPieceUnit    ,m_fPieceTurns   ,
                    m_fPieceNeedle  ,m_fStartTurns   ,
                    m_strRomanType  ,m_strWire       ,
                    m_fWireTurns    ,m_nWireType     ,

                    m_strPinBottom  ,m_strPinFace    ,
                    m_nPinType      ,m_strType       ,
                    m_strBaseType   ,m_bShowPZ       ,
                    m_strPZName     ,m_strSavedUserID,
                    DBS_GETDATESTR  ,m_strRemark     ,

                    m_strPieceName  ,m_strMatName    
                    );

   //-------------------------------
   CString strDensityInsertSQL = strSQL;
   CString strFaceCodeInsertFormatSQL = _T(""), strFaceCodeInsertValueSQL = _T("");
   CDBStyle_DesFaceCodeData oFaceCodeData;
   strFaceCodeInsertFormatSQL = oFaceCodeData.GetSQLFormat();

   int nCount  = m_faceData.m_lstFaceCode.GetCount();

   for (int i = 0; i < nCount; i++)
   {
      if (!strFaceCodeInsertValueSQL.IsEmpty())
      {
         strFaceCodeInsertValueSQL += _T(",");
      }
      CString strTmpValueSQL = _T("");

      CDBStyle_DesFaceCodeData* pCode = m_faceData.m_lstFaceCode.GetItem(i);
      if (pCode)
      {
         strTmpValueSQL.Format(_T("('%s','%s','%s','%s','%s',@IDensityID)"), 
            pCode->m_strName, pCode->m_sOldLen, pCode->m_strType, pCode->m_sLen, pCode->m_strUnit);
      }
      strFaceCodeInsertValueSQL += strTmpValueSQL;
   }

   CString strFaceCodeSQL = _T("");
   if (!strFaceCodeInsertValueSQL.IsEmpty())
   {
      strFaceCodeSQL.Format(_T("insert into %s(%s) values %s"), DB_TABLE_STYLE_DESFACECODE, strFaceCodeInsertFormatSQL, strFaceCodeInsertValueSQL);
   }

   strSQL.Format(_T("declare @IDensityID int \
                    set @IDensityID = 0 \
                    %s \
                    set @IDensityID = @@Identity \
                    %s"),
                    strDensityInsertSQL,
                    strFaceCodeSQL
                    );
   if (!pADOConn->ExecuteSQL(strSQL))
   {
      return FALSE;
   }
   return TRUE;
}

CDBStyle_DesDenisityList::CDBStyle_DesDenisityList()
{

}

CDBStyle_DesDenisityList::~CDBStyle_DesDenisityList()
{

}

void CDBStyle_DesDenisityList::DeleteItemByName(const CString & strName)
{
   int nCount = GetCount();
   for (int nIndex = 0;nIndex < nCount;++nIndex)
   {
      auto pData = GetItem(nIndex);
      if (NULL != pData && pData->m_strName == strName)
      {
         DeleteItem(nIndex);
         return;
      }
   }
}

CDBStyle_DesDenisityData * CDBStyle_DesDenisityList::GetItemByName(const CString & strName)
{
   int nCount = GetCount();
   for (int nIndex = 0;nIndex < nCount;++nIndex)
   {
      auto pData = GetItem(nIndex);
      if (NULL != pData && pData->m_strName == strName)
      {
         return pData;
      }
   }
   return NULL;
}

void CDBStyle_DesDenisityList::MatchData(CDBStyle_DesFaceCodeData* data)
{
   int nIndex = 0, nCount = GetCount();
   for (nIndex = 0; nIndex < nCount; nIndex++)
   {
      CDBStyle_DesDenisityData * pData = GetItem(nIndex);
      if (NULL != pData && pData->m_nID == data->m_nIDDensity)
      {
         pData->SetFaceData(data);
      }
   }
}

BOOL CDBStyle_DesDenisityList::GetDataByStyleID(CADOConn *pADOConn,int nStyleID)
{
   CString strSQL;
   strSQL.Format(_T("select * from %s where %s = '%d'"),
      DB_TABLE_STYLE_DESDENISITY,
      DBStyle_DesDenisity_Key_nStyleID,nStyleID
      );
   pADOConn->GetRecordSet(strSQL);

   while(!pADOConn->adoEOF())
   {
      CDBStyle_DesDenisityData * pNewData= new CDBStyle_DesDenisityData;
      pNewData->GetAllDBInfo(pADOConn);
      AddTail(pNewData);

      pADOConn->MoveNext();
   }

   //获取密度数据
   
   strSQL.Format(_T("select * from %s where %s in (select %s from %s where %s = '%d')"),
      DB_TABLE_STYLE_DESFACECODE,
      DBStyle_DesFaceCode_Key_IDDensity,
      DBStyle_DesDenisity_Key_ID,DB_TABLE_STYLE_DESDENISITY,
      DBStyle_DesDenisity_Key_nStyleID,nStyleID
      );
   pADOConn->GetRecordSet(strSQL);

   while(!pADOConn->adoEOF())
   {
      CDBStyle_DesFaceCodeData oData;
      oData.GetAllDBInfo(pADOConn);

      MatchData(&oData);

      pADOConn->MoveNext();
   }
   return TRUE;
}

#ifdef USING_GRIDCTRL_MARK

MAP_GridCtrl_AllData CDBStyle_DesDenisityList::CreateGridData()
{
   MAP_GridCtrl_AllData map_all_data;

   int nIndex = 0, nCount = GetCount();
   int nValidCount = 1;
   for (nIndex = 0; nIndex < nCount; nIndex++)
   {
      CDBStyle_DesDenisityData * pData = GetItem(nIndex);
      if (NULL != pData)
      {
         MAP_GridCtrl_RowData map_row_data;
         CString strIndex = _T("");
         strIndex.Format(FORMAT_INT, nValidCount);
         CString cName = _T("");
         for (int i = 0; i < 4; i++)
         {
            CDBStyle_DesFaceCodeData* pCode = pData->m_faceData.m_lstFaceCode.GetItem(i);
            if (pCode)
            {
               CString cKeyCode = _T("");
               cKeyCode.Format(_T("cFaceCode%d"),i+1);
               cName.Format(_T("%s: %s %s %s %s"), pCode->m_strName, pCode->m_sOldLen, pCode->m_strType, pCode->m_sLen, pCode->m_strUnit);
               pData->InsertRowData(cKeyCode, map_row_data, FORMAT_STRING, cName);//拉密
            }
         }

         pData->InsertRowData(DBStyle_DesDenisity_Key_cName          ,map_row_data, FORMAT_STRING,   pData->m_strName         );
         pData->InsertRowData(DBStyle_DesDenisity_Key_fHorDesSrc     ,map_row_data, CB_enum_FieldData_Double2Point, CB_enum_FieldCtrl_Text, FORMAT_FLOAT2DOT,   pData->m_fHorDesSrc      );
         pData->InsertRowData(DBStyle_DesDenisity_Key_fVerDesSrc     ,map_row_data, CB_enum_FieldData_Double2Point, CB_enum_FieldCtrl_Text, FORMAT_FLOAT2DOT,   pData->m_fVerDesSrc      );
         pData->InsertRowData(DBStyle_DesDenisity_Key_fHorDesNew     ,map_row_data, CB_enum_FieldData_Double2Point, CB_enum_FieldCtrl_Text, FORMAT_FLOAT2DOT,   pData->m_fHorDesNew      );
         pData->InsertRowData(DBStyle_DesDenisity_Key_fVerDesNew     ,map_row_data, CB_enum_FieldData_Double2Point, CB_enum_FieldCtrl_Text, FORMAT_FLOAT2DOT,   pData->m_fVerDesNew      );
         pData->InsertRowData(DBStyle_DesDenisity_Key_cStructure     ,map_row_data, FORMAT_STRING,   pData->m_strStructure    );
         pData->InsertRowData(DBStyle_DesDenisity_Key_cMaterial      ,map_row_data, FORMAT_STRING,   pData->m_strMaterial     );
         pData->InsertRowData(DBStyle_DesDenisity_Key_fPull          ,map_row_data, CB_enum_FieldData_Double2Point, CB_enum_FieldCtrl_Text, FORMAT_FLOAT2DOT,   pData->m_fPull           );
         pData->InsertRowData(DBStyle_DesDenisity_Key_cPullUnit      ,map_row_data, FORMAT_STRING,   pData->m_strPullUnit     );
         pData->InsertRowData(DBStyle_DesDenisity_Key_iPullType      ,map_row_data, FORMAT_INT   ,   pData->m_nPullType       );
         pData->InsertRowData(DBStyle_DesDenisity_Key_cNeedle        ,map_row_data, FORMAT_STRING,   pData->m_strNeedle       );
         /*pData->InsertRowData(DBStyle_DesDenisity_Key_fPieceUnit     ,map_row_data, FORMAT_STRING,   pData->m_fPieceUnit      );
         pData->InsertRowData(DBStyle_DesDenisity_Key_fPieceTurns    ,map_row_data, FORMAT_STRING,   pData->m_fPieceTurns     );
         pData->InsertRowData(DBStyle_DesDenisity_Key_fPieceNeedle   ,map_row_data, FORMAT_STRING,   pData->m_fPieceNeedle    );*/
         pData->InsertRowData(DBStyle_DesDenisity_Key_fStartTurns    ,map_row_data, CB_enum_FieldData_Double2Point, CB_enum_FieldCtrl_Text, FORMAT_FLOAT2DOT,   pData->m_fStartTurns     );
         pData->InsertRowData(DBStyle_DesDenisity_Key_cRomanType     ,map_row_data, FORMAT_STRING,   pData->m_strRomanType    );
         pData->InsertRowData(DBStyle_DesDenisity_Key_cWire          ,map_row_data, FORMAT_STRING,   pData->m_strWire         );
         pData->InsertRowData(DBStyle_DesDenisity_Key_fWireTurns     ,map_row_data, CB_enum_FieldData_Double2Point, CB_enum_FieldCtrl_Text, FORMAT_FLOAT2DOT,   pData->m_fWireTurns      );
         pData->InsertRowData(DBStyle_DesDenisity_Key_iWireType      ,map_row_data, FORMAT_INT   ,   pData->m_nWireType       );
         pData->InsertRowData(DBStyle_DesDenisity_Key_cPinBottom     ,map_row_data, FORMAT_STRING,   pData->m_strPinBottom    );
         pData->InsertRowData(DBStyle_DesDenisity_Key_cPinFace       ,map_row_data, FORMAT_STRING,   pData->m_strPinFace      );
         pData->InsertRowData(DBStyle_DesDenisity_Key_iPinType       ,map_row_data, FORMAT_INT   ,   pData->m_nPinType        );
         pData->InsertRowData(DBStyle_DesDenisity_Key_cType          ,map_row_data, FORMAT_STRING,   pData->m_strType         );
         pData->InsertRowData(DBStyle_DesDenisity_Key_cBaseType      ,map_row_data, FORMAT_STRING,   pData->m_strBaseType     );
         pData->InsertRowData(DBStyle_DesDenisity_Key_iShowPZ        ,map_row_data, FORMAT_INT   ,   pData->m_bShowPZ         );
         pData->InsertRowData(DBStyle_DesDenisity_Key_cPZName        ,map_row_data, FORMAT_STRING,   pData->m_strPZName       );
         pData->InsertRowData(DBStyle_DesDenisity_Key_cSavedUserID   ,map_row_data, FORMAT_STRING,   pData->m_strSavedUserID  );
         pData->InsertRowData(DBStyle_DesDenisity_Key_cSaveTime      ,map_row_data, FORMAT_STRING,   pData->m_strSaveTime     );
         pData->InsertRowData(DBStyle_DesDenisity_Key_cRemark        ,map_row_data, FORMAT_STRING,   pData->m_strRemark       );
       //pData->InsertRowData(DBStyle_DesDenisity_Key_cOrderNo       ,map_row_data, FORMAT_STRING,   pData->m_strOrderNo      );
         pData->InsertRowData(DBStyle_DesDenisity_Key_cPieceName     ,map_row_data, FORMAT_STRING,   pData->m_strPieceName    );
         pData->InsertRowData(DBStyle_DesDenisity_Key_cMatName       ,map_row_data, FORMAT_STRING,   pData->m_strMatName      );

         CString cUnit = _T("");
         cUnit.Format(_T("%.4f克%.2f转%.2f针"), pData->m_fPieceUnit, pData->m_fPieceTurns, pData->m_fPieceNeedle);
         pData->InsertRowData(DBStyle_DesDenisity_Key_fPieceUnit,  map_row_data, FORMAT_STRING, cUnit);//小片重量


         map_all_data.insert(make_pair(nValidCount,        map_row_data));
         //行数据插入所有数据中

         nValidCount++;
      }
   }

   return map_all_data;
}

#endif // USING_GRIDCTRL_MARK

CDBStyle_DensityFaceCodeData::CDBStyle_DensityFaceCodeData()
{

}

CDBStyle_DensityFaceCodeData::~CDBStyle_DensityFaceCodeData()
{
   m_lstFaceCode.Empty();
}

void CDBStyle_DensityFaceCodeData::ResetData()
{
   m_lstFaceCode.Empty();
}

void CDBStyle_DensityFaceCodeData::Copy(CDBStyle_DensityFaceCodeData * pData)
{
   ASSERT(NULL != pData);

   if (NULL == pData)
   {
      return;
   }
   m_nIDDensity = pData->m_nIDDensity;
   m_lstFaceCode.Copy(&pData->m_lstFaceCode);
}

void CDBStyle_DensityFaceCodeData::AddItem(CDBStyle_DesFaceCodeData * pData)
{
   m_lstFaceCode.AddItem(pData);
   if( 0 >= m_nIDDensity)
   {
      m_nIDDensity = pData->m_nIDDensity;
   }
}
