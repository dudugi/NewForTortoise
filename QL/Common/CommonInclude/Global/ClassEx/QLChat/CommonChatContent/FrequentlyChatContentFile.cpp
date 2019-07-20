#include "stdafx.h"

#include "..\..\tinyxml\tinyxml.h"
#include "FrequentlyChatContentFile.h"
#include "..\Utilities\QLChatString.h"
//#include "LOG\CReportLog.h"

const char *const CFrequentlyChatContentFile::SZ_XML_ELEMENT_CONTENT = "Content";
const char *const CFrequentlyChatContentFile::SZ_XML_ELEMENT_CHAT = "Chat";

BOOL CFrequentlyChatContentFile::ReadFile(const CString &sFilePath)
{
   if (sFilePath.IsEmpty())
   {
      //LOGEXEERROR(_T("常用聊天内容配置文件路径为空"));
      return FALSE;
   }

   if (!PathFileExists(sFilePath))
   {
      //LOGEXEINFO(_T("常用聊天内容配置文件不存在"));
      return FALSE;
   }

   TiXmlDocument xmlDoc;
   USES_CONVERSION;
   xmlDoc.SetCondenseWhiteSpace(false);
   if (!xmlDoc.LoadFile(W2A(sFilePath) ,TIXML_ENCODING_UTF8))
   {
      //LOGEXEERROR(_T("常用聊天内容配置文件读取失败"));
      return FALSE;
   }

   TiXmlElement *pRoot = xmlDoc.RootElement();

   if (!pRoot)
   {
      //LOGEXEERROR(_T("常用聊天内容配置文件读取失败，找不到根节点"));
      return FALSE;
   }

   std::vector<CString> vecContents;
   TiXmlElement *pContent = pRoot->FirstChildElement(SZ_XML_ELEMENT_CONTENT);
   while (pContent)
   {
      const char *szText = pContent->GetText();
      if (szText != nullptr)
      {
         CString sText = QLChat::UTF8_TO_UNICODE(szText);
         vecContents.push_back(sText);
      }
      pContent = pContent->NextSiblingElement(SZ_XML_ELEMENT_CONTENT);
   }
   m_vecContent.swap(vecContents);
   //LOGEXEINFO(_T("常用聊天内容配置文件读取正常结束"));
   return TRUE;
}

BOOL CFrequentlyChatContentFile::WriteFile(const CString &sFilePath)
{
   if (sFilePath.IsEmpty())
   {
      //LOGEXEERROR(_T("常用聊天内容配置文件写入失败，路径为空"));
      return FALSE;
   }

   TiXmlDocument xmlDoc;
   USES_CONVERSION;
   xmlDoc.SetCondenseWhiteSpace(false);

   TiXmlDeclaration *pDeclaration = new TiXmlDeclaration("1.0", "UTF-8", "yes");
   if(!pDeclaration)
   {
      //LOGEXEERROR(_T("常用聊天内容配置文件写入失败，声明生成失败"));
      return FALSE;
   }

   xmlDoc.LinkEndChild(pDeclaration);

   TiXmlElement *pRoot = new TiXmlElement(SZ_XML_ELEMENT_CHAT);
   xmlDoc.LinkEndChild(pRoot);

   for (auto Iter = m_vecContent.begin(); Iter != m_vecContent.end(); ++Iter)
   {
      TiXmlElement *pContent = new TiXmlElement(SZ_XML_ELEMENT_CONTENT);

      std::vector<char> str = QLChat::UNICODE_TO_UTF8(*Iter);
      TiXmlText *pTextType = new TiXmlText(str.data());
      pContent->LinkEndChild(pTextType);
      pRoot->LinkEndChild(pContent);
   }
   if (!xmlDoc.SaveFile(W2A(sFilePath)))
   {
      //LOGEXEERROR(_T("常用聊天内容配置文件写入失败"));
      return FALSE;
   }
   //LOGEXEINFO(_T("常用聊天内容配置文件写入成功"));
   return TRUE;
}