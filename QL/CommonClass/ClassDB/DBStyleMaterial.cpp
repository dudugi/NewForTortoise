#include "StdAfx.h"
#include "DBStyleMaterial.h"
#include "DBKeyDef.h"

#if MATERIEL_IMAGE
#include "..\ClassEx\ADOConn\DBImage.h"
#endif

using namespace Gdiplus;

//***************** CDBStyleMetarial *********************//
IMPLEMENT_SERIAL(CDBStyleMaterial,  CDataMid, 1)

   CDBStyleMaterial::CDBStyleMaterial(void)
{
#if MATERIEL_IMAGE
   m_pMaterielPic = nullptr;
#endif 

   ResetData();
}

CDBStyleMaterial::~CDBStyleMaterial(void)
{
#if MATERIEL_IMAGE
   ClearColorImage();
#endif
}

void CDBStyleMaterial::ResetData()
{
   m_nID = -1;                         //ID
   m_strStyleNo = _T("");              //款号
   m_strMaterialNo = _T("");           //物料编号
   m_strName = _T("");                 //物料名称
   m_strLevel1Type = _T("");           //大类别   
   m_strLevel2Type = _T("");           //中类别
   m_strLevel3Type = _T("");           //小类别
   m_strUnit = _T("");                 //物料单位
   m_lfCount = 0.0f;                   //物料数量
   m_strMemo = _T("");                 //物料说明
   m_strSupplier = _T("");             //供应商
   m_lfPrice = 0.0f;                   //物料单价
   m_lfTotalPrice = 0.0f;              //物料总价
   m_strBrand = _T("");                //物料品牌
   m_strChengFen = _T("");             //物料材质(成份)

#if MATERIEL_IMAGE
   ClearColorImage();
#endif
   m_bHaveDownPic = FALSE;
}

#if MATERIEL_IMAGE
void CDBStyleMaterial::ClearColorImage()
{
   if (nullptr != m_pMaterielPic)
   {
      delete m_pMaterielPic;
      m_pMaterielPic = nullptr;
   }
}
#endif



#ifdef USING_GRIDCTRL_MARK
//************************************
// <函数>:   ConvertDataToMapData
// <说明>:   数据转换为map列表数据
// <作者>:   Wangzy
// <日期>:   2019/05/25
// <Access>:public static 
// <Return>:BOOL：
// <参数>:   __out MAP_GridCtrl_RowData & mapData
// <参数>:   __in CDBStyleMaterial * pData
//************************************
BOOL CDBStyleMaterial::ConvertDataToMapData(__out MAP_GridCtrl_RowData &mapData, __in CDBStyleMaterial *pData)
{
   if (nullptr==pData)
   {
      return FALSE;
   }
   CDataMid::InsertRowData(DBStyleMetarial_ID           ,mapData,_T("%d"),pData->m_nID);
   CDataMid::InsertRowData(DBStyleMetarial_cStyleNo     ,pData->m_strStyleNo     ,mapData);                 //款号
   CDataMid::InsertRowData(DBStyleMetarial_cMaterialNo  ,pData->m_strMaterialNo  ,mapData);                 //物料编号
   CDataMid::InsertRowData(DBStyleMetarial_cName        ,pData->m_strName        ,mapData);                 //物料名称
   CDataMid::InsertRowData(DBStyleMetarial_cLevel1Type  ,pData->m_strLevel1Type  ,mapData);                 //大类别   
   CDataMid::InsertRowData(DBStyleMetarial_cLevel2Type  ,pData->m_strLevel2Type  ,mapData);                 //中类别
   CDataMid::InsertRowData(DBStyleMetarial_cLevel3Type  ,pData->m_strLevel3Type  ,mapData);                 //小类别
   CDataMid::InsertRowData(DBStyleMetarial_cUnit        ,pData->m_strUnit        ,mapData);                 //物料单位
   CDataMid::InsertRowData(DBStyleMetarial_fCount       ,mapData,CB_enum_FieldData_Double3Point,CB_enum_FieldCtrl_Text, FORMAT_FLOAT3DOT     ,pData->m_lfCount);        //物料数量
   CDataMid::InsertRowData(DBStyleMetarial_cMemo        ,pData->m_strMemo        ,mapData);                 //物料说明
   CDataMid::InsertRowData(DBStyleMetarial_cSupplier    ,pData->m_strSupplier    ,mapData);                 //供应商
   CDataMid::InsertRowData(DBStyleMetarial_fPrice       ,mapData, _T("%.2f")     ,pData->m_lfPrice);        //物料单价
   CDataMid::InsertRowData(DBStyleMetarial_fTotalPrice  ,mapData, _T("%.2f")     ,pData->m_lfTotalPrice);   //物料总价
   CDataMid::InsertRowData(DBStyleMetarial_cBrand       ,pData->m_strBrand       ,mapData);                 //物料品牌
   CDataMid::InsertRowData(DBStyleMetarial_cChengFen    ,pData->m_strChengFen    ,mapData);                 //物料材质(成份)

   return TRUE;
}
#endif


void CDBStyleMaterial::Copy(CDBStyleMaterial *pData)
{
   ASSERT(pData != NULL);
   m_nID             = pData->m_nID;                     //ID
   m_strStyleNo      = pData->m_strStyleNo;              //款号
   m_strMaterialNo   = pData->m_strMaterialNo;           //物料编号
   m_strName         = pData->m_strName;                 //物料名称
   m_strLevel1Type   = pData->m_strLevel1Type;           //大类别   
   m_strLevel2Type   = pData->m_strLevel2Type;           //中类别
   m_strLevel3Type   = pData->m_strLevel3Type;           //小类别
   m_strUnit         = pData->m_strUnit;                 //物料单位
   m_lfCount         = pData->m_lfCount;                 //物料数量
   m_strMemo         = pData->m_strMemo;                 //物料说明
   m_strSupplier     = pData->m_strSupplier;             //供应商
   m_lfPrice         = pData->m_lfPrice;                 //物料单价
   m_lfTotalPrice    = pData->m_lfTotalPrice;            //物料总价
   m_strBrand        = pData->m_strBrand;                //物料品牌
   m_strChengFen     = pData->m_strChengFen;             //物料材质(成份)

#if MATERIEL_IMAGE
   ClearColorImage();
   if (pData->m_pMaterielPic)
   {
      m_pMaterielPic = pData->m_pMaterielPic->Clone();
   }
   m_bHaveDownPic = pData->m_bHaveDownPic;//图片是否已下载 
#endif

}

void CDBStyleMaterial::GetAllDBInfo(CADOConn* pADOConn,bool bNeedPic/* = false*/)
{
   ASSERT(pADOConn != NULL);
   m_nID             = pADOConn->GetValueInt(DBStyleMetarial_ID);  
   m_strStyleNo      = pADOConn->GetValueString(DBStyleMetarial_cStyleNo       );
   m_strMaterialNo   = pADOConn->GetValueString(DBStyleMetarial_cMaterialNo    );
   m_strName         = pADOConn->GetValueString(DBStyleMetarial_cName          );
   m_strLevel1Type   = pADOConn->GetValueString(DBStyleMetarial_cLevel1Type    );
   m_strLevel2Type   = pADOConn->GetValueString(DBStyleMetarial_cLevel2Type    );
   m_strLevel3Type   = pADOConn->GetValueString(DBStyleMetarial_cLevel3Type    );
   m_strUnit         = pADOConn->GetValueString(DBStyleMetarial_cUnit          );
   m_lfCount         = pADOConn->GetValueDouble(DBStyleMetarial_fCount         );
   m_strMemo         = pADOConn->GetValueString(DBStyleMetarial_cMemo          );
   m_strSupplier     = pADOConn->GetValueString(DBStyleMetarial_cSupplier      );
   m_lfPrice         = pADOConn->GetValueDouble(DBStyleMetarial_fPrice         );
   m_lfTotalPrice    = pADOConn->GetValueDouble(DBStyleMetarial_fTotalPrice    );
   m_strBrand        = pADOConn->GetValueString(DBStyleMetarial_cBrand         );
   m_strChengFen     = pADOConn->GetValueString(DBStyleMetarial_cChengFen      );
   
   if (bNeedPic)
   {
#if MATERIEL_IMAGE
      ClearColorImage();
      CDBImage oImage;
      m_pMaterielPic = oImage.NewImageFromDB(DBMateriel_Key_cPic, pADOConn->GetRecoPtr());

#endif 
      m_bHaveDownPic = true;
   }
   else
   {
      m_bHaveDownPic = false;
   }
}

BOOL CDBStyleMaterial::InsetAllDBInfo(CADOConn* pADOConn)
{
   ASSERT(pADOConn != NULL);
   BOOL bRet =  pADOConn->ExecuteSQL(GetInsertSql());
   if (!bRet)
   {
      return FALSE;
   }

   if (m_bHaveDownPic
      &&nullptr != m_pMaterielPic)
   {
      CDBImage oImage;
      CString strSQL;
      strSQL.Format(_T("select %s from %s where %s = @@IDENTITY ;"),
         DBStyleMetarial_cPic,
         DB_TABLE_STYLEMATERIAL, 
         DBStyleMetarial_ID
         );
      pADOConn->GetRecordSet(strSQL);
      oImage.LoadImage2DB(DBStyleMetarial_cPic,m_pMaterielPic,
         pADOConn->GetRecoPtr());
   }
   
   return TRUE;
}

BOOL CDBStyleMaterial::UpdateAllDBInfo(CADOConn* pADOConn)
{
   ASSERT(pADOConn != NULL);
   return pADOConn->ExecuteSQL(GetUpdateSql());
}

BOOL CDBStyleMaterial::DeleteAllDBInfo(CADOConn* pADOConn)
{
   ASSERT(pADOConn != NULL);
   return pADOConn->ExecuteSQL(GetDeleteSql());
}

CString CDBStyleMaterial::GetDeleteByStyleNoSql(const CString & strStyleNo)
{
   CString strSQL = _T("");
   strSQL.Format(_T("delete from %s where %s='%s';"),DB_TABLE_STYLEMATERIAL,
      DBStyleMetarial_cStyleNo,strStyleNo);
   return strSQL;
}

CString CDBStyleMaterial::GetInsertSql()
{
   CString strSql = _T("");
   strSql.Format(
      _T("insert into %s (%s,%s,%s,%s,%s,\
         %s,%s,%s,%s,%s,\
         %s,%s,%s,%s) \
      values ('%s','%s','%s','%s','%s',\
      '%s','%s','%.4f','%s','%s',\
      '%.2f','%.2f','%s','%s'); "),

      DB_TABLE_STYLEMATERIAL,

      DBStyleMetarial_cStyleNo       ,
      DBStyleMetarial_cMaterialNo    ,
      DBStyleMetarial_cName          ,
      DBStyleMetarial_cLevel1Type    ,
      DBStyleMetarial_cLevel2Type    ,

      DBStyleMetarial_cLevel3Type    ,
      DBStyleMetarial_cUnit          ,
      DBStyleMetarial_fCount         ,
      DBStyleMetarial_cMemo          ,
      DBStyleMetarial_cSupplier      ,

      DBStyleMetarial_fPrice         ,
      DBStyleMetarial_fTotalPrice    ,
      DBStyleMetarial_cBrand         ,
      DBStyleMetarial_cChengFen      ,

      m_strStyleNo              ,
      m_strMaterialNo           ,
      m_strName                 ,
      m_strLevel1Type           ,
      m_strLevel2Type           ,

      m_strLevel3Type           ,
      m_strUnit                 ,
      m_lfCount                 ,
      m_strMemo                 ,
      m_strSupplier             ,

      m_lfPrice                 ,
      m_lfTotalPrice            ,
      m_strBrand                ,
      m_strChengFen
      );

   return strSql;
}

CString CDBStyleMaterial::GetUpdateSql()
{
   CString strSql = _T("");
   //update StyleMetarial set cStyleNo = '18G200',cColorNo = 'color7',iIsPrimary = 1,iSortId = 1 where ID = 7"
   //strSql.Format(_T("update %s set %s = '%s',%s = '%s',%s = %d,%s = %d where %s = %d"),DB_TABLE_STYLEMATERIAL,
   //                  DBStyleMetarial_cStyleNo,m_strStyleNo,
   //                  DBStyleMetarial_cColorNo,m_strColorNo,
   //                  DBStyleMetarial_iIsPrimary,m_iIsPrimary,
   //                  DBStyleMetarial_iSortId,m_iSortID,
   //                  DBStyleMetarial_ID,m_id);
   return strSql;
}

CString CDBStyleMaterial::GetDeleteSql()
{
   CString strSql = _T("");
   strSql.Format(_T("delete from %s where %s = %d;"),DB_TABLE_STYLEMATERIAL,DBStyleMetarial_ID,m_nID);
   
   return strSql;
}

void CDBStyleMaterial::GetImageFromDB(CADOConn* pAdo)
{
   ASSERT(pAdo != NULL);
   CString strSql = _T("");
   strSql.Format(_T(" select top 1 cPic from MaterielInfo where ID = '%s'"),m_strMaterialNo);
   pAdo->GetRecordSet(strSql);
   if (!pAdo->adoEOF())
   {
      ClearColorImage();
      CDBImage oImage;
      m_pMaterielPic = oImage.NewImageFromDB(DBMateriel_Key_cPic, pAdo->GetRecoPtr());
      m_bHaveDownPic = TRUE;
   }
}

//***************** CDBStyleMetarialList *********************//

IMPLEMENT_SERIAL(CDBStyleMaterialList,  CDataMid, 1)

std::shared_ptr<CDBStyleMaterialList> CDBStyleMaterialList::sm_inst;

CDBStyleMaterialList::CDBStyleMaterialList(void)
{

}

CDBStyleMaterialList::~CDBStyleMaterialList(void)
{

}

CDBStyleMaterialList * CDBStyleMaterialList::Instance()
{
   if(sm_inst.get() == 0)
      sm_inst = shared_ptr<CDBStyleMaterialList>(new CDBStyleMaterialList);

   return sm_inst.get();
}

#ifdef USING_GRIDCTRL_MARK

//************************************
// <函数>:   ConvertListToMap
// <说明>:   List列表转换为Map列表
// <作者>:   Wangzy
// <日期>:   2019/05/25
// <Access>:public static 
// <Return>:BOOL：
// <参数>:   __out MAP_GridCtrl_AllData & all_data
// <参数>:   __in CDBStyleMaterialList & listData
//************************************
BOOL CDBStyleMaterialList::ConvertListToMap(__out MAP_GridCtrl_AllData &mapData,__in CDBStyleMaterialList &listData)
{
   mapData.clear();
   int nCount = listData.GetCount();
   for (int nIndex=0; nIndex<nCount; ++nIndex)
   {
      auto pData = listData.GetItem(nIndex);
      if (nullptr == pData)
      {
         continue;
      }
      MAP_GridCtrl_RowData mapRowData;
      BOOL bSuc = CDBStyleMaterial::ConvertDataToMapData(mapRowData,pData);
      if (bSuc)
      {
         mapData.insert(make_pair(nIndex,mapRowData));
      }
   }

   return TRUE;
}

BOOL CDBStyleMaterialList::GetStyleMaterialInfo(CADOConn* pADOConn,CString strStyleNo,MAP_GridCtrl_AllData& all_data)
{
   ASSERT(pADOConn != NULL);
   ASSERT(!strStyleNo.IsEmpty());
   all_data.clear();

   CString strSql = _T("");
   strSql.Format(_T("select * from StyleMetarial where cStyleNo = '%s' order by iSortId;"),strStyleNo);
   pADOConn->GetRecordSet(strSql);

   int iCount = 1;
   int iLastSortID = -1;
   MAP_GridCtrl_RowData row_data;
   //while(!pADOConn->adoEOF())
   //{
   //   //int iSortID = pADOConn->GetValueInt(DBStyleMetarial_iSortId);
   //   //int iIsPrimary = pADOConn->GetValueInt(DBStyleMetarial_iIsPrimary);
   //   //CString strColor = pADOConn->GetValueString(DBStyleMetarial_cColorNo);
   //   if (iLastSortID < 0 )
   //   {
   //      iLastSortID = iSortID;
   //   }
   //   if (iLastSortID >=0 && iLastSortID != iSortID)
   //   {
   //      CString strColorTemp = _T("");
   //      while(iCount <= 6)
   //      {
   //         switch(iCount)
   //         {
   //         case 1://配色1
   //            InsertRowData(XMLCFG_MI_KEY_PEISE1,strColorTemp,row_data);
   //            break;
   //         case 2://配色2
   //            InsertRowData(XMLCFG_MI_KEY_PEISE2,strColorTemp,row_data);
   //            break;
   //         case 3://配色3
   //            InsertRowData(XMLCFG_MI_KEY_PEISE3,strColorTemp,row_data);
   //            break;
   //         case 4://配色4
   //            InsertRowData(XMLCFG_MI_KEY_PEISE4,strColorTemp,row_data);
   //            break;
   //         case 5://配色5
   //            InsertRowData(XMLCFG_MI_KEY_PEISE5,strColorTemp,row_data);
   //            break;
   //         case 6://配色6
   //            InsertRowData(XMLCFG_MI_KEY_PEISE6,strColorTemp,row_data);
   //            break;
   //         }
   //         ++iCount;
   //      }  
   //      auto itr_zhuse = row_data.find(XMLCFG_MI_KEY_ZHUSE);
   //      if (itr_zhuse == row_data.end())
   //      {
   //         InsertRowData(XMLCFG_MI_KEY_ZHUSE,strColorTemp,row_data);
   //      }
   //      all_data.insert(make_pair(all_data.size(),row_data));
   //      row_data.clear();
   //      iCount = 1;
   //      iLastSortID = iSortID;
   //   }

   //   if (iIsPrimary == 1) //主色
   //   {
   //      InsertRowData(XMLCFG_MI_KEY_ZHUSE,strColor,row_data);
   //   }
   //   else
   //   {
   //      switch(iCount)
   //      {
   //      case 1://配色1
   //         InsertRowData(XMLCFG_MI_KEY_PEISE1,strColor,row_data);
   //         break;
   //      case 2://配色2
   //         InsertRowData(XMLCFG_MI_KEY_PEISE2,strColor,row_data);
   //         break;
   //      case 3://配色3
   //         InsertRowData(XMLCFG_MI_KEY_PEISE3,strColor,row_data);
   //         break;
   //      case 4://配色4
   //         InsertRowData(XMLCFG_MI_KEY_PEISE4,strColor,row_data);
   //         break;
   //      case 5://配色5
   //         InsertRowData(XMLCFG_MI_KEY_PEISE5,strColor,row_data);
   //         break;
   //      case 6://配色6
   //         InsertRowData(XMLCFG_MI_KEY_PEISE6,strColor,row_data);
   //         break;
   //      }
   //      ++iCount;
   //   }
   //   pADOConn->MoveNext();   
   //}

   CString strColorTemp = _T("");
   while(iCount <= 6)
   {
      switch(iCount)
      {
      case 1://配色1
         InsertRowData(XMLCFG_MI_KEY_PEISE1,strColorTemp,row_data);
         break;
      case 2://配色2
         InsertRowData(XMLCFG_MI_KEY_PEISE2,strColorTemp,row_data);
         break;
      case 3://配色3
         InsertRowData(XMLCFG_MI_KEY_PEISE3,strColorTemp,row_data);
         break;
      case 4://配色4
         InsertRowData(XMLCFG_MI_KEY_PEISE4,strColorTemp,row_data);
         break;
      case 5://配色5
         InsertRowData(XMLCFG_MI_KEY_PEISE5,strColorTemp,row_data);
         break;
      case 6://配色6
         InsertRowData(XMLCFG_MI_KEY_PEISE6,strColorTemp,row_data);
         break;
      }
      ++iCount;
   }  
   auto itr_zhuse = row_data.find(XMLCFG_MI_KEY_ZHUSE);
   if (itr_zhuse == row_data.end())
   {
      InsertRowData(XMLCFG_MI_KEY_ZHUSE,strColorTemp,row_data);
   }
   all_data.insert(make_pair(all_data.size(),row_data));
   return TRUE;
}

//************************************
// <函数>:   GetStyleMaterialInfo
// <说明>:   获取款式的原辅料信息
// <作者>:   Wangzy
// <日期>:   2019/05/25
// <Access>:public 
// <Return>:int：小于0：获取失败; 大等于0：获取成功，并返回获取的数量;
// <参数>:   __in CADOConn * pADOConn
// <参数>:   __in const CString & strStyleNo
//************************************
int CDBStyleMaterialList::GetStyleMaterialInfo(__in CADOConn* pADOConn, __in const CString &strStyleNo)
{
   ASSERT(pADOConn != NULL);
   if (strStyleNo.IsEmpty())
   {
      return -1;
   }
   CString strSQL;

   strSQL.Format(_T("select * from %s where %s='%s' ;"),
      DB_TABLE_STYLEMATERIAL,
      DBStyleMetarial_cStyleNo,
      strStyleNo);

   pADOConn->GetRecordSet(strSQL);
   while (!pADOConn->adoEOF())
   {
      CDBStyleMaterial data;
      data.GetAllDBInfo(pADOConn,true);
      AddItem(&data);
      pADOConn->MoveNext();
   }
   int nRet = GetCount();

   return nRet;
}

//************************************
// <函数>:   GetOrgMaterialInfo
// <说明>:   获取可加入款式的原辅料信息
// <作者>:   Wangzy
// <日期>:   2019/05/27
// <Access>:public 
// <Return>:BOOL：
// <参数>:   __in CADOConn * pADOConn
// <参数>:   __in const CString & strLeve1Type ：一级类别（原料，辅料，其他）
// <参数>:   __in const CString & strLeve2Type ：二级类别 (辅料里的二级类别：)
// <参数>:   __in const CString & strLeve3Type ：三级类别 (辅料里的三级类别)
//************************************
BOOL CDBStyleMaterialList::GetOrgMaterialInfo(__in CADOConn* pADOConn,
   __in const CString &strLevel1Type,__in const CString &strLevel2Type,__in const CString &strLevel3Type)
{
   ASSERT(pADOConn != NULL);
   
   //辅料的过滤信息	by WangZY 2019/05/27
   CString strFilterSQL;
   if (!strLevel1Type.IsEmpty()
      &&strLevel1Type == _T("辅料"))
   {
      strFilterSQL.Format(_T(" where %s='%s' "),
         DBMateriel_Key_cLevel1Type,
         strLevel1Type);

      if (!strLevel2Type.IsEmpty())
      {
         strFilterSQL.AppendFormat(_T(" and %s='%s'"),
            DBMateriel_Key_cLevel2Type,
            strLevel2Type);
      }

      if (!strLevel3Type.IsEmpty())
      {
         strFilterSQL.AppendFormat(_T(" and %s='%s'"),
            DBMateriel_Key_cLevel3Type,
            strLevel3Type);
      }
   }

   //辅料信息   	by WangZY 2019/05/27
   CString strSubsidiarySQL;
   strSubsidiarySQL.Format(
      _T("select -1 as ID,'' as cStyleNo,m.ID as cMaterialNo,m.cName,m.cLevel1Type,m.cLevel2Type,\
      m.cLevel3Type,m.cUnit,0.0 as fCount,m.cMemo,m.cSupplier,m.nPrice as fPrice,0.0 as fTotalPrice,m.cBrand,\
      m.cChengFen\
      from MaterielInfo	as m %s "),
      strFilterSQL);

   if (!strLevel1Type.IsEmpty()
      &&strLevel1Type == _T("原料"))
   {
      if (!strLevel2Type.IsEmpty())
      {
         strFilterSQL.AppendFormat(_T(" where %s='%s'"),
            DBPinZhongSetting_cCate,
            strLevel2Type);
      }
   }

   //原料信息   	by WangZY 2019/05/27
   CString strRawSQL;
   strRawSQL.Format(
      _T("select -1 as ID,'' as cStyleNo, convert(varchar(20),p.ID) as cMaterialNo,p.cProductName as cName,\
      '原料' as cLevel1Type, p.cCate as cLevel2Type,'' as cLevel3Type, '千克' as cUnit,\
      0.0 as fCount,p.cZhiXingBiaoZun as cMemo,'' as cSupplier,p.cChengBenPrice as fPrice,\
      0.0 as fTotalPrice,'' as cBrand, p.cChenfen as cChengFen \
      from PinZhongSetting as P %s "),strFilterSQL);


   CString strSQL;
   if (strLevel1Type.IsEmpty())
   {
      strSQL.Format(_T(" %s union all %s ;"),strSubsidiarySQL,strRawSQL);
   }
   else if (strLevel1Type == _T("辅料"))
   {
      strSQL.Format(_T(" %s ;"),strSubsidiarySQL);
   }
   else if (strLevel1Type == _T("原料"))
   {
      strSQL.Format(_T(" %s ;"),strRawSQL);
   }
   else
   {
      return FALSE;
   }

   pADOConn->GetRecordSet(strSQL);
   while (!pADOConn->adoEOF())
   {
      CDBStyleMaterial data;
      data.GetAllDBInfo(pADOConn,false);
      AddItem(&data);
      pADOConn->MoveNext();
   }
   int nRet = GetCount();

   return nRet;


}

BOOL CDBStyleMaterialList::SaveStyleMaterialInfo(CADOConn* pADOConn,CString strStyleNo,MAP_GridCtrl_AllData all_data)
{
   ASSERT(pADOConn != NULL);
   CString strSql_Del;
   strSql_Del.Format(_T("delete from %s where %s = '%s';"),DB_TABLE_STYLEMATERIAL,DBStyleMetarial_cStyleNo,strStyleNo);
   pADOConn->ExecuteSQL(strSql_Del);
   //if (all_data.size() > 0)
   //{
   //   for (auto itr_row = all_data.begin(); itr_row != all_data.end(); ++itr_row)
   //   {
   //      CString strSql_Insert = _T("");
   //      CDBStyleMaterial obj;
 
   //      for (auto itr_col = itr_row->second.begin(); itr_col != itr_row->second.end(); ++itr_col)
   //      {
   //         obj.m_strStyleNo = strStyleNo;
   //         obj.m_strColorNo = itr_col->second.strValue;
   //         obj.m_iSortID = itr_row->first+1;      //从1开始
   //         if (itr_col->first != XMLCFG_MI_KEY_ZHUSE && !obj.m_strColorNo.IsEmpty())   //配色为空，则不插数据
   //         {
   //            obj.m_iIsPrimary = 0;
   //            strSql_Insert += obj.GetInsertSql();
   //         }
   //      }

   //      //主色
   //      auto itr_zhuse = itr_row->second.find(XMLCFG_MI_KEY_ZHUSE);
   //      if (itr_zhuse != itr_row->second.end())
   //      {
   //         obj.m_iIsPrimary = 1;
   //         obj.m_strStyleNo = strStyleNo;
   //         obj.m_strColorNo = itr_zhuse->second.strValue;
   //         obj.m_iSortID = itr_row->first+1;      //从1开始

   //         if (strSql_Insert.IsEmpty() && obj.m_strColorNo.IsEmpty())  //配色为空，主色为空，则不写数据
   //         {
   //            continue;
   //         }
   //         strSql_Insert += obj.GetInsertSql();
   //      }
   //      pADOConn->ExecuteSQL(strSql_Insert);
   //   }
   //}
   return TRUE;
}
#endif

BOOL CDBStyleMaterialList::ClearStyleMaterialInfo(CADOConn* pADOConn,CString strStyleNo)
{
   ASSERT(pADOConn != NULL);
   CString strSql_Del;
   strSql_Del.Format(_T("delete from %s where %s = '%s';"),DB_TABLE_STYLEMATERIAL,DBStyleMetarial_cStyleNo,strStyleNo);
   return pADOConn->ExecuteSQL(strSql_Del);
}

BOOL CDBStyleMaterialList::IsStyleMaterialInfoExist(CADOConn* pADOConn,CString strStyleNo)
{
   ASSERT(pADOConn != NULL);
   CString strSql;
   strSql.Format(_T("select count(*) as num from %s where %s = '%s';"),DB_TABLE_STYLEMATERIAL,DBStyleMetarial_cStyleNo,strStyleNo);
   pADOConn->GetRecordSet(strSql);
   if (!pADOConn->adoEOF())
   {
      int count = pADOConn->GetValueInt(_T("num"));
      if (count>0)
      {
         return TRUE;
      }
      return FALSE;
   }
   return TRUE;
}

CDBStyleMaterial* CDBStyleMaterialList::GetItem(int nIndex)
{
   if (nIndex<0||nIndex>=GetCount())
      return NULL;
   return (CDBStyleMaterial*)GetAt(FindIndex(nIndex));
}


CDBStyleMaterial* CDBStyleMaterialList::GetItemByMaterialNo(const CString & strMaterialNo)
{
   int nCount = GetCount();
   for (int nIndex = 0;nIndex < nCount;++nIndex)
   {
      auto pData = GetItem(nIndex);
      if (NULL != pData && pData->m_strMaterialNo == strMaterialNo)
      {
         return pData;
      }
   }
   return NULL;
}

void CDBStyleMaterialList::AddItem(CDBStyleMaterial* pItem)
{
   CDBStyleMaterial*pData=new CDBStyleMaterial;
   pData->Copy(pItem);
   AddTail(pData);
}

void CDBStyleMaterialList::DeleteItem(int nIndex)
{
   if (nIndex<0||nIndex>GetCount())
      return;
   CDBStyleMaterial *pObject=(CDBStyleMaterial*)GetItem(nIndex);
   delete pObject;
   pObject=NULL;
   RemoveAt(FindIndex(nIndex));
}

void CDBStyleMaterialList::DeleteItemByMaterialNo(const CString & strMaterialNo)
{
   int nCount = GetCount();
   for (int nIndex = 0;nIndex < nCount;++nIndex)
   {
      auto pData = GetItem(nIndex);
      if (NULL != pData && pData->m_strMaterialNo == strMaterialNo)
      {
         DeleteItem(nIndex);
         break;
      }
   }
}

void CDBStyleMaterialList::Copy(CDBStyleMaterialList * plst)
{
   Empty();
   int nCount = plst->GetCount();
   for (int nIndex = 0;nIndex < nCount;++nIndex)
   {
      auto pData = plst->GetItem(nIndex);
      if (NULL != pData)
      {
         AddItem(pData);
      }
   }

}

BOOL CDBStyleMaterialList::SaveStyleMaterial(CADOConn* pADOConn,CString strStyleNo)
{
   if (!pADOConn)
   {
      return FALSE;
   }
   int count = GetCount();
   if (count>0)
   {
      pADOConn->BeginTrans();
      BOOL bSuccess = TRUE;
      for (int index=0;index<count;++index)
      {
         CDBStyleMaterial *pData = GetItem(index);
         if (pData)
         {
            bSuccess = pData->InsetAllDBInfo(pADOConn);
         }
         if (!bSuccess)
         {
            break;
         }
      }
      if (bSuccess)
      {
         pADOConn->CommitTrans();
         return TRUE;
      }else
      {
         pADOConn->RollbackTrans();
         return FALSE;
      }
   }else
   {
      return FALSE;
   }
   
}



