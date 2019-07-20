#include "StdAfx.h"
#include "DBProcessInfo.h"
#include "DBKeyDef.h"
#include "DBKeyDef_V.h"
#include "DBKeyDef_Cust.h"

IMPLEMENT_SERIAL(CDBProcessInfoData,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBProcessInfoList,  CDataListMid, 1)

std::shared_ptr<CDBProcessInfoData> CDBProcessInfoData::sm_inst;
std::shared_ptr<CDBProcessInfoList> CDBProcessInfoList::sm_inst;

CDBProcessInfoData::CDBProcessInfoData(void)
{
	ResetData();
}


CDBProcessInfoData::~CDBProcessInfoData(void)
{
}

void CDBProcessInfoData::ResetData()
{
	m_nID = 0;
	m_strProName = _T("");//工序名称
	m_strProField = _T("");//工价字段
	m_strProItem = _T("");//工序项目
	m_strProChoose = _T("");//员工可选
	m_nSortID = 0;//排序ID
	m_nGetYarn = 0;
	m_nProCarryOut = 0;//是否必扫
   m_nCanEditCost = 0;//是否可编辑工价
	m_strProUpdate = _T("");//更新状态
	m_strPartLimit = _T("");//限制部门
	m_strPrevPro = _T("");//前道工序
	m_strProRemark = _T("");//备注

	m_strSysItem = _T("");
   m_nLimitHour = LimitHourDefafult;

   m_strZhipaiPerson = _T("");

   m_nOtherState = emGxOTM_Null;
   m_strDefaultGXGongjia = _T("");
   m_iTipPrice = 0;
   m_strBindRole = _T("");
   SetDataType(DAT_PROCESS);
}

void CDBProcessInfoData::Copy( CDBProcessInfoData *pData )
{
	ASSERT(pData != NULL);
	CDataMid::Copy(pData);

   m_nID          = pData->m_nID;
   m_strProName   = pData->m_strProName;//工序名称
   m_strProField  = pData->m_strProField;//工价字段
   m_strProItem   = pData->m_strProItem;//工序项目
   m_strProChoose = pData->m_strProChoose;//员工可选
   m_nSortID      = pData->m_nSortID;//排序ID
   m_nGetYarn     = pData->m_nGetYarn;
   m_nProCarryOut = pData->m_nProCarryOut;//是否必扫
   m_nCanEditCost = pData->m_nCanEditCost;//是否能编辑工价
   m_strProUpdate = pData->m_strProUpdate;//更新状态
   m_strPartLimit = pData->m_strPartLimit;//限制部门
   m_strPrevPro   = pData->m_strPrevPro;//前道工序
   m_strProRemark = pData->m_strProRemark;//备注
   m_strSysItem   = pData->m_strSysItem;
   m_nLimitHour   = pData->m_nLimitHour;
   m_strZhipaiPerson = pData->m_strZhipaiPerson;
   m_nOtherState  = pData->m_nOtherState;
   m_strDefaultGXGongjia = pData->m_strDefaultGXGongjia;
   m_iTipPrice = pData->m_iTipPrice;
   m_strBindRole = pData->m_strBindRole;
}

void CDBProcessInfoData::Swap( CDBProcessInfoData *pData )
{
	CDBProcessInfoData tmpData;
	tmpData.Copy(this);
	Copy(pData);
	pData->Copy(&tmpData);
}

CDBProcessInfoData * CDBProcessInfoData::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = shared_ptr<CDBProcessInfoData>(new CDBProcessInfoData);

	return sm_inst.get();
}

void CDBProcessInfoData::Serialize( CArchive& ar )
{
	 CDataMid::Serialize(ar);//父类函数

	 int nTagSize = 0;
	 CString strName;
	 int nNameSize;

	 ar.Flush();
	 if (ar.IsStoring())
	 {
		 MySerial.SaveDataInt64(ar,_T("PROPROID"),m_nID);
		 MySerial.SaveDataStr(ar, _T("PROCNAME"), m_strProName);
		 MySerial.SaveDataStr(ar, _T("PROFIELD"), m_strProField);
		 MySerial.SaveDataStr(ar, _T("PROCITEM"), m_strProItem);
		 MySerial.SaveDataStr(ar, _T("PROCHOSE"), m_strProChoose);
		 MySerial.SaveDataInt(ar, _T("PROSORID"), m_nSortID);
		 MySerial.SaveDataInt(ar, _T("PGETYARN"), m_nGetYarn);
		 MySerial.SaveDataInt(ar, _T("PROCARRY"), m_nProCarryOut);
		 MySerial.SaveDataStr(ar,_T("PROUPDAT"),m_strProUpdate);
		 MySerial.SaveDataStr(ar, _T("PROLIMIT"), m_strPartLimit);
		 MySerial.SaveDataStr(ar, _T("PROCPREV"), m_strPrevPro);
		 MySerial.SaveDataStr(ar, _T("PROREMAR"), m_strProRemark);
		 MySerial.SaveDataStr(ar, _T("PROSYSIT"), m_strSysItem);
       MySerial.SaveDataInt(ar,_T("OTHERSTATE"),m_nOtherState);
       MySerial.SaveDataStr(ar,_T("GXGONJIA"),m_strDefaultGXGongjia);//工序工价
		 nNameSize = 8;
		 strName = _T("DENDDEND");
		 ar << nNameSize;
		 ar << strName;
	 }
	 else
	 {
		 int nNumber = 0;
		 ar >> nNameSize;
		 ar >> strName;

		 if(strName.GetLength()!=nNameSize)
			 return;

		 while(strName != _T("DENDDEND"))
		 {
			 if(nNumber > 200)
			 {
				 return;
			 }
			 else if(strName == _T("PROPROID"))
			 {
				 ar >> nTagSize >> m_nID;
			 }
			 else if (strName == _T("PROCNAME"))
			 {
				 ar >>nTagSize >> m_strProName;
			 }
			 else if (strName == _T("PROFIELD"))
			 {
				 ar >>nTagSize >> m_strProField;
			 }
			 else if (strName == _T("PROCITEM"))
			 {
				ar >>nTagSize >> m_strProItem;
			 }
			 else if (strName == _T("PROCHOSE"))
			 {
				 ar >>nTagSize >> m_strProChoose;
			 }
			 else if (strName == _T("PROSORID"))				
			 {
				 ar >>nTagSize >> m_nSortID;
			 }
			 else if(strName == _T("PGETYARN"))
			 {
				 ar >> nTagSize >> m_nGetYarn;
			 }
			 else if (strName == _T("PROCARRY"))
			 {
				ar >>nTagSize >> m_nProCarryOut;
			 }
			 else if (strName == _T("PROUPDAT"))
			 {
				ar >>nTagSize >> m_strProUpdate;
			 }
			 else if (strName == _T("PROLIMIT"))
			 {
				 ar >>nTagSize >> m_strPartLimit;
			 }
			 else if (strName == _T("PROCPREV"))
			 {
				 ar >>nTagSize >> m_strPrevPro;
			 }
			 else if (strName == _T("PROREMAR"))
			 {
				 ar >>nTagSize >> m_strProRemark;
			 }
			 else if (strName == _T("PROSYSIT"))
			 {
				 ar >> nTagSize >> m_strSysItem;
			 }
          else if (strName == _T("GXGONJIA"))
          {
             ar >> nTagSize >> m_strDefaultGXGongjia;
          }
          else if (strName == _T("OTHERSTATE"))
          {
             int nTemp;
             ar >>nTagSize >> nTemp;
             m_nOtherState = (EM_OTHER_STATE_MOD)nTemp;
          }
			 else
			 {
				 ar >> nTagSize;
				 ar.Flush();
				 ar.GetFile()->Seek(nTagSize, CFile::current);
			 }
			 /////////////////////////////////////////////
			 strName = _T("");
			 ar >> nNameSize;
			 ar >> strName;
			 if(strName.GetLength() != nNameSize)
				 return;
			 nNumber++;
		 }
	 }

}

CString CDBProcessInfoData::SetDBEquals_Log(CDBProcessInfoData &pOldData)
{
   CString strActLog = _T("");
   if (m_strProName != pOldData.m_strProName)//工序名称
   {
      CString strProName;
      if (m_strProName.IsEmpty())
      {
         strProName = _T("空值");
      }
      strProName = m_strProName;
      strActLog += _T("工序名称:") + strProName + _T(",");
   }
   if (m_strProItem != pOldData.m_strProItem)//工序项目
   {
      CString strProItem;
      if (m_strProItem.IsEmpty())
      {
         strProItem = _T("空值");
      }
      strProItem = m_strProItem;
      strActLog += _T("工序项目:") + strProItem + _T(",");
   }
   if (m_strProChoose != pOldData.m_strProChoose)//员工可选
   {
      CString strProChoose;
      if (m_strProChoose.IsEmpty())
      {
         strProChoose = _T("空值");
      }
      strProChoose = m_strProChoose;
      strActLog += _T("员工可选:") + strProChoose + _T(",");
   }
   if (m_nSortID != pOldData.m_nSortID)//排序ID
   {
      CString strSortID;
      strSortID.Format(FORMAT_INT,m_nSortID);
      if (strSortID.IsEmpty())
      {
         strSortID = _T("空值");
      }
      strActLog += _T("排序ID:") + strSortID + _T(",");
   }
   if (m_nGetYarn != pOldData.m_nGetYarn)//是否领用纱线
   {
      CString strGetYarn;
      strGetYarn.Format(FORMAT_INT,m_nGetYarn);
      if (strGetYarn.IsEmpty())
      {
         strGetYarn = _T("空值");
      }
      strActLog += _T("是否领用纱线:") + strGetYarn + _T(",");
   }
   if (m_nProCarryOut != pOldData.m_nProCarryOut)//是否必扫
   {
      CString strProCarryOut;
      strProCarryOut.Format(FORMAT_INT,m_nProCarryOut);
      if (strProCarryOut.IsEmpty())
      {
         strProCarryOut = _T("空值");
      }
      strActLog += _T("是否必扫:") + strProCarryOut + _T(",");
   }
   if (m_nCanEditCost != pOldData.m_nCanEditCost)//是否可以编辑工价
   {
      CString strCanEditCost;
      strCanEditCost.Format(FORMAT_INT,m_nCanEditCost);
      if (strCanEditCost.IsEmpty())
      {
         strCanEditCost = _T("空值");
      }
      strActLog += _T("是否可以编辑工价:") + strCanEditCost + _T(",");
   }
   if (m_strProUpdate != pOldData.m_strProUpdate)//更新状态
   {
      CString strProUpdate;
      if (m_strProUpdate.IsEmpty())
      {
         strProUpdate = _T("空值");
      }
      strProUpdate = m_strProUpdate;
      strActLog += _T("更新状态:") + strProUpdate + _T(",");
   }
   if (m_strPartLimit != pOldData.m_strPartLimit)//限制部门
   {
      CString strPartLimit;
      if (m_strPartLimit.IsEmpty())
      {
         strPartLimit = _T("空值");
      }
      strPartLimit = m_strPartLimit;
      strActLog += _T("限制部门:") + strPartLimit + _T(",");
   }
   if (m_strPrevPro != pOldData.m_strPrevPro)//前道工序
   {
      CString strPrevPro;
      if (m_strPrevPro.IsEmpty())
      {
         strPrevPro = _T("空值");
      }
      strPrevPro = m_strPrevPro;
      strActLog += _T("前道工序:") + strPrevPro + _T(",");
   }
   if (m_strProRemark != pOldData.m_strProRemark)//备注
   {
      CString strProRemark;
      if (m_strProRemark.IsEmpty())
      {
         strProRemark = _T("空值");
      }
      strProRemark = m_strProRemark;
      strActLog += _T("备注:") + strProRemark + _T(",");
   }
   if (m_strSysItem != pOldData.m_strSysItem)//绑定到对应工序的字符串
   {
      CString strSysItem;
      if (m_strSysItem.IsEmpty())
      {
         strSysItem = _T("空值");
      }
      strSysItem = m_strSysItem;
      strActLog += _T("绑定到对应工序:") + strSysItem + _T(",");
   }
   if (m_nLimitHour != pOldData.m_nLimitHour)//工序限制的时长（用于超时警报）
   {
      CString strLimitHour;
      strLimitHour.Format(FORMAT_INT,m_nLimitHour);
      if (strLimitHour.IsEmpty())
      {
         strLimitHour = _T("空值");
      }
      strActLog += _T("限制时长:") + strLimitHour + _T(",");
   }
   if (m_strZhipaiPerson != pOldData.m_strZhipaiPerson)//对应工序的默认指派人
   {
      CString strZhipaiPerson;
      strZhipaiPerson = m_strZhipaiPerson;
      if (m_strZhipaiPerson.IsEmpty())
      {
         strZhipaiPerson = _T("空值");
      }
      
      strActLog += _T("默认指派人:") + strZhipaiPerson + _T(",");
   }
   //默认工序工价   add anjie by 2018/11/20
   if (m_strDefaultGXGongjia != pOldData.m_strDefaultGXGongjia)//工序限制的时长（用于超时警报）
   {
      CString strDefaultGXGongjia;
      strDefaultGXGongjia.Format(FORMAT_STRING,m_strDefaultGXGongjia);
      if (strDefaultGXGongjia.IsEmpty())
      {
         strDefaultGXGongjia = _T("空值");
      }
      strActLog += _T("默认工序工价:")+m_strDefaultGXGongjia + _T(",");
   }
   if (m_strBindRole != pOldData.m_strBindRole)
   {
      CString strBindRole = m_strBindRole;
      if (strBindRole.IsEmpty())
      {
         strBindRole = _T("空值");
      }
      strActLog += _T("默认绑定角色:")+strBindRole;
   }
   return strActLog;
}

BOOL CDBProcessInfoData::GetAllDBInfo( CADOConn *pADOConn )
{
	ASSERT(pADOConn != NULL);
	BOOL bRet = TRUE;

	if (NULL == pADOConn)
	{
		bRet = FALSE;
	}
	else
	{
      m_nID          = _ttoi(pADOConn->GetValueString(DBProcess_Key_ID));
      m_strProName   = pADOConn->GetValueString(DBProcess_key_Name);
      m_strProField  = pADOConn->GetValueString(DBProcess_key_Field);
      m_strProItem   = pADOConn->GetValueString(DBProcess_key_Item);
      m_strProChoose = pADOConn->GetValueString(DBProcess_key_Choose);
      m_nSortID      = _ttoi(pADOConn->GetValueString(DBProcess_key_SortID));
      m_nGetYarn     = _ttoi(pADOConn->GetValueString(DBProcess_Key_GetYarn));
      m_nProCarryOut = _ttoi(pADOConn->GetValueString(DBProcess_key_CarryOut));
      m_nCanEditCost = _ttoi(pADOConn->GetValueString(DBProcess_key_EditCost));
      m_strProUpdate = pADOConn->GetValueString(DBProcess_key_Update);
      m_strPartLimit = pADOConn->GetValueString(DBProcess_key_PartLimt);
      m_strPrevPro   = pADOConn->GetValueString(DBProcess_key_PrevPro);
      m_strProRemark = pADOConn->GetValueString(DBProcess_key_Remark);
      m_strSysItem   = pADOConn->GetValueString(DBProcess_key_SysItem);
      m_iTipPrice    = pADOConn->GetValueInt(DBProcess_key_iTipPrice);

      CString strLimitHour = pADOConn->GetValueString(DBProcess_key_LimitHour);
      if (strLimitHour.IsEmpty())
         m_nLimitHour = LimitHourDefafult;
      else
         m_nLimitHour = _ttoi(strLimitHour);

      m_strZhipaiPerson = pADOConn->GetValueString(DBProcess_key_cZhipaiPerson); 
      m_nOtherState = (EM_OTHER_STATE_MOD)pADOConn->GetValueInt(DBProcess_key_nOtherState);
      m_strDefaultGXGongjia = pADOConn->GetValueString(DBProcess_key_cGXGongJia);//默认工序工价，待替换
      m_strBindRole = pADOConn->GetValueString(DBProcess_key_cBindRole);
		bRet = TRUE;
	}

	return bRet;
}

BOOL CDBProcessInfoData::InsertAllDBInfoByName( CADOConn *pADOConn )
{
	ASSERT(pADOConn != NULL);
	ASSERT(!m_strProName.IsEmpty());
	BOOL bRet = TRUE;

	CString strSQL = _T("");
   //                               1  2  3  4  5  6  7  8  9  10 11 12 13 14
   strSQL.Format(_T("insert into %s(%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s)\
                    values('%s','%s','%s','%s', 1 + (select max(%s) from %s ),\
                    '%d','%d','%d','%s','%s',\
                    '%s','%s','%s','%d','%s','%d','%s','%d','%s')"),
                    DB_TABLE_PROCESS,
                    DBProcess_key_Name       ,//1
                    DBProcess_key_Field      ,//2
                    DBProcess_key_Item       ,//3
                    DBProcess_key_Choose     ,//4
                    DBProcess_key_SortID     ,//5
                    DBProcess_Key_GetYarn    ,//6
                    DBProcess_key_CarryOut   ,//7
                    DBProcess_key_EditCost   ,//8
                    DBProcess_key_Update     ,//9
                    DBProcess_key_PartLimt   ,//10
                    DBProcess_key_PrevPro    ,//11
                    DBProcess_key_Remark     ,//12
                    DBProcess_key_SysItem    ,//13
                    DBProcess_key_LimitHour  ,//14
                    DBProcess_key_cZhipaiPerson,
                    DBProcess_key_nOtherState,
                    DBProcess_key_cGXGongJia,//默认工价
                    DBProcess_key_iTipPrice,
                    DBProcess_key_cBindRole,
                    m_strProName             ,//1
                    m_strProField            ,//2
                    m_strProItem             ,//3
                    m_strProChoose           ,//4
                    DBProcess_key_SortID,DB_TABLE_PROCESS,//5
                    m_nGetYarn               ,//6
                    m_nProCarryOut           ,//7
                    m_nCanEditCost           ,//8
                    m_strProUpdate           ,//9
                    m_strPartLimit           ,//10
                    m_strPrevPro             ,//11
                    m_strProRemark           ,//12
                    m_strSysItem             ,//13
                    m_nLimitHour             ,//14
                    m_strZhipaiPerson        ,
                    m_nOtherState            ,
                    m_strDefaultGXGongjia,
                    m_iTipPrice,
                    m_strBindRole
                    );
	if (pADOConn->ExecuteSQL(strSQL))
	{
		bRet = TRUE;
	}
	else
	{
		bRet = FALSE;
	}

	return bRet;
}

BOOL CDBProcessInfoData::UpdateAllDBInfoByName( CADOConn *pADOConn,CString strOldName )
{
	ASSERT(pADOConn != NULL);

	m_strProName.Trim();
	ASSERT(!m_strProName.IsEmpty());

	BOOL bRet = TRUE;

	CString strSQL = _T("");
   //                              1         2       3       4       5
   strSQL.Format(_T("update %s set %s = '%s',%s='%s',%s='%s',%s='%s',%s='%d',\
                                   %s = '%d',%s='%d',%s='%d',%s='%s',%s='%s',\
                                   %s = '%s',%s='%s',%s ='%d',%s='%s',%s='%d' \
                                   %s = '%s',%s = '%d',%s = '%s' where %s='%s'"),DB_TABLE_PROCESS,
      DBProcess_key_Name      ,m_strProName     ,//1
      DBProcess_key_Field     ,m_strProField    ,//2
      DBProcess_key_Item      ,m_strProItem     ,//3
      DBProcess_key_Choose    ,m_strProChoose   ,//4
      DBProcess_key_SortID    ,m_nSortID        ,//5
      DBProcess_Key_GetYarn   ,m_nGetYarn       ,//6
      DBProcess_key_CarryOut  ,m_nProCarryOut   ,//7
      DBProcess_key_EditCost  ,m_nCanEditCost   ,//8
      DBProcess_key_Update    ,m_strProUpdate   ,//9
      DBProcess_key_PartLimt  ,m_strPartLimit   ,//10
      DBProcess_key_PrevPro   ,m_strPrevPro     ,//11
      DBProcess_key_Remark    ,m_strProRemark   ,//12
      DBProcess_key_LimitHour ,m_nLimitHour     ,//13
      DBProcess_key_cZhipaiPerson,m_strZhipaiPerson,
      DBProcess_key_nOtherState, m_nOtherState,
      DBProcess_key_cGXGongJia,m_strDefaultGXGongjia,
      DBProcess_key_iTipPrice,m_iTipPrice,
      DBProcess_key_cBindRole,m_strBindRole,
      DBProcess_key_Name      ,strOldName        //14
      );

	if (pADOConn->ExecuteSQL(strSQL))
	{
		bRet = TRUE;
	}
	else
	{
		bRet = FALSE;
	}


	return bRet;
}

BOOL CDBProcessInfoData::UpdateAllDBInfoByID( CADOConn *pADOConn )
{
	ASSERT(pADOConn != NULL);

	m_strProName.Trim();
	ASSERT(!m_strProName.IsEmpty());

	BOOL bRet = TRUE;

   CString strSQL = _T("");
   //                              1        2       3       4       5
   strSQL.Format(_T("update %s set %s ='%s',%s='%s',%s='%s',%s='%s',%s='%d',\
                                   %s ='%d',%s='%d',%s='%d',%s='%s',%s='%s',\
                                   %s ='%s',%s='%s',%s='%d',%s='%s',%s='%d', \
                                   %s ='%s',%s ='%d',%s = '%s' where %s='%lld'"),DB_TABLE_PROCESS,
                                   DBProcess_key_Name      ,m_strProName     ,//1
                                   DBProcess_key_Field     ,m_strProField    ,//2
                                   DBProcess_key_Item      ,m_strProItem     ,//3
                                   DBProcess_key_Choose    ,m_strProChoose   ,//4
                                   DBProcess_key_SortID    ,m_nSortID        ,//5
                                   DBProcess_Key_GetYarn   ,m_nGetYarn       ,//6
                                   DBProcess_key_CarryOut  ,m_nProCarryOut   ,//7
                                   DBProcess_key_EditCost  ,m_nCanEditCost   ,//8
                                   DBProcess_key_Update    ,m_strProUpdate   ,//9
                                   DBProcess_key_PartLimt  ,m_strPartLimit   ,//10
                                   DBProcess_key_PrevPro   ,m_strPrevPro     ,//11
                                   DBProcess_key_Remark    ,m_strProRemark   ,//12
                                   DBProcess_key_LimitHour ,m_nLimitHour     ,//13
                                   DBProcess_key_cZhipaiPerson,m_strZhipaiPerson,
                                   DBProcess_key_nOtherState, m_nOtherState,
                                   DBProcess_key_cGXGongJia, m_strDefaultGXGongjia,//默认工序工价
                                   DBProcess_key_iTipPrice,m_iTipPrice,
                                   DBProcess_key_cBindRole,m_strBindRole,
                                   DBProcess_Key_ID        ,m_nID             //14
                                   );

	if (pADOConn->ExecuteSQL(strSQL))
	{
		bRet = TRUE;
	}
	else
	{
		bRet = FALSE;
	}


	return bRet;
}

BOOL CDBProcessInfoData::DelAllDBInfoByName( CADOConn *pADOConn )
{
	ASSERT(pADOConn != NULL);

	m_strProName.Trim();
	ASSERT(!m_strProName.IsEmpty());

	BOOL bRet = TRUE;

	CString strSQL = _T("");
	strSQL.Format(_T("delete from %s where %s='%s'"),
      DB_TABLE_PROCESS,DBProcess_key_Name,m_strProName);

	if (pADOConn->ExecuteSQL(strSQL))
	{
		bRet = TRUE;
	}
	else
	{
		bRet = FALSE;
	}
	return bRet;
}

//验证是否包含有某一个状态（参数如果是组合状态只需拥有一种返回真）		by WangZY 2018/09/13
BOOL CDBProcessInfoData::TestGXIncludeOtherState(EM_OTHER_STATE_MOD emStateInclude) const
{
   return TestGXIncludeOtherState(emStateInclude,m_nOtherState);
}

BOOL CDBProcessInfoData::TestGXIncludeOtherState(EM_OTHER_STATE_MOD emStateInclude,EM_OTHER_STATE_MOD emCurState) const
{
   if (emGxOTM_Null == emStateInclude)
   {
      return !(emCurState);
   }
   else
   {
      BOOL bRet = emCurState&emStateInclude;

      return bRet;
   }
}

//验证是否拥有某个状态（参数如果是组合状态必须全部拥有返回真）		by WangZY 2018/09/13
BOOL CDBProcessInfoData::TestGXOtherState(EM_OTHER_STATE_MOD emStateTest)
{
   if (emGxOTM_Null == emStateTest)
   {
      return !(m_nOtherState);
   }
   else
   {
      BOOL bRet = !((m_nOtherState&emStateTest)^emStateTest);

      return bRet;
   }
}

//移除某个状态		by WangZY 2018/09/13
BOOL CDBProcessInfoData::RemoveOtherState(EM_OTHER_STATE_MOD emStateRemove)
{
   if (emGxOTM_Null == emStateRemove)
   {
      return FALSE;
   }
   else
   {
      m_nOtherState = (EM_OTHER_STATE_MOD)(m_nOtherState&(~emStateRemove));

      return TRUE;
   }
}

//添加某个状态		by WangZY 2018/09/13
BOOL CDBProcessInfoData::AddOtherState(EM_OTHER_STATE_MOD emStateAdd)
{
   if (emGxOTM_Null == emStateAdd)
   {
      m_nOtherState = emGxOTM_Null;
   }
   else
   {
      m_nOtherState = (EM_OTHER_STATE_MOD)(m_nOtherState|emStateAdd);
   }
   
   return TRUE;
}

BOOL CDBProcessInfoData::GetGongXuSort(CADOConn* pADOConn,__out map<int,CString>& map_gx_sort)
{
   map_gx_sort.clear();
   ASSERT(NULL != pADOConn);
   CString strSql = _T("");
   strSql.Format(_T("select %s,%s from %s order by %s;"),
      DBProcess_key_Name,DBProcess_key_SortID,
      DB_TABLE_PROCESS,
      DBProcess_key_SortID);
   pADOConn->GetRecordSet(strSql);
   while(!pADOConn->adoEOF())
   {
      int iSortID = pADOConn->GetValueInt(_T("iSortID"));
      CString strGxName = pADOConn->GetValueString(_T("cGXName"));
      map_gx_sort.insert(make_pair(iSortID,strGxName));
      pADOConn->MoveNext();
   }
   return TRUE;
}

BOOL CDBProcessInfoData::GetAllDBInfoByName( CADOConn *pADOConn )
{
   ASSERT(pADOConn != NULL);

   m_strProName.Trim();
   ASSERT(!m_strProName.IsEmpty());
   BOOL bRet = FALSE;
   CString strSQL = _T("");
   strSQL.Format(_T("select * from %s where %s = '%s'"),DB_TABLE_PROCESS,DBProcess_key_Name,m_strProName);
   pADOConn->GetRecordSet(strSQL);
   while(!pADOConn->adoEOF())
   {
      bRet = TRUE;
      GetAllDBInfo(pADOConn);
      pADOConn->MoveNext();
   }

   return bRet;
}

CDBProcessInfoList::CDBProcessInfoList()
{

}

CDBProcessInfoList::~CDBProcessInfoList()
{

}

CDBProcessInfoData* CDBProcessInfoList::GetItem( int nIndex )
{
	if (nIndex<0||nIndex>=GetCount())
		return NULL;
	return (CDBProcessInfoData*)GetAt(FindIndex(nIndex));
}

CDBProcessInfoData* CDBProcessInfoList::GetItemByName( CString strName )
{
	CDBProcessInfoData * pItem = NULL;
	strName.Trim();
	if (!strName.IsEmpty())
	{
		for(int i=0;i< GetCount();i++)
		{
			CDBProcessInfoData * pObject = GetItem(i);
			if(strName==pObject->m_strProName)
			{
				pItem = pObject;
				break;
			}
		}
	}

	return pItem;
}

CDBProcessInfoData* CDBProcessInfoList::GetItemByID( INT64 nID )
{
	CDBProcessInfoData * pItem = NULL;
	
	if (0 != nID)
	{
		for(int i=0;i< GetCount();i++)
		{
			CDBProcessInfoData * pObject = GetItem(i);
			if(nID==pObject->m_nID)
			{
				pItem = pObject;
				break;
			}
		}
	}

	return pItem;
}

//根据排序ID取Item		by WangZY 2018/09/14
CDBProcessInfoData* CDBProcessInfoList::GetItemBySortId(int nSortId)
{
   CDBProcessInfoData * pItem = nullptr;
   int nCount = GetCount();
   for(int i=0;i< nCount; i++)
   {
      CDBProcessInfoData * pObject = GetItem(i);
      if(nSortId==pObject->m_nSortID)
      {
         pItem = pObject;
         break;
      }
   }
   
   return pItem;
}

CDBProcessInfoData* CDBProcessInfoList::GetSysItem(CDBProcessRecordsData::Assign_Default_ProID nProID)
{
   CDBProcessInfoData * pItem = nullptr;
   int nCount = GetCount();
   for(int i=0;i< nCount; i++)
   {
      CDBProcessInfoData * pObject = GetItem(i);
      if(nProID==pObject->m_strSysItem)
      {
         pItem = pObject;
         break;
      }
   }

   return pItem;
}

CDBProcessInfoData* CDBProcessInfoList::GetItemByRole(const CString & strRole)
{
   CDBProcessInfoData * pItem = nullptr;
   int nCount = GetCount();
   for(int i=0;i< nCount; i++)
   {
      CDBProcessInfoData * pObject = GetItem(i);
      if(strRole==pObject->m_strBindRole)
      {
         pItem = pObject;
         break;
      }
   }

   return pItem;
}

int CDBProcessInfoList::GetIndexByName( CString strName )
{
	int nSel = -1;
	strName.Trim();
	if (!strName.IsEmpty())
	{
		for(int i=0;i< GetCount();i++)
		{
			CDBProcessInfoData * pObject = GetItem(i);
			if(strName==pObject->m_strProName)
			{
				nSel = i;
				break;
			}
		}
	}

	return nSel;
}

int CDBProcessInfoList::GetIndexByID( INT64 nID )
{
	int nSel = -1;


	for(int i=0;i< GetCount();i++)
	{
		CDBProcessInfoData * pObject = GetItem(i);
		if(nID==pObject->m_nID)
		{
			nSel = i;
			break;
		}
	}
	
	return nSel;
}

void CDBProcessInfoList::AddItem( CDBProcessInfoData* pItem )
{
	CDBProcessInfoData*pData = new CDBProcessInfoData;
	pData->Copy(pItem);
	AddTail(pData);
}

void CDBProcessInfoList::DeleteItem( int nIndex )
{
	if (nIndex<0||nIndex>GetCount())
		return;
	CDBProcessInfoData *pObject=(CDBProcessInfoData*)GetItem(nIndex);
	delete pObject;
	pObject=NULL;
	RemoveAt(FindIndex(nIndex));
}

void CDBProcessInfoList::DeleteItemByName( CString strName )
{
	strName.Trim();
	if (!strName.IsEmpty())
	{
		for(int i=0;i< GetCount();i++)
		{
			CDBProcessInfoData * pObject = GetItem(i);
			if(strName==pObject->m_strProName)
			{
				DeleteItem(i);
				break;
			}
		}
	}
}

void CDBProcessInfoList::SortBySortID()
{
	int nCount = GetCount();
	for (int i = 0;i < nCount;i++)
	{
		for (int j = i;j<nCount;j++)
		{
			auto pi = GetItem(i);
			auto pj = GetItem(j);
			if(pj->m_nSortID < pi->m_nSortID)
			{
				pi->Swap(pj);
			}
		}
	}
}

void CDBProcessInfoList::GetListFromDB(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);

	Empty();
	CString strSQL = _T("");
	strSQL.Format(_T("select * from %s  order by %s"),
      DB_TABLE_PROCESS,DBProcess_key_SortID);
	pADOConn->GetRecordSet(strSQL);
	while (!pADOConn->adoEOF())
	{
		CDBProcessInfoData oData;
		if(oData.GetAllDBInfo(pADOConn))
		{
			AddItem(&oData);
		}
		pADOConn->MoveNext();
	}
}

//************************************
// Method:    获取是否可以编辑工价
// Author:    wuZhiHua
// Date : 	  2018/03/26
// Access:    public 
// Returns:   BOOL
// Parameter: CADOConn * pADOConn
// Parameter: std::map<CString
// Parameter: bool> & mapProNameCanEditCost
//************************************
BOOL CDBProcessInfoList::GetCanEditCostMap(CADOConn *pADOConn , std::map<CString , bool> &mapProNameCanEditCost)
{
   CString strSQL = _T("");
   strSQL.Format(_T("select %s , %s from %s") , DBProcess_key_Name , DBProcess_key_EditCost , DB_TABLE_PROCESS);
   mapProNameCanEditCost.clear();

   BOOL ret = pADOConn->GetRecordSet(strSQL);
	while (!pADOConn->adoEOF())
	{
      int nCanEdit = 0;
      CString strName;
      strName = pADOConn->GetValueString(DBProcess_key_Name);
      nCanEdit = _ttoi(pADOConn->GetValueString(DBProcess_key_EditCost));

      mapProNameCanEditCost[strName] = nCanEdit == 0 ? false : true;
		pADOConn->MoveNext();
	}
   return ret;
}


CDBProcessInfoList * CDBProcessInfoList::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = shared_ptr<CDBProcessInfoList>(new CDBProcessInfoList);

	return sm_inst.get();
}

BOOL CDBProcessInfoList::GetTipPriceFlag(CADOConn* pADo,CString strGXName)
{
   ASSERT(pADo != NULL);
   if (strGXName.IsEmpty())
      return FALSE;

   BOOL bFlag = FALSE;
   CString strSql;
   strSql.Format(_T("select iTipPrice from Gongxu where cGXName = '%s';"),strGXName);
   pADo->GetRecordSet(strSql);
   if (!pADo->adoEOF())
   {
      bFlag = pADo->GetValueInt(_T("iTipPrice"))==1?TRUE:FALSE;
   }
   return bFlag;
}

#ifdef USING_GRIDCTRL_MARK

MAP_GridCtrl_AllData CDBProcessInfoList::CreateGridData()
{
	MAP_GridCtrl_AllData map_all_data;
	int nIndex = 0,nCount = GetCount();
	int nValidCount = 1;
	for (nIndex = 0;nIndex < nCount;nIndex++)
	{
		auto * pData = GetItem(nIndex);
		if (NULL != pData)
		{
			MAP_GridCtrl_RowData map_row_data;

         pData->InsertRowData(DBProcess_Key_ID           ,map_row_data, CB_enum_FieldData_Int, CB_enum_FieldCtrl_Text,FORMAT_INT   ,pData->m_nID                         );
         pData->InsertRowData(DBProcess_key_Name         ,map_row_data,FORMAT_STRING   ,pData->m_strProName                  );
         //pData->InsertRowData(DBProcess_key_Field      ,map_row_data,FORMAT_STRING   ,pData->m_strProField                 );
         pData->InsertRowData(DBProcess_key_Item         ,map_row_data,FORMAT_STRING   ,pData->m_strProItem                  );
         pData->InsertRowData(DBProcess_key_Choose       ,map_row_data,FORMAT_STRING   ,pData->m_strProChoose                );
         pData->InsertRowData(DBProcess_key_SortID       ,map_row_data,CB_enum_FieldData_Int,CB_enum_FieldCtrl_Text,FORMAT_INT,pData->m_nSortID);
         pData->InsertRowData(DBProcess_Key_GetYarn      ,map_row_data,FORMAT_INT   ,pData->m_nGetYarn                    );
         pData->InsertRowData(DBProcess_key_CarryOut     ,map_row_data,FORMAT_INT   ,pData->m_nProCarryOut                );
         pData->InsertRowData(DBProcess_key_Update       ,map_row_data,FORMAT_STRING   ,pData->m_strProUpdate                );
         pData->InsertRowData(DBProcess_key_PartLimt     ,map_row_data,FORMAT_STRING   ,pData->m_strPartLimit                );
         pData->InsertRowData(DBProcess_key_PrevPro      ,map_row_data,FORMAT_STRING   ,pData->m_strPrevPro                  );
         pData->InsertRowData(DBProcess_key_Remark       ,map_row_data,FORMAT_STRING   ,pData->m_strProRemark                );
         pData->InsertRowData(DBProcess_key_SysItem      ,map_row_data,FORMAT_STRING   ,pData->m_strSysItem                  );
         pData->InsertRowData(DBProcess_key_LimitHour    ,map_row_data,FORMAT_INT, CB_enum_FieldData_Int, CB_enum_FieldCtrl_Text ,pData->m_nLimitHour                  );
         pData->InsertRowData(DBProcess_key_cZhipaiPerson    ,map_row_data,FORMAT_STRING   ,pData->m_strZhipaiPerson                  );
         pData->InsertRowData(DBProcess_key_cGXGongJia,map_row_data,FORMAT_STRING   ,pData->m_strDefaultGXGongjia        );//默认工序工价
         pData->InsertRowData(DBProcess_key_iTipPrice,map_row_data,FORMAT_STRING   ,pData->m_iTipPrice==1?_T("是"):_T("否")        );//提示修改工价
         pData->InsertRowData(DBProcess_key_cBindRole,map_row_data,FORMAT_STRING   ,pData->m_strBindRole);//绑定的角色
			map_all_data.insert(make_pair(nValidCount,map_row_data));

			nValidCount++;
		}
	}

	return map_all_data;
}

#endif // USING_GRIDCTRL_MARK



