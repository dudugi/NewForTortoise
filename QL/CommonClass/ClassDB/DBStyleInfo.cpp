#include "StdAfx.h"
#include "DBStyleInfo.h"
#include "CommonAPI.h"
#include "DBVariousStyleInfo.h"
#include "DBProSet_Style.h"
#include "DBYarnInfo.h"
#include "DBKeyDef.h"

IMPLEMENT_SERIAL(CDBStyleInfoData,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBStyleInfoList,  CDataListMid, 1)

std::shared_ptr<CDBStyleInfoData> CDBStyleInfoData::sm_inst;
std::shared_ptr<CDBStyleInfoList> CDBStyleInfoList::sm_inst;


CDBStyleInfoData::CDBStyleInfoData()
{
     ResetData();
} 

CDBStyleInfoData::~CDBStyleInfoData()
{
}

void CDBStyleInfoData::ResetData()
{
	m_nID = 0;
	m_oleTimeCreate = COleDateTime::GetCurrentTime();
	m_oleTimeUpdate = COleDateTime::GetCurrentTime();
	m_strTypeName = _T("");
	m_strStyleNo = _T("");
	m_strStyleName = _T("");
   m_strYarnCate = _T("");
	m_strStyleIntro = _T("");
   m_strKsYears   = _T("");   //年份季度 lida 2018/06/29
   m_strActLog = _T("");

   m_nIncreaceNum = 0;
   m_nColorSuitNum = 0;
   m_nColorNum = 0;
   m_iUpOrDownShell = 0;  //上下架 1上架 0下架
   m_iFollow = 0;         //关注 1关注 0不关注

   m_strBasicNum = _T("");
   m_dtExpireTime = _T("");    //到期日期
   m_strCreator = _T("");        //创建人
   m_strCreateType = _T("");     //创建类型
   m_strTheme = _T("");          //主题
   m_strEdition = _T("");        //版本
   m_strCusCode = _T("");       //客户
   m_strCusKuanhao = _T("");     //客户款号
   m_strProcessStatus = _T("");  //工序状态
   m_dtMakingOrdTime = _T(""); //定版日期
   m_strMainMaterial = _T("");   //主原料
   m_strVersionNum = _T("");     //版单号
   m_strSinglePerson = _T("");   //制单人
   m_strPinMing = _T("");
   m_bIsDeleted = 0;//款式是否删除 yangjr 2019/05/20
   m_strMainPic = _T("");
   m_strState = _T("");
   m_strFangAnName = _T("");
   m_strPrority= _T("");  //优先级
   m_strNeedleType= _T("");  //针型
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
   m_dTotalOffer =0;    //总报价

   m_nGXSortID = 0;
   m_strGxPersonCode = _T("");

   SetDataType(DAT_STYLE);
}

void CDBStyleInfoData::Copy(CDBStyleInfoData *pData)
{
	ASSERT(pData != NULL);
	CDataMid::Copy(pData);
	m_nID = pData->m_nID;
	m_oleTimeUpdate = pData->m_oleTimeUpdate;
	m_strTypeName = pData->m_strTypeName;
	m_strStyleNo = pData->m_strStyleNo;
	m_strStyleName = pData->m_strStyleName;
   m_strYarnCate = pData->m_strYarnCate;
	m_strStyleIntro = pData->m_strStyleIntro;
	m_oleTimeCreate = pData->m_oleTimeCreate;
   m_strKsYears = pData->m_strKsYears;
   m_nColorNum = pData->m_nColorNum;
   m_nColorSuitNum = pData->m_nColorSuitNum;
   m_nIncreaceNum = pData->m_nIncreaceNum;
   m_strBasicNum = pData->m_strBasicNum;

   m_dtExpireTime = pData->m_dtExpireTime;    //到期日期
   m_strCreator = pData->m_strCreator;        //创建人
   m_strCreateType = pData->m_strCreateType;     //创建类型
   m_strTheme = pData->m_strTheme;          //主题
   m_strEdition = pData->m_strEdition;        //版本
   m_strCusCode = pData->m_strCusCode;       //客户
   m_strCusKuanhao = pData->m_strCusKuanhao;     //客户款号
   m_strProcessStatus = pData->m_strProcessStatus;  //工序状态

   m_dtMakingOrdTime = pData->m_dtMakingOrdTime; //定版日期
   m_strMainMaterial = pData->m_strMainMaterial;   //主原料
   m_strVersionNum = pData->m_strVersionNum;     //版单号
   m_strSinglePerson = pData->m_strSinglePerson;   //制单人
   m_strPinMing      = pData->m_strPinMing;
   m_bIsDeleted = pData->m_bIsDeleted;//款式是否删除 yangjr 2019/05/20
   m_iFollow         = pData->m_iFollow;//关注
   m_iUpOrDownShell  = pData->m_iUpOrDownShell;//上下架
   m_strMainPic = pData->m_strMainPic;
   m_strState = pData->m_strState;
   m_strFangAnName = pData->m_strFangAnName;
   m_strPrority =pData->m_strPrority;  //优先级
   m_strNeedleType=pData->m_strNeedleType;  //针型
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

   m_nGXSortID       = pData->m_nGXSortID;
   m_strGxPersonCode = pData->m_strGxPersonCode;
}

BOOL CDBStyleInfoData::GetAllDBInfo(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);

	BOOL bRet = TRUE;

	if (NULL == pADOConn)
	{
		bRet = FALSE;
	}
	else
	{
		m_nID				= _ttoi(pADOConn->GetValueString(DBKuanShi_key_ID));
		m_oleTimeUpdate		= QLCOMAPI.CString2OleDateTime(pADOConn->GetValueString(DBKuanShi_key_UpdateTime));
		m_strTypeName		= pADOConn->GetValueString(DBKuanShi_key_KindName);
		m_strStyleNo		= pADOConn->GetValueString(DBKuanShi_key_StyleNo);
		m_strStyleName		= pADOConn->GetValueString(DBKuanShi_key_StyleName);
      m_strYarnCate     = pADOConn->GetValueString(DBKuanShi_key_YarnCate);
		m_strStyleIntro		= pADOConn->GetValueString(DBKuanShi_key_StyleIntro);
		m_oleTimeCreate		= pADOConn->GetValueDate(DBKuanShi_key_CreateTime);
      m_strKsYears      = pADOConn->GetValueString(DBKuanShi_key_KsYears);
      m_nColorNum       = pADOConn->GetValueInt(DBKuanShi_key_nColorNum);
      m_nColorSuitNum   = pADOConn->GetValueInt(DBKuanShi_key_nColorSuitNum);
      m_nIncreaceNum    = pADOConn->GetValueInt(DBKuanShi_key_nIncreaseNum);
      m_strBasicNum     = pADOConn->GetValueString(DBKuanShi_key_cBasicSize);
      m_dtExpireTime = pADOConn->GetValueString(DBKuanShi_key_dtExpireTime);    //到期日期
      m_strCreator = pADOConn->GetValueString(DBKuanShi_key_cCreator);        //创建人
      m_strCreateType = pADOConn->GetValueString(DBKuanShi_key_cCreateType);     //创建类型
      m_strTheme = pADOConn->GetValueString(DBKuanShi_key_cTheme);          //主题
      m_strEdition = pADOConn->GetValueString(DBKuanShi_key_cEdition);        //版本
      m_strCusCode = pADOConn->GetValueString(DBKuanShi_key_cCusCode);       //客户
      m_strCusKuanhao = pADOConn->GetValueString(DBKuanShi_key_cCusKuanHao);     //客户款号
      m_strProcessStatus = pADOConn->GetValueString(DBKuanShi_key_cProcessStatus);  //工序状态
      m_dtMakingOrdTime = pADOConn->GetValueString(DBKuanShi_key_dtMakingOrdTime); //定版日期
      m_strMainMaterial = pADOConn->GetValueString(DBKuanShi_key_cMainMaterial);   //主原料
      m_strVersionNum = pADOConn->GetValueString(DBKuanShi_key_cVersionNum);     //版单号
      m_strSinglePerson = pADOConn->GetValueString(DBKuanShi_key_cSinglePerson);   //制单人
      m_strPinMing		= pADOConn->GetValueString(DBKuanShi_key_cPinMing		);
      m_bIsDeleted = pADOConn->GetValueInt(DBKuanShi_key_bIsDeleted		);;//款式是否删除 yangjr 2019/05/20
      m_iFollow         = pADOConn->GetValueInt(DBKuanShi_key_iFollow);//关注
      m_iUpOrDownShell  = pADOConn->GetValueInt(DBKuanShi_key_iShell);//上下架      bRet = TRUE;
      m_strMainPic      = pADOConn->GetValueString(DBKuanShi_key_cMainPic);   //主图
      m_strState        = pADOConn->GetValueString(DBKuanShi_key_cState);//状态
      m_strFangAnName   = pADOConn->GetValueString(DBKuanShi_key_cFangAnName);//方案名称
      m_strPrority  = pADOConn->GetValueString(DBKuanShi_key_cPriority);  //优先级
      m_strNeedleType  = pADOConn->GetValueString(DBKuanShi_key_cNeedleType);  //针型
      m_strModelMainPic = pADOConn->GetValueString(DBKuanShi_key_cModelMainPic);
      m_nSortIndex      = pADOConn->GetValueInt(DBKuanShi_key_nSortIndex);
      m_strBrand = pADOConn->GetValueString(DBKuanShi_key_cBrand);
      m_strCustomField1  = pADOConn->GetValueString(DBKuanShi_key_cCustomField1 );
      m_strCustomField2  = pADOConn->GetValueString(DBKuanShi_key_cCustomField2 );
      m_strCustomField3  = pADOConn->GetValueString(DBKuanShi_key_cCustomField3 );
      m_strCustomField4  = pADOConn->GetValueString(DBKuanShi_key_cCustomField4 );
      m_strCustomField5  = pADOConn->GetValueString(DBKuanShi_key_cCustomField5 );
      m_strCustomField6  = pADOConn->GetValueString(DBKuanShi_key_cCustomField6 );
      m_strCustomField7  = pADOConn->GetValueString(DBKuanShi_key_cCustomField7 );
      m_strCustomField8  = pADOConn->GetValueString(DBKuanShi_key_cCustomField8 );
      m_strCustomField9  = pADOConn->GetValueString(DBKuanShi_key_cCustomField9 );
      m_strCustomField10 = pADOConn->GetValueString(DBKuanShi_key_cCustomField10);

      m_dTotalCost = pADOConn->GetValueDouble(DBKuanShi_key_dTotalCost);     //总成本
      m_dTotalOffer = pADOConn->GetValueDouble(DBKuanShi_key_dTotalOffer);    //总报价

      m_nGXSortID        = pADOConn->GetValueInt(DBKuanShi_key_iGXSortID);
      m_strGxPersonCode  = pADOConn->GetValueString(DBKuanShi_key_cGxPersonCode);
   }

	return bRet;
}

//获取【整条】信息 yangjr 2018-3-29
BOOL CDBStyleInfoData::GetAllDBInfoByKuanHao(CADOConn *pADOConn,CString strKuanhao)
{
   if (!pADOConn)
   {
      return FALSE;
   }
   CString strSQL = _T("");
   strSQL.Format(_T("select * from %s where %s='%s'"),DB_TABLE_STYLE,DBKuanShi_key_StyleNo,strKuanhao);
   pADOConn->GetRecordSet(strSQL);
   if (!pADOConn->adoEOF())
   {
      GetAllDBInfo(pADOConn);
      return TRUE;
   }
   return FALSE;
}

BOOL CDBStyleInfoData::InsertAllDBInfoByStyleNo( CADOConn *pADOConn )
{
	ASSERT(pADOConn != NULL);
	m_strStyleNo.Trim();
	ASSERT(!m_strStyleNo.IsEmpty());

	BOOL bRet = TRUE;

	CString strSQL = _T(""),strFormat = _T(""),strValues = _T("");

	//					          1 ,2 ,3 ,4 ,5 ,6 ,7 ,8 ,9 ,10
	strFormat.Format(_T("    %s,%s,%s,%s,%s,%s   ,%s,%s,%s\
						         ,%s,%s,%s,%s,%s,%s,%s,%s,%s\
						         ,%s   ,%s   ,%s,%s,%s      ,%s\
                           ,%s,%s,%s,%s,%s,%s   ,%s,%s,%s\
                           ,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\
                           ,%s,%s,%s"),
						DBKuanShi_key_UpdateTime      ,//1
						DBKuanShi_key_KindName        ,//2
						DBKuanShi_key_StyleNo         ,//3
						DBKuanShi_key_StyleName       ,//4
                  DBKuanShi_key_StyleIntro      ,//5
                  DBKuanShi_key_CreateTime      ,//6
                  DBKuanShi_key_YarnCate        ,//8
                  DBKuanShi_key_KsYears         ,//9
                  DBKuanShi_key_nColorNum       ,//10
                  DBKuanShi_key_nColorSuitNum   ,//11
                  DBKuanShi_key_nIncreaseNum    ,//12
                  DBKuanShi_key_cBasicSize      ,//13
                  DBKuanShi_key_dtExpireTime    ,//14
                  DBKuanShi_key_cCreator        ,//15
                  DBKuanShi_key_cCreateType     ,//16
                  DBKuanShi_key_cTheme          ,//17
                  DBKuanShi_key_cCusCode        ,//18
                  DBKuanShi_key_cCusKuanHao     ,//19
                  DBKuanShi_key_cProcessStatus  ,//21
                  DBKuanShi_key_cEdition        ,//23
                  DBKuanShi_key_dtMakingOrdTime ,//25
                  DBKuanShi_key_cMainMaterial   ,//26
                  DBKuanShi_key_cVersionNum     ,//27
                  DBKuanShi_key_cSinglePerson   ,//30
                  DBKuanShi_key_cPinMing        ,//31
                  DBKuanShi_key_iFollow         ,//32
                  DBKuanShi_key_iShell   ,//33
                  DBKuanShi_key_cMainPic,//34
                  DBKuanShi_key_cState,
                  DBKuanShi_key_cFangAnName,
                  DBKuanShi_key_cPriority,
                  DBKuanShi_key_cNeedleType,
                  DBKuanShi_key_cModelMainPic,
                  DBKuanShi_key_cCustomField1 ,
                  DBKuanShi_key_cCustomField2 ,
                  DBKuanShi_key_cCustomField3 ,
                  DBKuanShi_key_cCustomField4 ,
                  DBKuanShi_key_cCustomField5 ,
                  DBKuanShi_key_cCustomField6 ,
                  DBKuanShi_key_cCustomField7 ,
                  DBKuanShi_key_cCustomField8 ,
                  DBKuanShi_key_cCustomField9 ,
                  DBKuanShi_key_cCustomField10,
                  DBKuanShi_key_cBrand,
                  DBKuanShi_key_dTotalCost,
                  DBKuanShi_key_dTotalOffer
                  );

	CString strGetDateStr = DBS_GETDATESTR;

	strValues.Format(_T("%s,'%s','%s','%s','%s',%s,       '%s','%s','%d',\
                       '%d','%d','%s','%s','%s','%s','%s','%s','%s',\
                        '%s'    ,'%s'    ,'%s','%s','%s'          ,'%s',\
                        '%s','%d','%d','%s','%s','%s' ,'%s','%s','%s',\
                        '%s','%s','%s','%s','%s','%s','%s','%s','%s','%s',\
                        '%s',%.2f,%.2f"),
                        strGetDateStr     ,//1
                        m_strTypeName     ,//2
                        m_strStyleNo      ,//3
                        m_strStyleName    ,//4
                        m_strStyleIntro   ,//5
                        strGetDateStr     ,//6
                        m_strYarnCate     ,//8
                        m_strKsYears      ,//9
                        m_nColorNum       ,//10
                        m_nColorSuitNum   ,//11
                        m_nIncreaceNum    ,//12
                        m_strBasicNum     ,//13
                        m_dtExpireTime    ,//14
                        m_strCreator        ,//15
                        m_strCreateType     ,//16
                        m_strTheme          ,//17
                        m_strCusCode        ,//18
                        m_strCusKuanhao     ,//19
                        m_strProcessStatus  ,//21
                        m_strEdition        ,//23
                        m_dtMakingOrdTime   ,//25
                        m_strMainMaterial   ,//26
                        m_strVersionNum     ,//27
                        m_strSinglePerson   ,//30
                        m_strPinMing        ,//31
                        m_iFollow           ,//32
                        m_iUpOrDownShell     ,//33
                        m_strMainPic,
                        m_strState,
                        m_strFangAnName,
                        m_strPrority,
                        m_strNeedleType,
                        m_strModelMainPic,
                        m_strCustomField1 ,
                        m_strCustomField2 ,
                        m_strCustomField3 ,
                        m_strCustomField4 ,
                        m_strCustomField5 ,
                        m_strCustomField6 ,
                        m_strCustomField7 ,
                        m_strCustomField8 ,
                        m_strCustomField9 ,
                        m_strCustomField10,
                        m_strBrand,
                        m_dTotalCost,
                        m_dTotalOffer
      );

	strSQL.Format(_T("insert into %s(%s) values(%s)"),DB_TABLE_STYLE,strFormat,strValues);

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
BOOL CDBStyleInfoData::UpdateBasicInfoByStyleNo(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);
   BOOL bRet = FALSE;
   if (m_strStyleNo.IsEmpty())
   {
      return bRet;
   }
   CString strSQL = _T("");

   //								          1      ,2      ,3      ,4      ,5      ,6      ,7      ,8      ,9     ,10
   strSQL.Format(_T("Update %s set %s='%s',%s='%s',%s='%s',%s='%s',%s='%s',%s='%s',%s='%s',%s='%s',        %s='%s',\
                                   %s='%s',%s='%s'                ,%s='%s',%s='%s',%s='%d',%s='%d',%s = '%s', \
                                   %s = '%s',%s = '%s',%s = '%s',%s = '%s',%s = '%s',%s = '%s',%s = '%s',%s = '%s'\
                                   ,%s = '%s',%s = '%s',%s = '%s',%s = '%s',%s = '%s' where %s='%s'"),
                    DB_TABLE_STYLE,
                    DBKuanShi_key_KindName		  ,m_strTypeName	   ,//1
                    DBKuanShi_key_StyleName		  ,m_strStyleName		,//2
                    DBKuanShi_key_StyleIntro		  ,m_strStyleIntro	,//3
                    DBKuanShi_key_KsYears         ,m_strKsYears      ,//4
                    DBKuanShi_key_cTheme          ,m_strTheme        ,//5
                    DBKuanShi_key_cCusCode        ,m_strCusCode      ,//6
                    DBKuanShi_key_cCusKuanHao     ,m_strCusKuanhao   ,//7
                    DBKuanShi_key_cEdition        ,m_strEdition      ,//8
                    DBKuanShi_key_dtMakingOrdTime ,m_dtMakingOrdTime ,//10
                    DBKuanShi_key_cMainMaterial   ,m_strMainMaterial ,//11
                    DBKuanShi_key_cVersionNum     ,m_strVersionNum   ,//12
                    DBKuanShi_key_cSinglePerson   ,m_strSinglePerson ,//15
                    DBKuanShi_key_cPinMing        ,m_strPinMing      ,//16
                    DBKuanShi_key_iFollow         ,m_iFollow         ,//17
                    DBKuanShi_key_iShell          ,m_iUpOrDownShell  ,//18
                    DBKuanShi_key_cState          ,m_strState        ,//19
                    DBKuanShi_key_cPriority,    m_strPrority,
                    DBKuanShi_key_cNeedleType,  m_strNeedleType,
                    DBKuanShi_key_cCustomField1 ,m_strCustomField1 ,
                    DBKuanShi_key_cCustomField2 ,m_strCustomField2 ,
                    DBKuanShi_key_cCustomField3 ,m_strCustomField3 ,
                    DBKuanShi_key_cCustomField4 ,m_strCustomField4 ,
                    DBKuanShi_key_cCustomField5 ,m_strCustomField5 ,
                    DBKuanShi_key_cCustomField6 ,m_strCustomField6 ,
                    DBKuanShi_key_cCustomField7 ,m_strCustomField7 ,
                    DBKuanShi_key_cCustomField8 ,m_strCustomField8 ,
                    DBKuanShi_key_cCustomField9 ,m_strCustomField9 ,
                    DBKuanShi_key_cCustomField10,m_strCustomField10,
                    DBKuanShi_key_cBrand        ,m_strBrand,
                    DBKuanShi_key_StyleNo          ,m_strStyleNo	 //20
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

BOOL CDBStyleInfoData::UpdateAllDBInfoByStyleNo( CADOConn *pADOConn )
{
	ASSERT(pADOConn != NULL);
	m_strStyleNo.Trim();
	ASSERT(!m_strStyleNo.IsEmpty());

	BOOL bRet = TRUE;

	CString strSQL = _T("");
	CString strGetDateStr = DBS_GETDATESTR;

	//								  1      ,2      ,3      ,4      ,5      ,6      ,7      ,8      ,9      ,10
	strSQL.Format(_T("Update %s set %s=%s  ,%s='%s',%s='%s',%s='%s'         ,%s='%s',%s='%s',%s='%d',%s='%d',\
                            %s='%d',%s='%s',%s='%s',%s='%s',%s='%s',%s='%s',%s='%s',%s='%s',%s='%s',\
									 %s='%s'        ,%s='%s'        ,%s='%s',%s='%s',%s='%d'                ,%s = '%s'\
                            		,%s='%s',%s='%d',%s='%d',%s = '%s',%s = '%s',%s = '%s',%s = '%s',%s = '%s'\
                            ,%s = '%s',%s = '%s',%s = '%s',%s = '%s',%s = '%s',%s = '%s',%s = '%s',%s = '%s'\
                            ,%s = '%s',%s = '%s',%s =%.2f,%s =%.2f where %s='%d'"),
                           DB_TABLE_STYLE,
									DBKuanShi_key_UpdateTime		,strGetDateStr			,//1
									DBKuanShi_key_KindName			,m_strTypeName			,//2
									DBKuanShi_key_StyleNo			,m_strStyleNo			,//3
									DBKuanShi_key_StyleName			,m_strStyleName		,//4
									DBKuanShi_key_StyleIntro		,m_strStyleIntro		,//5
                           DBKuanShi_key_YarnCate        ,m_strYarnCate       ,//7
                           DBKuanShi_key_KsYears         ,m_strKsYears        ,//8
                           DBKuanShi_key_nColorNum       , m_nColorNum        ,//9
                           DBKuanShi_key_nColorSuitNum   , m_nColorSuitNum    ,//10
                           DBKuanShi_key_nIncreaseNum    , m_nIncreaceNum     ,//11
                           DBKuanShi_key_cBasicSize      , m_strBasicNum      ,//12
                           DBKuanShi_key_dtExpireTime    ,m_dtExpireTime      ,//13
                           DBKuanShi_key_cCreator        ,m_strCreator          ,//14
                           DBKuanShi_key_cCreateType     ,m_strCreateType       ,//15
                           DBKuanShi_key_cTheme          ,m_strTheme            ,//16
                           DBKuanShi_key_cCusCode        ,m_strCusCode          ,//17
                           DBKuanShi_key_cCusKuanHao     ,m_strCusKuanhao       ,//18
                           DBKuanShi_key_cProcessStatus  ,m_strProcessStatus    ,//20
                           DBKuanShi_key_cEdition        ,m_strEdition          ,//22
                           DBKuanShi_key_dtMakingOrdTime ,m_dtMakingOrdTime   ,//24
                           DBKuanShi_key_cMainMaterial   ,m_strMainMaterial     ,//25
                           DBKuanShi_key_cVersionNum     ,m_strVersionNum       ,//26
                           DBKuanShi_key_cSinglePerson   ,m_strSinglePerson     ,//29
                           DBKuanShi_key_cPinMing        ,m_strPinMing        ,//30
                           DBKuanShi_key_bIsDeleted      ,m_bIsDeleted        ,//31
                           DBKuanShi_key_iFollow         ,m_iFollow           ,
                           DBKuanShi_key_iShell  ,m_iUpOrDownShell    ,
                           DBKuanShi_key_cState          ,m_strState          ,
                           DBKuanShi_key_cFangAnName     ,m_strFangAnName,
                           DBKuanShi_key_cPriority,m_strPrority,
                           DBKuanShi_key_cNeedleType,m_strNeedleType,
                           DBKuanShi_key_cCustomField1 ,m_strCustomField1 ,
                           DBKuanShi_key_cCustomField2 ,m_strCustomField2 ,
                           DBKuanShi_key_cCustomField3 ,m_strCustomField3 ,
                           DBKuanShi_key_cCustomField4 ,m_strCustomField4 ,
                           DBKuanShi_key_cCustomField5 ,m_strCustomField5 ,
                           DBKuanShi_key_cCustomField6 ,m_strCustomField6 ,
                           DBKuanShi_key_cCustomField7 ,m_strCustomField7 ,
                           DBKuanShi_key_cCustomField8 ,m_strCustomField8 ,
                           DBKuanShi_key_cCustomField9 ,m_strCustomField9 ,
                           DBKuanShi_key_cCustomField10,m_strCustomField10,
                           DBKuanShi_key_cBrand       ,m_strBrand,
                           DBKuanShi_key_dTotalCost,m_dTotalCost,
                           DBKuanShi_key_dTotalOffer,m_dTotalOffer,
                           DBKuanShi_key_ID				   ,m_nID					 //30
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
BOOL CDBStyleInfoData::UpdateShellDBInfoByStyleNo(CADOConn *pADOConn,int iShell,CString strStyleNo)// 根据款号更新上下架 liuhw 2019/05/20
{
   ASSERT(pADOConn != NULL);
   BOOL bRet = FALSE;
   CString strSql = _T("");
   strSql.Format(_T("update %s set %s = '%d' where %s = '%s'"),
      DB_TABLE_STYLE,DBKuanShi_key_iShell,iShell,DBKuanShi_key_StyleNo,strStyleNo);
   bRet = pADOConn->ExecuteSQL(strSql);

   return bRet;
}

BOOL CDBStyleInfoData::UpdateFollowDBInfoByStyleNo(CADOConn *pADOConn,int iFollow,CString strStyleNo)// 根据款号更新上下架 liuhw 2019/05/20
{
   ASSERT(pADOConn != NULL);
   BOOL bRet = FALSE;
   CString strSql = _T("");
   strSql.Format(_T("update %s set %s = '%d' where %s = '%s'"),
      DB_TABLE_STYLE,DBKuanShi_key_iFollow,iFollow,DBKuanShi_key_StyleNo,strStyleNo);
   bRet = pADOConn->ExecuteSQL(strSql);

   return bRet;
}
CString CDBStyleInfoData::GetUpdateSizeInfoToBasicSize(CString strStyleNo,CString strBasicSize)// 更新款式的基本尺码 liuhw 2019/05/26
{
   CString strSql = _T("");
   if (!strStyleNo.IsEmpty())
   {
      strSql.Format(_T("update %s set %s = '%s' where %s = '%s'"),
         DB_TABLE_STYLE,DBKuanShi_key_cBasicSize,strBasicSize,DBKuanShi_key_StyleNo,strStyleNo);
   }
   return strSql;
}
BOOL CDBStyleInfoData::DelAllDBInfoByStyleNo( CADOConn *pADOConn )
{
   ASSERT(pADOConn != NULL);
   m_strStyleNo.Trim();
   ASSERT(!m_strStyleNo.IsEmpty());

   BOOL bRet = TRUE;

   CString strSQL = GetDelAllDBInfoByStyleNoSql(m_strStyleNo); 

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

CString CDBStyleInfoData::GetDelAllDBInfoByStyleNoSql(CString strStyleNo)
{
   CString strSQL = _T("");
   strSQL.Format(_T("delete from %s where %s='%s'"),DB_TABLE_STYLE,DBKuanShi_key_StyleNo,strStyleNo);   
   return strSQL;
}

BOOL CDBStyleInfoData::IsRepeatStyleNo(CADOConn *pADOConn)//判断款号是否重复
{
   ASSERT(pADOConn != NULL);
   if (m_strStyleNo.IsEmpty())
   {
      return TRUE;
   }
   CString strSql = _T("");
   strSql.Format(_T("select count(*) num from %s where %s = '%s'"),DB_TABLE_STYLE,DBKuanShi_key_StyleNo,m_strStyleNo);
   pADOConn->GetRecordSet(strSql);
   if(!pADOConn->adoEOF())
   {
      int num = pADOConn->GetValueInt(_T("num"));
      if (num > 0)
      {
         return TRUE;
      }
   }
   return FALSE;
}

CString CDBStyleInfoData::SetDBEquals_Log(CDBStyleInfoData &pOldData)
{
   CString strActLog = _T("");
   if (m_strTypeName != pOldData.m_strTypeName)
   {
      CString strTypeName;
      if (m_strTypeName.IsEmpty())
      {
         strTypeName = _T("空值");
      }
      strTypeName = m_strTypeName;
      strActLog += _T("类型名称:") + strTypeName + _T(",");

   }
   if (m_strStyleNo != pOldData.m_strStyleNo)
   {
      CString strStyleNo;
      if (m_strStyleNo.IsEmpty())
      {
         strStyleNo = _T("空值");
      }
      strStyleNo = m_strStyleNo;
      strActLog += _T("款式号:") + strStyleNo + _T(",");

   }
   if (m_strStyleName != pOldData.m_strStyleName)
   {
      CString strStyleName;
      if (m_strStyleName.IsEmpty())
      {
         strStyleName = _T("空值");
      }
      strStyleName = m_strStyleName;
      strActLog += _T("款式名称:") + strStyleName + _T(",");

   }
   if (m_strYarnCate  != pOldData.m_strYarnCate )
   {
      CString strYarnCate;
      if (m_strYarnCate .IsEmpty())
      {
         strYarnCate = _T("空值");
      }
      strYarnCate = m_strYarnCate;
      strActLog += _T("纱线类别:") + strYarnCate + _T(",");

   }
   if (m_strStyleIntro  != pOldData.m_strStyleIntro )
   {
      CString strStyleIntro;
      if (m_strStyleIntro .IsEmpty())
      {
         strStyleIntro = _T("空值");
      }
      strStyleIntro = m_strStyleIntro ;
      strActLog += _T("款式说明:") + strStyleIntro + _T(",");
   }

   if (m_strKsYears != pOldData.m_strKsYears )
   {
      CString strKsYears ;
      if (m_strKsYears.IsEmpty())
      {
         strKsYears  = _T("空值");
      }
      strKsYears = m_strKsYears ;
      strActLog += _T("年份季度:") + strKsYears  + _T(",");
   }
   if (m_nColorNum != pOldData.m_nColorNum)
   {
      CString strColorNum;
      strColorNum.Format(FORMAT_INT, m_nColorNum);
      if (strColorNum.IsEmpty())
      {
         strColorNum = _T("空值");
      }
      strActLog += _T("配色数:") + strColorNum + _T(",");
   }
   if (m_nColorSuitNum != pOldData.m_nColorSuitNum)
   {
      CString strColorSuitNum;
      strColorSuitNum.Format(FORMAT_INT, m_nColorSuitNum);
      if (strColorSuitNum.IsEmpty())
      {
         strColorSuitNum = _T("空值");
      }
      strActLog += _T("配色套数:") + strColorSuitNum + _T(",");
   }
   if (m_nIncreaceNum != pOldData.m_nIncreaceNum)
   {
      CString strIncreaceNum;
      strIncreaceNum.Format(FORMAT_INT, m_nIncreaceNum);
      if (strIncreaceNum.IsEmpty())
      {
         strIncreaceNum = _T("空值");
      }
      strActLog += _T("尺码重量递增:") + strIncreaceNum + _T(",");
   }
   if (m_strBasicNum != pOldData.m_strBasicNum)
   {
      CString strBasicNum;
      strBasicNum.Format(FORMAT_STRING, m_strBasicNum);
      if (strBasicNum.IsEmpty())
      {
         strBasicNum = _T("空值");
      }
      strActLog += _T("尺码重量递增:") + strBasicNum + _T(",");
   }
   if (m_strPinMing != pOldData.m_strPinMing )
   {
      CString strPinMing;
      if (m_strPinMing.IsEmpty())
      {
         strPinMing  = _T("空值");
      }
      strPinMing  = m_strPinMing ;
      strActLog += _T("品名:") + strPinMing  + _T(",");
   }
   if (m_strState != pOldData.m_strState )
   {
      CString strState;
      if (m_strState.IsEmpty())
      {
         strState  = _T("空值");
      }
      strState  = m_strPinMing ;
      strActLog += _T("状态:") + strState + _T(",");
   }
   return strActLog;
}

void CDBStyleInfoData::DestroyAllLinkInfo( CADOConn *pADOConn )
{
	ASSERT(NULL != pADOConn);
	ASSERT(!m_strStyleNo.IsEmpty());

	CString strSQL = _T("");

	strSQL.Format(_T("delete from %s where %s = '%s'"),DB_TABLE_VARIOUSSTYLE,DBVarious_key_StyleNo,m_strStyleNo);
	pADOConn->AppendBatchSQL(strSQL);

   strSQL.Format(_T("delete from %s where %s = '%s'"),DB_TABLE_PROSET_STYLE,DBProSet_Style_key_StyleNo,m_strStyleNo);
   pADOConn->AppendBatchSQL(strSQL);

	pADOConn->ExecuteBatchSQL();

	CDBProSet_StyleData oDBProSet_StyleClearData;
	oDBProSet_StyleClearData.m_strStyleNo = m_strStyleNo;
	oDBProSet_StyleClearData.ClearAllStyleInfo(pADOConn);
}

void CDBStyleInfoData::Trim()
{
	m_strTypeName.Trim();
	m_strStyleNo.Trim();
	m_strStyleName.Trim();
	m_strStyleIntro.Trim();
   m_strKsYears.Trim();
   m_strBasicNum.Trim();
   m_strPinMing.Trim();
}

CDBStyleInfoData * CDBStyleInfoData::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = shared_ptr<CDBStyleInfoData>(new CDBStyleInfoData);

	return sm_inst.get();
}

//************************************
// <函数>:   UpdateSetNewMainPicByStyleNo
// <说明>:   根据款式号设置主图信息
// <作者>:   Wangzy
// <日期>:   2019/05/16
// <Access>:public static 
// <Return>:BOOL：
// <参数>:   CADOConn * pADOConn
// <参数>:   CString strStyleNo
// <参数>:   CString strMainPicName
//************************************
BOOL CDBStyleInfoData::UpdateSetNewMainPicByStyleNo(CADOConn *pADOConn,CString strStyleNo, CString strMainPicName)
{
   BOOL bRet = FALSE;
   ASSERT(pADOConn);
   CString strSQL;

   strSQL.Format(_T("Update %s set %s='%s' where %s = '%s' ;"),
      DB_TABLE_STYLE,

      DBKuanShi_key_cMainPic,
      strMainPicName,

      DBKuanShi_key_StyleNo,
      strStyleNo);

   bRet = pADOConn->ExecuteSQL(strSQL);

   return bRet;
}

BOOL CDBStyleInfoData::UpdateSetNewModelMainPicByStyleNo(CADOConn *pADOConn,const CString & strStyleNo,const CString & strMainPicName)
{
   BOOL bRet = FALSE;
   ASSERT(pADOConn);
   CString strSQL;

   strSQL.Format(_T("Update %s set %s='%s' where %s = '%s' ;"),
      DB_TABLE_STYLE,

      DBKuanShi_key_cModelMainPic,
      strMainPicName,

      DBKuanShi_key_StyleNo,
      strStyleNo);

   bRet = pADOConn->ExecuteSQL(strSQL);

   return bRet;
}

CString CDBStyleInfoData::GetDelSqlString(int nID,int nIsDeleted)
{
   CString strSql = _T("");
   strSql.Format(_T("update %s set %s=%d where %s='%d';"),DB_TABLE_STYLE,DBKuanShi_key_bIsDeleted,nIsDeleted,DBKuanShi_key_ID,nID);
   return strSql;
}

CString CDBStyleInfoData::GetDelSqlByStyleNo(CString strStyleNo,int nIsDeleted)
{
   CString strSql = _T("");
   strSql.Format(_T("update %s set %s=%d where %s='%s';"),DB_TABLE_STYLE,DBKuanShi_key_bIsDeleted,nIsDeleted,DBKuanShi_key_StyleNo,strStyleNo);
   return strSql;
}

//CDBStyleInfoList
CDBStyleInfoList::CDBStyleInfoList()
{
	ResetData();
}
CDBStyleInfoList::~CDBStyleInfoList()
{

}

void CDBStyleInfoList::ResetData()
{
	m_nSaleCount = 0;
}

CDBStyleInfoData*  CDBStyleInfoList::GetItem(int nIndex)
{
	if (nIndex<0||nIndex>=GetCount())
		return NULL;
	return (CDBStyleInfoData*)GetAt(FindIndex(nIndex));
}
void CDBStyleInfoList::AddItem(CDBStyleInfoData* pItem)
{
	CDBStyleInfoData*pData=new CDBStyleInfoData;
	pData->Copy(pItem);
	//AddTail(pData);
	AddHead(pData);
}
void CDBStyleInfoList::DeleteItem(int nIndex)
{
	if (nIndex<0||nIndex>GetCount())
		return;
	CDBStyleInfoData *pObject=(CDBStyleInfoData*)GetItem(nIndex);
	delete pObject;
	pObject=NULL;
	RemoveAt(FindIndex(nIndex));
}

CDBStyleInfoData* CDBStyleInfoList::GetItemByStyleNo( CString strStyleNo )
{
	CDBStyleInfoData * pItem = NULL;
	strStyleNo.Trim();
	if (!strStyleNo.IsEmpty())
	{
		for(int i=0;i< GetCount();i++)
		{
			CDBStyleInfoData * pObject = GetItem(i);
			if(strStyleNo==pObject->m_strStyleNo)
			{
				pItem = pObject;
				break;
			}
		}
	}

	return pItem;
}

int CDBStyleInfoList::GetIndexByStyleNo( CString strStyleNo )
{
	int nSel = -1;
	strStyleNo.Trim();
	if (!strStyleNo.IsEmpty())
	{
		for(int i=0;i< GetCount();i++)
		{
			auto pObject = GetItem(i);
			if(strStyleNo==pObject->m_strStyleNo)
			{
				nSel = i;
				break;
			}
		}
	}

	return nSel;
}

void CDBStyleInfoList::GetListFromDB(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);
	ResetData();
	Empty();
	CString strSQL = _T("");
	strSQL.Format(_T("select * from %s order by %s desc"),DB_TABLE_STYLE,DBKuanShi_key_UpdateTime);
	pADOConn->GetRecordSet(strSQL);
	while (!pADOConn->adoEOF())
	{
		CDBStyleInfoData oData;
		oData.GetAllDBInfo(pADOConn);
		AddItem(&oData);
		pADOConn->MoveNext();
	}
}

int CDBStyleInfoList::GetStyleSaleCount()
{
	return m_nSaleCount;
}

CDBStyleInfoList * CDBStyleInfoList::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = shared_ptr<CDBStyleInfoList>(new CDBStyleInfoList);

	return sm_inst.get();
}

BOOL CDBStyleInfoList::GetBaseSizeAndWeightPercent(CADOConn* pADOConn,CString strKsCode,CString& strBaseSize,CString& strWeightPercent)
{
   ASSERT(pADOConn != NULL);
   strBaseSize = strWeightPercent = _T("");
   CString strSql;
   strSql.Format(_T("select cBasicSize,nIncreaseNum from Kuanshi where cKuanhao = '%s';"),strKsCode);
   pADOConn->GetRecordSet(strSql);
   if (!pADOConn->adoEOF())
   {
      strBaseSize = pADOConn->GetValueString(_T("cBasicSize"));
      strWeightPercent = pADOConn->GetValueString(_T("nIncreaseNum"));
   }
   return TRUE;
}

BOOL CDBStyleInfoList::UpdateWeightPercent(CADOConn* pADOConn,CString strKsCode,CString& strWeightPercent)
{
   ASSERT(pADOConn != NULL);
   CString strSql;
   if (strWeightPercent.IsEmpty())
   {
      strWeightPercent = _T("0");
   }
   strSql.Format(_T("update Kuanshi set nIncreaseNum = '%s' where cKuanhao = '%s';"),strWeightPercent,strKsCode);
   return pADOConn->ExecuteSQL(strSql);
}

BOOL CDBStyleInfoList::GetStyleInfoByStyleNo(CADOConn *pADOConn,CString strStyleNo,__out CDBStyleInfoData& pData)
{
	ASSERT(pADOConn != NULL); 
	BOOL bRet = FALSE;

	CString strSQL = _T("");
	strSQL.Format(_T("select * from Kuanshi where cKuanhao = '%s'"),strStyleNo);
	bRet = pADOConn->GetRecordSet(strSQL);
	if (!pADOConn->adoEOF())
	{
		pData.GetAllDBInfo(pADOConn);
	}
	return bRet;
}

BOOL CDBStyleInfoList::CheckKsIsExists(CADOConn* pADOConn,CString strKsCode)
{
   ASSERT(pADOConn != NULL); 
   CString strSql = _T("");
   strSql.Format(_T("select ID from %s where %s = '%s';"),DB_TABLE_STYLE,DBKuanShi_key_StyleNo,strKsCode);
   pADOConn->GetRecordSet(strSql);
   if (!pADOConn->adoEOF())
   {
      return TRUE;
   }
   return FALSE;
}


CString my_ks_info::GetInsertSql()
{
   CString strFormat = _T("");
                       //1  2  3  4  5  6  7  8  9  10
   strFormat.Format(_T(" %s,%s,%s,%s,%s,%s,%s,%s,%s,%s\
                        ,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s"),
                       DBKuanShi_key_UpdateTime       ,//1
                       DBKuanShi_key_KindName         ,//2
                       DBKuanShi_key_StyleNo          ,//3
                       DBKuanShi_key_StyleName        ,//4
                       DBKuanShi_key_StyleIntro       ,//5
                       DBKuanShi_key_CreateTime       ,//6
                       DBKuanShi_key_YarnCate         ,//7
                       DBKuanShi_key_KsYears          ,//8
                       DBKuanShi_key_dtExpireTime     ,//9
                       DBKuanShi_key_cCreator         ,//10
                       DBKuanShi_key_cCreateType      ,//11
                       DBKuanShi_key_cTheme           ,//12
                       DBKuanShi_key_cCusCode         ,//13
                       DBKuanShi_key_cCusKuanHao      ,//14
                       DBKuanShi_key_cProcessStatus   ,//15
                       DBKuanShi_key_cEdition         ,//16
                       DBKuanShi_key_dtMakingOrdTime  ,//17
                       DBKuanShi_key_cMainMaterial    ,//18
                       DBKuanShi_key_cVersionNum      ,//19
                       DBKuanShi_key_cSinglePerson    ,//20
                       DBKuanShi_key_cPinMing
                       );  

   CString strGetDateStr = DBS_GETDATESTR;
   CString strValues = _T("");
   strValues.Format(_T("%s,'%s','%s','%s','%s',%s,'%s','%s','%s','%s',\
                       '%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s'"),
                       strGetDateStr      ,//1
                       m_strTypeName      ,//2
                       m_strStyleNo       ,//3
                       m_strStyleName     ,//4
                       m_strStyleIntro    ,//5
                       strGetDateStr      ,//6
                       m_strYarnCate      ,//7
                       m_strKsYears       ,//8
                       m_dtExpireTime     ,//9
                       m_cCreator         ,//10
                       m_cCreateType      ,//11
                       m_cTheme           ,//12
                       m_cCusCode         ,//13
                       m_cCusKuanhao      ,//14
                       m_cProcessStatus   ,//15
                       m_cEdition         ,//16
                       m_dtMakingOrdTime  ,//17
                       m_cMainMaterial    ,//18
                       m_cVersionNum      ,//19
                       m_cSinglePerson    ,//20
                       m_strPinMing       
                       );

   CString strSQL = _T("");
   strSQL.Format(_T("insert into %s(%s) values(%s)"),DB_TABLE_STYLE,strFormat,strValues);
   return strSQL;
};

CString my_ks_info::GetUpdateSql(BOOL bIgnoreNull/* = TRUE*/)
{
   if (m_strStyleNo.IsEmpty())
   {
      return _T("");
   }
   CString strSql = _T("");
   CString strText;
   
   if (!m_strTypeName.IsEmpty() || !bIgnoreNull)
   {
      strText.Format(_T("%s = '%s',"),DBKuanShi_key_KindName,m_strTypeName);
      strSql += strText;
   }
   if (!m_strStyleName.IsEmpty() || !bIgnoreNull)
   {
      strText.Format(_T("%s = '%s',"),DBKuanShi_key_StyleName,m_strStyleName);
      strSql += strText;
   }
   if (!m_strYarnCate.IsEmpty() || !bIgnoreNull)
   {
      strText.Format(_T("%s = '%s',"),DBKuanShi_key_YarnCate,m_strYarnCate);
      strSql += strText;
   }
   if (!m_strKsYears.IsEmpty() || !bIgnoreNull)
   {
      strText.Format(_T("%s = '%s',"),DBKuanShi_key_KsYears,m_strKsYears);
      strSql += strText;
   }
   if(!m_dtExpireTime.IsEmpty() || !bIgnoreNull)
   {
      strText.Format(_T("%s = '%s',"),DBKuanShi_key_dtExpireTime,m_dtExpireTime);
      strSql += strText;
   }
   if(!m_cCreator.IsEmpty() || !bIgnoreNull)
   {
      strText.Format(_T("%s = '%s',"),DBKuanShi_key_cCreator,m_cCreator);
      strSql += strText;
   }
   if(!m_cCreateType.IsEmpty() || !bIgnoreNull)
   {
      strText.Format(_T("%s = '%s',"),DBKuanShi_key_cCreateType,m_cCreateType);
      strSql += strText;
   }
   if(!m_cTheme.IsEmpty() || !bIgnoreNull)
   {
      strText.Format(_T("%s = '%s',"),DBKuanShi_key_cTheme,m_cTheme);
      strSql += strText;
   }
   if(!m_cCusCode.IsEmpty() || !bIgnoreNull)
   {
      strText.Format(_T("%s = '%s',"),DBKuanShi_key_cCusCode,m_cCusCode);
      strSql += strText;
   }
   if(!m_cCusKuanhao.IsEmpty() || !bIgnoreNull)
   {
      strText.Format(_T("%s = '%s',"),DBKuanShi_key_cCusKuanHao,m_cCusKuanhao);
      strSql += strText;
   }
   if(!m_cProcessStatus.IsEmpty() || !bIgnoreNull)
   {
      strText.Format(_T("%s = '%s',"),DBKuanShi_key_cProcessStatus,m_cProcessStatus);
      strSql += strText;
   }
   if(!m_cEdition.IsEmpty() || !bIgnoreNull)
   {
      strText.Format(_T("%s = '%s',"),DBKuanShi_key_cEdition,m_cEdition);
      strSql += strText;
   }
   if(!m_dtMakingOrdTime.IsEmpty() || !bIgnoreNull)
   {
      strText.Format(_T("%s = '%s',"),DBKuanShi_key_dtMakingOrdTime         ,m_dtMakingOrdTime);
      strSql += strText;
   }
   if(!m_cMainMaterial.IsEmpty() || !bIgnoreNull)
   {
      strText.Format(_T("%s = '%s',"),DBKuanShi_key_cMainMaterial        ,m_cMainMaterial);
      strSql += strText;
   }
   if(!m_cVersionNum.IsEmpty() || !bIgnoreNull)
   {
      strText.Format(_T("%s = '%s',"),DBKuanShi_key_cVersionNum        ,m_cVersionNum);
      strSql += strText;
   }
   if(!m_cSinglePerson.IsEmpty() || !bIgnoreNull)
   {
      strText.Format(_T("%s = '%s',"),DBKuanShi_key_cSinglePerson       ,m_cSinglePerson);
      strSql += strText;
   }
   if (!m_strPinMing.IsEmpty() || !bIgnoreNull)
   {
      strText.Format(_T("%s = '%s',"),DBKuanShi_key_cPinMing,m_strPinMing);
      strSql += strText;
   }
   //更新时间
   CString strGetDateStr = DBS_GETDATESTR;
   strText.Format(_T("%s = %s,"),DBKuanShi_key_UpdateTime,strGetDateStr);
   strSql += strText;

   if (!strSql.IsEmpty())
   {
      strSql = strSql.Left(strSql.GetLength() - 1);// 取掉最后一个,
      CString strRetSql;  
      strRetSql.Format(_T("update %s set %s where %s = '%s'"),DB_TABLE_STYLE,strSql,DBKuanShi_key_StyleNo,m_strStyleNo);
      return strRetSql;
   }
   return _T("");
};
