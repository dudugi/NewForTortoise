#include "stdafx.h"
#include "DBProAct.h"
#include "DBKeyDef_V.h"
#include "DBDef.h"
#include "DBStyleInfo_V.h"
#include "DBKeyDef.h"
#include "DBStyle_CheckRecords.h"
#include "DBProcessRecords.h"
#include "DBUserStylePermission.h"
#include "DBProSet_Style.h"
 

CDBProAct::CDBProAct(void)
{
}


CDBProAct::~CDBProAct(void)
{
}

int CDBProAct::CompareStyleProOrder(CADOConn * pADOConn,const CString & strStyleNo,int nCurProOrder)
{
   ASSERT(!strStyleNo.IsEmpty());
   CString strSQL = _T("");
   strSQL.Format(_T("select %s from %s where %s = '%s'"),DBVStyle_key_iGXSortID,DB_VIEW_KUANSHI,
      DBVStyle_key_cKuanhao,strStyleNo);

   pADOConn->GetRecordSet(strSQL);
   if (!pADOConn->adoEOF())
   {
      int nCurSortID = pADOConn->GetValueInt(DBVStyle_key_iGXSortID);
      if (nCurSortID < nCurProOrder)
      {
         return 1;
      }
      else if (nCurSortID == nCurProOrder)
      {
         return 0;
      }
      else if (nCurSortID > nCurProOrder)
      {
         return -1;
      }
   }

   return 1;
}

BOOL CDBProAct::HasMustRunningPro(CADOConn * pADOConn,const CString & strStyleNo,int nCurProOrder)
{
   CString strSQL = _T("");

   strSQL.Format(_T("select count(*) as num from  %s dt_2 \
      left join %s dt_3 on dt_3.%s = dt_2.%s\
   where dt_2.%s = '%s'\
      and dt_3.%s > ISNULL((select %s from %s where %s = '%s'),0)\
      and dt_3.%s < '%d' and %s = '%d'"),
      DB_TABLE_PROSET_STYLE,
      DB_TABLE_PROCESS,
      DBProcess_key_Name,DBProSet_Style_key_ProName,
      DBProSet_Style_key_StyleNo,strStyleNo,
      DBProcess_key_SortID,
      DBVStyle_key_iGXSortID,DB_VIEW_KUANSHI,DBVStyle_key_cKuanhao,strStyleNo,
      DBProcess_key_SortID,nCurProOrder,
      DBProcess_key_CarryOut,TRUE
      );
   pADOConn->GetRecordSet(strSQL);
   if (!pADOConn->adoEOF())
   {
      return 0 != pADOConn->GetValueInt(_T("num"));
   }


   return FALSE;
}

CDBProSearch::CDBProSearch()
{

}

CDBProSearch::~CDBProSearch()
{

}

std::vector<S_ProUserStyleInfo> CDBProSearch::GetUserProStyleInfo(CADOConn * pADOConn,const CString & strUserID,const CString & strGroup)
{
   std::vector<S_ProUserStyleInfo> vecRet;

   CString strSQL;
   strSQL.Format(_T("select %s,%s from %s\
   where %s in (\
      select %s from %s where %s = '%s' and (%s & 3 = 3 or %s & 3 = 3))\
      and ((%s = '%s' and %s = '%d') or \
      (%s = '%d' and %s in (select %s from %s where %s = '%s' and %s = '%d' or %s = '%s' and %s = '%d')))"),
      DBVStyle_key_cKuanhao,DBVStyle_key_cCheckState,
      DB_VIEW_KUANSHI,
      DBVStyle_key_cKuanhao,
      DBUserStylePermission_V_key_cKuanhao,DB_VIEW_USERSTYLE_PERMISSION,
      DBUserStylePermission_V_key_cUserID,strUserID,
      DBUserStylePermission_V_key_nPermission,DBUserStylePermission_V_key_FixPermission,
      DBVStyle_key_cGXPersonCode,strUserID,
      DBVStyle_key_cCheckState,CDBStyle_CheckRecordsData::en_CheckOut,
      DBVStyle_key_cCheckState,CDBStyle_CheckRecordsData::en_CheckIn,
      DBVStyle_key_cKuanhao,
      DBKuanshi_NextProInfo_V_key_cKuanhao, DB_VIEW_KUANSHI_NEXTPROINFO,
      DBKuanshi_NextProInfo_V_key_cNextUserID,strUserID,
      DBKuanshi_NextProInfo_V_key_bIsGroup,CDBProSet_StyleData::en_Person,
      DBKuanshi_NextProInfo_V_key_cNextUserID,strGroup,
      DBKuanshi_NextProInfo_V_key_bIsGroup,CDBProSet_StyleData::en_Group
      );

   pADOConn->GetRecordSet(strSQL);
   CString strStyleNo;
   int nCheckState = CDBStyle_CheckRecordsData::en_CheckIn;
   S_ProUserStyleInfo oneData;
   while (!pADOConn->adoEOF())
   {
      strStyleNo = pADOConn->GetValueString(DBVStyle_key_cKuanhao);
      nCheckState = pADOConn->GetValueInt(DBVStyle_key_cCheckState);
      oneData.m_strStyleNo = strStyleNo;
      oneData.m_nInfoType = nCheckState == CDBStyle_CheckRecordsData::en_CheckIn ? en_Pro_Prepare : en_Pro_Running;
      vecRet.push_back(oneData);

      pADOConn->MoveNext();
   }


   return vecRet;
}

std::vector<S_ProUserStyleInfo> CDBProSearch::GetUserProStyleInfoFinished(CADOConn * pADOConn,
   const CString & strUserID, UINT uSortID,const CString & strUserDuty,const CString & strTreeCode)
{
   std::vector<S_ProUserStyleInfo> vecRet;

   CString strSQLWhere;
   strSQLWhere.Format(_T(" ((%s = '%d' and %s = '%d') or (%s > '%d' and %s in (select distinct %s from %s where %s = '%s' )))"),
      DBVStyle_key_iGXSortID, uSortID,
      DBVStyle_key_cCheckState,CDBStyle_CheckRecordsData::en_CheckIn,
      DBVStyle_key_iGXSortID, uSortID,
      DBVStyle_key_cKuanhao,
      DBProcessRecords_Key_cCode,
      DB_TABLE_PROCESSRECORDS,
      DBProcessRecords_Key_cPersonCode, strUserID
      );
   CString strSQL;
   strSQL.Format(_T("select %s,%s from %s \
      where %s"), DBVStyle_key_cKuanhao, DBVStyle_key_cCheckState,
                    DB_VIEW_KUANSHI, strSQLWhere);

   if (-1 == strUserID.Find(_T("管理员")))
   {
      CString strFilterPermission = _T(""),strStyleNoInList;//权限过滤

      strStyleNoInList.Format(_T(" select %s from %s dt_usp where %s = '%s' \n\
 and (%s & %d = %d or %s & %d = %d) and ((convert(varchar,%s) >= convert(varchar,GETDATE())) or %s = '')\n\
 and ((%s <> 2) or (%s = 2 and exists\n\
 (SELECT %s FROM %s  dt_kn left join %s dt_vs on dt_vs.%s = dt_kn.%s \n\
 WHERE dt_kn.%s = dt_usp.%s and dt_vs.%s = '%d' \n\
 and ((dt_kn.%s = '%d' and '%s' = dt_kn.%s) or (dt_kn.%s = '%d' and dt_kn.%s = '%s'))))\n\
 or (%s = 2 and '%s' in (select distinct %s from %s where %s = dt_usp.%s and %s <> '%d')))"),
 DBUserStylePermission_V_key_cKuanhao,
 DB_VIEW_USERSTYLE_PERMISSION,
 DBUserStylePermission_V_key_cUserID,strUserID,
 DBUserStylePermission_V_key_nPermission,CDBUserStylePermissionData::en_Read,CDBUserStylePermissionData::en_Read,
 DBUserStylePermission_V_key_FixPermission,CDBUserStylePermissionData::en_Read,CDBUserStylePermissionData::en_Read,
 DBUserStylePermission_V_key_nPermissionTime,DBUserStylePermission_V_key_nPermissionTime,
 DBUserStylePermission_V_key_nUserType,DBUserStylePermission_V_key_nUserType,

 DBKuanshi_NextProInfo_V_key_cNextUserID,
 DB_VIEW_KUANSHI_NEXTPROINFO,
 DB_VIEW_KUANSHI,
 DBVStyle_key_cKuanhao,DBKuanshi_NextProInfo_V_key_cKuanhao,
 DBKuanshi_NextProInfo_V_key_cKuanhao,DBUserStylePermission_V_key_cKuanhao,
 DBVStyle_key_cCheckState,CDBStyle_CheckRecordsData::en_CheckIn,

 DBKuanshi_NextProInfo_V_key_bIsGroup,CDBProSet_StyleData::en_Person,
 strUserID,DBKuanshi_NextProInfo_V_key_cNextUserID,
 DBKuanshi_NextProInfo_V_key_bIsGroup,CDBProSet_StyleData::en_Group,
 DBKuanshi_NextProInfo_V_key_cNextUserID,strUserID,

 DBUserStylePermission_V_key_nUserType,
 strUserID,
 DBProcessRecords_Key_cPersonCode,
 DB_TABLE_PROCESSRECORDS,
 DBProcessRecords_Key_cCode,DBUserStylePermission_V_key_cKuanhao,
 DBProcessRecords_Key_iState,CDBProcessRecordsData::ASSIGN_STATE_UNBEG

 );

      if (strUserDuty == _T("部门主管"))
      {
         strStyleNoInList.AppendFormat(_T("\n\ union select distinct dt_ret.%s from %s dt_us \n\
 left join ( select dt_vs.%s,case when dt_vs.%s = '%d' then dt_vs.%s else dt_vkn.%s end as cNextUserID \n\
 ,case when dt_vs.%s = '%d' then '%d' else dt_vkn.%s end as bIsGroup \n\
 from %s dt_vs left join %s dt_vkn on dt_vkn.%s = dt_vs.%s) dt_ret on \n\
 ( isnull(dt_ret.bIsGroup,'%d') = '%d' and dt_ret.cNextUserID = dt_us.%s) or (dt_ret.bIsGroup = '%d' and dt_ret.cNextUserID = dt_us.%s) \n\
 where dt_us.%s = '%s' and dt_ret.%s is not null \n\
 union  select distinct dt_pr.%s from %s dt_us left join %s dt_pr on dt_pr.%s = dt_us.%s \n\
 where dt_us.%s = '%s' and dt_pr.%s is not null and dt_pr.%s <> '%d'"),
 DBVStyle_key_cKuanhao,DB_TABLE_PERSON,
 DBVStyle_key_cKuanhao,
 DBVStyle_key_cCheckState,CDBStyle_CheckRecordsData::en_CheckOut,
 DBVStyle_key_cCheckPerson,
 DBKuanshi_NextProInfo_V_key_cNextUserID,
 DBVStyle_key_cCheckState,CDBStyle_CheckRecordsData::en_CheckOut,
 CDBProSet_StyleData::en_Person,
 DBKuanshi_NextProInfo_V_key_bIsGroup,

 DB_VIEW_KUANSHI,
 DB_VIEW_KUANSHI_NEXTPROINFO,
 DBKuanshi_NextProInfo_V_key_cKuanhao, DBVStyle_key_cKuanhao,

 CDBProSet_StyleData::en_Person,CDBProSet_StyleData::en_Person,
 DBPerson_key_UserID,
 CDBProSet_StyleData::en_Group,
 DBPerson_key_cUserGroup,

 DBPerson_key_TreeCode,strTreeCode,
 DBVStyle_key_cKuanhao,

 DBProcessRecords_Key_cCode,
 DB_TABLE_PERSON,DB_TABLE_PROCESSRECORDS,
 DBProcessRecords_Key_cPersonCode,DBPerson_key_UserID,
 DBPerson_key_TreeCode,strTreeCode,
 DBProcessRecords_Key_cCode,
 DBProcessRecords_Key_iState,CDBProcessRecordsData::ASSIGN_STATE_UNBEG
 );
      }
      strFilterPermission.Format(_T("%s in (%s)"), DBVStyle_key_cKuanhao,strStyleNoInList );

      strSQL.Append(_T(" AND "));
      strSQL.Append(strFilterPermission);
   }



   pADOConn->GetRecordSet(strSQL);

   CString strStyleNo;
   int nCheckState = CDBStyle_CheckRecordsData::en_CheckIn;
   S_ProUserStyleInfo oneData;
   while (!pADOConn->adoEOF())
   {
      strStyleNo = pADOConn->GetValueString(DBVStyle_key_cKuanhao);
      nCheckState = pADOConn->GetValueInt(DBVStyle_key_cCheckState);
      oneData.m_strStyleNo = strStyleNo;
      oneData.m_nInfoType = nCheckState == CDBStyle_CheckRecordsData::en_CheckIn ? en_Pro_Prepare : en_Pro_Running;
      vecRet.push_back(oneData);

      pADOConn->MoveNext();
   }

   return vecRet;
}
