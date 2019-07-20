#include "StdAfx.h"
#include "DBColorPriceSet.h"
#include "CommonAPI.h"
#include "DBKeyDef.h"
#include "DBKeyDef_V.h"
#include "DBKeyDef_Cust.h"

IMPLEMENT_SERIAL(CDBDataColorPriceSet,  CDataMid, 1)
   IMPLEMENT_SERIAL(CDBDataColorPriceSetInfoList,  CDataListMid, 1)

   std::shared_ptr<CDBDataColorPriceSet> CDBDataColorPriceSet::sm_inst;
std::shared_ptr<CDBDataColorPriceSetInfoList> CDBDataColorPriceSetInfoList::sm_inst;

CDBDataColorPriceSet::CDBDataColorPriceSet(void)
{
   ResetData();
}

CDBDataColorPriceSet * CDBDataColorPriceSet::Instance()
{
   if(sm_inst.get() == 0)
      sm_inst = shared_ptr<CDBDataColorPriceSet>(new CDBDataColorPriceSet);

   return sm_inst.get();
}

CDBDataColorPriceSet::~CDBDataColorPriceSet(void)
{
}
void CDBDataColorPriceSet::ResetData()
{
   m_str_dDate      =_T("");
   m_str_iSunhao    =_T("");
   m_str_iSalePrice =_T("");
   m_str_iPrice     =_T("");
   m_str_cDaihao    =_T("");
   m_str_cCate      =_T("");
   m_str_cCusCode   =_T("");
   m_str_ID         =_T("");
   m_str_cCusCate   =_T("");
   m_str_cCusName   =_T("");
   /*m_str_cCusAbbName=_T("");
   m_str_vCusAbbName=_T("");*/
   m_str_fZMDSalePrice=_T("");  //ר�������۵���
   m_str_fZhekou=_T("");  //�ۿ�
   m_str_cChenfen = _T("");
   m_str_fBeiLv = _T("");
}
void CDBDataColorPriceSet::Copy(CDBDataColorPriceSet *pData)
{
   ASSERT(pData != NULL);
   CDataMid::Copy(pData);

   m_str_dDate      =pData->m_str_dDate      	;
   m_str_iSunhao    =pData->m_str_iSunhao    	   ;
   m_str_iSalePrice =pData->m_str_iSalePrice 		;
   m_str_iPrice     =pData->m_str_iPrice     	;
   m_str_cDaihao    =pData->m_str_cDaihao    	;
   m_str_cCate      =pData->m_str_cCate      	   ;
   m_str_cCusCode   =pData->m_str_cCusCode        ;
   m_str_ID         =pData->m_str_ID           ;
   m_str_cCusCate   =pData->m_str_cCusCate   	   ;
   m_str_cCusName   =pData->m_str_cCusName   	   ;
   /*m_str_cCusAbbName=pData->m_str_cCusAbbName		;
   m_str_vCusAbbName=pData->m_str_vCusAbbName  ;*/
   m_str_fZMDSalePrice=pData->m_str_fZMDSalePrice;  //ר�������۵���
   m_str_fZhekou=pData->m_str_fZhekou;  //�ۿ�
   m_str_cChenfen = pData->m_str_cChenfen;	//�ɷ�
   m_str_fBeiLv   = pData->m_str_fBeiLv; //����
}
void CDBDataColorPriceSet::Serialize(CArchive& ar)
{

}

//����Ʒ�ֵĿͻ����ƻ�ȡ�۸���Ϣ		by WangZY 2018/04/22
BOOL CDBDataColorPriceSet::GetInfoByCateAndCusCode(CADOConn *pADOConn, 
   CString strColorCate,CString strCusCode)
{
   ASSERT(NULL != pADOConn);
   BOOL bRet = FALSE;
   if (NULL == pADOConn)
   {
      return bRet;
   }

   CString strSQL = _T("");
   strSQL.Format(_T("select * from %s \
                    where %s='%s' and %s='%s'"),
                    DB_VIEW_COLORPRICE,

                    DBPRICESET_KEY_cCusCode,
                    strCusCode,

                    DBPRICESET_KEY_cCate,
                    strColorCate
                    );

   pADOConn->GetRecordSet(strSQL);
   while (!pADOConn->adoEOF())
   {
      GetAllDBInfo(pADOConn);
      pADOConn->MoveNext();

      return TRUE;
   }

   return FALSE;


}

//��ȡ����������Ϣ
BOOL CDBDataColorPriceSet::GetAllDBInfo(CADOConn *pADOConn)
{
   ASSERT(NULL != pADOConn);
   BOOL bRet = FALSE;
   if (NULL == pADOConn)
   {
      return bRet;
   }
   else
   {
      m_str_dDate      =pADOConn->GetValueString(DBPRICESET_KEY_dDate      );     //����
      m_str_iSunhao    =pADOConn->GetValueDoubleStr(DBPRICESET_KEY_iSunhao,4       );  //���
      m_str_iSalePrice =pADOConn->GetValueDoubleStr(DBPRICESET_KEY_iSalePrice,2	);  //���۵���
      m_str_iPrice     =pADOConn->GetValueDoubleStr(DBPRICESET_KEY_iPrice ,2    	);  //����
      m_str_cDaihao    =pADOConn->GetValueString(DBPRICESET_KEY_cDaihao    	);  //Ʒ�ִ���
      m_str_cCate      =pADOConn->GetValueString(DBPRICESET_KEY_cCate         );  //Ʒ��
      m_str_cCusCode   =pADOConn->GetValueString(DBPRICESET_KEY_cCusCode      );  //�ͻ����
      m_str_ID         =pADOConn->GetValueString(DBPRICESET_KEY_ID         );     //ID
      m_str_cCusCate   =pADOConn->GetValueString(DBPRICESET_KEY_cCusCate      );  //�ͻ�����
      m_str_cCusName   =pADOConn->GetValueString(DBPRICESET_KEY_cCusName      );  //�ͻ�ȫ��
      //m_str_cCusAbbName=pADOConn->GetValueString(DBPRICESET_KEY_cCusAbbName	);  //�ͻ����
      //m_str_vCusAbbName=pADOConn->GetValueString(DBPRICESET_KEY_vCusAbbName);     //�ͻ�
      m_str_fZMDSalePrice = pADOConn->GetValueDoubleStr(DBPRICESET_KEY_fZMDSalePrice,2);  //ר�������۵���
      m_str_fZhekou       = pADOConn->GetValueDoubleStr(DBPRICESET_KEY_fZhekou,2);  //�ۿ�
      m_str_cChenfen		= pADOConn->GetValueString(DBPRICESET_KEY_cChenfen);		//�ɷ�
      m_str_fBeiLv      = pADOConn->GetValueDoubleStr(DBPRICESET_KEY_fBeiLv,2);  //����
      return TRUE;
   }                  
}
#ifdef USING_GRIDCTRL_MARK
void CDBDataColorPriceSet::ToGridDB(MAP_GridCtrl_RowData *pRowData) //���ת��ΪDB���� liuhw 2018/09/15
{
   ASSERT(pRowData != NULL);
   m_str_dDate      =pRowData->find(DBPRICESET_KEY_dDate)->second.strValue;  //����
   m_str_iSunhao    =pRowData->find(DBPRICESET_KEY_iSunhao)->second.strValue;  //���
   m_str_iSalePrice =pRowData->find(DBPRICESET_KEY_iSalePrice)->second.strValue;  //���۵���
   m_str_iPrice     =pRowData->find(DBPRICESET_KEY_iPrice)->second.strValue;  //����
   m_str_cDaihao    =pRowData->find(DBPRICESET_KEY_cDaihao)->second.strValue;  //Ʒ�ִ���
   m_str_cCate      =pRowData->find(DBPRICESET_KEY_cCate)->second.strValue;  //Ʒ��
   m_str_cCusCode   =pRowData->find(DBPRICESET_KEY_cCusCode)->second.strValue;  //�ͻ����
   m_str_ID         =pRowData->find(DBPRICESET_KEY_ID)->second.strValue;  //ID
   m_str_fZMDSalePrice=pRowData->find(DBPRICESET_KEY_fZMDSalePrice)->second.strValue;  //ר�������۵���
   m_str_fZhekou    =pRowData->find(DBPRICESET_KEY_fZhekou)->second.strValue;  //�ۿ�
   m_str_cChenfen   =pRowData->find(DBPRICESET_KEY_cChenfen)->second.strValue;	//�ɷ�
   m_str_fBeiLv     = pRowData->find(DBPRICESET_KEY_fBeiLv)->second.strValue;    //����     add anjie by 2018/10/25
}
#endif // USING_GRIDCTRL_MARK

//�Ƚ��޸�ǰ�����ݣ����޸��˵����ݱ�������
CString CDBDataColorPriceSet::SetDBEquals_Log(CDBDataColorPriceSet &pOldData)
{
   CString strActLog = _T("");
   if (m_str_dDate != pOldData.m_str_dDate)
   {
      CString str_dData;
      if (m_str_dDate.IsEmpty())
      {
         str_dData = _T("��ֵ");
      }
      str_dData = m_str_dDate;
      strActLog += _T("����") + str_dData + _T(",");
   }
   if (m_str_iSunhao != pOldData.m_str_iSunhao)
   {
      CString str_iSunhao;
      if (m_str_iSunhao.IsEmpty())
      {
         str_iSunhao = _T("��ֵ");
      }
      str_iSunhao = m_str_iSunhao;
      strActLog += _T("���:") + str_iSunhao + _T(",");
   }
   if (m_str_iSalePrice  != pOldData.m_str_iSalePrice )
   {
      CString str_iSalePrice;
      if (m_str_iSalePrice.IsEmpty())
      {
         str_iSalePrice = _T("��ֵ");
      }
      str_iSalePrice = m_str_iSalePrice;
      strActLog += _T("���۵���:") + str_iSalePrice + _T(",");
   }
   if (m_str_iPrice != pOldData.m_str_iPrice)
   {
      CString str_iPrice;
      if (m_str_iPrice.IsEmpty())
      {
         str_iPrice = _T("��ֵ");
      }
      str_iPrice = m_str_iPrice;
      strActLog += _T("����:") + str_iPrice + _T(",");
   }
   if (m_str_cDaihao != pOldData.m_str_cDaihao)
   {
      CString str_cDaihao;
      if (m_str_cDaihao.IsEmpty())
      {
         str_cDaihao = _T("��ֵ");
      }
      str_cDaihao = m_str_cDaihao;
      strActLog += _T("Ʒ�ִ���:") + str_cDaihao + _T(",");
   }
   if (m_str_cCate != pOldData.m_str_cCate)
   {
      CString str_cCate;
      if (m_str_cCate.IsEmpty())
      {
         str_cCate = _T("��ֵ");
      }
      str_cCate = m_str_cCate;
      strActLog += _T("Ʒ��:") + str_cCate + _T(",");
   }
   if (m_str_cCusCode != pOldData.m_str_cCusCode)
   {
      CString str_cCusCode;
      if (m_str_cCusCode.IsEmpty())
      {
         str_cCusCode = _T("��ֵ");
      }
      str_cCusCode = m_str_cCusCode;
      strActLog += _T("�ͻ����:") + str_cCusCode + _T(",");
   }
   if (m_str_cCusCate  != pOldData.m_str_cCusCate )
   {
      CString str_cCusCate;
      if (m_str_cCusCate .IsEmpty())
      {
         str_cCusCate = _T("��ֵ");
      }
      str_cCusCate = m_str_cCusCate ;
      strActLog += _T("�ͻ�����:") + str_cCusCate + _T(",");
   }
   if (m_str_cCusName != pOldData.m_str_cCusName)
   {
      CString str_cCusName;
      if (m_str_cCusName.IsEmpty())
      {
         str_cCusName = _T("��ֵ");
      }
      str_cCusName = m_str_cCusName;
      strActLog += _T("�ͻ�ȫ��:") + str_cCusName + _T(",");
   }
   /*if (m_str_cCusAbbName != pOldData.m_str_cCusAbbName)
   {
   CString str_cCusAbbName;
   if (m_str_cCusAbbName.IsEmpty())
   {
   str_cCusAbbName = _T("��ֵ");
   }
   str_cCusAbbName = m_str_cCusAbbName;
   strActLog += _T("�ͻ����:") + str_cCusAbbName + _T(",");
   }
   if (m_str_vCusAbbName != pOldData.m_str_vCusAbbName)
   {
   CString str_vCusAbbName;
   if (m_str_vCusAbbName.IsEmpty())
   {
   str_vCusAbbName = _T("��ֵ");
   }
   str_vCusAbbName = m_str_vCusAbbName;
   strActLog += _T("�ͻ�:") + str_vCusAbbName + _T(",");
   }*/
   if (m_str_fZMDSalePrice != pOldData.m_str_fZMDSalePrice)
   {
      CString str_fZMDSalePrice;
      if (m_str_fZMDSalePrice.IsEmpty())
      {
         str_fZMDSalePrice = _T("��ֵ");
      }
      str_fZMDSalePrice = m_str_fZMDSalePrice;
      strActLog += _T("ר�������۵���:") + str_fZMDSalePrice + _T(",");
   }
   if (m_str_fZhekou != pOldData.m_str_fZhekou)
   {
      CString str_fZhekou;
      if (m_str_fZhekou.IsEmpty())
      {
         str_fZhekou = _T("��ֵ");
      }
      str_fZhekou = m_str_fZhekou;
      strActLog += _T("�ۿ�:") + str_fZhekou + _T(",");
   }
   if (m_str_cChenfen != pOldData.m_str_cChenfen)
   {
      CString str_cChenfen;
      if (m_str_cChenfen.IsEmpty())
      {
         str_cChenfen = _T("��ֵ");
      }
      str_cChenfen = m_str_cChenfen;
      strActLog += _T("�ɷ�:") + str_cChenfen + _T(",");
   }
   if (m_str_fBeiLv != pOldData.m_str_fBeiLv)
   {
      CString str_fBeiLv;
      if (m_str_fBeiLv.IsEmpty())
      {
         str_fBeiLv = _T("��ֵ");
      }
      str_fBeiLv = m_str_cChenfen;
      strActLog += _T("�ɷ�:") + str_fBeiLv + _T(",");
   }
   return strActLog;
}

CDBDataColorPriceSetInfoList::CDBDataColorPriceSetInfoList(void)
{
}

CDBDataColorPriceSetInfoList::~CDBDataColorPriceSetInfoList(void)
{
}

CDBDataColorPriceSet* CDBDataColorPriceSetInfoList::GetItem( int nIndex )
{
   if (nIndex<0||nIndex>=GetCount())
      return NULL;
   return (CDBDataColorPriceSet*)GetAt(FindIndex(nIndex));
}

void CDBDataColorPriceSetInfoList::AddItem( CDBDataColorPriceSet* pItem )
{
   CDBDataColorPriceSet*pData=new CDBDataColorPriceSet;
   pData->Copy(pItem);
   AddTail(pData);
}

void CDBDataColorPriceSetInfoList::DeleteItem( int nIndex )
{
   if (nIndex<0||nIndex>GetCount())
      return;
   CDBDataColorPriceSet *pObject=(CDBDataColorPriceSet*)GetItem(nIndex);
   delete pObject;
   pObject=NULL;
   RemoveAt(FindIndex(nIndex));
}

CDBDataColorPriceSetInfoList * CDBDataColorPriceSetInfoList::Instance()
{
   if(sm_inst.get() == 0)
      sm_inst = shared_ptr<CDBDataColorPriceSetInfoList>(new CDBDataColorPriceSetInfoList);

   return sm_inst.get();
}

BOOL CDBDataColorPriceSetInfoList::GetListFromDB(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);

   Empty();
   CString strSQL = _T("");
   strSQL.Format(_T("select * from %s"),DB_VIEW_COLORPRICE);

   pADOConn->GetRecordSet(strSQL);
   while (!pADOConn->adoEOF())
   {
      CDBDataColorPriceSet oData;
      oData.GetAllDBInfo(pADOConn);
      AddItem(&oData);
      pADOConn->MoveNext();
   }
   return TRUE;
}

#ifdef USING_GRIDCTRL_MARK
BOOL CDBDataColorPriceSetInfoList::GetDataFromDB(CADOConn *pADOConn,MAP_GridCtrl_AllData &allData)
{
   ASSERT(pADOConn != NULL);
   Empty();
   allData.clear();
   CString strSQL = _T("");
   strSQL.Format(_T("select * from %s"),DB_VIEW_COLORPRICE);

   pADOConn->GetRecordSet(strSQL);
   int index =1;
   while (!pADOConn->adoEOF())
   {
      CDBDataColorPriceSet oData;
      oData.GetAllDBInfo(pADOConn);
      AddItem(&oData);
      MAP_GridCtrl_RowData map_row_data; 
      InsertRowData(DBPRICESET_KEY_dDate      ,oData.m_str_dDate,map_row_data);
      InsertRowData(DBPRICESET_KEY_iSunhao    ,oData.m_str_iSunhao,map_row_data,CB_enum_FieldData_Double2Point);
      InsertRowData(DBPRICESET_KEY_iSalePrice ,oData.m_str_iSalePrice,map_row_data,CB_enum_FieldData_Double2Point);
      InsertRowData(DBPRICESET_KEY_iPrice     ,oData.m_str_iPrice,map_row_data,CB_enum_FieldData_Double2Point);
      InsertRowData(DBPRICESET_KEY_cDaihao    ,oData.m_str_cDaihao,map_row_data);
      InsertRowData(DBPRICESET_KEY_cCate      ,oData.m_str_cCate,map_row_data);
      InsertRowData(DBPRICESET_KEY_cCusCode   ,oData.m_str_cCusCode,map_row_data);
      InsertRowData(DBPRICESET_KEY_ID         ,oData.m_str_ID,map_row_data, CB_enum_FieldData_Int);
      InsertRowData(DBPRICESET_KEY_cCusCate   ,oData.m_str_cCusCate,map_row_data);
      InsertRowData(DBPRICESET_KEY_cCusName   ,oData.m_str_cCusName,map_row_data);
      /*InsertRowData(DBPRICESET_KEY_cCusAbbName,oData.m_str_cCusAbbName,map_row_data);
      InsertRowData(DBPRICESET_KEY_vCusAbbName,oData.m_str_vCusAbbName,map_row_data);*/
      InsertRowData(DBPRICESET_KEY_fZMDSalePrice    ,oData.m_str_fZMDSalePrice,map_row_data,CB_enum_FieldData_Double2Point);
      InsertRowData(DBPRICESET_KEY_fZhekou    ,oData.m_str_fZhekou,map_row_data,CB_enum_FieldData_Double2Point);
      InsertRowData(DBPRICESET_KEY_cChenfen, oData.m_str_cChenfen,map_row_data);
      InsertRowData(DBPRICESET_KEY_fBeiLv, oData.m_str_fBeiLv,map_row_data,CB_enum_FieldData_Double2Point);//�������
      allData.insert(make_pair(index,map_row_data));
      index++;
      pADOConn->MoveNext();
   }
   return TRUE;
}
BOOL CDBDataColorPriceSetInfoList::UpdateOneByID(CADOConn *pADOConn,const MAP_GridCtrl_RowData &oneRow)
{
   ASSERT(pADOConn != NULL);
   CString strSQL = _T("");
   strSQL.Format(_T("Update %s \
                    set %s='%s',%s='%s',%s='%s',%s='%s',%s='%s',\
                    %s='%s',%s='%s',%s='%s',%s='%s',%s='%s',%s='%s' \
                    where %s='%s'")
                    ,DB_TABLE_COLORPRICE

                    ,DBPRICESET_KEY_cCusCode,oneRow.find(DBPRICESET_KEY_cCusCode)->second.strValue
                    ,DBPRICESET_KEY_dDate,oneRow.find(DBPRICESET_KEY_dDate)->second.strValue      
                    ,DBPRICESET_KEY_iSunhao,oneRow.find(DBPRICESET_KEY_iSunhao)->second.strValue      
                    ,DBPRICESET_KEY_iSalePrice,oneRow.find(DBPRICESET_KEY_iSalePrice)->second.strValue
                    ,DBPRICESET_KEY_iPrice,oneRow.find(DBPRICESET_KEY_iPrice)->second.strValue  

                    ,DBPRICESET_KEY_cDaihao,oneRow.find(DBPRICESET_KEY_cDaihao)->second.strValue      
                    ,DBPRICESET_KEY_cCate,oneRow.find(DBPRICESET_KEY_cCate)->second.strValue
                    ,DBPRICESET_KEY_fZhekou,oneRow.find(DBPRICESET_KEY_fZhekou)->second.strValue
                    ,DBPRICESET_KEY_fZMDSalePrice,oneRow.find(DBPRICESET_KEY_fZMDSalePrice)->second.strValue
                    ,DBPRICESET_KEY_cChenfen,oneRow.find(DBPRICESET_KEY_cChenfen)->second.strValue
                    ,DBPRICESET_KEY_fBeiLv,oneRow.find(DBPRICESET_KEY_fBeiLv)->second.strValue//�������
                    ,DBPRICESET_KEY_ID,oneRow.find(DBPRICESET_KEY_ID)->second.strValue	
                    );
   return pADOConn->ExecuteSQL(strSQL);
}
BOOL CDBDataColorPriceSetInfoList::InsertOne(CADOConn *pADOConn,const MAP_GridCtrl_RowData &oneRow)
{
   ASSERT(pADOConn != NULL);
   CString strSQL = _T("");
   strSQL.Format(_T("insert into %s(\
                    %s,%s,%s,%s,%s,\
                    %s,%s,%s,%s,%s,%s)\
                    values('%s','%s','%s','%s','%s',\
                    '%s','%s','%s','%s','%s','%s')"),
                    DB_TABLE_COLORPRICE,

                    DBPRICESET_KEY_cCusCode,
                    DBPRICESET_KEY_dDate,
                    DBPRICESET_KEY_iSunhao,
                    DBPRICESET_KEY_iSalePrice, 
                    DBPRICESET_KEY_iPrice,

                    DBPRICESET_KEY_cDaihao,
                    DBPRICESET_KEY_cCate,
                    DBPRICESET_KEY_fZhekou,
                    DBPRICESET_KEY_fZMDSalePrice,
                    DBPRICESET_KEY_cChenfen
                    ,DBPRICESET_KEY_fBeiLv
                    ,oneRow.find(DBPRICESET_KEY_cCusCode)->second.strValue
                    ,oneRow.find(DBPRICESET_KEY_dDate)->second.strValue      
                    ,oneRow.find(DBPRICESET_KEY_iSunhao)->second.strValue      
                    ,oneRow.find(DBPRICESET_KEY_iSalePrice)->second.strValue
                    ,oneRow.find(DBPRICESET_KEY_iPrice)->second.strValue      
                    ,oneRow.find(DBPRICESET_KEY_cDaihao)->second.strValue      
                    ,oneRow.find(DBPRICESET_KEY_cCate)->second.strValue
                    ,oneRow.find(DBPRICESET_KEY_fZhekou)->second.strValue
                    ,oneRow.find(DBPRICESET_KEY_fZMDSalePrice)->second.strValue
                    ,oneRow.find(DBPRICESET_KEY_cChenfen)->second.strValue
                    ,oneRow.find(DBPRICESET_KEY_fBeiLv)->second.strValue
                    );
   return pADOConn->ExecuteSQL(strSQL);
}

//��ȡһ�п�������		by WangZY 2017/08/22
BOOL CDBDataColorPriceSetInfoList::GetEmptyRowData(__out MAP_GridCtrl_RowData &mapEmptyRowData)
{
   mapEmptyRowData.clear();

   InsertRowData(DBPRICESET_KEY_dDate      ,_T(""),mapEmptyRowData);
   InsertRowData(DBPRICESET_KEY_iSunhao    ,_T(""),mapEmptyRowData,CB_enum_FieldData_Double2Point);
   InsertRowData(DBPRICESET_KEY_iSalePrice ,_T(""),mapEmptyRowData,CB_enum_FieldData_Double2Point);
   InsertRowData(DBPRICESET_KEY_iPrice     ,_T(""),mapEmptyRowData,CB_enum_FieldData_Double2Point);
   InsertRowData(DBPRICESET_KEY_cDaihao    ,_T(""),mapEmptyRowData);
   InsertRowData(DBPRICESET_KEY_cCate      ,_T(""),mapEmptyRowData);
   InsertRowData(DBPRICESET_KEY_cCusCode   ,_T(""),mapEmptyRowData);
   InsertRowData(DBPRICESET_KEY_ID         ,_T(""),mapEmptyRowData, CB_enum_FieldData_Int);
   InsertRowData(DBPRICESET_KEY_cCusCate   ,_T(""),mapEmptyRowData);
   InsertRowData(DBPRICESET_KEY_cCusName   ,_T(""),mapEmptyRowData);
   /*InsertRowData(DBPRICESET_KEY_cCusAbbName,_T(""),mapEmptyRowData);
   InsertRowData(DBPRICESET_KEY_vCusAbbName,_T(""),mapEmptyRowData);*/
   InsertRowData(DBPRICESET_KEY_fZhekou ,_T(""),mapEmptyRowData,CB_enum_FieldData_Double2Point);
   InsertRowData(DBPRICESET_KEY_fZMDSalePrice ,_T(""),mapEmptyRowData,CB_enum_FieldData_Double2Point);
   InsertRowData(DBPRICESET_KEY_cChenfen, _T(""),mapEmptyRowData);
   InsertRowData(DBPRICESET_KEY_fBeiLv ,_T(""),mapEmptyRowData,CB_enum_FieldData_Double2Point);

   return TRUE;
}

//�����ύ�����޸�		by WangZY 2017/08/23
BOOL CDBDataColorPriceSetInfoList::MultiModifyData(__in CADOConn *pADOConn,
   __in MAP_GridCtrl_AllData &mapAddData, 
   __in MAP_GridCtrl_AllData &mapModifyData, 
   __in MAP_GridCtrl_AllData &mapDeleteData,
   __in CString strMaker)
{
   ASSERT(pADOConn != NULL);
   CString strSQL = _T("");

   //ִ��ɾ��
   for (auto it=mapDeleteData.begin(); it!=mapDeleteData.end(); ++it)
   {
      CString strID; 
      auto itData = it->second.find(DBPRICESET_KEY_ID);
      if (itData == it->second.end())
      {
         return FALSE;
      }
      strID = itData->second.strValue;

      strSQL.Format(_T("Delete FROM %s where %s='%s'"),
         DB_TABLE_COLORPRICE,DBPRICESET_KEY_ID,strID);

      pADOConn->AppendBatchSQL(strSQL);

      CString strCusCode;
      CString strCate;
      CString strDaihao;
      CString strPrice;
      CString strSalePrice;
      CString strSunhao;
      CString strDate;
      CString strZhekou;
      CString strZMDSalePrice;
      CString strChenfen;
      CString strBeiLv;
      //�ͻ���
      itData = it->second.find(DBPRICESET_KEY_cCusCode);
      if (itData != it->second.end())
      {
         strCusCode = itData->second.strValue;
      }

      //Ʒ��
      itData = it->second.find(DBPRICESET_KEY_cCate);
      if (itData != it->second.end())
      {
         strCate = itData->second.strValue;
      }

      //����
      itData = it->second.find(DBPRICESET_KEY_cDaihao);
      if (itData != it->second.end())
      {
         strDaihao = itData->second.strValue;
      }

      //����
      itData = it->second.find(DBPRICESET_KEY_iPrice);
      if (itData != it->second.end())
      {
         strPrice = itData->second.strValue;
      }

      //���۵���
      itData = it->second.find(DBPRICESET_KEY_iSalePrice);
      if (itData != it->second.end())
      {
         strSalePrice = itData->second.strValue;
      }
      //���
      itData = it->second.find(DBPRICESET_KEY_iSunhao);
      if (itData != it->second.end())
      {
         strSunhao = itData->second.strValue;
      }
      //����
      itData = it->second.find(DBPRICESET_KEY_dDate);
      if (itData != it->second.end())
      {
         strDate = itData->second.strValue;
      }
      //ר�������۵���
      itData = it->second.find(DBPRICESET_KEY_fZMDSalePrice);
      if (itData != it->second.end())
      {
         strZMDSalePrice = itData->second.strValue;
      }
      //�ۿ�
      itData = it->second.find(DBPRICESET_KEY_fZhekou);
      if (itData != it->second.end())
      {
         strZhekou = itData->second.strValue;
      }

      //�ɷ�
      itData = it->second.find(DBPRICESET_KEY_cChenfen);
      if (itData != it->second.end())
      {
         strChenfen = itData->second.strValue;
      }
      //����
      itData = it->second.find(DBPRICESET_KEY_fBeiLv);
      if (itData != it->second.end())
      {
         strBeiLv = itData->second.strValue;
      }
      //������־sql
      CString strSQLLog;

      strSQLLog.Format(_T("insert into WorkLog(cCate,cType,cCode,cMaker,cMemo) \
                          values('�۸�','�۸�����ɾ��','%s','%s',\
                          '%s,%s,%s,%s,%s,%s,%s,%s,%s')"),
                          strID,strMaker,strID, strCusCode, strCate, strDaihao,
                          strPrice,strSalePrice,strSunhao,strDate,strMaker);

      pADOConn->AppendBatchSQL(strSQLLog);
   }


   /*BOOL bBegin = pADOConn->BeginTrans();
   if (!bBegin)
   {
   return FALSE;
   }*/

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
      auto itData = it->second.find(DBPRICESET_KEY_ID);
      if (itData == it->second.end())
      {
         bUpdateSuccess = FALSE;

         break;
      }
      strID = itData->second.strValue;

      CString strCusCode;
      CString strCate;
      CString strDaihao;
      CString strPrice;
      CString strSalePrice;
      CString strSunhao;
      CString strDate;
      CString strZhekou;
      CString strZMDSalePrice;
      CString strChenfen;
      CString strBeiLv;
      //�ͻ���
      itData = it->second.find(DBPRICESET_KEY_cCusCode);
      if (itData != it->second.end())
      {
         strCusCode = itData->second.strValue;
      }

      //Ʒ��
      itData = it->second.find(DBPRICESET_KEY_cCate);
      if (itData != it->second.end())
      {
         strCate = itData->second.strValue;
      }

      //�ɷ�
      itData = it->second.find(DBPRICESET_KEY_cChenfen);
      if (itData != it->second.end())
      {
         strChenfen = itData->second.strValue;
      }

      //����
      itData = it->second.find(DBPRICESET_KEY_cDaihao);
      if (itData != it->second.end())
      {
         strDaihao = itData->second.strValue;
      }

      //����
      itData = it->second.find(DBPRICESET_KEY_iPrice);
      if (itData != it->second.end())
      {
         strPrice = itData->second.strValue;
      }

      //���۵���
      itData = it->second.find(DBPRICESET_KEY_iSalePrice);
      if (itData != it->second.end())
      {
         strSalePrice = itData->second.strValue;
      }
      //���
      itData = it->second.find(DBPRICESET_KEY_iSunhao);
      if (itData != it->second.end())
      {
         strSunhao = itData->second.strValue;
      }
      //����
      itData = it->second.find(DBPRICESET_KEY_dDate);
      if (itData != it->second.end())
      {
         strDate = itData->second.strValue;
      }
      //ר�������۵���
      itData = it->second.find(DBPRICESET_KEY_fZMDSalePrice);
      if (itData != it->second.end())
      {
         strZMDSalePrice = itData->second.strValue;
      }
      //�ۿ�
      itData = it->second.find(DBPRICESET_KEY_fZhekou);
      if (itData != it->second.end())
      {
         strZhekou = itData->second.strValue;
      }
      //����
      itData = it->second.find(DBPRICESET_KEY_fBeiLv);
      if (itData != it->second.end())
      {
         strBeiLv = itData->second.strValue;
      }
      BOOL bHasSame = FALSE;
      CString strJudgeSQL = _T("");

      strJudgeSQL.Format(_T("select Count(*) from %s WITH (NOLOCK) \
                            where %s='%s' and %s='%s' and %s<>'%s'"),
                            DB_TABLE_COLORPRICE,DBPRICESET_KEY_cCusCode,strCusCode,DBPRICESET_KEY_cDaihao,
                            strDaihao,DBPRICESET_KEY_ID,strID);

      pADOConn->GetRecordSet(strJudgeSQL);
      while (!pADOConn->adoEOF())
      {
         int count = pADOConn->GetValueInt(0);
         if (count>0)
         {
            bHasSame = TRUE;

            break;
         }
         break;
      }
      if (bHasSame)
      {
         bUpdateSuccess = FALSE;

         break;
      }

      strSQL.Format(_T("Update %s set %s='%s',%s='%s',%s='%s',%s='%s',\
                       %s='%s',%s='%s',%s='%s',%s='%s',%s='%s',%s='%s',%s='%s' where %s='%s'"),
                       DB_TABLE_COLORPRICE
                       ,DBPRICESET_KEY_cCusCode,strCusCode
                       ,DBPRICESET_KEY_dDate,strDate    
                       ,DBPRICESET_KEY_iSunhao,strSunhao      
                       ,DBPRICESET_KEY_iSalePrice,strSalePrice
                       ,DBPRICESET_KEY_iPrice,strPrice      
                       ,DBPRICESET_KEY_cDaihao,strDaihao     
                       ,DBPRICESET_KEY_cCate,strCate
                       ,DBPRICESET_KEY_fZMDSalePrice,strZMDSalePrice
                       ,DBPRICESET_KEY_fZhekou,strZhekou
                       ,DBPRICESET_KEY_cChenfen,strChenfen
                       ,DBPRICESET_KEY_fBeiLv,strBeiLv
                       ,DBPRICESET_KEY_ID,strID);

      pADOConn->ExecuteSQL(strSQL);

      //������־sql
      CString strSQLLog;

      strSQLLog.Format(_T("insert into WorkLog(cCate,cType,cCode,cMaker,cMemo) \
                          values('�۸�','�۸������޸�','%s','%s',\
                          '%s,%s,%s,%s,%s,%s,%s,%s,%s')"),
                          strID,strMaker,strID, strCusCode, strCate, strDaihao,
                          strPrice,strSalePrice,strSunhao,strDate,strMaker);

      pADOConn->ExecuteSQL(strSQLLog);
   }

   if (!bUpdateSuccess)
   {
      //BOOL bRollback = pADOConn->RollbackTrans();

      return FALSE;
   }

   //ִ������
   BOOL bAddSuccess = TRUE;
   for (auto it=mapAddData.begin(); it!=mapAddData.end(); ++it)
   {
      CString strCusCode;
      CString strCate;
      CString strDaihao;
      CString strPrice;
      CString strSalePrice;
      CString strSunhao;
      CString strDate;
      CString strZhekou;
      CString strZMDSalePrice;
      CString strChenfen;
      CString strBeiLv;
      //�ͻ���
      auto itData = it->second.find(DBPRICESET_KEY_cCusCode);
      if (itData != it->second.end())
      {
         strCusCode = itData->second.strValue;
      }

      //Ʒ��
      itData = it->second.find(DBPRICESET_KEY_cCate);
      if (itData != it->second.end())
      {
         strCate = itData->second.strValue;
      }

      //�ɷ�
      itData = it->second.find(DBPRICESET_KEY_cChenfen);
      if (itData != it->second.end())
      {
         strChenfen = itData->second.strValue;
      }

      //����
      itData = it->second.find(DBPRICESET_KEY_cDaihao);
      if (itData != it->second.end())
      {
         strDaihao = itData->second.strValue;
      }

      //����
      itData = it->second.find(DBPRICESET_KEY_iPrice);
      if (itData != it->second.end())
      {
         strPrice = itData->second.strValue;
      }

      //���۵���
      itData = it->second.find(DBPRICESET_KEY_iSalePrice);
      if (itData != it->second.end())
      {
         strSalePrice = itData->second.strValue;
      }
      //���
      itData = it->second.find(DBPRICESET_KEY_iSunhao);
      if (itData != it->second.end())
      {
         strSunhao = itData->second.strValue;
      }
      //����
      itData = it->second.find(DBPRICESET_KEY_dDate);
      if (itData != it->second.end())
      {
         strDate = itData->second.strValue;
      }
      //ר�������۵���
      itData = it->second.find(DBPRICESET_KEY_fZMDSalePrice);
      if (itData != it->second.end())
      {
         strZMDSalePrice = itData->second.strValue;
      }
      //�ۿ�
      itData = it->second.find(DBPRICESET_KEY_fZhekou);
      if (itData != it->second.end())
      {
         strZhekou = itData->second.strValue;
      }
      //����
      itData = it->second.find(DBPRICESET_KEY_fBeiLv);
      if (itData != it->second.end())
      {
         strBeiLv = itData->second.strValue;
      }
      BOOL bHasSame = FALSE;
      CString strJudgeSQL = _T("");

      strJudgeSQL.Format(_T("select Count(*) from %s WITH (NOLOCK) \
                            where %s='%s' and %s='%s'"),
                            DB_TABLE_COLORPRICE,DBPRICESET_KEY_cCusCode,strCusCode,DBPRICESET_KEY_cDaihao,
                            strDaihao);

      pADOConn->GetRecordSet(strJudgeSQL);
      while (!pADOConn->adoEOF())
      {
         int count = pADOConn->GetValueInt(0);
         if (count>0)
         {
            bHasSame = TRUE;

            break;
         }
         break;
      }
      if (bHasSame)
      {
         bUpdateSuccess = FALSE;

         strSQL.Format(_T("Update %s set %s='%s',%s='%s',%s='%s',\
                          %s='%s',%s='%s',%s='%s',%s='%s',%s='%s',%s='%s' where %s='%s' and %s='%s'"),
                          DB_TABLE_COLORPRICE
                          ,DBPRICESET_KEY_cCate,strCate
                          ,DBPRICESET_KEY_dDate,strDate    
                          ,DBPRICESET_KEY_iSunhao,strSunhao      
                          ,DBPRICESET_KEY_iSalePrice,strSalePrice
                          ,DBPRICESET_KEY_iPrice,strPrice
                          ,DBPRICESET_KEY_fZMDSalePrice,strZMDSalePrice
                          ,DBPRICESET_KEY_fZhekou,strZhekou
                          ,DBPRICESET_KEY_cChenfen,strChenfen
                          ,DBPRICESET_KEY_cCusCode,strCusCode
                          ,DBPRICESET_KEY_cDaihao,strDaihao
                          ,DBPRICESET_KEY_fBeiLv,strBeiLv
                          );

         BOOL bExec = pADOConn->ExecuteSQL(strSQL);
         if (!bExec)
         {
            bAddSuccess = FALSE;

            break;
         }
         //������־sql
         CString strSQLLog;
         CString strID;
         strSQLLog.Format(_T("insert into WorkLog(cCate,cType,cCode,cMaker,cMemo) \
                             values('�۸�','�۸���������ת�޸�','%s','%s',\
                             '%s,%s,%s,%s,%s,%s,%s,%s,%s')"),
                             strID,strMaker,strID, strCusCode, strCate, strDaihao,
                             strPrice,strSalePrice,strSunhao,strDate,strMaker);

         pADOConn->ExecuteSQL(strSQLLog);

      }
      else
      {
         strSQL.Format(_T("insert into %s(%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s)\
                          values('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s')"),
                          DB_TABLE_COLORPRICE
                          ,DBPRICESET_KEY_cCusCode
                          ,DBPRICESET_KEY_dDate
                          ,DBPRICESET_KEY_iSunhao
                          ,DBPRICESET_KEY_iSalePrice 
                          ,DBPRICESET_KEY_iPrice
                          ,DBPRICESET_KEY_cDaihao
                          ,DBPRICESET_KEY_cCate
                          ,DBPRICESET_KEY_fZMDSalePrice
                          ,DBPRICESET_KEY_fZhekou
                          ,DBPRICESET_KEY_cChenfen
                          ,DBPRICESET_KEY_fBeiLv
                          ,strCusCode
                          ,strDate      
                          ,strSunhao      
                          ,strSalePrice
                          ,strPrice      
                          ,strDaihao      
                          ,strCate
                          ,strZMDSalePrice
                          ,strZhekou
                          ,strChenfen
                          ,strBeiLv);

         BOOL bExec = pADOConn->ExecuteSQL(strSQL);
         if (!bExec)
         {
            bAddSuccess = FALSE;

            break;
         }

         //������־sql
         CString strSQLLog;
         CString strID;
         strSQLLog.Format(_T("insert into WorkLog(cCate,cType,cCode,cMaker,cMemo) \
                             values('�۸�','�۸���������','%s','%s',\
                             '%s,%s,%s,%s,%s,%s,%s,%s,%s')"),
                             strID,strMaker,strID, strCusCode, strCate, strDaihao,
                             strPrice,strSalePrice,strSunhao,strDate,strMaker);

         pADOConn->ExecuteSQL(strSQLLog);
      }
   }

   if (!bAddSuccess)
   {
      //BOOL bRollback = pADOConn->RollbackTrans();

      return FALSE;
   }

   /*
   BOOL bCommit = pADOConn->CommitTrans();
   if (!bCommit)
   {
   return FALSE;
   }
   */

   return TRUE;
}

//�����������ݵĽӿ�		by WangZY 2017/08/27
MAP_GridCtrl_AllData CDBDataColorPriceSetInfoList::CreateGridData()
{
   MAP_GridCtrl_AllData  map_all_data;

   int nIndex = 0,nCount = GetCount();
   int nValidCount = 1;
   for (nIndex = 0;nIndex < nCount;nIndex++)
   {
      CDBDataColorPriceSet *pData = GetItem(nIndex);
      if (NULL != pData)
      {
         MAP_GridCtrl_RowData map_row_data; 

         InsertRowData(DBPRICESET_KEY_dDate      ,pData->m_str_dDate,map_row_data);
         InsertRowData(DBPRICESET_KEY_iSunhao    ,pData->m_str_iSunhao,map_row_data,CB_enum_FieldData_Double2Point);
         InsertRowData(DBPRICESET_KEY_iSalePrice ,pData->m_str_iSalePrice,map_row_data,CB_enum_FieldData_Double2Point);
         InsertRowData(DBPRICESET_KEY_iPrice     ,pData->m_str_iPrice,map_row_data,CB_enum_FieldData_Double2Point);
         InsertRowData(DBPRICESET_KEY_cDaihao    ,pData->m_str_cDaihao,map_row_data);
         InsertRowData(DBPRICESET_KEY_cCate      ,pData->m_str_cCate,map_row_data);
         InsertRowData(DBPRICESET_KEY_cCusCode   ,pData->m_str_cCusCode,map_row_data);
         InsertRowData(DBPRICESET_KEY_ID         ,pData->m_str_ID,map_row_data, CB_enum_FieldData_Int);
         InsertRowData(DBPRICESET_KEY_cCusCate   ,pData->m_str_cCusCate,map_row_data);
         InsertRowData(DBPRICESET_KEY_cCusName   ,pData->m_str_cCusName,map_row_data);
         //InsertRowData(DBPRICESET_KEY_cCusAbbName,pData->m_str_cCusAbbName,map_row_data);
         //InsertRowData(DBPRICESET_KEY_vCusAbbName,pData->m_str_vCusAbbName,map_row_data);
         InsertRowData(DBPRICESET_KEY_fZhekou ,pData->m_str_fZhekou,map_row_data,CB_enum_FieldData_Double2Point);
         InsertRowData(DBPRICESET_KEY_fZMDSalePrice     ,pData->m_str_fZMDSalePrice,map_row_data,CB_enum_FieldData_Double2Point);
         InsertRowData(DBPRICESET_KEY_cChenfen      ,pData->m_str_cChenfen,map_row_data);
         InsertRowData(DBPRICESET_KEY_fBeiLv ,pData->m_str_fBeiLv,map_row_data,CB_enum_FieldData_Double2Point);

         //�����ݲ�������������
         map_all_data.insert(make_pair(nValidCount,map_row_data));
         nValidCount++;
      }
   }

   return map_all_data;
}

void CDBDataColorPriceSetInfoList::InsertRowData( CString strFiedID,CString strValue,MAP_GridCtrl_RowData& map_row_data,ENUM_FIELDTYPE_DATA nFieldType/*= enum_FieldData_CString*/,ENUM_FIELDTYPE_CONTROL nFieldTypeCtr/*= enum_FieldCtrl_Text*/ )
{
   S_GridCtrl_FieldData s_data;		//����״̬
   s_data.strValue = strValue;
   s_data.fieldDataType = nFieldType;
   s_data.fieldCtrlType = nFieldTypeCtr;
   map_row_data.insert(make_pair(strFiedID,s_data));
}
#endif //USING_GRIDCTRL_MARK

BOOL CDBDataColorPriceSetInfoList::DeleteOneByID(CADOConn *pADOConn,CString strID)
{
   ASSERT(pADOConn != NULL);

   CString strSQL = _T("");
   strSQL.Format(_T("Delete FROM %s where %s='%s'"),DB_TABLE_COLORPRICE,DBPRICESET_KEY_ID,strID);

   return pADOConn->ExecuteSQL(strSQL);   
}
//
//float CDBDataColorPriceSetInfoList::GetSalePrice( CString m_str_cCusCode,CString cDaiHao )
//{
//	int nIndex = 0,nCount = GetCount();
//	CString strEmptyDaiHaoPrice = _T("");//���������еĿյĿͻ� ������ͬ�ĵ�һ������ 
//	for (nIndex = 0;nIndex < nCount;nIndex++)
//	{
//		auto pData = GetItem(nIndex);
//		if (NULL != pData)
//		{
//			if (0 == pData->m_str_cDaihao.CompareNoCase(cDaiHao) && strEmptyDaiHaoPrice.IsEmpty() && pData->m_str_cCusCode.IsEmpty())
//			{
//				strEmptyDaiHaoPrice = pData->m_str_iPrice;
//			}
//			if (pData->m_str_cCusCode == m_str_cCusCode && 0 == pData->m_str_cDaihao.CompareNoCase(cDaiHao))
//			{
//				return _ttof(pData->m_str_iPrice);
//			}
//		}
//	}
//
//	if (!strEmptyDaiHaoPrice.IsEmpty())
//	{
//		return _ttof(strEmptyDaiHaoPrice);
//	}
//
//	return 0;
//}

//����(�ͻ�+Ʒ��+����)��(�ͻ�+Ʒ��)��(Ʒ��+����)������ȡ�۸��Ҳ�������NULL yangjr 2018/4/22
CDBDataColorPriceSet *CDBDataColorPriceSetInfoList::GetPriceData( CString str_cCusCode,CString strCate,CString cDaiHao )
{
   int nIndex = 0,nCount = GetCount();   
   CDBDataColorPriceSet *pDataAll = nullptr;//(�ͻ�+Ʒ��+����)
   CDBDataColorPriceSet *pDataCusAndCate = nullptr;//(�ͻ�+Ʒ��)
   CDBDataColorPriceSet *pDataCateAndDaihao = nullptr;//(Ʒ��+����)
   for (nIndex = 0;nIndex < nCount;nIndex++)
   {
      CDBDataColorPriceSet *pData = GetItem(nIndex);
      if (NULL != pData)
      {
         if (str_cCusCode==pData->m_str_cCusCode 
            && strCate== pData->m_str_cCate 
            && 0 == pData->m_str_cDaihao.CompareNoCase(cDaiHao))//(�ͻ�+Ʒ��+����)
         {
            pDataAll = pData;
         }else if (str_cCusCode==pData->m_str_cCusCode 
            && strCate== pData->m_str_cCate
            && pData->m_str_cDaihao.IsEmpty())//(�ͻ�+Ʒ��+�����ǿյ�)
         {
            pDataCusAndCate = pData;
         }else if (strCate== pData->m_str_cCate 
            && 0 == pData->m_str_cDaihao.CompareNoCase(cDaiHao)
            && pData->m_str_cCusCode.IsEmpty())//(Ʒ��+����+�ͻ��ǿյ�)
         {
            pDataCateAndDaihao = pData;
         }         
      }
   }
   if (pDataAll)
   {
      return pDataAll;//(�ͻ�+Ʒ��+����) ���ȷ���
   }
   if (pDataCusAndCate)
   {
      return pDataCusAndCate;//(�ͻ�+Ʒ��) �ڶ�����
   }
   if (pDataCateAndDaihao)
   {
      return pDataCateAndDaihao;//(Ʒ��+����)��󷵻�
   }
   return nullptr;//û���ҵ����ؿ�ָ��
}

BOOL CDBDataColorPriceSetInfoList::GetPriceDataNew(CString strCate,CString strCf,CString& strPrice)
{
   strPrice = _T("0.00");
   int nIndex = 0,nCount = GetCount(); 
   for (nIndex = 0;nIndex < nCount;nIndex++)
   {
      CDBDataColorPriceSet *pData = GetItem(nIndex);
      if (NULL != pData && strCate.Trim() == pData->m_str_cCate.Trim() && strCf.Trim() == pData->m_str_cChenfen.Trim())
      {
         strPrice = pData->m_str_iSalePrice;
         return TRUE;
      }
   }
   return FALSE;
}

//CString CDBDataColorPriceSetInfoList::GetYarnSalePrice(CString strCusCode,CString strCate)
//{
//   if (strCusCode.IsEmpty() || strCate.IsEmpty())
//      return _T("0");
//
//   CString strPrice = _T("0"),strTempPrice= _T("0");
//
//   for (int nIndex = 0;nIndex < GetCount();nIndex++)
//   {
//      auto pData = GetItem(nIndex);
//      if (NULL != pData)
//      {
//         if (pData->m_str_cCate.Trim() == strCate.Trim())
//         {
//            if (pData->m_str_cCusCode.Trim() == _T(""))
//            {
//               strTempPrice =  pData->m_str_iSalePrice;
//            }
//  
//            if (pData->m_str_cCusCode.Trim() == strCusCode.Trim())
//            {
//               return pData->m_str_iSalePrice;
//            }
//         }
//      }
//   }
//
//   return strTempPrice;
//}

std::vector<CString> CDBDataColorPriceSetInfoList::GetDaiHao(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);
   vector<CString> vec_Daihao;
   CString strSQL = _T("select distinct cDaihao from ColorPrice order by cDaihao;");
   pADOConn->GetRecordSet(strSQL);

   while (!pADOConn->adoEOF())
   {
      CString strDaihao = pADOConn->GetValueString(_T("cDaihao"));
      vec_Daihao.push_back(strDaihao);
      pADOConn->MoveNext();
   }
   return vec_Daihao;
}
//��Ӧ�ͻ���Ʒ�ִ����ڼ۸����ñ����Ƿ���ڲ����ڶ�Ӧid����ͬ���� yangjr 2017-8-9
BOOL CDBDataColorPriceSetInfoList::IsExitSameDataModify(CADOConn *pADOConn,CString strCusCode,CString strDaihao,CString strID,CString strPinZhong)
{
   ASSERT(pADOConn != NULL);
   CString strSQL = _T("");
   strSQL.Format(_T("select Count(*) from %s where %s='%s' and %s='%s' and %s='%s' and %s<>'%s'"),
      DB_TABLE_COLORPRICE,DBPRICESET_KEY_cCusCode,strCusCode,DBPRICESET_KEY_cDaihao
      ,strDaihao,DBPRICESET_KEY_cCate,strPinZhong,DBPRICESET_KEY_ID,strID);
   pADOConn->GetRecordSet(strSQL);
   while (!pADOConn->adoEOF())
   {
      int count = pADOConn->GetValueInt(0);
      if (count>0)
      {
         return TRUE;
      }
      break;
   }
   return FALSE;
}
//��Ӧ�ͻ���Ʒ�ִ����ڼ۸����ñ����Ƿ������ͬ���� yangjr 2017-8-9
BOOL CDBDataColorPriceSetInfoList::IsExitSameDataAdd(CADOConn *pADOConn,CString strCusCode,CString strDaihao,CString strPinZhong)
{
   ASSERT(pADOConn != NULL);
   CString strSQL = _T("");
   strSQL.Format(_T("select Count(*) from %s where %s='%s' and %s='%s' and %s='%s'"),
      DB_TABLE_COLORPRICE,DBPRICESET_KEY_cCusCode,strCusCode
      ,DBPRICESET_KEY_cDaihao,strDaihao
      ,DBPRICESET_KEY_cCate,strPinZhong
      );
   pADOConn->GetRecordSet(strSQL);
   while (!pADOConn->adoEOF())
   {
      int count = pADOConn->GetValueInt(0);
      if (count>0)
      {
         return TRUE;
      }
      break;
   }
   return FALSE;
}

//��ȡ��ǰʱ����-��-��yangjr 2017-8-9
BOOL CDBDataColorPriceSetInfoList::GetTodayDate(CADOConn *pADOConn,CString &date)
{
   ASSERT(pADOConn != NULL);
   date = _T("");
   CString strSQL = _T("select CONVERT(varchar(10),getdate(),120)");
   pADOConn->GetRecordSet(strSQL);
   while (!pADOConn->adoEOF())
   {
      date = pADOConn->GetValueString(0);
      return TRUE;
   }
   return FALSE;
}

CString CDBDataColorPriceSetInfoList::GetClrPriceDataInfo(CADOConn* pADOConn,CString strSehao,CString strCusCode)
{
   ASSERT(pADOConn != NULL);
   if (strSehao.IsEmpty())
   {
      return _T("");
   }
   CString strDaihao = strSehao.Left(1);
   CString strSQL = _T("");
   strSQL.Format(_T("select top 1 iPrice from ColorPrice where cDaihao = '%s' and cCusCode = '%s'"),strDaihao,strCusCode);
   pADOConn->GetRecordSet(strSQL);
   if (!pADOConn->adoEOF())
   {
      return pADOConn->GetValueString(_T("iPrice"));
   }
   else
   {
      strSQL.Format(_T("select top 1 iPrice from ColorPrice where cDaihao = '%s' and cCusCode = ''"),strDaihao);
      pADOConn->GetRecordSet(strSQL);
      if (!pADOConn->adoEOF())
      {
         return pADOConn->GetValueString(_T("iPrice"));
      }
      else
      {
         strSQL.Format(_T("select top 1 iPrice from ColorPrice where cDaihao = '%s' "),strDaihao);
         pADOConn->GetRecordSet(strSQL);
         if (!pADOConn->adoEOF())
         {
            return pADOConn->GetValueString(_T("iPrice"));
         }
      }
   }
   return _T("");
}

CString CDBDataColorPriceSetInfoList::GetChengfen(CADOConn* pADOconn,CString strCusCode,CString strSehao)
{
   ASSERT(pADOconn != NULL);
   CString strSql;
   strSql.Format(_T("select t1.cChenfen from ColorPrice as t1\
                    left join Color as t2 on t1.cCate = t2.cCate\
                    where t1.cCusCode = '%s' and t2.cSehao = '%s'"),strCusCode,strSehao);
   pADOconn->GetRecordSet(strSql);
   if (!pADOconn->adoEOF())
   {
      return pADOconn->GetValueString(_T("cChenfen"));
   }
   return _T("");
}


BOOL CDBDataColorPriceSetInfoList::UpdateYarnZMJ(CADOConn *pADOConn,std::vector<CString>vecID,double fBeilv,BOOL bBeilv)
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
      ,DB_TABLE_COLORPRICE,DBPRICESET_KEY_fZMDSalePrice,
      DBPRICESET_KEY_iSalePrice,fBeilv,DBPRICESET_KEY_ID,strFilter);

   //�ۿ�
   if (bBeilv)
   {
      strSQL.Format(_T("Update %s set %s=(%s / %.2f) where %s in %s")
         ,DB_TABLE_COLORPRICE,DBPRICESET_KEY_fZMDSalePrice,
         DBPRICESET_KEY_iSalePrice,fBeilv,DBPRICESET_KEY_ID,strFilter);
   }

   return pADOConn->ExecuteSQL(strSQL);
}


void my_ColorPriceSet::ResetData()
{
   m_str_ID        = _T("") ;  //ID
   m_str_dDate     = DBS_GETDATASTR_23  ;  //����
   m_str_iSunhao   = _T("0")  ;  //���
   m_str_iSalePrice = _T("0") ;  //���۵���
   m_str_iPrice    = _T("0")  ;  //����
   m_str_cDaihao   = _T("")  ;  //Ʒ�ִ���
   m_str_cCate     = _T("")  ;  //Ʒ��
   m_str_cCusCode   = _T("") ;  //�ͻ����
   m_str_cCusName   = _T("");    //�ͻ�����
   m_str_fZMDSalePrice = _T("0") ;  //ר�������۵���
   m_str_fZhekou = _T("1") ;  //�ۿ�
   m_str_cChenfen = _T("") ;	//�ɷ�
   m_str_fBeiLv = _T("1") ;   //����    add anjie by 2018/10/25
}

CString my_ColorPriceSet::GetInsertSql()
{
   CString strField,strValues;
   strField.Format(_T("%s,%s,%s,%s,%s, %s,%s,%s,%s,%s, %s"),
      DBPRICESET_KEY_cCusCode,
      DBPRICESET_KEY_cCate,
      DBPRICESET_KEY_cDaihao,
      DBPRICESET_KEY_iPrice,
      DBPRICESET_KEY_iSalePrice,

      DBPRICESET_KEY_iSunhao,
      DBPRICESET_KEY_fZMDSalePrice,
      DBPRICESET_KEY_fZhekou,
      DBPRICESET_KEY_cChenfen,
      DBPRICESET_KEY_fBeiLv,
      
      DBPRICESET_KEY_dDate);

   strValues.Format(_T("'%s','%s','%s',%s,%s, %s,%s,%s,'%s',%s, %s"),
      m_str_cCusCode,
      m_str_cCate,
      m_str_cDaihao,
      m_str_iPrice,
      m_str_iSalePrice,

      m_str_iSunhao,
      m_str_fZMDSalePrice,
      m_str_fZhekou,
      m_str_cChenfen,
      m_str_fBeiLv,

      m_str_dDate);
   CString strSql;
   strSql.Format(_T("insert into %s (%s) values(%s);"),DB_TABLE_COLORPRICE,strField,strValues);
   return strSql;
}

CString my_ColorPriceSet::GetUpdateSql()
{
   CString strUpdate;
   strUpdate.Format(_T("%s='%s',%s='%s',%s='%s',%s=%s,%s=%s,%s=%s,%s=%s,%s=%s,%s='%s',%s=%s,%s=%s"),
      DBPRICESET_KEY_cCusCode,m_str_cCusCode,
      DBPRICESET_KEY_cCate,m_str_cCate,
      DBPRICESET_KEY_cDaihao,m_str_cDaihao,
      DBPRICESET_KEY_iPrice,m_str_iPrice,
      DBPRICESET_KEY_iSalePrice,m_str_iSalePrice,

      DBPRICESET_KEY_iSunhao,m_str_iSunhao,
      DBPRICESET_KEY_fZMDSalePrice,m_str_fZMDSalePrice,
      DBPRICESET_KEY_fZhekou,m_str_fZhekou,
      DBPRICESET_KEY_cChenfen,m_str_cChenfen,
      DBPRICESET_KEY_fBeiLv,m_str_fBeiLv,

      DBPRICESET_KEY_dDate,m_str_dDate);
   CString strSql;
   strSql.Format(_T("update %s set %s where %s = %s;"),DB_TABLE_COLORPRICE,strUpdate,DBPRICESET_KEY_ID,m_str_ID);
   return strSql;
}

CString my_ColorPriceSet::GetLog()
{
   CString strLog;
   strLog.Format(_T("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s"),
      m_str_cCusCode,m_str_cCusName,m_str_cCate,m_str_cDaihao,m_str_iPrice,m_str_iSalePrice,
      m_str_iSunhao,m_str_fZMDSalePrice,m_str_fZhekou,m_str_cChenfen,m_str_fBeiLv);
   return strLog;
}

void my_ColorPriceSet::CheckData()
{
   if (m_str_iPrice.IsEmpty())
   {
      m_str_iPrice = _T("0");
   }
   if (m_str_iSalePrice.IsEmpty())
   {
      m_str_iSalePrice = _T("0");
   }
   if (m_str_iSunhao.IsEmpty())
   {
      m_str_iSunhao = _T("0");
   }
   if (m_str_fZMDSalePrice.IsEmpty())
   {
      m_str_fZMDSalePrice = _T("0");
   }
   if (m_str_fZhekou.IsEmpty())
   {
      m_str_fZhekou = _T("0");
   }
   if (m_str_fBeiLv.IsEmpty())
   {
      m_str_fBeiLv = _T("0");
   }
}
