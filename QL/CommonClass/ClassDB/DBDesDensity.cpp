#include "StdAfx.h"
#include "DBDesDensity.h"
#include "DBKeyDef.h"
#include "ADOConn/DBImage.h"


IMPLEMENT_SERIAL(CDBFaceCode,  CDataMid, 1)
std::shared_ptr<CDBFaceCode> CDBFaceCode::sm_inst;

CDBFaceCode::CDBFaceCode()
{
	ResetData();
}

CDBFaceCode::~CDBFaceCode()
{

}

void CDBFaceCode::ResetData()
{
	m_nID = -1;			//����ID
	m_strName = _T("");	//���� eg:������
	m_sOldLen = _T("");		//
	m_strType = _T("");	//���� eg:֧��
	m_sLen = _T("");			//����
	m_strUnit = _T("");	//��λ eg:����

	m_nIDDensity = -1;	//�ܶȹ����ֶ�����ID
}

BOOL CDBFaceCode::GetAllDBInfo(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);

	BOOL bRet = TRUE;

	if (NULL == pADOConn)
	{
		bRet = FALSE;
	}
	else
	{
		m_nID = pADOConn->GetValueInt64(DBDesFaceCode_key_ID);				//����ID
		m_strName = pADOConn->GetValueString(DBDesFaceCode_key_NAME);		//���� eg:������
		m_sOldLen = pADOConn->GetValueString(DBDesFaceCode_key_LENOLD);		//
		m_strType = pADOConn->GetValueString(DBDesFaceCode_key_TYPE);		//���� eg:֧��
		m_sLen = pADOConn->GetValueString(DBDesFaceCode_key_LEN);			//����
		m_strUnit = pADOConn->GetValueString(DBDesFaceCode_key_UNIT);		//��λ eg:����

		m_nIDDensity = pADOConn->GetValueInt64(DBDesFaceCode_key_IDDENSITY);	//�ܶȹ����ֶ�����ID

		bRet = TRUE;
	}

	return bRet;
}

void CDBFaceCode::Copy(CDBFaceCode *pData)
{
	m_nID = pData->m_nID;			//����ID
	m_strName = pData->m_strName;	//���� eg:������
	m_sOldLen = pData->m_sOldLen;	//
	m_strType = pData->m_strType;	//���� eg:֧��
	m_sLen = pData->m_sLen;			//����
	m_strUnit = pData->m_strUnit;	//��λ eg:����

	m_nIDDensity = pData->m_nIDDensity;	//�ܶȹ����ֶ�����ID
}

CString CDBFaceCode::GetSQLFormat()
{
	CString strRet = _T("");
	//
	strRet.Format(_T("%s,%s,%s,%s,%s,%s"),
		DBDesFaceCode_key_NAME			,
		DBDesFaceCode_key_LENOLD		,
		DBDesFaceCode_key_TYPE			,
		DBDesFaceCode_key_LEN			,
		DBDesFaceCode_key_UNIT			,
		DBDesFaceCode_key_IDDENSITY		
		);

	return strRet;
}

CString CDBFaceCode::GetValueFormat(const CString & strName, const CString & strOldLen, const CString & strType, const CString & strLen, const CString & strUnit, const __int64 nIDDensity)
{
   CString strRet = _T("");
   strRet.Format(_T("('%s','%s','%s','%s','%s','%lld')"),
      strName, strOldLen,  strType,strLen, strUnit, nIDDensity);
   return strRet;
}

CDBFaceCode * CDBFaceCode::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = shared_ptr<CDBFaceCode>(new CDBFaceCode);

	return sm_inst.get();
}

//CDBFaceCodeList
IMPLEMENT_SERIAL(CDBFaceCodeList,  CDataListMid, 1)
std::shared_ptr<CDBFaceCodeList> CDBFaceCodeList::sm_inst;
CDBFaceCodeList::CDBFaceCodeList()
{

}
CDBFaceCodeList::~CDBFaceCodeList()
{

}
CDBFaceCode*  CDBFaceCodeList::GetItem(int nIndex)
{
	if (nIndex<0||nIndex>=GetCount())
		return NULL;

	return (CDBFaceCode*)GetAt(FindIndex(nIndex));
}
void CDBFaceCodeList::AddItem(CDBFaceCode* pItem)
{
	CDBFaceCode*pData = new CDBFaceCode;
	pData->Copy(pItem);
	AddTail(pData);
}
void CDBFaceCodeList::DeleteItem(int nIndex)
{
	if (nIndex<0||nIndex>GetCount())
		return;

	CDBFaceCode *pObject = (CDBFaceCode*)GetItem(nIndex);
	delete pObject;
	pObject = NULL;

	RemoveAt(FindIndex(nIndex));
}

CDBFaceCodeList* CDBFaceCodeList:: Instance()		//��ȡ��ָ�룩ʵ��
{
	if(sm_inst.get() == 0)
		sm_inst = shared_ptr<CDBFaceCodeList>(new CDBFaceCodeList);

	return sm_inst.get();
}

/////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CDBDensity,  CDataMid, 1)
std::shared_ptr<CDBDensity> CDBDensity::sm_inst;

CDBDensity::CDBDensity()
{
#if Des_IMAGE
   m_pFlowerPatternPic = NULL;
#endif // Des_IMAGE
	ResetData();
}

CDBDensity::~CDBDensity()
{
#if Des_IMAGE
   ClearColorImage();
#endif // Des_IMAGE
}

void CDBDensity::ResetData()
{
	m_nID = -1;				//����ID
	m_strName = _T("");		//����
	m_fHorDesSrc = 0;		//����
	m_fVerDesSrc = 0;		//ֱ��
	m_fHorDesNew = 0;		//����
	m_fVerDesNew = 0;		//ֱ��
	m_strStructure = _T("");//�����ṹ
	m_strMaterial = _T("");	//ë��

	m_fPull = 0;			//����
	m_strPullUnit = _T("");	//��λ
	m_nPullType = 0;		//eg:ȫ���� or ������
	m_strNeedle = _T("");	//����

	//СƬ����
	m_fPieceUnit = 0;		//��
	m_fPieceTurns = 0;		//ת
	m_fPieceNeedle = 0;		//��

	//��ͷ��ת
	m_fStartTurns = 0;

	//��������
	m_strRomanType = _T("");

	//��˿ת��
	m_strWire = _T("");		//��˿
	m_fWireTurns = 0;		//ת
	m_nWireType = 0;		//�Ƿ�ȫ��˿


	//����
	m_bShowPZ = FALSE;
	m_strPZName = _T("");//��������
	m_strPinBottom = _T("");//��
	m_strPinFace = _T("");	//��
	m_nPinType = 0;			//��������

	m_strType = _T("");		//�ܶ�����
	m_strBaseType = _T("");	

   m_strSavedUserID = _T("");
   m_strSaveTime    = _T("");
   m_strRemark      = _T("");
   m_strOrderNo     = _T("");

   m_strPieceName   = _T("");
   m_strMatName     = _T("");

   m_strSavedUserName = _T("");
#if Des_IMAGE
   ClearColorImage();
#endif // Des_IMAGE
}

BOOL CDBDensity::UpdateDBInfo(CADOConn *pADOConn)
{
   pADOConn->GetValueString(DBDesDensity_key_Name)= m_strName;			//����
   return TRUE;
}

BOOL CDBDensity::GetAllDBInfo(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);

	BOOL bRet = TRUE;

	if (NULL == pADOConn)
	{
		bRet = FALSE;
	}
	else
	{
		m_nID			= pADOConn->GetValueInt(DBDesDensity_key_ID);						//����ID
		m_strName		= pADOConn->GetValueString(DBDesDensity_key_Name);			//����
		m_fHorDesSrc	= pADOConn->GetValueDouble(DBDesDensity_key_HorDesSrc);		//����
		m_fVerDesSrc	= pADOConn->GetValueDouble(DBDesDensity_key_VerDesSrc);		//ֱ��
		m_fHorDesNew	= pADOConn->GetValueDouble(DBDesDensity_key_HorDesNew);		//����
		m_fVerDesNew	= pADOConn->GetValueDouble(DBDesDensity_key_VerDesNew);		//ֱ��
		m_strStructure	= pADOConn->GetValueString(DBDesDensity_key_Structure);	//�����ṹ
		m_strMaterial	= pADOConn->GetValueString(DBDesDensity_key_Material);	//ë��

		m_fPull			= pADOConn->GetValueDouble(DBDesDensity_key_Pull);				//����
		m_strPullUnit	= pADOConn->GetValueString(DBDesDensity_key_PullUnit);	//��λ
		m_nPullType		= pADOConn->GetValueInt(DBDesDensity_key_PullType);			//eg:ȫ���� or ������
		m_strNeedle		= pADOConn->GetValueString(DBDesDensity_key_Needle);		//����

		//СƬ����
		m_fPieceUnit	= pADOConn->GetValueDouble(DBDesDensity_key_PieceUnit);		//��
		m_fPieceTurns	= pADOConn->GetValueDouble(DBDesDensity_key_PieceTurns);	//ת
		m_fPieceNeedle	= pADOConn->GetValueDouble(DBDesDensity_key_PieceNeedle);	//��

		//��ͷ��ת
		m_fStartTurns	= pADOConn->GetValueDouble(DBDesDensity_key_StartTurns);

		//��������
		m_strRomanType	= pADOConn->GetValueString(DBDesDensity_key_RomanType);

		//��˿ת��
		m_strWire		= pADOConn->GetValueString(DBDesDensity_key_Wire);			//��˿
		m_fWireTurns	= pADOConn->GetValueDouble(DBDesDensity_key_WireTurns);		//ת
		m_nWireType		= pADOConn->GetValueInt(DBDesDensity_key_WireType);			//�Ƿ�ȫ��˿

		//����
		m_bShowPZ		= pADOConn->GetValueInt(DBDesDensity_key_ShowPZ);
		m_strPZName		= pADOConn->GetValueString(DBDesDensity_key_PZName);
		m_strPinBottom	= pADOConn->GetValueString(DBDesDensity_key_PinBottom);	//��
		m_strPinFace	= pADOConn->GetValueString(DBDesDensity_key_PinFace);		//��
		m_nPinType		= pADOConn->GetValueInt(DBDesDensity_key_PinType);			//��������

		m_strType		= pADOConn->GetValueString(DBDesDensity_key_Type);			//�ܶ�����
		m_strBaseType	= pADOConn->GetValueString(DBDesDensity_key_BaseType);	

      m_strSavedUserID= pADOConn->GetValueString(DBDesDensity_key_cSavedUserID);
      m_strSaveTime   = pADOConn->GetValueString(DBDesDensity_key_cSaveTime   );
      m_strRemark     = pADOConn->GetValueString(DBDesDensity_key_cRemark     );
      m_strOrderNo    = pADOConn->GetValueString(DBDesDensity_key_cOrderNo    );

      m_strPieceName  = pADOConn->GetValueString(DBDesDensity_key_cPieceName);
      m_strMatName    = pADOConn->GetValueString(DBDesDensity_key_cMatName  );
#if Des_IMAGE
      ClearColorImage();
      CDBImage oImage;
      m_pFlowerPatternPic = oImage.NewImageFromDB(DBDesDensity_key_cFlowerPatternPic, pADOConn->GetRecoPtr());
#endif 
   }


	return bRet;
}

void CDBDensity::Copy(CDBDensity *pData)
{
	m_nID              = pData->m_nID;					//����ID
	m_strName          = pData->m_strName;			   //����
	m_fHorDesSrc       = pData->m_fHorDesSrc;		   //����
	m_fVerDesSrc       = pData->m_fVerDesSrc;		   //ֱ��
	m_fHorDesNew       = pData->m_fHorDesNew;		   //����
	m_fVerDesNew       = pData->m_fVerDesNew;		   //ֱ��
	m_strStructure     = pData->m_strStructure;	   //�����ṹ
	m_strMaterial      = pData->m_strMaterial;	   //ë��

	m_fPull            = pData->m_fPull;				//����
	m_strPullUnit      = pData->m_strPullUnit;	   //��λ
	m_nPullType        = pData->m_nPullType;		   //eg:ȫ���� or ������
	m_strNeedle        = pData->m_strNeedle;		   //����

	                                                //СƬ����
	m_fPieceUnit       = pData->m_fPieceUnit;		   //��
	m_fPieceTurns      = pData->m_fPieceTurns;	   //ת
	m_fPieceNeedle     = pData->m_fPieceNeedle;	   //��

	                                                //��ͷ��ת
	m_fStartTurns      = pData->m_fStartTurns;

	                                                //��������
	m_strRomanType     = pData->m_strRomanType;

	                                                //��˿ת��
	m_strWire          = pData->m_strWire;			   //��˿
	m_fWireTurns       = pData->m_fWireTurns;		   //ת
	m_nWireType        = pData->m_nWireType;		   //�Ƿ�ȫ��˿

	                                                //����
	m_bShowPZ          = pData->m_bShowPZ;
	m_strPZName        = pData->m_strPZName;
	m_strPinBottom     = pData->m_strPinBottom;     //��
	m_strPinFace       = pData->m_strPinFace;		   //��
	m_nPinType         = pData->m_nPinType;			//��������

	m_strType          = pData->m_strType;			   //�ܶ�����
	m_strBaseType      = pData->m_strBaseType;	

   m_strSavedUserID   = pData->m_strSavedUserID;
   m_strSaveTime      = pData->m_strSaveTime   ;
   m_strRemark        = pData->m_strRemark     ;
   m_strOrderNo       = pData->m_strOrderNo    ;

   m_strPieceName     = pData->m_strPieceName  ;
   m_strMatName       = pData->m_strMatName    ;

   m_strSavedUserName = pData->m_strSavedUserName;
   m_faceData.Copy(&pData->m_faceData);
#if Des_IMAGE
   ClearColorImage();
   if (pData->m_pFlowerPatternPic)
   {
      m_pFlowerPatternPic = pData->m_pFlowerPatternPic->Clone();
   }
#endif
}

CString CDBDensity::GetInsertSQL()
{
	CString strRet = _T(""),strFormat = _T(""),strValue = _T("");

   //                   1  2  3  4  5  6  7  8  9  10
   strFormat.Format(_T("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,\
                        %s,%s,%s,%s,%s,%s,%s,%s,%s,%s,\
                        %s,%s,%s,%s,%s,%s,%s,%s,%s,%s,\
                        %s,%s"),
						DBDesDensity_key_Name		,//1
						DBDesDensity_key_HorDesSrc	,//2
						DBDesDensity_key_VerDesSrc	,//3
						DBDesDensity_key_HorDesNew	,//4
						DBDesDensity_key_VerDesNew	,//5
						DBDesDensity_key_Structure	,//6
						DBDesDensity_key_Material	,//7
						DBDesDensity_key_Pull		,//8
						DBDesDensity_key_PullUnit	,//9
						DBDesDensity_key_PullType	,//10
						DBDesDensity_key_Needle		,//11
						DBDesDensity_key_PieceUnit	,//12
						DBDesDensity_key_PieceTurns	,//13
						DBDesDensity_key_PieceNeedle,//14
						DBDesDensity_key_StartTurns	,//15
						DBDesDensity_key_RomanType	,//16
						DBDesDensity_key_Wire		,//17
						DBDesDensity_key_WireTurns	,//18
						DBDesDensity_key_WireType	,//19
						DBDesDensity_key_PinBottom	,//20
						DBDesDensity_key_PinFace	,//21
						DBDesDensity_key_PinType	,//22
						DBDesDensity_key_Type		,//23
						DBDesDensity_key_BaseType	,//24
						DBDesDensity_key_ShowPZ		,//25
						DBDesDensity_key_PZName		,//26
                  DBDesDensity_key_cSavedUserID,//27
                  DBDesDensity_key_cSaveTime   ,//28
                  DBDesDensity_key_cRemark     ,//29
                  DBDesDensity_key_cOrderNo    ,//30
                  DBDesDensity_key_cPieceName  ,//31
                  DBDesDensity_key_cMatName  
						);

   CString strSaveTime = _T("");
   if (m_strSaveTime.IsEmpty())
   {
      strSaveTime = DBS_GETDATESTR;
   }
   else 
   {
      strSaveTime.Format(_T("'%s'"),m_strSaveTime);
   }

	//                   1    2      3      4      5      6    7    8      9    10
   strValue.Format(_T("'%s','%.2f','%.2f','%.2f','%.2f','%s','%s','%.2f','%s','%d',\
                       '%s','%.2f','%.2f','%.2f','%.2f','%s','%s','%.2f','%d','%s',\
                       '%s','%d'  ,'%s'  ,'%s'  ,'%d'  ,'%s','%s', %s  ,'%s','%s',\
                       '%s','%s'"),
		m_strName		,//1
		m_fHorDesSrc	,//2  ffff
		m_fVerDesSrc	,//3  ffff
		m_fHorDesNew	,//4  ffff
		m_fVerDesNew	,//5  ffff
		m_strStructure	,//6
		m_strMaterial	,//7
		m_fPull			,//8  ffff
		m_strPullUnit	,//9
		m_nPullType		,//10 dddd
		m_strNeedle		,//11
		m_fPieceUnit	,//12 ffff
		m_fPieceTurns	,//13 ffff
		m_fPieceNeedle	,//14 ffff
		m_fStartTurns	,//15 ffff
		m_strRomanType	,//16
		m_strWire		,//17
		m_fWireTurns	,//18 ffff
		m_nWireType		,//19 dddd
		m_strPinBottom	,//20
		m_strPinFace	,//21
		m_nPinType		,//22 dddd
		m_strType		,//23
		m_strBaseType	,//24
		m_bShowPZ		,//25
		m_strPZName		,//26
      m_strSavedUserID,//27
      strSaveTime     ,//28
      m_strRemark     ,//29
      m_strOrderNo    ,//30
      m_strPieceName  ,//31
      m_strMatName     //32
		);

	strRet.Format(_T("insert into %s(%s) values(%s)"),DB_TABLE_DESDENSITY,strFormat,strValue);

	return strRet;
}

CDBDensity * CDBDensity::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = shared_ptr<CDBDensity>(new CDBDensity);

	return sm_inst.get();
}

void CDBDensity::SetFaceData(CDBFaceCode* data)
{
   if (data->m_nIDDensity == m_nID)
   {
      m_faceData.AddItem(data);
   }
}

BOOL CDBDensity::UpdateAllDBInfoByID(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);
   BOOL bRet = TRUE;
   CString strSQL = _T("");

   pADOConn->BeginTrans();

   strSQL.Format(_T("update %s set %s='%s',%s='%s',%s='%s',%s='%s',%s='%.2f',\
      %s='%.2f',%s='%.2f',%s='%.2f',%s='%2f',%s ='%.4f' ,%s ='%.2f' ,%s ='%.2f', \
      %s='%s',%s='%d',%s='%.2f',%s='%s',%s='%s',%s='%.2f',%s='%d',%s='%d',%s='%s',%s='%s',%s='%s',\
      %s='%d',%s='%s',%s='%s',%s='%s',%s='%s',%s = '%s',%s = '%s',%s = %s\
      where %s='%lld'"), DB_TABLE_DENSITY,
      DBDesDensity_key_Name, m_strName,
      DBDesDensity_key_Structure, m_strStructure,
      DBDesDensity_key_Material, m_strMaterial,
      DBDesDensity_key_Needle, m_strNeedle,
      DBDesDensity_key_HorDesSrc, m_fHorDesSrc,
      DBDesDensity_key_VerDesSrc, m_fVerDesSrc,
      DBDesDensity_key_HorDesNew, m_fHorDesNew,
      DBDesDensity_key_VerDesNew, m_fVerDesNew,
      DBDesDensity_key_Pull, m_fPull,
      DBDesDensity_key_PieceUnit, m_fPieceUnit,
      DBDesDensity_key_PieceTurns, m_fPieceTurns,
      DBDesDensity_key_PieceNeedle, m_fPieceNeedle,

      DBDesDensity_key_PullUnit, m_strPullUnit,
      DBDesDensity_key_PullType, m_nPullType,
      DBDesDensity_key_StartTurns, m_fStartTurns,
      DBDesDensity_key_RomanType, m_strRomanType,
      DBDesDensity_key_Wire, m_strWire,
      DBDesDensity_key_WireTurns, m_fWireTurns,
      DBDesDensity_key_WireType, m_nWireType,
      DBDesDensity_key_ShowPZ, m_bShowPZ,
      DBDesDensity_key_PZName, m_strPZName,
      DBDesDensity_key_PinBottom, m_strPinBottom,
      DBDesDensity_key_PinFace, m_strPinFace,
      DBDesDensity_key_PinType, m_nPinType,
      DBDesDensity_key_Type, m_strType,
      DBDesDensity_key_BaseType, m_strBaseType,
      DBDesDensity_key_cPieceName, m_strPieceName,
      DBDesDensity_key_cMatName, m_strMatName,
      DBDesDensity_key_cSavedUserID,m_strSavedUserID,
      DBDesDensity_key_cRemark,m_strRemark,
      DBDesDensity_key_cSaveTime,DBS_GETDATESTR,

      DBDesDensity_key_ID, m_nID);
   
   if (!pADOConn->ExecuteSQL(strSQL))
   {
      pADOConn->RollbackTrans();
      return FALSE;
   }

   strSQL.Format(_T("delete from %s where %s = '%llld'"),DB_TABLE_DESFACECODE,DBDesFaceCode_key_IDDENSITY,m_nID);
   if (!pADOConn->ExecuteSQL(strSQL))
   {
      pADOConn->RollbackTrans();
      return FALSE;
   }

   int nCount = m_faceData.m_lstFaceCode.GetCount();
   CString strFaceCodeInsertFormatSQL = _T(""),  strFaceCodeInsertValueSQL = _T("");
   CDBFaceCode oFaceCodeData;
   strFaceCodeInsertFormatSQL = oFaceCodeData.GetSQLFormat();

   for (int i = 0; i < nCount; i++)
   {
      if (!strFaceCodeInsertValueSQL.IsEmpty())
      {
         strFaceCodeInsertValueSQL += _T(",");
      }
      CString strTmpValueSQL = _T("");

      CDBFaceCode* pCode = m_faceData.m_lstFaceCode.GetItem(i);
      if (pCode)
      {
         strTmpValueSQL = pCode->GetValueFormat(pCode->m_strName, pCode->m_sOldLen, pCode->m_strType, pCode->m_sLen, pCode->m_strUnit, m_nID);
      }
      strFaceCodeInsertValueSQL += strTmpValueSQL;
   }
   if (!strFaceCodeInsertValueSQL.IsEmpty())
   {
      strSQL.Format(_T("insert into %s(%s) values %s"), DB_TABLE_DESFACECODE, strFaceCodeInsertFormatSQL, strFaceCodeInsertValueSQL);
   }

   if (!pADOConn->ExecuteSQL(strSQL))
   {
      pADOConn->RollbackTrans();
      return FALSE;
   }

   if (pADOConn->CommitTrans())
   {
      bRet = TRUE;
   }
   else
   {
      bRet = FALSE;
   }

   return bRet;
}

BOOL CDBDensity::InsertAllDBInfoByID(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);

   BOOL bRet = TRUE;

   CString strSQL = _T("");
   strSQL.Format(_T("insert into %s (%s, %s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,\
                     %s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s)\
					 values('%s','%s','%s','%s','%.2f', '%.2f','%.2f','%.2f','%.2f','%.4f','%.2f','%.2f'\
      '%s','%d','%.2f','%s','%s','%.2f','%d''%d','%s','%s','%s',\
      '%d','%s','%s','%s','%s','%s')"), DB_TABLE_DENSITY,\
      DBDesDensity_key_Name, DBDesDensity_key_Structure, DBDesDensity_key_Material, DBDesDensity_key_Needle, DBDesDensity_key_HorDesSrc, \
      DBDesDensity_key_VerDesSrc, DBDesDensity_key_HorDesNew, DBDesDensity_key_VerDesNew, DBDesDensity_key_Pull, DBDesDensity_key_PieceUnit, \
      DBDesDensity_key_PieceTurns, DBDesDensity_key_PieceNeedle,

      DBDesDensity_key_PullUnit,  
      DBDesDensity_key_PullType,  
      DBDesDensity_key_StartTurns,
      DBDesDensity_key_RomanType, 
      DBDesDensity_key_Wire,      
      DBDesDensity_key_WireTurns, 
      DBDesDensity_key_WireType,  
      DBDesDensity_key_ShowPZ,    
      DBDesDensity_key_PZName,    
      DBDesDensity_key_PinBottom, 
      DBDesDensity_key_PinFace,   
      DBDesDensity_key_PinType,   
      DBDesDensity_key_Type,      
      DBDesDensity_key_BaseType,  
      DBDesDensity_key_cPieceName,
      DBDesDensity_key_cMatName,  
      DBDesDensity_key_cRemark, 
      m_strName,
      m_strStructure,
      m_strMaterial,
      m_strNeedle,
      m_fHorDesSrc,
      m_fVerDesSrc,
      m_fHorDesNew,
      m_fVerDesNew,
      m_fPull,
      m_fPieceUnit,
      m_fPieceTurns,
      m_fPieceNeedle,

      m_strPullUnit,
      m_nPullType,
      m_fStartTurns,
      m_strRomanType,
      m_strWire,
      m_fWireTurns,
      m_nWireType,
      m_bShowPZ,
      m_strPZName,
      m_strPinBottom,
      m_strPinFace,
      m_nPinType,
      m_strType,
      m_strBaseType,
      m_strPieceName,
      m_strMatName,
      m_strRemark
   );

   //-------------------------------
   CString strDensityInsertSQL = GetInsertSQL();
   CString strFaceCodeInsertFormatSQL = _T(""), strFaceCodeInsertValueSQL = _T("");
   CDBFaceCode oFaceCodeData;
   strFaceCodeInsertFormatSQL = oFaceCodeData.GetSQLFormat();

   int nCount  = m_faceData.m_lstFaceCode.GetCount();

   for (int i = 0; i < nCount; i++)
   {
      if (!strFaceCodeInsertValueSQL.IsEmpty())
      {
         strFaceCodeInsertValueSQL += _T(",");
      }
      CString strTmpValueSQL = _T("");

      CDBFaceCode* pCode = m_faceData.m_lstFaceCode.GetItem(i);
      if (pCode)
      {
         //strTmpValueSQL = pCode->GetValueFormat(pCode->m_strName, pCode->m_sOldLen, pCode->m_strType, pCode->m_sLen, pCode->m_strUnit, m_nID);
         strTmpValueSQL.Format(_T("('%s','%s','%s','%s','%s',@IDensityID)"), 
            pCode->m_strName, pCode->m_sOldLen, pCode->m_strType, pCode->m_sLen, pCode->m_strUnit);
      }
      strFaceCodeInsertValueSQL += strTmpValueSQL;
   }

   CString strFaceCodeSQL = _T("");
   if (!strFaceCodeInsertValueSQL.IsEmpty())
   {
      strFaceCodeSQL.Format(_T("insert into %s(%s) values %s"), DB_TABLE_DESFACECODE, strFaceCodeInsertFormatSQL, strFaceCodeInsertValueSQL);
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

#if Des_IMAGE
void CDBDensity::ClearColorImage()
{
   if (NULL != m_pFlowerPatternPic)
   {
      delete m_pFlowerPatternPic;
      m_pFlowerPatternPic = NULL;
   }
}
#endif // Des_IMAGE

//CDBFaceCodeList
IMPLEMENT_SERIAL(CDBDensityList,  CDataListMid, 1)
std::shared_ptr<CDBDensityList> CDBDensityList::sm_inst;
CDBDensityList::CDBDensityList()
{

}

CDBDensityList::~CDBDensityList()
{

}

CDBDensity*  CDBDensityList::GetItem(int nIndex)
{
	if (nIndex<0||nIndex>=GetCount())
		return NULL;

	return (CDBDensity*)GetAt(FindIndex(nIndex));
}

CDBDensity* CDBDensityList::GetItemByName(const CString & strName)
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

void CDBDensityList::AddItem(CDBDensity* pItem)
{
	CDBDensity*pData = new CDBDensity;
	pData->Copy(pItem);
	AddTail(pData);
}

void CDBDensityList::DeleteItem(int nIndex)
{
	if (nIndex<0||nIndex>GetCount())
		return;

	CDBDensity *pObject = (CDBDensity*)GetItem(nIndex);
	delete pObject;
	pObject = NULL;

	RemoveAt(FindIndex(nIndex));
}

BOOL CDBDensityList::DeleteUserByUserID(CADOConn* pADOConn, vector<CString>vecUserID)
{
   ASSERT(pADOConn != NULL);
   if (vecUserID.size() <= 0)
      return FALSE;

   CString strUserID;
   for (int i = 0; i < (int)vecUserID.size(); ++i)
   {
      strUserID += _T("'") + vecUserID[i] + _T("',");
   }
   strUserID.TrimRight(_T(","));
   CString strSql;
   strSql.Format(_T("delete from %s where %s in (%s)"), _T("DesDensity"), DBDesDensity_key_ID, strUserID);
   return pADOConn->ExecuteSQL(strSql);
}

CDBDensityList* CDBDensityList:: Instance()		//��ȡ��ָ�룩ʵ��
{
	if(sm_inst.get() == 0)
		sm_inst = shared_ptr<CDBDensityList>(new CDBDensityList);

	return sm_inst.get();
}

void CDBDensityList::MatchData(CDBFaceCode* data)
{
   int nIndex = 0, nCount = GetCount();
   for (nIndex = 0; nIndex < nCount; nIndex++)
   {
      CDBDensity * pData = GetItem(nIndex);
      if (NULL != pData && pData->m_nID == data->m_nIDDensity)
      {
         pData->SetFaceData(data);
      }
   }
}

#ifdef USING_GRIDCTRL_MARK
MAP_GridCtrl_AllData CDBDensityList::CreateGridData(const CString & strUserDuty/*=_T("")*/)
{
   MAP_GridCtrl_AllData map_all_data;

   int nIndex = 0, nCount = GetCount();
   int nValidCount = 1;
   for (nIndex = 0; nIndex < nCount; nIndex++)
   {
      CDBDensity * pData = GetItem(nIndex);
      if (NULL != pData)
      {
         MAP_GridCtrl_RowData map_row_data;
         CString strIndex = _T("");
         strIndex.Format(FORMAT_INT, nValidCount);
         CString cName = _T("");
         for (int i = 0; i < 4; i++)
         {
            CDBFaceCode* pCode = pData->m_faceData.m_lstFaceCode.GetItem(i);
            if (pCode)
            {
               CString cKeyCode = _T("");
               cKeyCode.Format(_T("cFaceCode%d"),i+1);
               cName.Format(_T("%s: %s %s %s %s"), pCode->m_strName, pCode->m_sOldLen, pCode->m_strType, pCode->m_sLen, pCode->m_strUnit);
               pData->InsertRowData(cKeyCode, map_row_data, FORMAT_STRING, cName);//����
            }
         }

         pData->InsertRowData(DBDesDensity_key_ID,         map_row_data, CB_enum_FieldData_Int, CB_enum_FieldCtrl_Text, _T("%lld"), pData->m_nID);         //ID
         pData->InsertRowData(DBDesDensity_key_Name,       map_row_data, FORMAT_STRING,   pData->m_strName);     //����
         pData->InsertRowData(DBDesDensity_key_HorDesSrc,  map_row_data, CB_enum_FieldData_Double2Point, CB_enum_FieldCtrl_Text, FORMAT_FLOAT2DOT, pData->m_fHorDesSrc);  //���º���
         pData->InsertRowData(DBDesDensity_key_VerDesSrc,  map_row_data, CB_enum_FieldData_Double2Point, CB_enum_FieldCtrl_Text, FORMAT_FLOAT2DOT, pData->m_fVerDesSrc);  //����ֱ��
         pData->InsertRowData(DBDesDensity_key_HorDesNew,  map_row_data, CB_enum_FieldData_Double2Point, CB_enum_FieldCtrl_Text, FORMAT_FLOAT2DOT, pData->m_fHorDesNew);  //�»�����
         pData->InsertRowData(DBDesDensity_key_VerDesNew,  map_row_data, CB_enum_FieldData_Double2Point, CB_enum_FieldCtrl_Text, FORMAT_FLOAT2DOT, pData->m_fVerDesNew);  //�»�ֱ��
         pData->InsertRowData(DBDesDensity_key_Structure,  map_row_data, FORMAT_STRING,   pData->m_strStructure);//�����ṹ
         pData->InsertRowData(DBDesDensity_key_Material,   map_row_data, FORMAT_STRING,   pData->m_strMaterial); //ë��
         pData->InsertRowData(DBDesDensity_key_Pull,       map_row_data, CB_enum_FieldData_Double2Point, CB_enum_FieldCtrl_Text, FORMAT_FLOAT2DOT, pData->m_fPull);       //����
         pData->InsertRowData(DBDesDensity_key_PullUnit,   map_row_data, FORMAT_STRING,   pData->m_strPullUnit); //������λ
         pData->InsertRowData(DBDesDensity_key_PullType,   map_row_data, FORMAT_INT,   pData->m_nPullType);   //eg:ȫ���� or ������
         pData->InsertRowData(DBDesDensity_key_Needle,     map_row_data, FORMAT_STRING,   pData->m_strNeedle);   //����
         pData->InsertRowData(DBDesDensity_key_StartTurns, map_row_data, CB_enum_FieldData_Double2Point, CB_enum_FieldCtrl_Text, FORMAT_FLOAT2DOT, pData->m_fStartTurns); //��ͷ��ת
         pData->InsertRowData(DBDesDensity_key_RomanType,  map_row_data, FORMAT_STRING,   pData->m_strRomanType);//��������
         pData->InsertRowData(DBDesDensity_key_Wire,       map_row_data, FORMAT_STRING,   pData->m_strWire);     //��˿
         pData->InsertRowData(DBDesDensity_key_WireTurns,  map_row_data, FORMAT_FLOAT2DOT, pData->m_fWireTurns);  //ת
         pData->InsertRowData(DBDesDensity_key_WireType,   map_row_data, FORMAT_INT,   pData->m_nWireType);   //�Ƿ�ȫ��˿
         pData->InsertRowData(DBDesDensity_key_ShowPZ,     map_row_data, FORMAT_INT,   pData->m_bShowPZ);     //�Ƿ���ʾ����
         pData->InsertRowData(DBDesDensity_key_PZName,     map_row_data, FORMAT_STRING,   pData->m_strPZName);   //��������
         pData->InsertRowData(DBDesDensity_key_PinBottom,  map_row_data, FORMAT_STRING,   pData->m_strPinBottom);//��
         pData->InsertRowData(DBDesDensity_key_PinFace,    map_row_data, FORMAT_STRING,   pData->m_strPinFace);  //��
         pData->InsertRowData(DBDesDensity_key_PinType,    map_row_data, FORMAT_INT,   pData->m_nPinType);    //��������
         pData->InsertRowData(DBDesDensity_key_Type,       map_row_data, FORMAT_STRING,   pData->m_strType);     //�ܶ��Զ�������
         pData->InsertRowData(DBDesDensity_key_BaseType,   map_row_data, FORMAT_STRING, pData->m_strBaseType); //�����ܶ� or �����ܶ�
         pData->InsertRowData(DBDesDensity_key_cSavedUserID, map_row_data, FORMAT_STRING, pData->m_strSavedUserID);  //������
         pData->InsertRowData(DBDesDensity_key_cSaveTime,  map_row_data, CB_enum_FieldData_Time, CB_enum_FieldCtrl_DateTime, FORMAT_STRING, pData->m_strSaveTime);  //����ʱ��
         pData->InsertRowData(DBDesDensity_key_cRemark,    map_row_data, FORMAT_STRING, pData->m_strRemark);   //�ܶ�˵��
         pData->InsertRowData(DBDesDensity_key_cOrderNo,   map_row_data, FORMAT_STRING, pData->m_strOrderNo);   //������
         pData->InsertRowData(DBDesDensity_key_cPieceName, map_row_data, FORMAT_STRING,   pData->m_strPieceName);//��Ƭ����
         pData->InsertRowData(DBDesDensity_key_cMatName,   map_row_data, FORMAT_STRING, pData->m_strMatName);  //��������
         CString cUnit = _T("");
         cUnit.Format(_T("%.4f��%.2fת%.2f��"), pData->m_fPieceUnit, pData->m_fPieceTurns, pData->m_fPieceNeedle);
         pData->InsertRowData(DBDesDensity_key_PieceUnit,  map_row_data, FORMAT_STRING, cUnit);//СƬ����

         map_all_data.insert(make_pair(nValidCount,        map_row_data));
         //�����ݲ�������������

         nValidCount++;
      }
   }

   return map_all_data;
}
#endif

IMPLEMENT_SERIAL(CDBDensityFaceCodeData,  CDataMid, 1)
CDBDensityFaceCodeData::CDBDensityFaceCodeData()
{

}

CDBDensityFaceCodeData::~CDBDensityFaceCodeData()
{
	m_lstFaceCode.Empty();
}

void CDBDensityFaceCodeData::Copy(CDBDensityFaceCodeData * pData)
{
	ASSERT(NULL != pData);

	if (NULL == pData)
	{
		return;
	}
	m_nIDDensity = pData->m_nIDDensity;
	m_lstFaceCode.Empty();
	int nIndex = 0,nCount = pData->m_lstFaceCode.GetCount();
	for (nIndex = 0;nIndex < nCount;nIndex++)
	{
		auto pFaceCodeData = pData->m_lstFaceCode.GetItem(nIndex);
		if (NULL != pFaceCodeData)
		{
			if (0 == m_lstFaceCode.GetCount() && 0 >= m_nIDDensity)
			{
				m_nIDDensity = pFaceCodeData->m_nIDDensity;
			}
			m_lstFaceCode.AddItem(pFaceCodeData);
		}
	}
}

void CDBDensityFaceCodeData::AddItem(CDBFaceCode * pData)
{
	ASSERT(NULL != pData);
	
	if (0 == m_lstFaceCode.GetCount())
	{
		m_nIDDensity = pData->m_nIDDensity;
	}
	m_lstFaceCode.AddItem(pData);
}

IMPLEMENT_SERIAL(CDBDensityFaceCodeList,  CDataListMid, 1)

CDBDensityFaceCodeList::CDBDensityFaceCodeList()
{

}

CDBDensityFaceCodeList::~CDBDensityFaceCodeList()
{
	Empty();
}

CDBDensityFaceCodeData* CDBDensityFaceCodeList::GetItem(int nIndex)
{
	if (nIndex<0||nIndex>=GetCount())
		return NULL;

	return (CDBDensityFaceCodeData*)GetAt(FindIndex(nIndex));
}

CDBDensityFaceCodeData* CDBDensityFaceCodeList::GetItemByIDDensity(int nID)
{
	int nIndex = 0,nCount = GetCount();
	for (nIndex = 0;nIndex < nCount;nIndex++)
	{
		auto pData = GetItem(nIndex);
		if (NULL != pData)
		{
			if (nID = pData->m_nIDDensity)
			{
				return pData;
			}
		}
	}
	return 0;
}

void CDBDensityFaceCodeList::AddItem(CDBDensityFaceCodeData* pItem)
{
	CDBDensityFaceCodeData*pData = new CDBDensityFaceCodeData;
	pData->Copy(pItem);
	AddTail(pData);
}

void CDBDensityFaceCodeList::DeleteItem(int nIndex)
{
	if (nIndex<0||nIndex>GetCount())
		return;

	CDBDensityFaceCodeData *pObject = (CDBDensityFaceCodeData*)GetItem(nIndex);
	delete pObject;
	pObject = NULL;

	RemoveAt(FindIndex(nIndex));
}