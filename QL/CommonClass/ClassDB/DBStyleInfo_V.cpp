#include "StdAfx.h"
#include "DBStyleInfo_V.h"
#include "DBCustomInfo.h"
//#include "DBStyleInfo.h"
#include "DBKeyDef_V.h"
#include <list>
#include "DBStyle_CheckRecords.h"


std::shared_ptr<CDBStyleInfoList_V> CDBStyleInfoList_V::sm_inst;

CDBStyleInfoData_V::CDBStyleInfoData_V(void)
{
	ResetData();
}


CDBStyleInfoData_V::~CDBStyleInfoData_V(void)
{
}

void CDBStyleInfoData_V::ResetData()
{
	m_nID				= 0;
	m_oleUpdateTime		= COleDateTime::GetCurrentTime();
	m_strTypeName		= _T("");
	m_strStyleNo		= _T("");
	m_strStyleName		= _T("");
   m_strYarnCate     = _T("");
	m_strStyleIntro		= _T("");
	m_oledtCreatTime	= COleDateTime::GetCurrentTime();
   m_strPinMing		=	_T("")	;//品名 yangjr2018/5/11
   m_strKsYears      = _T("");
   m_strCraftsmen  = _T("");    //工艺师
   m_strPatternMaker  = _T("");    //制版师
   m_strClassType = _T("");

   m_dtExpireTime = _T("");    //到期日期
   m_strCreator = _T("");        //创建人
   m_strCreateType = _T("");     //创建类型
   m_strTheme = _T("");          //主题
   m_strEdition = _T("");        //版本
   m_strCusCode = _T("");       //客户
   m_strCusKuanhao = _T("");     //客户款号
   m_strProcessStatus = _T("");  //工序状态
   m_strDesigner = _T("");       //设计师
   m_dtMakingOrdTime = _T(""); //定版日期
   m_strMainMaterial = _T("");   //主原料
   m_strVersionNum = _T("");     //版单号
   m_strSinglePerson = _T("");   //制单人
   m_nCheckState = 0;
   m_strCheckPerson = _T("");
   m_nVersionState    = 0;
   m_strVersionPerson = _T("");
   m_bIsDeleted = 0;//款式是否删除 yangjr 2019/05/20
   m_iUpOrDownShell = 0;  //上下架 1上架 0下架
   m_iFollow = 0;         //关注 1关注 0不关注	
   m_strMainPic = _T("");
   m_nGXSortID       = 0;
   m_strGXPersonCode = _T("");
   m_strState = _T("");
   m_strFangAnName = _T("");
   m_strPrority = _T("");  //优先级
   m_strNeedleType = _T("");  //针型
   m_strStyleDescription = _T("");
   m_strModelMainPic = _T("");
   m_nSortIndex = 0;
   m_strBrand = _T("");
   m_strCustomField1  = _T("");
   m_strCustomField2  = _T("");
   m_strCustomField3  = _T("");
   m_strCustomField4  = _T("");
   m_strCustomField5  = _T("");
   m_strCustomField6  = _T("");
   m_strCustomField7  = _T("");
   m_strCustomField8  = _T("");
   m_strCustomField9  = _T("");
   m_strCustomField10 = _T("");

   m_dTotalCost = 0;     //总成本
   m_dTotalOffer = 0;    //总报价

   m_bCostAndOfferChanged = FALSE;

   SetDataType(DAT_VSTYLE);
}

void CDBStyleInfoData_V::Copy( CDBStyleInfoData_V * pData )
{
	ASSERT(NULL != pData);
	CDataMid::Copy(pData);
	m_nID				= pData->m_nID				;
	m_oleUpdateTime		= pData->m_oleUpdateTime			;
	m_strTypeName		= pData->m_strTypeName		;
	m_strStyleNo		= pData->m_strStyleNo		;
	m_strStyleName		= pData->m_strStyleName		;
   m_strYarnCate     = pData->m_strYarnCate		;
	m_strStyleIntro		= pData->m_strStyleIntro		;
	m_oledtCreatTime	= pData->m_oledtCreatTime	;
   m_strPinMing = pData->m_strPinMing;
   m_strKsYears   = pData->m_strKsYears;
   m_strCraftsmen = pData->m_strCraftsmen;    //工艺师
   m_strPatternMaker = pData->m_strPatternMaker;    //制版师
   m_strClassType = pData->m_strClassType;

   m_dtExpireTime = pData->m_dtExpireTime;    //到期日期
   m_strCreator = pData->m_strCreator;        //创建人
   m_strCreateType = pData->m_strCreateType;     //创建类型
   m_strTheme = pData->m_strTheme;          //主题
   m_strEdition = pData->m_strEdition;        //版本
   m_strCusCode = pData->m_strCusCode;       //客户
   m_strCusKuanhao = pData->m_strCusKuanhao;     //客户款号
   m_strProcessStatus = pData->m_strProcessStatus;  //工序状态
   m_strDesigner = pData->m_strDesigner;       //设计师
   m_dtMakingOrdTime = pData->m_dtMakingOrdTime; //定版日期
   m_strMainMaterial = pData->m_strMainMaterial;   //主原料
   m_strVersionNum = pData->m_strVersionNum;     //版单号
   m_strSinglePerson = pData->m_strSinglePerson;   //制单人
   m_nCheckState = pData->m_nCheckState;
   m_strCheckPerson = pData->m_strCheckPerson;
   m_bIsDeleted = pData->m_bIsDeleted;//款式是否删除 yangjr 2019/05/20
   m_iUpOrDownShell = pData->m_iUpOrDownShell;  //上下架 1上架 0下架
   m_iFollow = pData->m_iFollow;         //关注 1关注 0不关注
   m_strMainPic = pData->m_strMainPic;
   m_nGXSortID       = pData->m_nGXSortID      ;
   m_strGXPersonCode = pData->m_strGXPersonCode;
   m_strState = pData->m_strState;
   m_strFangAnName = pData->m_strFangAnName;
   m_nVersionState    = pData->m_nVersionState   ;
   m_strVersionPerson = pData->m_strVersionPerson;
   m_strPrority = pData->m_strPrority;
   m_strNeedleType = pData->m_strNeedleType;
   m_strStyleDescription = pData->m_strStyleDescription;
   m_strModelMainPic = pData->m_strModelMainPic;
   m_nSortIndex = pData->m_nSortIndex;
   m_strBrand = pData->m_strBrand;
   m_strCustomField1  = pData->m_strCustomField1 ;
   m_strCustomField2  = pData->m_strCustomField2 ;
   m_strCustomField3  = pData->m_strCustomField3 ;
   m_strCustomField4  = pData->m_strCustomField4 ;
   m_strCustomField5  = pData->m_strCustomField5 ;
   m_strCustomField6  = pData->m_strCustomField6 ;
   m_strCustomField7  = pData->m_strCustomField7 ;
   m_strCustomField8  = pData->m_strCustomField8 ;
   m_strCustomField9  = pData->m_strCustomField9 ;
   m_strCustomField10 = pData->m_strCustomField10;

   m_dTotalCost = pData->m_dTotalCost;     //总成本
   m_dTotalOffer = pData->m_dTotalOffer;    //总报价 

   m_strHelpSeekerID = pData->m_strHelpSeekerID;

   m_bCostAndOfferChanged = pData->m_bCostAndOfferChanged;
}

void CDBStyleInfoData_V::ToDBData(CDBStyleInfoData& oDBData)
{
	oDBData.m_nID				=	m_nID				;
	oDBData.m_oleTimeUpdate		=	m_oleUpdateTime		;
	oDBData.m_strTypeName		=	m_strTypeName		;
	oDBData.m_strStyleNo		=	m_strStyleNo		;
	oDBData.m_strStyleName		=	m_strStyleName		;
	oDBData.m_strStyleIntro		=	m_strStyleIntro		;
	oDBData.m_oleTimeCreate		=	m_oledtCreatTime	;
   oDBData.m_strPinMing			=	m_strPinMing			;
   oDBData.m_strYarnCate      = m_strYarnCate;
   oDBData.m_strKsYears    = m_strKsYears;

   oDBData.m_dtExpireTime =  m_dtExpireTime;    //到期日期
   oDBData.m_strCreator =  m_strCreator;        //创建人
   oDBData.m_strCreateType =  m_strCreateType;     //创建类型
   oDBData.m_strTheme =  m_strTheme;          //主题
   oDBData.m_strEdition =  m_strEdition;        //版本
   oDBData.m_strCusCode =  m_strCusCode;       //客户
   oDBData.m_strCusKuanhao =  m_strCusKuanhao;     //客户款号
   oDBData.m_strProcessStatus =  m_strProcessStatus;  //工序状态
   oDBData.m_dtMakingOrdTime = m_dtMakingOrdTime; //定版日期
   oDBData.m_strMainMaterial = m_strMainMaterial;   //主原料
   oDBData.m_strVersionNum = m_strVersionNum;     //版单号
   oDBData.m_strSinglePerson = m_strSinglePerson;   //制单人
   oDBData.m_bIsDeleted = m_bIsDeleted;
   oDBData.m_iFollow = m_iFollow;
   oDBData.m_iUpOrDownShell = m_iUpOrDownShell;
   oDBData.m_strMainPic = m_strMainPic;
   oDBData.m_strState = m_strState;
   oDBData.m_strFangAnName = m_strFangAnName;
   oDBData.m_strNeedleType = m_strNeedleType;
   oDBData.m_strPrority = m_strPrority;
   oDBData.m_strModelMainPic = m_strModelMainPic;
   oDBData.m_nSortIndex = m_nSortIndex;
   oDBData.m_strBrand = m_strBrand;
   oDBData.m_strCustomField1  = m_strCustomField1 ;
   oDBData.m_strCustomField2  = m_strCustomField2 ;
   oDBData.m_strCustomField3  = m_strCustomField3 ;
   oDBData.m_strCustomField4  = m_strCustomField4 ;
   oDBData.m_strCustomField5  = m_strCustomField5 ;
   oDBData.m_strCustomField6  = m_strCustomField6 ;
   oDBData.m_strCustomField7  = m_strCustomField7 ;
   oDBData.m_strCustomField8  = m_strCustomField8 ;
   oDBData.m_strCustomField9  = m_strCustomField9 ;
   oDBData.m_strCustomField10 = m_strCustomField10;
   oDBData.m_dTotalOffer = m_dTotalOffer;
   oDBData.m_dTotalCost = m_dTotalCost;
}

void CDBStyleInfoData_V::CopyBasicInfo(CDBStyleInfoData_V * pData)
{
   m_strTypeName     = pData->m_strTypeName    ;
   m_strStyleName    = pData->m_strStyleName   ;
   m_strStyleIntro   = pData->m_strStyleIntro  ;
   m_strKsYears      = pData->m_strKsYears     ;
   m_strTheme        = pData->m_strTheme       ;
   m_strCusCode      = pData->m_strCusCode     ;
   m_strCusKuanhao   = pData->m_strCusKuanhao  ;
   m_strEdition      = pData->m_strEdition     ;
   m_dtMakingOrdTime = pData->m_dtMakingOrdTime;
   m_strMainMaterial = pData->m_strMainMaterial;
   m_strVersionNum   = pData->m_strVersionNum  ;
   m_strSinglePerson = pData->m_strSinglePerson;
   m_strPinMing      = pData->m_strPinMing     ;
   m_iFollow         = pData->m_iFollow        ;
   m_iUpOrDownShell  = pData->m_iUpOrDownShell ;
   m_strState        = pData->m_strState       ;
   m_strPrority      = pData->m_strPrority     ;
   m_strNeedleType   = pData->m_strNeedleType  ;
   m_strStyleNo      = pData->m_strStyleNo     ;
   m_strBrand        = pData->m_strBrand        ;
   m_strCustomField1  = pData->m_strCustomField1 ;
   m_strCustomField2  = pData->m_strCustomField2 ;
   m_strCustomField3  = pData->m_strCustomField3 ;
   m_strCustomField4  = pData->m_strCustomField4 ;
   m_strCustomField5  = pData->m_strCustomField5 ;
   m_strCustomField6  = pData->m_strCustomField6 ;
   m_strCustomField7  = pData->m_strCustomField7 ;
   m_strCustomField8  = pData->m_strCustomField8 ;
   m_strCustomField9  = pData->m_strCustomField9 ;
   m_strCustomField10 = pData->m_strCustomField10;
   m_dTotalCost = pData->m_dTotalCost;     //总成本
   m_dTotalOffer = pData->m_dTotalOffer;    //总报价

   m_bCostAndOfferChanged = pData->m_bCostAndOfferChanged;
}

BOOL CDBStyleInfoData_V::GetAllDBInfo( CADOConn *pADOConn )
{
   ASSERT(NULL != pADOConn);
   BOOL bRet = FALSE;
   if (NULL == pADOConn)
   {
      return bRet;
   }
   else
   {
      m_nID				=	pADOConn->GetValueInt(DBKuanShi_key_ID);
      m_oleUpdateTime.ParseDateTime(pADOConn->GetValueString(DBKuanShi_key_UpdateTime));
      m_strTypeName		=	pADOConn->GetValueString(DBKuanShi_key_KindName		);
      m_strStyleNo		=	pADOConn->GetValueString(DBKuanShi_key_StyleNo		);
      m_strStyleName		=	pADOConn->GetValueString(DBKuanShi_key_StyleName	);
      m_strYarnCate     =  pADOConn->GetValueString(DBKuanShi_key_YarnCate	);
      m_strStyleIntro		=	pADOConn->GetValueString(DBKuanShi_key_StyleIntro	);
      m_oledtCreatTime.ParseDateTime(pADOConn->GetValueString(DBKuanShi_key_CreateTime		));
      m_strPinMing      =	pADOConn->GetValueString(DBKuanShi_key_cPinMing		);
      m_strKsYears      = pADOConn->GetValueString(DBKuanShi_key_KsYears);

      m_dtExpireTime = pADOConn->GetValueString(DBKuanShi_key_dtExpireTime);    //到期日期
      m_strCreator = pADOConn->GetValueString(DBKuanShi_key_cCreator);        //创建人
      m_strCreateType = pADOConn->GetValueString(DBKuanShi_key_cCreateType);     //创建类型
      m_strTheme = pADOConn->GetValueString(DBKuanShi_key_cTheme);          //主题
      m_strEdition = pADOConn->GetValueString(DBKuanShi_key_cEdition);        //版本
      m_strCusCode = pADOConn->GetValueString(DBKuanShi_key_cCusCode);       //客户
      m_strCusKuanhao = pADOConn->GetValueString(DBKuanShi_key_cCusKuanHao);     //客户款号
      m_strProcessStatus = pADOConn->GetValueString(DBKuanShi_key_cProcessStatus);  //工序状态
      m_strDesigner = pADOConn->GetValueString(DBVStyle_key_cDesigner);       //设计师
      m_dtMakingOrdTime = pADOConn->GetValueString(DBKuanShi_key_dtMakingOrdTime); //定版日期
      m_strMainMaterial = pADOConn->GetValueString(DBKuanShi_key_cMainMaterial);   //主原料
      m_strVersionNum = pADOConn->GetValueString(DBKuanShi_key_cVersionNum);     //版单号
      m_strSinglePerson = pADOConn->GetValueString(DBKuanShi_key_cSinglePerson);   //制单人
      m_nCheckState = pADOConn->GetValueInt(DBVStyle_key_cCheckState);
      m_strCheckPerson = pADOConn->GetValueString(DBVStyle_key_cCheckPerson);
      m_bIsDeleted = pADOConn->GetValueInt(DBVStyle_key_bIsDeleted);//款式是否删除 yangjr 2019/05/20
      m_iFollow = pADOConn->GetValueInt(DBKuanShi_key_iFollow);
      m_iUpOrDownShell = pADOConn->GetValueInt(DBKuanShi_key_iShell);     
      m_strMainPic = pADOConn->GetValueString(DBKuanShi_key_cMainPic);
      m_nGXSortID          = pADOConn->GetValueInt(DBVStyle_key_iGXSortID    );
      m_strGXPersonCode    = pADOConn->GetValueString(DBVStyle_key_cGXPersonCode);
      m_strState           = pADOConn->GetValueString(DBVStyle_key_cState);
      m_strCraftsmen        = pADOConn->GetValueString(DBVStyle_key_cCraftsmen   );
      m_strPatternMaker        = pADOConn->GetValueString(DBVStyle_key_cPatternMaker);
      m_strFangAnName      = pADOConn->GetValueString(DBVStyle_key_cFangAnName);
      m_nVersionState      = pADOConn->GetValueInt(DBVStyle_key_nVersionState);
      m_strVersionPerson   = pADOConn->GetValueString(DBVStyle_key_cVersionPerson);
      m_strNeedleType = pADOConn->GetValueString(DBKuanShi_key_cNeedleType);
      m_strPrority = pADOConn->GetValueString(DBKuanShi_key_cPriority);
      m_strStyleDescription = pADOConn->GetValueString(DBStyle_Description_Key_cDescription);
      m_strModelMainPic = pADOConn->GetValueString(DBKuanShi_key_cModelMainPic);
      m_nSortIndex         = pADOConn->GetValueInt(DBKuanShi_key_nSortIndex);
      
      m_strBrand         = pADOConn->GetValueString(DBKuanShi_key_cBrand      );
      m_strCustomField1  = pADOConn->GetValueString(DBVStyle_key_cCustomField1 );
      m_strCustomField2  = pADOConn->GetValueString(DBVStyle_key_cCustomField2 );
      m_strCustomField3  = pADOConn->GetValueString(DBVStyle_key_cCustomField3 );
      m_strCustomField4  = pADOConn->GetValueString(DBVStyle_key_cCustomField4 );
      m_strCustomField5  = pADOConn->GetValueString(DBVStyle_key_cCustomField5 );
      m_strCustomField6  = pADOConn->GetValueString(DBVStyle_key_cCustomField6 );
      m_strCustomField7  = pADOConn->GetValueString(DBVStyle_key_cCustomField7 );
      m_strCustomField8  = pADOConn->GetValueString(DBVStyle_key_cCustomField8 );
      m_strCustomField9  = pADOConn->GetValueString(DBVStyle_key_cCustomField9 );
      m_strCustomField10 = pADOConn->GetValueString(DBVStyle_key_cCustomField10);

      m_dTotalCost = pADOConn->GetValueDouble(DBKuanShi_key_dTotalCost);     //总成本
      m_dTotalOffer = pADOConn->GetValueDouble(DBKuanShi_key_dTotalOffer);    //总报价

      m_strHelpSeekerID = pADOConn->GetValueString(DBVStyle_key_cHelpSeekerID);    //总报价
      bRet = TRUE;
	}

	return bRet;
}

//只获取必要的字段信息		by WangZY 2018/05/29
BOOL CDBStyleInfoData_V::GetAllDBInfoWithNecessaryField(CADOConn *pADOConn)
{
	ASSERT(NULL != pADOConn);
	BOOL bRet = FALSE;
	if (NULL == pADOConn)
	{
		return bRet;
	}
	else
	{
		m_nID					=	pADOConn->GetValueInt(DBKuanShi_key_ID);
		m_strStyleNo		=	pADOConn->GetValueString(DBKuanShi_key_StyleNo		);
		m_strStyleName		=	pADOConn->GetValueString(DBKuanShi_key_StyleName	);
		m_strStyleIntro		=	pADOConn->GetValueString(DBKuanShi_key_StyleIntro	);
		
		bRet = TRUE;
	}

	return bRet;
}

CDBStyleInfoList_V::CDBStyleInfoList_V()
{

}

CDBStyleInfoList_V::~CDBStyleInfoList_V()
{

}

CDBStyleInfoData_V* CDBStyleInfoList_V::GetItem( int nIndex )
{
	if (nIndex<0||nIndex>=GetCount())
		return NULL;
	return (CDBStyleInfoData_V*)GetAt(FindIndex(nIndex));
}

CDBStyleInfoData_V* CDBStyleInfoList_V::GetItemByStyleNo( CString strStyleNo )
{
   CDBStyleInfoData_V * pItem = NULL;
   strStyleNo.Trim();
   if (!strStyleNo.IsEmpty())
   {
      int count = GetCount();
      CString tempStr = strStyleNo.MakeUpper();
      for(int i=0;i< count;++i)
      {
         CDBStyleInfoData_V * pObject = GetItem(i);
         CString kuanhao = pObject->m_strStyleNo;
         if(tempStr==kuanhao.MakeUpper())
         {
            pItem = pObject;
            break;
         }
      }
   }

   return pItem;
}

CDBStyleInfoData_V* CDBStyleInfoList_V::GetItemByID(int nStyleID)
{
   CDBStyleInfoData_V * pItem = NULL;
   if (nStyleID > 0)
   {
      int count = GetCount();
      for(int i=0;i< count;++i)
      {
         CDBStyleInfoData_V * pObject = GetItem(i);
         if(pObject && pObject->m_nID == nStyleID)
         {
            pItem = pObject;
            break;
         }
      }
   }

   return pItem;
}

int CDBStyleInfoList_V::GetIndexByStyleNo( CString strStyleNo )
{
	int nSel = -1;
	strStyleNo.Trim();
	if (!strStyleNo.IsEmpty())
	{
      int count = GetCount();
      CString tempStr = strStyleNo.MakeUpper();
		for(int i=0;i< count;++i)
		{
			auto pObject = GetItem(i);
         CString kuanhao = pObject->m_strStyleNo;
         if(tempStr==kuanhao.MakeUpper())
			{
				nSel = i;
				break;
			}
		}
	}

	return nSel;
}

void CDBStyleInfoList_V::AddItem( CDBStyleInfoData_V* pItem )
{
	CDBStyleInfoData_V*pData=new CDBStyleInfoData_V;
	pData->Copy(pItem);
	AddTail(pData);
}

void CDBStyleInfoList_V::DeleteItem( int nIndex )
{
	if (nIndex<0||nIndex>GetCount())
		return;
	CDBStyleInfoData_V *pObject=(CDBStyleInfoData_V*)GetItem(nIndex);
	delete pObject;
	pObject=NULL;
	RemoveAt(FindIndex(nIndex));
}

//只获取必要的字段信息		by WangZY 2018/05/29
BOOL CDBStyleInfoList_V::GetListFromDBWithNecessaryField(CADOConn *pADOConn)
{
	Empty();
	BOOL bRet = FALSE;

	ASSERT(pADOConn != NULL);

	if (NULL == pADOConn)
	{
		bRet = FALSE;
	}
	else
	{
		CString strSQL = _T("");
		
		strSQL.Format(_T("select %s,%s,%s,%s from %s"),
			DBKuanShi_key_ID,
			DBKuanShi_key_StyleNo,
			DBKuanShi_key_StyleName,
			DBKuanShi_key_StyleIntro,
			DB_TABLE_STYLE);
		
		pADOConn->GetRecordSet(strSQL);

		while (!pADOConn->adoEOF())
		{
			CDBStyleInfoData_V oData;
			oData.GetAllDBInfoWithNecessaryField(pADOConn);

			AddItem(&oData);
			pADOConn->MoveNext();
		}
	}

	return bRet;
}

//根据ID号获取【整条】信息 yangjr2017-9-20
BOOL CDBStyleInfoList_V::GetListFromDBByID(CADOConn *pADOConn,CString strID,CDBStyleInfoData_V &data)
{
   ASSERT(pADOConn != NULL);
   if (NULL == pADOConn)
   {
      return FALSE;
   }
   else
   {
      CString strSQL = _T("");
      strSQL.Format(_T("select * from %s where ID = '%s'"),DB_VIEW_KUANSHI,strID);
      pADOConn->GetRecordSet(strSQL);
      while (!pADOConn->adoEOF())
      {
         return data.GetAllDBInfo(pADOConn);
      }
   }

   return FALSE;
}

CDBStyleInfoList_V * CDBStyleInfoList_V::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = shared_ptr<CDBStyleInfoList_V>(new CDBStyleInfoList_V);

	return sm_inst.get();
}


BOOL CDBStyleInfoList_V::GetStyleCostAndOffer(CADOConn* pAdo,CDBStyleInfoData_V *data)
{
   ASSERT(pAdo != NULL);
   if (data != nullptr)
   {
      CString strSql;
      strSql.Format(_T("select %s,%s from %s where %s ='%s';"),DBKuanShi_key_dTotalCost,DBKuanShi_key_dTotalOffer,
         DB_VIEW_KUANSHI,DBKuanShi_key_StyleNo,data->m_strStyleNo);

      pAdo->GetRecordSet(strSql);
      if (!pAdo->adoEOF())
      {
         data->m_dTotalCost = pAdo->GetValueDouble(DBKuanShi_key_dTotalCost);
         data->m_dTotalOffer =  pAdo->GetValueDouble(DBKuanShi_key_dTotalOffer);
      }
      return TRUE;
   }
   return FALSE;
}

#ifdef USING_GRIDCTRL_MARK
MAP_GridCtrl_AllData CDBStyleInfoList_V::CreatrGridData()
{
	MAP_GridCtrl_AllData  map_all_data;

   POSITION pos = this->GetHeadPosition();
   while(pos != NULL)
   {
      CDBStyleInfoData_V* pData =(CDBStyleInfoData_V*)this->GetNext(pos);
      if (pData)
      {
         MAP_GridCtrl_RowData map_row_data;
         pData->InsertRowData(DBKuanShi_key_ID				,map_row_data,CB_enum_FieldData_Int,CB_enum_FieldCtrl_Text,FORMAT_INT	,pData->m_nID);
         
         pData->InsertRowData(DBKuanShi_key_iFollow				,map_row_data,CB_enum_FieldData_Int,CB_enum_FieldCtrl_Text,FORMAT_INT	,pData->m_iFollow);
         pData->InsertRowData(DBKuanShi_key_iShell	   ,map_row_data,CB_enum_FieldData_Int,CB_enum_FieldCtrl_Text,FORMAT_INT	,pData->m_iUpOrDownShell);

         //2017/08/03 zhangt 款式维护中日期的显示
         if(pData->m_oleUpdateTime.m_status == COleDateTime::valid)
            pData->InsertRowData(DBKuanShi_key_UpdateTime		,map_row_data,CB_enum_FieldData_Time,CB_enum_FieldCtrl_DateTime,FORMAT_STRING	,pData->m_oleUpdateTime.Format(_T("%Y-%m-%d"))); //%H:%M:%S
         else
            pData->InsertRowData(DBKuanShi_key_UpdateTime		,map_row_data,CB_enum_FieldData_Time,CB_enum_FieldCtrl_DateTime,FORMAT_STRING	,_T(""));
         //2017/08/03_end
         pData->InsertRowData(DBKuanShi_key_KindName		,map_row_data,FORMAT_STRING	,pData->m_strTypeName		);
         
         pData->InsertRowData(DBKuanShi_key_StyleNo		,map_row_data,FORMAT_STRING	,pData->m_strStyleNo		);

         pData->InsertRowData(DBKuanShi_key_StyleName		   ,map_row_data,FORMAT_STRING	,pData->m_strStyleName		);	
         //2017/08/11 zhangt 款式维护 创建时间 显示
         if(pData->m_oledtCreatTime.m_status == COleDateTime::valid)
            pData->InsertRowData(DBKuanShi_key_CreateTime		,map_row_data,CB_enum_FieldData_Time,CB_enum_FieldCtrl_DateTime,FORMAT_STRING	,pData->m_oledtCreatTime.Format(_T("%Y-%m-%d %H:%M:%S")));
         else
            pData->InsertRowData(DBKuanShi_key_CreateTime		,map_row_data,CB_enum_FieldData_Time,CB_enum_FieldCtrl_DateTime,FORMAT_STRING	,_T("")	);
         pData->InsertRowData(DBKuanShi_key_cPinMing			,map_row_data,pData->m_strPinMing		);
         pData->InsertRowData(DBKuanShi_key_KsYears			,map_row_data,pData->m_strKsYears);
         pData->InsertRowData(DBVStyle_key_cCraftsmen   ,map_row_data,FORMAT_STRING	,pData->m_strCraftsmen			);
         pData->InsertRowData(DBVStyle_key_cPatternMaker,map_row_data,FORMAT_STRING	,pData->m_strPatternMaker			);
         // 版房新增款式表数据-----start liuhw 2019/05/08
         pData->InsertRowData(DBKuanShi_key_dtExpireTime    ,map_row_data,CB_enum_FieldData_Time,CB_enum_FieldCtrl_DateTime,FORMAT_STRING, pData->m_dtExpireTime);
         pData->InsertRowData(DBKuanShi_key_cCreator        ,map_row_data,FORMAT_STRING, pData->m_strCreator);
         pData->InsertRowData(DBKuanShi_key_cCreateType     ,map_row_data,FORMAT_STRING, pData->m_strCreateType);
         pData->InsertRowData(DBKuanShi_key_cTheme          ,map_row_data,FORMAT_STRING, pData->m_strTheme);
         pData->InsertRowData(DBKuanShi_key_cCusCode       ,map_row_data,FORMAT_STRING, pData->m_strCusCode);
         pData->InsertRowData(DBKuanShi_key_cCusKuanHao     ,map_row_data,FORMAT_STRING, pData->m_strCusKuanhao);
         if (pData->m_strProcessStatus.IsEmpty())
         {
            pData->InsertRowData(DBVStyle_key_cState    ,map_row_data,FORMAT_STRING,pData->m_strState     );//56
         }
         else
         {
            pData->InsertRowData(DBVStyle_key_cState    ,map_row_data,FORMAT_STRING, pData->m_strProcessStatus);
         }

         pData->InsertRowData(DBKuanShi_key_cEdition        ,map_row_data,FORMAT_STRING, pData->m_strEdition);
         pData->InsertRowData(DBVStyle_key_cDesigner       ,map_row_data,FORMAT_STRING,pData->m_strDesigner         );//49
         pData->InsertRowData(DBKuanShi_key_dtMakingOrdTime ,map_row_data,FORMAT_STRING,pData->m_dtMakingOrdTime   );//50     
         pData->InsertRowData(DBKuanShi_key_cMainMaterial   ,map_row_data,FORMAT_STRING,pData->m_strMainMaterial     );//51 
         pData->InsertRowData(DBKuanShi_key_cVersionNum     ,map_row_data,FORMAT_STRING,pData->m_strVersionNum       );//52
         pData->InsertRowData(DBKuanShi_key_cSinglePerson   ,map_row_data,FORMAT_STRING,pData->m_strSinglePerson     );//55
         // 版房新增款式表数据-----end liuhw 2019/05/08
         pData->InsertRowData(DBVStyle_key_cCheckState      ,map_row_data,FORMAT_STRING,pData->m_nCheckState == CDBStyle_CheckRecordsData::en_CheckIn ? _T("检入") : _T("检出")          );//52
         pData->InsertRowData(DBVStyle_key_cCheckPerson     ,map_row_data,FORMAT_STRING,pData->m_strCheckPerson     );//55
         pData->InsertRowData(DBVStyle_key_cFangAnName      ,map_row_data,FORMAT_STRING,pData->m_strFangAnName     );//57
         pData->InsertRowData(DBVStyle_key_nVersionState    ,map_row_data,FORMAT_INT,pData->m_nVersionState     );//56
         pData->InsertRowData(DBVStyle_key_cVersionPerson   ,map_row_data,FORMAT_STRING,pData->m_strVersionPerson     );//57
         map_all_data.insert(make_pair(map_all_data.size(),map_row_data));
      }
   }
	return map_all_data;
}
MAP_GridCtrl_AllData CDBStyleInfoList_V::CreatrGridData_Kuanhao()
{
   MAP_GridCtrl_AllData  map_all_data;

   POSITION pos = this->GetHeadPosition();
   while(pos != NULL)
   {
      CDBStyleInfoData_V* pData =(CDBStyleInfoData_V*)this->GetNext(pos);
      if (pData)
      {
         MAP_GridCtrl_RowData map_row_data;
         pData->InsertRowData(DBKuanShi_key_StyleNo		,map_row_data,FORMAT_STRING	,pData->m_strStyleNo);
         map_all_data.insert(make_pair(map_all_data.size(),map_row_data));
      }
   }
   return map_all_data;
}
//生成一条空的行数据		by WangZY 2017/08/24
BOOL CDBStyleInfoList_V::GetEmptyRowData(__out MAP_GridCtrl_RowData &mapEmptyRowData)
{
	mapEmptyRowData.clear();

	InsertRowData(DBKuanShi_key_ID					,_T(""),mapEmptyRowData,CB_enum_FieldData_Int,CB_enum_FieldCtrl_Text);
   InsertRowData(DBKuanShi_key_iFollow				,_T(""),mapEmptyRowData,CB_enum_FieldData_Int,CB_enum_FieldCtrl_Text);
   InsertRowData(DBKuanShi_key_iShell	,_T(""),mapEmptyRowData,CB_enum_FieldData_Int,CB_enum_FieldCtrl_Text);

	InsertRowData(DBKuanShi_key_UpdateTime			,_T(""),mapEmptyRowData,CB_enum_FieldData_Time,CB_enum_FieldCtrl_DateTime);
	InsertRowData(DBKuanShi_key_KindName			,_T(""),mapEmptyRowData);
	InsertRowData(DBKuanShi_key_StyleNo				,_T(""),mapEmptyRowData);
	InsertRowData(DBKuanShi_key_StyleName			,_T(""),mapEmptyRowData);
	InsertRowData(DBKuanShi_key_CreateTime			,_T(""),mapEmptyRowData,CB_enum_FieldData_Time,CB_enum_FieldCtrl_DateTime);


   // 版房新增款式表数据-----start liuhw 2019/05/08
    InsertRowData(DBKuanShi_key_dtExpireTime    ,_T(""),mapEmptyRowData,CB_enum_FieldData_Time,CB_enum_FieldCtrl_DateTime);
    InsertRowData(DBKuanShi_key_cCreator        ,_T(""),mapEmptyRowData);
    InsertRowData(DBKuanShi_key_cCreateType     ,_T(""),mapEmptyRowData);
    InsertRowData(DBKuanShi_key_cTheme          ,_T(""),mapEmptyRowData);
    InsertRowData(DBKuanShi_key_cCusCode       ,_T(""),mapEmptyRowData);
    InsertRowData(DBKuanShi_key_cCusKuanHao     ,_T(""),mapEmptyRowData);
    InsertRowData(DBKuanShi_key_cEdition        ,_T(""),mapEmptyRowData);

     InsertRowData(DBVStyle_key_cDesigner       ,_T(""),mapEmptyRowData);
     InsertRowData(DBKuanShi_key_dtMakingOrdTime ,_T(""),mapEmptyRowData);  
     InsertRowData(DBKuanShi_key_cMainMaterial   ,_T(""),mapEmptyRowData);
     InsertRowData(DBKuanShi_key_cVersionNum     ,_T(""),mapEmptyRowData);
     InsertRowData(DBVStyle_key_cCraftsmen       ,_T(""),mapEmptyRowData);
     InsertRowData(DBVStyle_key_cPatternMaker    ,_T(""),mapEmptyRowData);
     InsertRowData(DBKuanShi_key_cSinglePerson   ,_T(""),mapEmptyRowData);
     InsertRowData(DBVStyle_key_cCheckState      ,_T(""),mapEmptyRowData);
     InsertRowData(DBVStyle_key_cCheckPerson     ,_T(""),mapEmptyRowData);
     InsertRowData(DBVStyle_key_cState           ,_T(""),mapEmptyRowData);
     InsertRowData(DBVStyle_key_cFangAnName      ,_T(""),mapEmptyRowData);
     InsertRowData(DBVStyle_key_nVersionState    ,_T(""),mapEmptyRowData);
     InsertRowData(DBVStyle_key_cVersionPerson   ,_T(""),mapEmptyRowData);
   // 版房新增款式表数据-----end liuhw 2019/05/08

	return TRUE;
}


//批量提交数据修改		by WangZY 2017/08/24
BOOL CDBStyleInfoList_V::SaveMultiModifyData(__in CADOConn *pADOConn,
											__in MAP_GridCtrl_AllData &mapAddData,
											__in MAP_GridCtrl_AllData &mapModifyData,
											__in MAP_GridCtrl_AllData &mapDeleteData,
											__in CString strMaker)
{
	ASSERT(pADOConn != NULL);
	//需要提交代码		by WangZY 2017/08/27

   std::list<CString> lstSQL;
	CString strSQL = _T("");

#pragma region 款式批量删除

   CString strDelLog;
	//执行删除
	for (auto it=mapDeleteData.begin(); it!=mapDeleteData.end(); ++it)
	{
		CString strId;
		auto itData = it->second.find(DBKuanShi_key_ID);
		if (itData == it->second.end())
		{
			return FALSE;
		}
		strId = itData->second.strValue;

		strSQL.Format(_T("Delete FROM %s where %s='%s';"),
			DB_TABLE_STYLE,DBKuanShi_key_ID,strId);
		
      lstSQL.push_back(strSQL);
		//pADOConn->AppendBatchSQL(strSQL);
      strDelLog += strId +_T(",");
	}

   if (!strDelLog.IsEmpty())
   {
      CString strSQLLog;

      strSQLLog.Format(_T("insert into WorkLog(cCate,cType,cCode,cMaker,cMemo) \
                          values('款式','款式批量删除','%s','%s','%s') ;"),
                          _T(""),strMaker,strDelLog);

      //pADOConn->AppendBatchSQL(strSQLLog);
      lstSQL.push_back(strSQL);
   }
#pragma endregion 款式批量删除

#pragma region 款式批量修改
	//执行修改
   CString strUpdateLog;
	for (auto it=mapModifyData.begin(); it!=mapModifyData.end(); ++it)
	{
		CString strValueSet; 
      CString strFilter;
      CString strId;
      for (auto itField=it->second.begin(); itField!=it->second.end(); ++itField)
      {
         if(itField->first == DBKuanShi_key_ID)
         {
            strId = itField->second.strValue;
            strFilter.Format(_T(" where %s='%s' "),
               DBKuanShi_key_ID,strId);
         }
         else
         {
            CString strValue;
            /*if (itField->first == DBKuanShi_key_iFanLiFlag)
            {
               strValue.Format(_T("%s='%d'"),
                  itField->first,
                  (itField->second.strValue==_T("否")?0:1));
            }
            else*/
            {
               strValue.Format(_T("%s='%s'"),
                  itField->first,
                  itField->second.strValue);
            }
            
            if (strValueSet.IsEmpty())
            {
               strValueSet.Format(_T("Update %s set %s"),
                  DB_TABLE_STYLE,
                  strValue);
            }
            else
            {
               strValueSet += _T(",");
               strValueSet += strValue;
            }
         }
      }

      strSQL.Format(_T("%s %s ;"),strValueSet,strFilter);
      //pADOConn->AppendBatchSQL(strSQL);
      lstSQL.push_back(strSQL);
      strUpdateLog += strId + _T(",");
   }

   if (!strUpdateLog.IsEmpty())
   {
      CString strSQLLog;

      strSQLLog.Format(_T("insert into WorkLog(cCate,cType,cCode,cMaker,cMemo) \
                          values('款式','款式批量修改','%s','%s','%s') ;"),
                          _T(""),strMaker,strUpdateLog);

      //pADOConn->AppendBatchSQL(strSQLLog);
      lstSQL.push_back(strSQL);
   }
#pragma endregion 款式批量修改

#pragma region 款式批量新增
	//执行新增
   CString strAddLog;
   for (auto it=mapAddData.begin(); it!=mapAddData.end(); ++it)
   {
      CString strValueSet; 
      CString strValueKey;
      CString strStyleNo;
      for (auto itField=it->second.begin(); itField!=it->second.end(); ++itField)
      {
         if(itField->first == DBKuanShi_key_ID)
         {
            continue;
         }
         else
         {
            if (itField->first == DBKuanShi_key_StyleNo)
            {
               strStyleNo = itField->first;
            }

            CString strValue;
           
            /*if (itField->first == DBKuanShi_key_iFanLiFlag)
            {
               strValue.Format(_T("'%s'"),(itField->second.strValue==_T("否")?0:1));
            }
            else*/
            {
               strValue.Format(_T("'%s'"),itField->second.strValue);
            }
            
            
            if (strValueSet.IsEmpty())
            {
               strValueKey = itField->first;
               strValueSet = strValue;
            }
            else
            {
               strValueKey += _T(",");
               strValueKey = itField->first;

               strValueSet += _T(",");
               strValueSet += strValue;
            }
         }
      }

      strSQL.Format(_T("insert into %s(%s) value(%s) ;"),strValueKey,strValueSet);
      //pADOConn->AppendBatchSQL(strSQL);
      lstSQL.push_back(strSQL);
      strAddLog += strStyleNo + _T(",");
   }

   if (!strAddLog.IsEmpty())
   {
      CString strSQLLog;

      strSQLLog.Format(_T("insert into WorkLog(cCate,cType,cCode,cMaker,cMemo) \
                          values('款式','款式批量新增','%s','%s','%s') ;"),
                          _T(""),strMaker,strAddLog);

      //pADOConn->AppendBatchSQL(strSQLLog);
      lstSQL.push_back(strSQL);
   }
#pragma endregion 款式批量新增	


   BOOL bBegin = pADOConn->BeginTrans();
   if (!bBegin)
   {
      return FALSE;
   }

   BOOL bExec = TRUE;
   for (auto it=lstSQL.begin();it!=lstSQL.end(); ++it)
   {
      bExec = pADOConn->ExecuteSQL(*it);
      if (!bExec)
      {
         break;
      }
   }
   //BOOL bExec = pADOConn->ExecuteBatchSQL();
   if (!bExec)
   {
      BOOL bRollback = pADOConn->RollbackTrans();

      return FALSE;
   }
   BOOL bCommit = pADOConn->CommitTrans();
   if (!bCommit)
   {
      return FALSE;
   }

	return TRUE;
}

MAP_GridCtrl_RowData CDBStyleInfoList_V::GetRowData(CDBStyleInfoData_V* pData)
{
   MAP_GridCtrl_RowData map_row_data;
   if (pData)
   {
      pData->InsertRowData(DBKuanShi_key_ID				,map_row_data,CB_enum_FieldData_Int,CB_enum_FieldCtrl_Text,FORMAT_INT	,pData->m_nID);
      pData->InsertRowData(DBKuanShi_key_iFollow				,map_row_data,CB_enum_FieldData_Int,CB_enum_FieldCtrl_Text,FORMAT_INT	,pData->m_iFollow);
      pData->InsertRowData(DBKuanShi_key_iShell		,map_row_data,CB_enum_FieldData_Int,CB_enum_FieldCtrl_Text,FORMAT_INT	,pData->m_iUpOrDownShell);

      //2017/08/03 zhangt 款式维护中日期的显示
      if(pData->m_oleUpdateTime.m_status == COleDateTime::valid)
         pData->InsertRowData(DBKuanShi_key_UpdateTime		,map_row_data,CB_enum_FieldData_Time,CB_enum_FieldCtrl_DateTime,FORMAT_STRING	,pData->m_oleUpdateTime.Format(_T("%Y-%m-%d"))); //%H:%M:%S
      else
         pData->InsertRowData(DBKuanShi_key_UpdateTime		,map_row_data,CB_enum_FieldData_Time,CB_enum_FieldCtrl_DateTime,FORMAT_STRING	,_T(""));
      //2017/08/03_end
      pData->InsertRowData(DBKuanShi_key_KindName		,map_row_data,FORMAT_STRING	,pData->m_strTypeName		);

      pData->InsertRowData(DBKuanShi_key_StyleNo		,map_row_data,FORMAT_STRING	,pData->m_strStyleNo		);
      
      pData->InsertRowData(DBKuanShi_key_StyleName		,map_row_data,FORMAT_STRING	,pData->m_strStyleName		);

      //2017/08/11 zhangt 款式维护 创建时间 显示
      if(pData->m_oledtCreatTime.m_status == COleDateTime::valid)
         pData->InsertRowData(DBKuanShi_key_CreateTime		,map_row_data,CB_enum_FieldData_Time,CB_enum_FieldCtrl_DateTime,FORMAT_STRING	,pData->m_oledtCreatTime.Format(_T("%Y-%m-%d %H:%M:%S")));
      else
         pData->InsertRowData(DBKuanShi_key_CreateTime		,map_row_data,CB_enum_FieldData_Time,CB_enum_FieldCtrl_DateTime,FORMAT_STRING	,_T("")	);
      //2017/08/11_end

      pData->InsertRowData(DBKuanShi_key_cPinMing			,map_row_data,pData->m_strPinMing		);
      pData->InsertRowData(DBKuanShi_key_KsYears			,map_row_data,pData->m_strKsYears);
      pData->InsertRowData(DBVStyle_key_cCraftsmen   ,map_row_data,FORMAT_STRING	,pData->m_strCraftsmen			);
      pData->InsertRowData(DBVStyle_key_cPatternMaker,map_row_data,FORMAT_STRING	,pData->m_strPatternMaker			);

      // 版房新增款式表数据-----start liuhw 2019/05/08
      pData->InsertRowData(DBKuanShi_key_dtExpireTime    ,map_row_data,CB_enum_FieldData_Time,CB_enum_FieldCtrl_DateTime,FORMAT_STRING, pData->m_dtExpireTime);
      pData->InsertRowData(DBKuanShi_key_cCreator        ,map_row_data,FORMAT_STRING, pData->m_strCreator);
      pData->InsertRowData(DBKuanShi_key_cCreateType     ,map_row_data,FORMAT_STRING, pData->m_strCreateType);
      pData->InsertRowData(DBKuanShi_key_cTheme          ,map_row_data,FORMAT_STRING, pData->m_strTheme);
      pData->InsertRowData(DBKuanShi_key_cCusCode       ,map_row_data,FORMAT_STRING, pData->m_strCusCode);
      pData->InsertRowData(DBKuanShi_key_cCusKuanHao     ,map_row_data,FORMAT_STRING, pData->m_strCusKuanhao);
      if (pData->m_strProcessStatus.IsEmpty())
      {
         pData->InsertRowData(DBVStyle_key_cState    ,map_row_data,FORMAT_STRING,pData->m_strState     );//56
      }
      else
      {
         pData->InsertRowData(DBVStyle_key_cState    ,map_row_data,FORMAT_STRING, pData->m_strProcessStatus);
      }
      pData->InsertRowData(DBKuanShi_key_cEdition        ,map_row_data,FORMAT_STRING, pData->m_strEdition);
      pData->InsertRowData(DBVStyle_key_cDesigner       ,map_row_data,FORMAT_STRING,pData->m_strDesigner         );//49
      pData->InsertRowData(DBKuanShi_key_dtMakingOrdTime ,map_row_data,FORMAT_STRING,pData->m_dtMakingOrdTime   );//50     
      pData->InsertRowData(DBKuanShi_key_cMainMaterial   ,map_row_data,FORMAT_STRING,pData->m_strMainMaterial     );//51 
      pData->InsertRowData(DBKuanShi_key_cVersionNum     ,map_row_data,FORMAT_STRING,pData->m_strVersionNum       );//52
      pData->InsertRowData(DBKuanShi_key_cSinglePerson   ,map_row_data,FORMAT_STRING,pData->m_strSinglePerson     );//55
      pData->InsertRowData(DBVStyle_key_cCheckState      ,map_row_data,FORMAT_STRING,pData->m_nCheckState == CDBStyle_CheckRecordsData::en_CheckOut ? _T("检出") : _T("检入")     );//55
      pData->InsertRowData(DBVStyle_key_cCheckPerson     ,map_row_data,FORMAT_STRING,pData->m_strCheckPerson    );//55
      pData->InsertRowData(DBVStyle_key_cFangAnName      ,map_row_data,FORMAT_STRING,pData->m_strFangAnName     );//57
      pData->InsertRowData(DBVStyle_key_nVersionState    ,map_row_data,FORMAT_INT,pData->m_nVersionState     );//58
      pData->InsertRowData(DBVStyle_key_cVersionPerson   ,map_row_data,FORMAT_STRING,pData->m_strVersionPerson     );//59

      // 版房新增款式表数据-----end liuhw 2019/05/08

   }
   return map_row_data;
}

#endif // USING_GRIDCTRL_MARK

BOOL CDBStyleInfoList_V::GetStyleInfo(CADOConn* pADOConn,CString strKuanhao,__out CDBStyleInfoData_V* pObj)
{
   if (pObj == NULL)
      return FALSE;

   ASSERT(pADOConn != NULL);

   CString strSql = _T("");
   strSql.Format(_T("select * from %s where %s = '%s';"),DB_VIEW_KUANSHI,DBVStyle_key_cKuanhao,strKuanhao);

   pADOConn->GetRecordSet(strSql);
   if(!pADOConn->adoEOF())
   {
      pObj->GetAllDBInfo(pADOConn);
   }
   return TRUE;
}

//根据款号获取修改时间		by WangZY 2018/08/31
BOOL CDBStyleInfoList_V::GetStyleUpdateDateByStyleNo(__in CADOConn* pADOConn, 
   __in CString strKuanhao, __out CString &strDate)
{
   ASSERT(pADOConn != NULL);

   CString strSql = _T("");
   
   strSql.Format(_T("select %s from %s where %s='%s' ;"),
      DBKuanShi_key_UpdateTime,
      DB_TABLE_STYLE,
      DBKuanShi_key_StyleNo,
      strKuanhao);
                    
   pADOConn->GetRecordSet(strSql);
   if(!pADOConn->adoEOF())
   {
      strDate = pADOConn->GetValueString(DBKuanShi_key_UpdateTime);

      return TRUE;
   }

   return FALSE;
}
