// QlFileTransferEx.h : QlFileTransferEx DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "CommonAPI.h"
#include "tinyxml\tinyxml.h"


/******************�ַ������� ��Կ����*************************/
#define WORD_PWD_KEY			52369
#define CONST_PWD_C1			52845
#define CONST_PWD_C2			22719

// CQlFileTransferExApp
// �йش���ʵ�ֵ���Ϣ������� QlFileTransferEx.cpp
//

class CQlFileTransferExApp : public CWinApp
{

public:
	CString m_strKdsPath;//kds��Ŀ¼��eg:���������
	CString m_strSvrPath;//�������˻��ļ�
	CString m_strMgnPath;//���������˻��ļ�
	CString m_strMacPath;//���������˻��ļ�

private:
	ULONG_PTR m_nGdiplusToken;			//GDI+

public:
	CQlFileTransferExApp();
	void GetIniKeyValue( CString strSection,CString strKeyName,CString &strKeyValue,CString strPathFile);
	void SetIniKeyValue( CString strSection,CString strKeyName,CString strKeyValue,CString strPathFile);
	CString OnEncodeStr( CString strData, WORD nKey = WORD_PWD_KEY);
	CString OnDecodeStr( CString strData, WORD nKey = WORD_PWD_KEY);

	//�������״̬ �ж��Ƿ������ӵ��κ�����(���������߹�����)
	BOOL CheckNetState();

	//�Ӽ�¼���л�ȡ��Ӧ��ͼƬ������תΪbase64�ַ���
	int LoadImageStringFromDB(CString strField,_RecordsetPtr ptSet,wstring & sBase64);

	//��ȡutf8�����ַ�������ת��unicode����
	CString  GetTinyXmlNodeString( TiXmlElement * pElement);

	CString  GetTinyXmlAttriString(TiXmlElement * pElement,const char * Attri);

	/*

	TiXmlElement* pDetail = new TiXmlElement("Detail");
	pProductInfo->LinkEndChild(pDetail);
	//pDetail->SetAttribute("attribute",(_bstr_t)pDoc->m_oProductInfo.m_strDetails);
	TiXmlText * text = new TiXmlText((_bstr_t)(pDoc->m_oProductInfo.m_strDetails));  ///�ı�
	pDetail->LinkEndChild(text);
*/
	//���һ������TiXmlText�µ�TiXmlElement��TiXmlElement��pParrentElecment������ȥ
	TiXmlElement*     LinkTextElementFormat(TiXmlElement * pParrentElecment,CString sElementValue,_In_z_ _FormatMessage_format_string_ LPCTSTR pszFormat,...);

	TiXmlElement*     LinkTextElement(TiXmlElement * pParrentElecment,CString sElementValue,CString sTextValue);
/*

	TiXmlElement* pSize = new TiXmlElement("Size");
	pProcessroot->LinkEndChild(pSize);
	pSize->SetAttribute("attribute",(_bstr_t)strGGName);*/
	//���һ������Attribute�µ�TiXmlElement��TiXmlElement��pParrentElecment������ȥ
	TiXmlElement*     LinkAttributeElement(TiXmlElement * pParrentElecment,CString sElementValue,CString sAttributeDestribution,CString sAttributeValue);

	inline void     UNICODE_TO_UTF8(const std::wstring& uni_str, std::string& utf8_str);

	std::string     UNICODE_TO_UTF8(CStringW strIn);

	//UTF8����תunicode
	inline void     UTF8_TO_UNICODE(const std::string utf8_str,std::wstring& uni_str);

	CString         UTF8_TO_UNICODE(const std::string utf8_str);

	inline void ACP_TO_UNICODE(const std::string acp_str,std::wstring& uni_str);

	inline void UNICODE_TO_ACP(const std::wstring& uni_str,std::string& acp_str);

	inline void ACP_TO_UTF8(const std::string acp_str,std::string& utf8_str);
	inline void UTF8_TO_ACP(const std::string utf8_str,std::string& acp_str);

   BOOL CreateFolder(LPCTSTR szFolder);//�������Ŀ¼

   CString GetFileParentFolder(LPCTSTR strFilePath);//��ȡ�ļ��� ��·���������̷�+·����

#ifndef _UNICODE
	std::string     ACP_TO_UTF8(CString strIn);
	CString         UTF8_TO_ACP(const std::string utf8_str);
#endif // _UNICODE
   //������Դ���ַ�����  
   BOOL LoadResourceToContent(UINT uID, const CString & strType, CString& csContent);
   //����Դ�ͷŵ��ļ�
   BOOL FreeResourceToFile(UINT uID, const CString & strType, const CString & strOutputPath);
// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CQlFileTransferExApp theApp;
