#include "StdAfx.h"
#include "CFileShapeGye.h"
//#include "CDataQili.h"
//#include "CGlobalSet.h"
//#include <MainShape.h>
//#include "PatternTypeTable.h"
#pragma 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define DEF_SHAPEFILE_USER_NAME L"UserShape.gye"
namespace RnString
{
   inline void UNICODE_TO_ACP(const std::wstring& uni_str,std::string& acp_str)
   {
      long l_l_Len = WideCharToMultiByte(
         CP_ACP,
         NULL,
         uni_str.c_str(),
         -1,
         NULL,
         0,
         NULL,
         FALSE ); 

      // 申请存储Unicode代码的字符串所需要的内存
      char* l_p_afterchange = new char[l_l_Len+1];

      // 转换字符集编码格式从UTF8到Unicode
      WideCharToMultiByte(
         CP_ACP,
         NULL,
         uni_str.c_str(),
         -1,
         l_p_afterchange,
         l_l_Len,
         NULL,
         FALSE );

      l_p_afterchange[l_l_Len] = '\0'; 
      acp_str = std::string(l_p_afterchange);
      delete[] l_p_afterchange;
   }

   inline std::string WCStr2StrACP( const CStringW & wstr )
   {
      CStringW strTemp = wstr;
      std::wstring strw = strTemp.GetBuffer();
      strTemp.ReleaseBuffer();
      std::string strUTF8 = "";
      UNICODE_TO_ACP(strw, strUTF8 );
      return strUTF8;
   }
}


CFileShapeGye::CFileShapeGye( void )/*:m_pShapeData(NULL)*/
{

//   m_type = enGye;
//   m_exName = _T("Gye"); //后缀名   
//#ifdef _DEBUG
//   g_sql.Read(_T("CFileShapeGye"),_T("errgye00001:System gye file does not exist!!!"));
//#endif
   InitXmlDoc();
}

CFileShapeGye::~CFileShapeGye( void )
{
    //if(NULL != m_pShapeData)
    //{
    //    delete m_pShapeData;
    //    m_pShapeData = NULL;
    //}
}

BOOL CFileShapeGye::GetShapeSubNode(const CStringW SubName,TiXmlElement** SubNode)
{
   //获取根节点
   TiXmlElement* root = NULL;
   if(false == GetRootDataNode(&root))
      return FALSE;
   std::string strsub = RnString::WCStr2StrACP(SubName);
   (*SubNode) = root->FirstChildElement(strsub.c_str());
   if (NULL == (*SubNode))
   {
      return FALSE;
   }
   return TRUE;
}

//CString CFileShapeGye::GetDefaultGyePath()
//{
//   //先从用户路径，如果不存在则使用系统gye路径 - 保留上一次设置的成型设计参数
//   CGlobalSet *pGlobalSet = CGlobalSetSingleton::InstanceGlobalSet();
//   CString strDefault = pGlobalSet->GetKnitPatternUserPath(DEF_SHAPEFILE_USER_NAME);
//   if(!RnFile::IsFileExistCanRead(strDefault))
//   {
//      strDefault = RnFile::GetModulePathFile(L"")  + DEF_SHAPEFILE_NAME; 
//      if(!RnFile::IsFileExistCanRead(strDefault))
//      {
//         AfxMessageBox(g_sql.Read(_T("CFileShapeGye"),_T("errgye00001:System gye file does not exist!!!")));
//         strDefault = _T("");
//      }
//   }
//   return strDefault;
//}

void CFileShapeGye::InitXmlDoc()
{
   if(NULL == m_pDoc)
   {
      m_pDoc = new TiXmlDocument();
   }
   Init();
   //根节点
   TiXmlElement* root = NULL;
   VERIFY(root = AddRootDataNode("ShapeDesign"));

}

//int CFileShapeGye::FileNewBySysGye()
//{
//   InitXmlDoc();
//   //新建的时候先从用户路径获取相应的GYE数据，如果不存在则使用系统gye路径 - 保留上一次设置的成型设计参数
//
//   m_strFilePathName = RnFile::GetModulePathFile(L"")  + DEF_SHAPEFILE_NAME; 
//   if(!RnFile::IsFileExistCanRead(m_strFilePathName))
//   {
//      AfxMessageBox(g_sql.Read(_T("errgye00001:System gye file does not exist!!!")));
//      m_strFilePathName = _T("");
//   }
//   if(m_strFilePathName.IsEmpty()) 
//   {
//      if(NULL == m_pShapeData)
//      {
//         m_pShapeData = new CShapeProfileData;
//      }
//      return 0;
//   }
//   std::string strAcpFileName;
//   RnString::UNICODE_TO_ACP(m_strFilePathName.GetBuffer(),strAcpFileName);
//   SAFE_DELETE(m_pShapeData);
//   if (NULL == m_pShapeData)
//   {
//      m_pShapeData = new CShapeProfileData;
//   }
//   if (m_pDoc->LoadFile(strAcpFileName.c_str())==FALSE)
//   {
//      ASSERT(0);
//      return 0;
//   }
//   ReadShapeData();
//   return 1;
//}

//int CFileShapeGye::FileNew()
//{
//   InitXmlDoc();
//   //新建的时候先从用户路径获取相应的GYE数据，如果不存在则使用系统gye路径 - 保留上一次设置的成型设计参数
//   m_strFilePathName = GetDefaultGyePath();
//   if(m_strFilePathName.IsEmpty()) 
//   {
//      if(NULL == m_pShapeData)
//      {
//         m_pShapeData = new CShapeProfileData;
//      }
//      return 0;
//   }
//   std::string strAcpFileName;
//   RnString::UNICODE_TO_ACP(m_strFilePathName.GetBuffer(),strAcpFileName);
//   SAFE_DELETE(m_pShapeData);
//   if (NULL == m_pShapeData)
//   {
//      m_pShapeData = new CShapeProfileData;
//   }
//   if (m_pDoc->LoadFile(strAcpFileName.c_str())==FALSE)
//   {
//      ASSERT(0);
//      return 0;
//   }
//   ReadShapeData();
//   return 1;
//}
//
BOOL CFileShapeGye::FileOpen(LPCTSTR lpFilePath, CShapeProfileData *pShapeData)
{
   //CStringW m_strFilePathName;
   if(NULL != lpFilePath)
   {
      m_strFilePathName = lpFilePath;
   }

   CString sExt = PathFindExtension(lpFilePath);
   sExt.MakeUpper();
   if (sExt == _T(".CXC"))
   {
      return TRUE;
   }

   std::string strAcpFileName;
   RnString::UNICODE_TO_ACP(m_strFilePathName.GetBuffer(),strAcpFileName);
   if (m_pDoc->LoadFile(strAcpFileName.c_str())==FALSE)
   {
      return FALSE;
   }
   else
   {
      ReadShapeData(pShapeData);
   }
   return TRUE;
}

BOOL CFileShapeGye::FileWrite(CShapeProfileData *pShapeData)
{
   if(m_strFilePathName.IsEmpty())
   {
      return FALSE;
   }

   WriteShapeData(pShapeData);
   std::string strAcpFileName;
   RnString::UNICODE_TO_ACP(m_strFilePathName.GetBuffer(),strAcpFileName);
   if (!m_pDoc->SaveFile(strAcpFileName.c_str()))
   {
      return FALSE;
   }
   return TRUE;
}

//
//int CFileShapeGye::FileSave(LPCTSTR lpszPathName)
//{
//   InitXmlDoc();
//   WriteShapeData();
//   //文件名为空的情况下默认保存到用户路径
//   if (lpszPathName==NULL)
//   {
//      CGlobalSet *pGlobalSet = CGlobalSetSingleton::InstanceGlobalSet();
//      m_strFilePathName = pGlobalSet->GetKnitPatternUserPath(DEF_SHAPEFILE_USER_NAME);
//   }
//   else
//   {
//      m_strFilePathName = lpszPathName;
//      //如果结尾没有.gye则自动添加
//      CString m_strExt = m_strFilePathName.Right(4);
//      if (m_strExt.MakeUpper() != L".GYE")
//      {
//         m_strFilePathName += _T(".gye");
//      }
//      else
//      {
//         CString m_right;
//         int iPointPos = m_strFilePathName.ReverseFind('.');
//         m_right = m_strFilePathName.Left(iPointPos);
//         m_strFilePathName = m_right+ L".gye";
//      }
//   }
//   if(!m_pDoc->SaveFile(m_strFilePathName.GetBuffer()))
//   {
//      RnMessageBox(g_sql.Read(_T("保存文件失败！")));
//   }
//   m_strFilePathName.ReleaseBuffer();
//   SAFE_DELETE(m_pDoc);
//   return 1;
//}
//
//int CFileShapeGye::FileWrite( const CKnitData *pdata )
//{
//   const CShapeProfileData* pTempData =  dynamic_cast<const CShapeProfileData*>(pdata);
//   if(NULL == pTempData)
//   {
//      return 0;
//   }
//   if (  NULL == m_pShapeData)
//   {
//      m_pShapeData = new CShapeProfileData();
//   }
//   *m_pShapeData = *pTempData;
//   ////#4171 多尺码RNF套针法底图 提示内存不足 导致崩溃 start Duchen 2017/12/07 14:20 dc171207
//   //m_pShapeData->ClearCanvasData();
//   ////#4171 多尺码RNF套针法底图 提示内存不足 导致崩溃 end   Duchen 2017/12/07 14:20
//   return 1;
//}
//
//int CFileShapeGye::FileRead( CKnitData *pdata )
//{
//   CShapeProfileData * ptmp = dynamic_cast<CShapeProfileData*>(pdata);
//	if(NULL == ptmp) return 0;
//	if(m_pShapeData) 
//   {
//		*ptmp = *m_pShapeData;
//   }
//	else
//	{
//		FileNew();
//      *ptmp = *m_pShapeData;
//      return 0;//当前没数据可读
//	}
//	return 1;
//}

//BOOL CFileShapeGye::ReadShapeList(CString &strNodeName,TYPE_LIST_SHAPE &shapelist)
//{
//   //获取根节点
//   //获取根节点
//   TiXmlElement * pXMLSelectedEle = NULL;
//   GetShapeSubNode(strNodeName,&pXMLSelectedEle);
//   if (NULL == pXMLSelectedEle)
//   {
//      return FALSE;
//   }
//   ShapeProfileRow profileRow;
//   int iNoteValue = 0;
//   CString strValue;
//   shapelist.clear();
//   TiXmlElement * pXMLValueEle = pXMLSelectedEle->FirstChildElement();
//   for ( ;NULL != pXMLValueEle;pXMLValueEle = pXMLValueEle->NextSiblingElement())
//   {
//      if (TIXML_SUCCESS == pXMLValueEle->QueryIntAttribute("rowindex",&iNoteValue))
//      {
//         profileRow.iRowIndex = iNoteValue;
//         //#4170 成型bug 相同GYE 在新旧版本上出现不同的结果 start Duchen 2016/11/23 15:47 dc161121
//         profileRow.m_nRowIndexReal = iNoteValue;
//         //#4170 成型bug 相同GYE 在新旧版本上出现不同的结果 end   Duchen 2016/11/23 15:47
//      }
//      if (TIXML_SUCCESS == pXMLValueEle->QueryIntAttribute("rowcount",&iNoteValue))
//      {
//         profileRow.iRowCount = iNoteValue;
//      }
//      if (TIXML_SUCCESS == pXMLValueEle->QueryIntAttribute("needlenum",&iNoteValue))
//      {
//         profileRow.iNeedleNum = iNoteValue;
//      }
//      if (TIXML_SUCCESS == pXMLValueEle->QueryIntAttribute("needletype",&iNoteValue))
//      {
//         profileRow.en_NeedleType = (ShapeSpace::Needle_Type)iNoteValue;
//         if (profileRow.en_NeedleType == ShapeSpace::en_Needle_SuoZhen_Custom) //屏蔽缩针(用户)
//         {
//            profileRow.en_NeedleType = ShapeSpace::en_Needle_SuoZhen_Basemap;
//         }
//      }
//      if (TIXML_SUCCESS == pXMLValueEle->QueryIntAttribute("times",&iNoteValue))
//      {
//         profileRow.iTimes = iNoteValue;
//      }
//      if (TIXML_SUCCESS == pXMLValueEle->QueryIntAttribute("needlemove",&iNoteValue))
//      {
//         profileRow.iNeedleMoveNum = iNoteValue;
//      }
//      if (TIXML_SUCCESS == pXMLValueEle->QueryIntAttribute("needleless",&iNoteValue))
//      {
//         profileRow.iNeedleLess = iNoteValue;
//      }
//      if (TIXML_SUCCESS == pXMLValueEle->QueryIntAttribute("effective",&iNoteValue))
//      {
//         profileRow.effective =(UINT)iNoteValue;
//      }
//      //编织色码处理 非法字符值为0
//      strValue = (CString)pXMLValueEle->Attribute("knitsign");
//
//      //ZB-649 成型编织新增组织（参考恒强） start Duchen 2019/03/01 13:35 dc190225
//      CString sKnitSign = strValue;
//      //ZB-649 成型编织新增组织（参考恒强） end   Duchen 2019/03/01 13:35
//      
//      //#4217 成型【编织】新增常用组织类型列表 start Duchen 2016/01/20 10:06 dc170116
//      profileRow.GetKnitSign(strValue);
//      auto pOrgKnitSignName = pXMLValueEle->Attribute("orgknitsignname");
//      if (pOrgKnitSignName != nullptr)
//      {
//         strValue = RnString::UTF8_TO_UNICODE(pOrgKnitSignName);
//
//         //ZB-649 成型编织新增组织（参考恒强） start Duchen 2019/03/01 13:35 dc190225
//         //面1x1改成面1x1罗纹 面2x1改成面2x1罗纹 兼容老的gye处理
//         CPatternTypeTable::GetInstance().ConvertName(sKnitSign, &strValue);
//         //ZB-649 成型编织新增组织（参考恒强） end   Duchen 2019/03/01 13:35
//
//         profileRow.m_sOrgKnitSignName = strValue;
//      }
//      else
//      {
//         profileRow.m_sOrgKnitSignName.Empty();
//      }
////      profileRow.vecKnitSign.clear();
////        int nFind;
////        if (-1 == strValue.Find(','))
////        {
////           profileRow.vecKnitSign.push_back(_tstoi(strValue));
////        }
////        else
////        {
////           while(strValue.Find(',')!=-1)
////           {
////              nFind=strValue.Find(',');
////              if(strValue.Left(nFind)!=_T(""))
////                 profileRow.vecKnitSign.push_back(_tstoi(strValue.Left(nFind)));
////              strValue=strValue.Mid(nFind+1);
////           }
////           profileRow.vecKnitSign.push_back(_tstoi(strValue));
////        }
//      //#4217 成型【编织】新增常用组织类型列表 end   Duchen 2016/01/20 10:06
//      if (TIXML_SUCCESS ==pXMLValueEle->QueryIntAttribute("domain1",&iNoteValue))
//         profileRow.paramKnitRow.bDomain1 = iNoteValue;  
//      if (TIXML_SUCCESS ==pXMLValueEle->QueryIntAttribute("domain2",&iNoteValue))
//         profileRow.paramKnitRow.bDomain2 = iNoteValue;
//      if (TIXML_SUCCESS ==pXMLValueEle->QueryIntAttribute("speed1",&iNoteValue))
//         profileRow.paramKnitRow.bSpeed1 = iNoteValue;
//      if (TIXML_SUCCESS ==pXMLValueEle->QueryIntAttribute("speed2",&iNoteValue))
//         profileRow.paramKnitRow.bSpeed2 = iNoteValue;
//      if (TIXML_SUCCESS ==pXMLValueEle->QueryIntAttribute("yarn1",&iNoteValue))
//         profileRow.paramKnitRow.bYarn1 = iNoteValue;
//      if (TIXML_SUCCESS ==pXMLValueEle->QueryIntAttribute("yarn2",&iNoteValue))
//         profileRow.paramKnitRow.bYarn2 = iNoteValue;    
//      if (TIXML_SUCCESS ==pXMLValueEle->QueryIntAttribute("roller1",&iNoteValue))
//         profileRow.paramKnitRow.bRoller1 = iNoteValue;
//      if (TIXML_SUCCESS ==pXMLValueEle->QueryIntAttribute("roller2",&iNoteValue))
//         profileRow.paramKnitRow.bRoller2 = iNoteValue; 
//      if (TIXML_SUCCESS ==pXMLValueEle->QueryIntAttribute("height",&iNoteValue))
//         profileRow.iHeight=((float)iNoteValue)/2;
//      shapelist.push_back(profileRow);
//   }
//   return TRUE;
//}

//BOOL CFileShapeGye::WriteShapeList(CString &strNodeName,TYPE_LIST_SHAPE &shapelist)
//{
//   TiXmlElement * pXMLRootEle  = m_pDoc->RootElement();
//   int iNoteValue = 0;
//   CString strValue; 
//   CString strTemp;
//   //创建父节点
//   std::string nodeName = RnString::WCStr2StrACP(strNodeName);//;CStrToChar(strNodeName);
//   TiXmlElement *elmProfile=new TiXmlElement(nodeName.c_str());
//
//   //查找同名节点并删除
//   TiXmlElement* pFindNode = pXMLRootEle->FirstChildElement(nodeName.c_str());
//   if (NULL != pFindNode)
//   {
//      TiXmlNode* pDelnode = pFindNode; 
//      pXMLRootEle->RemoveChild(pDelnode);
//   }
//   pXMLRootEle->LinkEndChild(elmProfile);
//   TYPE_LIST_SHAPE::iterator shapeList_Iter = shapelist.begin();
//   for (;shapeList_Iter != shapelist.end(); ++shapeList_Iter)
//   {
//      TiXmlElement *elmlist=new TiXmlElement("list");
//      elmlist->SetAttribute("rowindex",shapeList_Iter->iRowIndex);
//      elmlist->SetAttribute("rowcount",shapeList_Iter->iRowCount);
//      elmlist->SetAttribute("needlenum",shapeList_Iter->iNeedleNum);
//      elmlist->SetAttribute("needletype",(int)shapeList_Iter->en_NeedleType);
//      elmlist->SetAttribute("times",shapeList_Iter->iTimes);
//      elmlist->SetAttribute("needlemove",shapeList_Iter->iNeedleMoveNum);
//      elmlist->SetAttribute("needleless",shapeList_Iter->iNeedleLess);
//      elmlist->SetAttribute("effective",(int)shapeList_Iter->effective);
//      //编织色码处理
//      //#4217 成型【编织】新增常用组织类型列表 start Duchen 2016/01/20 10:06 dc170116
//      strValue = ShapeProfileRow::GetMultlineBianma(shapeList_Iter->m_vect2DKnit);
//      std::string chSign = RnString::WCStr2StrACP(strValue);
////       strValue = L"";
////       TYPE_VEC_KNITSIGN::iterator sign_Iter = shapeList_Iter->vecKnitSign.begin();
////       for (;sign_Iter != shapeList_Iter->vecKnitSign.end();++sign_Iter)
////       {
////          if ((sign_Iter+1) != shapeList_Iter->vecKnitSign.end())
////          {
////             strTemp.Format(L"%d,",(*sign_Iter));
////             strValue += strTemp;
////          }
////          else
////          {
////             strTemp.Format(L"%d",(*sign_Iter));
////             strValue += strTemp;
////             break;
////          }
////       }
////       std::string chSign = RnString::WCStr2StrACP(strValue);
//      //#4217 成型【编织】新增常用组织类型列表 end   Duchen 2016/01/20 10:06
//      elmlist->SetAttribute("knitsign",chSign.c_str());
//      //#4217 成型【编织】新增常用组织类型列表 start Duchen 2016/01/20 10:06 dc170116
//      chSign = RnString::WCStr2StrACP(shapeList_Iter->m_sOrgKnitSignName);
//      RnString::ACP_TO_UTF8(chSign, chSign);
//      elmlist->SetAttribute("orgknitsignname", chSign.c_str());
//      //#4217 成型【编织】新增常用组织类型列表 end   Duchen 2016/01/20 10:06
//      elmlist->SetAttribute("domain1",shapeList_Iter->paramKnitRow.bDomain1);         
//      elmlist->SetAttribute("domain2",shapeList_Iter->paramKnitRow.bDomain2);
//      elmlist->SetAttribute("speed1",shapeList_Iter->paramKnitRow.bSpeed1);
//      elmlist->SetAttribute("speed2",shapeList_Iter->paramKnitRow.bSpeed2);
//      elmlist->SetAttribute("yarn1",shapeList_Iter->paramKnitRow.bYarn1);
//      elmlist->SetAttribute("yarn2",shapeList_Iter->paramKnitRow.bYarn2);        
//      elmlist->SetAttribute("roller1",shapeList_Iter->paramKnitRow.bRoller1);
//      elmlist->SetAttribute("roller2",shapeList_Iter->paramKnitRow.bRoller2);
//      elmlist->SetAttribute("height",(shapeList_Iter->iHeight)*2);
//      elmProfile->LinkEndChild(elmlist);
//   }
//   return TRUE;
//}

//-----------------------------------------------------------
//第一部分 工艺单数据操作
//工艺单部分数据
//BOOL CFileShapeGye::ReadProfileData(CShapeProfileData *pShapeData)
//{
//   CString strNodeName = L"Profile_LBody";
//   ReadShapeList(strNodeName,pShapeData->m_LShapeData);
//   strNodeName = L"Profile_RBody";
//   ReadShapeList(strNodeName,pShapeData->m_RShapeData);
//   strNodeName = L"Profile_LNeck";
//   ReadShapeList(strNodeName,pShapeData->m_VLShapeData);
//   strNodeName = L"Profile_RNeck";
//   ReadShapeList(strNodeName,pShapeData->m_VRShapeData);
//
//   strNodeName = L"Cycle_LBody";
//   ReadCycleData(strNodeName,pShapeData->m_vectLCycle);
//   strNodeName = L"Cycle_RBody";
//   ReadCycleData(strNodeName,pShapeData->m_vectRCycle);
//   strNodeName = L"Cycle_LNeck";
//   ReadCycleData(strNodeName,pShapeData->m_vectLNCycle);
//   strNodeName = L"Cycle_RNeck";
//   ReadCycleData(strNodeName,pShapeData->m_vectRNCycle);
//   return TRUE;
//}

//工艺单部分数据写入
//BOOL CFileShapeGye::WriteProfileData(CShapeProfileData *pShapeData)
//{
//   CString strNodeName = L"Profile_LBody";
//   WriteShapeList(strNodeName,pShapeData->m_LShapeData);
//   strNodeName = L"Profile_RBody";
//   WriteShapeList(strNodeName,pShapeData->m_RShapeData);
//   strNodeName = L"Profile_LNeck";
//   WriteShapeList(strNodeName,pShapeData->m_VLShapeData);
//   strNodeName = L"Profile_RNeck";
//   WriteShapeList(strNodeName,pShapeData->m_VRShapeData);
//
//   strNodeName = L"Cycle_LBody";
//   WriteCycleData(strNodeName,pShapeData->m_vectLCycle);
//   strNodeName = L"Cycle_RBody";
//   WriteCycleData(strNodeName,pShapeData->m_vectRCycle);
//   strNodeName = L"Cycle_LNeck";
//   WriteCycleData(strNodeName,pShapeData->m_vectLNCycle);
//   strNodeName = L"Cycle_RNeck";
//   WriteCycleData(strNodeName,pShapeData->m_vectRNCycle);
//   return TRUE;
//}

//-------------------------------------------------------------
//第二部分机型选项
//BOOL CFileShapeGye::ReadMacTypeData(CShapeProfileData *pShapeData)
//{
//   //获取根节点
//   TiXmlElement * pXMLSelectedEle = NULL;
//   GetShapeSubNode(_T("MachineType"),&pXMLSelectedEle);
//   if (NULL == pXMLSelectedEle)
//   {
//      return FALSE;
//   }
//   int iNoteValue;
//   if(TIXML_SUCCESS ==pXMLSelectedEle->QueryIntAttribute("bottomexist",&iNoteValue))
//      pShapeData->IsBottomExist =(BOOL) iNoteValue;
//   if(TIXML_SUCCESS ==pXMLSelectedEle->QueryIntAttribute("machinetype",&iNoteValue))
//      pShapeData->m_nMachineType =(ShapeSpace::Sys_Type) iNoteValue;
//   if(TIXML_SUCCESS ==pXMLSelectedEle->QueryIntAttribute("zhixuanzhenMac",&iNoteValue))
//      pShapeData->IsZhiXuanZhen =(BOOL) iNoteValue;
//   pShapeData->m_CombType = (CString)pXMLSelectedEle->Attribute("combtype");
//   if(TIXML_SUCCESS ==pXMLSelectedEle->QueryIntAttribute("needletrans",&iNoteValue))
//      pShapeData->m_nNeedleTrans =(ShapeSpace::NeedleTrans_Type) iNoteValue;
//
//   pShapeData->iMianshaCenterNum =(CString)pXMLSelectedEle->Attribute("iMianshaCenterNum");
//   if (pShapeData->iMianshaCenterNum == _T(""))
//   {
//      pShapeData->iMianshaCenterNum = _T("0");
//   }
//   if(TIXML_SUCCESS ==pXMLSelectedEle->QueryIntAttribute("bIsMianshaCenter",&iNoteValue))
//      pShapeData->bIsMianshaCenter =(BOOL) iNoteValue;
//   else 
//      pShapeData->bIsMianshaCenter = 0 ;
//   if(TIXML_SUCCESS ==pXMLSelectedEle->QueryIntAttribute("enBodySizeFlag",&iNoteValue))
//      pShapeData->enBodySizeFlag =(ShapeSpace::BODYSIZEFLAG) iNoteValue;
//   else
//      pShapeData->enBodySizeFlag = ShapeSpace::enSize_XS;
//   if(TIXML_SUCCESS ==pXMLSelectedEle->QueryIntAttribute("enBodySizeType",&iNoteValue))
//      pShapeData->enBodySizeType =(ShapeSpace::BODYSIZETYPE) iNoteValue;
//   else
//      pShapeData->enBodySizeType = ShapeSpace::enSizeType_diaomu;
//   return TRUE;
//}

//BOOL CFileShapeGye::WriteMacTypeData(CShapeProfileData *pShapeData)
//{
//   //查找同名节点并删除 
//   TiXmlElement * pXMLRootEle  = m_pDoc->RootElement();
//   TiXmlElement * pFindNode = pXMLRootEle->FirstChildElement("MachineType");
//   if (NULL != pFindNode)
//   {
//      TiXmlNode* pDelnode = pFindNode; 
//      pXMLRootEle->RemoveChild(pDelnode);
//   }
//   //新建MachineType节点
//   TiXmlElement *elmMachine=new TiXmlElement("MachineType");
//   pXMLRootEle->LinkEndChild(elmMachine);
//
//
//   elmMachine->SetAttribute("bottomexist",(int)pShapeData->IsBottomExist); 
//   elmMachine->SetAttribute("machinetype",(int)pShapeData->m_nMachineType);
//   elmMachine->SetAttribute("zhixuanzhenMac",(int)pShapeData->IsZhiXuanZhen);
//   std::string chSign = RnString::WCStr2StrACP(pShapeData->m_CombType);
//   elmMachine->SetAttribute("combtype",chSign.c_str());
//   elmMachine->SetAttribute("needletrans",(int)pShapeData->m_nNeedleTrans);
//   std::string mianshaNum = RnString::WCStr2StrACP(pShapeData->iMianshaCenterNum);
//   elmMachine->SetAttribute("iMianshaCenterNum",/*(int)*/mianshaNum);
//   elmMachine->SetAttribute("bIsMianshaCenter",(int)pShapeData->bIsMianshaCenter);
//   elmMachine->SetAttribute("enBodySizeFlag",(int)pShapeData->enBodySizeFlag);
//   elmMachine->SetAttribute("enBodySizeType",(int)pShapeData->enBodySizeType);
//   return TRUE;
//}
//-------------------------------------------------------------
//第三部分大身选项
BOOL CFileShapeGye::ReadBodySetData(CShapeProfileData *pShapeData)
{
   //获取根节点
   TiXmlElement * pXMLSelectedEle = NULL;
   GetShapeSubNode(_T("BodyType"),&pXMLSelectedEle);
   if (NULL == pXMLSelectedEle)
   {
      return FALSE;
   }
   int iNoteValue;
   //if(TIXML_SUCCESS ==pXMLSelectedEle->QueryIntAttribute("IsBodySymmetry",&iNoteValue))
   //   pShapeData->IsBodySymmetry =(BOOL) iNoteValue;
   //if(TIXML_SUCCESS ==pXMLSelectedEle->QueryIntAttribute("IsNeckSymmetry",&iNoteValue))
   //   pShapeData->IsNeckSymmetry =(BOOL) iNoteValue;
   //if(TIXML_SUCCESS ==pXMLSelectedEle->QueryIntAttribute("StartWidth",&iNoteValue))
   //   pShapeData->m_iStartWidth =(UINT) iNoteValue;
   //if(TIXML_SUCCESS ==pXMLSelectedEle->QueryIntAttribute("nNeedleType",&iNoteValue))
   //   pShapeData->m_nNeedleType =(ShapeSpace::Row_Type) iNoteValue;
   //if(TIXML_SUCCESS ==pXMLSelectedEle->QueryIntAttribute("StartOffset",&iNoteValue))
   //   pShapeData->m_iStartOffset =(int) iNoteValue;
   if(TIXML_SUCCESS ==pXMLSelectedEle->QueryIntAttribute("ShapeType",&iNoteValue))
      pShapeData->m_enShapeType =(ShapeSpace::Shape_Type) iNoteValue;


   return TRUE;
}
BOOL CFileShapeGye::WriteBodySetData(CShapeProfileData *pShapeData)
{
   TiXmlElement * pXMLRootEle = m_pDoc->RootElement();
   TiXmlElement * pFindNode = pXMLRootEle->FirstChildElement("BodyType");
   if (NULL == pFindNode)
   {
      TiXmlElement *elmBody=new TiXmlElement("BodyType");
      pXMLRootEle->LinkEndChild(elmBody);
   }

   TiXmlElement *elmBody = pXMLRootEle->FirstChildElement("BodyType");
   if (NULL == pFindNode)
   {
      return FALSE;
   }

   //elmBody->SetAttribute("IsBodySymmetry",(int)pShapeData->IsBodySymmetry);
   //elmBody->SetAttribute("IsNeckSymmetry",(int)pShapeData->IsNeckSymmetry);
   //elmBody->SetAttribute("StartWidth",(int)pShapeData->m_iStartWidth);
   //elmBody->SetAttribute("nNeedleType",(int)pShapeData->m_nNeedleType);
   //elmBody->SetAttribute("StartOffset",(int)pShapeData->m_iStartOffset);
   elmBody->SetAttribute("ShapeType",(int)pShapeData->m_enShapeType);
   return TRUE;
}


//第四部分V领设置部分

BOOL CFileShapeGye :: ReadNeckSetData(CShapeProfileData *pShapeData)
{
   //获取根节点
   TiXmlElement * pXMLSelectedEle = NULL;
   GetShapeSubNode(_T("NeckSet"),&pXMLSelectedEle);
   if (NULL == pXMLSelectedEle)
   {
      return FALSE;
   }
   int iNoteValue;
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("NeckType",&iNoteValue))
   //   pShapeData->m_nNeckType =(ShapeSpace::Neck_Type) iNoteValue;
   if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("NeckSplit",&iNoteValue))
      pShapeData->m_bNeckSplit =(BYTE) iNoteValue;
   if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("isBottmsprate",&iNoteValue))
      pShapeData->m_isBottomSeparate =(BOOL) iNoteValue;
   if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("isNeckSplit",&iNoteValue))
      pShapeData->m_isNeckSeparate =(bool) iNoteValue;
   if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("isVneckYTX",&iNoteValue))
      pShapeData->m_isVneckYTX =(BOOL) iNoteValue;
  /* if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("NeedleSafeNO",&iNoteValue))
      pShapeData->m_bNeedleSafeNO =(BYTE) iNoteValue;
   if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("NeckStartWidth",&iNoteValue))
      pShapeData->m_iNeckStartWidth =(int) iNoteValue;
   if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("NeckOffSet",&iNoteValue))
      pShapeData->m_iNeckOffSet =(int) iNoteValue;
   if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("NeckAutoHeight",&iNoteValue))
		pShapeData->m_bNeckAutoHeight =(BOOL) iNoteValue;
   if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("NeckStartHeight",&iNoteValue))
      pShapeData->m_iNeckStartHeight =(int) iNoteValue;*/
   if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("Enecktype",&iNoteValue))
      pShapeData->m_nEnecktype =(ShapeSpace::ENeck_Type) iNoteValue;
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("bVNeckCZ",&iNoteValue))
   //   pShapeData->m_bVNeckCZ =(BOOL) iNoteValue;
   //else
   //   pShapeData->m_bVNeckCZ = FALSE;
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("bDeleteCenterLine",&iNoteValue))
   //   pShapeData->m_bDeleteCenterLine =(BOOL) iNoteValue;
   //else
   //   pShapeData->m_bDeleteCenterLine = FALSE;

	if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("m_bTiHuaShouZhen",&iNoteValue))
		pShapeData->m_bTiHuaShouZhen =(BOOL) iNoteValue;
	else
	{
		pShapeData->m_bTiHuaShouZhen = (_T("shuangmiantihua") == pShapeData->m_ModData.m_strTransType);
	}

 //  if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("m_IsTrans",&iNoteValue))
	//   pShapeData->m_IsTrans =(BOOL) iNoteValue;
 //  else
	//   pShapeData->m_IsTrans = FALSE;

 //  if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("m_iLoopCount",&iNoteValue))
	//   pShapeData->m_iLoopCount = iNoteValue;
 //  else
	//   pShapeData->m_iLoopCount = 1;
   return TRUE;
}
BOOL CFileShapeGye :: WriteNeckSetData(CShapeProfileData *pShapeData)
{
   TiXmlElement * pXMLRootEle = m_pDoc->RootElement();
   TiXmlElement * elmneck = pXMLRootEle->FirstChildElement("NeckSet");
   if (NULL == elmneck)
   {
      elmneck=new TiXmlElement("NeckSet");
      pXMLRootEle->LinkEndChild(elmneck);
   }


   //elmneck->SetAttribute("NeckType",(int)pShapeData->m_nNeckType);
   elmneck->SetAttribute("NeckSplit",(int)pShapeData->m_bNeckSplit);
   elmneck->SetAttribute("isBottmsprate",(int)pShapeData->m_isBottomSeparate);
   elmneck->SetAttribute("isNeckSplit",(int)pShapeData->m_isNeckSeparate);
   elmneck->SetAttribute("isVneckYTX",(int)pShapeData->m_isVneckYTX);
 //  elmneck->SetAttribute("NeedleSafeNO",(int)pShapeData->m_bNeedleSafeNO);
 //  elmneck->SetAttribute("NeckStartWidth",(int)pShapeData->m_iNeckStartWidth);
 //  elmneck->SetAttribute("NeckOffSet",(int)pShapeData->m_iNeckOffSet);
	//elmneck->SetAttribute("NeckAutoHeight",(int)pShapeData->m_bNeckAutoHeight);
 //  elmneck->SetAttribute("NeckStartHeight",(int)pShapeData->m_iNeckStartHeight);
   elmneck->SetAttribute("Enecktype",(int)pShapeData->m_nEnecktype);
   //elmneck->SetAttribute("bVNeckCZ",(int)pShapeData->m_bVNeckCZ);
	//elmneck->SetAttribute("bDeleteCenterLine",(int)pShapeData->m_bDeleteCenterLine);
	elmneck->SetAttribute("m_bTiHuaShouZhen",(int)pShapeData->m_bTiHuaShouZhen);
   //elmneck->SetAttribute("m_IsTrans",(int)pShapeData->m_IsTrans);
   //elmneck->SetAttribute("m_iLoopCount",(int)pShapeData->m_iLoopCount);
   return TRUE;
}

////第五部分 收针设置部分
BOOL CFileShapeGye::ReadNeedleSetData(CShapeProfileData *pShapeData)
{
   //获取根节点
   TiXmlElement * pXMLSelectedEle = NULL;
   GetShapeSubNode(_T("NeedleLessType"),&pXMLSelectedEle);
   if (NULL == pXMLSelectedEle)
   {
      return FALSE;
   }
   //TiXmlElement * pXMLSelectedEle2=pXMLSelectedEle->FirstChildElement("FrontKnit") ;//前编织 
   //if (pXMLSelectedEle2==NULL)
   //{
   //   return FALSE;
   //}
   //TiXmlElement * pXMLSelectedEle3=pXMLSelectedEle->FirstChildElement("Frontsign");
   //if (pXMLSelectedEle3==NULL)
   //{
   //   return FALSE;
   //}
   //int  iNoteValue,keyId;
   //CString NoteStr;
   //TYPE_VEC_KNITSIGN temp;
   //if (NULL!=pXMLSelectedEle2)
   //{
   //   if(TIXML_SUCCESS ==pXMLSelectedEle2->QueryIntAttribute("leftsign",&iNoteValue))
   //      pShapeData->m_NeedleSigns.bFrontLMarkSign =(BYTE) iNoteValue;
   //   if(TIXML_SUCCESS ==pXMLSelectedEle2->QueryIntAttribute("rightsign",&iNoteValue))
   //      pShapeData->m_NeedleSigns.bFrontRMarkSign =(BYTE) iNoteValue;
   //}
   //for ( ;NULL != pXMLSelectedEle3;pXMLSelectedEle3 = pXMLSelectedEle3->NextSiblingElement("Frontsign"))
   //{
   //   if(TIXML_SUCCESS ==pXMLSelectedEle3->QueryIntAttribute("key",&keyId))
   //   {

   //      NoteStr=pXMLSelectedEle3->Attribute("leftbody");
   //      temp.empty();
   //      temp=GetBianmaInt(NoteStr);
   //      pShapeData->m_NeedleSigns.vecFrontLTranSigns[keyId]=temp;
   //      NoteStr=pXMLSelectedEle3->Attribute("rightbody");
   //      temp.empty();
   //      temp=GetBianmaInt(NoteStr);
   //      pShapeData->m_NeedleSigns.vecFrontRTranSigns[keyId]=temp;
   //      NoteStr=pXMLSelectedEle3->Attribute("leftneck");
   //      temp.empty();
   //      temp=GetBianmaInt(NoteStr);
   //      pShapeData->m_NeedleSigns.vecFrontNeckLTranSigns[keyId]=temp;
   //      NoteStr=pXMLSelectedEle3->Attribute("rightneck");
   //      temp.empty();
   //      temp=GetBianmaInt(NoteStr);
   //      pShapeData->m_NeedleSigns.vecFrontNeckRTranSigns[keyId]=temp;
   //   }

   //}
   ///////////////////////////////////////
   //pXMLSelectedEle2=pXMLSelectedEle->FirstChildElement("BackKnit") ;//后编织 
   //if (pXMLSelectedEle2==NULL)
   //{
   //   return FALSE;
   //}
   //pXMLSelectedEle3=pXMLSelectedEle->FirstChildElement("Backsign");
   //if (pXMLSelectedEle3==NULL)
   //{
   //   return FALSE;
   //}
   //if(TIXML_SUCCESS == pXMLSelectedEle2->QueryIntAttribute("leftsign",&iNoteValue))
   //   pShapeData->m_NeedleSigns.bBackLMarkSign =(BYTE) iNoteValue;
   //if(TIXML_SUCCESS == pXMLSelectedEle2->QueryIntAttribute("rightsign",&iNoteValue))
   //   pShapeData->m_NeedleSigns.bBackRMarkSign =(BYTE) iNoteValue;
   //for ( ;NULL != pXMLSelectedEle3;pXMLSelectedEle3 = pXMLSelectedEle3->NextSiblingElement("Backsign"))
   //{
   //   if(TIXML_SUCCESS == pXMLSelectedEle3->QueryIntAttribute("key",&keyId))
   //   {
   //      NoteStr=pXMLSelectedEle3->Attribute("leftbody");
   //      temp.empty();
   //      temp=GetBianmaInt(NoteStr);
   //      pShapeData->m_NeedleSigns.vecBackLTranSigns[keyId]=temp;
   //      NoteStr=pXMLSelectedEle3->Attribute("rightbody");
   //      temp.empty();
   //      temp=GetBianmaInt(NoteStr);
   //      pShapeData->m_NeedleSigns.vecBackRTranSigns[keyId]=temp;
   //      NoteStr=pXMLSelectedEle3->Attribute("leftneck");
   //      temp.empty();
   //      temp=GetBianmaInt(NoteStr);
   //      pShapeData->m_NeedleSigns.vecBackNeckLTranSigns[keyId]=temp;
   //      NoteStr=pXMLSelectedEle3->Attribute("rightneck");
   //      temp.empty();
   //      temp=GetBianmaInt(NoteStr);
   //      pShapeData->m_NeedleSigns.vecBackNeckRTranSigns[keyId]=temp;
   //   }
   //}
   //////////////平收 收针方式
   int iNoteValue = 0;
   TiXmlElement * pXMLSelectedEle2=pXMLSelectedEle->FirstChildElement("NeedleLessSet");
   if (pXMLSelectedEle2==NULL)
   {
      return FALSE;
   }
   if(TIXML_SUCCESS == pXMLSelectedEle2->QueryIntAttribute("FlatNeedleType",&iNoteValue))
      pShapeData->m_NeedleSigns.m_nFlatType =(ShapeSpace::NeedleFlat_Type) iNoteValue;
   /*if(TIXML_SUCCESS == pXMLSelectedEle2->QueryIntAttribute("bodyneedle2type",&iNoteValue))
      pShapeData->m_NeedleSigns.m_bodyneedle2type =(ShapeSpace::Reduce_Type) iNoteValue;
   if(TIXML_SUCCESS == pXMLSelectedEle2->QueryIntAttribute("bodyneedle3type",&iNoteValue))
      pShapeData->m_NeedleSigns.m_bodyneedle3type =(ShapeSpace::Reduce_Type) iNoteValue;
   if(TIXML_SUCCESS == pXMLSelectedEle2->QueryIntAttribute("neckneedle2type",&iNoteValue))
      pShapeData->m_NeedleSigns.m_neckneedle2type =(ShapeSpace::Reduce_Type) iNoteValue;
   if(TIXML_SUCCESS == pXMLSelectedEle2->QueryIntAttribute("neckneedle3type",&iNoteValue))
      pShapeData->m_NeedleSigns.m_neckneedle3type =(ShapeSpace::Reduce_Type) iNoteValue;*/

   return TRUE;
}

//TYPE_VEC_KNITSIGN CFileShapeGye::GetBianmaInt(CString str)
//{
//   CString temp;
//   TYPE_VEC_KNITSIGN bianma_temp;
//   int pos=0;
//   int size;
//   while (str.Find(_T(","),0)!=-1)
//   {
//      size=str.GetLength();
//      pos=str.Find(_T(","),0);
//      temp=str.Left(pos);
//      str=str.Right(size-pos-1);
//      bianma_temp.push_back(_tstoi(temp));
//   }
//   if (str!="")
//   {
//      bianma_temp.push_back(_tstoi(str));
//   }
//   return bianma_temp;
//}

//CString CFileShapeGye::GetBianma(TYPE_VEC_KNITSIGN data)
//{
//   int size,m_iter;
//   CString strBianma,temp;
//   strBianma=_T("");
//   size=data.size();
//   if (size)
//   {
//      strBianma.Format(_T("%d"),data[0]);
//      for(m_iter=1;m_iter<size;m_iter++)
//      {
//         temp.Format(_T(",%d"),data[m_iter]);
//         strBianma+=temp;
//      }
//   }
//   return strBianma;
//}


BOOL CFileShapeGye::WriteNeedleSetData(CShapeProfileData *pShapeData)
{
   TYPE_MAP_SIGN::iterator iter;
   //CString strtemp;
   //int i;
   TiXmlElement * pXMLRootEle  = m_pDoc->RootElement();
   TiXmlElement * pFindNode = pXMLRootEle->FirstChildElement("NeedleLessType");
   std::string char_temp;
   if (NULL==pFindNode)//删除收针设置节点
   {
      TiXmlElement *elmneedle=new TiXmlElement("NeedleLessType");
      pXMLRootEle->LinkEndChild(elmneedle);
   }

   TiXmlElement * elmneedle = pXMLRootEle->FirstChildElement("NeedleLessType");
   if (NULL==pFindNode)//删除收针设置节点
   {
      return FALSE;
   }

   //TiXmlElement *elmneedleKnit=new TiXmlElement("FrontKnit");//前编织
   //elmneedle->LinkEndChild(elmneedleKnit);
   //elmneedleKnit->SetAttribute("leftsign",(int)pShapeData->m_NeedleSigns.bFrontLMarkSign);
   //elmneedleKnit->SetAttribute("rightsign",(int)pShapeData->m_NeedleSigns.bFrontRMarkSign);
   //for(i=0;i<7;i++)
   //{
   //   TiXmlElement *elmneedleknit2=new TiXmlElement("Frontsign");
   //   elmneedle->LinkEndChild(elmneedleknit2);
   //   elmneedleknit2->SetAttribute("key",i+1);
   //   strtemp=GetBianma(pShapeData->m_NeedleSigns.vecFrontLTranSigns[i+1]);
   //   char_temp = RnString::WCStr2StrACP(strtemp);
   //   elmneedleknit2->SetAttribute("leftbody",char_temp.c_str());
   //   strtemp=GetBianma(pShapeData->m_NeedleSigns.vecFrontRTranSigns[i+1]);
   //   char_temp=RnString::WCStr2StrACP(strtemp);
   //   elmneedleknit2->SetAttribute("rightbody",char_temp.c_str());
   //   strtemp=GetBianma(pShapeData->m_NeedleSigns.vecFrontNeckLTranSigns[i+1]);
   //   char_temp=RnString::WCStr2StrACP(strtemp);
   //   elmneedleknit2->SetAttribute("leftneck",char_temp.c_str());
   //   strtemp=GetBianma(pShapeData->m_NeedleSigns.vecFrontNeckRTranSigns[i+1]);
   //   char_temp=RnString::WCStr2StrACP(strtemp);
   //   elmneedleknit2->SetAttribute("rightneck",char_temp.c_str());
   //}
   ///*delete elmneedleKnit;*/
   //elmneedleKnit=new TiXmlElement("BackKnit");//后编织
   //elmneedle->LinkEndChild(elmneedleKnit);
   //elmneedleKnit->SetAttribute("leftsign",(int)pShapeData->m_NeedleSigns.bBackLMarkSign);
   //elmneedleKnit->SetAttribute("rightsign",(int)pShapeData->m_NeedleSigns.bBackRMarkSign);
   //for(i=0;i<7;i++)
   //{
   //   TiXmlElement *elmneedleknit2=new TiXmlElement("Backsign");
   //   elmneedle->LinkEndChild(elmneedleknit2);
   //   elmneedleknit2->SetAttribute("key",i+1);
   //   strtemp=GetBianma(pShapeData->m_NeedleSigns.vecBackLTranSigns[i+1]);
   //   char_temp=RnString::WCStr2StrACP(strtemp);
   //   elmneedleknit2->SetAttribute("leftbody",char_temp.c_str());
   //   strtemp=GetBianma(pShapeData->m_NeedleSigns.vecBackRTranSigns[i+1]);
   //   char_temp=RnString::WCStr2StrACP(strtemp);
   //   elmneedleknit2->SetAttribute("rightbody",char_temp.c_str());
   //   strtemp=GetBianma(pShapeData->m_NeedleSigns.vecBackNeckLTranSigns[i+1]);
   //   char_temp=RnString::WCStr2StrACP(strtemp);
   //   elmneedleknit2->SetAttribute("leftneck",char_temp.c_str());
   //   strtemp=GetBianma(pShapeData->m_NeedleSigns.vecBackNeckRTranSigns[i+1]);
   //   char_temp=RnString::WCStr2StrACP(strtemp);
   //   elmneedleknit2->SetAttribute("rightneck",char_temp.c_str());
   //}

   TiXmlElement * elmneedleKnit = elmneedle->FirstChildElement("NeedleLessSet");
   if (NULL==elmneedleKnit)//删除收针设置节点
   {
      elmneedleKnit=new TiXmlElement("NeedleLessSet");//收针设置
      elmneedle->LinkEndChild(elmneedleKnit);
   }

   elmneedleKnit->SetAttribute("FlatNeedleType",(int)pShapeData->m_NeedleSigns.m_nFlatType);
   //elmneedleKnit->SetAttribute("bodyneedle2type",(int)pShapeData->m_NeedleSigns.m_bodyneedle2type);
   //elmneedleKnit->SetAttribute("bodyneedle3type",(int)pShapeData->m_NeedleSigns.m_bodyneedle3type);
   //elmneedleKnit->SetAttribute("neckneedle2type",(int)pShapeData->m_NeedleSigns.m_neckneedle2type);
   //elmneedleKnit->SetAttribute("neckneedle3type",(int)pShapeData->m_NeedleSigns.m_neckneedle3type);
   return TRUE;
}

///第六部分 其他设置部分
BOOL CFileShapeGye::ReadOtherSetData(CShapeProfileData *pShapeData)
{
   //获取根节点
   TiXmlElement * pXMLSelectedEle = NULL;
   GetShapeSubNode(_T("OtherSet"),&pXMLSelectedEle);
   if (NULL == pXMLSelectedEle)
   {
      return FALSE;
   }
   int iNoteValue;
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("MinSuspendNeedleNum",&iNoteValue))
   //   pShapeData->m_OtherParamSet.iMinSuspendNeedleNum =(UINT) iNoteValue;
   if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("CottonRowNum",&iNoteValue))
      pShapeData->m_OtherParamSet.iCottonRowNum =(UINT) iNoteValue;
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("LessColor",&iNoteValue))
   //   pShapeData->m_OtherParamSet.LessColor =(BYTE) iNoteValue;
   //#4373 分别翻针的check和listbox里面的0：使不能分别翻针矛盾 start Duchen 2017/04/25 13:14 dc170424
   /*if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("bColorFBFZ",&iNoteValue))
      pShapeData->m_OtherParamSet.m_fbfz =(BYTE) iNoteValue;
   else
      pShapeData->m_OtherParamSet.m_fbfz = 5;*/
   //#4373 分别翻针的check和listbox里面的0：使不能分别翻针矛盾 end   Duchen 2017/04/25 13:14
   /*if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("Cottontype",&iNoteValue))
      pShapeData->m_OtherParamSet.m_nCottontype =(ShapeSpace::Cotton_Type) iNoteValue;
   if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("DoubleRibColor",&iNoteValue))
      pShapeData->m_OtherParamSet.DoubleRibColor =(BYTE) iNoteValue;
   if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("Ribtype",&iNoteValue))
      pShapeData->m_OtherParamSet.m_nRibtype =(ShapeSpace::Rib_Type) iNoteValue;
   if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("RibSaving",&iNoteValue))
      pShapeData->m_OtherParamSet.m_bRibSaving =(BOOL) iNoteValue;
   if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("ModeJDM",&iNoteValue))
      pShapeData->m_OtherParamSet.ModeJDM =(UINT) iNoteValue;
   if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("AutoNeckCenter",&iNoteValue))
      pShapeData->m_OtherParamSet.m_bAutoNeckCenter =(BOOL) iNoteValue;
   if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("SeperateLine",&iNoteValue))
      pShapeData->m_OtherParamSet.m_bSeperateLine =(BOOL) iNoteValue;
   if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("VNeckYarn",&iNoteValue))
      pShapeData->m_OtherParamSet.m_bVNeckYarn =(BOOL) iNoteValue;*/
   if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("AddType",&iNoteValue))
      pShapeData->m_OtherParamSet.m_AddType =(ShapeSpace::Add_Type) iNoteValue;
	/*if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("CancelType",&iNoteValue))
		pShapeData->m_OtherParamSet.m_cancelType =(ShapeSpace::CANCEL_TYPE) iNoteValue;
	else
		pShapeData->m_OtherParamSet.m_cancelType = ShapeSpace::en_Cancel_NON;

	if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("m_bDaiShaDaJie",&iNoteValue))
		pShapeData->m_OtherParamSet.m_bDaiShaDaJie = (BOOL) iNoteValue;
	else
		pShapeData->m_OtherParamSet.m_bDaiShaDaJie = TRUE;

	if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("m_bDaiShaOut",&iNoteValue))
		pShapeData->m_OtherParamSet.m_bDaiShaOut = (BOOL) iNoteValue;
	else
		pShapeData->m_OtherParamSet.m_bDaiShaOut = FALSE;

   if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("Youxiao",&iNoteValue))
      pShapeData->m_OtherParamSet.effectiveNum =(UINT) iNoteValue;
   if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("Notdo",&iNoteValue))
      pShapeData->m_OtherParamSet.iNotTreatmentNeedle =(int) iNoteValue;
   if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("huiti",&iNoteValue))
      pShapeData->m_OtherParamSet.iYarnKickBackNeedle =(int) iNoteValue;
   if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("iNeckUseOneYarn",&iNoteValue))
      pShapeData->m_OtherParamSet.iNeckUseOneYarn =(int) iNoteValue;*/
   if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("iFeiShaOneYarn",&iNoteValue))
      pShapeData->m_OtherParamSet.m_IsAbandon_Oneyarn =(BOOL) iNoteValue;
   if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("abandon_rowcount",&iNoteValue))
      pShapeData->m_OtherParamSet.m_uAbandon_RowCount = iNoteValue;
 //  if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("bJiaBPs",&iNoteValue))
 //     pShapeData->m_OtherParamSet.m_bJiaBPs = (BOOL)iNoteValue;
 //  if(TIXML_SUCCESS ==pXMLSelectedEle->QueryIntAttribute("bPackMode",&iNoteValue))
 //     pShapeData->m_OtherParamSet.m_bPackMode =(BOOL) iNoteValue;
 //  else
 //     pShapeData->m_OtherParamSet.m_bPackMode = 0;
 //  if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("bCZTuck",&iNoteValue))
 //     pShapeData->m_OtherParamSet.m_bCZTuck = iNoteValue;
 //  else 
 //     pShapeData->m_OtherParamSet.m_bCZTuck = 1;
 //  if(TIXML_SUCCESS ==pXMLSelectedEle->QueryIntAttribute("bAllQidiMode",&iNoteValue))
 //     pShapeData->m_OtherParamSet.m_bFeiShaAllQidiMode =(BOOL) iNoteValue;
 //  else
 //     pShapeData->m_OtherParamSet.m_bFeiShaAllQidiMode = 0;


 //  if(TIXML_SUCCESS ==pXMLSelectedEle->QueryIntAttribute("m_bAutoPressYarnMode",&iNoteValue))
 //     pShapeData->m_OtherParamSet.m_bAutoPressYarnMode =(BOOL) iNoteValue;
 //  else
 //     pShapeData->m_OtherParamSet.m_bAutoPressYarnMode = TRUE;

 //  if(TIXML_SUCCESS ==pXMLSelectedEle->QueryIntAttribute("m_bAutoPressYarnUseWasteYarn",&iNoteValue))
 //     pShapeData->m_OtherParamSet.m_bAutoPressYarnUseWasteYarn =(BOOL) iNoteValue;
 //  else
 //     pShapeData->m_OtherParamSet.m_bAutoPressYarnUseWasteYarn = TRUE;

   if(TIXML_SUCCESS ==pXMLSelectedEle->QueryIntAttribute("m_iLiuBianZS",&iNoteValue))
	   pShapeData->m_OtherParamSet.m_iLiuBianZS =(BOOL) iNoteValue;
   else
	   pShapeData->m_OtherParamSet.m_iLiuBianZS = 4;

 //  if(TIXML_SUCCESS ==pXMLSelectedEle->QueryIntAttribute("ClipYarnPos",&iNoteValue))
 //     pShapeData->m_OtherParamSet.m_ClipYarnPos = iNoteValue;
 //  else
 //     pShapeData->m_OtherParamSet.m_ClipYarnPos = 61;
 //  

	//if(TIXML_SUCCESS ==pXMLSelectedEle->QueryIntAttribute("m_bChaiXian",&iNoteValue))
	//	pShapeData->m_OtherParamSet.m_bChaiXian = (BOOL)iNoteValue;
	//else
	//	pShapeData->m_OtherParamSet.m_bChaiXian = FALSE;

	//if(TIXML_SUCCESS ==pXMLSelectedEle->QueryIntAttribute("m_bVLDiJiaoHua",&iNoteValue))
	//	pShapeData->m_OtherParamSet.m_bVLDiJiaoHua = (BOOL)iNoteValue;
	//else
	//	pShapeData->m_OtherParamSet.m_bVLDiJiaoHua = FALSE;

	//if(TIXML_SUCCESS ==pXMLSelectedEle->QueryIntAttribute("m_enJLTuckColor",&iNoteValue))
	//	pShapeData->m_OtherParamSet.m_enJLTuckColor = (ShapeSpace::JIADLINGTUCK)iNoteValue;
	//else
	//	pShapeData->m_OtherParamSet.m_enJLTuckColor = ShapeSpace::enJLTuck;

	//if(TIXML_SUCCESS ==pXMLSelectedEle->QueryIntAttribute("m_nCZType",&iNoteValue))
	//	pShapeData->m_OtherParamSet.m_nCZType = (ShapeSpace::CHANZHENTUCK)iNoteValue;
	//else
	//	pShapeData->m_OtherParamSet.m_nCZType = ShapeSpace::enTuck;

 //  //#4629 V领产针时，因产针次数少了一次，造成中留 针变多 start Duchen 2017/08/22 10:00 dc160821
 //  if(TIXML_SUCCESS ==pXMLSelectedEle->QueryIntAttribute("m_nVNeckCZType",&iNoteValue))
 //     pShapeData->m_OtherParamSet.m_nVNeckCZType = (ShapeSpace::VNECKCHANZHENTYPE)iNoteValue;
 //  else
 //     pShapeData->m_OtherParamSet.m_nVNeckCZType = ShapeSpace::enBoLiuZhenFirst;
 //  //#4629 V领产针时，因产针次数少了一次，造成中留 针变多 end   Duchen 2017/08/22 10:00

	//if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("m_jiadmgd",&iNoteValue))
	//	pShapeData->m_OtherParamSet.m_jiadmgd =(UINT)iNoteValue;
	//else
	//	pShapeData->m_OtherParamSet.m_jiadmgd = 0;

 //  //#4373 分别翻针的check和listbox里面的0：使不能分别翻针矛盾 start Duchen 2017/04/25 13:14 dc170424
 //  int nIsFBFZ = 0;
 //  if(TIXML_SUCCESS != pXMLSelectedEle->QueryIntAttribute("bFBFZ", &nIsFBFZ))
 //  {
 //      pShapeData->m_OtherParamSet.m_fbfz = 1; //以前没有选项,22功能线是1号色
 //  }
 //  else
 //  {
 //     if (nIsFBFZ == FALSE)
 //     {
 //        pShapeData->m_OtherParamSet.m_fbfz = 1; //以前选项不打勾,22功能线是1号色
 //     }
 //     else
 //     {
 //        int nFBFZColor = 0;
 //        if(TIXML_SUCCESS != pXMLSelectedEle->QueryIntAttribute("bColorFBFZ", &nFBFZColor))
 //           pShapeData->m_OtherParamSet.m_fbfz = 5; //以前只有勾选，没下拉，22功能线就是5号色
 //        else
 //           pShapeData->m_OtherParamSet.m_fbfz = static_cast<BYTE>(nFBFZColor);
 //     }
 //  }
 //  pShapeData->m_OtherParamSet.m_bFBFZ = TRUE;
   /*if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("bFBFZ",&iNoteValue))
      pShapeData->m_OtherParamSet.m_bFBFZ = (BOOL)iNoteValue;
   else 
      pShapeData->m_OtherParamSet.m_bFBFZ = FALSE;*/
   //#4373 分别翻针的check和listbox里面的0：使不能分别翻针矛盾 end   Duchen 2017/04/25 13:14

   ////#3663 成型参数添加废纱纱出、橡筋纱出选项 start Duchen 2016/09/26 11:36 dc160926
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("m_bRubYarnOut",&iNoteValue))
   //   pShapeData->m_OtherParamSet.m_bRubYarnOut = (BOOL)iNoteValue;
   //else 
   //   pShapeData->m_OtherParamSet.m_bRubYarnOut = TRUE;

   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("m_bRubberYarnOut",&iNoteValue))
   //   pShapeData->m_OtherParamSet.m_bRubberYarnOut = (BOOL)iNoteValue;
   //else 
   //   pShapeData->m_OtherParamSet.m_bRubberYarnOut = TRUE;
   ////#3663 成型参数添加废纱纱出、橡筋纱出选项 end   Duchen 2016/09/26 11:36

   //#3665 开领新增单纱嘴废纱方式 start Duchen 2017/12/12 17:58 dc161211
   if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("m_bSingleSplitYarnNeck",&iNoteValue))
      pShapeData->m_OtherParamSet.m_bSingleSplitYarnNeck = (BOOL)iNoteValue;
   else 
      pShapeData->m_OtherParamSet.m_bSingleSplitYarnNeck = FALSE;
   //#3665 开领新增单纱嘴废纱方式 end   Duchen 2017/12/12 17:58

   if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("KaisFlatNeedleType",&iNoteValue))
      pShapeData->m_OtherParamSet.m_nKaiSFlatType =(ShapeSpace::NeedleFlat_Type) iNoteValue;
   else
      pShapeData->m_OtherParamSet.m_nKaiSFlatType = pShapeData->m_NeedleSigns.m_nFlatType;

   if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("NeckFlatNeedleType",&iNoteValue))
      pShapeData->m_OtherParamSet.m_nNeckFlatType =(ShapeSpace::NeedleFlat_Type) iNoteValue;
   else
      pShapeData->m_OtherParamSet.m_nNeckFlatType = pShapeData->m_NeedleSigns.m_nFlatType;

   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("m_iQiJiaZhuanshu",&iNoteValue))
   //   pShapeData->m_OtherParamSet.m_iQiJiaZhuanshu =(int) iNoteValue;
   //else
   //   pShapeData->m_OtherParamSet.m_iQiJiaZhuanshu =pShapeData->m_OtherParamSet.m_uAbandon_RowCount/2;

   ////#3111 平收落布拉针行数设置 start Duchen 2016/08/03 14:02 dc160801
   ////elmneck->SetAttribute("m_nFlatReduceLuoBuLineCount",(int)pShapeData->m_OtherParamSet.m_nFlatReduceLuoBuLineCount);
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("m_nFlatReduceLuoBuLineCount",&iNoteValue))
   //   pShapeData->m_OtherParamSet.m_nFlatReduceLuoBuLineCount =(int) iNoteValue;
   //else
   //   pShapeData->m_OtherParamSet.m_nFlatReduceLuoBuLineCount = 5;
   ////#3111 平收落布拉针行数设置 end   Duchen 2016/08/03 14:02
   ////自动剪刀夹子 yangjr 2016-11-3
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("m_bAutoCutClip",&iNoteValue))
   //   pShapeData->m_OtherParamSet.m_bAutoCutClip = (BOOL)iNoteValue;
   //else 
   //   pShapeData->m_OtherParamSet.m_bAutoCutClip = TRUE;

   ////ZB-381 成型增加纱嘴自动对齐功能选项 start Duchen 2018/07/06 17:11 dc180702
   //if (TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("m_bYarnInAutoAlign",&iNoteValue))
   //   pShapeData->m_OtherParamSet.m_bYarnInAutoAlign = (BOOL)iNoteValue;
   //else
   //   pShapeData->m_OtherParamSet.m_bYarnInAutoAlign = FALSE;
   ////ZB-381 成型增加纱嘴自动对齐功能选项 end   Duchen 2018/07/06 17:11

   ////ZB-962 成型设置：其他页面新增参数“落布行数” start Duchen 2020/07/22 16:29 dc200720
   //if (TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("m_nLuoBuHangShu",&iNoteValue))
   //   pShapeData->m_OtherParamSet.m_nLuoBuHangShu = (int)iNoteValue;
   //else
   //   pShapeData->m_OtherParamSet.m_nLuoBuHangShu = 4;
   ////ZB-962 成型设置：其他页面新增参数“落布行数” end   Duchen 2020/07/22 16:29
   return TRUE;
}
BOOL CFileShapeGye::WriteOtherSetData(CShapeProfileData *pShapeData)
{
   TiXmlElement * pXMLRootEle = m_pDoc->RootElement();
   TiXmlElement * elmneck = pXMLRootEle->FirstChildElement("OtherSet");
   if (NULL == elmneck)
   {
      elmneck=new TiXmlElement("OtherSet");
      pXMLRootEle->LinkEndChild(elmneck);
   }

   //elmneck->SetAttribute("MinSuspendNeedleNum",(int)pShapeData->m_OtherParamSet.iMinSuspendNeedleNum);
   elmneck->SetAttribute("CottonRowNum",(int)pShapeData->m_OtherParamSet.iCottonRowNum);
 //  elmneck->SetAttribute("LessColor",(int)pShapeData->m_OtherParamSet.LessColor);
 //  elmneck->SetAttribute("bColorFBFZ",(int)pShapeData->m_OtherParamSet.m_fbfz);
 //  elmneck->SetAttribute("Cottontype",(int)pShapeData->m_OtherParamSet.m_nCottontype);
 //  elmneck->SetAttribute("DoubleRibColor",(int)pShapeData->m_OtherParamSet.DoubleRibColor);
 //  elmneck->SetAttribute("Ribtype",(int)pShapeData->m_OtherParamSet.m_nRibtype);
 //  elmneck->SetAttribute("RibSaving",(int)pShapeData->m_OtherParamSet.m_bRibSaving);//
 //  elmneck->SetAttribute("ModeJDM",(int)pShapeData->m_OtherParamSet.ModeJDM);
 //  elmneck->SetAttribute("AutoNeckCenter",(int)pShapeData->m_OtherParamSet.m_bAutoNeckCenter);
 //  elmneck->SetAttribute("SeperateLine",(int)pShapeData->m_OtherParamSet.m_bSeperateLine);
 //  elmneck->SetAttribute("VNeckYarn",(int)pShapeData->m_OtherParamSet.m_bVNeckYarn);
   elmneck->SetAttribute("AddType",(int)pShapeData->m_OtherParamSet.m_AddType);
	//elmneck->SetAttribute("CancelType",(int)pShapeData->m_OtherParamSet.m_cancelType);
	//elmneck->SetAttribute("m_bDaiShaDaJie",(int)pShapeData->m_OtherParamSet.m_bDaiShaDaJie);
	//elmneck->SetAttribute("m_bDaiShaOut",(int)pShapeData->m_OtherParamSet.m_bDaiShaOut);
 //  elmneck->SetAttribute("Youxiao",(int)pShapeData->m_OtherParamSet.effectiveNum);
 //  elmneck->SetAttribute("Notdo",(int)pShapeData->m_OtherParamSet.iNotTreatmentNeedle);
 //  elmneck->SetAttribute("huiti",(int)pShapeData->m_OtherParamSet.iYarnKickBackNeedle);
 //  elmneck->SetAttribute("iNeckUseOneYarn",(int)pShapeData->m_OtherParamSet.iNeckUseOneYarn);
   elmneck->SetAttribute("iFeiShaOneYarn",(int)pShapeData->m_OtherParamSet.m_IsAbandon_Oneyarn);
   elmneck->SetAttribute("abandon_rowcount",pShapeData->m_OtherParamSet.m_uAbandon_RowCount);
 //  elmneck->SetAttribute("m_iQiJiaZhuanshu",(int)pShapeData->m_OtherParamSet.m_iQiJiaZhuanshu);
 //  elmneck->SetAttribute("bJiaBPs",pShapeData->m_OtherParamSet.m_bJiaBPs);
 //  elmneck->SetAttribute("bPackMode",pShapeData->m_OtherParamSet.m_bPackMode);
 //  elmneck->SetAttribute("bCZTuck",pShapeData->m_OtherParamSet.m_bCZTuck);
 //  elmneck->SetAttribute("bAllQidiMode",pShapeData->m_OtherParamSet.m_bFeiShaAllQidiMode);
 //  elmneck->SetAttribute("m_bAutoPressYarnMode",pShapeData->m_OtherParamSet.m_bAutoPressYarnMode);
 //  elmneck->SetAttribute("m_bAutoPressYarnUseWasteYarn",pShapeData->m_OtherParamSet.m_bAutoPressYarnUseWasteYarn);
   elmneck->SetAttribute("m_iLiuBianZS",pShapeData->m_OtherParamSet.m_iLiuBianZS);
 //  elmneck->SetAttribute("ClipYarnPos",pShapeData->m_OtherParamSet.m_ClipYarnPos);
	//elmneck->SetAttribute("m_bChaiXian",pShapeData->m_OtherParamSet.m_bChaiXian);
	//elmneck->SetAttribute("m_bVLDiJiaoHua",pShapeData->m_OtherParamSet.m_bVLDiJiaoHua);
	//elmneck->SetAttribute("m_enJLTuckColor",pShapeData->m_OtherParamSet.m_enJLTuckColor);
	//elmneck->SetAttribute("m_nCZType",pShapeData->m_OtherParamSet.m_nCZType);

 //  //#4629 V领产针时，因产针次数少了一次，造成中留 针变多 start Duchen 2017/08/22 10:00 dc160821
 //  elmneck->SetAttribute("m_nVNeckCZType", pShapeData->m_OtherParamSet.m_nVNeckCZType);
 //  //#4629 V领产针时，因产针次数少了一次，造成中留 针变多 end   Duchen 2017/08/22 10:00

 //  elmneck->SetAttribute("m_jiadmgd",pShapeData->m_OtherParamSet.m_jiadmgd);
 //  elmneck->SetAttribute("bFBFZ",pShapeData->m_OtherParamSet.m_bFBFZ);
 //  //#3663 成型参数添加废纱纱出、橡筋纱出选项 start Duchen 2016/09/26 11:36 dc160926
 //  elmneck->SetAttribute("m_bRubYarnOut",pShapeData->m_OtherParamSet.m_bRubYarnOut);
 //  elmneck->SetAttribute("m_bRubberYarnOut",pShapeData->m_OtherParamSet.m_bRubberYarnOut);
 //  //#3663 成型参数添加废纱纱出、橡筋纱出选项 end   Duchen 2016/09/26 11:36

   //#3665 开领新增单纱嘴废纱方式 start Duchen 2017/12/12 17:58 dc161211
   elmneck->SetAttribute("m_bSingleSplitYarnNeck", pShapeData->m_OtherParamSet.m_bSingleSplitYarnNeck);
   //#3665 开领新增单纱嘴废纱方式 end   Duchen 2017/12/12 17:58

   elmneck->SetAttribute("KaisFlatNeedleType",(int)pShapeData->m_OtherParamSet.m_nKaiSFlatType);
   elmneck->SetAttribute("NeckFlatNeedleType",(int)pShapeData->m_OtherParamSet.m_nNeckFlatType);
   ////#3111 平收落布拉针行数设置 start Duchen 2016/08/03 14:02 dc160801
   //elmneck->SetAttribute("m_nFlatReduceLuoBuLineCount",(int)pShapeData->m_OtherParamSet.m_nFlatReduceLuoBuLineCount);
   ////#3111 平收落布拉针行数设置 end   Duchen 2016/08/03 14:02
   //elmneck->SetAttribute("m_bAutoCutClip",pShapeData->m_OtherParamSet.m_bAutoCutClip);//自动剪刀夹子 yangjr 

   ////ZB-381 成型增加纱嘴自动对齐功能选项 start Duchen 2018/07/06 17:11 dc180702
   //elmneck->SetAttribute("m_bYarnInAutoAlign",pShapeData->m_OtherParamSet.m_bYarnInAutoAlign);
   ////ZB-381 成型增加纱嘴自动对齐功能选项 end   Duchen 2018/07/06 17:11

   ////ZB-962 成型设置：其他页面新增参数“落布行数” start Duchen 2020/07/22 16:29 dc200720
   //elmneck->SetAttribute("m_nLuoBuHangShu",pShapeData->m_OtherParamSet.m_nLuoBuHangShu);
   ////ZB-962 成型设置：其他页面新增参数“落布行数” end   Duchen 2020/07/22 16:29
   return TRUE;
}

BOOL CFileShapeGye::ReadBottomSetData(CShapeProfileData *pShapeData)
{
   //获取根节点
   TiXmlElement * pXMLSelectedEle = NULL;
   GetShapeSubNode(_T("BottomSet"),&pXMLSelectedEle);
   if (NULL == pXMLSelectedEle)
   {
      return FALSE;
   }
   int iNoteValue;
   /*if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("ModWidth",&iNoteValue))
      pShapeData->m_ModData.m_uModWidth =(UINT) iNoteValue;
   else
      pShapeData->m_ModData.m_uModWidth = 0 ;
   if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("FBKint",&iNoteValue))pShapeData->m_ModData.m_enFBKnit =(ShapeSpace::FroBkNeedle) iNoteValue;*/
   if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("Luobu",&iNoteValue))pShapeData->m_ModData.m_enLuoBu =(ShapeSpace::QHLuoBu) iNoteValue;
   //pShapeData->m_ModData.m_strModType=pXMLSelectedEle->Attribute("ModType");
   pShapeData->m_ModData.m_strTransType=pXMLSelectedEle->Attribute("TRansType");
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("MacType",&iNoteValue))pShapeData->m_ModData.m_enMacType =(ShapeSpace::Sys_Type) iNoteValue;

   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("Revolution",&iNoteValue))pShapeData->m_ModData.m_dRevolution =(double)iNoteValue/2;
   //else pShapeData->m_ModData.m_dRevolution = 0;

   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("EmptyRevolution",&iNoteValue))pShapeData->m_ModData.m_dEmptyRevolution =(double)iNoteValue/2;
   //else pShapeData->m_ModData.m_dEmptyRevolution = 0;
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("LWJiaSi",&iNoteValue))pShapeData->m_ModData.m_uLWJiasi =(int)iNoteValue;
   //else 
   //   pShapeData->m_ModData.m_uLWJiasi = 0;
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("IsLWJiaSi",&iNoteValue))pShapeData->m_ModData.Is_LWJiaSi =(BOOL)iNoteValue;
   //else 
   //   pShapeData->m_ModData.Is_LWJiaSi = 0;
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("BottonExist",&iNoteValue))pShapeData->m_ModData.IsBottomExist =(BOOL) iNoteValue;
   //else pShapeData->m_ModData.IsBottomExist = 0;
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("VlFlag",&iNoteValue))pShapeData->m_ModData.IsVLFlag =(BOOL) iNoteValue;
   //else pShapeData->m_ModData.IsVLFlag = 0;

   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("m_isHouQiKongZhuan",&iNoteValue))pShapeData->m_ModData.m_isHouQiKongZhuan =(BOOL) iNoteValue; //新增后起底空转 2015222 LIINYP
   //else pShapeData->m_ModData.m_isHouQiKongZhuan = 0;

   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("BianZJ",&iNoteValue))pShapeData->m_ModData.m_BZJ =(ShapeSpace::NeedleTrans_Type) iNoteValue;
   //pShapeData->m_ModData.m_strCombType=pXMLSelectedEle->Attribute("CombType");
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("FistYarn",&iNoteValue))pShapeData->m_ModData.m_FirstShaZui =(int) iNoteValue;
   //else pShapeData->m_ModData.m_FirstShaZui = 0;
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("SecondYarn",&iNoteValue))pShapeData->m_ModData.m_SecondShaZui =(int) iNoteValue;
   //else pShapeData->m_ModData.m_SecondShaZui = 0;
   return TRUE;
}

BOOL CFileShapeGye::WriteBottomSetData(CShapeProfileData *pShapeData)
{
   TiXmlElement * pXMLRootEle = m_pDoc->RootElement();
   TiXmlElement * elmbottomtype = pXMLRootEle->FirstChildElement("BottomSet");
   if (NULL == elmbottomtype)
   {
      elmbottomtype=new TiXmlElement("BottomSet");
      pXMLRootEle->LinkEndChild(elmbottomtype);
   }

   std::string char_temp;
   //elmbottomtype->SetAttribute("ModWidth",(int)pShapeData->m_ModData.m_uModWidth);
   //elmbottomtype->SetAttribute("FBKint",(int)pShapeData->m_ModData.m_enFBKnit);
   elmbottomtype->SetAttribute("Luobu",(int)pShapeData->m_ModData.m_enLuoBu);
   //char_temp = RnString::WCStr2StrACP(pShapeData->m_ModData.m_strModType);
   //elmbottomtype->SetAttribute("ModType",char_temp.c_str());
   char_temp=RnString::WCStr2StrACP(pShapeData->m_ModData.m_strTransType);
   elmbottomtype->SetAttribute("TRansType",char_temp.c_str());
   //elmbottomtype->SetAttribute("MacType",(int)pShapeData->m_ModData.m_enMacType);
   //elmbottomtype->SetAttribute("Revolution",(int)(pShapeData->m_ModData.m_dRevolution*2));
   //elmbottomtype->SetAttribute("EmptyRevolution",(int)(pShapeData->m_ModData.m_dEmptyRevolution*2));
   //elmbottomtype->SetAttribute("LWJiaSi",(int)(pShapeData->m_ModData.m_uLWJiasi));
   //elmbottomtype->SetAttribute("IsLWJiaSi",(int)(pShapeData->m_ModData.Is_LWJiaSi));
   //elmbottomtype->SetAttribute("BottonExist",(int)pShapeData->m_ModData.IsBottomExist);
   //elmbottomtype->SetAttribute("VlFlag",(int)pShapeData->m_ModData.IsVLFlag);
   //elmbottomtype->SetAttribute("m_isHouQiKongZhuan",(int)pShapeData->m_ModData.m_isHouQiKongZhuan); //新增后起底空转 2015222 LIINYP
   //elmbottomtype->SetAttribute("BianZJ",(int)pShapeData->m_ModData.m_BZJ);
   //char_temp=RnString::WCStr2StrACP(pShapeData->m_ModData.m_strCombType);
   //elmbottomtype->SetAttribute("CombType",char_temp.c_str());
   //elmbottomtype->SetAttribute("FistYarn",(int)pShapeData->m_ModData.m_FirstShaZui);
   //elmbottomtype->SetAttribute("SecondYarn",(int)pShapeData->m_ModData.m_SecondShaZui);


   return TRUE;
}
///////////////////段数与纱嘴
BOOL CFileShapeGye::WriteParamSetData(CShapeProfileData *pShapeData)
{
   TiXmlElement * pXMLRootEle = m_pDoc->RootElement();
   TiXmlElement * elmparam = pXMLRootEle->FirstChildElement("ParamSet");
   if (NULL == elmparam)
   {
      elmparam=new TiXmlElement("ParamSet");
      pXMLRootEle->LinkEndChild(elmparam);
   }

   //elmparam->SetAttribute("paraBirdEyes",(int)pShapeData->m_ParamSet.paraBirdEyes.Idex);
   //elmparam->SetAttribute("paraFullNeedle",(int)pShapeData->m_ParamSet.paraFullNeedle.Idex);
   //elmparam->SetAttribute("paraSplitYarn",(int)pShapeData->m_ParamSet.paraSplitYarn.Idex);
   //elmparam->SetAttribute("paraMainYarn",(int)pShapeData->m_ParamSet.paraMainYarn.Idex);
   //elmparam->SetAttribute("paraMainRacing ",(int)pShapeData->m_ParamSet.paraMainRacing.Idex);

   //elmparam->SetAttribute("paraRibbingKnit",(int)pShapeData->m_ParamSet.paraRibbingKnit.Idex);
   //elmparam->SetAttribute("paraTransition",(int)pShapeData->m_ParamSet.paraTransition.Idex);
   //elmparam->SetAttribute("paraBody",(int)pShapeData->m_ParamSet.paraBody.Idex);
   //elmparam->SetAttribute("paraFlatInsert_Left",(int)pShapeData->m_ParamSet.paraFlatInsert_Left.Idex);
   //elmparam->SetAttribute("paraFlatInsert_Right",(int)pShapeData->m_ParamSet.paraFlatInsert_Right.Idex);

   //elmparam->SetAttribute("paraAutoInsert",(int)pShapeData->m_ParamSet.paraAutoInsert.Idex);
   //elmparam->SetAttribute("paraVNeck",(int)pShapeData->m_ParamSet.paraVNeck.Idex);
   //elmparam->SetAttribute("paraVNeck_Left",(int)pShapeData->m_ParamSet.paraVNeck_Left.Idex);
   //elmparam->SetAttribute("paraVNeck_Right",(int)pShapeData->m_ParamSet.paraVNeck_Right.Idex);
   ////ZB-804 增加一个V领拆行的速度段数 start Duchen 2020/07/30 14:40 dc200727
   //elmparam->SetAttribute("paraVNeckSpeed_Left",(int)pShapeData->m_ParamSet.paraVNeckSpeed_Left.Idex);
   //elmparam->SetAttribute("paraVNeckSpeed_Right",(int)pShapeData->m_ParamSet.paraVNeckSpeed_Right.Idex);
   ////ZB-804 增加一个V领拆行的速度段数 end   Duchen 2020/07/30 14:40
   //elmparam->SetAttribute("paraDoffing1",(int)pShapeData->m_ParamSet.paraDoffing1.Idex);

   //elmparam->SetAttribute("paraCircleNeck",(int)pShapeData->m_ParamSet.paraCircleNeck.Idex);
   //elmparam->SetAttribute("paraDoffing2",(int)pShapeData->m_ParamSet.paraDoffing2.Idex);
   //elmparam->SetAttribute("paraCotton",(int)pShapeData->m_ParamSet.paraCotton.Idex);
   //elmparam->SetAttribute("paraTransNeedle",(int)pShapeData->m_ParamSet.paraTransNeedle.Idex);
   //elmparam->SetAttribute("paraPPYarn",(int)pShapeData->m_ParamSet.paraPPYarn.Idex);
   //elmparam->SetAttribute("paraDxj",(int)pShapeData->m_ParamSet.paraDxj.Idex);   //新增底橡筋 20151221 LINYP
   //elmparam->SetAttribute("paraComb",(int)pShapeData->m_ParamSet.paraComb.Idex);
   ////#2393 成型缩针行翻针度目拉力等可以单独设置一段度目 start Duchen 2016/08/24 16:38 dc160822
   //elmparam->SetAttribute("paraSuoZhen", (int)pShapeData->m_ParamSet.paraSuoZhen.Idex);
   ////#2393 成型缩针行翻针度目拉力等可以单独设置一段度目 end   Duchen 2016/08/24 16:38
   ////#3346 全提花 结束时自动添加翻单面（用主纱做单面编织一转） start Duchen 2016/09/05 15:17 dc160905
   //elmparam->SetAttribute("paraQuanTiHuaTaoKou", (int)pShapeData->m_ParamSet.paraQuanTiHuaTaoKou.Idex);
   //elmparam->SetAttribute("paraQuanTiHuaTaoKouFangSong", (int)pShapeData->m_ParamSet.paraQuanTiHuaTaoKouFangSong.Idex);
   ////#3346 全提花 结束时自动添加翻单面（用主纱做单面编织一转） end   Duchen 2016/09/05 15:17

   ////ZB-950 沙嘴和段数增加局部提花度目段设置 start Duchen 2020/08/13 10:17 dc200810
   //elmparam->SetAttribute("paraJuBuTiHua", (int)pShapeData->m_ParamSet.paraJuBuTiHua.Idex);
   ////ZB-950 沙嘴和段数增加局部提花度目段设置 end   Duchen 2020/08/13 10:17

   ////ZB-746 收针度目放松 start Duchen 2019/05/05 15:15 dc190429
   //elmparam->SetAttribute("paraShouZhenDumuFangSong", (int)pShapeData->m_ParamSet.paraShouZhenDumuFangSong.Idex);
   ////ZB-746 收针度目放松 end   Duchen 2019/05/05 15:15
   ////ZB-784 坯布增加头尾放松属性，转制版自动在头尾设置放松度目 start Duchen 2019/09/29 17:52 dc190923
   //elmparam->SetAttribute("paraAttachmentLoosen", (int)pShapeData->m_ParamSet.paraAttachmentLoosen.Idex);
   //elmparam->SetAttribute("paraAttachmentTightYuanTong", (int)pShapeData->m_ParamSet.paraAttachmentTightYuanTong.Idex);
   //elmparam->SetAttribute("paraAttachmentSipin", (int)pShapeData->m_ParamSet.paraAttachmentSipin.Idex);
   ////ZB-784 坯布增加头尾放松属性，转制版自动在头尾设置放松度目 end   Duchen 2019/09/29 17:52
   //elmparam->SetAttribute("m_bMainYarnFirst",(int)pShapeData->m_ParamSet.m_bMainYarnFirst);
   //elmparam->SetAttribute("m_bMainYarnSec",(int)pShapeData->m_ParamSet.m_bMainYarnSec);
   //elmparam->SetAttribute("m_bRubYarnFirst",(int)pShapeData->m_ParamSet.m_bRubYarnFirst);
   //elmparam->SetAttribute("m_bRubYarnSec",(int)pShapeData->m_ParamSet.m_bRubYarnSec);
   ////elmparam->SetAttribute("m_NeckYarn",(int)pShapeData->m_ParamSet.m_NeckYarn);
   elmparam->SetAttribute("m_IsBoarOneYarn",(int)pShapeData->m_ParamSet.m_IsOneYarn);

   //elmparam->SetAttribute("bLuoWenYarn",(int)pShapeData->m_ParamSet.bLuoWenYarn);

   ////#5652 沙嘴和段数增加罗纹沙嘴1 start Duchen 2017/12/05 15:26 dc171205
   //elmparam->SetAttribute("m_byLuoWnYarn1", (int)pShapeData->m_ParamSet.m_byLuoWnYarn1);
   ////#5652 沙嘴和段数增加罗纹沙嘴1 end   Duchen 2017/12/05 15:26

   //elmparam->SetAttribute("bPPYarn",(int)pShapeData->m_ParamSet.bPPYarn);
   //elmparam->SetAttribute("bLwJsYarn",(int)pShapeData->m_ParamSet.bLwJsYarn);
   //elmparam->SetAttribute("bRubberYarn",(int)pShapeData->m_ParamSet.bRubberYarn);
   //elmparam->SetAttribute("bDxjYarn",(int)pShapeData->m_ParamSet.bDxjYarn); //新增底橡筋 20151221 LINYP
   elmparam->SetAttribute("bSetSecYarnLeft",(int)pShapeData->m_ParamSet.bSetSecYarnLeft);
   elmparam->SetAttribute("bSetWasteSecYarnLeft",(int)pShapeData->m_ParamSet.bSetWasteSecYarnLeft);
   ////#4497 stoll部分机型纱嘴在右边，希望我们成型设计可以支持大身纱嘴2、废纱纱嘴2在右边 start Duchen 2017/03/03 10:11 dc170227
   //elmparam->SetAttribute("m_bAllYarnRight",(int)pShapeData->m_ParamSet.m_bAllYarnRight);
   ////#4497 stoll部分机型纱嘴在右边，希望我们成型设计可以支持大身纱嘴2、废纱纱嘴2在右边 end   Duchen 2017/03/03 10:11
   //elmparam->SetAttribute("paramset",(int)pShapeData->m_ParamSet.m_nParamType);
	elmparam->SetAttribute("m_NeckIsOneYarn",(int)pShapeData->m_ParamSet.m_NeckIsOneYarn);
   ////#2912 成型支持单纱嘴最开领分边织 start Duchen 2016/07/20 10:16 dc160718
   //elmparam->SetAttribute("m_NeckIsOneYarnTwoWay",(int)pShapeData->m_ParamSet.m_bNeckOneYarnTwoWay);
   ////#2912 成型支持单纱嘴最开领分边织 end   Duchen 2016/07/20 10:16
   return TRUE;
}
BOOL CFileShapeGye::ReadParamSetData(CShapeProfileData *pShapeData)
{
   //获取根节点
   TiXmlElement * pXMLSelectedEle = NULL;
   GetShapeSubNode(_T("ParamSet"),&pXMLSelectedEle);
   if (NULL == pXMLSelectedEle)
   {
      return FALSE;
   }
   int iNoteValue;
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("paraBirdEyes",&iNoteValue))pShapeData->m_ParamSet.paraBirdEyes.Idex =(BYTE) iNoteValue;
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("paraFullNeedle",&iNoteValue))pShapeData->m_ParamSet.paraFullNeedle.Idex =(BYTE) iNoteValue;
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("paraSplitYarn",&iNoteValue))pShapeData->m_ParamSet.paraSplitYarn.Idex =(BYTE) iNoteValue;
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("paraMainYarn",&iNoteValue))pShapeData->m_ParamSet.paraMainYarn.Idex =(BYTE) iNoteValue;
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("paraMainRacing",&iNoteValue))pShapeData->m_ParamSet.paraMainRacing.Idex =(BYTE) iNoteValue;
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("paraRibbingKnit",&iNoteValue))pShapeData->m_ParamSet.paraRibbingKnit.Idex =(BYTE) iNoteValue;
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("paraTransition",&iNoteValue))pShapeData->m_ParamSet.paraTransition.Idex =(BYTE) iNoteValue;
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("paraBody",&iNoteValue))pShapeData->m_ParamSet.paraBody.Idex =(BYTE) iNoteValue;
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("paraFlatInsert_Left",&iNoteValue))pShapeData->m_ParamSet.paraFlatInsert_Left.Idex =(BYTE) iNoteValue;
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("paraFlatInsert_Right",&iNoteValue))pShapeData->m_ParamSet.paraFlatInsert_Right.Idex =(BYTE) iNoteValue;
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("paraAutoInsert",&iNoteValue))pShapeData->m_ParamSet.paraAutoInsert.Idex =(BYTE) iNoteValue;
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("paraVNeck",&iNoteValue))pShapeData->m_ParamSet.paraVNeck.Idex =(BYTE) iNoteValue;
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("paraVNeck_Left",&iNoteValue))pShapeData->m_ParamSet.paraVNeck_Left.Idex =(BYTE) iNoteValue;
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("paraVNeck_Right",&iNoteValue))pShapeData->m_ParamSet.paraVNeck_Right.Idex =(BYTE) iNoteValue;
   ////ZB-804 增加一个V领拆行的速度段数 start Duchen 2020/07/30 14:40 dc200727
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("paraVNeckSpeed_Left",&iNoteValue))
   //   pShapeData->m_ParamSet.paraVNeckSpeed_Left.Idex =(BYTE) iNoteValue;
   //else
   //   pShapeData->m_ParamSet.paraVNeckSpeed_Left.Idex =(BYTE) pShapeData->m_ParamSet.paraBody.Idex;
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("paraVNeckSpeed_Right",&iNoteValue))
   //   pShapeData->m_ParamSet.paraVNeckSpeed_Right.Idex =(BYTE) iNoteValue;
   //else
   //   pShapeData->m_ParamSet.paraVNeckSpeed_Right.Idex =(BYTE) pShapeData->m_ParamSet.paraBody.Idex;
   ////ZB-804 增加一个V领拆行的速度段数 end   Duchen 2020/07/30 14:40
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("paraDoffing1",&iNoteValue))pShapeData->m_ParamSet.paraDoffing1.Idex =(BYTE) iNoteValue;

   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("paraCircleNeck",&iNoteValue))pShapeData->m_ParamSet.paraCircleNeck.Idex =(BYTE) iNoteValue;
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("paraDoffing2",&iNoteValue))pShapeData->m_ParamSet.paraDoffing2.Idex =(BYTE) iNoteValue;
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("paraCotton",&iNoteValue))pShapeData->m_ParamSet.paraCotton.Idex =(BYTE) iNoteValue;
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("paraTransNeedle",&iNoteValue))pShapeData->m_ParamSet.paraTransNeedle.Idex =(BYTE) iNoteValue;
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("paraPPYarn",&iNoteValue))pShapeData->m_ParamSet.paraPPYarn.Idex =(BYTE) iNoteValue;
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("paraDxj",&iNoteValue))pShapeData->m_ParamSet.paraDxj.Idex =(BYTE) iNoteValue;  //新增底橡筋 20151221 LINYP
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("paraComb",&iNoteValue))pShapeData->m_ParamSet.paraComb.Idex =(BYTE) iNoteValue;
   ////ZB-746 收针度目放松 start Duchen 2019/05/05 15:15 dc190429
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("paraShouZhenDumuFangSong",&iNoteValue))pShapeData->m_ParamSet.paraShouZhenDumuFangSong.Idex =(BYTE) iNoteValue;
   ////ZB-746 收针度目放松 end   Duchen 2019/05/05 15:15
   ////#2393 成型缩针行翻针度目拉力等可以单独设置一段度目 start Duchen 2016/08/24 16:38 dc160822
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("paraSuoZhen", &iNoteValue))pShapeData->m_ParamSet.paraSuoZhen.Idex = (BYTE)iNoteValue;
   ////#2393 成型缩针行翻针度目拉力等可以单独设置一段度目 end   Duchen 2016/08/24 16:38
   ////#3346 全提花 结束时自动添加翻单面（用主纱做单面编织一转） start Duchen 2016/09/05 15:17 dc160905
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("paraQuanTiHuaTaoKou", &iNoteValue))
   //   pShapeData->m_ParamSet.paraQuanTiHuaTaoKou.Idex = (BYTE)iNoteValue;
   //else
   //   pShapeData->m_ParamSet.paraQuanTiHuaTaoKou.Idex = pShapeData->m_ParamSet.paraBody.Idex;
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("paraQuanTiHuaTaoKouFangSong", &iNoteValue))
   //   pShapeData->m_ParamSet.paraQuanTiHuaTaoKouFangSong.Idex = (BYTE)iNoteValue;
   //else
   //   pShapeData->m_ParamSet.paraQuanTiHuaTaoKouFangSong.Idex = pShapeData->m_ParamSet.paraBody.Idex;

   ////ZB-950 沙嘴和段数增加局部提花度目段设置 start Duchen 2020/08/13 10:17 dc200810
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("paraJuBuTiHua", &iNoteValue))
   //    pShapeData->m_ParamSet.paraJuBuTiHua.Idex = (BYTE)iNoteValue;
   //else
   //    pShapeData->m_ParamSet.paraJuBuTiHua.Idex = 0;
   ////ZB-950 沙嘴和段数增加局部提花度目段设置 end   Duchen 2020/08/13 10:17

   ////ZB-784 坯布增加头尾放松属性，转制版自动在头尾设置放松度目 start Duchen 2019/09/29 17:52 dc190923
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("paraAttachmentLoosen",&iNoteValue))pShapeData->m_ParamSet.paraAttachmentLoosen.Idex =(BYTE) iNoteValue;
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("paraAttachmentTightYuanTong",&iNoteValue))pShapeData->m_ParamSet.paraAttachmentTightYuanTong.Idex =(BYTE) iNoteValue;
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("paraAttachmentSipin",&iNoteValue))pShapeData->m_ParamSet.paraAttachmentSipin.Idex =(BYTE) iNoteValue;
   ////ZB-784 坯布增加头尾放松属性，转制版自动在头尾设置放松度目 end   Duchen 2019/09/29 17:52

   ////#3346 全提花 结束时自动添加翻单面（用主纱做单面编织一转） end   Duchen 2016/09/05 15:17
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("m_bMainYarnFirst",&iNoteValue))pShapeData->m_ParamSet.m_bMainYarnFirst =(BYTE) iNoteValue;
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("m_bMainYarnSec",&iNoteValue))pShapeData->m_ParamSet.m_bMainYarnSec =(BYTE) iNoteValue;
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("m_bRubYarnFirst",&iNoteValue))pShapeData->m_ParamSet.m_bRubYarnFirst =(BYTE) iNoteValue;
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("m_bRubYarnSec",&iNoteValue))pShapeData->m_ParamSet.m_bRubYarnSec =(BYTE) iNoteValue;
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("m_NeckYarn",&iNoteValue))pShapeData->m_ParamSet.m_NeckYarn =(BYTE) iNoteValue;
   if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("m_IsBoarOneYarn",&iNoteValue))pShapeData->m_ParamSet.m_IsOneYarn =(BOOL) iNoteValue;
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("bLuoWenYarn",&iNoteValue))pShapeData->m_ParamSet.bLuoWenYarn =(BYTE) iNoteValue;

   ////#5652 沙嘴和段数增加罗纹沙嘴1 start Duchen 2017/12/05 15:26 dc171205
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("m_byLuoWnYarn1", &iNoteValue))
   //   pShapeData->m_ParamSet.m_byLuoWnYarn1 = (BYTE)iNoteValue;
   //else
   //   pShapeData->m_ParamSet.m_byLuoWnYarn1 = pShapeData->m_ParamSet.m_bMainYarnFirst;
   ////#5652 沙嘴和段数增加罗纹沙嘴1 end   Duchen 2017/12/05 15:26

   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("bPPYarn",&iNoteValue))
   //   pShapeData->m_ParamSet.bPPYarn =(BYTE) iNoteValue;
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("bLwJsYarn",&iNoteValue))
   //   pShapeData->m_ParamSet.bLwJsYarn =(BYTE) iNoteValue;
   //else
   //   pShapeData->m_ParamSet.bLwJsYarn = 0;
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("bRubberYarn",&iNoteValue))pShapeData->m_ParamSet.bRubberYarn =(BYTE) iNoteValue;
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("bDxjYarn",&iNoteValue))pShapeData->m_ParamSet.bDxjYarn =(BYTE) iNoteValue;//新增底橡筋 20151221 LINYP
   if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("bSetSecYarnLeft",&iNoteValue))pShapeData->m_ParamSet.bSetSecYarnLeft =(BOOL) iNoteValue;
   if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("bSetWasteSecYarnLeft",&iNoteValue))pShapeData->m_ParamSet.bSetWasteSecYarnLeft =(BOOL) iNoteValue;
 //  //#4497 stoll部分机型纱嘴在右边，希望我们成型设计可以支持大身纱嘴2、废纱纱嘴2在右边 start Duchen 2017/03/03 10:11 dc170227
 //  if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("m_bAllYarnRight",&iNoteValue))pShapeData->m_ParamSet.m_bAllYarnRight =(BOOL) iNoteValue;
 //  //#4497 stoll部分机型纱嘴在右边，希望我们成型设计可以支持大身纱嘴2、废纱纱嘴2在右边 end   Duchen 2017/03/03 10:11
	//if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("paramset",&iNoteValue))pShapeData->m_ParamSet.m_nParamType =(ShapeSpace::KnitPara_Type) iNoteValue;
	if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("m_NeckIsOneYarn",&iNoteValue))
		pShapeData->m_ParamSet.m_NeckIsOneYarn =(BOOL) iNoteValue;
	else
	{
      pShapeData->m_ParamSet.m_NeckIsOneYarn = FALSE;
		////旧的GYE是通过单纱嘴开领深度判断是否单纱嘴开领,要做兼容
		//MainShape shapeImp;

		////工艺单数据对称
		//CShapeProfileData fileData = *pShapeData;
		///*if (fileData.IsBodySymmetry)
		//{
		//	fileData.m_RShapeData = fileData.m_LShapeData;
		//	fileData.m_vectRCycle = fileData.m_vectLCycle;
		//}
		//if (fileData.IsNeckSymmetry)
		//{
		//	fileData.m_VRShapeData = fileData.m_VLShapeData;
		//	fileData.m_vectRNCycle = fileData.m_vectLNCycle;
		//}*/
		//pShapeData->m_ParamSet.m_NeckIsOneYarn = shapeImp.NeckUseOneYarn(&fileData);
	}
   ////#2912 成型支持单纱嘴最开领分边织 start Duchen 2016/07/20 10:16 dc160718
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("m_NeckIsOneYarnTwoWay", &iNoteValue))
   //   pShapeData->m_ParamSet.m_bNeckOneYarnTwoWay = (BOOL)iNoteValue;
   ////#2912 成型支持单纱嘴最开领分边织 end   Duchen 2016/07/20 10:16
   return TRUE;
}
////////////保留花样数据
//void CFileShapeGye::ClearBoardDataChange(std::vector<CString> &str_vec,CKnitData &data,BOOL action_idex)
//{
//   //action_idex 为0 则数据转换为字符串，不为0反之
//   CClearBorderCData * cleardata = dynamic_cast<CClearBorderCData*>(&data);
//   if (action_idex == 0)
//   {
//      //处理清边前色码容器
//      TYPE_VEC_CLB::iterator clBoard_iter;
//      TYPE_VEC_KNITSIGN cleardata_vec;
//      cleardata_vec.clear();
//      CString str_temp =L"";
//      clBoard_iter = cleardata->vecClearBorder.begin();
//      for (clBoard_iter ; clBoard_iter != cleardata->vecClearBorder.end(); clBoard_iter++)
//      {
//         cleardata_vec.push_back((BYTE)*clBoard_iter);
//      }
//      str_temp =GetBianma(cleardata_vec);
//      str_vec.push_back(str_temp);
//      str_temp = L"";
//      //处理自定义色码
//      str_temp =GetBianma(cleardata->vecCustomColor);
//      str_vec.push_back(str_temp);
//      str_temp = L"";
//      //清边后色码容器处理
//      str_temp =GetBianma(cleardata->vecFinalColor);
//      str_vec.push_back(str_temp);
//   }
//   else
//   {
//      ASSERT(str_vec.size() == 3);
//      CString str_temp =L"";
//      TYPE_VEC_KNITSIGN datatemp;
//      for (int i = 0 ; i< str_vec.size() ;i ++)
//      {
//         str_temp = str_vec[i];
//         datatemp = GetBianmaInt(str_temp);
//         //处理清边前色码容器
//         if (0 == i)
//         {
//            cleardata->vecClearBorder.clear();
//            for (int idex = 0; idex < datatemp.size() ; idex ++)
//            {
//               cleardata->vecClearBorder.push_back((ShapeSpace::CLEARBORDERTYPE)(datatemp[idex]));
//            }
//         }
//         //处理自定义色码
//         if ( 1 == i)
//         {
//            cleardata->vecCustomColor = datatemp ;
//         }
//         //清边后色码容器处理
//         if (2 == i)
//         {
//            cleardata->vecFinalColor = datatemp ;
//         }
//      }
//   }
//}

BOOL CFileShapeGye::ReadBoardSetData(CShapeProfileData *pShapeData)
{
   //获取根节点
   TiXmlElement * pXMLSelectedEle = NULL;
   GetShapeSubNode(_T("BoardSet"),&pXMLSelectedEle);
   if (NULL == pXMLSelectedEle)
   {
      return FALSE;
   }
   int iNoteValue; 
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("IsKeepPattern",&iNoteValue))pShapeData->IsKeepPattern =(BOOL) iNoteValue;
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("IsKeepIntersia",&iNoteValue))pShapeData->IsKeepIntersia =(BOOL) iNoteValue;
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("IsKeepOpt",&iNoteValue))pShapeData->IsKeepOpt =(BOOL) iNoteValue;
   ////#4168 套图时保留度目图的内容 start Duchen 2017/05/26 9:56 dc160522
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("m_bKeepDumu",&iNoteValue))pShapeData->m_bKeepDumu =(BOOL) iNoteValue;
   ////#4168 套图时保留度目图的内容 end   Duchen 2017/05/26 9:56
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("m_ptCenterX",&iNoteValue))pShapeData->m_ptCenter.x =(LONG) iNoteValue;
   //if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("m_ptCenterY",&iNoteValue))pShapeData->m_ptCenter.y =(LONG) iNoteValue;
   if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("x_Border_up",&iNoteValue))pShapeData->x_Border_up =(UINT) iNoteValue;
   if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("x_Border_down",&iNoteValue))pShapeData->x_Border_down =(UINT) iNoteValue;
   if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("y_Border",&iNoteValue))pShapeData->y_Border =(UINT) iNoteValue;
   //#4066 清边时上留边未使用指定色码清边 start Duchen 2016/11/04 15:02 dc161031
   if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("m_nYNeckBottomBorder",&iNoteValue))pShapeData->m_nYNeckBottomBorder = (UINT)iNoteValue;
   //#4066 清边时上留边未使用指定色码清边 end   Duchen 2016/11/04 15:02
   //清边设置
   /*if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("bClearBorder",&iNoteValue))pShapeData->m_ClearBorderPara.bClearBorder =(BOOL) iNoteValue;
   if(TIXML_SUCCESS == pXMLSelectedEle->QueryIntAttribute("iClearCount",&iNoteValue))pShapeData->m_ClearBorderPara.iClearCount =(int) iNoteValue;*/
   
   //CString str = RnString::Char2WChar(pXMLSelectedEle->Attribute("m_vectModuleInfo"));
   //ReadModuleInfo(str, pShapeData);
   //清边数据转换
   //std::vector<CString> str_clear;
   //str_clear.clear();
   //CString NoteStr;
   //NoteStr=pXMLSelectedEle->Attribute("vecClearBorder");
   //str_clear.push_back(NoteStr);
   //NoteStr=pXMLSelectedEle->Attribute("vecCustomColor");
   //str_clear.push_back(NoteStr);
   //NoteStr=pXMLSelectedEle->Attribute("vecFinalColor");
   //str_clear.push_back(NoteStr);
   //ClearBoardDataChange(str_clear,pShapeData->m_ClearBorderPara,1);
   return TRUE;
}
BOOL CFileShapeGye::WriteBoardSetData(CShapeProfileData *pShapeData)
{
   TiXmlElement * pXMLRootEle = m_pDoc->RootElement();
   TiXmlElement * elmboard = pXMLRootEle->FirstChildElement("BoardSet");
   if (NULL == elmboard)
   {
      elmboard=new TiXmlElement("BoardSet");
      pXMLRootEle->LinkEndChild(elmboard);
   }

   //elmboard->SetAttribute("IsKeepPattern",(int)pShapeData->IsKeepPattern);
   //elmboard->SetAttribute("IsKeepIntersia",(int)pShapeData->IsKeepIntersia);
   //elmboard->SetAttribute("IsKeepOpt",(int)pShapeData->IsKeepOpt);
   ////#4168 套图时保留度目图的内容 start Duchen 2017/05/26 9:56 dc160522
   //elmboard->SetAttribute("m_bKeepDumu",(int)pShapeData->m_bKeepDumu);
   ////#4168 套图时保留度目图的内容 end   Duchen 2017/05/26 9:56
   //elmboard->SetAttribute("m_ptCenterX",(int)pShapeData->m_ptCenter.x);
   //elmboard->SetAttribute("m_ptCenterY",(int)pShapeData->m_ptCenter.y);
   elmboard->SetAttribute("x_Border_up",(int)pShapeData->x_Border_up);
   elmboard->SetAttribute("x_Border_down",(int)pShapeData->x_Border_down);
   elmboard->SetAttribute("y_Border",(int)pShapeData->y_Border);
   //#4066 清边时上留边未使用指定色码清边 start Duchen 2016/11/04 15:02 dc161031
   elmboard->SetAttribute("m_nYNeckBottomBorder",(int)pShapeData->m_nYNeckBottomBorder);
   //#4066 清边时上留边未使用指定色码清边 end   Duchen 2016/11/04 15:02
   //std::string char_temp;

   //CString str;
   //WriteModuleInfo(str, pShapeData);
   //CStringA strA = RnString::WChar2Char(str);
   //elmboard->SetAttribute("m_vectModuleInfo", strA.GetBuffer());

   ////清边设置数据
   //std::vector<CString> str_clear;
   //str_clear.clear();
   ////数据转换
   //ClearBoardDataChange(str_clear,pShapeData->m_ClearBorderPara,0);
   //elmboard->SetAttribute("bClearBorder",(int)pShapeData->m_ClearBorderPara.bClearBorder);
   //elmboard->SetAttribute("iClearCount",(int)pShapeData->m_ClearBorderPara.iClearCount);
   //if (str_clear.size() != 3)
   //{
   //   return FALSE;
   //}
   //char_temp=RnString::WCStr2StrACP(str_clear[0]);
   //elmboard->SetAttribute("vecClearBorder",char_temp.c_str());
   //char_temp=RnString::WCStr2StrACP(str_clear[1]);
   //elmboard->SetAttribute("vecCustomColor",char_temp.c_str());
   //char_temp=RnString::WCStr2StrACP(str_clear[2]);
   //elmboard->SetAttribute("vecFinalColor",char_temp.c_str());
   return TRUE;
}


//--------------------------------------------------------------
//外部接口
//读取成型所有数据
BOOL CFileShapeGye::ReadShapeData(CShapeProfileData *pShapeData)
{

   BOOL rt;
   rt=TRUE;
   //if (!ReadProfileData(m_pShapeData))
   //{
   //   rt= FALSE;
   //}
   //if (!ReadMacTypeData(m_pShapeData))
   //{
   //   rt= FALSE;
   //}

   if(!ReadBodySetData(pShapeData))
   {
      rt= FALSE;
	}
	if (!ReadBottomSetData(pShapeData))
	{
		rt= FALSE;
	}
   if (!ReadNeckSetData(pShapeData))
   {
      rt= FALSE;
   }
   if (!ReadNeedleSetData(pShapeData))
   {
      rt= FALSE;
   }
   if (!ReadOtherSetData(pShapeData))
   {
      rt= FALSE;
   }
   if (!ReadParamSetData(pShapeData))
   {
      rt= FALSE;
   }
   if (!ReadBoardSetData(pShapeData))
   {
      rt= FALSE;
   }
   return rt;
}

//写入成型数据
BOOL CFileShapeGye::WriteShapeData(CShapeProfileData *pShapeData)
{
   //WriteProfileData(m_pShapeData);
   //WriteMacTypeData(m_pShapeData);
   WriteBodySetData(pShapeData);
   WriteNeckSetData(pShapeData);
   WriteNeedleSetData(pShapeData);
   WriteOtherSetData(pShapeData);
   WriteBottomSetData(pShapeData);
   WriteParamSetData(pShapeData);
   WriteBoardSetData(pShapeData);
   return TRUE;
}



//BOOL CFileShapeGye::WriteByStream(CString strFileName)
//{
//   int cbMultiByte = WideCharToMultiByte(CP_ACP,WC_COMPOSITECHECK,strFileName,-1,NULL,0,NULL,NULL);
//   char *pszText = new char[cbMultiByte];
//   memset(pszText,cbMultiByte,sizeof(pszText));
//   WideCharToMultiByte(CP_ACP,WC_COMPOSITECHECK,strFileName,-1,pszText,cbMultiByte,NULL,NULL);
//   m_pDoc->Parse(pszText,NULL,TIXML_DEFAULT_ENCODING);
//   ReadShapeData();
//   delete []pszText;
//   return TRUE;
//}

//BOOL CFileShapeGye::WriteCycleData( CString &strNodeName, MAP_CYCLEARTS &shapelist )
//{
//   TiXmlElement * pXMLRootEle  = m_pDoc->RootElement();
//   int iNoteValue = 0;
//   CString strValue; 
//   CString strTemp;
//   //创建父节点
//   std::string nodeName = RnString::WCStr2StrACP(strNodeName);
//   TiXmlElement *elmProfile=new TiXmlElement(nodeName.c_str());
//
//   //查找同名节点并删除
//   TiXmlElement* pFindNode = pXMLRootEle->FirstChildElement(nodeName.c_str());
//   if (NULL != pFindNode)
//   {
//      TiXmlNode* pDelnode = pFindNode; 
//      pXMLRootEle->RemoveChild(pDelnode);
//   }
//   pXMLRootEle->LinkEndChild(elmProfile);
//   MAP_CYCLEARTS::iterator shapeList_Iter = shapelist.begin();
//   for (;shapeList_Iter != shapelist.end(); ++shapeList_Iter)
//   {
//      TiXmlElement *elmlist=new TiXmlElement("cycle");
//      elmlist->SetAttribute("iBegin", shapeList_Iter->first.iIndexBegin);
//      elmlist->SetAttribute("iEnd",shapeList_Iter->first.iIndexEnd);
//      elmlist->SetAttribute("iTimes",shapeList_Iter->second);
//      elmProfile->LinkEndChild(elmlist);
//   }
//   return TRUE;
//}
//
//BOOL CFileShapeGye::ReadCycleData( CString &strNodeName, MAP_CYCLEARTS &shapelist )
//{
//   //获取根节点
//   TiXmlElement * pXMLSelectedEle = NULL;
//   GetShapeSubNode(strNodeName,&pXMLSelectedEle);
//   if (NULL == pXMLSelectedEle)
//   {
//      return FALSE;
//   }
//   int iNoteValue = 0;
//   CString strValue;
//   shapelist.clear();
//   TiXmlElement * pXMLValueEle = pXMLSelectedEle->FirstChildElement();
//   for ( ;NULL != pXMLValueEle;pXMLValueEle = pXMLValueEle->NextSiblingElement())
//   {
//      int iBegin = 1, iEnd = 1, iTimes = 1;
//      if (TIXML_SUCCESS == pXMLValueEle->QueryIntAttribute("iBegin",&iNoteValue))
//      {
//         iBegin = iNoteValue;
//      }
//      if (TIXML_SUCCESS == pXMLValueEle->QueryIntAttribute("iEnd",&iNoteValue))
//      {
//         iEnd = iNoteValue;
//      }
//      if (TIXML_SUCCESS == pXMLValueEle->QueryIntAttribute("iTimes",&iNoteValue))
//      {
//         iTimes = iNoteValue;
//      }
//      tagCycleArts cycle(iBegin, iEnd);
//      shapelist[cycle] = iTimes;
//   }
//   return TRUE;
//}

//BOOL CFileShapeGye::WriteModuleInfo( CString &strNodeName,  CShapeProfileData *pShapeData )
//{
//	for (size_t sizeInfo = 0; sizeInfo != pShapeData->m_vectModuleInfo.size(); ++sizeInfo)
//	{
//		const tagKeepInfo &info = pShapeData->m_vectModuleInfo[sizeInfo];
//		CString str;
//		CString strTemp;
//		for (size_t size=0;size!=info.vectModuleData.size();++size)
//		{
//			strTemp.Format(L"%d,", info.vectModuleData[size]);
//			str += strTemp;
//		}
//		strTemp.Format(L":%d, %d,|", info.sizeModule.cx, info.sizeModule.cy);
//		str += strTemp;
//		strNodeName += str;
//	}
//	return TRUE;
//}

//BOOL CFileShapeGye::ReadModuleInfo( CString &strNodeName, CShapeProfileData *pShapeData )
//{
//	while(strNodeName.Find(L"|", 0) !=-1)
//	{
//		tagKeepInfo info;
//		int size = strNodeName.GetLength();
//		int  posRow = strNodeName.Find(_T("|"),0);
//		CString temp = strNodeName.Left(posRow);
//		strNodeName = strNodeName.Right(size-posRow-1);
//
//		int posVect = temp.Find(_T(":"), 0);
//		CString strVect = temp.Left(posVect);
//		temp = temp.Right(temp.GetLength() - posVect - 1);
//		while(strVect.Find(L",", 0) !=-1)
//		{
//			int sizeTemp = strVect.GetLength();
//			int  pos = strVect.Find(_T(","),0);
//			CString strInt = strVect.Left(pos);
//			BYTE byte  =  _ttoi(strInt);
//			info.vectModuleData.push_back(byte);
//			strVect = strVect.Right(sizeTemp-pos-1);
//		}
//
//		if (temp.Find(L",", 0) !=-1)
//		{
//			int sizeTemp = temp.GetLength();
//			int  pos = temp.Find(_T(","),0);
//			CString strInt = temp.Left(pos);
//			info.sizeModule.cx  =  _ttoi(strInt);
//			temp = temp.Right(sizeTemp-pos-1);
//		}
//		if (temp.Find(L",", 0) !=-1)
//		{
//			int sizeTemp = temp.GetLength();
//			int  pos = temp.Find(_T(","),0);
//			CString strInt = temp.Left(pos);
//			info.sizeModule.cy  =  _ttoi(strInt);
//			temp = temp.Right(sizeTemp-pos-1);
//		}
//		pShapeData->m_vectModuleInfo.push_back(info);
//	}
//	return TRUE;
//}

//bool CFileShapeGye::GetObjectData( IKnitFile* pKnitFile, LP_SUBFILEPARAM pSubFileParam )
//{
//   ASSERT(pSubFileParam);
//   ASSERT(pKnitFile);
//   if(NULL == m_pShapeData)
//   {
//      FileNew();
//   }
//   InitXmlDoc();
//   //获取存储xml流 
//   std::string xmlStr;
//   if(false == WriteShapeData())
//      return true;
//
//   GetStream(xmlStr);
//   //请求内存
//   unsigned long lBufferSize = xmlStr.length();
//   if (false == (*pKnitFile)->AskBuffer(lBufferSize + 1, &(pSubFileParam->pBuffer)))
//      return false;
//
//   // 数据不为0时拷贝内存
//   if (0 < lBufferSize)
//   {
//      memcpy(pSubFileParam->pBuffer, xmlStr.data(), lBufferSize);
//   }
//   strcpy_s(pSubFileParam->szSuffixName, 8, RnString::WCStr2StrACP(m_exName).c_str());
//   pSubFileParam->iTypeCompress = 0;
//   pSubFileParam->iTypeCrypt    = 0;
//   pSubFileParam->ulFileSize    = lBufferSize;
//
//   return true;
//}


//bool CFileShapeGye::SetObjectData( const char* pData, DWORD dwSize )
//{
//   // 文件不存在，创建
//   if (0 == dwSize)
//   {
//      FileNew();
//      return true;
//   }
//   // 生成文件对象数据
//   else
//   {
//      std::string inStream;
//      inStream.insert(inStream.begin(),pData,pData + dwSize);
//      if(inStream.empty()||NULL == m_pDoc)
//         return false;
//      InitXmlDoc();
//      m_pDoc->Clear();
//      m_pDoc->Parse(inStream.c_str());
//      if (false == ReadShapeData())
//      {
//         FileNew();
//         return false;
//      }
//   }
//   return true;
//}



/*工艺转制版
1、读取qldata指定路径的gye配置
2、读取qldata工艺数据与gye配置融合
3、成型并将当前工艺gye存入kni工作区
4、再次进成型读取当前kni工作去gye

新建Kxx
1、FileNew读取系统或用户配置gye
2、进入成型读取kni工作区gye
3，4同上

打开
1、如果kni工作区中有gye直接读取
2、否则FileNew
3,4同上*/

bool CFileShapeGye::StreamParseSub( const string& inStream, CShapeProfileData *pShapeData)
{
   if(inStream.empty()||NULL == m_pDoc)
      return false;


   //解析流
   m_pDoc->Clear();
   m_pDoc->Parse(inStream.c_str());
   
   ReadShapeData(pShapeData);

   return true;
}

bool CFileShapeGye::StreamParse( const string& inStream, CShapeProfileData *pShapeData)
{
   CFileShapeGye GyeTemp;
   return GyeTemp.StreamParseSub(inStream, pShapeData);
}

//获取流
void CFileShapeGye::GetStreamSub(string& strStream, CShapeProfileData *pShapeData)
{
   WriteShapeData(pShapeData);
   TiXmlPrinter printer;
   m_pDoc->Accept(&printer);

   strStream = printer.CStr();
}

void CFileShapeGye::GetStream(string& strStream, CShapeProfileData *pShapeData)
{
   CFileShapeGye GyeTemp;
   GyeTemp.GetStreamSub(strStream, pShapeData);
}

//
//bool CFileShapeGye::StreamCreate( string& outStream )
//{
//   return true;
//}

