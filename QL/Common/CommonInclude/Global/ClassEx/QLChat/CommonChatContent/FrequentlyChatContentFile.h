#pragma once
/*************************************************
// <文件>: FrequentlyChatContentFile.h
// <说明>: 常用聊天内容，xml配置文件读写类
// <作者>: duchen
// <日期>: 2019/02/22
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#include <vector>
#include <afxstr.h>

class CFrequentlyChatContentFile
{
public:
   BOOL ReadFile(const CString &sFilePath); //读文件
   BOOL WriteFile(const CString &sFilePath); //写文件
   std::vector<CString> m_vecContent; //常用文字内容容器

   static const char *const SZ_XML_ELEMENT_CHAT; //xml元素字符串 chat
   static const char *const SZ_XML_ELEMENT_CONTENT; //xml元素字符串 content
};