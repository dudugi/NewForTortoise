#include "StdAfx.h"
#include "DBKeyDef.h"
#include "DBStyleDescription.h"

std::shared_ptr<CDBStyleDescription> CDBStyleDescription::sm_inst;

CDBStyleDescription::CDBStyleDescription()
{
   ResetData();
}

CDBStyleDescription::~CDBStyleDescription()
{
   ResetData();
}
void CDBStyleDescription::ResetData()
{
   m_ID = -1;
   m_strKuanhao  = _T("");
   m_strDesrciption = _T("");
}

void CDBStyleDescription::Copy(CDBStyleDescription *pData)
{
   m_ID = pData->m_ID;
   m_strKuanhao = pData->m_strKuanhao;
   m_strDesrciption = pData->m_strDesrciption;
}

CString CDBStyleDescription::GetInsertSql()
{
   CString strSql;
   strSql.Format(_T("insert into %s (%s,%s) values('%s','%s');"),DB_TABLE_STYLE_DESCRIPTION,
      DBStyle_Description_Key_cKuanhao,DBStyle_Description_Key_cDescription,
      m_strKuanhao,m_strDesrciption.Left(500));
   return strSql;
}

CString CDBStyleDescription::GetUpdateSql()
{
   CString strSql;
   strSql.Format(_T("update %s set %s='%s' where %s='%s';"),DB_TABLE_STYLE_DESCRIPTION,
      DBStyle_Description_Key_cDescription,m_strDesrciption.Left(500),
      DBStyle_Description_Key_cKuanhao,m_strKuanhao);
   return strSql;
}

CString CDBStyleDescription::GetDeleteSql()
{
   CString strSql;
   strSql.Format(_T("delete from %s where %s='%s';"),DB_TABLE_STYLE_DESCRIPTION,
      DBStyle_Description_Key_cKuanhao,m_strKuanhao);
   return strSql;
}

CString CDBStyleDescription::GetDeleteByStyleNoSql(const CString & strStyleNo)
{
   CString strSql;
   strSql.Format(_T("delete from %s where %s='%s';"),DB_TABLE_STYLE_DESCRIPTION,
      DBStyle_Description_Key_cKuanhao,strStyleNo);
   return strSql;
}

CDBStyleDescription * CDBStyleDescription::Instance()
{
   if(sm_inst.get() == 0)
      sm_inst = shared_ptr<CDBStyleDescription>(new CDBStyleDescription);

   return sm_inst.get();
}

BOOL CDBStyleDescription::DoInsert(CADOConn *pADOConn)
{
   ASSERT(pADOConn!=NULL);
   CString strSql;
   strSql.Format(_T("if exists(select * from %s where %s = '%s')\
      begin\
      %s\
      end\
      else\
      begin\
      %s\
      end"),
     DB_TABLE_STYLE_DESCRIPTION,DBStyle_Description_Key_cKuanhao,m_strKuanhao,
     GetUpdateSql(),GetInsertSql());
   return pADOConn->ExecuteSQL(strSql);
}

BOOL CDBStyleDescription::DoUpdate(CADOConn *pADOConn)
{
   ASSERT(pADOConn!=NULL);
   return pADOConn->ExecuteSQL(GetUpdateSql());
}

BOOL CDBStyleDescription::DoDelete(CADOConn *pADOConn)
{
   ASSERT(pADOConn!=NULL);
   return pADOConn->ExecuteSQL(GetDeleteSql());
}



