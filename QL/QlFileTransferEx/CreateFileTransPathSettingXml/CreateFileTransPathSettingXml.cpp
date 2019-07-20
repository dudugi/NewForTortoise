// CreateFileTransPathSettingXml.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <tinyxml\tinyxml.h>
#include <CommonAPI.h>
#include <vector>


CCommonAPI QLCOMAPI;

typedef struct S_SUBITEM_INFO{
   char sKey[50];//Key
   char sPath[256];//Path
   bool bUploadZip;//UploadZip
   bool bDownDelZip;//DownDelZip
   bool bUnZipFailRename;//UnZipFailRename
}SubItemInfo;


inline void     UNICODE_TO_UTF8(const std::wstring& uni_str, std::string& utf8_str);

std::string     UNICODE_TO_UTF8(CStringW strIn);

//UTF8����תunicode
inline void     UTF8_TO_UNICODE(const std::string utf8_str,std::wstring& uni_str);

CString         UTF8_TO_UNICODE(const std::string utf8_str);

inline void ACP_TO_UNICODE(const std::string acp_str,std::wstring& uni_str);

inline void UNICODE_TO_ACP(const std::wstring& uni_str,std::string& acp_str);

inline void ACP_TO_UTF8(const std::string acp_str,std::string& utf8_str);
inline void UTF8_TO_ACP(const std::string utf8_str,std::string& acp_str);

#ifndef _UNICODE
std::string     ACP_TO_UTF8(CString strIn);
CString         UTF8_TO_ACP(const std::string utf8_str);
#endif // _UNICODE

S_SUBITEM_INFO SetSubItemInfo(const CString & strKey,const CString & strPath,bool bUploadZip = true,
   bool bDownDelZip = true,bool bUnZipFailName = false);
std::vector<SubItemInfo> GetSubItemInfo();

TiXmlElement* LinkTextElement(TiXmlElement * pParrentElecment,CString sElementValue,CString sTextValue)
{
#ifdef _UNICODE
   CStringW sw(sTextValue),sValueW(sElementValue);
   TiXmlElement* pChild = new TiXmlElement(UNICODE_TO_UTF8(sValueW).c_str());
   pParrentElecment->LinkEndChild(pChild);
   TiXmlText * text = new TiXmlText(UNICODE_TO_UTF8(sw).c_str());  ///�ı�
   pChild->LinkEndChild(text);
#else
   TiXmlElement* pChild = new TiXmlElement(ACP_TO_UTF8(sElementValue).c_str());
   pParrentElecment->LinkEndChild(pChild);
   TiXmlText * text = new TiXmlText(ACP_TO_UTF8(sTextValue).c_str());  ///�ı�
   pChild->LinkEndChild(text);
#endif // _UNICODE

   return pChild;
}

int _tmain(int argc, _TCHAR* argv[])
{
   TiXmlDocument doc;
   TiXmlDeclaration* declaration = new TiXmlDeclaration("1.0", "UTF-8", "yes");
   if(!declaration)
      return 0;
   doc.LinkEndChild(declaration);

   TiXmlElement* root = new TiXmlElement("Root");
   doc.LinkEndChild(root);

   auto vec_SubItem = GetSubItemInfo();

   for (auto it = vec_SubItem.begin();it != vec_SubItem.end();++it)
   {
      auto pSubItem = LinkTextElement(root,_T("SubItem"),_T(""));
      LinkTextElement(pSubItem,_T("Key"),CString(it->sKey));
      LinkTextElement(pSubItem,_T("Path"),CString(it->sPath));
      LinkTextElement(pSubItem,_T("UploadZip"),it->bUploadZip ? _T("1") : _T("0"));
      LinkTextElement(pSubItem,_T("DownDelZip"),it->bDownDelZip ? _T("1") : _T("0"));
      LinkTextElement(pSubItem,_T("UnZipFailRename"),it->bUnZipFailRename ? _T("1") : _T("0"));
   }

   CString strXmlFile = _T("FileTransPathSetting.xml");

   char szFarFilePath[256] = {0};
   QLCOMAPI.WCharToMByte(strXmlFile,szFarFilePath,sizeof(szFarFilePath)/sizeof(szFarFilePath[0]));
   doc.SaveFile(szFarFilePath);

	return 0;
}

S_SUBITEM_INFO SetSubItemInfo(const CString & strKey,const CString & strPath,bool bUploadZip /*= true*/, bool bDownDelZip /*= true*/,bool bUnZipFailName /*= false*/)
{
   S_SUBITEM_INFO s_ValueInfo;
   memset(s_ValueInfo.sKey,0,sizeof(s_ValueInfo.sKey));
   memset(s_ValueInfo.sPath,0,sizeof(s_ValueInfo.sPath));
   QLCOMAPI.WCharToMByte(strKey,s_ValueInfo.sKey,sizeof(s_ValueInfo.sKey)/sizeof(s_ValueInfo.sKey[0]));
   QLCOMAPI.WCharToMByte(strPath,s_ValueInfo.sPath,sizeof(s_ValueInfo.sPath)/sizeof(s_ValueInfo.sPath[0]));

   s_ValueInfo.bUploadZip = bUploadZip;
   s_ValueInfo.bDownDelZip = bDownDelZip;
   s_ValueInfo.bUnZipFailRename = bUnZipFailName;
   return s_ValueInfo;
}

std::vector<SubItemInfo> GetSubItemInfo()
{
   std::vector<SubItemInfo> vecRet;

   //Order_Process
   //������/$OrderNo$/�����ļ�/$Size$/
   vecRet.push_back(SetSubItemInfo(_T("File_Pattern")             ,_T("������/$OrderNo$/�ư��ļ�/$Size$/")));
   vecRet.push_back(SetSubItemInfo(_T("File_Process")             ,_T("������/$OrderNo$/�����ļ�/$Size$/")));
   vecRet.push_back(SetSubItemInfo(_T("File_Design")              ,_T("������/$OrderNo$/����ļ�/$Size$/")));
   vecRet.push_back(SetSubItemInfo(_T("File_Mac")                 ,_T("������/$OrderNo$/�ϻ��ļ�/$Size$/")));
   vecRet.push_back(SetSubItemInfo(_T("File_Order")               ,_T("������/$OrderNo$/�����ļ�/$Size$/")));
   vecRet.push_back(SetSubItemInfo(_T("File_Thc")                 ,_T("������/$OrderNo$/$Size$/")));
   vecRet.push_back(SetSubItemInfo(_T("File_Picture")             ,_T("������/$OrderNo$/ͼƬ�ļ�/$Size$/"),false,false,true));
   vecRet.push_back(SetSubItemInfo(_T("File_Thumbnail")           ,_T("������/$OrderNo$/ͼƬ�ļ�/����ͼ/"),false,false,true));
   vecRet.push_back(SetSubItemInfo(_T("File_StyleImage")          ,_T("������/$OrderNo$/StyleImage/$Size$/")));
   vecRet.push_back(SetSubItemInfo(_T("File_ChatFile")            ,_T("������/$OrderNo$/ChatFile/$Size$/"),false,false,true));
   vecRet.push_back(SetSubItemInfo(_T("File_ImgProDetail")        ,_T("������/$OrderNo$/ImgProDetail/$Size$/"),false,false,true));
   vecRet.push_back(SetSubItemInfo(_T("File_ImgModel")            ,_T("������/$OrderNo$/ImgModel/$Size$/"),false,false,true));
   vecRet.push_back(SetSubItemInfo(_T("File_ImgModelThumbnail")   ,_T("������/$OrderNo$/ImgModel/����ͼ/"),false,false,true));
   vecRet.push_back(SetSubItemInfo(_T("File_Video")               ,_T("������/$OrderNo$/��Ƶ�ļ�/"),false,false,true));

   vecRet.push_back(SetSubItemInfo(_T("File_BackUp_Pattern")       ,_T("������/$OrderNo$/BackUpFile/�ư��ļ�/$Version$/$Size$/")));
   vecRet.push_back(SetSubItemInfo(_T("File_BackUp_Process")       ,_T("������/$OrderNo$/BackUpFile/�����ļ�/$Version$/$Size$/")));
   vecRet.push_back(SetSubItemInfo(_T("File_BackUp_Design")        ,_T("������/$OrderNo$/BackUpFile/����ļ�/$Version$/$Size$/")));
   vecRet.push_back(SetSubItemInfo(_T("File_BackUp_Mac")           ,_T("������/$OrderNo$/BackUpFile/�ϻ��ļ�/$Version$/$Size$/")));
   vecRet.push_back(SetSubItemInfo(_T("File_BackUp_Order")         ,_T("������/$OrderNo$/BackUpFile/�����ļ�/$Version$/$Size$/")));
   vecRet.push_back(SetSubItemInfo(_T("File_BackUp_Picture")       ,_T("������/$OrderNo$/BackUpFile/ͼƬ�ļ�/$Version$/$Size$/"),false,false,true));
   vecRet.push_back(SetSubItemInfo(_T("File_BackUP_Thumbnail")     ,_T("������/$OrderNo$/BackUpFile/ͼƬ�ļ�/����ͼ/"),false,false,true));
   vecRet.push_back(SetSubItemInfo(_T("File_BackUp_StyleImage")    ,_T("������/$OrderNo$/BackUpFile/StyleImage/$Version$/$Size$/")));
   vecRet.push_back(SetSubItemInfo(_T("File_BackUp_ChatFile")      ,_T("������/$OrderNo$/BackUpFile/ChatFile/$Version$/$Size$/"),false,false,true));
   vecRet.push_back(SetSubItemInfo(_T("File_BackUp_ImgProDetail")  ,_T("������/$OrderNo$/BackUpFile/ImgProDetail/$Version$/$Size$/"),false,false,true));
   vecRet.push_back(SetSubItemInfo(_T("File_BackUp_ImgModel")      ,_T("������/$OrderNo$/BackUpFile/ImgModel/$Version$/$Size$/"),false,false,true));

   vecRet.push_back(SetSubItemInfo(_T("Lib_Bmp")            ,_T("�����/��ͼ��/")));
   vecRet.push_back(SetSubItemInfo(_T("Lib_Style")          ,_T("�����/��ʽ��/")));
   vecRet.push_back(SetSubItemInfo(_T("Lib_Process")        ,_T("�����/���տ�/")));
   vecRet.push_back(SetSubItemInfo(_T("Lib_Density")        ,_T("�����/����/�ܶȱ�/")));
   vecRet.push_back(SetSubItemInfo(_T("Lib_Component")      ,_T("�����/����/������/")));
   vecRet.push_back(SetSubItemInfo(_T("Lib_PatternConfig")  ,_T("�����/Сͼ��/")));
   vecRet.push_back(SetSubItemInfo(_T("Lib_Modfile")        ,_T("�����/���ÿ�/")));

   vecRet.push_back(SetSubItemInfo(_T("Other_Exchange")     ,_T("�����ļ�/"),false,false,true));
   vecRet.push_back(SetSubItemInfo(_T("Other_GlobalChat")   ,_T("GlobalChat/"),false,false,true));
   vecRet.push_back(SetSubItemInfo(_T("Other_WebImage")     ,_T("Web��/������/"),false,false,true));

   return vecRet;
}

void  UNICODE_TO_UTF8(const std::wstring& uni_str, std::string& utf8_str)
{
   long  l_l_Len  = WideCharToMultiByte(
      CP_UTF8,
      NULL,
      uni_str.c_str(),
      -1,
      NULL,
      0,
      NULL,
      FALSE ); 

   // ����洢Unicode������ַ�������Ҫ���ڴ�
   char*  l_p_afterchange = new char[l_l_Len+1];

   // ת���ַ��������ʽ��UTF8��Unicode
   WideCharToMultiByte(
      CP_UTF8,
      NULL,
      uni_str.c_str(),
      -1,
      l_p_afterchange,
      l_l_Len,
      NULL,
      FALSE );

   l_p_afterchange[l_l_Len] = '\0'; 
   utf8_str = std::string(l_p_afterchange);
   delete[] l_p_afterchange;
}

std::string UNICODE_TO_UTF8(CStringW strIn)
{
   std::wstring strwstr(strIn.GetBuffer());
   std::string strOut;
   UNICODE_TO_UTF8(strwstr,strOut);
   return strOut;
}

void UTF8_TO_UNICODE( const std::string utf8_str,std::wstring& uni_str )
{
   long  l_l_Len  = MultiByteToWideChar( 
      CP_UTF8,
      0,
      utf8_str.c_str(),
      static_cast<int>( utf8_str.length() ),
      NULL,
      0 ); 

   // ����洢Unicode������ַ�������Ҫ���ڴ�
   wchar_t*  l_p_afterchange = new wchar_t[l_l_Len+1];

   // ת���ַ��������ʽ��UTF8��Unicode
   MultiByteToWideChar(
      CP_UTF8,
      0,
      utf8_str.c_str(),
      static_cast<int>( utf8_str.length() ),
      l_p_afterchange,
      l_l_Len );  

   l_p_afterchange[l_l_Len] = L'\0'; 
   uni_str = std::wstring(l_p_afterchange);
   delete[] l_p_afterchange;
}

CString UTF8_TO_UNICODE( const std::string utf8_str )
{
   std::wstring strOut;
   UTF8_TO_UNICODE(utf8_str,strOut);
   return CString(strOut.c_str());
}

void ACP_TO_UNICODE(const std::string acp_str,std::wstring& uni_str)
{
   long  l_l_Len  = MultiByteToWideChar(
      CP_ACP,
      0,
      acp_str.c_str(),
      static_cast<int>( acp_str.length() ),
      NULL,
      0 ); 

   // ����洢Unicode������ַ�������Ҫ���ڴ�
   wchar_t*  l_p_afterchange = new wchar_t[l_l_Len+1];

   // ת���ַ��������ʽ��UTF8��Unicode
   MultiByteToWideChar(
      CP_ACP,
      0,
      acp_str.c_str(),
      static_cast<int>( acp_str.length() ),
      l_p_afterchange,
      l_l_Len );  

   l_p_afterchange[l_l_Len] = L'\0'; 
   uni_str = std::wstring(l_p_afterchange);
   delete[] l_p_afterchange;
}

void UNICODE_TO_ACP(const std::wstring& uni_str,std::string& acp_str)
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

   // ����洢Unicode������ַ�������Ҫ���ڴ�
   char* l_p_afterchange = new char[l_l_Len+1];

   // ת���ַ��������ʽ��UTF8��Unicode
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

void ACP_TO_UTF8(const std::string acp_str,std::string& utf8_str)
{
   std::wstring uni_str;
   ACP_TO_UNICODE(acp_str,uni_str);
   UNICODE_TO_UTF8(uni_str,utf8_str);
}

void UTF8_TO_ACP(const std::string utf8_str,std::string& acp_str)
{
   std::wstring uni_str;
   UTF8_TO_UNICODE(utf8_str,uni_str);
   UNICODE_TO_ACP(uni_str,acp_str);
}

#ifndef _UNICODE
std::string ACP_TO_UTF8(CString strIn)
{
   std::string strstr(strIn);
   std::string strOut;
   ACP_TO_UTF8(strstr,strOut);
   return strOut;
}

CString UTF8_TO_ACP(const std::string utf8_str)
{
   std::wstring strOut;
   UTF8_TO_UNICODE(utf8_str,strOut);
   return CString(strOut.c_str());
}
#endif