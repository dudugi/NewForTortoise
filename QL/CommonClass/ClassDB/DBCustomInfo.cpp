#include "StdAfx.h"
#include "DBCustomInfo.h"
#include <algorithm>

IMPLEMENT_SERIAL(CDBCustomInfoData,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBCustomInfoList,  CDataListMid, 1)

std::shared_ptr<CDBCustomInfoData> CDBCustomInfoData::sm_inst;
std::shared_ptr<CDBCustomInfoList> CDBCustomInfoList::sm_inst;

CDBCustomInfoData::CDBCustomInfoData()
{
	ResetData();
} 

CDBCustomInfoData::~CDBCustomInfoData()
{
}

void CDBCustomInfoData::ResetData()
{
	m_nID = 0;
	m_oleUpdateTime = COleDateTime::GetCurrentTime();
	m_strCate = _T("");
	m_strCusCate = _T("");
	m_strCusCode = _T("");
	m_strCusName = _T("");
	m_strCusAbbrevName = _T("");
	m_strCusAddr = _T("");
	m_strCusPerson = _T("");
	m_strCusPhone = _T("");
	m_strCusFax = _T("");
	m_strMobile = _T("");
	m_strWeChat = _T("");
	m_strRemark = _T("");
	m_strVenWeb = _T("");
	m_strVenCode = _T("");
	m_strVenPwd = _T("");
	m_strCusPwd = _T("");
	m_fArrears = 0.0;
	m_fDeposit = 0.0;
	m_fLimit = 0.0;
	m_strProvince = _T("");
	m_strCity = _T("");
	m_strArea = _T("");
	m_strState = _T("");
	m_nDeliveryDays = 0;
	m_nNum = 0;
	m_nLoss = 0;
	m_strEMS = _T("");
	m_strParrentCode = _T("");
	m_strClerkCode = _T("");
	m_strRebate = _T("");
	m_strWorkDoc = _T("");
	m_strTag = _T("");
	m_strDeliveryDoc = _T("");
	m_strDepotPos = _T("");
	m_strSign = _T("");
	m_nCusLv = 0;
   m_strNewCusName = _T("");
   m_iTreeGroupID = -1;
   m_iJijiaType = 0;
   m_fAddinPrice  = 0.00;       //���ۼۼӼ�        add by lida 2018/05/24
   m_bPrintDiaoPai = 0;     //�Ƿ��ӡ����    add by lida 2018/05/24
   m_bPrintYuE = 0;         //�Ƿ��ӡ���    add by lida 2018/05/24
	SetDataType(DAT_CUSTOM);
   m_fZMZheKou = 0;
   m_strSalesID = _T("");
}

void CDBCustomInfoData::Trim()
{
	m_strCate.Trim();
	m_strCusCate.Trim();
	m_strCusCode.Trim();
	m_strCusName.Trim();
	m_strCusAbbrevName.Trim();
	m_strCusAddr.Trim();
	m_strCusPerson.Trim();
	m_strCusPhone.Trim();
	m_strCusFax.Trim();
	m_strMobile.Trim();
	m_strWeChat.Trim();
	m_strRemark.Trim();
	m_strVenWeb.Trim();
	m_strVenCode.Trim();
	m_strVenPwd.Trim();
	m_strCusPwd.Trim();
	m_strProvince.Trim();
	m_strCity.Trim();
	m_strArea.Trim();
	m_strState.Trim();
	m_strEMS.Trim();
	m_strParrentCode.Trim();
	m_strClerkCode.Trim();
	m_strRebate.Trim();
	m_strWorkDoc.Trim();
	m_strTag.Trim();
	m_strDeliveryDoc.Trim();
	m_strDepotPos.Trim();
	m_strSign.Trim();
   m_strNewCusName.Trim();
   m_strSalesID.Trim();
}

void CDBCustomInfoData:: Copy(CDBCustomInfoData *pData)
{
	ASSERT(pData != NULL);
	CDataMid::Copy(pData);

	m_nID = pData->m_nID;
	m_oleUpdateTime = pData->m_oleUpdateTime;
	m_strCate = pData->m_strCate;
	m_strCusCate = pData->m_strCusCate;
	m_strCusCode = pData->m_strCusCode;
	m_strCusName = pData->m_strCusName;
	m_strCusAbbrevName = pData->m_strCusAbbrevName;
	m_strCusAddr = pData->m_strCusAddr;
	m_strCusPerson = pData->m_strCusPerson;
	m_strCusPhone = pData->m_strCusPhone;
	m_strCusFax = pData->m_strCusFax;
	m_strMobile = pData->m_strMobile;
	m_strWeChat = pData->m_strWeChat;
	m_strRemark = pData->m_strRemark;
	m_strVenWeb = pData->m_strVenWeb;
	m_strVenCode = pData->m_strVenCode;
	m_strVenPwd = pData->m_strVenPwd;
	m_strCusPwd = pData->m_strCusPwd;
	m_fArrears = pData->m_fArrears;
	m_fDeposit = pData->m_fDeposit;
	m_fLimit = pData->m_fLimit;
	m_strProvince = pData->m_strProvince;
	m_strCity = pData->m_strCity;
	m_strArea = pData->m_strArea;
	m_strState = pData->m_strState;
	m_nDeliveryDays = pData->m_nDeliveryDays;
	m_nNum = pData->m_nNum;
	m_nLoss = pData->m_nLoss;
	m_strEMS = pData->m_strEMS;
	m_strParrentCode = pData->m_strParrentCode;
	m_strClerkCode = pData->m_strClerkCode;
	m_strRebate = pData->m_strRebate;
	m_strWorkDoc = pData->m_strWorkDoc;
	m_strTag = pData->m_strTag;
	m_strDeliveryDoc = pData->m_strDeliveryDoc;
	m_strDepotPos = pData->m_strDepotPos;
	m_strSign = pData->m_strSign;
	m_strCusUnit = pData->m_strCusUnit;
	m_nCusLv = pData->m_nCusLv;
   m_strNewCusName = pData->m_strNewCusName;
   m_iTreeGroupID = pData->m_iTreeGroupID;
   m_iJijiaType = pData->m_iJijiaType;
   m_fAddinPrice = pData->m_fAddinPrice;       //���ۼۼӼ�        add by lida 2018/05/24
   m_bPrintDiaoPai = pData->m_bPrintDiaoPai;     //�Ƿ��ӡ����    add by lida 2018/05/24
   m_bPrintYuE = pData->m_bPrintYuE;         //�Ƿ��ӡ���    add by lida 2018/05/24
   m_fZMZheKou = pData->m_fZMZheKou;
   m_strSalesID = pData->m_strSalesID;
}

void CDBCustomInfoData::Serialize(CArchive& ar)
{
	CDataMid::Serialize(ar);//���ຯ��

	int nTagSize = 0;
	CString strName;
	int nNameSize;

	ar.Flush();
	if (ar.IsStoring())
	{
		MySerial.SaveDataInt(ar,_T("CUSTOMID"),m_nID);
		MySerial.SaveColeDateTime(ar,_T("UPDATIME"),m_oleUpdateTime);
		MySerial.SaveDataStr(ar,_T("CUSTCATE"),m_strCate);
		MySerial.SaveDataStr(ar,_T("TCUSCATE"),m_strCusCate);
		MySerial.SaveDataStr(ar,_T("CUSTCODE"),m_strCusCode);
		MySerial.SaveDataStr(ar,_T("CUSTNAME"),m_strCusName);
		MySerial.SaveDataStr(ar,_T("CUABBREV"),m_strCusAbbrevName);
		MySerial.SaveDataStr(ar,_T("CUSTADDR"),m_strCusAddr);
		MySerial.SaveDataStr(ar,_T("CUPERSON"),m_strCusPerson);
		MySerial.SaveDataStr(ar,_T("CUSPHONE"),m_strCusPhone);
		MySerial.SaveDataStr(ar,_T("CUSTOFAX"),m_strCusFax);
		MySerial.SaveDataStr(ar,_T("TCUSTTEL"),m_strMobile);
		MySerial.SaveDataStr(ar,_T("CSWECHAT"),m_strWeChat);
		MySerial.SaveDataStr(ar,_T("CUREMARK"),m_strRemark);
		MySerial.SaveDataStr(ar,_T("CUVENWEB"),m_strVenWeb);
		MySerial.SaveDataStr(ar,_T("CVENCODE"),m_strCusCode);
		MySerial.SaveDataStr(ar,_T("CUVENPWD"),m_strVenPwd);
		MySerial.SaveDataStr(ar,_T("THPASSWD"),m_strCusPwd);
		MySerial.SaveDataFloat(ar,_T("CARREARS"),m_fArrears);
		MySerial.SaveDataFloat(ar,_T("CDEPOSIT"),m_fDeposit);
		MySerial.SaveDataFloat(ar,_T("CUSLIMIT"),m_fLimit);
		MySerial.SaveDataStr(ar,_T("PROVINCE"),m_strProvince);
		MySerial.SaveDataStr(ar,_T("CUSTCITY"),m_strCity);
		MySerial.SaveDataStr(ar,_T("CUSTAREA"),m_strArea);
		MySerial.SaveDataStr(ar,_T("CUSSTATE"),m_strState);
		MySerial.SaveDataInt(ar,_T("CUSDDAYS"),m_nDeliveryDays);
		MySerial.SaveDataInt(ar,_T("CUSTONUM"),m_nNum);
		MySerial.SaveDataInt(ar,_T("CUSTLOSS"),m_nLoss);
		MySerial.SaveDataStr(ar,_T("CUSTOEMS"),m_strEMS);
		MySerial.SaveDataStr(ar,_T("PARRCODE"),m_strParrentCode);
		MySerial.SaveDataStr(ar,_T("CLERKCOD"),m_strClerkCode);
		MySerial.SaveDataStr(ar,_T("CUREBATE"),m_strRebate);
		MySerial.SaveDataStr(ar,_T("CWORKDOC"),m_strWorkDoc);
		MySerial.SaveDataStr(ar,_T("CUSTOTAG"),m_strTag);
		MySerial.SaveDataStr(ar,_T("DELIVDOC"),m_strDeliveryDoc);
		MySerial.SaveDataStr(ar,_T("DEPOTPOS"),m_strDepotPos);
		MySerial.SaveDataStr(ar,_T("CUSTSIGN"),m_strSign);
		MySerial.SaveDataStr(ar,_T("CUSTUNIT"),m_strCusUnit);
		MySerial.SaveDataInt(ar,_T("CUSLEVER"),m_nCusLv);
      MySerial.SaveDataStr(ar,_T("CUSNEWNAME"),m_strNewCusName);
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

			else if (strName == _T("CUSTOMID"))
			{
				ar >>nTagSize >> m_nID;
			}
			else if (strName == _T("UPDATIME"))
			{
				ar >>nTagSize >> m_oleUpdateTime;
			}
			else if (strName == _T("CUSTCATE"))
			{
				ar >> nTagSize >> m_strCate;
			}
			else if(strName == _T("TCUSCATE"))
			{
				ar >>nTagSize >> m_strCusCate;
			}
			else if(strName == _T("CUSTCODE"))
			{
				ar >>nTagSize >> m_strCusCode;
			}
			else if(strName == _T("CUSTNAME"))
			{
				ar >>nTagSize >> m_strCusName;
			}
			else if(strName == _T("CUABBREV"))
			{
				ar >>nTagSize >> m_strCusAbbrevName;
			}
			else if(strName == _T("CUSTADDR"))
			{
				ar >>nTagSize >> m_strCusAddr;
			}
			else if(strName == _T("CUPERSON"))
			{
				ar >>nTagSize >> m_strCusPerson;
			}
			else if(strName == _T("CUSPHONE"))
			{
				ar >>nTagSize >> m_strCusPhone;
			}
			else if(strName == _T("CUSTOFAX"))
			{
				ar >>nTagSize >> m_strCusFax;
			}
			else if(strName == _T("TCUSTTEL"))
			{
				ar >>nTagSize >> m_strMobile;
			}
			else if(strName == _T("CSWECHAT"))
			{
				ar >>nTagSize >> m_strWeChat;
			}
			else if(strName == _T("CUREMARK"))
			{
				ar >>nTagSize >> m_strRemark;
			}
			else if(strName == _T("CUVENWEB"))
			{
				ar >>nTagSize >> m_strVenWeb;
			}
			else if(strName == _T("CVENCODE"))
			{
				ar >>nTagSize >> m_strVenCode;
			}
			else if(strName == _T("CUVENPWD"))
			{
				ar >>nTagSize >> m_strVenPwd;
			}
			else if(strName == _T("THPASSWD"))
			{
				ar >>nTagSize >> m_strCusPwd;
			}
			else if(strName == _T("CARREARS"))
			{
				ar >>nTagSize >> m_fArrears;
			}
			else if(strName == _T("CDEPOSIT"))
			{
				ar >>nTagSize >> m_fDeposit;
			}
			else if(strName == _T("CUSLIMIT"))
			{
				ar >>nTagSize >> m_fLimit;
			}
			else if(strName == _T("PROVINCE"))
			{
				ar >>nTagSize >> m_strProvince;
			}
			else if(strName == _T("CUSTCITY"))
			{
				ar >>nTagSize >> m_strCity;
			}
			else if(strName == _T("CUSTAREA"))
			{
				ar >>nTagSize >> m_strArea;
			}
			else if(strName == _T("CUSSTATE"))
			{
				ar >>nTagSize >> m_strState;
			}
			else if(strName == _T("CUSDDAYS"))
			{
				ar >>nTagSize >> m_nDeliveryDays;
			}
			else if(strName == _T("CUSTONUM"))
			{
				ar >>nTagSize >> m_nNum;
			}
			else if(strName == _T("CUSTLOSS"))
			{
				ar >>nTagSize >> m_nLoss;
			}
			else if(strName == _T("CUSTOEMS"))
			{
				ar >>nTagSize >> m_strEMS;
			}
			else if(strName == _T("PARRCODE"))
			{
				ar >>nTagSize >> m_strParrentCode;
			}
			else if(strName == _T("CLERKCOD"))
			{
				ar >>nTagSize >> m_strClerkCode;
			}
			else if(strName == _T("CUREBATE"))
			{
				ar >>nTagSize >> m_strRebate;
			}
			else if(strName == _T("CWORKDOC"))
			{
				ar >>nTagSize >> m_strWorkDoc;
			}
			else if(strName == _T("CUSTOTAG"))
			{
				ar >>nTagSize >> m_strTag;
			}
			else if(strName == _T("DELIVDOC"))
			{
				ar >>nTagSize >> m_strDeliveryDoc;
			}
			else if(strName == _T("DEPOTPOS"))
			{
				ar >>nTagSize >> m_strDepotPos;
			}
			else if(strName == _T("CUSTSIGN"))
			{
				ar >>nTagSize >> m_strSign;
			}
			else if(strName == _T("CUSTUNIT"))
			{
				ar >>nTagSize >> m_strCusUnit;
			}
			else if(strName == _T("CUSLEVER"))
			{
				ar >>nTagSize >> m_nCusLv;
         }else if(strName == _T("CUSNEWNAME"))
         {
            ar >>nTagSize >> m_strNewCusName;
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

CDBCustomInfoData * CDBCustomInfoData::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = shared_ptr<CDBCustomInfoData>(new CDBCustomInfoData);

	return sm_inst.get();
}

//���ݿͻ���Ż�ȡ����������Ϣ yangjr 2018-3-27
BOOL CDBCustomInfoData::GetAllDBInfoByCusCode(CADOConn *pADOConn,CString strCusCode)
{
   ASSERT(pADOConn != NULL);
   CString strSQL = _T("");
   strSQL.Format(_T("select * ,(dbo.getPY(cCusName)+'-'+cCusName) as %s from %s where %s='%s'")
      ,CustomerTable_newCusName,DB_TABLE_CUSTOM,DBCustomer_key_Code,strCusCode);

   pADOConn->GetRecordSet(strSQL);
   if (!pADOConn->adoEOF())
   {  
      GetAllDBInfo(pADOConn);
      m_strNewCusName = pADOConn->GetValueString(CustomerTable_newCusName);      
      return TRUE;
   }
   return FALSE;
}

BOOL CDBCustomInfoData::GetAllDBInfo(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);

	BOOL bRet = TRUE;

	if (NULL == pADOConn)
	{
		bRet = FALSE;
	}
	else
	{
		m_strCusCode = pADOConn->GetValueString(DBCustomer_key_Code);
  /*    if (m_strCusCode == _T("255"))
      {
         ASSERT(0);
      }*/
		m_strCusPwd = pADOConn->GetValueString(DBCustomer_key_Pwd);
		m_strCusName = pADOConn->GetValueString(DBCustomer_key_Name);
		m_strCusUnit = pADOConn->GetValueString(DBCustomer_key_Unit);
		m_strCusAddr = pADOConn->GetValueString(DBCustomer_key_Addr);
		m_strMobile = pADOConn->GetValueString(DBCustomer_key_Mobile);
		m_nCusLv = _ttoi(pADOConn->GetValueString(DBCustomer_key_LV));
		m_strCusCate = pADOConn->GetValueString(DBCustomer_key_CusCate);


		m_nID = pADOConn->GetValueInt(DBCustomer_key_ID);
		
		m_oleUpdateTime = pADOConn->GetValueDate(DBCustomer_key_UpdateTime);
		m_strCate = pADOConn->GetValueString(DBCustomer_key_Cate);
		m_strCusCate = pADOConn->GetValueString(DBCustomer_key_CusCate);
		m_strCusCode = pADOConn->GetValueString(DBCustomer_key_Code);
		m_strCusName = pADOConn->GetValueString(DBCustomer_key_Name);
		m_strCusAbbrevName = pADOConn->GetValueString(DBCustomer_key_Abbrev);
		m_strCusAddr = pADOConn->GetValueString(DBCustomer_key_Addr);
		m_strCusPerson = pADOConn->GetValueString(DBCustomer_key_Person);
		m_strCusPhone = pADOConn->GetValueString(DBCustomer_key_Phone);
		m_strCusFax = pADOConn->GetValueString(DBCustomer_key_Fax);
		m_strMobile = pADOConn->GetValueString(DBCustomer_key_Mobile);
		//m_strWeChat = pADOConn->GetValueString(DBCustomer_key_WeChat );
		m_strRemark = pADOConn->GetValueString(DBCustomer_key_Remark);
		m_strVenWeb = pADOConn->GetValueString(DBCustomer_key_VenWeb);
		m_strVenCode = pADOConn->GetValueString(DBCustomer_key_VenCode);
		m_strVenPwd = pADOConn->GetValueString(DBCustomer_key_VenPwd);
		m_strCusPwd = pADOConn->GetValueString(DBCustomer_key_Pwd);
		m_fArrears = _ttof(pADOConn->GetValueDoubleStr(DBCustomer_key_Arrears,2));
		m_fDeposit = _ttof(pADOConn->GetValueDoubleStr(DBCustomer_key_Deposit,2));
		m_fLimit = _ttof(pADOConn->GetValueDoubleStr(DBCustomer_key_Limit,2));
		m_strProvince = pADOConn->GetValueString(DBCustomer_key_Province);
		m_strCity = pADOConn->GetValueString(DBCustomer_key_City);
		m_strArea = pADOConn->GetValueString(DBCustomer_key_Area);
		m_strState = pADOConn->GetValueString(DBCustomer_key_State);
		m_nDeliveryDays = pADOConn->GetValueInt(DBCustomer_key_DeliveDays);
		m_nNum = pADOConn->GetValueInt(DBCustomer_key_Num);
		m_nLoss = pADOConn->GetValueInt(DBCustomer_key_Loss);
		m_strEMS = pADOConn->GetValueString(DBCustomer_key_EMS);
		m_strParrentCode = pADOConn->GetValueString(DBCustomer_key_ParrentCode);
		m_strClerkCode = pADOConn->GetValueString(DBCustomer_key_ClerkCode);
		m_strRebate = pADOConn->GetValueString(DBCustomer_key_Rebate);
		m_strWorkDoc = pADOConn->GetValueString(DBCustomer_key_WorkDoc);
		m_strTag = pADOConn->GetValueString(DBCustomer_key_Tag);
		m_strDeliveryDoc = pADOConn->GetValueString(DBCustomer_key_DeliveDoc);
		m_strDepotPos = pADOConn->GetValueString(DBCustomer_key_DepotPos);
		m_strSign = pADOConn->GetValueString(DBCustomer_key_Sign);
		m_strCusUnit = pADOConn->GetValueString(DBCustomer_key_Unit);
		m_nCusLv = pADOConn->GetValueInt(DBCustomer_key_LV);
      m_iTreeGroupID = pADOConn->GetValueInt(DBCustomer_key_iTreeGroupID);
      m_iJijiaType = pADOConn->GetValueInt(DBCustomer_key_iJijiaType);
      m_fAddinPrice = pADOConn->GetValueDouble(DBCustomer_key_fAddinPrice);       //���ۼۼӼ�        add by lida 2018/05/24
      m_bPrintDiaoPai = pADOConn->GetValueInt(DBCustomer_key_bPrintDiaoPai);     //�Ƿ��ӡ����    add by lida 2018/05/24
      m_bPrintYuE = pADOConn->GetValueInt(DBCustomer_key_bPrintYuE);         //�Ƿ��ӡ���    add by lida 2018/05/24
      m_fZMZheKou = pADOConn->GetValueDouble(DBCustomer_key_fZMZheKou); 
      m_strSalesID = pADOConn->GetValueString(DBCustomer_key_cSalesID);
		bRet = TRUE;
	}

	return bRet;
}

BOOL CDBCustomInfoData::InsertAllDBInfo( CADOConn *pADOConn )
{
	ASSERT(pADOConn != NULL);
	m_strCusCode.Trim();
	ASSERT(!m_strCusCode.IsEmpty());

   //δָ��������Ĭ��Ϊδ���� add by huangym 2019/1/23
   m_iTreeGroupID = -1 == m_iTreeGroupID ? 2 : m_iTreeGroupID;
	BOOL bRet = TRUE;

	CString strSQL = _T("");

	CString strFormat = _T(""),strValue = _T("");
	//					1 ,2 ,3 ,4 ,5 ,6 ,7 ,8 ,9 ,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39
	strFormat.Format(_T("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,\
                        %s,%s,%s,%s,%s,%s,%s,%s,%s,%s,\
                        %s,%s,%s,%s,%s,%s,%s,%s,%s,%s,\
                        %s,%s,%s,%s,%s,%s,%s,%s,%s,%s,\
                        %s,%s,%s,%s,%s"),
		DBCustomer_key_UpdateTime, //2
		DBCustomer_key_Cate,	   //3
		DBCustomer_key_CusCate,	   //4
		DBCustomer_key_Code,	   //5
		DBCustomer_key_Name,	   //6
		DBCustomer_key_Abbrev,	   //7
		DBCustomer_key_Addr,	   //8
		DBCustomer_key_Person,	   //9
		DBCustomer_key_Phone,	   //10
		DBCustomer_key_Fax,		   //11
		DBCustomer_key_Mobile,	   //12
		DBCustomer_key_WeChat,	   //13
		DBCustomer_key_Remark,	   //14
		DBCustomer_key_VenWeb,	   //15
		DBCustomer_key_VenCode,	   //16
		DBCustomer_key_VenPwd,	   //17
		DBCustomer_key_Pwd,		   //18
		DBCustomer_key_Arrears,	   //19
		DBCustomer_key_Deposit,	   //20
		DBCustomer_key_Limit,	   //21
		DBCustomer_key_Province,   //22
		DBCustomer_key_City,	   //23
		DBCustomer_key_Area,	   //24
		DBCustomer_key_State,	   //25
		DBCustomer_key_DeliveDays, //26
		DBCustomer_key_Num,		   //27
		DBCustomer_key_Loss,	   //28
		DBCustomer_key_EMS,		   //29
		DBCustomer_key_ParrentCode,//30
		DBCustomer_key_ClerkCode,  //31
		DBCustomer_key_Rebate,	   //32
		DBCustomer_key_WorkDoc,	   //33
		DBCustomer_key_Tag,		   //34
		DBCustomer_key_DeliveDoc,  //35
		DBCustomer_key_DepotPos,   //36
		DBCustomer_key_Sign,	   //37
		DBCustomer_key_Unit,	   //38
		DBCustomer_key_LV,		   //39
      DBCustomer_key_iTreeGroupID, //40
      DBCustomer_key_iJijiaType, //40
      DBCustomer_key_fAddinPrice,
      DBCustomer_key_bPrintDiaoPai,
      DBCustomer_key_bPrintYuE,
      DBCustomer_key_fZMZheKou,
      DBCustomer_key_cSalesID
		);

	strValue.Format(_T("%s,'%s','%s','%s','%s','%s','%s','%s','%s','%s',\
                      '%s','%s','%s','%s','%s','%s','%s','%f','%f','%f',\
                      '%s','%s','%s','%s','%d','%d','%d','%s','%s','%s',\
                      '%s','%s','%s','%s','%s','%s','%s','%d','%d','%d',\
                      '%f','%d','%d','%f','%s'"),
		DBS_GETDATESTR,			//1
		m_strCate,				//2
		m_strCusCate,			//3
		m_strCusCode,			//4
		m_strCusName,			//5
		m_strCusAbbrevName,		//6
		m_strCusAddr,			//7
		m_strCusPerson,			//8
		m_strCusPhone,			//9
		m_strCusFax,			//10
		m_strMobile,			//11
		m_strWeChat,			//12
		m_strRemark,			//13
		m_strVenWeb,			//14
		m_strVenCode,			//15
		m_strVenPwd,			//16
		m_strCusPwd,			//17
		m_fArrears,				//18  ----
		m_fDeposit,				//19  ----
		m_fLimit,				//20  ----
		m_strProvince,			//21
		m_strCity,				//22
		m_strArea,				//23
		m_strState,				//24
		m_nDeliveryDays,		//25  ----
		m_nNum,					//26  ----
		m_nLoss,				//27  ----
		m_strEMS,				//28
		m_strParrentCode,		//29
		m_strClerkCode,			//30
		m_strRebate,			//31
		m_strWorkDoc,			//32
		m_strTag,				//33
		m_strDeliveryDoc,		//34
		m_strDepotPos,			//35
		m_strSign,				//36
		m_strCusUnit,			//37
		m_nCusLv	,		   //38  ----
      m_iTreeGroupID,    //39
      m_iJijiaType,    //40
      m_fAddinPrice,
      m_bPrintDiaoPai,
      m_bPrintYuE,
      m_fZMZheKou,
      m_strSalesID
		);

	strSQL.Format(_T("insert into %s(%s) \
					 values(%s)"),DB_TABLE_CUSTOM,
					 strFormat,strValue);

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

BOOL CDBCustomInfoData::UpdateAllDBInfoByID( CADOConn *pADOConn )
{
	ASSERT(pADOConn != NULL);
	m_strCusCode.Trim();
	ASSERT(!m_strCusCode.IsEmpty());

   //δָ��������Ĭ��Ϊδ���� add by huangym 2019/1/23
   m_iTreeGroupID = -1 == m_iTreeGroupID ? 2 : m_iTreeGroupID;
	BOOL bRet = TRUE;

	CString strSQL = _T("");
   //						1       2       3       4       5       6       7       8       9       10
	strSQL.Format(_T("Update %s set %s= %s ,%s='%s',%s='%s',%s='%s',%s='%s',%s='%s',%s='%s',%s='%s',%s='%s',%s='%s',\
									%s='%s',%s='%s',%s='%s',%s='%s',%s='%s',%s='%s',%s='%f',%s='%f',%s='%f',%s='%s',\
									%s='%s',%s='%s',%s='%s',%s='%d',%s='%d',%s='%d',%s='%s',%s='%s',%s='%s',%s='%s',\
									%s='%s',%s='%s',%s='%s',%s='%s',%s='%s',%s='%s',%s='%d', %s='%d', %s='%d',%s='%f',\
                           %s='%d',%s='%d',%s='%f',%s='%s' where %s='%s'"),DB_TABLE_CUSTOM,
		DBCustomer_key_UpdateTime,DBS_GETDATESTR,	  //1
		DBCustomer_key_Cate,m_strCate,				  //2
		DBCustomer_key_CusCate,m_strCusCate,		  //3
		DBCustomer_key_Name,m_strCusName,			  //4
		DBCustomer_key_Abbrev,m_strCusAbbrevName,	  //5
		DBCustomer_key_Addr,m_strCusAddr,			  //6
		DBCustomer_key_Person,m_strCusPerson,		  //7
		DBCustomer_key_Phone,m_strCusPhone,			  //8
		DBCustomer_key_Fax,m_strCusFax,				  //9
		DBCustomer_key_Mobile,m_strMobile,			  //10
		DBCustomer_key_WeChat,m_strWeChat,			  //11
		DBCustomer_key_Remark,m_strRemark,			  //12
		DBCustomer_key_VenWeb,m_strVenWeb,			  //13
		DBCustomer_key_VenCode,m_strVenCode,		  //14
		DBCustomer_key_VenPwd,m_strVenPwd,			  //15
		DBCustomer_key_Pwd,m_strCusPwd,				  //16
		DBCustomer_key_Arrears,m_fArrears,			  //17  ----
		DBCustomer_key_Deposit,m_fDeposit,			  //18  ----
		DBCustomer_key_Limit,m_fLimit,				  //19  ----
		DBCustomer_key_Province,m_strProvince,		  //20
		DBCustomer_key_City,m_strCity,				  //21
		DBCustomer_key_Area,m_strArea,				  //22
		DBCustomer_key_State,m_strState,			  //23
		DBCustomer_key_DeliveDays,m_nDeliveryDays,	  //24  ----
		DBCustomer_key_Num,m_nNum,					  //25  ----
		DBCustomer_key_Loss,m_nLoss,				  //26  ----
		DBCustomer_key_EMS,m_strEMS,				  //27
		DBCustomer_key_ParrentCode,m_strParrentCode,  //28
		DBCustomer_key_ClerkCode,m_strClerkCode,	  //29
		DBCustomer_key_Rebate,m_strRebate,			  //30
		DBCustomer_key_WorkDoc,m_strWorkDoc,		  //31
		DBCustomer_key_Tag,m_strTag,				  //32
		DBCustomer_key_DeliveDoc,m_strDeliveryDoc,	  //33
		DBCustomer_key_DepotPos,m_strDepotPos,		  //34
		DBCustomer_key_Sign,m_strSign,				  //35
		DBCustomer_key_Unit,m_strCusUnit,			  //36
		DBCustomer_key_LV,m_nCusLv,					  //37  ----
      DBCustomer_key_iTreeGroupID,m_iTreeGroupID,//38
      DBCustomer_key_iJijiaType,m_iJijiaType, 	 //39
      DBCustomer_key_fAddinPrice,m_fAddinPrice,
      DBCustomer_key_bPrintDiaoPai,m_bPrintDiaoPai,
      DBCustomer_key_bPrintYuE,m_bPrintYuE,
      DBCustomer_key_fZMZheKou,m_fZMZheKou,
      DBCustomer_key_cSalesID,m_strSalesID,
      DBCustomer_key_Code,m_strCusCode		  //40
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

BOOL CDBCustomInfoData::DelAllDBInfoByID( CADOConn *pADOConn )
{
	ASSERT(pADOConn != NULL);
	m_strCusCode.Trim();
	ASSERT(!m_strCusCode.IsEmpty());

	BOOL bRet = TRUE;

	CString strSQL = _T("");
	strSQL.Format(_T("delete from %s where %s='%s'"),DB_TABLE_CUSTOM,DBCustomer_key_Code,m_strCusCode);

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

//���ݿͻ���Ÿ��¶�Ӧ�ͻ���ר���� yangjr 2018/8/22
BOOL CDBCustomInfoData::UpdateStorageZMJ(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);
   m_strCusCode.Trim();
   ASSERT(!m_strCusCode.IsEmpty());
   BOOL bRet = TRUE;
   CString strSQL = _T("");   
   strSQL.Format(_T("update OrderInStorage set fTuanGouJia = cast((fPiFaJia*(%.2f)+0.55) as int),cYouHuiJiaType='ר����' \
       from OrderInStorage as A,V_RdRecordsChild as B \
   where A.storageCate = '�������' and A.cCusCode='%s' and A.cCeLiang = '����' and A.shipDate = '' \
   and A.cCode=B.cCode and isnull(B.fTuanGouJia,0)<=0")
   ,m_fZMZheKou,m_strCusCode);

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

//CDBCustomInfoList
CDBCustomInfoList::CDBCustomInfoList()
{

}
CDBCustomInfoList::~CDBCustomInfoList()
{

}

CDBCustomInfoData*  CDBCustomInfoList::GetItem(int nIndex)
{
	if (nIndex<0||nIndex>=GetCount())
		return NULL;
	return (CDBCustomInfoData*)GetAt(FindIndex(nIndex));
}
void CDBCustomInfoList::AddItem(CDBCustomInfoData* pItem)
{
	CDBCustomInfoData*pData=new CDBCustomInfoData;
	pData->Copy(pItem);
	//AddTail(pData);
	AddHead(pData);
}
void CDBCustomInfoList::DeleteItem(int nIndex)
{
	if (nIndex<0||nIndex>GetCount())
		return;
	CDBCustomInfoData *pObject=(CDBCustomInfoData*)GetItem(nIndex);
	delete pObject;
	pObject=NULL;
	RemoveAt(FindIndex(nIndex));
}

CDBCustomInfoData* CDBCustomInfoList::GetItemByCustomID( CString strCustomID )
{
	CDBCustomInfoData * pItem = NULL;
	strCustomID.Trim();
	if (!strCustomID.IsEmpty())
	{
		for(int i=0;i< GetCount();i++)
		{
			CDBCustomInfoData * pObject = GetItem(i);
			if(strCustomID==pObject->m_strCusCode)
			{
				pItem = pObject;
				break;
			}
		}
	}

	return pItem;
}

CDBCustomInfoData* CDBCustomInfoList::GetItemByCustomName(CString strCustomName)
{
   CDBCustomInfoData * pItem = NULL;
   strCustomName.Trim();
   if (!strCustomName.IsEmpty())
   {
      for(int i=0;i< GetCount();i++)
      {
         CDBCustomInfoData * pObject = GetItem(i);
         if(strCustomName==pObject->m_strCusName)
         {
            pItem = pObject;
            break;
         }
      }
   }

   return pItem;
}

int CDBCustomInfoList::GetIndexByCustomID( CString strCustomID )
{
	int nSel = -1;
	strCustomID.Trim();
	if (!strCustomID.IsEmpty())
	{
		for(int i=0;i< GetCount();i++)
		{
			auto pObject = GetItem(i);
			if(strCustomID==pObject->m_strCusCode)
			{
				nSel = i;
				break;
			}
		}
	}

	return nSel;
}

void CDBCustomInfoList::GetListFromDB(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);
	
	Empty();
	CString strSQL = _T("");
	strSQL.Format(_T("select * ,(dbo.getPY(cCusName)+'-'+cCusName) as %s from %s")
      ,CustomerTable_newCusName,DB_TABLE_CUSTOM);

	pADOConn->GetRecordSet(strSQL);
	while (!pADOConn->adoEOF())
	{
		CDBCustomInfoData oData;
		oData.GetAllDBInfo(pADOConn);
		oData.m_strNewCusName = pADOConn->GetValueString(CustomerTable_newCusName);
		AddItem(&oData);
		pADOConn->MoveNext();
	}
}

CDBCustomInfoList * CDBCustomInfoList::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = shared_ptr<CDBCustomInfoList>(new CDBCustomInfoList);

	return sm_inst.get();
}

void CDBCustomInfoList::GetCustmerInfo(CADOConn *pADOConn,CDBCustomInfoData* pData)
{
	ASSERT(pADOConn != NULL);
	if (pData->m_strCusCode.IsEmpty())
		return;
	CString strSQL = _T("");
	strSQL.Format(_T("select * ,(dbo.getPY(cCusName)+'-'+cCusName) as %s from %s where %s = '%s';")
      ,CustomerTable_newCusName,DB_TABLE_CUSTOM,DBCustomer_key_Code,pData->m_strCusCode);
	pADOConn->GetRecordSet(strSQL);
	if (!pADOConn->adoEOF())
	{
		pData->GetAllDBInfo(pADOConn);
	}
	return;
}

#ifdef USING_GRIDCTRL_MARK
MAP_GridCtrl_AllData CDBCustomInfoList::CreateGridData(std::vector<int> treeGroupIDLst,CString strSaleID,BOOL bLimitSale/* = FALSE*/)
{
	MAP_GridCtrl_AllData  map_all_data;
   std::vector<CDBCustomInfoData *> dataLst;

   int nCount = GetCount();
   if (TRUE == bLimitSale)
   {
      for (int i = 0; i < nCount; i++)
      {
         CDBCustomInfoData * pData = GetItem(i);
         if (pData && pData->m_strSalesID.MakeUpper() == strSaleID.MakeUpper())
         {
            dataLst.push_back(pData);
         }
      }
   }else
   {
      for (int i = 0; i < nCount; i++)
      {
         CDBCustomInfoData * pData = GetItem(i);
         if (pData)
         {
            auto it = std::find(treeGroupIDLst.begin(), treeGroupIDLst.end(), pData->m_iTreeGroupID);

            dataLst.push_back(pData);
         }
      }
   }


	int nValidCount = 1;
	for (size_t i = 0; i < dataLst.size() ;i++)
	{
		CDBCustomInfoData * pData = dataLst[i];
		if (NULL != pData)
		{
			MAP_GridCtrl_RowData map_row_data;
			CreateGridData(pData,map_row_data);
         map_all_data.insert(make_pair(nValidCount,map_row_data));
			nValidCount++;
		}
	}
	return map_all_data;
}

MAP_GridCtrl_AllData CDBCustomInfoList::CreateGridData(CString strSaleID,BOOL bLimitSale/* = FALSE*/)
{
   MAP_GridCtrl_AllData  map_all_data;

   int nIndex = 0,nCount = GetCount();
   int nValidCount = 1;
   if (bLimitSale)
   {
      for (nIndex = 0;nIndex < nCount;nIndex++)
      {
         CDBCustomInfoData * pData = GetItem(nIndex);
         if (NULL != pData && pData->m_strSalesID.MakeUpper() == strSaleID.MakeUpper())
         {
            MAP_GridCtrl_RowData map_row_data;
            CreateGridData(pData,map_row_data);
            map_all_data.insert(make_pair(nValidCount,map_row_data));
            nValidCount++;
         }
      }
   }
   else
   {
      for (nIndex = 0;nIndex < nCount;nIndex++)
      {
         CDBCustomInfoData * pData = GetItem(nIndex);
         if (NULL != pData)
         {
            MAP_GridCtrl_RowData map_row_data;
            CreateGridData(pData,map_row_data);
            map_all_data.insert(make_pair(nValidCount,map_row_data));
            nValidCount++;
         }
      }
   }

   return map_all_data;
}

BOOL CDBCustomInfoList::CreateGridData(const CDBCustomInfoData* pData,MAP_GridCtrl_RowData& map_row_data)
{
   if (pData == NULL)
      return FALSE;

   pData->InsertRowData(DBCustomer_key_ID			,map_row_data,CB_enum_FieldData_Int,CB_enum_FieldCtrl_Text,FORMAT_INT,pData->m_nID					);
   pData->InsertRowData(DBCustomer_key_UpdateTime	,map_row_data,CB_enum_FieldData_Time,CB_enum_FieldCtrl_DateTime,FORMAT_STRING	,pData->m_oleUpdateTime.Format(_T("%Y-%m-%d %H:%M:%S"))		);
   pData->InsertRowData(DBCustomer_key_Cate		,map_row_data,FORMAT_STRING	,pData->m_strCate				);//����
   pData->InsertRowData(DBCustomer_key_CusCate	,map_row_data,FORMAT_STRING	,pData->m_strCusCate			);//����
   pData->InsertRowData(DBCustomer_key_Code		,map_row_data,FORMAT_STRING	,pData->m_strCusCode			);
   pData->InsertRowData(DBCustomer_key_Name		,map_row_data,FORMAT_STRING	,pData->m_strCusName			);
   pData->InsertRowData(DBCustomer_key_Abbrev		,map_row_data,FORMAT_STRING	,pData->m_strCusAbbrevName		);
   pData->InsertRowData(DBCustomer_key_Addr		,map_row_data,FORMAT_STRING	,pData->m_strCusAddr			);
   pData->InsertRowData(DBCustomer_key_Person		,map_row_data,FORMAT_STRING	,pData->m_strCusPerson			);
   pData->InsertRowData(DBCustomer_key_Phone		,map_row_data,FORMAT_STRING	,pData->m_strCusPhone			);
   pData->InsertRowData(DBCustomer_key_Fax		,map_row_data,FORMAT_STRING	,pData->m_strCusFax				);
   pData->InsertRowData(DBCustomer_key_Mobile		,map_row_data,FORMAT_STRING	,pData->m_strMobile				);
   pData->InsertRowData(DBCustomer_key_WeChat		,map_row_data,FORMAT_STRING	,pData->m_strWeChat				);
   pData->InsertRowData(DBCustomer_key_Remark		,map_row_data,FORMAT_STRING	,pData->m_strRemark				);
   pData->InsertRowData(DBCustomer_key_VenWeb		,map_row_data,FORMAT_STRING	,pData->m_strVenWeb				);
   pData->InsertRowData(DBCustomer_key_VenCode	,map_row_data,FORMAT_STRING	,pData->m_strVenCode			);
   pData->InsertRowData(DBCustomer_key_VenPwd		,map_row_data,FORMAT_STRING	,pData->m_strVenPwd				);
   pData->InsertRowData(DBCustomer_key_Pwd		,map_row_data,FORMAT_STRING	,pData->m_strCusPwd				);
   pData->InsertRowData(DBCustomer_key_Arrears	,map_row_data,CB_enum_FieldData_Double2Point,CB_enum_FieldCtrl_Text,FORMAT_PRICE,pData->m_fArrears				);
   pData->InsertRowData(DBCustomer_key_Deposit	,map_row_data,CB_enum_FieldData_Double2Point,CB_enum_FieldCtrl_Text,FORMAT_PRICE,pData->m_fDeposit				);
   pData->InsertRowData(DBCustomer_key_Limit		,map_row_data,CB_enum_FieldData_Double2Point,CB_enum_FieldCtrl_Text,FORMAT_PRICE,pData->m_fLimit				);
   pData->InsertRowData(DBCustomer_key_Province	,map_row_data,FORMAT_STRING	,pData->m_strProvince			);
   pData->InsertRowData(DBCustomer_key_City		,map_row_data,FORMAT_STRING	,pData->m_strCity				);
   pData->InsertRowData(DBCustomer_key_Area		,map_row_data,FORMAT_STRING	,pData->m_strArea				);
   pData->InsertRowData(DBCustomer_key_State		,map_row_data,FORMAT_STRING	,pData->m_strState				);
   pData->InsertRowData(DBCustomer_key_DeliveDays	,map_row_data,CB_enum_FieldData_Int,CB_enum_FieldCtrl_Text,FORMAT_INT,pData->m_nDeliveryDays			);
   pData->InsertRowData(DBCustomer_key_Num		,map_row_data,CB_enum_FieldData_Int,CB_enum_FieldCtrl_Text,FORMAT_INT,pData->m_nNum					);
   pData->InsertRowData(DBCustomer_key_Loss		,map_row_data,CB_enum_FieldData_Int,CB_enum_FieldCtrl_Text,FORMAT_INT,pData->m_nLoss					);
   pData->InsertRowData(DBCustomer_key_EMS		,map_row_data,FORMAT_STRING	,pData->m_strEMS				);
   pData->InsertRowData(DBCustomer_key_ParrentCode,map_row_data,FORMAT_STRING	,pData->m_strParrentCode		);
   pData->InsertRowData(DBCustomer_key_ClerkCode	,map_row_data,FORMAT_STRING	,pData->m_strClerkCode			);
   pData->InsertRowData(DBCustomer_key_Rebate		,map_row_data,FORMAT_STRING	,pData->m_strRebate				);
   pData->InsertRowData(DBCustomer_key_WorkDoc	,map_row_data,FORMAT_STRING	,pData->m_strWorkDoc			);
   pData->InsertRowData(DBCustomer_key_Tag		,map_row_data,FORMAT_STRING	,pData->m_strTag				);
   pData->InsertRowData(DBCustomer_key_DeliveDoc	,map_row_data,FORMAT_STRING	,pData->m_strDeliveryDoc		);
   pData->InsertRowData(DBCustomer_key_DepotPos	,map_row_data,FORMAT_STRING	,pData->m_strDepotPos			);
   pData->InsertRowData(DBCustomer_key_Sign		,map_row_data,FORMAT_STRING	,pData->m_strSign				);
   pData->InsertRowData(DBCustomer_key_Unit		,map_row_data,FORMAT_STRING	,pData->m_strCusUnit			);
   pData->InsertRowData(DBCustomer_key_LV			,map_row_data,CB_enum_FieldData_Int,CB_enum_FieldCtrl_Text,FORMAT_INT,pData->m_nCusLv				);
   //�ͻ����� �������ݿ���� yangjr 2017-8-16
   pData->InsertRowData(CustomerTable_newCusName		,map_row_data,FORMAT_STRING	,pData->m_strNewCusName				);
   pData->InsertRowData(DBCustomer_key_iTreeGroupID	,map_row_data, CB_enum_FieldData_Int, CB_enum_FieldCtrl_Text,FORMAT_INT	,pData->m_iTreeGroupID			);
   //���ۼۼƼ۷�ʽ anjie 2018/11/19
   CString strJiJiaType = _T("���ۿۻ���");
   if (0 <pData->m_iJijiaType)
   {
      strJiJiaType = _T("������");
   }
   else if (0>pData->m_iJijiaType)
   {
      strJiJiaType = _T("Ĭ�ϼƼ�");
   }
   pData->InsertRowData(DBCustomer_key_iJijiaType		,map_row_data,FORMAT_STRING	,strJiJiaType			);
   pData->InsertRowData(DBCustomer_key_fAddinPrice		,map_row_data,CB_enum_FieldData_Double2Point,CB_enum_FieldCtrl_Text,FORMAT_PRICE	,pData->m_fAddinPrice			);
   pData->InsertRowData(DBCustomer_key_bPrintDiaoPai		,map_row_data,FORMAT_STRING	,pData->m_bPrintDiaoPai	?_T("��"):_T("��")		);
   pData->InsertRowData(DBCustomer_key_bPrintYuE		,map_row_data,FORMAT_STRING	,pData->m_bPrintYuE ?_T("��"):_T("��")			);
   pData->InsertRowData(DBCustomer_key_fZMZheKou		,map_row_data,CB_enum_FieldData_Double2Point	,CB_enum_FieldCtrl_Text,FORMAT_PRICE,pData->m_fZMZheKou			);
   pData->InsertRowData(DBCustomer_key_cSalesID		,map_row_data,FORMAT_STRING	,pData->m_strSalesID			);
   return TRUE;
}

BOOL CDBCustomInfoList::CreateDropPopGridData(const CDBCustomInfoData* pData,MAP_GridCtrl_RowData& map_row_data)
{
   if (pData == NULL)
      return FALSE;

   // DBCustomInfo.m_strCusCode = pADOConn->GetValueString(DBCustomer_key_Code);
   InsertRowData(TABLE_CUSTOMER_1_CODE,pData->m_strCusCode,map_row_data);

   //DBCustomInfo.m_strCusAbbrevName = pADOConn->GetValueString(DBCustomer_key_Abbrev);
   InsertRowData(TABLE_CUSTOMER_1_NAME,pData->m_strCusName,map_row_data);

   //DBCustomInfo.m_strCusCate = pADOConn->GetValueString(DBCustomer_key_CusCate);
   InsertRowData(TABLE_CUSTOMER_1_CATE,pData->m_strCusCate,map_row_data);

   //DBCustomInfo.m_strMobile = pADOConn->GetValueString(DBCustomer_key_Mobile);
   InsertRowData(TABLE_CUSTOMER_1_PHONE,pData->m_strMobile,map_row_data);

   //DBCustomInfo.m_fDeposit = _ttof(pADOConn->GetValueString(DBCustomer_key_Deposit));
   CString strValue;
   strValue.Format(_T("%f"),pData->m_fDeposit);
   InsertRowData(TABLE_CUSTOMER_1_MARGIN,strValue,map_row_data);

   //DBCustomInfo.m_fLimit = _ttof(pADOConn->GetValueString(DBCustomer_key_Limit));
   strValue.Format(_T("%f"),pData->m_fLimit);
   InsertRowData(TABLE_CUSTOMER_1_UP_LIMIT,strValue,map_row_data);

   //DBCustomInfo.m_strProvince = pADOConn->GetValueString(DBCustomer_key_Province);
   InsertRowData(TABLE_CUSTOMER_1_SHENG,pData->m_strProvince,map_row_data);

   //DBCustomInfo.m_strEMS = pADOConn->GetValueString(DBCustomer_key_EMS);
   InsertRowData(TABLE_CUSTOMER_1_KUAIDI,pData->m_strEMS,map_row_data);
   return TRUE;
}

MAP_GridCtrl_AllData CDBCustomInfoList::CreateGridData( std::vector<int> treeGroupIDLst,CString strSaleID,CString strCusName,BOOL bLimitSale /*= FALSE*/ )
{
   MAP_GridCtrl_AllData  map_all_data;
   std::vector<CDBCustomInfoData *> dataLst;

   int nCount = GetCount();
   if (TRUE == bLimitSale)
   {
      for (int i = 0; i < nCount; i++)
      {
         CDBCustomInfoData * pData = GetItem(i);
         if (pData && pData->m_strSalesID.MakeUpper() == strSaleID.MakeUpper())
         {
            auto it = std::find(treeGroupIDLst.begin() ,treeGroupIDLst.end(), pData->m_iTreeGroupID);
            if (it != treeGroupIDLst.end())
            {
               if (strCusName == pData->m_strCusName)
               {
                   dataLst.push_back(pData);
               }
            }
         }
      }
   }else
   {
      for (int i = 0; i < nCount; i++)
      {
         CDBCustomInfoData * pData = GetItem(i);
         if (pData)
         {
            auto it = std::find(treeGroupIDLst.begin() ,treeGroupIDLst.end(), pData->m_iTreeGroupID);
            if (it != treeGroupIDLst.end())
            {
               if (strCusName == pData->m_strCusName)
               {
                  dataLst.push_back(pData);
               }
            }
         }
      }
   }
   int nValidCount = 1;
   for (size_t i = 0; i < dataLst.size() ;i++)
   {
      CDBCustomInfoData * pData = dataLst[i];
      if (NULL != pData)
      {
         MAP_GridCtrl_RowData map_row_data;
         CreateGridData(pData,map_row_data);
         map_all_data.insert(make_pair(nValidCount,map_row_data));
         nValidCount++;
      }
   }
   return map_all_data;
}

//����һ���յ�������		by WangZY 2017/08/24
BOOL CDBCustomInfoList::GetEmptyRowData(__out MAP_GridCtrl_RowData &mapEmptyRowData)
{
	mapEmptyRowData.clear();

	InsertRowData(DBCustomer_key_ID			 ,_T(""), mapEmptyRowData,CB_enum_FieldData_Int,CB_enum_FieldCtrl_Text);
	InsertRowData(DBCustomer_key_UpdateTime ,_T(""), mapEmptyRowData,CB_enum_FieldData_Time,CB_enum_FieldCtrl_DateTime);
	InsertRowData(DBCustomer_key_Cate		 ,_T(""), mapEmptyRowData);//����
	InsertRowData(DBCustomer_key_CusCate	 ,_T(""), mapEmptyRowData);//����
	InsertRowData(DBCustomer_key_Code		 ,_T(""), mapEmptyRowData);
	InsertRowData(DBCustomer_key_Name		 ,_T(""), mapEmptyRowData);
	InsertRowData(DBCustomer_key_Abbrev		 ,_T(""), mapEmptyRowData);
	InsertRowData(DBCustomer_key_Addr		 ,_T(""), mapEmptyRowData);
	InsertRowData(DBCustomer_key_Person		 ,_T(""), mapEmptyRowData);
	InsertRowData(DBCustomer_key_Phone		 ,_T(""), mapEmptyRowData);
	InsertRowData(DBCustomer_key_Fax			 ,_T(""), mapEmptyRowData);
	InsertRowData(DBCustomer_key_Mobile		 ,_T(""), mapEmptyRowData);
	InsertRowData(DBCustomer_key_WeChat		 ,_T(""), mapEmptyRowData);
	InsertRowData(DBCustomer_key_Remark		 ,_T(""), mapEmptyRowData);
	InsertRowData(DBCustomer_key_VenWeb		 ,_T(""), mapEmptyRowData);
	InsertRowData(DBCustomer_key_VenCode	 ,_T(""), mapEmptyRowData);
	InsertRowData(DBCustomer_key_VenPwd		 ,_T(""), mapEmptyRowData);
	InsertRowData(DBCustomer_key_Pwd			 ,_T(""), mapEmptyRowData);
	InsertRowData(DBCustomer_key_Arrears	 ,_T(""), mapEmptyRowData,CB_enum_FieldData_Double2Point,CB_enum_FieldCtrl_Text);
	InsertRowData(DBCustomer_key_Deposit	 ,_T(""), mapEmptyRowData,CB_enum_FieldData_Double2Point,CB_enum_FieldCtrl_Text);
	InsertRowData(DBCustomer_key_Limit		 ,_T(""), mapEmptyRowData,CB_enum_FieldData_Double2Point,CB_enum_FieldCtrl_Text);
	InsertRowData(DBCustomer_key_Province	 ,_T(""), mapEmptyRowData);
	InsertRowData(DBCustomer_key_City		 ,_T(""), mapEmptyRowData);
	InsertRowData(DBCustomer_key_Area		 ,_T(""), mapEmptyRowData);
	InsertRowData(DBCustomer_key_State		 ,_T(""), mapEmptyRowData);
	InsertRowData(DBCustomer_key_DeliveDays ,_T(""), mapEmptyRowData,CB_enum_FieldData_Int,CB_enum_FieldCtrl_Text);
	InsertRowData(DBCustomer_key_Num			 ,_T(""), mapEmptyRowData,CB_enum_FieldData_Int,CB_enum_FieldCtrl_Text);
	InsertRowData(DBCustomer_key_Loss		 ,_T(""), mapEmptyRowData,CB_enum_FieldData_Int,CB_enum_FieldCtrl_Text);
	InsertRowData(DBCustomer_key_EMS			 ,_T(""), mapEmptyRowData);
	InsertRowData(DBCustomer_key_ParrentCode,_T(""), mapEmptyRowData);
	InsertRowData(DBCustomer_key_ClerkCode	 ,_T(""), mapEmptyRowData);
	InsertRowData(DBCustomer_key_Rebate		 ,_T(""), mapEmptyRowData);
	InsertRowData(DBCustomer_key_WorkDoc	 ,_T(""), mapEmptyRowData);
	InsertRowData(DBCustomer_key_Tag			 ,_T(""), mapEmptyRowData);
	InsertRowData(DBCustomer_key_DeliveDoc	 ,_T(""), mapEmptyRowData);
	InsertRowData(DBCustomer_key_DepotPos	 ,_T(""), mapEmptyRowData);
	InsertRowData(DBCustomer_key_Sign		 ,_T(""), mapEmptyRowData);
	InsertRowData(DBCustomer_key_Unit		 ,_T(""), mapEmptyRowData);
	InsertRowData(DBCustomer_key_LV			 ,_T(""), mapEmptyRowData,CB_enum_FieldData_Int,CB_enum_FieldCtrl_Text);
	InsertRowData(CustomerTable_newCusName	 ,_T(""), mapEmptyRowData);
   InsertRowData(DBCustomer_key_iTreeGroupID	 ,_T(""), mapEmptyRowData, CB_enum_FieldData_Int, CB_enum_FieldCtrl_Text);
	InsertRowData(DBCustomer_key_iJijiaType ,_T(""), mapEmptyRowData);		
   InsertRowData(DBCustomer_key_fAddinPrice ,_T(""), mapEmptyRowData,CB_enum_FieldData_Double2Point,CB_enum_FieldCtrl_Text);	
   InsertRowData(DBCustomer_key_bPrintDiaoPai ,_T(""), mapEmptyRowData);	
   InsertRowData(DBCustomer_key_bPrintYuE ,_T(""), mapEmptyRowData);
   InsertRowData(DBCustomer_key_fZMZheKou ,_T(""), mapEmptyRowData);   
   InsertRowData(DBCustomer_key_cSalesID ,_T(""), mapEmptyRowData);   
	return TRUE;
}

//�����ύ�����޸�		by WangZY 2017/08/24
BOOL CDBCustomInfoList::SaveMultiModifyData(__in CADOConn *pADOConn,
											__in MAP_GridCtrl_AllData &mapAddData,
											__in MAP_GridCtrl_AllData &mapModifyData,
											__in MAP_GridCtrl_AllData &mapDeleteData,
											__in CString strMaker)
{
	ASSERT(pADOConn != NULL);
	//��Ҫд�ύ����		by WangZY 2017/08/27
	
	CString strSQL = _T("");

	//ִ��ɾ��
	for (auto it=mapDeleteData.begin(); it!=mapDeleteData.end(); ++it)
	{
		CString strID; 
		auto itData = it->second.find(DBCustomer_key_ID);
		if (itData == it->second.end())
		{
			return FALSE;
		}
		//ID
		strID = itData->second.strValue;
		
		strSQL.Format(_T("delete from %s where %s='%s'"),
			DB_TABLE_CUSTOM,DBCustomer_key_ID,strID);

		
		pADOConn->AppendBatchSQL(strSQL);
		
		CString strCusCode;
		CString strCate;
		CString strCusCate;
		CString strCusName;
		CString strDate;

		//�ͻ�����
		itData = it->second.find(DBCustomer_key_Code);
		if (itData != it->second.end())
		{
			strCusCode = itData->second.strValue;
		}
		
		//����
		itData = it->second.find(DBCustomer_key_Cate);
		if (itData != it->second.end())
		{
			strCate = itData->second.strValue;
		}

		//�ͻ�����
		itData = it->second.find(DBCustomer_key_CusCate);
		if (itData != it->second.end())
		{
			strCusCate = itData->second.strValue;
		}

		//�ͻ�����
		itData = it->second.find(DBCustomer_key_Name);
		if (itData != it->second.end())
		{
			strCusName = itData->second.strValue;
		}

		//����
		itData = it->second.find(DBCustomer_key_UpdateTime);
		if (itData != it->second.end())
		{
			strDate = itData->second.strValue;
		}
		
		//������־sql
		CString strSQLLog;

		strSQLLog.Format(_T("insert into WorkLog(cCate,cType,cCode,cMaker,cMemo) \
								  values('�ͻ�','�ͻ�����ɾ��','%s','%s',\
								  '%s,%s,%s,%s,%s,%s,%s')"),
								  strID,strMaker,strID, strCusCode, strCate, strCusCate,
								  strCusName,strDate,strMaker);

		pADOConn->AppendBatchSQL(strSQLLog);
	}


	//BOOL bBegin = pADOConn->BeginTrans();
	//if (!bBegin)
	//{
	//return FALSE;
	//}
	
	BOOL bExec = pADOConn->ExecuteBatchSQL();
	if (!bExec)
	{
		//BOOL bRollback = pADOConn->RollbackTrans();

		return FALSE;
	}

	//ִ���޸�
	BOOL bUpdateSuccess = TRUE;
	for (auto it=mapModifyData.begin(); it!=mapModifyData.end(); ++it)
	{
		CString strID; 
		auto itData = it->second.find(DBCustomer_key_ID);
		if (itData == it->second.end())
		{
			bUpdateSuccess = FALSE;
			
			break;
		}
		strID = itData->second.strValue;

		CString strCusCode;			//�ͻ�����
		CString strCate;				//����
		CString strCusCate;			//�ͻ�����---->������
		CString strCusName;			//�ͻ�����
		CString strDate;				//��������

		CString strCusAbbName;		//�ͻ����
		CString strCusAddress;		//�ͻ���ַ
		CString strCusPerson;		//�ͻ���ϵ��
		CString strCusPhone;			//�ͻ��绰
		CString strCusFax;			//�ͻ�����
		CString strCusMobile;		//�ͻ��ֻ�
		CString strCusWeixin;		//�ͻ�΢��
		CString strCusMemo;			//��ע
		CString strVenWeb;			//�ҵ��µ�ƽ̨
		CString strVenCode;			//�ҵ��µ��ʺ�
		CString strVenPwd;			//�ҵ��µ�����
		CString strPwd;				//��¼����
		CString strArrears;			//�ڳ����
		CString strDeposit;			//��֤��
		CString strLimit;				//Ƿ������
		CString strProvince;			//ʡ
		CString strCity;				//��
		CString strArea;				//����
		CString strState;				//״̬
		CString strDeliveDays;		//��������
		CString strNum;				//����
		CString strSunhao;			//���
		CString strEMS;				//���
		CString strParentCode;		//�ϼ�����
		CString strUserCode;			//ҵ��Ա���
		CString strFandian;			//����
		CString strJGD;				//Ĭ�ϼӹ���
		CString strTag;				//Ĭ�ϵ���
		CString strDeliveDoc;		//Ĭ�Ϸ�����
		CString strDepotPos;			//��λ
		CString strSign;				//ǩ��
		CString strUnit;				//��λ
		CString strCusLv;				//�ȼ�
		CString strJiJiaType;     //���ۼۼƼ۷�ʽ
#pragma region �ͻ������޸�

		//�ͻ�����      			
		itData = it->second.find(DBCustomer_key_Code);	
		if (itData != it->second.end())
		{
			strCusCode = itData->second.strValue;
		}

		//����            			
		itData = it->second.find(DBCustomer_key_Cate);	
		if (itData != it->second.end())
		{
			strCate = itData->second.strValue;
		}

		//�ͻ�����---->������			
		itData = it->second.find(DBCustomer_key_CusCate);	
		if (itData != it->second.end())
		{
			strCusCate = itData->second.strValue;
		}

		//�ͻ�����      			
		itData = it->second.find(DBCustomer_key_Name);	
		if (itData != it->second.end())
		{
			strCusName = itData->second.strValue;
		}

		//��������        			
		itData = it->second.find(DBCustomer_key_UpdateTime);	
		if (itData != it->second.end())
		{
			strDate = itData->second.strValue;
		}

		//�ͻ����      			
		itData = it->second.find(DBCustomer_key_Abbrev);	
		if (itData != it->second.end())
		{
			strCusAbbName = itData->second.strValue;
		}

		//�ͻ���ַ      			
		itData = it->second.find(DBCustomer_key_Addr);	
		if (itData != it->second.end())
		{
			strCusAddress = itData->second.strValue;
		}

		//�ͻ���ϵ��    			
		itData = it->second.find(DBCustomer_key_Person);	
		if (itData != it->second.end())
		{
			strCusPerson = itData->second.strValue;
		}

		//�ͻ��绰        			
		itData = it->second.find(DBCustomer_key_Phone);	
		if (itData != it->second.end())
		{
			strCusPhone = itData->second.strValue;
		}

		//�ͻ�����        			
		itData = it->second.find(DBCustomer_key_Fax);	
		if (itData != it->second.end())
		{
			strCusFax = itData->second.strValue;
		}

		//�ͻ��ֻ�      			
		itData = it->second.find(DBCustomer_key_Mobile);	
		if (itData != it->second.end())
		{
			strCusMobile = itData->second.strValue;
		}

		//�ͻ�΢��      			
		itData = it->second.find(DBCustomer_key_WeChat);	
		if (itData != it->second.end())
		{
			strCusWeixin = itData->second.strValue;
		}

		//��ע          			
		itData = it->second.find(DBCustomer_key_Remark);	
		if (itData != it->second.end())
		{
			strCusMemo = itData->second.strValue;
		}

		//�ҵ��µ�ƽ̨    			
		itData = it->second.find(DBCustomer_key_VenWeb);	
		if (itData != it->second.end())
		{
			strVenWeb = itData->second.strValue;
		}

		//�ҵ��µ��ʺ�    			
		itData = it->second.find(DBCustomer_key_VenCode);	
		if (itData != it->second.end())
		{
			strVenCode = itData->second.strValue;
		}

		//�ҵ��µ�����  			
		itData = it->second.find(DBCustomer_key_VenPwd);	
		if (itData != it->second.end())
		{
			strVenPwd = itData->second.strValue;
		}

		//��¼����      			
		itData = it->second.find(DBCustomer_key_Pwd);	
		if (itData != it->second.end())
		{
			strPwd = itData->second.strValue;
		}

		//�ڳ����          			
		itData = it->second.find(DBCustomer_key_Arrears);	
		if (itData != it->second.end())
		{
			strArrears = itData->second.strValue;
		}

		//��֤��          			
		itData = it->second.find(DBCustomer_key_Deposit);	
		if (itData != it->second.end())
		{
			strDeposit = itData->second.strValue;
		}

		//Ƿ������      			
		itData = it->second.find(DBCustomer_key_Limit);	
		if (itData != it->second.end())
		{
			strLimit = itData->second.strValue;
		}

		//ʡ              			
		itData = it->second.find(DBCustomer_key_Province);	
		if (itData != it->second.end())
		{
			strProvince = itData->second.strValue;
		}

		//��              			
		itData = it->second.find(DBCustomer_key_City);	
		if (itData != it->second.end())
		{
			strCity = itData->second.strValue;
		}

		//����            			
		itData = it->second.find(DBCustomer_key_Area);	
		if (itData != it->second.end())
		{
			strArea = itData->second.strValue;
		}

		//״̬            			
		itData = it->second.find(DBCustomer_key_State);	
		if (itData != it->second.end())
		{
			strState = itData->second.strValue;
		}

		//��������          			
		itData = it->second.find(DBCustomer_key_DeliveDays);	
		if (itData != it->second.end())
		{
			strDeliveDays = itData->second.strValue;
		}

		//����          			
		itData = it->second.find(DBCustomer_key_Num);	
		if (itData != it->second.end())
		{
			strNum = itData->second.strValue;
		}

		//���            			
		itData = it->second.find(DBCustomer_key_Loss);	
		if (itData != it->second.end())
		{
			strSunhao = itData->second.strValue;
		}

		//���            			
		itData = it->second.find(DBCustomer_key_EMS);	
		if (itData != it->second.end())
		{
			strEMS = itData->second.strValue;
		}

		//�ϼ�����    			
		itData = it->second.find(DBCustomer_key_ParrentCode);	
		if (itData != it->second.end())
		{
			strParentCode = itData->second.strValue;
		}

		//ҵ��Ա���			
		itData = it->second.find(DBCustomer_key_ClerkCode);	
		if (itData != it->second.end())
		{
			strUserCode = itData->second.strValue;
		}

		//����      			
		itData = it->second.find(DBCustomer_key_Rebate);	
		if (itData != it->second.end())
		{
			strFandian = itData->second.strValue;
		}

		//Ĭ�ϼӹ���  			
		itData = it->second.find(DBCustomer_key_WorkDoc);	
		if (itData != it->second.end())
		{
			strJGD = itData->second.strValue;
		}

		//Ĭ�ϵ���      			
		itData = it->second.find(DBCustomer_key_Tag);	
		if (itData != it->second.end())
		{
			strTag = itData->second.strValue;
		}

		//Ĭ�Ϸ�����  			
		itData = it->second.find(DBCustomer_key_DeliveDoc);	
		if (itData != it->second.end())
		{
			strDeliveDoc = itData->second.strValue;
		}

		//��λ      			
		itData = it->second.find(DBCustomer_key_DepotPos);	
		if (itData != it->second.end())
		{
			strDepotPos = itData->second.strValue;
		}

		//ǩ��        			
		itData = it->second.find(DBCustomer_key_Sign);	
		if (itData != it->second.end())
		{
			strSign = itData->second.strValue;
		}

		//��λ      			
		itData = it->second.find(DBCustomer_key_Unit);	
		if (itData != it->second.end())
		{
			strUnit = itData->second.strValue;
		}

		//�ȼ�        			
		itData = it->second.find(DBCustomer_key_LV);	
		if (itData != it->second.end())
		{
			strCusLv = itData->second.strValue;
		}
      //���ۼۼƼ۷�ʽ        
      itData = it->second.find(DBCustomer_key_iJijiaType);	
      if (itData != it->second.end())
      {
         strJiJiaType = itData->second.strValue;
      }
#pragma endregion �ͻ������޸�
		
		
		strSQL.Format(_T("Update %s set %s='%s',%s='%s',%s='%s',%s='%s',%s='%s',\
							  %s='%s',%s='%s',%s='%s',%s='%s',%s='%s',\
							  %s='%s',%s='%s',%s='%s',%s='%s',%s='%s',\
							  %s='%s',%s='%s',%s='%s',%s='%s',%s='%s',\
							  %s='%s',%s='%s',%s='%s',%s='%s',%s='%s',\
							  %s='%s',%s='%s',%s='%s',%s='%s',%s='%s',\
							  %s='%s',%s='%s',%s='%s',%s='%s',%s='%s',\
							%s='%s',%s='%s',%s='%s',%s='%s' where %s='%s'"),
							DB_TABLE_CUSTOM, 

			DBCustomer_key_UpdateTime	, strDate,					//��������
			DBCustomer_key_Cate			, strCate,					//����
			DBCustomer_key_CusCate		, strCusCate,				//�ͻ�����---->������
			DBCustomer_key_Code			, strCusCode,				//�ͻ�����
			DBCustomer_key_Name			, strCusName,				//�ͻ�����

			DBCustomer_key_Abbrev		, strCusAbbName,			//�ͻ����
			DBCustomer_key_Addr			, strCusAddress,			//�ͻ���ַ
			DBCustomer_key_Person		, strCusPerson,			//�ͻ���ϵ��
			DBCustomer_key_Phone			, strCusPhone,				//�ͻ��绰
			DBCustomer_key_Fax			, strCusFax,				//�ͻ�����

			DBCustomer_key_Mobile		, strCusMobile,			//�ͻ��ֻ�
			DBCustomer_key_WeChat		, strCusWeixin,			//�ͻ�΢��
			DBCustomer_key_Remark		, strCusMemo,				//��ע
			DBCustomer_key_VenWeb		, strVenWeb,				//�ҵ��µ�ƽ̨
			DBCustomer_key_VenCode		, strVenCode,				//�ҵ��µ��ʺ�

			DBCustomer_key_VenPwd		, strVenPwd,				//�ҵ��µ�����
			DBCustomer_key_Pwd			, strPwd,					//��¼����
			DBCustomer_key_Arrears		, strArrears,				//�ڳ����
			DBCustomer_key_Deposit		, strDeposit,				//��֤��
			DBCustomer_key_Limit			, strLimit,					//Ƿ������

			DBCustomer_key_Province		, strProvince,				//ʡ
			DBCustomer_key_City			, strCity,					//��
			DBCustomer_key_Area			, strArea,					//����
			DBCustomer_key_State			, strState,					//״̬
			DBCustomer_key_DeliveDays	, strDeliveDays,			//��������

			DBCustomer_key_Num			, strNum,					//����
			DBCustomer_key_Loss			, strSunhao,				//���
			DBCustomer_key_EMS			, strEMS,					//���
			DBCustomer_key_ParrentCode	, strParentCode,			//�ϼ�����
			DBCustomer_key_ClerkCode	, strUserCode,				//ҵ��Ա���

			DBCustomer_key_Rebate		, strFandian,				//����
			DBCustomer_key_WorkDoc		, strJGD,					//Ĭ�ϼӹ���
			DBCustomer_key_Tag			, strTag,					//Ĭ�ϵ���
			DBCustomer_key_DeliveDoc	, strDeliveDoc,			//Ĭ�Ϸ�����
			DBCustomer_key_DepotPos		, strDepotPos,				//��λ

			DBCustomer_key_Sign			, strSign,					//ǩ��
			DBCustomer_key_Unit			, strUnit,					//��λ
			DBCustomer_key_LV				, strCusLv,					//�ȼ�
         DBCustomer_key_iJijiaType				, strJiJiaType,					//���ۼۼƼ۷�ʽ
			DBCustomer_key_ID				, strID);					//ID


		pADOConn->ExecuteSQL(strSQL);
		
		//������־sql
		CString strSQLLog;

		strSQLLog.Format(_T("insert into WorkLog(cCate,cType,cCode,cMaker,cMemo) \
								  values('�ͻ�','�ͻ������޸�','%s','%s',\
								  '%s,%s,%s,%s,%s,%s,%s')"),
								  strID,strMaker,strID, strCusCode, strCate, strCusCate,
								  strCusName,strDate,strMaker);

		pADOConn->ExecuteSQL(strSQLLog);
	}
	
	if (!bUpdateSuccess)
	{
		//BOOL bRollback = pADOConn->RollbackTrans();

		return FALSE;
	}
#pragma region �ͻ���������

	//ִ������
	BOOL bAddSuccess = TRUE;
	for (auto it=mapAddData.begin(); it!=mapAddData.end(); ++it)
	{
		CString strCusCode;			//�ͻ�����
		CString strCate;				//����
		CString strCusCate;			//�ͻ�����---->������
		CString strCusName;			//�ͻ�����
		CString strDate;				//��������

		CString strCusAbbName;		//�ͻ����
		CString strCusAddress;		//�ͻ���ַ
		CString strCusPerson;		//�ͻ���ϵ��
		CString strCusPhone;			//�ͻ��绰
		CString strCusFax;			//�ͻ�����
		CString strCusMobile;		//�ͻ��ֻ�
		CString strCusWeixin;		//�ͻ�΢��
		CString strCusMemo;			//��ע
		CString strVenWeb;			//�ҵ��µ�ƽ̨
		CString strVenCode;			//�ҵ��µ��ʺ�
		CString strVenPwd;			//�ҵ��µ�����
		CString strPwd;				//��¼����
		CString strArrears;			//�ڳ����
		CString strDeposit;			//��֤��
		CString strLimit;				//Ƿ������
		CString strProvince;			//ʡ
		CString strCity;				//��
		CString strArea;				//����
		CString strState;				//״̬
		CString strDeliveDays;		//��������
		CString strNum;				//����
		CString strSunhao;			//���
		CString strEMS;				//���
		CString strParentCode;		//�ϼ�����
		CString strUserCode;			//ҵ��Ա���
		CString strFandian;			//����
		CString strJGD;				//Ĭ�ϼӹ���
		CString strTag;				//Ĭ�ϵ���
		CString strDeliveDoc;		//Ĭ�Ϸ�����
		CString strDepotPos;			//��λ
		CString strSign;				//ǩ��
		CString strUnit;				//��λ
		CString strCusLv;				//�ȼ�
      CString strJiJiaType;     //���ۼۼƼ۷�ʽ

		//�ͻ�����      			
		auto itData = it->second.find(DBCustomer_key_Code);	
		if (itData != it->second.end())
		{
			strCusCode = itData->second.strValue;
		}

		//����            			
		itData = it->second.find(DBCustomer_key_Cate);	
		if (itData != it->second.end())
		{
			strCate = itData->second.strValue;
		}

		//�ͻ�����---->������			
		itData = it->second.find(DBCustomer_key_CusCate);	
		if (itData != it->second.end())
		{
			strCusCate = itData->second.strValue;
		}

		//�ͻ�����      			
		itData = it->second.find(DBCustomer_key_Name);	
		if (itData != it->second.end())
		{
			strCusName = itData->second.strValue;
		}

		//��������        			
		itData = it->second.find(DBCustomer_key_UpdateTime);	
		if (itData != it->second.end())
		{
			strDate = itData->second.strValue;
		}

		//�ͻ����      			
		itData = it->second.find(DBCustomer_key_Abbrev);	
		if (itData != it->second.end())
		{
			strCusAbbName = itData->second.strValue;
		}

		//�ͻ���ַ      			
		itData = it->second.find(DBCustomer_key_Addr);	
		if (itData != it->second.end())
		{
			strCusAddress = itData->second.strValue;
		}

		//�ͻ���ϵ��    			
		itData = it->second.find(DBCustomer_key_Person);	
		if (itData != it->second.end())
		{
			strCusPerson = itData->second.strValue;
		}

		//�ͻ��绰        			
		itData = it->second.find(DBCustomer_key_Phone);	
		if (itData != it->second.end())
		{
			strCusPhone = itData->second.strValue;
		}

		//�ͻ�����        			
		itData = it->second.find(DBCustomer_key_Fax);	
		if (itData != it->second.end())
		{
			strCusFax = itData->second.strValue;
		}

		//�ͻ��ֻ�      			
		itData = it->second.find(DBCustomer_key_Mobile);	
		if (itData != it->second.end())
		{
			strCusMobile = itData->second.strValue;
		}

		//�ͻ�΢��      			
		itData = it->second.find(DBCustomer_key_WeChat);	
		if (itData != it->second.end())
		{
			strCusWeixin = itData->second.strValue;
		}

		//��ע          			
		itData = it->second.find(DBCustomer_key_Remark);	
		if (itData != it->second.end())
		{
			strCusMemo = itData->second.strValue;
		}

		//�ҵ��µ�ƽ̨    			
		itData = it->second.find(DBCustomer_key_VenWeb);	
		if (itData != it->second.end())
		{
			strVenWeb = itData->second.strValue;
		}

		//�ҵ��µ��ʺ�    			
		itData = it->second.find(DBCustomer_key_VenCode);	
		if (itData != it->second.end())
		{
			strVenCode = itData->second.strValue;
		}

		//�ҵ��µ�����  			
		itData = it->second.find(DBCustomer_key_VenPwd);	
		if (itData != it->second.end())
		{
			strVenPwd = itData->second.strValue;
		}

		//��¼����      			
		itData = it->second.find(DBCustomer_key_Pwd);	
		if (itData != it->second.end())
		{
			strPwd = itData->second.strValue;
		}

		//�ڳ����          			
		itData = it->second.find(DBCustomer_key_Arrears);	
		if (itData != it->second.end())
		{
			strArrears = itData->second.strValue;
		}

		//��֤��          			
		itData = it->second.find(DBCustomer_key_Deposit);	
		if (itData != it->second.end())
		{
			strDeposit = itData->second.strValue;
		}

		//Ƿ������      			
		itData = it->second.find(DBCustomer_key_Limit);	
		if (itData != it->second.end())
		{
			strLimit = itData->second.strValue;
		}

		//ʡ              			
		itData = it->second.find(DBCustomer_key_Province);	
		if (itData != it->second.end())
		{
			strProvince = itData->second.strValue;
		}

		//��              			
		itData = it->second.find(DBCustomer_key_City);	
		if (itData != it->second.end())
		{
			strCity = itData->second.strValue;
		}

		//����            			
		itData = it->second.find(DBCustomer_key_Area);	
		if (itData != it->second.end())
		{
			strArea = itData->second.strValue;
		}

		//״̬            			
		itData = it->second.find(DBCustomer_key_State);	
		if (itData != it->second.end())
		{
			strState = itData->second.strValue;
		}

		//��������          			
		itData = it->second.find(DBCustomer_key_DeliveDays);	
		if (itData != it->second.end())
		{
			strDeliveDays = itData->second.strValue;
		}

		//����          			
		itData = it->second.find(DBCustomer_key_Num);	
		if (itData != it->second.end())
		{
			strNum = itData->second.strValue;
		}

		//���            			
		itData = it->second.find(DBCustomer_key_Loss);	
		if (itData != it->second.end())
		{
			strSunhao = itData->second.strValue;
		}

		//���            			
		itData = it->second.find(DBCustomer_key_EMS);	
		if (itData != it->second.end())
		{
			strEMS = itData->second.strValue;
		}

		//�ϼ�����    			
		itData = it->second.find(DBCustomer_key_ParrentCode);	
		if (itData != it->second.end())
		{
			strParentCode = itData->second.strValue;
		}

		//ҵ��Ա���			
		itData = it->second.find(DBCustomer_key_ClerkCode);	
		if (itData != it->second.end())
		{
			strUserCode = itData->second.strValue;
		}

		//����      			
		itData = it->second.find(DBCustomer_key_Rebate);	
		if (itData != it->second.end())
		{
			strFandian = itData->second.strValue;
		}

		//Ĭ�ϼӹ���  			
		itData = it->second.find(DBCustomer_key_WorkDoc);	
		if (itData != it->second.end())
		{
			strJGD = itData->second.strValue;
		}

		//Ĭ�ϵ���      			
		itData = it->second.find(DBCustomer_key_Tag);	
		if (itData != it->second.end())
		{
			strTag = itData->second.strValue;
		}

		//Ĭ�Ϸ�����  			
		itData = it->second.find(DBCustomer_key_DeliveDoc);	
		if (itData != it->second.end())
		{
			strDeliveDoc = itData->second.strValue;
		}

		//��λ      			
		itData = it->second.find(DBCustomer_key_DepotPos);	
		if (itData != it->second.end())
		{
			strDepotPos = itData->second.strValue;
		}

		//ǩ��        			
		itData = it->second.find(DBCustomer_key_Sign);	
		if (itData != it->second.end())
		{
			strSign = itData->second.strValue;
		}

		//��λ      			
		itData = it->second.find(DBCustomer_key_Unit);	
		if (itData != it->second.end())
		{
			strUnit = itData->second.strValue;
		}

		//�ȼ�        			
		itData = it->second.find(DBCustomer_key_LV);	
		if (itData != it->second.end())
		{
			strCusLv = itData->second.strValue;
		}
      //���ۼۼƼ۷�ʽ        
      itData = it->second.find(DBCustomer_key_iJijiaType);	
      if (itData != it->second.end())
      {
         strJiJiaType = itData->second.strValue;
      }

		CString strSQL;

		strSQL.Format(_T("insert into %s(%s,%s,%s,%s,%s,\
							  %s,%s,%s,%s,%s,\
							  %s,%s,%s,%s,%s,\
							  %s,%s,%s,%s,%s,\
							  %s,%s,%s,%s,%s,\
							  %s,%s,%s,%s,%s,\
							  %s,%s,%s,%s,%s,\
							  %s,%s,%s,%s)\
							values('%s','%s','%s','%s','%s',\
							'%s','%s','%s','%s','%s',\
							'%s','%s','%s','%s','%s',\
							'%s','%s','%s','%s','%s',\
							'%s','%s','%s','%s','%s',\
							'%s','%s','%s','%s','%s',\
							'%s','%s','%s','%s','%s',\
							'%s','%s','%s','%s')"),
							DB_TABLE_CUSTOM,

							DBCustomer_key_UpdateTime	,
							DBCustomer_key_Cate			,
							DBCustomer_key_CusCate		,
							DBCustomer_key_Code			,
							DBCustomer_key_Name			,

							DBCustomer_key_Abbrev		,
							DBCustomer_key_Addr			,
							DBCustomer_key_Person		,
							DBCustomer_key_Phone			,
							DBCustomer_key_Fax			,

							DBCustomer_key_Mobile		,
							DBCustomer_key_WeChat		,
							DBCustomer_key_Remark		,
							DBCustomer_key_VenWeb		,
							DBCustomer_key_VenCode		,

							DBCustomer_key_VenPwd		,
							DBCustomer_key_Pwd			,
							DBCustomer_key_Arrears		,
							DBCustomer_key_Deposit		,
							DBCustomer_key_Limit			,

							DBCustomer_key_Province		,
							DBCustomer_key_City			,
							DBCustomer_key_Area			,
							DBCustomer_key_State			,
							DBCustomer_key_DeliveDays	,

							DBCustomer_key_Num			,
							DBCustomer_key_Loss			,
							DBCustomer_key_EMS			,
							DBCustomer_key_ParrentCode	,
							DBCustomer_key_ClerkCode	,

							DBCustomer_key_Rebate		,
							DBCustomer_key_WorkDoc		,
							DBCustomer_key_Tag			,
							DBCustomer_key_DeliveDoc	,
							DBCustomer_key_DepotPos		,

							DBCustomer_key_Sign			,
							DBCustomer_key_Unit			,
							DBCustomer_key_LV				,
                     DBCustomer_key_iJijiaType  ,
							strDate,					//��������
							strCate,					//����
							strCusCate,				//�ͻ�����
							strCusCode,				//�ͻ�����
							strCusName,				//�ͻ�����

							strCusAbbName,			//�ͻ����
							strCusAddress,			//�ͻ���ַ
							strCusPerson,			//�ͻ���ϵ��
							strCusPhone,			//�ͻ��绰
							strCusFax,				//�ͻ�����

							strCusMobile,			//�ͻ��ֻ�
							strCusWeixin,			//�ͻ�΢��
							strCusMemo,				//��ע
							strVenWeb,				//�ҵ��µ�ƽ̨
							strVenCode,				//�ҵ��µ��ʺ�

							strVenPwd,				//�ҵ��µ�����
							strPwd,					//��¼����
							strArrears,				//�ڳ����
							strDeposit,				//��֤��
							strLimit,				//Ƿ������

							strProvince,			//ʡ
							strCity,					//��
							strArea,					//����
							strState,				//״̬
							strDeliveDays,			//��������

							strNum,					//����
							strSunhao,				//���
							strEMS,					//���
							strParentCode,			//�ϼ�����
							strUserCode,			//ҵ��Ա���

							strFandian,				//����
							strJGD,					//Ĭ�ϼӹ���
							strTag,					//Ĭ�ϵ���
							strDeliveDoc,			//Ĭ�Ϸ�����
							strDepotPos,			//��λ

							strSign,					//ǩ��
							strUnit,					//��λ
							strCusLv					//�ȼ�
                     ,strJiJiaType
							);
			
			BOOL bExec = pADOConn->ExecuteSQL(strSQL);
			if (!bExec)
			{
				bAddSuccess = FALSE;

				break;
			}

			//������־sql
			CString strSQLLog;

			strSQLLog.Format(_T("insert into WorkLog(cCate,cType,cCode,cMaker,cMemo) \
									  values('�ͻ�','�ͻ���������','%s','%s',\
									  '%s,%s,%s,%s,%s,%s')"),
									  strCusCode,strMaker,strCusCode, strCate, strCusCate,
									  strCusName,strDate,strMaker);

			pADOConn->ExecuteSQL(strSQLLog);
	}

	if (!bAddSuccess)
	{
		//BOOL bRollback = pADOConn->RollbackTrans();

		return FALSE;
	}
#pragma endregion �ͻ���������
	
	//BOOL bCommit = pADOConn->CommitTrans();
	//if (!bCommit)
	//{
	//	return FALSE;
	//}

	

	return TRUE;
}

MAP_GridCtrl_AllData CDBCustomInfoList::CreateGridData_Cumstomer(CADOConn *pADOConn,CString strFilter,Enum_Customer_State stateType)
{
	ASSERT(pADOConn != NULL);
	MAP_GridCtrl_AllData  map_all_data;

	//CString strFilter = _T("��Ӧ��");
	CString strSQL = _T("");
   if (strFilter.IsEmpty())
   {
      switch(stateType)
      {
      case Enum_Customer_ZanBuHeZuo://��Ҫ�߳�״̬Ϊ�ݲ������Ŀͻ� yangjr 2017-7-26
         strSQL.Format(_T("select %s, %s, %s , %s, %s from %s where %s != '%s' order by %s;"),
            DBCustomer_key_Code,DBCustomer_key_Name,DBCustomer_key_CusCate,DBCustomer_key_Person,DBCustomer_key_iTreeGroupID,DB_TABLE_CUSTOM,DBCustomer_key_Cate, _T("�ݲ�����"),DBCustomer_key_Code);
         break;
      default:
         strSQL.Format(_T("select %s, %s, %s , %s, %s from %s order by %s;"),
            DBCustomer_key_Code,DBCustomer_key_Name,DBCustomer_key_CusCate,DBCustomer_key_Person,DBCustomer_key_iTreeGroupID,DB_TABLE_CUSTOM,DBCustomer_key_Cate,DBCustomer_key_Code);
         break;
      }      
   }else
   {
      switch(stateType)
      {
		case Enum_Customer_OrderOutWork:	//������ѯ:ί��ӹ�
			strSQL.Format(_T("select %s, %s,\
				cCusPhone as %s , %s, %s \
				from %s where %s<>'%s' and cState<>'�ݲ�����' \
				order by %s;"),
				DBCustomer_key_Code,DBCustomer_key_Name,DBCustomer_key_CusCate,DBCustomer_key_Person,DBCustomer_key_iTreeGroupID,
				DB_TABLE_CUSTOM,DBCustomer_key_Cate,strFilter,DBCustomer_key_Code);
			break;
		case Enum_Customer_FinancialLedger:
			strSQL.Format(_T("select %s,%s,%s , %s, %s \
								  from %s \
								  where %s != '%s' order by %s;"),
								  DBCustomer_key_Code,DBCustomer_key_Name,DBCustomer_key_CusCate,DBCustomer_key_Person,DBCustomer_key_iTreeGroupID,
								  DB_TABLE_CUSTOM,DBCustomer_key_Cate,strFilter,DBCustomer_key_Code);
			break;
      case Enum_Customer_ZanBuHeZuo:
         strSQL.Format(_T("select %s,%s, %s , %s, %s from %s where %s != '%s' and %s != '%s' order by %s;"),
            DBCustomer_key_Code,DBCustomer_key_Name,DBCustomer_key_CusCate,DBCustomer_key_Person,DBCustomer_key_iTreeGroupID,DB_TABLE_CUSTOM,DBCustomer_key_Cate,strFilter, 
            DBCustomer_key_State,_T("�ݲ�����"),DBCustomer_key_Code);
         break;
	  case  Enum_Customer_JinZhiOrder://����µ��пͻ��б���ʾ����Ӧ�̣���𣩡��ݲ�������״̬������ֹ�µ���״̬���ͻ������б���
		  strSQL.Format(_T("select %s,%s, %s , %s, %s from %s where %s != '%s' and %s != '%s' and %s != '%s'  order by %s;"),
		  DBCustomer_key_Code,DBCustomer_key_Name,DBCustomer_key_CusCate,DBCustomer_key_Person,DBCustomer_key_iTreeGroupID,DB_TABLE_CUSTOM,DBCustomer_key_Cate,strFilter, 
		  DBCustomer_key_State,_T("�ݲ�����"),DBCustomer_key_State,_T("��ֹ�µ�"),DBCustomer_key_Code);
		  break;
      default:
         strSQL.Format(_T("select %s, %s, %s , %s, %s from %s where %s != '%s' order by %s;"),
            DBCustomer_key_Code,DBCustomer_key_Name,DBCustomer_key_CusCate,DBCustomer_key_Person,DBCustomer_key_iTreeGroupID,DB_TABLE_CUSTOM,DBCustomer_key_Cate,strFilter,DBCustomer_key_Code);
         break;
      }
   }
	pADOConn->GetRecordSet(strSQL);

	int nRow = 0;
	while (!pADOConn->adoEOF())
	{
		MAP_GridCtrl_RowData map_row_data;

		CString strCode = pADOConn->GetValueString(DBCustomer_key_Code);
		S_GridCtrl_FieldData s_filed_Code;
		s_filed_Code.strValue = strCode;
		s_filed_Code.fieldDataType = CB_enum_FieldData_CString;
		s_filed_Code.fieldCtrlType = CB_enum_FieldCtrl_Text;
		map_row_data.insert(make_pair(TABLE_CUSTOMER_CODE	,s_filed_Code));//Code
		
		CString strName = pADOConn->GetValueString(DBCustomer_key_Name);
		S_GridCtrl_FieldData s_filed_Name;
		s_filed_Name.strValue = strName;
		s_filed_Name.fieldDataType = CB_enum_FieldData_CString;
		s_filed_Name.fieldCtrlType = CB_enum_FieldCtrl_Text;
		map_row_data.insert(make_pair(TABLE_CUSTOMER_NAME	,s_filed_Name));//Name

		CString strCate = pADOConn->GetValueString(DBCustomer_key_CusCate);
		S_GridCtrl_FieldData s_filed_Cate;
		s_filed_Cate.strValue = strCate;
		s_filed_Cate.fieldDataType = CB_enum_FieldData_CString;
		s_filed_Cate.fieldCtrlType = CB_enum_FieldCtrl_Text;
		map_row_data.insert(make_pair(TABLE_CUSTOMER_CAPTION	,s_filed_Cate));//Name

      InsertRowData(TABLE_CUSTOMER_1_GroupID,pADOConn->GetValueString(DBCustomer_key_iTreeGroupID),map_row_data);

      InsertRowData(TABLE_CUSTOMER_1_CusPerson,pADOConn->GetValueString(DBCustomer_key_Person),map_row_data);

		map_all_data.insert(make_pair(nRow++,map_row_data));
		pADOConn->MoveNext();
	}
	return map_all_data;
}

MAP_GridCtrl_AllData CDBCustomInfoList::CreateGridData_Cumstomer_1(CADOConn *pADOConn,BOOL bHasAbbreviation /*= TRUE*/)
{
	ASSERT(pADOConn != NULL);
	MAP_GridCtrl_AllData  map_all_data;
   ////��ȡ�ͻ�cCusCode<>'0000' and cCate<>'��Ӧ��' and cState<>'�ݲ�����' order by cCusCode yangjr 2017-7-28
	//CString strFilter = _T("��Ӧ��");
	CString strSQL = _T("");

   CString strCusAbbName = _T("");
   //if (bHasAbbreviation)
   //{
   //   strCusAbbName = _T("(dbo.getPY(cCusName)+'-'+cCusName)");
   //}
   //else
      strCusAbbName= _T("(cCusName)");

	strSQL.Format(_T("select %s,%s as %s,%s,%s,%s,%s,%s,%s,%s,%s from %s where %s <>'0000' and %s <>'��Ӧ��'and %s<>'�ݲ�����' and %s<>'��ֹ�µ�' order by %s;")
      ,DBCustomer_key_Code,strCusAbbName,DBCustomer_key_Abbrev,DBCustomer_key_CusCate,DBCustomer_key_Mobile,DBCustomer_key_Deposit,DBCustomer_key_Limit
		,DBCustomer_key_Province,DBCustomer_key_EMS,DBCustomer_key_iTreeGroupID,DBCustomer_key_Person,DB_TABLE_CUSTOM,DBCustomer_key_Code,DBCustomer_key_Cate,DBCustomer_key_State,DBCustomer_key_State,DBCustomer_key_Code);
	pADOConn->GetRecordSet(strSQL);

	int nRow = 0;
	while (!pADOConn->adoEOF())
	{
		MAP_GridCtrl_RowData map_row_data;
      CDBCustomInfoData DBCustomInfo;

		DBCustomInfo.m_strCusCode = pADOConn->GetValueString(DBCustomer_key_Code);
		InsertRowData(TABLE_CUSTOMER_1_CODE,DBCustomInfo.m_strCusCode,map_row_data);

		DBCustomInfo.m_strCusAbbrevName = pADOConn->GetValueString(DBCustomer_key_Abbrev);
		InsertRowData(TABLE_CUSTOMER_1_NAME,DBCustomInfo.m_strCusAbbrevName,map_row_data);

		DBCustomInfo.m_strCusCate = pADOConn->GetValueString(DBCustomer_key_CusCate);
		InsertRowData(TABLE_CUSTOMER_1_CATE,DBCustomInfo.m_strCusCate,map_row_data);

		DBCustomInfo.m_strMobile = pADOConn->GetValueString(DBCustomer_key_Mobile);
		InsertRowData(TABLE_CUSTOMER_1_PHONE,DBCustomInfo.m_strMobile,map_row_data);

		DBCustomInfo.m_fDeposit = _ttof(pADOConn->GetValueString(DBCustomer_key_Deposit));
      CString strValue = pADOConn->GetValueString(DBCustomer_key_Deposit);
		InsertRowData(TABLE_CUSTOMER_1_MARGIN,strValue,map_row_data);

		DBCustomInfo.m_fLimit = _ttof(pADOConn->GetValueString(DBCustomer_key_Limit));
      strValue   = pADOConn->GetValueString(DBCustomer_key_Limit);
		InsertRowData(TABLE_CUSTOMER_1_UP_LIMIT,strValue,map_row_data);

      DBCustomInfo.m_strProvince = pADOConn->GetValueString(DBCustomer_key_Province);
		InsertRowData(TABLE_CUSTOMER_1_SHENG,DBCustomInfo.m_strProvince,map_row_data);

      DBCustomInfo.m_strEMS = pADOConn->GetValueString(DBCustomer_key_EMS);
		InsertRowData(TABLE_CUSTOMER_1_KUAIDI,DBCustomInfo.m_strEMS,map_row_data);

      InsertRowData(TABLE_CUSTOMER_1_GroupID,pADOConn->GetValueString(DBCustomer_key_iTreeGroupID),map_row_data);

      InsertRowData(TABLE_CUSTOMER_1_CusPerson,pADOConn->GetValueString(DBCustomer_key_Person),map_row_data);

		map_all_data.insert(make_pair(nRow++,map_row_data));
      AddItem(&DBCustomInfo);
		pADOConn->MoveNext();
	}
	return map_all_data;			
}

MAP_GridCtrl_AllData CDBCustomInfoList::CreateGridData_Cumstomer_OrderEntry(CADOConn *pADOConn,__out map<CString/*CusCode*/,CString/*iDays*/>& map_CusDays)
{
	map_CusDays.clear();
	ASSERT(pADOConn != NULL);
	MAP_GridCtrl_AllData  map_all_data;
	CString strSQL = _T("");
	strSQL.Format(_T("select %s,(dbo.getPY(%s)+'-'+%s) as %s,\
		%s ,%s from %s where %s<>'��Ӧ��' and %s<>'�ݲ�����' and %s<>'��ֹ�µ�';"),
		DBCustomer_key_Code,DBCustomer_key_Name,DBCustomer_key_Name,DBCustomer_key_Abbrev,DBCustomer_key_CusCate,DBCustomer_key_DeliveDays,
		DB_TABLE_CUSTOM,DBCustomer_key_Cate,DBCustomer_key_State,DBCustomer_key_State);
	pADOConn->GetRecordSet(strSQL);
	while(!pADOConn->adoEOF())
	{
		MAP_GridCtrl_RowData map_row_data;

		CString strCode = pADOConn->GetValueString(DBCustomer_key_Code);
		S_GridCtrl_FieldData s_filed_Code;
		s_filed_Code.strValue = strCode;
		s_filed_Code.fieldDataType = CB_enum_FieldData_CString;
		s_filed_Code.fieldCtrlType = CB_enum_FieldCtrl_Text;
		map_row_data.insert(make_pair(TABLE_CUSTOMER_CODE	,s_filed_Code));//Code

		CString strName = pADOConn->GetValueString(DBCustomer_key_Abbrev);
		S_GridCtrl_FieldData s_filed_Name;
		s_filed_Name.strValue = strName;
		s_filed_Name.fieldDataType = CB_enum_FieldData_CString;
		s_filed_Name.fieldCtrlType = CB_enum_FieldCtrl_Text;
		map_row_data.insert(make_pair(TABLE_CUSTOMER_NAME	,s_filed_Name));//Name

		CString strCate = pADOConn->GetValueString(DBCustomer_key_CusCate);
		S_GridCtrl_FieldData s_filed_Cate;
		s_filed_Cate.strValue = strCate;
		s_filed_Cate.fieldDataType = CB_enum_FieldData_CString;
		s_filed_Cate.fieldCtrlType = CB_enum_FieldCtrl_Text;
		map_row_data.insert(make_pair(TABLE_CUSTOMER_CAPTION	,s_filed_Cate));//Cate

		CString striDays = pADOConn->GetValueString(DBCustomer_key_DeliveDays);

		map_CusDays.insert(make_pair(strCode,striDays));	
		map_all_data.insert(make_pair(map_all_data.size(),map_row_data));
		pADOConn->MoveNext();
	}
	return map_all_data;	
}

//��ȡ��Ӧ�ͻ����͵����ų��ݲ����������пͻ����� yangjr 2017-12-12
MAP_GridCtrl_AllData CDBCustomInfoList::CreateGridData_CumstomerByCate(CADOConn *pADOConn,CString strFilterCusCate)
{
   ASSERT(pADOConn != NULL);
   MAP_GridCtrl_AllData  map_all_data;
      
   if (strFilterCusCate.IsEmpty())
   {
      return map_all_data;
   }
   CString strSQL = _T("");   
   strSQL.Format(_T("select %s,%s,%s,%s,%s from %s where %s = '%s' and %s != '%s' order by %s;"),
      DBCustomer_key_Code,DBCustomer_key_Name,DBCustomer_key_iTreeGroupID,DBCustomer_key_CusCate,DBCustomer_key_Person,DB_TABLE_CUSTOM,DBCustomer_key_Cate,strFilterCusCate, 
      DBCustomer_key_State,_T("�ݲ�����"),DBCustomer_key_Code);
   pADOConn->GetRecordSet(strSQL);

   int nRow = 0;
   while (!pADOConn->adoEOF())
   {
      MAP_GridCtrl_RowData map_row_data;

      CString strCode = pADOConn->GetValueString(DBCustomer_key_Code);
      S_GridCtrl_FieldData s_filed_Code;
      s_filed_Code.strValue = strCode;
      s_filed_Code.fieldDataType = CB_enum_FieldData_CString;
      s_filed_Code.fieldCtrlType = CB_enum_FieldCtrl_Text;
      map_row_data.insert(make_pair(TABLE_CUSTOMER_CODE	,s_filed_Code));//Code

      CString strName = pADOConn->GetValueString(DBCustomer_key_Name);
      S_GridCtrl_FieldData s_filed_Name;
      s_filed_Name.strValue = strName;
      s_filed_Name.fieldDataType = CB_enum_FieldData_CString;
      s_filed_Name.fieldCtrlType = CB_enum_FieldCtrl_Text;
      map_row_data.insert(make_pair(TABLE_CUSTOMER_NAME	,s_filed_Name));//Name

      CString strCate = pADOConn->GetValueString(DBCustomer_key_CusCate);
      S_GridCtrl_FieldData s_filed_Cate;
      s_filed_Cate.strValue = strCate;
      s_filed_Cate.fieldDataType = CB_enum_FieldData_CString;
      s_filed_Cate.fieldCtrlType = CB_enum_FieldCtrl_Text;
      map_row_data.insert(make_pair(TABLE_CUSTOMER_CAPTION	,s_filed_Cate));//Name

      CString strPerson = pADOConn->GetValueString(DBCustomer_key_Person);
      S_GridCtrl_FieldData s_filed_Person;
      s_filed_Person.strValue = strPerson;
      s_filed_Person.fieldDataType = CB_enum_FieldData_CString;
      s_filed_Person.fieldCtrlType = CB_enum_FieldCtrl_Text;
      map_row_data.insert(make_pair(TABLE_CUSTOMER_1_CusPerson	,s_filed_Person));//Person
      
      CString strGroupID = pADOConn->GetValueString(DBCustomer_key_iTreeGroupID);
      S_GridCtrl_FieldData s_filed_GroupID;
      s_filed_GroupID.strValue = strGroupID;
      s_filed_GroupID.fieldDataType = CB_enum_FieldData_Int;
      s_filed_GroupID.fieldCtrlType = CB_enum_FieldCtrl_Text;
      map_row_data.insert(make_pair(TABLE_CUSTOMER_1_GroupID	,s_filed_GroupID));//Person

      map_all_data.insert(make_pair(nRow++,map_row_data));
      pADOConn->MoveNext();
   }
   return map_all_data;
}

//��ȡ��ǰ�ͻ����ۻ�Ƿ���� yangjr 2017-07-28
CString CDBCustomInfoList::GetQianKuanJinEr(CADOConn *pADOConn,CString cusCode)
{
   ASSERT(pADOConn != NULL);
   
   CString strSQL = _T("");
   strSQL.Format(_T("select convert(decimal(18,2),isnull(%s+dbo.getYS(%s)-dbo.getSS(%s),0)) as JE from %s where %s='%s';") \
      ,DBCustomer_key_Arrears,DBCustomer_key_Code,DBCustomer_key_Code,DB_TABLE_CUSTOM,DBCustomer_key_Code,cusCode);
   pADOConn->GetRecordSet(strSQL);

   CString strQK = _T("0");
   while (!pADOConn->adoEOF())
   {
      strQK = pADOConn->GetValueString(_T("JE"));
      pADOConn->MoveNext();
   }
   return strQK;
}

//��ȡ��ǰǷ��Ӧ�̵Ľ�� yangjr 2018/1/9
CString CDBCustomInfoList::GetQianGongYingShangKuanJinEr(CADOConn *pADOConn,CString cusCode)
{
   ASSERT(pADOConn != NULL);

   CString strSQL = _T("");
   strSQL.Format(_T("select convert(decimal(18,2),isnull(%s+dbo.getYF(%s)-dbo.getSF(%s),0)) as JE from %s where %s='%s';") \
      ,DBCustomer_key_Arrears,DBCustomer_key_Code,DBCustomer_key_Code,DB_TABLE_CUSTOM,DBCustomer_key_Code,cusCode);
   pADOConn->GetRecordSet(strSQL);

   CString strQK = _T("0");
   while (!pADOConn->adoEOF())
   {
      strQK = pADOConn->GetValueString(_T("JE"));
      pADOConn->MoveNext();
   }
   return strQK;
}

//sqr��ʽ ��ȡ��ǰ�ͻ����ۻ�Ƿ���� yangjr 2018-4-9
CString CDBCustomInfoList::GetNewQianKuanJinEr(CADOConn *pADOConn,CString cusCode)
{
   ASSERT(pADOConn != NULL);

   CString strSQL = _T("");
   strSQL.Format(_T("select convert(decimal(18,2),isnull(dbo.getLastYuE('%s'),0)) as JE;"),cusCode);
   pADOConn->GetRecordSet(strSQL);

   CString strQK = _T("0");
   if (!pADOConn->adoEOF())
   {
      strQK = pADOConn->GetValueDoubleStr(_T("JE"),2);     
   }
   return strQK;
}

CString CDBCustomInfoList::GetCusQKLimit(CADOConn *pADOConn,CString cusCode)
{
	ASSERT(pADOConn != NULL);

	CString strLimit = _T("0.00");
	CString strSQL = _T("");
	strSQL.Format(_T("select %s from %s where %s = '%s'"),DBCustomer_key_Limit,DB_TABLE_CUSTOM,DBCustomer_key_Code,cusCode);
	pADOConn->GetRecordSet(strSQL);
	if (!pADOConn->adoEOF())
	{
		strLimit = pADOConn->GetValueDoubleStr(DBCustomer_key_Limit,2);
	}
	return strLimit;
}

CString CDBCustomInfoList::GetNewCusCode(CADOConn* pADOConn)
{
	ASSERT(pADOConn != NULL);
	CString strSQL = _T("");
	strSQL.Format(_T("select top 1 cCusCode from Customer order by ID desc;"));
	pADOConn->GetRecordSet(strSQL);
	CString strCusCode = _T("");
	if (!pADOConn->adoEOF())
	{
		strCusCode = pADOConn->GetValueString(_T("cCusCode"));
	}
	if (!strCusCode.IsEmpty())
	{
		char s_ch[50],s_num[50];
		int iLen = strCusCode.GetLength();
		int iNum =0,iCh = 0;
		for (int i =0; i< iLen; ++i)
		{
			if (strCusCode[i] >= '0' && strCusCode[i] <= '9')
			{
				s_num[iNum++] = strCusCode[i];
			}
			else
			{
				s_ch[iCh++] = strCusCode[i];
			}
		}
		s_num[iNum++] = '\0';
		s_ch[iCh++] = '\0';
		CString strNum ; strNum = s_num;
		CString strCh; strCh = s_ch;
		CString strTemp;
		strTemp.Format(FORMAT_INT,_ttoi(strNum)+1);
		strCusCode = strCh + strTemp;
		return strCusCode;
	}
	else
	{
		return _T("");
	}
}

BOOL CDBCustomInfoList::GetKeHuDuiZhang(CADOConn* pADOConn,CString strBegTime,CString strEndTime,MAP_GridCtrl_AllData& map_all_data)
{
   map_all_data.clear();
   ASSERT(pADOConn != NULL);

   CString strSql = _T("");
   //strSql.Format(_T("select T.*,(T.�ڳ���� - T.���� + T.����) as ��� from \
   //   (select a.cCusCode as �ͻ�����,a.cCusName as �ͻ�����,a.cCusPerson as ��ϵ��,a.cCusMobile as ��ϵ��ʽ,a.cCusAddress as ��ַ,a.iMoney as �ڳ����,isnull(c.����,0) as ����,isnull(b.����,0)as ����,\
   //   a.iShangxian as Ԥ����� from Customer as a\
   //   left join\
   //   (select cCusCode,sum(fFahuoJE) as ���� from FahuoRecord where cShenheState = '�����' and fFahuoJE > 0 group by cCusCode) as b\
   //   on a.cCusCode = b.cCusCode\
   //   left join\
   //   (select cCusCode,0-sum(fFahuoJE) as ���� from FahuoRecord where cShenheState = '�����' and fFahuoJE < 0 group by cCusCode) as c\
   //   on a.cCusCode = c.cCusCode\
   //   ) as T"));

   //�����������������·������˻���
   strSql.Format(_T("select T.*,(T.������������+T.���·�������-abs(T.�˻����)) as ���۽��,(T.�ڳ���� - T.���� + T.����) as ��� from \
      (select a.cCusCode as �ͻ�����,a.cCusName as �ͻ�����,a.cCusPerson as ��ϵ��,a.cCusMobile as ��ϵ��ʽ,a.cCusAddress as ��ַ,\
      a.iMoney as �ڳ����,isnull(c.����,0) as ����,isnull(b.����,0)as ����,a.iShangxian as Ԥ�����,\
      isnull(d.�����������,0) as �����������,isnull(d.������������,0) as ������������,isnull(e.���·������,0) as ���·������,isnull(e.���·�������,0) as ���·�������,\
      isnull(g.�˻����,0) as �˻���� from Customer as a\
   left join\
      (select cCusCode,sum(fFahuoJE) as ���� from FahuoRecord where cShenheState = '�����' and fFahuoJE > 0 and cFahuoDate between '%s' and '%s' group by cCusCode) as b on a.cCusCode = b.cCusCode\
      left join\
      (select cCusCode,0-sum(fFahuoJE) as ���� from FahuoRecord where cShenheState = '�����' and fFahuoJE < 0 and cFahuoDate between '%s' and '%s' group by cCusCode) as c on a.cCusCode = c.cCusCode\
   left join\
      (select T1.cCusCode,sum(T2.fJE) as �����������,sum(case isnull(T2.isCheckFanLi,0) when 0 then T2.fJE else  0 end) as ������������ from FahuoRecord as T1 \
      left join FahuoRecords as T2 on T1.cFahuoCode = T2.cFahuoCode\
      left join Customer as T3 on T1.cCusCode = T3.cCusCode\
      where T1.cShenheState = '�����' and cDataType ='��������' and T1.cFahuoDate between '%s' and '%s' group by T1.cCusCode) as d on a.cCusCode = d.cCusCode \
   left join\
      (select T1.cCusCode,sum(T2.fJE) as ���·������,sum(case isnull(T2.isCheckFanLi,0) when 0 then T2.fJE else  0 end) as ���·������� from FahuoRecord as T1 \
      left join FahuoRecords as T2 on T1.cFahuoCode = T2.cFahuoCode\
      left join Customer as T3 on T1.cCusCode = T3.cCusCode\
      where T1.cShenheState = '�����' and cDataType ='���·���' and T1.cFahuoDate between '%s' and '%s' group by T1.cCusCode )as e on a.cCusCode = e.cCusCode \
   left join\
      (select T1.cCusCode,sum(T2.fJE) as �˻���� from FahuoRecord as T1 \
      left join FahuoRecords as T2 on T1.cFahuoCode = T2.cFahuoCode\
      left join Customer as T3 on T1.cCusCode = T3.cCusCode\
      where T1.cShenheState = '�����' and cDataType ='�˻�����' and T1.cFahuoDate between '%s' and '%s' group by T1.cCusCode) as g on  a.cCusCode = g.cCusCode \
   ) as T"),strBegTime,strEndTime,strBegTime,strEndTime,strBegTime,strEndTime,strBegTime,strEndTime,strBegTime,strEndTime);

   pADOConn->GetRecordSet(strSql);
   while(!pADOConn->adoEOF())
   {
      MAP_GridCtrl_RowData row_data;
      InsertRowData(_T("�ͻ�����"),pADOConn->GetValueString(_T("�ͻ�����")),row_data);
      InsertRowData(_T("�ͻ�����"),pADOConn->GetValueString(_T("�ͻ�����")),row_data);
      InsertRowData(_T("��ϵ��ʽ"),pADOConn->GetValueString(_T("��ϵ��ʽ")),row_data);
      InsertRowData(_T("��ַ"),    pADOConn->GetValueString(_T("��ַ")),    row_data);
      InsertRowData(_T("��ϵ��"),pADOConn->GetValueString(_T("��ϵ��")),row_data);
      InsertRowData(_T("�ڳ����"),pADOConn->GetValueString(_T("�ڳ����")),row_data,CB_enum_FieldData_Double2Point);
      InsertRowData(_T("����"),    pADOConn->GetValueString(_T("����")),    row_data,CB_enum_FieldData_Double2Point);
      InsertRowData(_T("����"),    pADOConn->GetValueString(_T("����")),    row_data,CB_enum_FieldData_Double2Point);
      InsertRowData(_T("���"),    pADOConn->GetValueString(_T("���")),    row_data,CB_enum_FieldData_Double2Point);
      InsertRowData(_T("Ԥ�����"),pADOConn->GetValueString(_T("Ԥ�����")),row_data,CB_enum_FieldData_Double2Point);
      InsertRowData(_T("�����������"),pADOConn->GetValueString(_T("�����������")),row_data,CB_enum_FieldData_Double2Point);
      InsertRowData(_T("���·������"),pADOConn->GetValueString(_T("���·������")),row_data,CB_enum_FieldData_Double2Point);
      InsertRowData(_T("�˻����"),pADOConn->GetValueString(_T("�˻����")),row_data,CB_enum_FieldData_Double2Point);
      InsertRowData(_T("���۽��"),pADOConn->GetValueString(_T("���۽��")),row_data,CB_enum_FieldData_Double2Point);

      map_all_data.insert(make_pair(map_all_data.size(),row_data));
      pADOConn->MoveNext();
   }
   return TRUE;
}

BOOL CDBCustomInfoList::GetCusPrintFlag(CADOConn* pADOConn,CString strCusCode,__out int& iPrintDp,__out int& iPrintYE)
{
   ASSERT(pADOConn != NULL);
   CString strSql = _T("");
   strSql.Format(_T("select top 1 %s,%s from %s where %s = '%s'"),
      DBCustomer_key_bPrintDiaoPai,DBCustomer_key_bPrintYuE,DB_TABLE_CUSTOM,
      DBCustomer_key_Code,strCusCode);
   pADOConn->GetRecordSet(strSql);
   if (!pADOConn->adoEOF())
   {
      iPrintDp = pADOConn->GetValueInt(DBCustomer_key_bPrintDiaoPai);
      iPrintYE = pADOConn->GetValueInt(DBCustomer_key_bPrintYuE);
   }
   return TRUE;
}    
#endif // USING_GRIDCTRL_MARK
//�ж϶�Ӧ������Ա�Ƿ��пͻ� Yangjr 2018-9-1
BOOL CDBCustomInfoList::IsSalesHaveCus(CADOConn *pADOConn,CString strSalesID)
{
   ASSERT(pADOConn != NULL);
   CString strLimit = _T("0.00");
   CString strSQL = _T("");
   strSQL.Format(_T("select count(*) as num from %s where %s = '%s'"),DB_TABLE_CUSTOM,DBCustomer_key_cSalesID,strSalesID);
   pADOConn->GetRecordSet(strSQL);
   if (!pADOConn->adoEOF())
   {
      int num = pADOConn->GetValueInt(_T("num"));
      if (num>0)
      {
         return TRUE;
      }
   }
   return FALSE;
}
void CDBCustomInfoList::GetAllDBInfoCusName_BasicInfo(vector<CString> &vecCusName)// ��ȡ���еĿͻ����ƣ��ͻ�ר�� liuhw 2019/05/21
{
   vecCusName.clear();
   for (int i = 0;i < GetCount();++i)
   {
      CDBCustomInfoData *pData = GetItem(i);
      if (pData != NULL)
      {
         vecCusName.push_back(pData->m_strCusName);
      }
   }
}

                


CString my_customer_info::GetUpdateSql(BOOL bIgnoreNull /*= TRUE*/)
{
   if (m_strCusCode.IsEmpty())
   {
      return _T("");
   }
   CString strSql = _T("");
   CString strText;

   if (!m_strCate.IsEmpty() || !bIgnoreNull)
   {
      strText.Format(_T("%s = '%s',"),DBCustomer_key_Cate,m_strCate);
      strSql += strText;
   }

   if (!m_strCusCate.IsEmpty() || !bIgnoreNull)
   {
      strText.Format(_T("%s = '%s',"),DBCustomer_key_CusCate,m_strCusCate);
      strSql += strText;
   }

   if (!m_strCusName.IsEmpty() || !bIgnoreNull)
   {
      strText.Format(_T("%s = '%s',"),DBCustomer_key_Name,m_strCusName);
      strSql += strText;
   }

   if (!m_strCusAddr.IsEmpty() || !bIgnoreNull)
   {
      strText.Format(_T("%s = '%s',"),DBCustomer_key_Addr,m_strCusAddr);
      strSql += strText;
   }

   if (!m_strCusPerson.IsEmpty() || !bIgnoreNull)
   {
      strText.Format(_T("%s = '%s',"),DBCustomer_key_Person,m_strCusPerson);
      strSql += strText;
   }

   if (!m_strCusPhone.IsEmpty() || !bIgnoreNull)
   {
      strText.Format(_T("%s = '%s',"),DBCustomer_key_Phone,m_strCusPhone);
      strSql += strText;
   }

   if (!m_strCusFax.IsEmpty() || !bIgnoreNull)
   {
      strText.Format(_T("%s = '%s',"),DBCustomer_key_Fax,m_strCusFax);
      strSql += strText;
   }

   if (!m_strMobile.IsEmpty() || !bIgnoreNull)
   {
      strText.Format(_T("%s = '%s',"),DBCustomer_key_Mobile,m_strMobile);
      strSql += strText;
   }

   if (!m_strCusCate.IsEmpty() || !bIgnoreNull)
   {
      strText.Format(_T("%s = '%s',"),DBCustomer_key_Remark,m_strRemark);
      strSql += strText;
   }

   if (!m_strVenWeb.IsEmpty() || !bIgnoreNull)
   {
      strText.Format(_T("%s = '%s',"),DBCustomer_key_VenWeb,m_strVenWeb);
      strSql += strText;
   }

   if (!m_strCusPwd.IsEmpty() || !bIgnoreNull)
   {
      strText.Format(_T("%s = '%s',"),DBCustomer_key_Pwd,m_strCusPwd);
      strSql += strText;
   }

   if (!m_fArrears.IsEmpty() || !bIgnoreNull)
   {
      strText.Format(_T("%s = '%.2f',"),DBCustomer_key_Arrears,_ttof(m_fArrears));
      strSql += strText;
   }

   if (m_fDeposit>= 0 || !bIgnoreNull)
   {
      strText.Format(_T("%s = '%.2f',"),DBCustomer_key_Deposit,m_fDeposit);
      strSql += strText;
   }

   if (m_fLimit>= 0 || !bIgnoreNull)
   {
      strText.Format(_T("%s = '%.2f',"),DBCustomer_key_Limit,m_fLimit);
      strSql += strText;
   }
   if(!m_strCusAbbrevName.IsEmpty() || !bIgnoreNull)
   {
      strText.Format(_T("%s = '%s',"),DBCustomer_key_Abbrev,m_strCusAbbrevName);
      strSql += strText;
   }
   if (!m_strProvince.IsEmpty() || !bIgnoreNull)
   {
      strText.Format(_T("%s = '%s',"),DBCustomer_key_Province,m_strProvince);
      strSql += strText;
   }

   if (!m_strCity.IsEmpty() || !bIgnoreNull)
   {
      strText.Format(_T("%s = '%s',"),DBCustomer_key_City,m_strCity);
      strSql += strText;
   }

   if (m_nDeliveryDays >=0 || !bIgnoreNull)
   {
      strText.Format(_T("%s = '%d',"),DBCustomer_key_DeliveDays,m_nDeliveryDays);
      strSql += strText;
   }

   if (!m_strEMS.IsEmpty() || !bIgnoreNull)
   {
      strText.Format(_T("%s = '%s',"),DBCustomer_key_EMS,m_strEMS);
      strSql += strText;
   }

   if (!m_strClerkCode.IsEmpty() || !bIgnoreNull)
   {
      strText.Format(_T("%s = '%s',"),DBCustomer_key_ClerkCode,m_strClerkCode);
      strSql += strText;
   }

   if (m_nCusLv>=0 || !bIgnoreNull)
   {
      strText.Format(_T("%s = '%d',"),DBCustomer_key_LV,m_nCusLv);
      strSql += strText;
   }

   if (m_iTreeGroupID>=0|| !bIgnoreNull)
   {
      strText.Format(_T("%s = '%d',"),DBCustomer_key_iTreeGroupID,m_iTreeGroupID);
      strSql += strText;
   }

   if (m_iJijiaType>=0|| !bIgnoreNull)
   {
      strText.Format(_T("%s = '%d',"),DBCustomer_key_iJijiaType,m_iJijiaType);
      strSql += strText;
   }
   if (m_fAddinPrice>=0|| !bIgnoreNull)
   {
      strText.Format(_T("%s = '%.2f',"),DBCustomer_key_fAddinPrice,m_fAddinPrice);
      strSql += strText;
   }
   if (m_bPrintDiaoPai>=0|| !bIgnoreNull)
   {
      strText.Format(_T("%s = '%d',"),DBCustomer_key_bPrintDiaoPai,m_bPrintDiaoPai);
      strSql += strText;
   }
   if (m_bPrintYuE>=0|| !bIgnoreNull)
   {
      strText.Format(_T("%s = '%d',"),DBCustomer_key_bPrintYuE,m_bPrintYuE);
      strSql += strText;
   }
   if (m_fZMZheKou>=0|| !bIgnoreNull)
   {
      strText.Format(_T("%s = '%.2f',"),DBCustomer_key_fZMZheKou,m_fZMZheKou);
      strSql += strText;
   }
   if (!m_strSalesID.IsEmpty() || !bIgnoreNull)
   {
      strText.Format(_T("%s = '%s',"),DBCustomer_key_cSalesID,m_strSalesID);
      strSql += strText;
   }
   //����ʱ��
   CString strGetDateStr = DBS_GETDATESTR;
   strText.Format(_T("%s = %s,"),DBCustomer_key_UpdateTime,strGetDateStr);
   strSql += strText;

   if (!strSql.IsEmpty())
   {
      strSql = strSql.Left(strSql.GetLength() - 1);// ȡ�����һ��,
      CString strRetSql;  
      strRetSql.Format(_T("update %s set %s where %s = '%s'"),DB_TABLE_CUSTOM,strSql,DBCustomer_key_Code,m_strCusCode);
      return strRetSql;
   }
   return _T("");
};

CString my_customer_info::GetInsertSql()
{
   CString strFormat = _T(""),strValue = _T(""),strSQL = _T("");
   strFormat.Format(_T("%s,%s,%s,%s,%s,%s, %s,%s,%s,%s,%s, %s,%s,%s,%s,%s, %s,%s,%s,%s,%s, %s,%s,%s,%s,%s, %s,%s,%s,%s"),
      DBCustomer_key_Cate,			
      DBCustomer_key_CusCate,		
      DBCustomer_key_Code,
      DBCustomer_key_Name,
      DBCustomer_key_Addr,
      DBCustomer_key_Abbrev,

      DBCustomer_key_Person,
      DBCustomer_key_Phone,
      DBCustomer_key_Fax,
      DBCustomer_key_Mobile,
      DBCustomer_key_Remark,

      DBCustomer_key_VenWeb,
      DBCustomer_key_Pwd,
      DBCustomer_key_Province	,
      DBCustomer_key_City,
      DBCustomer_key_EMS,

      DBCustomer_key_ClerkCode,	
      DBCustomer_key_cSalesID,
      DBCustomer_key_UpdateTime,
      DBCustomer_key_LV,
      DBCustomer_key_iTreeGroupID,

      DBCustomer_key_iJijiaType,
      DBCustomer_key_DeliveDays,
      DBCustomer_key_bPrintDiaoPai,
      DBCustomer_key_bPrintYuE,
      DBCustomer_key_Limit,

      DBCustomer_key_Arrears,
      DBCustomer_key_fAddinPrice,
      DBCustomer_key_fZMZheKou,
      DBCustomer_key_Deposit);

   if (m_nDeliveryDays == -1)
   {
      m_nDeliveryDays = 15;
   }
   if (m_nCusLv == -1)
   {
      m_nCusLv = 1;
   }
   if (m_iTreeGroupID == -1)
   {
      m_iTreeGroupID = 1;
   }
   if (m_iJijiaType == -1)
   {
      m_iJijiaType = 1;
   }
   if (m_bPrintDiaoPai == -1)
   {
      m_bPrintDiaoPai = 0;
   }
   if (m_bPrintYuE == -1)
   {
      m_bPrintYuE = 0;
   }  
   if (m_fZMZheKou == -1)
   {
      m_fZMZheKou = 1;
   }
   if (m_fAddinPrice == -1)
   {
      m_fAddinPrice = 0;
   }
   if (m_fDeposit == -1)
   {
      m_fDeposit = 0;
   }
   if (m_fLimit == -1)
   {
      m_fLimit = 0;
   }
   strValue.Format(_T("'%s','%s','%s','%s','%s','%s',\
                      '%s','%s','%s','%s','%s',\
                      '%s','%s','%s','%s','%s',\
                      '%s','%s',%s,'%d','%d',\
                      '%d','%d','%d','%d','%.2f',\
                      '%.2f','%.2f','%.2f','%.2f'"),
                      m_strCate,m_strCusCate,m_strCusCode,m_strCusName,m_strCusAddr,m_strCusAbbrevName,
                      m_strCusPerson,m_strCusPhone,m_strCusFax,m_strMobile,m_strRemark,
                      m_strVenWeb,m_strCusPwd,m_strProvince,m_strCity,m_strEMS,
                      m_strClerkCode,m_strSalesID,DBS_GETDATESTR,m_nCusLv,m_iTreeGroupID,m_iJijiaType,
                      m_nDeliveryDays,m_bPrintDiaoPai,m_bPrintYuE,m_fLimit,_ttof(m_fArrears),
                      m_fAddinPrice,m_fZMZheKou,m_fDeposit);

   strSQL.Format(_T("insert into %s(%s) values(%s)"),DB_TABLE_CUSTOM,strFormat,strValue);
   return strSQL;
};

