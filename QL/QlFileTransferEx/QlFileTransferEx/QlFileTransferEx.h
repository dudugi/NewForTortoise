// QlFileTransferEx.h : QlFileTransferEx DLL 的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include "CommonAPI.h"
#include "tinyxml\tinyxml.h"


/******************字符串加密 秘钥常量*************************/
#define WORD_PWD_KEY			52369
#define CONST_PWD_C1			52845
#define CONST_PWD_C2			22719

// CQlFileTransferExApp
// 有关此类实现的信息，请参阅 QlFileTransferEx.cpp
//

class CQlFileTransferExApp : public CWinApp
{

public:
	CString m_strKdsPath;//kds根目录（eg:琪利软件）
	CString m_strSvrPath;//服务器账户文件
	CString m_strMgnPath;//订单管理账户文件
	CString m_strMacPath;//机器管理账户文件

private:
	ULONG_PTR m_nGdiplusToken;			//GDI+

public:
	CQlFileTransferExApp();
	void GetIniKeyValue( CString strSection,CString strKeyName,CString &strKeyValue,CString strPathFile);
	void SetIniKeyValue( CString strSection,CString strKeyName,CString strKeyValue,CString strPathFile);
	CString OnEncodeStr( CString strData, WORD nKey = WORD_PWD_KEY);
	CString OnDecodeStr( CString strData, WORD nKey = WORD_PWD_KEY);

	//检测网络状态 判断是否有连接到任何网络(局域网或者广域网)
	BOOL CheckNetState();

	//从记录集中获取对应的图片并将其转为base64字符串
	int LoadImageStringFromDB(CString strField,_RecordsetPtr ptSet,wstring & sBase64);

	//读取utf8结点的字符串，并转成unicode返回
	CString  GetTinyXmlNodeString( TiXmlElement * pElement);

	CString  GetTinyXmlAttriString(TiXmlElement * pElement,const char * Attri);

	/*

	TiXmlElement* pDetail = new TiXmlElement("Detail");
	pProductInfo->LinkEndChild(pDetail);
	//pDetail->SetAttribute("attribute",(_bstr_t)pDoc->m_oProductInfo.m_strDetails);
	TiXmlText * text = new TiXmlText((_bstr_t)(pDoc->m_oProductInfo.m_strDetails));  ///文本
	pDetail->LinkEndChild(text);
*/
	//添加一个带有TiXmlText新的TiXmlElement到TiXmlElement（pParrentElecment）里面去
	TiXmlElement*     LinkTextElementFormat(TiXmlElement * pParrentElecment,CString sElementValue,_In_z_ _FormatMessage_format_string_ LPCTSTR pszFormat,...);

	TiXmlElement*     LinkTextElement(TiXmlElement * pParrentElecment,CString sElementValue,CString sTextValue);
/*

	TiXmlElement* pSize = new TiXmlElement("Size");
	pProcessroot->LinkEndChild(pSize);
	pSize->SetAttribute("attribute",(_bstr_t)strGGName);*/
	//添加一个带有Attribute新的TiXmlElement到TiXmlElement（pParrentElecment）里面去
	TiXmlElement*     LinkAttributeElement(TiXmlElement * pParrentElecment,CString sElementValue,CString sAttributeDestribution,CString sAttributeValue);

	inline void     UNICODE_TO_UTF8(const std::wstring& uni_str, std::string& utf8_str);

	std::string     UNICODE_TO_UTF8(CStringW strIn);

	//UTF8编码转unicode
	inline void     UTF8_TO_UNICODE(const std::string utf8_str,std::wstring& uni_str);

	CString         UTF8_TO_UNICODE(const std::string utf8_str);

	inline void ACP_TO_UNICODE(const std::string acp_str,std::wstring& uni_str);

	inline void UNICODE_TO_ACP(const std::wstring& uni_str,std::string& acp_str);

	inline void ACP_TO_UTF8(const std::string acp_str,std::string& utf8_str);
	inline void UTF8_TO_ACP(const std::string utf8_str,std::string& acp_str);

   BOOL CreateFolder(LPCTSTR szFolder);//创建多层目录

   CString GetFileParentFolder(LPCTSTR strFilePath);//获取文件的 父路径（驱动盘符+路径）

#ifndef _UNICODE
	std::string     ACP_TO_UTF8(CString strIn);
	CString         UTF8_TO_ACP(const std::string utf8_str);
#endif // _UNICODE
   //加载资源到字符串中  
   BOOL LoadResourceToContent(UINT uID, const CString & strType, CString& csContent);
   //将资源释放到文件
   BOOL FreeResourceToFile(UINT uID, const CString & strType, const CString & strOutputPath);
// 重写
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CQlFileTransferExApp theApp;
