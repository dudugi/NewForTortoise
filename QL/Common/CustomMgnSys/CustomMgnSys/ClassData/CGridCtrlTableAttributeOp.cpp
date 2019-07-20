#include "StdAfx.h"
#include "../CustomMgnSys.h"
#include "rnstring.h"
#include "rnfile.h"
#include "CGridCtrlTableAttributeOp.h"
#include "CDBFieldDefine.h"

#include <algorithm>
#include "tinyxml\tinyxml.h"
#include "CDataTableAttrFileAndFieldDefine.h"


std::shared_ptr<CGridCtrlTableAttributeOp> CGridCtrlTableAttributeOp::sm_inst;

CGridCtrlTableAttributeOp::CGridCtrlTableAttributeOp(void)
{
   m_mapFunc[TABLE_TABLESTYLE] = &CGridCtrlTableAttributeOp::CreateTABLESTYLE;
   m_mapFunc[TABLE_STAFFMGN] = &CGridCtrlTableAttributeOp::Create_StaffMgn;
   m_mapFunc[TABLE_CUSMGN] = &CGridCtrlTableAttributeOp::Create_CusMgn;
   m_mapFunc[TABLE_ORDER_LOG] = &CGridCtrlTableAttributeOp::Create_LogInfo;
   m_mapFunc[TABLE_CUSMGN_OPRECORDS] = &CGridCtrlTableAttributeOp::Create_CusMgnOpRecords;
}


CGridCtrlTableAttributeOp::~CGridCtrlTableAttributeOp(void)
{
   m_mapFunc.swap(map<CString, funcCreateAttri>() );
   m_mapFunc2Param.swap( map<CString, funcCreateAttri2Param>() );
}

CString CGridCtrlTableAttributeOp::GetUserTableConfigXmlPath()//�û�·��
{
//	CString pathName = theApp.m_strKdsWorkPath + "\\�û��ļ�\\����\\TableConfigXml\\";
//	return pathName;
   CString pathName = RnFile::GetModulePathFile(_T("")) + "TableConfigXml\\";
   return pathName;
}
CString CGridCtrlTableAttributeOp::GetSysTableConfigXmlPath()//ϵͳ·��
{
	CString pathName = RnFile::GetModulePathFile(_T("")) + "TableConfigXml\\";
	return pathName;
}

void CGridCtrlTableAttributeOp::SortFieldToMap(MAP_GridCtrl_FieldAtrri & tableFieldAtrri,S_GridCtrl_TableAttri & tableAttri,int & nBeginIndex)
{
	vector<S_GridCtrl_FieldAtrri> vec_Atrri ;

	//��map���뵽�����б���
	for (auto it = tableFieldAtrri.begin();it != tableFieldAtrri.end();++it)
	{
		vec_Atrri.push_back(it->second);
	}

	//����
	std::sort(vec_Atrri.begin(),vec_Atrri.end(),[](const S_GridCtrl_FieldAtrri & field1,const S_GridCtrl_FieldAtrri & field2){return field1.iColIndex < field2.iColIndex;});
	//���²���
	tableFieldAtrri.clear();
	for (auto vec_it = vec_Atrri.begin();vec_it != vec_Atrri.end();++vec_it)
	{
		tableAttri.mapTableFeildPos.insert(make_pair(nBeginIndex,vec_it->strColID));
		vec_it->iColIndex = nBeginIndex;
		tableAttri.mapFeildAtrri.insert(make_pair(vec_it->strColID,*vec_it));
		++nBeginIndex;
	}
}

BOOL CGridCtrlTableAttributeOp::ReadTableAttri(CString fileName,S_GridCtrl_TableAttri &tableAttri,BOOL bNoXml/*=FALSE*/)
{	
	if(bNoXml)
	{
		return ReadDefaultTableAttri(fileName,tableAttri);
	}

   return UpdateGridStyleAttriInfo(fileName , tableAttri);
}


BOOL CGridCtrlTableAttributeOp::CombineDefaultTableAttri(CString DefaultFilelName,S_GridCtrl_TableAttri &tableAttri)
{
	BOOL bRet = TRUE;

	S_GridCtrl_TableAttri defaulttableAttri;
	if(ReadDefaultTableAttri(DefaultFilelName,defaulttableAttri))//��ȡ�����е�����
	{
		S_GridCtrl_TableAttri tmptableAttri = tableAttri;
		//int nCount = tmptableAttri.mapTableFeildPos.size();
		for (MAP_GridCtrl_FieldPos::iterator iterDefaultPos=defaulttableAttri.mapTableFeildPos.begin();
			iterDefaultPos!=defaulttableAttri.mapTableFeildPos.end();++iterDefaultPos)
		{
			MAP_GridCtrl_FieldAtrri::iterator iterDefaultFieldAtrri =  defaulttableAttri.mapFeildAtrri.find(iterDefaultPos->second);
			ASSERT(iterDefaultFieldAtrri!=defaulttableAttri.mapFeildAtrri.end());

			BOOL bExist = FALSE;

			CString strDefaultFieldName = iterDefaultFieldAtrri->second.strColID;
			for (MAP_GridCtrl_FieldPos::iterator iterPos=tmptableAttri.mapTableFeildPos.begin();
				iterPos!=tmptableAttri.mapTableFeildPos.end();++iterPos)
			{
				MAP_GridCtrl_FieldAtrri::iterator iterFieldAtrri =  tmptableAttri.mapFeildAtrri.find(iterPos->second);
				ASSERT(iterFieldAtrri!=tmptableAttri.mapFeildAtrri.end());

				if (strDefaultFieldName == iterFieldAtrri->second.strColID)
				{
					bExist = TRUE;

					// �����������뵽����ı�������� 2017-1-3 wangzl ��������ʵ�� ���Ż�����
					auto itFindField = tableAttri.mapFeildAtrri.find(iterPos->second);
					ASSERT(itFindField != tableAttri.mapFeildAtrri.end());
					if (itFindField != tableAttri.mapFeildAtrri.end())
					{
						itFindField->second.strColDestribution = iterDefaultFieldAtrri->second.strColDestribution;
						itFindField->second.strTableID = iterDefaultFieldAtrri->second.strTableID;
					}
					//����ʵ��end
					break;
				}
			}

			if (bExist)
			{
				//TRACE(_T("%s Exist\n"),iterDefaultFieldAtrri->second.strColID);
			}
			else
			{
				//�����ھ����
				int nSel = tableAttri.mapTableFeildPos.size()+1;
				tableAttri.mapTableFeildPos.insert(make_pair(nSel,strDefaultFieldName));
				S_GridCtrl_FieldAtrri FeildAtrri(strDefaultFieldName,nSel,strDefaultFieldName,false,false); 
				FeildAtrri.strColDestribution = iterDefaultFieldAtrri->second.strColDestribution;
				FeildAtrri.strTableID = iterDefaultFieldAtrri->second.strTableID;
            FeildAtrri.strColShowName = iterDefaultFieldAtrri->second.strColShowName;
				tableAttri.mapFeildAtrri.insert(make_pair(strDefaultFieldName,FeildAtrri));
			}
		}
	}
	else
	{
		bRet = FALSE;
	}

	return bRet;
}

BOOL CGridCtrlTableAttributeOp::ReadTableAttriFromXml(CString fullName,S_GridCtrl_TableAttri &tableAttri)
{
	try
	{	
		//�޸����ֽ�������ʽ��ȡ�ļ����ɹ�������		by WangZY 2017/12/15
		tableAttri.mapFeildAtrri.clear();
		tableAttri.mapTableFeildPos.clear();
		//����һ��XML���ĵ�����
		string strFileName;
		RnString::UNICODE_TO_ACP(fullName.GetBuffer(),strFileName);
		fullName.ReleaseBuffer();
		TiXmlDocument *pMyDocument = new TiXmlDocument(strFileName.c_str());
		if (pMyDocument == NULL)
		{
			return FALSE;
		}
		pMyDocument->LoadFile();

		TiXmlElement *pRootElement = pMyDocument->RootElement();
		if (pRootElement == NULL)
		{
			delete pMyDocument;//2017/06/06 zhangt �ͷ��ڴ�
			return FALSE;
		}

		TiXmlElement *FirstVersion = pRootElement->FirstChildElement();
		while (FirstVersion != NULL)
		{
			const char* cvalue;
			cvalue = FirstVersion->Value();   

			if (0 == strcmp(cvalue, "isShowTitleFilter"))
			{	//��ʾ�б���ɸѡ��		by WangZY 2017/06/07
				cvalue = FirstVersion->GetText();
				tableAttri.isShowTitleFilter = atoi(cvalue)?true:false;   
			}
			else if (0 == strcmp(cvalue,"isAllowSort"))
			{            
				cvalue = FirstVersion->GetText();
				tableAttri.isAllowSort = atoi(cvalue)?true:false;           
			}
			else if (0 == strcmp(cvalue,"isMultiRowSelect"))
			{
				cvalue = FirstVersion->GetText();
				tableAttri.isMultiRowSelect = (BOOL)atoi(cvalue)?true:false;  
			}
			else if (0 == strcmp(cvalue,"IsMultiRowSelectNoLoseFocus"))
			{
				cvalue = FirstVersion->GetText();
				tableAttri.IsMultiRowSelectNoLoseFocus = (BOOL)atoi(cvalue)?true:false; 
			}
			else if (0 == strcmp(cvalue,"isShowSortBar"))
			{
				cvalue = FirstVersion->GetText();
				tableAttri.isShowSortBar = (BOOL)atoi(cvalue)?true:false; 
			}
			else if (0 == strcmp(cvalue,"DataRowHeight"))
			{
				cvalue = FirstVersion->GetText();
				tableAttri.nDataRowHeight = atoi(cvalue);
			}
			else if (0 == strcmp(cvalue,"isShowSumBar"))
			{
				cvalue = FirstVersion->GetText();
				tableAttri.isShowSumBar = atoi(cvalue)?true:false; 
			}
			else if (0 == strcmp(cvalue,"isWholeRowSelect"))
			{
				cvalue = FirstVersion->GetText();
				tableAttri.isWholeRowSelect = atoi(cvalue)?true:false; 
			}
			else if (0 == strcmp(cvalue,"iDataRowFont"))
			{
				cvalue = FirstVersion->GetText();
				tableAttri.iDataRowFont = atoi(cvalue); 
			}else if (0 == strcmp(cvalue,"isEnableDragCol"))
			{
				cvalue = FirstVersion->GetText();
				tableAttri.isEnableDragCol = atoi(cvalue)?true:false; //��λ���ܷ��϶� yangjr 2017-6-13
			}   
			else if (0 == strcmp(cvalue,"isEnableEdit"))
			{
				cvalue = FirstVersion->GetText();
				tableAttri.isEnableEdit = atoi(cvalue)?true:false;	//���Ƿ�ɱ༭	by WangZY 2017/06/15
         }else if (0 == strcmp(cvalue,"iPageRows"))
         {
            cvalue = FirstVersion->GetText();
            tableAttri.iPageRows = atoi(cvalue);
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
						delete pMyDocument;//2017/06/06 zhangt �ͷ��ڴ�
						return FALSE;
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
							delete pMyDocument;//2017/06/06 zhangt �ͷ��ڴ�
							return FALSE;
						}
					}else
					{
						delete pMyDocument;//2017/06/06 zhangt �ͷ��ڴ�
						return FALSE;
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
							delete pMyDocument;//2017/06/06 zhangt �ͷ��ڴ�
							return FALSE;
						}
					}else
					{
						delete pMyDocument;//2017/06/06 zhangt �ͷ��ڴ�
						return FALSE;
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
					pElement2 = pElement->FirstChildElement("isEnableFilter");//���ܷ����� yangjr 2017-6-9
					if (pElement2 != NULL)
					{                  
						cvalue = pElement2->GetText();  
						if (cvalue!=NULL)
						{
							oneFieldAtrri.isEnableFilter = atoi(cvalue)?true:false;
						}
					}               
					tableAttri.mapFeildAtrri.insert(make_pair(oneFieldAtrri.strColID,oneFieldAtrri));
					tableAttri.mapTableFeildPos.insert(make_pair(i,oneFieldAtrri.strColID));
				}
			}
         else if(0 == strcmp(cvalue,"UpdateDateTime"))
         {
            cvalue = FirstVersion->GetText();
            tableAttri.strUpdateTime = cvalue;
         }
         else if(0 == strcmp(cvalue,"isNoUpdateServerStyle"))
         {
            cvalue = FirstVersion->GetText();
            tableAttri.isNoUpdateServerStyle = atoi(cvalue)?true:false;
         }

			FirstVersion = FirstVersion->NextSiblingElement();
		}
		delete pMyDocument;//2017/06/06 zhangt �ͷ��ڴ�
	}
	catch (string& e)
	{
      CString s(e.c_str());
		return FALSE;
	}
	catch (...)
	{

	}
	return TRUE;
}

CGridCtrlTableAttributeOp * CGridCtrlTableAttributeOp::Instance()
{
   if(sm_inst.get() == 0)
      sm_inst = shared_ptr<CGridCtrlTableAttributeOp>(new CGridCtrlTableAttributeOp);

   return sm_inst.get();
}


//************************************
// Method:    ���±����ʽ
// Author:    wuZhiHua
// Date : 	  2018/04/02
// Access:    private 
// Returns:   BOOL
// Parameter: TiXmlElement * pElement
//************************************
BOOL CGridCtrlTableAttributeOp::UpdateGridStyleAttriInfo(CString fileName , S_GridCtrl_TableAttri &tableAttri)
{
   //��ȡ���ݿ�����  
   //DBTableStyleGlobalSetInfoList dataLst;   
   CString updateTime , serverStyleXml;

   CString pathNameUser = GetUserTableConfigXmlPath() + fileName + _T(".XML");//�û�·��   
   if (RnFile::IsFileExist(pathNameUser))//�û��ļ����� ����ȡ�û��ļ��ı����ʽ
   {
      //��ȡ�û�Ŀ¼
      if( !ReadTableAttriFromXml(pathNameUser ,tableAttri) )
      {
         return FALSE;
      }
      CombineDefaultTableAttri(fileName,tableAttri);//�ϲ�ϵͳĿ¼�ı����ʽ
          
      return WriteTableAttri(fileName , tableAttri);
   }
   else  //�û��ļ������ڣ���ȡϵͳ�ļ�
   {
      CString pathNameDefault = GetSysTableConfigXmlPath() + fileName + _T(".XML");//ϵͳ·�����ļ�
      if (RnFile::IsFileExist(pathNameDefault))//ϵͳ·�������ļ�
      {
         if(ReadTableAttriFromXml(pathNameDefault,tableAttri))//��ȡϵͳĿ¼�ļ�
         {
                              
            return WriteTableAttri(fileName , tableAttri);//д�û�·��
         }else
         {
            return FALSE;
         }
      }
      else //ϵͳ·���������ļ�
      {
         if(ReadDefaultTableAttri(fileName,tableAttri))//��ȡ�����е�����
         {
            
            WriteTableAttriAsDefault(fileName,tableAttri);//дϵͳ·��
            return WriteTableAttri(fileName , tableAttri);//д�û�·��
         }
         else
         {
            return FALSE;
         }         
      }
   }
}



void CGridCtrlTableAttributeOp::LinkIntValueToElement(int iValue,TiXmlElement *pElement)
{
	CString strValue;
	strValue.Format(_T("%d"),iValue);
	TiXmlText *NameContent =new TiXmlText(RnString::UNICODE_TO_UTF8(strValue).c_str());
	pElement->LinkEndChild(NameContent);
}

void CGridCtrlTableAttributeOp::LinkCStringValueToElement(CString strValue,TiXmlElement *pElement)
{
	TiXmlText *NameContent =new TiXmlText(RnString::UNICODE_TO_UTF8(strValue).c_str());
	pElement->LinkEndChild(NameContent);
}

BOOL CGridCtrlTableAttributeOp::WriteTableAttri(CString fileName,const S_GridCtrl_TableAttri &tableAttri)
{
	CString pathName = GetUserTableConfigXmlPath() ;
	RnFile::MakeSureDirectoryPathExists(pathName);
	CString fullName = pathName + fileName +  _T(".XML");
	return WriteTableAttriToXml(fullName,tableAttri);   
}
//��ʼ��ϵͳĿ¼�µı����ʽ yangjr 2018-1-15
BOOL CGridCtrlTableAttributeOp::InitDefaultTableAttri(CString fileName)
{
	CString pathName = GetSysTableConfigXmlPath() ;
	RnFile::MakeSureDirectoryPathExists(pathName);
	S_GridCtrl_TableAttri tableAttri;
	if(ReadDefaultTableAttri(fileName,tableAttri))//��ȡ�����е�����
	{
		CString fullName = pathName + fileName +  _T(".XML");
		return WriteTableAttriToXml(fullName,tableAttri);   
	}
	else
	{      
		return FALSE;
	}
}

//��ʼ���û�Ŀ¼�µı����ʽ yangjr 2018-1-15
BOOL CGridCtrlTableAttributeOp::InitUserTableAttri(CString fileName,S_GridCtrl_TableAttri &tableAttri)
{
	CString pathNameUser =GetUserTableConfigXmlPath() + fileName + _T(".XML");
	RnFile::MakeSureDirectoryPathExists(GetUserTableConfigXmlPath());

	InitDefaultTableAttri(fileName); //���ô����ʼ��ϵͳĿ¼�����û�д��봴���ľͲ���ʼ��  

	CString pathNameDefault = GetSysTableConfigXmlPath() + fileName + _T(".XML");//ϵͳ·�����ļ�
	if (!RnFile::IsFileExist(pathNameDefault))//ϵͳ·���������ļ�
	{
		return FALSE;
	}
	else //ϵͳ·�������ļ�,
	{
		ReadTableAttriFromXml(pathNameDefault,tableAttri);//��ȡϵͳĿ¼�ļ�
		CombineDefaultTableAttri(fileName,tableAttri);
		return  WriteTableAttriToXml(pathNameUser,tableAttri); 
	}
}

BOOL CGridCtrlTableAttributeOp::WriteTableAttriAsDefault(CString fileName,const S_GridCtrl_TableAttri &tableAttri)
{
	CString pathName = GetSysTableConfigXmlPath();
	RnFile::MakeSureDirectoryPathExists(pathName);
	CString fullName = pathName + fileName +  _T(".XML");
	return WriteTableAttriToXml(fullName,tableAttri);
}
BOOL CGridCtrlTableAttributeOp::WriteTableAttriToXml(CString fullName,const S_GridCtrl_TableAttri &tableAttri)
{
	try
	{
		//����һ��XML���ĵ�����
		string strFileName;
		RnString::UNICODE_TO_ACP(fullName.GetBuffer(),strFileName);
		fullName.ReleaseBuffer();

      // �����µ�xml
		TiXmlDocument *myDocument =new TiXmlDocument(strFileName.c_str());

		//����һ����Ԫ�ز����ӡ�
		TiXmlElement *RootElement =new TiXmlElement("tableAttri");
		myDocument->LinkEndChild(RootElement);

		TiXmlElement *pPersonElement =new TiXmlElement("isAllowSort");
		RootElement->LinkEndChild(pPersonElement);
		LinkIntValueToElement(tableAttri.isAllowSort,pPersonElement);

		//��ʾ�б���ɸѡ��		by WangZY 2017/06/07
		pPersonElement =new TiXmlElement("isShowTitleFilter");
		RootElement->LinkEndChild(pPersonElement);
		LinkIntValueToElement(tableAttri.isShowTitleFilter,pPersonElement);

		pPersonElement =new TiXmlElement("isMultiRowSelect");
		RootElement->LinkEndChild(pPersonElement);
		LinkIntValueToElement(tableAttri.isMultiRowSelect,pPersonElement);

		pPersonElement =new TiXmlElement("IsMultiRowSelectNoLoseFocus");
		RootElement->LinkEndChild(pPersonElement);
		LinkIntValueToElement(tableAttri.IsMultiRowSelectNoLoseFocus,pPersonElement);

		pPersonElement =new TiXmlElement("isShowSortBar");
		RootElement->LinkEndChild(pPersonElement);
		LinkIntValueToElement(tableAttri.isShowSortBar,pPersonElement);

		pPersonElement =new TiXmlElement("isShowSumBar");
		RootElement->LinkEndChild(pPersonElement);
		LinkIntValueToElement(tableAttri.isShowSumBar,pPersonElement);

		pPersonElement =new TiXmlElement("isWholeRowSelect");
		RootElement->LinkEndChild(pPersonElement);
		LinkIntValueToElement(tableAttri.isWholeRowSelect,pPersonElement);

		pPersonElement =new TiXmlElement("DataRowHeight");
		RootElement->LinkEndChild(pPersonElement);
		LinkIntValueToElement(tableAttri.nDataRowHeight,pPersonElement);

		pPersonElement =new TiXmlElement("iDataRowFont");
		RootElement->LinkEndChild(pPersonElement);
		LinkIntValueToElement(tableAttri.iDataRowFont,pPersonElement);

		pPersonElement =new TiXmlElement("isEnableDragCol");
		RootElement->LinkEndChild(pPersonElement);
		LinkIntValueToElement(tableAttri.isEnableDragCol,pPersonElement);//��λ���ܷ��϶� yangjr 2017-6-13

		//���Ƿ�ɱ༭	by WangZY 2017/06/15
		pPersonElement =new TiXmlElement("isEnableEdit");
		RootElement->LinkEndChild(pPersonElement);
		LinkIntValueToElement(tableAttri.isEnableEdit,pPersonElement);

      pPersonElement =new TiXmlElement("iPageRows");
      RootElement->LinkEndChild(pPersonElement);
      LinkIntValueToElement(tableAttri.iPageRows,pPersonElement);

		pPersonElement =new TiXmlElement("ItemCount");
		RootElement->LinkEndChild(pPersonElement);
		LinkIntValueToElement(tableAttri.mapFeildAtrri.size(),pPersonElement);
		CString strItem;
		for (MAP_GridCtrl_FieldPos::const_iterator iterIndex= tableAttri.mapTableFeildPos.begin();
			iterIndex!=tableAttri.mapTableFeildPos.end();++iterIndex)
		{         
			strItem.Format(_T("Item%d"),iterIndex->first);
			TiXmlElement *pPersonElement2 =new TiXmlElement(RnString::UNICODE_TO_UTF8(strItem).c_str());
			pPersonElement->LinkEndChild(pPersonElement2);

			MAP_GridCtrl_FieldAtrri::const_iterator iterFind = tableAttri.mapFeildAtrri.find(iterIndex->second);
			ASSERT(iterFind!=tableAttri.mapFeildAtrri.end());
			TiXmlElement *pPersonElement3 =new TiXmlElement("enColSumType");
			pPersonElement2->LinkEndChild(pPersonElement3);
			LinkIntValueToElement((int)iterFind->second.enColSumType,pPersonElement3);

			pPersonElement3 =new TiXmlElement("enSerchType");
			pPersonElement2->LinkEndChild(pPersonElement3);
			LinkIntValueToElement((int)iterFind->second.enSerchType,pPersonElement3);

			pPersonElement3 =new TiXmlElement("iColFont");
			pPersonElement2->LinkEndChild(pPersonElement3);
			LinkIntValueToElement(iterFind->second.iColFont,pPersonElement3);

			pPersonElement3 =new TiXmlElement("iColIndex");
			pPersonElement2->LinkEndChild(pPersonElement3);
			LinkIntValueToElement(iterFind->second.iColIndex,pPersonElement3);

			pPersonElement3 =new TiXmlElement("iColWidth");
			pPersonElement2->LinkEndChild(pPersonElement3);
			LinkIntValueToElement(iterFind->second.iColWidth,pPersonElement3);

			pPersonElement3 =new TiXmlElement("iLock");
			pPersonElement2->LinkEndChild(pPersonElement3);
			LinkIntValueToElement(iterFind->second.iLock,pPersonElement3);

			pPersonElement3 =new TiXmlElement("isEdit");
			pPersonElement2->LinkEndChild(pPersonElement3);
			LinkIntValueToElement(iterFind->second.isEdit,pPersonElement3);

			pPersonElement3 =new TiXmlElement("IsFontWeight");
			pPersonElement2->LinkEndChild(pPersonElement3);
			LinkIntValueToElement(iterFind->second.IsFontWeight,pPersonElement3);

			pPersonElement3 =new TiXmlElement("isShow");
			pPersonElement2->LinkEndChild(pPersonElement3);
			LinkIntValueToElement(iterFind->second.isShow,pPersonElement3);

			pPersonElement3 =new TiXmlElement("strColFormat");
			pPersonElement2->LinkEndChild(pPersonElement3);
			LinkCStringValueToElement(iterFind->second.strColFormat,pPersonElement3);

			pPersonElement3 =new TiXmlElement("strColID");
			pPersonElement2->LinkEndChild(pPersonElement3);
			LinkCStringValueToElement(iterFind->second.strColID,pPersonElement3);

			pPersonElement3 =new TiXmlElement("strColShowName");
			pPersonElement2->LinkEndChild(pPersonElement3);
			LinkCStringValueToElement(iterFind->second.strColShowName,pPersonElement3);

			pPersonElement3 =new TiXmlElement("isEnableFilter");
			pPersonElement2->LinkEndChild(pPersonElement3);
			LinkIntValueToElement(iterFind->second.isEnableFilter,pPersonElement3);
		}

      //�����������
      TiXmlElement* pUpdateDateTime =new TiXmlElement("UpdateDateTime");
      RootElement->LinkEndChild(pUpdateDateTime);
      LinkCStringValueToElement(tableAttri.strUpdateTime, pUpdateDateTime);

      TiXmlElement* pNoUpdateServerStyle =new TiXmlElement("isNoUpdateServerStyle"); //�Ƿ���±����ʽ yangjr 2018/5/29
      RootElement->LinkEndChild(pNoUpdateServerStyle);
      LinkIntValueToElement(tableAttri.isNoUpdateServerStyle, pNoUpdateServerStyle);

		if (!myDocument->SaveFile())//���浽�ļ�
		{
			delete myDocument;//2017/06/06 zhangt �ͷ��ڴ�
			return FALSE;
		}

		delete myDocument;//2017/06/06 zhangt �ͷ��ڴ�
	}
	catch(string& e)
	{
      CString s(e.c_str());
		return FALSE;
	}
	return TRUE;
}

BOOL CGridCtrlTableAttributeOp::ReadDefaultTableAttri(CString fileName,S_GridCtrl_TableAttri &tableAttri)
{
    BOOL bCreate = TRUE;    //�Ƿ��Ѿ������˱����ʽ

    if (m_mapFunc.find(fileName) != m_mapFunc.end())
    {
       bCreate = TRUE;
       (this->*m_mapFunc[fileName])(tableAttri);
    }
    else
    {
       if (m_mapFunc2Param.find(fileName) != m_mapFunc2Param.end())
       {
          bCreate = TRUE;
          (this->*m_mapFunc2Param[fileName])(tableAttri,fileName);
       }
    }
    return bCreate;
}

void CGridCtrlTableAttributeOp::CreateTABLESTYLE(S_GridCtrl_TableAttri &tableAttri)
{ 
	int colIndex = 1;
	//��ʾ�ڼ���  //������                      //��ʾ����         //�Ƿ���ʾ //�Ƿ�༭
	InsertFeildID(tableAttri,  colIndex ,  TABLESTYLE_strColID              , _T("������")     ,_T(""),_T(""), TRUE   ,FALSE,127); colIndex++;
	InsertFeildID(tableAttri,  colIndex ,  TABLESTYLE_strColShowName        , _T("��ʾ����")   ,_T(""),_T(""), TRUE   ,TRUE,120 ); colIndex++;
	InsertFeildID(tableAttri,  colIndex ,  TABLESTYLE_iColWidth             , _T("���")       ,_T(""),_T(""), TRUE   ,TRUE,60 ); colIndex++;
	InsertFeildID(tableAttri,  colIndex ,  TABLESTYLE_isShow                , _T("�Ƿ���ʾ")   ,_T(""),_T(""), TRUE   ,TRUE,65); colIndex++;
	InsertFeildID(tableAttri,  colIndex ,  TABLESTYLE_isEdit                , _T("�Ƿ�༭")   ,_T(""),_T(""), TRUE   ,TRUE,65); colIndex++;
	InsertFeildID(tableAttri,  colIndex ,  TABLESTYLE_iLock                 , _T("������")     ,_T(""),_T(""), TRUE   ,TRUE,90); colIndex++;
	// InsertFeildID(tableAttri,  -1       ,  TABLESTYLE_strColFormat          , _T("��ʽ��")     ,_T(""),_T(""), FALSE  );
	InsertFeildID(tableAttri,  colIndex ,  TABLESTYLE_enColSumType          , _T("�ϼƷ�ʽ")   ,_T(""),_T(""), TRUE   ); colIndex++;
	InsertFeildID(tableAttri,  colIndex ,  TABLESTYLE_enSerchType           , _T("������ʽ")   ,_T(""),_T(""), TRUE   ); colIndex++;
	InsertFeildID(tableAttri,  colIndex ,  TABLESTYLE_iColFont              , _T("�����С")   ,_T(""),_T(""), TRUE    ,TRUE,65); colIndex++;
	InsertFeildID(tableAttri,  colIndex ,  TABLESTYLE_IsFontWeight          , _T("����Ӵ�")   ,_T(""),_T(""), TRUE    ,TRUE,65); colIndex++;
	InsertFeildID(tableAttri,  colIndex ,  TABLESTYLE_isEnableFilter        , _T("�ܷ�ɸѡ")   ,_T(""),_T(""), TRUE    ,TRUE,65); colIndex++;  
	InsertFeildID(tableAttri,  colIndex ,  TABLESTYLE_strColDestribution    , _T("���ֶ�˵��") ,_T(""),_T(""), TRUE    ,TRUE,300); colIndex++;  
	InsertFeildID(tableAttri,  colIndex ,  TABLESTYLE_strTableID    , _T("���ֶ����ڱ�") ,_T(""),_T(""), FALSE    ,FALSE,80); colIndex++;  
	tableAttri.isEnableDragCol = FALSE; //��λ�ò��ܸı�
	tableAttri.isShowSortBar = TRUE;	//��ʾɸѡ��
}

void CGridCtrlTableAttributeOp::InsertFeildID(S_GridCtrl_TableAttri &tableAttri,
	short iColIndex_In,CString strColID_In,CString strColShowName_In ,CString strColDestribution,
	CString strTableID_In,bool isShow_In ,bool isEdit_In ,short iColWidth_In ,
	bool isEnableFilter_In ,BYTE iLock_In ,ENUM_COLSUMTYPE enColSumType_In ,
	BYTE iColFont_In ,bool IsFontWeight_In,
	ENUM_COLSERCHTYPE enSerchType_In ,CString strColFormat_In)
{
	if (strColDestribution.IsEmpty())
	{
		strColDestribution = strColShowName_In;
	}
	tableAttri.mapTableFeildPos.insert(make_pair(iColIndex_In,strColID_In));
	S_GridCtrl_FieldAtrri FeildAtrri(strColID_In,iColIndex_In,strColShowName_In,isShow_In,isEdit_In,
		iColWidth_In,isEnableFilter_In,iLock_In,enColSumType_In,iColFont_In,IsFontWeight_In,enSerchType_In,strColFormat_In,strColDestribution,strTableID_In);      
	tableAttri.mapFeildAtrri.insert(make_pair(strColID_In,FeildAtrri));
}

void CGridCtrlTableAttributeOp::CreateEmptyFieldAttri( S_GridCtrl_TableAttri &tableAttri,CStringList& strlFieldName )
{
	int nIndex = 0,nCount = strlFieldName.GetCount();
	for (nIndex = 0;nIndex < nCount;nIndex++)
	{
		CString strFileldName = strlFieldName.GetAt(strlFieldName.FindIndex(nIndex));
		InsertFeildID(tableAttri,  nIndex+1,strFileldName,strFileldName,FALSE,FALSE);
	}
}


//void CGridCtrlTableAttributeOp::Create_OperateLog(S_GridCtrl_tableAttri &tableAttri)
//{
//	int colIndex = 1;
//	InsertFeildID(tableAttri,  colIndex ,  DBWorkLog_key_Maker		, _T("�û�")    ,_T("") ,DB_TABLE_LOG,		TRUE ,	FALSE , 150); colIndex++;
//	InsertFeildID(tableAttri,  colIndex ,  DBWorkLog_key_Cate	, _T("�����")  ,_T("") ,DB_TABLE_LOG,	TRUE ,	FALSE , 100); colIndex++;
//	InsertFeildID(tableAttri,  colIndex ,  DBWorkLog_key_InterFace	, _T("����")  ,_T("") ,DB_TABLE_LOG,	TRUE ,	FALSE , 120); colIndex++;
//	InsertFeildID(tableAttri,  colIndex ,  DBWorkLog_key_Code	, _T("��ر��")  ,_T("") ,DB_TABLE_LOG,	TRUE ,	FALSE , 100); colIndex++;
//	InsertFeildID(tableAttri,  colIndex ,  DBWorkLog_key_Type	, _T("����")  ,_T("") ,DB_TABLE_LOG,	TRUE ,	FALSE , 100); colIndex++;
//	InsertFeildID(tableAttri,  colIndex ,  DBWorkLog_key_Detail	, _T("����")  ,_T("") ,DB_TABLE_LOG,	TRUE ,	FALSE , 350); colIndex++;
//	InsertFeildID(tableAttri,  colIndex ,  DBWorkLog_key_Date	, _T("ʱ��")  ,_T("") ,DB_TABLE_LOG,	TRUE ,	FALSE , 170); colIndex++;
//
//	tableAttri.isAllowSort = TRUE;
//	tableAttri.isMultiRowSelect = FALSE;
//	tableAttri.IsMultiRowSelectNoLoseFocus = FALSE;
//	tableAttri.isShowSortBar = FALSE;
//	tableAttri.isShowSumBar = TRUE;
//	tableAttri.isWholeRowSelect = TRUE;
//	tableAttri.nDataRowHeight = CB_GRIDCTRL_DEFAULT_ROWHEIGHT;
//	tableAttri.iDataRowFont = CB_GRIDCTRL_DEFAULT_FONT;
//	tableAttri.isShowSortBar = TRUE;
//}

void CGridCtrlTableAttributeOp::Create_StaffMgn(S_GridCtrl_TableAttri &tableAttri)
{
   int colIndex = 1;
   //�ڼ���		������											����				��ʾ	�༭

   InsertFeildID(tableAttri,  colIndex ,  DBUser_key_ID				, _T("ID")          ,_T("ID")        ); colIndex++;   
   InsertFeildID(tableAttri,  colIndex ,  DBUser_key_cUserID		, _T("�û���")      ,_T("�û���")   ); colIndex++;
   //InsertFeildID(tableAttri,  colIndex ,  DBUser_key_cPassword	, _T("����")        ,_T("����")    ); colIndex++;
   InsertFeildID(tableAttri,  colIndex ,  DBUser_key_cUserName		, _T("����")        ,_T("����")    ); colIndex++;   
   InsertFeildID(tableAttri,  colIndex ,  DBUser_key_cUserDate		, _T("ע��ʱ��")        ,_T("ע��ʱ��")    ); colIndex++;   
   InsertFeildID(tableAttri,  colIndex ,  DBUser_key_dtLastLoadTime	, _T("����¼ʱ��")    ,_T("����¼ʱ��")); colIndex++;
   InsertFeildID(tableAttri,  colIndex ,  DBUser_key_iUserState		, _T("״̬")        ,_T("״̬")    ); colIndex++;

   tableAttri.isAllowSort = TRUE;
   tableAttri.isMultiRowSelect = FALSE;
   tableAttri.IsMultiRowSelectNoLoseFocus = FALSE;
   tableAttri.isShowSortBar = FALSE;
   tableAttri.isShowSumBar = FALSE;
   tableAttri.isWholeRowSelect = TRUE;
   tableAttri.nDataRowHeight = CB_GRIDCTRL_DEFAULT_ROWHEIGHT;
   tableAttri.iDataRowFont = CB_GRIDCTRL_DEFAULT_FONT;
}

void CGridCtrlTableAttributeOp::Create_CusMgn(S_GridCtrl_TableAttri &tableAttri)
{
   int colIndex = 1;
   //�ڼ���		������											����				��ʾ	�༭
   InsertFeildID(tableAttri,  colIndex ,  DBCusBase_key_ID				   , _T("ID")           ,_T("ID")        ); colIndex++;   
   InsertFeildID(tableAttri,  colIndex ,  DBCusBase_key_cCusCode			, _T("�ͻ����")      ,_T("�ͻ����")        ); colIndex++;   
   InsertFeildID(tableAttri,  colIndex ,  DBCusBase_key_cCusName			, _T("�ͻ�����")      ,_T("�ͻ�����")        ); colIndex++;   
   InsertFeildID(tableAttri,  colIndex ,  DBCusBase_key_cCusAddress		, _T("��ַ")          ,_T("��ַ")        ); colIndex++;   
   InsertFeildID(tableAttri,  colIndex ,  DBCusBase_key_cCusPhone			, _T("��ϵ�绰")      ,_T("��ϵ�绰")        ); colIndex++; 
   InsertFeildID(tableAttri,  colIndex ,  DBCusBase_key_cCusContacts		, _T("��ϵ��")        ,_T("��ϵ��")        ); colIndex++;   
   InsertFeildID(tableAttri,  colIndex ,  DBCusBase_key_cPDMVersion		, _T("�汾��")        ,_T("�汾��")              ); colIndex++;   
   InsertFeildID(tableAttri,  colIndex ,  DBCusBase_key_cProvince			, _T("ʡ��")          ,_T("ʡ��")                ); colIndex++;   
   InsertFeildID(tableAttri,  colIndex ,  DBCusBase_key_isLocalDB			, _T("�Ƿ񱾵ز���")   ,_T("�Ƿ񱾵ز���")         ); colIndex++;
   InsertFeildID(tableAttri,  colIndex ,  DBCusBase_key_cServerPerson			, _T("������Ա")      ,_T("")        ); colIndex++;   
   InsertFeildID(tableAttri,  colIndex ,  DBCusBase_key_iClientNum			, _T("�ͻ�������")      ,_T("")        ); colIndex++;   
   InsertFeildID(tableAttri,  colIndex ,  DBCusBase_key_cMemo			, _T("��ע")      ,_T("")        ); colIndex++; 

   InsertFeildID(tableAttri,  colIndex ,  DBCusDb_key_cDbServerName		, _T("���ݿ�����")     ,_T("���ݿ�����")           ); colIndex++; 
   InsertFeildID(tableAttri,  colIndex ,  DBCusDb_key_iDbServerPort		, _T("���ݿ�˿�")     ,_T("���ݿ�˿�")        ); colIndex++;  
   InsertFeildID(tableAttri,  colIndex ,  DBCusDb_key_cDbAccount			, _T("���ݿ��˻�")     ,_T("���ݿ��˻�")        ); colIndex++;  
   InsertFeildID(tableAttri,  colIndex ,  DBCusDb_key_cDbPassword			, _T("���ݿ�����")     ,_T("���ݿ�����")        ); colIndex++;  
   InsertFeildID(tableAttri,  colIndex ,  DBCusDb_key_cDbServerIP			, _T("���ݿ�IP")       ,_T("���ݿ�IP")          ); colIndex++;  
   InsertFeildID(tableAttri,  colIndex ,  XML_CUSMGN_FIELD_cTime			, _T("����ʱ��")       ,_T("����ʱ��")          ); colIndex++; 
   InsertFeildID(tableAttri,  colIndex ,  XML_CUSMGN_FIELD_cPerson		, _T("�����֤")        ,_T("�����֤")        ); colIndex++;  
   InsertFeildID(tableAttri,  colIndex ,  XML_CUSMGN_FIELD_cModeData		, _T("����ģ��")        ,_T("����ģ��")        ); colIndex++;  
   InsertFeildID(tableAttri,  colIndex ,  XML_CUSMGN_FIELD_cBeginTime	, _T("��ʼʱ��")        ,_T("��ʼʱ��")          ); colIndex++;

   tableAttri.isAllowSort = TRUE;
   tableAttri.isMultiRowSelect = FALSE;
   tableAttri.IsMultiRowSelectNoLoseFocus = FALSE;
   tableAttri.isShowSortBar = FALSE;
   tableAttri.isShowSumBar = FALSE;
   tableAttri.isWholeRowSelect = TRUE;
   tableAttri.nDataRowHeight = CB_GRIDCTRL_DEFAULT_ROWHEIGHT;
   tableAttri.iDataRowFont = CB_GRIDCTRL_DEFAULT_FONT;
}

//		by WangZY 2018/08/24
void CGridCtrlTableAttributeOp::Create_LogInfo(S_GridCtrl_TableAttri &tableAttri)
{
   int colIndex = 1;
   //��ʾ�ڼ���  //������                      //��ʾ����         //�Ƿ���ʾ	
   InsertFeildID(tableAttri,  colIndex ,  DBWorkLog_key_Cate		,_T("���")		   ,_T("���")	,_T(""), TRUE		,FALSE); colIndex++;
   InsertFeildID(tableAttri,  colIndex ,  DBWorkLog_key_Code		,_T("����")		   ,_T("����")	,_T(""), TRUE		,FALSE); colIndex++;
   InsertFeildID(tableAttri,  colIndex ,  DBWorkLog_key_Date		,_T("��������")	,_T("��������")	,_T(""), TRUE		,FALSE); colIndex++;
   InsertFeildID(tableAttri,  colIndex ,  DBWorkLog_key_Maker		,_T("������Ա")	,_T("������Ա")	,_T(""), TRUE		,FALSE); colIndex++;
   InsertFeildID(tableAttri,  colIndex ,  DBWorkLog_key_Type		,_T("��������")	,_T("��������")	,_T(""), TRUE		,FALSE); colIndex++;
   InsertFeildID(tableAttri,  colIndex ,  DBWorkLog_key_Detail		,_T("��ע")		   ,_T("��ע")	,_T(""), TRUE		,FALSE); colIndex++;

}
//�ͻ�����--������¼ yangjr 2018/8/30
void CGridCtrlTableAttributeOp::Create_CusMgnOpRecords(S_GridCtrl_TableAttri &tableAttri)
{
   int colIndex = 1;
   //�ڼ���		������											����				��ʾ	�༭
   InsertFeildID(tableAttri,  colIndex ,  DBCusOpRds_key_ID				   , _T("ID")           ,_T("")        ); colIndex++;  
   InsertFeildID(tableAttri,  colIndex ,  DBCusOpRds_key_cOpType			, _T("��������")           ,_T("")        ); colIndex++;  
   
   InsertFeildID(tableAttri,  colIndex ,  DBCusOpRds_key_cCusCode			, _T("�ͻ����")      ,_T("")        ); colIndex++;   
   InsertFeildID(tableAttri,  colIndex ,  DBCusOpRds_key_cCusName			, _T("�ͻ�����")      ,_T("")        ); colIndex++;   
   InsertFeildID(tableAttri,  colIndex ,  DBCusOpRds_key_cCusAddress		, _T("��ַ")          ,_T("")        ); colIndex++;   
   InsertFeildID(tableAttri,  colIndex ,  DBCusOpRds_key_cCusPhone			, _T("��ϵ�绰")      ,_T("")        ); colIndex++; 
   InsertFeildID(tableAttri,  colIndex ,  DBCusOpRds_key_cCusContacts		, _T("��ϵ��")        ,_T("")        ); colIndex++;   
   InsertFeildID(tableAttri,  colIndex ,  DBCusOpRds_key_cPDMVersion		, _T("�汾��")        ,_T("")              ); colIndex++;   
   InsertFeildID(tableAttri,  colIndex ,  DBCusOpRds_key_cProvince			, _T("ʡ��")          ,_T("")                ); colIndex++;   
   InsertFeildID(tableAttri,  colIndex ,  DBCusOpRds_key_isLocalDB			, _T("�Ƿ񱾵ز���")   ,_T("")         ); colIndex++;
   InsertFeildID(tableAttri,  colIndex ,  DBCusOpRds_key_cServerPerson	, _T("������Ա")      ,_T("")        ); colIndex++;   
   InsertFeildID(tableAttri,  colIndex ,  DBCusOpRds_key_iClientNum		, _T("�ͻ�������")     ,_T("")        ); colIndex++;   
   InsertFeildID(tableAttri,  colIndex ,  DBCusOpRds_key_cMemo			   , _T("��ע")           ,_T("")        ); colIndex++; 

   InsertFeildID(tableAttri,  colIndex ,  DBCusOpRds_key_cDbServerName		, _T("���ݿ�����")     ,_T("")           ); colIndex++; 
   InsertFeildID(tableAttri,  colIndex ,  DBCusOpRds_key_iDbServerPort		, _T("���ݿ�˿�")     ,_T("")        ); colIndex++;  
   InsertFeildID(tableAttri,  colIndex ,  DBCusOpRds_key_cDbAccount			, _T("���ݿ��˻�")     ,_T("")        ); colIndex++;  
   InsertFeildID(tableAttri,  colIndex ,  DBCusOpRds_key_cDbPassword			, _T("���ݿ�����")     ,_T("")        ); colIndex++;  
   InsertFeildID(tableAttri,  colIndex ,  DBCusOpRds_key_cDbServerIP			, _T("���ݿ�IP")       ,_T("")          ); colIndex++;  

   InsertFeildID(tableAttri,  colIndex ,  DBCusOpRds_key_cTime			, _T("����ʱ��")       ,_T("")          ); colIndex++; 
   InsertFeildID(tableAttri,  colIndex ,  DBCusOpRds_key_cPerson		, _T("�����֤")        ,_T("")        ); colIndex++;  
   InsertFeildID(tableAttri,  colIndex ,  DBCusOpRds_key_cModeData		, _T("����ģ��")        ,_T("")        ); colIndex++;  
   InsertFeildID(tableAttri,  colIndex ,  DBCusOpRds_key_cBeginTime	, _T("��ʼʱ��")        ,_T("")          ); colIndex++;
   InsertFeildID(tableAttri,  colIndex ,  DBCusOpRds_key_fChongZhiJE	, _T("���γ�ֵ���")        ,_T("")          ); colIndex++;
   tableAttri.isAllowSort = TRUE;
   tableAttri.isMultiRowSelect = FALSE;
   tableAttri.IsMultiRowSelectNoLoseFocus = FALSE;
   tableAttri.isShowSortBar = FALSE;
   tableAttri.isShowSumBar = FALSE;
   tableAttri.isWholeRowSelect = TRUE;
   tableAttri.nDataRowHeight = CB_GRIDCTRL_DEFAULT_ROWHEIGHT;
   tableAttri.iDataRowFont = CB_GRIDCTRL_DEFAULT_FONT;
}

