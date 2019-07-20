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
      g_mapSetField.push_back(make_pair(DBKuanShi_key_StyleNo          , _T("���")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_StyleName        , _T("��ʽ����")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_cVersionNum      , _T("�浥��")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_CreateTime       , _T("��������")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_dtMakingOrdTime  , _T("��������")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_cCusKuanHao      , _T("�ͻ����")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_KsYears          , _T("��ݼ���")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_cTheme           , _T("����")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_KindName         , _T("����")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_cPinMing         , _T("Ʒ��")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_cMainMaterial    , _T("��ԭ��")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_cCusCode         , _T("�ͻ�")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_cEdition         , _T("�汾")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_cSinglePerson    , _T("�Ƶ���")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_iFollow          , _T("��ע")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_iShell           , _T("��/�¼�")));
      g_mapSetField.push_back(make_pair(DBVStyle_key_cKSMemo           , _T("��ע")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_cState           , _T("״̬")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_nSortIndex       , _T("չʾ����")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_cBrand           , _T("Ʒ��")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_cNeedleType      , _T("����")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_cCustomField1    , _T("�Զ����ֶ�1")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_cCustomField2    , _T("�Զ����ֶ�2")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_cCustomField3    , _T("�Զ����ֶ�3")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_cCustomField4    , _T("�Զ����ֶ�4")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_cCustomField5    , _T("�Զ����ֶ�5")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_cCustomField6    , _T("�Զ����ֶ�6")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_cCustomField7    , _T("�Զ����ֶ�7")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_cCustomField8    , _T("�Զ����ֶ�8")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_cCustomField9    , _T("�Զ����ֶ�9")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_cCustomField10   , _T("�Զ����ֶ�10")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_dTotalCost    , _T("�ܳɱ�")));
      g_mapSetField.push_back(make_pair(DBKuanShi_key_dTotalOffer   , _T("�ܱ���")));
   }

   return g_mapSetField;
}

CDBStyle_Basic_FieldSetList * CDBStyle_Basic_FieldSetList::Instance()
{
   if(sm_inst.get() == 0)
      sm_inst = shared_ptr<CDBStyle_Basic_FieldSetList>(new CDBStyle_Basic_FieldSetList);

   return sm_inst.get();
}

