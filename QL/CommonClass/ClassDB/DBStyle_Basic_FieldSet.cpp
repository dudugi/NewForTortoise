#include "StdAfx.h"
#include "DBStyle_Basic_FieldSet.h"
#include "DBKeyDef.h"
#include "DBKeyDef_V.h"

IMPLEMENT_SERIAL(CDBStyle_Basic_FieldSetData,CDataMid,1)

std::shared_ptr<CDBStyle_Basic_FieldSetList> CDBStyle_Basic_FieldSetList::sm_inst;

CDBStyle_Basic_FieldSetData::CDBStyle_Basic_FieldSetData()
{
   ResetData();
}

CDBStyle_Basic_FieldSetData::~CDBStyle_Basic_FieldSetData()
{
}

void CDBStyle_Basic_FieldSetData::ResetData()
{
   m_strColID       = _T("");
   m_strDisplayName = _T("");
   m_bShow          = FALSE;
   m_nSortIndex     = 0;
   m_bOnPanel       = FALSE;

   SetDataType(DAT_STYLE_BASIC_FIELDSET);
}

void CDBStyle_Basic_FieldSetData::Copy( CDBStyle_Basic_FieldSetData *pData )
{
   ASSERT(pData!=NULL);
   CDataMid::Copy(pData);

   m_strColID       = pData->m_strColID       ;
   m_strDisplayName = pData->m_strDisplayName ;
   m_bShow          = pData->m_bShow          ;
   m_nSortIndex     = pData->m_nSortIndex     ;
   m_bOnPanel       = pData->m_bOnPanel       ;
}

BOOL CDBStyle_Basic_FieldSetData::GetAllDBInfo( CADOConn *pADOConn )
{
   ASSERT(pADOConn != NULL);

   m_strColID       = pADOConn->GetValueString(DBStyle_Basic_FieldSet_Key_cColID      );
   m_strDisplayName = pADOConn->GetValueString(DBStyle_Basic_FieldSet_Key_cDisplayName);
   m_bShow          = pADOConn->GetValueInt   (DBStyle_Basic_FieldSet_Key_bShow       );
   m_nSortIndex     = pADOConn->GetValueInt   (DBStyle_Basic_FieldSet_Key_nSortIndex  );
   m_bOnPanel       = pADOConn->GetValueInt   (DBStyle_Basic_FieldSet_Key_bOnPanel    );

   return TRUE;
}

CString CDBStyle_Basic_FieldSetData::GetInsertSQL() const
{
   CString strRet = _T("");

   strRet.Format(_T("insert into %s (%s,%s,%s,%s,%s) values('%s','%s','%d','%d','%d')"),
      DB_TABLE_STYLE_BASIC_FIELDSET,
      DBStyle_Basic_FieldSet_Key_cColID      ,
      DBStyle_Basic_FieldSet_Key_cDisplayName,
      DBStyle_Basic_FieldSet_Key_bShow       ,
      DBStyle_Basic_FieldSet_Key_nSortIndex  ,
      DBStyle_Basic_FieldSet_Key_bOnPanel    ,
      m_strColID      ,
      m_strDisplayName,
      m_bShow         ,
      m_nSortIndex    ,
      m_bOnPanel
      );

   return strRet;
}

CDBStyle_Basic_FieldSetList::CDBStyle_Basic_FieldSetList()
{

}

CDBStyle_Basic_FieldSetList::~CDBStyle_Basic_FieldSetList()
{

}

BOOL CDBStyle_Basic_FieldSetList::GetListFromDB(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);

   Empty();
   CString strSQL;
   strSQL.Format(_T("select * from %s order by %s"),DB_TABLE_STYLE_BASIC_FIELDSET,DBStyle_Basic_FieldSet_Key_nSortIndex);
   pADOConn->GetRecordSet(strSQL);
   Empty();
   CDBStyle_Basic_FieldSetData oData;
   while(!pADOConn->adoEOF())
   {
      oData.GetAllDBInfo(pADOConn);
      AddItem(&oData);

      pADOConn->MoveNext();
   }

   return TRUE;
}

std::vector<pair<CString/*Field*/,CString/*oldName*/>> g_mapSetField;

std::vector<std::pair<CString,CString>> & CDBStyle_Basic_FieldSetList::GetDefineBasicFieldInfo()
{
   if (g_mapSetField.empty())
   {
      g_mapSetField.push_back(make_pair(DBKuanShi_key_StyleNo          , _T("款号")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_StyleName        , _T("款式名称")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_cVersionNum      , _T("版单号")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_CreateTime       , _T("创建日期")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_dtMakingOrdTime  , _T("定版日期")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_cCusKuanHao      , _T("客户款号")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_KsYears          , _T("年份季度")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_cTheme           , _T("主题")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_KindName         , _T("款型")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_cPinMing         , _T("品类")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_cMainMaterial    , _T("主原料")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_cCusCode         , _T("客户")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_cEdition         , _T("版本")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_cSinglePerson    , _T("制单人")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_iFollow          , _T("关注")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_iShell           , _T("上/下架")));
      g_mapSetField.push_back(make_pair(DBVStyle_key_cKSMemo           , _T("备注")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_cState           , _T("状态")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_nSortIndex       , _T("展示排名")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_cBrand           , _T("品牌")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_cNeedleType      , _T("针型")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_cCustomField1    , _T("自定义字段1")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_cCustomField2    , _T("自定义字段2")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_cCustomField3    , _T("自定义字段3")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_cCustomField4    , _T("自定义字段4")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_cCustomField5    , _T("自定义字段5")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_cCustomField6    , _T("自定义字段6")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_cCustomField7    , _T("自定义字段7")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_cCustomField8    , _T("自定义字段8")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_cCustomField9    , _T("自定义字段9")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_cCustomField10   , _T("自定义字段10")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_dTotalCost    , _T("总成本")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_dTotalOffer   , _T("总报价")));
   }

   return g_mapSetField;
}

CDBStyle_Basic_FieldSetList * CDBStyle_Basic_FieldSetList::Instance()
{
   if(sm_inst.get() == 0)
      sm_inst = shared_ptr<CDBStyle_Basic_FieldSetList>(new CDBStyle_Basic_FieldSetList);

   return sm_inst.get();
}

