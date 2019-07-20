#include "StdAfx.h"
#include "DBPinZhongSetting.h"


CDBPinZhongSetting::CDBPinZhongSetting(void)
{
	ResetData();
}

CDBPinZhongSetting::~CDBPinZhongSetting(void)
{
}

void CDBPinZhongSetting::ResetData()
{
	m_ID = -1;
	m_cCate = _T("");		
	m_cChenfen = _T("");	
   m_strfSalePrice      = _T("");//销售单价 2位小数
   m_cZhiXingBiaoZun = _T("");	//执行标准
   m_strfFahuoSunhao    = _T("0.01");//发货损耗 2位小数
   m_strfShoufaMaxSunhao= _T("0.05");//收发最大损耗(kg) 4位小数
   m_strisKoukuan       = _T("0");//超过最大损耗扣款
   m_strfZMDSalePrice   = _T("");//专卖店销售单价
   m_strfZhekou         = _T("0.30");//折扣 2位小数
   m_strfKouKuanPrice = _T("0");
   m_strPWeight = _T("0");
   m_cProductName = _T(""); //产品名称
   m_strBeiLv = _T("0");
   m_strYarnCode = _T("");
   m_iCheckOuterYarn = 0;
   m_strPrintYarn = _T("");
}

void CDBPinZhongSetting::Copy(CDBPinZhongSetting * pData)
{
	ASSERT(NULL != pData);
	CDataMid::Copy(pData);

	m_ID = pData->m_ID;
	m_cCate = pData->m_cCate;
	m_cChenfen = pData->m_cChenfen;
   m_strfSalePrice = pData->m_strfSalePrice;//销售单价 2位小数
   m_cZhiXingBiaoZun= pData->m_cZhiXingBiaoZun;	//执行标准
   m_strfFahuoSunhao = pData->m_strfFahuoSunhao;//发货损耗 2位小数
   m_strfShoufaMaxSunhao = pData->m_strfShoufaMaxSunhao;//收发最大损耗(kg) 4位小数
   m_strisKoukuan = pData->m_strisKoukuan;//超过最大损耗扣款
   m_strfZMDSalePrice =pData->m_strfZMDSalePrice;//专卖店销售单价
   m_strfZhekou = pData->m_strfZhekou;//折扣 2位小数
   m_strfKouKuanPrice = pData->m_strfKouKuanPrice;
   m_strPWeight = pData->m_strPWeight;
   m_cProductName = pData->m_cProductName;
   m_strBeiLv     = pData->m_strBeiLv;
   m_strYarnCode  = pData->m_strYarnCode;
   m_iCheckOuterYarn = pData->m_iCheckOuterYarn;
   m_strPrintYarn = pData->m_strPrintYarn;
   m_strChengbenPrice = pData->m_strChengbenPrice;
}

void CDBPinZhongSetting::GetAllDataInfo(CADOConn *pADOConn)
{
	ASSERT(NULL != pADOConn);
	m_ID			      = pADOConn->GetValueInt(DBPinZhongSetting_ID);
   m_cCate		      = pADOConn->GetValueString(DBPinZhongSetting_cCate);
   m_cChenfen		   = pADOConn->GetValueString(DBPinZhongSetting_cChenfen);
   m_strfSalePrice      = pADOConn->GetValueDoubleStr(DBPinZhongSetting_fSalePrice,2);
   m_cZhiXingBiaoZun    = pADOConn->GetValueString(DBPinZhongSetting_cZhiXingBiaoZun);
   m_strfFahuoSunhao    = pADOConn->GetValueDoubleStr(DBPinZhongSetting_fFahuoSunhao,4);
   m_strfShoufaMaxSunhao= pADOConn->GetValueDoubleStr(DBPinZhongSetting_fShoufaMaxSunhao,2);
   m_strisKoukuan       = pADOConn->GetValueDoubleStr(DBPinZhongSetting_isKoukuan,0);
   m_strfZMDSalePrice   = pADOConn->GetValueDoubleStr(DBPinZhongSetting_fZMDSalePrice,2);
   m_strfZhekou         = pADOConn->GetValueDoubleStr(DBPinZhongSetting_fZhekou,2);
   m_strfKouKuanPrice   = pADOConn->GetValueDoubleStr(DBPinZhongSetting_fKouKuanPrice,2);
   m_strPWeight         = pADOConn->GetValueDoubleStr(DBPinZhongSetting_fPWeight,4);
   m_cProductName       = pADOConn->GetValueString(DBPinZhongSetting_cProductName);
   m_strBeiLv           = pADOConn->GetValueDoubleStr(DBPinZhongSetting_fBelLv,2);
   m_strYarnCode        = pADOConn->GetValueString(DBPinZhongSetting_cYarnCode);
   m_iCheckOuterYarn = pADOConn->GetValueInt(DBPinZhongSetting_IsOuterYarn);
   m_strPrintYarn = pADOConn->GetValueString(DBPinZhongSetting_cPrintYarn);
   m_strChengbenPrice = pADOConn->GetValueString(DBPinZhongSetting_cChengBenPrice);
}

BOOL CDBPinZhongSetting::InsertDBInfo(CADOConn *pADOConn)
{
   if (!pADOConn)
   {
      return FALSE;
   }
   CString strSql = _T("");
   strSql.Format(_T("insert into %s \
      (%s,%s,%s,%s,%s\
      ,%s,%s,%s,%s,%s,\
      %s,%s,%s,%s,%s,\
      %s,%s) \
      values('%s','%s','%s','%s','%s'\
      ,'%s','%s','%s','%s','%s',\
      '%s','%s','%s','%s','%d',\
      '%s','%s')"),
      DB_TABLE_PINZHONGSETTING
      ,DBPinZhongSetting_cCate,DBPinZhongSetting_cChenfen,DBPinZhongSetting_fSalePrice
      ,DBPinZhongSetting_cZhiXingBiaoZun,DBPinZhongSetting_fFahuoSunhao,DBPinZhongSetting_fShoufaMaxSunhao
      ,DBPinZhongSetting_isKoukuan,DBPinZhongSetting_fZMDSalePrice,DBPinZhongSetting_fZhekou,DBPinZhongSetting_fKouKuanPrice
      ,DBPinZhongSetting_fPWeight,DBPinZhongSetting_cProductName,DBPinZhongSetting_fBelLv,DBPinZhongSetting_cYarnCode,DBPinZhongSetting_IsOuterYarn
      ,DBPinZhongSetting_cPrintYarn,DBPinZhongSetting_cChengBenPrice
	  ,m_cCate,m_cChenfen,m_strfSalePrice,m_cZhiXingBiaoZun,m_strfFahuoSunhao
      ,m_strfShoufaMaxSunhao,m_strisKoukuan,m_strfZMDSalePrice,m_strfZhekou,m_strfKouKuanPrice
      ,m_strPWeight,m_cProductName,m_strBeiLv,m_strYarnCode,m_iCheckOuterYarn
	  ,m_strPrintYarn,m_strChengbenPrice);                    
   return pADOConn->ExecuteSQL(strSql);
}

BOOL CDBPinZhongSetting::UpdateChenfenByID(CADOConn *pADOConn)
{
   if (!pADOConn)
   {
      return FALSE;
   }
   CString strSql = _T("");
   strSql.Format(_T("UPDATE %s SET %s='%s',%s='%s',%s='%s',%s='%s',%s='%s',\
                    %s='%s',%s='%s',%s='%s',%s='%s',%s='%s',\
                    %s='%s',%s='%s',%s='%s',%s='%d',%s='%s',\
                    %s = '%s' where %s='%d'"),
      DB_TABLE_PINZHONGSETTING
      ,DBPinZhongSetting_cChenfen,m_cChenfen
      ,DBPinZhongSetting_fSalePrice,m_strfSalePrice
      ,DBPinZhongSetting_cZhiXingBiaoZun,m_cZhiXingBiaoZun
      ,DBPinZhongSetting_fFahuoSunhao,m_strfFahuoSunhao
      ,DBPinZhongSetting_fShoufaMaxSunhao,m_strfShoufaMaxSunhao
      ,DBPinZhongSetting_isKoukuan,m_strisKoukuan
      ,DBPinZhongSetting_fZMDSalePrice,m_strfZMDSalePrice
      ,DBPinZhongSetting_fZhekou,m_strfZhekou
      ,DBPinZhongSetting_fKouKuanPrice,m_strfKouKuanPrice
      ,DBPinZhongSetting_fPWeight,m_strPWeight
      ,DBPinZhongSetting_cProductName,m_cProductName
      ,DBPinZhongSetting_fBelLv,m_strBeiLv
      ,DBPinZhongSetting_cYarnCode,m_strYarnCode
      ,DBPinZhongSetting_IsOuterYarn,m_iCheckOuterYarn
	  ,DBPinZhongSetting_cPrintYarn,m_strPrintYarn
     ,DBPinZhongSetting_cChengBenPrice,m_strChengbenPrice
      ,DBPinZhongSetting_ID,m_ID);
   return pADOConn->ExecuteSQL(strSql);
}

BOOL CDBPinZhongSetting::DelAllDBInfoByID(CADOConn *pADOConn)
{
   if (!pADOConn)
   {
      return FALSE;
   }
   CString strSql = _T("");
   strSql.Format(_T("Delete %s where %s='%d'"),
      DB_TABLE_PINZHONGSETTING,DBPinZhongSetting_ID,m_ID);
   return pADOConn->ExecuteSQL(strSql);
}

CString CDBPinZhongSetting::SetDBEquals_Log(CDBPinZhongSetting &pOldData)
{
   CString strActLog = _T("");
   if (m_cCate != pOldData.m_cCate)
   {
      CString strCate;
      if (m_cCate.IsEmpty())
      {
         strCate = _T("空值");
      }
      strCate = m_cCate;
      strActLog += _T("纱线品种:") + strCate + _T(",");
   }
   if (m_cChenfen != pOldData.m_cChenfen)
   {
      CString strChenfen;
      if (m_cChenfen.IsEmpty())
      {
         strChenfen = _T("空值");
      }
      strChenfen = m_cChenfen;
      strActLog += _T("成份:") + strChenfen + _T(",");

   }
   if (m_strfSalePrice != pOldData.m_strfSalePrice)
   {
      CString strfSalePrice;
      if (m_strfSalePrice.IsEmpty())
      {
         strfSalePrice = _T("空值");
      }
      strfSalePrice = m_strfSalePrice;
      strActLog += _T("销售单价:") + strfSalePrice + _T(",");

   }
   if (m_cZhiXingBiaoZun != pOldData.m_cZhiXingBiaoZun)
   {
      CString strZhiXingBiaoZun;
      if (m_cZhiXingBiaoZun.IsEmpty())
      {
         strZhiXingBiaoZun = _T("空值");
      }
      strZhiXingBiaoZun = m_cZhiXingBiaoZun;
      strActLog += _T("执行标准:") + strZhiXingBiaoZun + _T(",");

   }
   if (m_strfFahuoSunhao != pOldData.m_strfFahuoSunhao)
   {
      CString strfFahuoSunhao;
      if (m_strfFahuoSunhao.IsEmpty())
      {
         strfFahuoSunhao = _T("空值");
      }
      strfFahuoSunhao = m_strfFahuoSunhao;
      strActLog += _T("发货损耗:") + strfFahuoSunhao + _T(",");
   }
   if (m_strfShoufaMaxSunhao != pOldData.m_strfShoufaMaxSunhao)
   {
      CString strfShoufaMaxSunhao;
      if (m_strfShoufaMaxSunhao.IsEmpty())
      {
         strfShoufaMaxSunhao = _T("空值");
      }
      strfShoufaMaxSunhao = m_strfShoufaMaxSunhao;
      strActLog += _T("收发最大损耗:") + strfShoufaMaxSunhao + _T(",");
   }
   if (m_strisKoukuan != pOldData.m_strisKoukuan)
   {
      CString strisKoukuan;
      if (m_strisKoukuan.IsEmpty())
      {
         strisKoukuan = _T("空值");
      }
      strisKoukuan = m_strisKoukuan;
      strActLog += _T("超过最大损耗扣款:") + strisKoukuan + _T(",");
   }
   if (m_strfZMDSalePrice != pOldData.m_strfZMDSalePrice)
   {
      CString strfZMDSalePrice;
      if (m_strfZMDSalePrice.IsEmpty())
      {
         strfZMDSalePrice = _T("空值");
      }
      strfZMDSalePrice = m_strfZMDSalePrice;
      strActLog += _T("专卖店销售单价:") + strfZMDSalePrice + _T(",");
   }
   if (m_strfZhekou != pOldData.m_strfZhekou)
   {
      CString strfZhekou;
      if (m_strfZhekou.IsEmpty())
      {
         strfZhekou = _T("空值");
      }
      strfZhekou = m_strfZhekou;
      strActLog += _T("折扣:") + strfZhekou + _T(",");
   }
   if (m_strfKouKuanPrice != pOldData.m_strfKouKuanPrice)
   {
      CString strfKouKuanPrice;
      if (m_strfKouKuanPrice.IsEmpty())
      {
         strfKouKuanPrice = _T("空值");
      }
      strfKouKuanPrice = m_strfKouKuanPrice;
      strActLog += _T("扣款单价:") + strfKouKuanPrice + _T(",");
   }
   if (m_strPWeight != pOldData.m_strPWeight)
   {
      CString strPWeight;
      if (m_strPWeight.IsEmpty())
      {
         strPWeight = _T("空值");
      }
      strPWeight = m_strPWeight;
      strActLog += _T("去皮重量:") + strPWeight + _T(",");
   }
   if (m_cProductName != pOldData.m_cProductName)
   {
      CString strProductName;
      if (m_cProductName.IsEmpty())
      {
         strProductName = _T("空值");
      }
      strProductName = m_cProductName;
      strActLog += _T("产品名称:") + strProductName + _T(",");
   }
   if (m_strBeiLv != pOldData.m_strBeiLv)
   {
      CString strBeiLv;
      if (m_strBeiLv.IsEmpty())
      {
         strBeiLv = _T("空值");
      }
      strBeiLv = m_strBeiLv;
      strActLog += _T("倍率:") + strBeiLv + _T(",");
   }
   if (m_strYarnCode != pOldData.m_strYarnCode)
   {
      CString strText;
      if (m_strYarnCode.IsEmpty())
      {
         strText = _T("空值");
      }
      strText = m_strYarnCode;
      strActLog += _T("纱线类别代号:") + m_strYarnCode + _T(",");
   }
   if (m_strPrintYarn != pOldData.m_strPrintYarn)
   {
	   CString strText;
	   if (m_strPrintYarn.IsEmpty())
	   {
		   strText = _T("空值");
	   }
	   strText = m_strPrintYarn;
	   strActLog += _T("打印纱线:") + m_strPrintYarn + _T(",");
   }
   return strActLog;
}

//根据 品种类型 获取数据信息		by WangZY 2018/04/22
BOOL CDBPinZhongSetting::GetInfoByCate(CADOConn *pADOConn,CString strCate)
{
	ASSERT(pADOConn != NULL);
	if (strCate.IsEmpty())
	{
		return FALSE;
	}

	CString strSQL = _T("");
	strSQL.Format(_T("select * from %s where %s='%s'"),
		DB_TABLE_PINZHONGSETTING,
		DBPinZhongSetting_cCate,
		strCate);

	pADOConn->GetRecordSet(strSQL);
	while (!pADOConn->adoEOF())
	{
		GetAllDataInfo(pADOConn);      
		pADOConn->MoveNext();

		return TRUE;
	}

	return FALSE;
}

//**************************CDBPinZhongSettingList******************//

std::shared_ptr<CDBPinZhongSettingList> CDBPinZhongSettingList::sm_inst;

CDBPinZhongSettingList * CDBPinZhongSettingList::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = shared_ptr<CDBPinZhongSettingList>(new CDBPinZhongSettingList);

	return sm_inst.get();
}

CDBPinZhongSettingList::CDBPinZhongSettingList()
{

}

CDBPinZhongSettingList::~CDBPinZhongSettingList()
{

}
#ifdef USING_GRIDCTRL_MARK
MAP_GridCtrl_AllData CDBPinZhongSettingList::GetMapGridData()
{
   MAP_GridCtrl_AllData map_all_data;
   for(int i=0;i< GetCount();i++)
   {
      CDBPinZhongSetting * pObject = GetItem(i);
      if(pObject)
      {
         MAP_GridCtrl_RowData row_data;
         CString strTemp = _T("");
         strTemp.Format(FORMAT_INT,pObject->m_ID);
         InsertRowData(DBPinZhongSetting_ID, strTemp, row_data, CB_enum_FieldData_Int);
         InsertRowData(DBPinZhongSetting_cCate	,		pObject->m_cCate,row_data);
         InsertRowData(DBPinZhongSetting_cChenfen	,		pObject->m_cChenfen,row_data);         
         //InsertRowData(DBPinZhongSetting_fSalePrice	,		pObject->m_strfSalePrice,row_data, CB_enum_FieldData_Double2Point);
         //InsertRowData(DBPinZhongSetting_cZhiXingBiaoZun	,		pObject->m_cZhiXingBiaoZun,row_data);
         //InsertRowData(DBPinZhongSetting_fFahuoSunhao	,		pObject->m_strfFahuoSunhao,row_data, CB_enum_FieldData_Double4Point);
         //InsertRowData(DBPinZhongSetting_fShoufaMaxSunhao	,		pObject->m_strfShoufaMaxSunhao,row_data, CB_enum_FieldData_Double2Point);
         //InsertRowData(DBPinZhongSetting_isKoukuan	,		pObject->m_strisKoukuan,row_data);
         //InsertRowData(DBPinZhongSetting_fZMDSalePrice	,		pObject->m_strfZMDSalePrice,row_data, CB_enum_FieldData_Double2Point);
         //InsertRowData(DBPinZhongSetting_fZhekou	,		pObject->m_strfZhekou,row_data, CB_enum_FieldData_Double2Point);
         //InsertRowData(DBPinZhongSetting_fKouKuanPrice	,		pObject->m_strfKouKuanPrice,row_data,CB_enum_FieldData_Double2Point);
         InsertRowData(DBPinZhongSetting_fPWeight	,		pObject->m_strPWeight,row_data, CB_enum_FieldData_Double4Point);
         InsertRowData(DBPinZhongSetting_cProductName, pObject->m_cProductName,row_data);
         InsertRowData(DBPinZhongSetting_cYarnCode, pObject->m_strYarnCode,row_data);
         InsertRowData(DBPinZhongSetting_IsOuterYarn, pObject->m_iCheckOuterYarn==1?_T("是"):_T("否"),row_data);
         InsertRowData(DBPinZhongSetting_cChengBenPrice, pObject->m_strChengbenPrice,row_data);
		 //InsertRowData(DBPinZhongSetting_cPrintYarn, pObject->m_strPrintYarn,row_data);
         map_all_data.insert(make_pair(map_all_data.size(),row_data));	
      }
   }  
   return map_all_data;
}
MAP_GridCtrl_AllData CDBPinZhongSettingList::GetMapGridDataBelLv()
{
   MAP_GridCtrl_AllData map_all_data;
   for(int i=0;i< GetCount();i++)
   {
      CDBPinZhongSetting * pObject = GetItem(i);
      if(pObject)
      {
         MAP_GridCtrl_RowData row_data;
         CString strTemp = _T("");
         strTemp.Format(FORMAT_INT,pObject->m_ID);
         InsertRowData(DBPinZhongSetting_ID	,		strTemp,row_data, CB_enum_FieldData_Int);
         InsertRowData(DBPinZhongSetting_cCate	,		pObject->m_cCate,row_data);
         InsertRowData(DBPinZhongSetting_cChenfen	,		pObject->m_cChenfen,row_data);         
         InsertRowData(DBPinZhongSetting_fSalePrice	,		pObject->m_strfSalePrice,row_data, CB_enum_FieldData_Double2Point);
         InsertRowData(DBPinZhongSetting_cZhiXingBiaoZun	,		pObject->m_cZhiXingBiaoZun,row_data);
         InsertRowData(DBPinZhongSetting_fFahuoSunhao	,		pObject->m_strfFahuoSunhao,row_data, CB_enum_FieldData_Double4Point);
         InsertRowData(DBPinZhongSetting_fShoufaMaxSunhao	,		pObject->m_strfShoufaMaxSunhao,row_data, CB_enum_FieldData_Double2Point);
         InsertRowData(DBPinZhongSetting_isKoukuan	,		pObject->m_strisKoukuan,row_data);
         InsertRowData(DBPinZhongSetting_fZMDSalePrice	,		pObject->m_strfZMDSalePrice,row_data, CB_enum_FieldData_Double2Point);
         InsertRowData(DBPinZhongSetting_fBelLv	,		pObject->m_strBeiLv,row_data);//倍率
         InsertRowData(DBPinZhongSetting_fKouKuanPrice	,		pObject->m_strfKouKuanPrice,row_data, CB_enum_FieldData_Double2Point);
         InsertRowData(DBPinZhongSetting_fPWeight	,		pObject->m_strPWeight,row_data, CB_enum_FieldData_Double4Point);
         InsertRowData(DBPinZhongSetting_cProductName, pObject->m_cProductName,row_data);
         InsertRowData(DBPinZhongSetting_IsOuterYarn, pObject->m_iCheckOuterYarn==1?_T("是"):_T("否"),row_data);
         InsertRowData(DBPinZhongSetting_cYarnCode, pObject->m_strYarnCode,row_data);
		 InsertRowData(DBPinZhongSetting_cPrintYarn, pObject->m_strPrintYarn,row_data);//打印纱线 add anjie by 2019/03/30
         map_all_data.insert(make_pair(map_all_data.size(),row_data));	
      }
   }  
   return map_all_data;
}

MAP_GridCtrl_AllData CDBPinZhongSettingList::GetMapEasyGridDataBelLv()
{
	MAP_GridCtrl_AllData map_all_data;
	for(int i=0;i< GetCount();i++)
	{
		CDBPinZhongSetting * pObject = GetItem(i);
		if(pObject)
		{
			MAP_GridCtrl_RowData row_data;
			CString strTemp = _T("");
			strTemp.Format(FORMAT_INT,pObject->m_ID);
			InsertRowData(DBPinZhongSetting_ID	,		strTemp,row_data, CB_enum_FieldData_Int);
			InsertRowData(DBPinZhongSetting_cCate	,		pObject->m_cCate,row_data);
			InsertRowData(DBPinZhongSetting_cPrintYarn, pObject->m_strPrintYarn,row_data);//打印纱线 add anjie by 2019/03/30
			map_all_data.insert(make_pair(map_all_data.size(),row_data));	
		}
	}  

	 return map_all_data;
}
#endif// USING_GRIDCTRL_MARK

void CDBPinZhongSettingList::AddItem( CDBPinZhongSetting* pItem )
{
   CDBPinZhongSetting*pData=new CDBPinZhongSetting;
   pData->Copy(pItem);
   AddTail(pData);
}

CDBPinZhongSetting * CDBPinZhongSettingList::GetItemByID( int iID )
{
   CDBPinZhongSetting * pItem = NULL;  
   for(int i=0;i< GetCount();i++)
   {
      CDBPinZhongSetting * pObject = GetItem(i);
      if(iID==pObject->m_ID)
      {
         pItem = pObject;
         break;
      }
   }
   return pItem;
}
 void CDBPinZhongSettingList::DeleteItem(int iID)
 {
    for(int i=0;i< GetCount();i++)
    {
       CDBPinZhongSetting * pObject = GetItem(i);
       if(iID==pObject->m_ID)
       {
          RemoveAt(FindIndex(i));
          break;
       }
    }
 }

 CDBPinZhongSetting*  CDBPinZhongSettingList::GetItem(int nIndex)
 {
    if (nIndex<0||nIndex>=GetCount())
       return NULL;
    return (CDBPinZhongSetting*)GetAt(FindIndex(nIndex));
 }

CDBPinZhongSetting * CDBPinZhongSettingList::GetItemByCate(CString strCate)
{
   CDBPinZhongSetting * pItem = NULL; 
   for(int i=0;i< GetCount();i++)
   {
      CDBPinZhongSetting * pObject = GetItem(i);
      if(strCate==pObject->m_cCate)
      {
         pItem = pObject;
         break;
      }
   }
   return pItem;
}
void CDBPinZhongSettingList::GetYarnCF_Cate_Info(__in CADOConn *pADOConn,__in CString strCate,__out CString &strCF)// 根据纱线类别获取纱线成份 liuhw 2019/03/01
{
   ASSERT(pADOConn != NULL);
   strCF = _T("");
   CString strSql = _T("");
   strSql.Format(_T("SELECT %s from %s where %s = '%s'"),DBPinZhongSetting_cChenfen,
      DB_TABLE_PINZHONGSETTING,DBPinZhongSetting_cCate,strCate);
   pADOConn->GetRecordSet(strSql);
   if (!pADOConn->adoEOF())
   {
      strCF = pADOConn->GetValueString(DBPinZhongSetting_cChenfen);
   }
}

void CDBPinZhongSettingList::GetListFromDB(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);
   Empty();
   CString strSQL = _T("");
   strSQL.Format(_T("select * from %s"),DB_TABLE_PINZHONGSETTING);
   pADOConn->GetRecordSet(strSQL);
   while (!pADOConn->adoEOF())
   {
      CDBPinZhongSetting oData;
      oData.GetAllDataInfo(pADOConn);      
      AddItem(&oData);
      pADOConn->MoveNext();
   }
}

BOOL CDBPinZhongSettingList::GetFahuoSunhao(__in CADOConn *pADOConn,__in CString strYarnCate,__out CString& strFHSH)
{
   ASSERT(pADOConn != NULL);
   strFHSH = _T("");
   CString strSql = _T("");
   strSql.Format(_T("select top 1 fFahuoSunhao from PinZhongSetting where cCate = '%s'"),strYarnCate);
   pADOConn->GetRecordSet(strSql);
   if (!pADOConn->adoEOF())
   {
      strFHSH = pADOConn->GetValueString(_T("fFahuoSunhao"));
   }
   return TRUE;
}


BOOL CDBPinZhongSettingList::UpdateYarnZMJ(CADOConn *pADOConn,std::vector<CString>vecID,double fBeilv,BOOL bBeilv)
{
   if (!pADOConn || vecID.empty())
   {
      return FALSE;
   }
   CString strFilter = _T(" (");
   for (auto iter = vecID.begin();iter!=vecID.end();++iter)
   {
      if(iter!=vecID.begin())
      {
         strFilter += _T(",");
      }
      strFilter += *iter;
   }
   strFilter += _T(") ");
   CString strSQL = _T("");
   strSQL.Format(_T("Update %s set %s=(%s * %.2f) where %s in %s")
      ,DB_TABLE_PINZHONGSETTING,DBPinZhongSetting_fZMDSalePrice,
      DBPinZhongSetting_fSalePrice,fBeilv,DBPinZhongSetting_ID,strFilter);

   if (bBeilv)
   {
      strSQL.Format(_T("Update %s set %s=(%s / %.2f) where %s in %s")
         ,DB_TABLE_PINZHONGSETTING,DBPinZhongSetting_fZMDSalePrice,
         DBPinZhongSetting_fSalePrice,fBeilv,DBPinZhongSetting_ID,strFilter);
   }
   return pADOConn->ExecuteSQL(strSQL);
}

BOOL CDBPinZhongSettingList::GetYarnOuterFlag(__in CADOConn* pAdo,__in CString strYarnCate)
{
   ASSERT(pAdo);
   if (pAdo && !strYarnCate.IsEmpty())
   {
      CString strSql = _T("");
      strSql.Format(_T("select top 1 %s from %s where %s = '%s';"),
                     DBPinZhongSetting_IsOuterYarn,DB_TABLE_PINZHONGSETTING,DBPinZhongSetting_cCate,strYarnCate);
      pAdo->GetRecordSet(strSql);
      if (!pAdo->adoEOF())
      {
         return pAdo->GetValueInt(DBPinZhongSetting_IsOuterYarn);
      }
   }
   return FALSE;
}
