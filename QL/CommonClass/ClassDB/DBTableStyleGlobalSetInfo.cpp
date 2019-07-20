#include "StdAfx.h"
#include "DBKeyDef.h"
#include "rnfile.h"
#include "DBTableStyleGlobalSetInfo.h"
#include "CGridCtrlTableAttributeOp.h"
//#include "DBDataColSet.h"
//#include "DBTableStyleAttrSet.h"
#include <set>

IMPLEMENT_SERIAL(DBTableStyleGlobalSetInfo,  CDataMid, 1)
IMPLEMENT_SERIAL(DBTableStyleGlobalSetInfoList,  CDataListMid, 1)

std::shared_ptr<DBTableStyleGlobalSetInfoList> DBTableStyleGlobalSetInfoList::sm_inst;

DBTableStyleGlobalSetInfo::DBTableStyleGlobalSetInfo()
{
   ResetData();
} 

DBTableStyleGlobalSetInfo::~DBTableStyleGlobalSetInfo()
{
}

void DBTableStyleGlobalSetInfo::ResetData()
{
   m_nID = -1;
   m_cXmlFileName = _T("");   //xml文件名
   m_cXmlDesc     = _T("");   //xml说明
   m_cInitSettingXml = _T("");//出厂设置XML内容
   m_cRealTimeXml = _T("");   //实时的xml内容
   m_cUpdateTime = _T("");    //实时更新时间
}

void DBTableStyleGlobalSetInfo::Copy(DBTableStyleGlobalSetInfo *pData)
{
	ASSERT(pData != NULL);
	CDataMid::Copy(pData);

	m_nID		=	pData->m_nID;
   m_cXmlFileName		=	pData->m_cXmlFileName;
   m_cXmlDesc		=	pData->m_cXmlDesc;
   m_cInitSettingXml		=	pData->m_cInitSettingXml;
   m_cRealTimeXml		=	pData->m_cRealTimeXml;
   m_cUpdateTime		=	pData->m_cUpdateTime;
}

BOOL DBTableStyleGlobalSetInfo::GetAllDBInfo(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);

	BOOL bRet = TRUE;

	if (NULL == pADOConn)
	{
		bRet = FALSE;
	}
	else
	{
		m_nID			         =	pADOConn->GetValueInt(DBTableStyleGlobalSet_key_ID);
      m_cXmlFileName			=	pADOConn->GetValueString(DBTableStyleGlobalSet_key_cXmlFileName);
      m_cXmlDesc			=	pADOConn->GetValueString(DBTableStyleGlobalSet_key_cXmlDesc);
      m_cInitSettingXml			=	pADOConn->GetValueString(DBTableStyleGlobalSet_key_cInitSettingXmlFile);
      m_cRealTimeXml			=	pADOConn->GetValueString(DBTableStyleGlobalSet_key_cRealTimeXmlFile);
      m_cUpdateTime			=	pADOConn->GetValueString(DBTableStyleGlobalSet_key_dUpdateTime);

		bRet = TRUE;
	}

	return bRet;
}


BOOL DBTableStyleGlobalSetInfo::InsertAllDBInfo( CADOConn *pADOConn )
{
	ASSERT(pADOConn != NULL);
	BOOL bRet = TRUE;

	if (pADOConn->ExecuteSQL(GetInsertSQL()))
	{
      pADOConn->GetRecordSet(_T("SELECT @@IDENTITY AS ID"));
      if (!pADOConn->adoEOF())
      {
         m_nID = pADOConn->GetValueInt(DBTableStyleGlobalSet_key_ID);
      }

		bRet = TRUE;
	}
	else
	{
		bRet = FALSE;
	}

	return bRet;
}

BOOL DBTableStyleGlobalSetInfo::DeleteInfoByID(CADOConn *pADOConn)
{
   CString sqlStr = _T("");
   sqlStr.Format(_T("delete from %s where ID = %d") , DB_TABLE_STYLE_GLOBAL_SET ,m_nID);

   return pADOConn->ExecuteSQL(sqlStr);
}

BOOL DBTableStyleGlobalSetInfo::UpdateInfoByID(CADOConn *pADOConn )
{
   CString sqlStr = _T("");
   sqlStr.Format(_T("update %s set %s = '%s' , %s = '%s' , %s = '%s' , %s = '%s' , %s = '%s' where ID = %d") , DB_TABLE_STYLE_GLOBAL_SET ,
      DBTableStyleGlobalSet_key_cXmlFileName , m_cXmlFileName,
      DBTableStyleGlobalSet_key_cXmlDesc , m_cXmlDesc,
      DBTableStyleGlobalSet_key_cInitSettingXmlFile , m_cInitSettingXml,
      DBTableStyleGlobalSet_key_cRealTimeXmlFile , m_cRealTimeXml,
      DBTableStyleGlobalSet_key_dUpdateTime , m_cUpdateTime, m_nID);

   return pADOConn->ExecuteSQL(sqlStr);
}

CString DBTableStyleGlobalSetInfo::GetInsertSQL()
{
   CString strSQL = _T(""),strFormat = _T(""),strValue = _T("");

   strFormat.Format(_T("%s , %s , %s , %s , %s"),
   DBTableStyleGlobalSet_key_cXmlFileName, 
   DBTableStyleGlobalSet_key_cXmlDesc, 
   DBTableStyleGlobalSet_key_cInitSettingXmlFile, 
   DBTableStyleGlobalSet_key_cRealTimeXmlFile, 
   DBTableStyleGlobalSet_key_dUpdateTime
   );

   strValue.Format(_T(" '%s','%s','%s','%s','%s' "),
   m_cXmlFileName , m_cXmlDesc,
   m_cInitSettingXml, m_cRealTimeXml,
   m_cUpdateTime
   );

   strSQL.Format(_T("insert into %s (%s) values(%s)"),DB_TABLE_STYLE_GLOBAL_SET ,strFormat,strValue);

	return strSQL;
}

//DBTableStyleGlobalSetInfoList
DBTableStyleGlobalSetInfoList::DBTableStyleGlobalSetInfoList()
{
}

DBTableStyleGlobalSetInfoList::~DBTableStyleGlobalSetInfoList()
{
}

DBTableStyleGlobalSetInfo*  DBTableStyleGlobalSetInfoList::GetItem(int nIndex)
{
   if (nIndex<0||nIndex>=GetCount())
      return NULL;
   return (DBTableStyleGlobalSetInfo*)GetAt(FindIndex(nIndex));
}

void DBTableStyleGlobalSetInfoList:: AddItem(DBTableStyleGlobalSetInfo* pItem)
{
   DBTableStyleGlobalSetInfo*pData=new DBTableStyleGlobalSetInfo;
   pData->Copy(pItem);
   AddTail(pData);
}

void DBTableStyleGlobalSetInfoList::DeleteItem(int nIndex)
{
   if (nIndex<0||nIndex>GetCount())
      return;
   DBTableStyleGlobalSetInfo *pObject=(DBTableStyleGlobalSetInfo*)GetItem(nIndex);
   delete pObject;
   pObject=NULL;
   RemoveAt(FindIndex(nIndex));
}


DBTableStyleGlobalSetInfoList * DBTableStyleGlobalSetInfoList::Instance()
{
   if(sm_inst.get() == 0)
      sm_inst = shared_ptr<DBTableStyleGlobalSetInfoList>(new DBTableStyleGlobalSetInfoList);

   return sm_inst.get();
}

//************************************
// Method:    更新实时XML数据
// Author:    wuZhiHua
// Date : 	  2018/04/17
// Access:    public 
// Returns:   BOOL
// Parameter: CString fileName
//************************************
BOOL DBTableStyleGlobalSetInfoList::UpdateCurrentTimeXmlDataFromLocalData(CADOConn *pADOConn,CString fileName, CString strTime)
{
   CString sqlStr = _T("");

   S_GridCtrl_TableAtrri tableAtrri;
   CGridCtrlTableAttributeOp *op = CGridCtrlTableAttributeOp::Instance();
   if( !op->ReadTableAtrri(fileName ,tableAtrri ) )
   {
      return FALSE;
   }

   tableAtrri.strUpdateTime = strTime;

   CString strXml = AttriStructToAttriStr(tableAtrri);
   if (!strXml.IsEmpty())
   {
      sqlStr.Format(_T("update %s set %s = '%s' , %s = '%s' where %s = '%s'") , DB_TABLE_STYLE_GLOBAL_SET ,
         DBTableStyleGlobalSet_key_cRealTimeXmlFile , strXml ,
         DBTableStyleGlobalSet_key_dUpdateTime , strTime,
         DBTableStyleGlobalSet_key_cXmlFileName , fileName);
   }

   return pADOConn->ExecuteSQL(sqlStr);
}


//************************************
// Method:    用初始化数据 更新实时XML数据 
// Author:    wuZhiHua
// Date : 	  2018/04/17
// Access:    public 
// Returns:   BOOL
// Parameter: CString fileName
//************************************
BOOL DBTableStyleGlobalSetInfoList::UpdateCurrentTimeXmlDataFromInitData(CADOConn *pADOConn,CString fileName, CString strTime , CString &updateXmlstr)
{
   CString sqlStr;
   sqlStr.Format(_T("select %s from %s where %s = '%s'") ,DBTableStyleGlobalSet_key_cInitSettingXmlFile ,
      DB_TABLE_STYLE_GLOBAL_SET ,DBTableStyleGlobalSet_key_cXmlFileName , fileName);

   CString strInitXml;
   pADOConn->GetRecordSet(sqlStr);
   if (!pADOConn->adoEOF())
   {
      strInitXml = pADOConn->GetValueString(DBTableStyleGlobalSet_key_cInitSettingXmlFile);

      S_GridCtrl_TableAtrri initXmlAttr;
      initXmlAttr = AttriStrToAttriStruct(strInitXml);
      initXmlAttr.strUpdateTime = strTime;

      CString strXml = AttriStructToAttriStr(initXmlAttr);

      sqlStr.Format(_T("update %s set %s = '%s' , %s = '%s' where %s = '%s'") , DB_TABLE_STYLE_GLOBAL_SET ,
         DBTableStyleGlobalSet_key_cRealTimeXmlFile , strXml ,
         DBTableStyleGlobalSet_key_dUpdateTime , strTime,
         DBTableStyleGlobalSet_key_cXmlFileName , fileName);

      updateXmlstr = strXml;
   }

   return pADOConn->ExecuteSQL(sqlStr);
}


//************************************
// Method:    更新出厂设置 会覆盖实时数据
// Author:    wuZhiHua
// Date : 	  2018/04/17
// Access:    public 
// Returns:   BOOL
// Parameter: CString fileName
//************************************
BOOL DBTableStyleGlobalSetInfoList::UpdateInitSetXmlData(CADOConn *pADOConn, CString fileName, CString strTime)
{
   CString sqlStr = _T("");

   S_GridCtrl_TableAtrri tableAtrri;
   CGridCtrlTableAttributeOp *op = CGridCtrlTableAttributeOp::Instance();
   if( !op->ReadTableAtrri(fileName ,tableAtrri ) )
   {
      return FALSE;
   }

   tableAtrri.strUpdateTime = strTime;

   CString strXml = AttriStructToAttriStr(tableAtrri);
   if (!strXml.IsEmpty())
   {
      sqlStr.Format(_T("update %s set %s = '%s' , %s = '%s' , %s = '%s' where %s = '%s'") , DB_TABLE_STYLE_GLOBAL_SET ,
         DBTableStyleGlobalSet_key_cInitSettingXmlFile , strXml ,
         DBTableStyleGlobalSet_key_cRealTimeXmlFile , strXml ,
         DBTableStyleGlobalSet_key_dUpdateTime , strTime,
         DBTableStyleGlobalSet_key_cXmlFileName , fileName);
   }

   return pADOConn->ExecuteSQL(sqlStr);
}


//************************************
// Method:    合并代码数据  到实时XML内容  恢复出厂设置内容
// Author:    wuZhiHua
// Date : 	  2018/04/18
// Access:    public 
// Returns:   BOOL
// Parameter: CADOConn * pADOConn
// Parameter: CString fileName
// Parameter: CString strTime
//************************************
BOOL DBTableStyleGlobalSetInfoList::CombineDefaultTableAtrri(CADOConn *pADOConn,CString fileName, CString strTime)
{
   CString sqlStr;
   sqlStr.Format(_T("select %s , %s from %s where %s = '%s'") ,DBTableStyleGlobalSet_key_cInitSettingXmlFile , DBTableStyleGlobalSet_key_cRealTimeXmlFile,
      DB_TABLE_STYLE_GLOBAL_SET ,DBTableStyleGlobalSet_key_cXmlFileName , fileName);

   CString strInitXml , strRealTimeXml;
   pADOConn->GetRecordSet(sqlStr);
   if (!pADOConn->adoEOF())
   {
      strInitXml = pADOConn->GetValueString(DBTableStyleGlobalSet_key_cInitSettingXmlFile);
      strRealTimeXml = pADOConn->GetValueString(DBTableStyleGlobalSet_key_cRealTimeXmlFile);

      S_GridCtrl_TableAtrri initXmlAttr , realTimeXmlAttr;
      initXmlAttr = AttriStrToAttriStruct(strInitXml);
      realTimeXmlAttr = AttriStrToAttriStruct(strRealTimeXml);

      CGridCtrlTableAttributeOp *op = CGridCtrlTableAttributeOp::Instance();
      op->CombineDefaultTableAtrri(fileName, initXmlAttr);
      op->CombineDefaultTableAtrri(fileName, realTimeXmlAttr);

      initXmlAttr.strUpdateTime = strTime;
      realTimeXmlAttr.strUpdateTime = strTime;
      strInitXml = AttriStructToAttriStr(initXmlAttr);
      strRealTimeXml = AttriStructToAttriStr(realTimeXmlAttr);


      sqlStr.Format(_T("update %s set %s = '%s' , %s = '%s' , %s = '%s' where %s = '%s'") , DB_TABLE_STYLE_GLOBAL_SET ,
         DBTableStyleGlobalSet_key_cInitSettingXmlFile , strInitXml ,
         DBTableStyleGlobalSet_key_cRealTimeXmlFile , strRealTimeXml ,
         DBTableStyleGlobalSet_key_dUpdateTime , strTime,
         DBTableStyleGlobalSet_key_cXmlFileName , fileName);
   }

   return pADOConn->ExecuteSQL(sqlStr);
}


////************************************
//// Method:    更新数据列  还有属性设置
//// Author:    wuZhiHua
//// Date : 	  2018/04/18
//// Access:    public 
//// Returns:   BOOL
//// Parameter: CADOConn * pADOConn
//// Parameter: CString strTime
////************************************
//BOOL DBTableStyleGlobalSetInfoList::UpdateColSetAndStyleAttrSet(CADOConn *pADOConn , CString strTime)
//{
//   //std::map<CString, CGridCtrlTableAttributeOp::funcCreateAttri> mapFunc = CGridCtrlTableAttributeOp::Instance()->m_mapFunc;
//   //std::map<CString, CGridCtrlTableAttributeOp::funcCreateAttri2Param> mapFunc2Param = CGridCtrlTableAttributeOp::Instance()->m_mapFunc2Param;
//
//   DBTableStyleAttrSetLst styleAttrSet;
//   styleAttrSet.GetListFromDB(pADOConn);
//
//   std::map<CString , CString> mapFileTimeXml;
//
//   CString sqlStr;
//   sqlStr.Format(_T("select %s , %s  from %s") , DBTableStyleGlobalSet_key_cXmlFileName ,
//      DBTableStyleGlobalSet_key_cRealTimeXmlFile ,
//      DB_TABLE_STYLE_GLOBAL_SET);
//
//   pADOConn->GetRecordSet(sqlStr);
//   while (!pADOConn->adoEOF())
//   {
//      CString fileName = pADOConn->GetValueString(DBTableStyleGlobalSet_key_cXmlFileName);
//      CString realTimeXml = pADOConn->GetValueString(DBTableStyleGlobalSet_key_cRealTimeXmlFile);
//      mapFileTimeXml[fileName] = realTimeXml;
//      pADOConn->MoveNext();
//   }
//
//
//   int indexCount = 0;
//   CString allSql = _T("");
//   for (auto it = mapFileTimeXml.begin(); it != mapFileTimeXml.end(); it++)
//   {
//      S_GridCtrl_TableAtrri tableAtrri = AttriStrToAttriStruct(it->second);
//
//      tableAtrri.strUpdateTime = strTime;
//
//      UpdateColSetAndStyleAttrSet( pADOConn , &styleAttrSet, tableAtrri );
//
//      CString updateXmlStr = AttriStructToAttriStr(tableAtrri);
//      if (!updateXmlStr.IsEmpty())
//      {
//         sqlStr.Format(_T("update %s set  %s = '%s' , %s = '%s' where %s = '%s'") , DB_TABLE_STYLE_GLOBAL_SET ,
//            DBTableStyleGlobalSet_key_dUpdateTime , strTime,
//            DBTableStyleGlobalSet_key_cRealTimeXmlFile , updateXmlStr ,
//            DBTableStyleGlobalSet_key_cXmlFileName , it->first);
//
//         indexCount++;
//         allSql += sqlStr + _T("\n");
//
//         if (indexCount % 30 == 0)
//         {
//            pADOConn->ExecuteSQL(allSql);
//            allSql = _T("");
//         }
//      }
//   }
//
//   return pADOConn->ExecuteSQL(allSql);
//}
//
////************************************
//// Method:    更新数据列  还有属性设置 单个数据
//// Author:    wuZhiHua
//// Date : 	  2018/04/18
//// Access:    public 
//// Returns:   void
//// Parameter: S_GridCtrl_TableAtrri & tableAtrri
////************************************
//void DBTableStyleGlobalSetInfoList::UpdateColSetAndStyleAttrSet(CADOConn *pADOConn, DBTableStyleAttrSetLst  *pStyleAttrSet, S_GridCtrl_TableAtrri& tableAtrri)
//{
//   //更新属性
//   CString strValue = _T("");
//   DBTableStyleAttrSetData *pData = nullptr;
//   pData =  pStyleAttrSet->GetFiledValueByKey(DBTableStyleSet_FiledKey_ShowFilter ,
//      pADOConn , strValue);
//   if (pData)
//   {
//      tableAtrri.isShowSortBar = (strValue == _T("0")) ? false : true;
//   }
//
//   pData =  pStyleAttrSet->GetFiledValueByKey(DBTableStyleSet_FiledKey_AllowSort ,
//      pADOConn , strValue);
//   if (pData)
//   {
//      tableAtrri.isAllowSort = (strValue == _T("0")) ? false : true;
//   }
//
//   pData =  pStyleAttrSet->GetFiledValueByKey(DBTableStyleSet_FiledKey_WholeRowSelect ,
//      pADOConn , strValue);
//   if (pData)
//   {
//      tableAtrri.isWholeRowSelect = (strValue == _T("0")) ? false : true;
//   }
//
//   pData =  pStyleAttrSet->GetFiledValueByKey(DBTableStyleSet_FiledKey_ShowTotal ,
//      pADOConn , strValue);
//   if (pData)
//   {
//      tableAtrri.isShowSumBar = (strValue == _T("0")) ? false : true;
//   }
//
//   pData =  pStyleAttrSet->GetFiledValueByKey(DBTableStyleSet_FiledKey_MultiLineSelect ,
//      pADOConn , strValue);
//   if (pData)
//   {
//      tableAtrri.isMultiRowSelect = (strValue == _T("0")) ? false : true;
//   }
//
//   pData =  pStyleAttrSet->GetFiledValueByKey(DBTableStyleSet_FiledKey_MulLineSelNoLoseFocus ,
//      pADOConn , strValue);
//   if (pData)
//   {
//      tableAtrri.IsMultiRowSelectNoLoseFocus = (strValue == _T("0")) ? false : true;
//   }
//
//   pData =  pStyleAttrSet->GetFiledValueByKey(DBTableStyleSet_FiledKey_RowHeight ,
//      pADOConn , strValue);
//   if (pData)
//   {
//      tableAtrri.nDataRowHeight = _wtoi(strValue);
//   }
//
//   pData =  pStyleAttrSet->GetFiledValueByKey(DBTableStyleSet_FiledKey_AllFont ,
//      pADOConn , strValue);
//   if (pData)
//   {
//      tableAtrri.iDataRowFont = _wtoi(strValue);
//   }
//
//   pData =  pStyleAttrSet->GetFiledValueByKey(DBTableStyleSet_FiledKey_TitleFilter ,
//      pADOConn , strValue);
//   if (pData)
//   {
//      tableAtrri.isShowTitleFilter = (strValue == _T("0")) ? false : true;
//   }
//
//   pData =  pStyleAttrSet->GetFiledValueByKey(DBTableStyleSet_FiledKey_EnableDragCol ,
//      pADOConn , strValue);
//   if (pData)
//   {
//      tableAtrri.isEnableDragCol = (strValue == _T("0")) ? false : true;
//   }
//
//   pData =  pStyleAttrSet->GetFiledValueByKey(DBTableStyleSet_FiledKey_PrintHeXiang ,
//      pADOConn , strValue);
//   if (pData)
//   {
//      tableAtrri.isPrintHengXiang = (strValue == _T("0")) ? false : true;
//   }
//}


//************************************
// Method:    数据库XML字符串转 表格样式属性结构体
// Author:    wuZhiHua
// Date : 	  2018/04/17
// Access:    private 
// Returns:   S_GridCtrl_TableAtrri
// Parameter: CString attriStr
//************************************
S_GridCtrl_TableAtrri DBTableStyleGlobalSetInfoList::AttriStrToAttriStruct(CString attriStr)
{
   S_GridCtrl_TableAtrri tableAtrri;
   TiXmlDocument *pMyDocument = new TiXmlDocument();
   pMyDocument->Parse(RnString::UNICODE_TO_UTF8(attriStr).c_str());

   TiXmlElement *pRootElement = pMyDocument->RootElement();
   TiXmlElement *FirstVersion = pRootElement->FirstChildElement();
   while (FirstVersion != NULL)
   {
      const char* cvalue;
      cvalue = FirstVersion->Value();   

      if (0 == strcmp(cvalue, "isShowTitleFilter"))
      {	
         cvalue = FirstVersion->GetText();
         tableAtrri.isShowTitleFilter = atoi(cvalue)?true:false;   
      }
      else if (0 == strcmp(cvalue,"isAllowSort"))
      {            
         cvalue = FirstVersion->GetText();
         tableAtrri.isAllowSort = atoi(cvalue)?true:false;           
      }
      else if (0 == strcmp(cvalue,"isMultiRowSelect"))
      {
         cvalue = FirstVersion->GetText();
         tableAtrri.isMultiRowSelect = (BOOL)atoi(cvalue)?true:false;  
      }
      else if (0 == strcmp(cvalue,"IsMultiRowSelectNoLoseFocus"))
      {
         cvalue = FirstVersion->GetText();
         tableAtrri.IsMultiRowSelectNoLoseFocus = (BOOL)atoi(cvalue)?true:false; 
      }
      else if (0 == strcmp(cvalue,"isShowSortBar"))
      {
         cvalue = FirstVersion->GetText();
         tableAtrri.isShowSortBar = (BOOL)atoi(cvalue)?true:false; 
      }
      else if (0 == strcmp(cvalue,"DataRowHeight"))
      {
         cvalue = FirstVersion->GetText();
         tableAtrri.nDataRowHeight = atoi(cvalue);
      }
      else if (0 == strcmp(cvalue,"isShowSumBar"))
      {
         cvalue = FirstVersion->GetText();
         tableAtrri.isShowSumBar = atoi(cvalue)?true:false; 
      }
      else if (0 == strcmp(cvalue,"isWholeRowSelect"))
      {
         cvalue = FirstVersion->GetText();
         tableAtrri.isWholeRowSelect = atoi(cvalue)?true:false; 
      }
      else if (0 == strcmp(cvalue,"iDataRowFont"))
      {
         cvalue = FirstVersion->GetText();
         tableAtrri.iDataRowFont = atoi(cvalue); 
      }else if (0 == strcmp(cvalue,"isEnableDragCol"))
      {
         cvalue = FirstVersion->GetText();
         tableAtrri.isEnableDragCol = atoi(cvalue)?true:false; 
      }   
      else if (0 == strcmp(cvalue,"isEnableEdit"))
      {
         cvalue = FirstVersion->GetText();
         tableAtrri.isEnableEdit = atoi(cvalue)?true:false;
      }
      else if (0 == strcmp(cvalue,"iPageRows"))
      {
         cvalue = FirstVersion->GetText();
         tableAtrri.iPageRows = atoi(cvalue);
      }
      else if (0 == strcmp(cvalue,"isMainSortDesc"))
      {
         cvalue = FirstVersion->GetText();
         tableAtrri.isMainSortDesc = atoi(cvalue);
      }else if (0 == strcmp(cvalue,"isSecondSortDesc"))
      {
         cvalue = FirstVersion->GetText();
         tableAtrri.isSecondSortDesc = atoi(cvalue);
      }
      else if (0 == strcmp(cvalue,"mainSortField"))
      {
         tableAtrri.mainSortField = FirstVersion->GetText();
      }
      else if (0 == strcmp(cvalue,"secondSortField"))
      {
         tableAtrri.secondSortField = FirstVersion->GetText();
      }
      else if (0 == strcmp(cvalue,"ItemCount"))
      {
         cvalue = FirstVersion->GetText();
         int count = atoi(cvalue);
         CString strIndex;
         TiXmlElement *pElement = NULL;
         string strvalue;
         CString Cstrvalue;
         for(int i=1;i<=count;++i)
         {
            strIndex.Format(_T("Item%d"),i);
            pElement = FirstVersion->FirstChildElement(RnString::UNICODE_TO_UTF8(strIndex).c_str());
            if (pElement == NULL)
            {
               delete pMyDocument;//2017/06/06 zhangt 释放内存
               return tableAtrri;
            } 
            S_GridCtrl_FieldAtrri oneFieldAtrri;
            TiXmlElement *pElement2 = pElement->FirstChildElement("enColSumType");
            if (pElement2 != NULL)
            {
               cvalue = pElement2->GetText();
               if (cvalue!=NULL)
               {
                  oneFieldAtrri.enColSumType = (ENUM_COLSUMTYPE)atoi(cvalue); 
               }
            }

            pElement2 = pElement->FirstChildElement("enSerchType");
            if (pElement2 != NULL)
            {
               cvalue = pElement2->GetText();
               if (cvalue!=NULL)
               {
                  oneFieldAtrri.enSerchType = (ENUM_COLSERCHTYPE)atoi(cvalue); 
               }
            } 

            pElement2 = pElement->FirstChildElement("iColFont");
            if (pElement2 != NULL)
            {
               cvalue = pElement2->GetText();
               if (cvalue!=NULL)
               {
                  oneFieldAtrri.iColFont = atoi(cvalue);
               }
            }                

            pElement2 = pElement->FirstChildElement("iColIndex");
            if (pElement2 != NULL)
            {
               cvalue = pElement2->GetText();
               if (cvalue!=NULL)
               {
                  oneFieldAtrri.iColIndex = atoi(cvalue);
               }
               else
               {
                  delete pMyDocument;//2017/06/06 zhangt 释放内存
                  return tableAtrri;
               }
            }else
            {
               delete pMyDocument;//2017/06/06 zhangt 释放内存
               return tableAtrri;
            }  


            pElement2 = pElement->FirstChildElement("iColWidth");
            if (pElement2 != NULL)
            {
               cvalue = pElement2->GetText();
               if (cvalue!=NULL)
               {
                  oneFieldAtrri.iColWidth = atoi(cvalue);
               }
            }

            pElement2 = pElement->FirstChildElement("iLock");
            if (pElement2 != NULL)
            {
               cvalue = pElement2->GetText();
               if (cvalue!=NULL)
               {
                  oneFieldAtrri.iLock = atoi(cvalue);
               }
            }

            pElement2 = pElement->FirstChildElement("isEdit");
            if (pElement2 != NULL)
            {
               cvalue = pElement2->GetText();
               if (cvalue!=NULL)
               {
                  oneFieldAtrri.isEdit = atoi(cvalue)?true:false;
               }
            }               

            pElement2 = pElement->FirstChildElement("IsFontWeight");
            if (pElement2 != NULL)
            {
               cvalue = pElement2->GetText();
               if (cvalue!=NULL)
               {
                  oneFieldAtrri.IsFontWeight = atoi(cvalue)?true:false;
               }
            }               

            pElement2 = pElement->FirstChildElement("isShow");
            if (pElement2 != NULL)
            {
               cvalue = pElement2->GetText();
               if (cvalue!=NULL)
               {
                  oneFieldAtrri.isShow = atoi(cvalue)?true:false;
               }
            }

            pElement2 = pElement->FirstChildElement("strColFormat");
            if (pElement2 != NULL)
            {                  
               cvalue = pElement2->GetText();  
               if (cvalue!=NULL)
               {
                  oneFieldAtrri.strColFormat = RnString::Char2WCharUTF8(cvalue);
               }
            }

            pElement2 = pElement->FirstChildElement("strColID");
            if (pElement2 != NULL)
            {                  
               cvalue = pElement2->GetText();  
               if (cvalue!=NULL)
               {
                  oneFieldAtrri.strColID = RnString::Char2WCharUTF8(cvalue);
               }else
               {
                  delete pMyDocument;//2017/06/06 zhangt 释放内存
                  return tableAtrri;
               }
            }else
            {
               delete pMyDocument;//2017/06/06 zhangt 释放内存
               return tableAtrri;
            }

            pElement2 = pElement->FirstChildElement("strColShowName");
            if (pElement2 != NULL)
            {                  
               cvalue = pElement2->GetText();  
               if (cvalue!=NULL)
               {
                  oneFieldAtrri.strColShowName = RnString::Char2WCharUTF8(cvalue);
               }
            }
            pElement2 = pElement->FirstChildElement("isEnableFilter");//列能否排序 yangjr 2017-6-9
            if (pElement2 != NULL)
            {                  
               cvalue = pElement2->GetText();  
               if (cvalue!=NULL)
               {
                  oneFieldAtrri.isEnableFilter = atoi(cvalue)?true:false;
               }
            }               
            tableAtrri.mapFeildAtrri.insert(make_pair(oneFieldAtrri.strColID,oneFieldAtrri));
            tableAtrri.mapTableFeildPos.insert(make_pair(i,oneFieldAtrri.strColID));
         }
      }
      else if(0 == strcmp(cvalue,"UpdateDateTime"))
      {
         cvalue = FirstVersion->GetText();
         tableAtrri.strUpdateTime = cvalue;
      }

      FirstVersion = FirstVersion->NextSiblingElement();
   }
   delete pMyDocument;
   pMyDocument = nullptr;
   return tableAtrri;
}


//************************************
// Method:    表格样式属性结构体 转数据库XML字符串
// Author:    wuZhiHua
// Date : 	  2018/04/18
// Access:    public 
// Returns:   CString
// Parameter: S_GridCtrl_TableAtrri attri
//************************************
CString DBTableStyleGlobalSetInfoList::AttriStructToAttriStr(S_GridCtrl_TableAtrri tableAtrri)
{
   CString retStr;

   CGridCtrlTableAttributeOp *op = CGridCtrlTableAttributeOp::Instance();

   // 创建新的xml
   TiXmlDocument *myDocument =new TiXmlDocument();

   //创建一个根元素并连接。
   TiXmlElement *RootElement =new TiXmlElement("TableAtrri");
   myDocument->LinkEndChild(RootElement);

   TiXmlElement *pPersonElement =new TiXmlElement("isAllowSort");
   RootElement->LinkEndChild(pPersonElement);
   op->LinkIntValueToElement(tableAtrri.isAllowSort,pPersonElement);

   //显示列标题筛选器		by WangZY 2017/06/07
   pPersonElement =new TiXmlElement("isShowTitleFilter");
   RootElement->LinkEndChild(pPersonElement);
   op->LinkIntValueToElement(tableAtrri.isShowTitleFilter,pPersonElement);

   pPersonElement =new TiXmlElement("isMultiRowSelect");
   RootElement->LinkEndChild(pPersonElement);
   op->LinkIntValueToElement(tableAtrri.isMultiRowSelect,pPersonElement);

   pPersonElement =new TiXmlElement("IsMultiRowSelectNoLoseFocus");
   RootElement->LinkEndChild(pPersonElement);
   op->LinkIntValueToElement(tableAtrri.IsMultiRowSelectNoLoseFocus,pPersonElement);

   pPersonElement =new TiXmlElement("isShowSortBar");
   RootElement->LinkEndChild(pPersonElement);
   op->LinkIntValueToElement(tableAtrri.isShowSortBar,pPersonElement);

   pPersonElement =new TiXmlElement("isShowSumBar");
   RootElement->LinkEndChild(pPersonElement);
   op->LinkIntValueToElement(tableAtrri.isShowSumBar,pPersonElement);

   pPersonElement =new TiXmlElement("isWholeRowSelect");
   RootElement->LinkEndChild(pPersonElement);
   op->LinkIntValueToElement(tableAtrri.isWholeRowSelect,pPersonElement);

   pPersonElement =new TiXmlElement("DataRowHeight");
   RootElement->LinkEndChild(pPersonElement);
   op->LinkIntValueToElement(tableAtrri.nDataRowHeight,pPersonElement);

   pPersonElement =new TiXmlElement("iDataRowFont");
   RootElement->LinkEndChild(pPersonElement);
   op->LinkIntValueToElement(tableAtrri.iDataRowFont,pPersonElement);

   pPersonElement =new TiXmlElement("isEnableDragCol");
   RootElement->LinkEndChild(pPersonElement);
   op->LinkIntValueToElement(tableAtrri.isEnableDragCol,pPersonElement);//列位置能否拖动 yangjr 2017-6-13

   //表是否可编辑	by WangZY 2017/06/15
   pPersonElement =new TiXmlElement("isEnableEdit");
   RootElement->LinkEndChild(pPersonElement);
   op->LinkIntValueToElement(tableAtrri.isEnableEdit,pPersonElement);

   pPersonElement =new TiXmlElement("iPageRows");
   RootElement->LinkEndChild(pPersonElement);
   op->LinkIntValueToElement(tableAtrri.iPageRows,pPersonElement);

   pPersonElement =new TiXmlElement("mainSortField");
   RootElement->LinkEndChild(pPersonElement);
   op->LinkCStringValueToElement(tableAtrri.mainSortField,pPersonElement);
   pPersonElement =new TiXmlElement("secondSortField");
   RootElement->LinkEndChild(pPersonElement);
   op->LinkCStringValueToElement(tableAtrri.secondSortField,pPersonElement);

   pPersonElement =new TiXmlElement("isMainSortDesc");
   RootElement->LinkEndChild(pPersonElement);
   op->LinkIntValueToElement(tableAtrri.isMainSortDesc,pPersonElement);
   pPersonElement =new TiXmlElement("isSecondSortDesc");
   RootElement->LinkEndChild(pPersonElement);
   op->LinkIntValueToElement(tableAtrri.isSecondSortDesc,pPersonElement);

   pPersonElement =new TiXmlElement("ItemCount");
   RootElement->LinkEndChild(pPersonElement);
   op->LinkIntValueToElement(tableAtrri.mapFeildAtrri.size(),pPersonElement);
   CString strItem;
   for (MAP_GridCtrl_FieldPos::const_iterator iterIndex= tableAtrri.mapTableFeildPos.begin();
      iterIndex!=tableAtrri.mapTableFeildPos.end();++iterIndex)
   {         
      strItem.Format(_T("Item%d"),iterIndex->first);
      TiXmlElement *pPersonElement2 =new TiXmlElement(RnString::UNICODE_TO_UTF8(strItem).c_str());
      pPersonElement->LinkEndChild(pPersonElement2);

      MAP_GridCtrl_FieldAtrri::const_iterator iterFind = tableAtrri.mapFeildAtrri.find(iterIndex->second);
      ASSERT(iterFind!=tableAtrri.mapFeildAtrri.end());
      TiXmlElement *pPersonElement3 =new TiXmlElement("enColSumType");
      pPersonElement2->LinkEndChild(pPersonElement3);
      op->LinkIntValueToElement((int)iterFind->second.enColSumType,pPersonElement3);

      pPersonElement3 =new TiXmlElement("enSerchType");
      pPersonElement2->LinkEndChild(pPersonElement3);
      op->LinkIntValueToElement((int)iterFind->second.enSerchType,pPersonElement3);

      pPersonElement3 =new TiXmlElement("iColFont");
      pPersonElement2->LinkEndChild(pPersonElement3);
      op->LinkIntValueToElement(iterFind->second.iColFont,pPersonElement3);

      pPersonElement3 =new TiXmlElement("iColIndex");
      pPersonElement2->LinkEndChild(pPersonElement3);
      op->LinkIntValueToElement(iterFind->second.iColIndex,pPersonElement3);

      pPersonElement3 =new TiXmlElement("iColWidth");
      pPersonElement2->LinkEndChild(pPersonElement3);
      op->LinkIntValueToElement(iterFind->second.iColWidth,pPersonElement3);

      pPersonElement3 =new TiXmlElement("iLock");
      pPersonElement2->LinkEndChild(pPersonElement3);
      op->LinkIntValueToElement(iterFind->second.iLock,pPersonElement3);

      pPersonElement3 =new TiXmlElement("isEdit");
      pPersonElement2->LinkEndChild(pPersonElement3);
      op->LinkIntValueToElement(iterFind->second.isEdit,pPersonElement3);

      pPersonElement3 =new TiXmlElement("IsFontWeight");
      pPersonElement2->LinkEndChild(pPersonElement3);
      op->LinkIntValueToElement(iterFind->second.IsFontWeight,pPersonElement3);

      pPersonElement3 =new TiXmlElement("isShow");
      pPersonElement2->LinkEndChild(pPersonElement3);
      op->LinkIntValueToElement(iterFind->second.isShow,pPersonElement3);

      pPersonElement3 =new TiXmlElement("strColFormat");
      pPersonElement2->LinkEndChild(pPersonElement3);
      op->LinkCStringValueToElement(iterFind->second.strColFormat,pPersonElement3);

      pPersonElement3 =new TiXmlElement("strColID");
      pPersonElement2->LinkEndChild(pPersonElement3);
      op->LinkCStringValueToElement(iterFind->second.strColID,pPersonElement3);

      pPersonElement3 =new TiXmlElement("strColShowName");
      pPersonElement2->LinkEndChild(pPersonElement3);
      op->LinkCStringValueToElement(iterFind->second.strColShowName,pPersonElement3);

      pPersonElement3 =new TiXmlElement("isEnableFilter");
      pPersonElement2->LinkEndChild(pPersonElement3);
      op->LinkIntValueToElement(iterFind->second.isEnableFilter,pPersonElement3);
   }

   TiXmlElement* pUpdateDateTime =new TiXmlElement("UpdateDateTime");
   RootElement->LinkEndChild(pUpdateDateTime);
   op->LinkCStringValueToElement(tableAtrri.strUpdateTime, pUpdateDateTime);


   TiXmlPrinter xmlPrint;
   myDocument->Accept(&xmlPrint);
   string strTmp = xmlPrint.CStr();
   delete myDocument;
   myDocument = nullptr;
   retStr = RnString::UTF8_TO_UNICODE(strTmp);

   return retStr;
}


//************************************
// Method:    根据文件名获取 数据库表格样式实时数据
// Author:    wuZhiHua
// Date : 	  2018/04/18
// Access:    public 
// Returns:   CString
// Parameter: CADOConn * pADOConn
// Parameter: CString fileName
//************************************
CString DBTableStyleGlobalSetInfoList::GetStyleInfoByFileName(CADOConn *pADOConn, CString fileName , CString &updateTime)
{
   CString sqlStr = _T("") , realTimeStr = _T("");
   sqlStr.Format(_T("select %s , %s from %s where %s = '%s'") , DBTableStyleGlobalSet_key_dUpdateTime ,
      DBTableStyleGlobalSet_key_cRealTimeXmlFile , DB_TABLE_STYLE_GLOBAL_SET,
      DBTableStyleGlobalSet_key_cXmlFileName , fileName);


   pADOConn->GetRecordSet(sqlStr);
   if (!pADOConn->adoEOF())
   {
      updateTime = pADOConn->GetValueString(DBTableStyleGlobalSet_key_dUpdateTime);
      realTimeStr = pADOConn->GetValueString(DBTableStyleGlobalSet_key_cRealTimeXmlFile);
   }

   return realTimeStr;
}

#ifdef USING_GRIDCTRL_MARK
//************************************
// Method:    获取表格
// Author:    wuZhiHua
// Date : 	  2018/04/16
// Access:    private 
// Returns:   void
// Parameter: MAP_GridCtrl_AllData & allData
//************************************
void DBTableStyleGlobalSetInfoList::GetGridData(CADOConn *pADOConn, __out MAP_GridCtrl_AllData& mapAllData)
{
   CString sqlStr;
   sqlStr.Format(_T("select %s , %s , %s from %s") , DBTableStyleGlobalSet_key_cXmlFileName ,
      DBTableStyleGlobalSet_key_cXmlDesc ,
      DBTableStyleGlobalSet_key_dUpdateTime,
      DB_TABLE_STYLE_GLOBAL_SET);

   mapAllData.clear();
   MAP_GridCtrl_RowData mapRowData;
   S_GridCtrl_FieldData data;
   data.fieldCtrlType = CB_enum_FieldCtrl_Text;
   data.fieldDataType = CB_enum_FieldData_CString;

   int index = 1;
   pADOConn->GetRecordSet(sqlStr);
   while (!pADOConn->adoEOF())
   {
      mapRowData.clear();
      data.strValue = pADOConn->GetValueString(DBTableStyleGlobalSet_key_cXmlFileName);
      mapRowData.insert(make_pair(DBTableStyleGlobalSet_key_cXmlFileName,data));

      data.strValue = pADOConn->GetValueString(DBTableStyleGlobalSet_key_cXmlDesc);
      mapRowData.insert(make_pair(DBTableStyleGlobalSet_key_cXmlDesc,data));

      data.strValue = pADOConn->GetValueString(DBTableStyleGlobalSet_key_dUpdateTime);
      mapRowData.insert(make_pair(DBTableStyleGlobalSet_key_dUpdateTime,data));


      mapAllData.insert(MAP_GridCtrl_AllData::value_type(index++, mapRowData));
      pADOConn->MoveNext();
   }
}

//************************************
// Method:    插入或更新实时XML数据
// Author:    yangjr
// Date : 	  2018/05/29
// Access:    public 
// Returns:   BOOL
// Parameter: CString fileName xml文件名， S_GridCtrl_TableAtrri &tableAtrri 表格样式
//************************************
BOOL DBTableStyleGlobalSetInfoList::InsertOrUpdateStyle(CADOConn *pADOConn,CString fileName,const S_GridCtrl_TableAtrri &tableAtrri)
{
   CString sqlStr = _T("");
   CString strXml = AttriStructToAttriStr(tableAtrri);
   if (!strXml.IsEmpty())
   {
      sqlStr.Format(_T("if exists (select %s from %s where %s='%s') \
         update %s set %s = '%s' , %s = '%s' where %s = '%s' \
         else insert into %s (%s,%s,%s) values ('%s','%s','%s')") , 
         DBTableStyleGlobalSet_key_cXmlFileName,DB_TABLE_STYLE_GLOBAL_SET ,DBTableStyleGlobalSet_key_cXmlFileName , fileName
         ,DB_TABLE_STYLE_GLOBAL_SET,DBTableStyleGlobalSet_key_cRealTimeXmlFile , strXml ,
         DBTableStyleGlobalSet_key_dUpdateTime , tableAtrri.strUpdateTime,DBTableStyleGlobalSet_key_cXmlFileName , fileName
         ,DB_TABLE_STYLE_GLOBAL_SET,DBTableStyleGlobalSet_key_cXmlFileName , DBTableStyleGlobalSet_key_cRealTimeXmlFile,DBTableStyleGlobalSet_key_dUpdateTime
         ,fileName,strXml,tableAtrri.strUpdateTime);
   }

   return pADOConn->ExecuteSQL(sqlStr);
}

//************************************
// Method:    获取服务器的XML数据
// Author:    yangjr
// Date : 	  2018/05/29
// Access:    public 
// Returns:   BOOL，S_GridCtrl_TableAtrri &tableAtrri 表格样式
// Parameter: CString fileName xml文件名
BOOL DBTableStyleGlobalSetInfoList::GetServerStyle(CADOConn *pADOConn,CString fileName,S_GridCtrl_TableAtrri &tableAtrri)
{
   if (!pADOConn)
   {
      return FALSE;
   }
    CString sqlStr = _T("");
    sqlStr.Format(_T("select %s,%s from %s where %s='%s';") , 
                     DBTableStyleGlobalSet_key_cRealTimeXmlFile,DBTableStyleGlobalSet_key_dUpdateTime
                     ,DB_TABLE_STYLE_GLOBAL_SET ,DBTableStyleGlobalSet_key_cXmlFileName , fileName);
    pADOConn->GetRecordSet(sqlStr);
    if (!pADOConn->adoEOF())
    {
       CString strXml = pADOConn->GetValueString(DBTableStyleGlobalSet_key_cRealTimeXmlFile);
       if (strXml.IsEmpty())
       {
          return FALSE;
       }
       tableAtrri = AttriStrToAttriStruct(strXml);
       tableAtrri.strUpdateTime = pADOConn->GetValueString(DBTableStyleGlobalSet_key_dUpdateTime);
       return TRUE;
    }else
    {
       return FALSE;
    }
}

#endif