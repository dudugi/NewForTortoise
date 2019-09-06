// TestSqlite.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "GetNeedleModNames.h"
#include "CppSQLite3U.h"
#include <vector>


using namespace std;

BOOL GetNeedleModNames(LPCTSTR pszFilePath, std::vector<CString> *pvecNames)
{
   if (!PathFileExists(pszFilePath))
      return FALSE;

   std::vector<CString> vecNames;

   CppSQLite3DB db;
   CStringW sFilePath;
   sFilePath = pszFilePath;
   db.open(sFilePath);

   CStringW Key = (L"Raynen_Soft");

   db.OpenKey(Key,Key.GetLength());
  

   if(!db.tableExists((L"ModData")))
   {
      return FALSE;
   }

   CppSQLite3Query q = db.execQuery((L"select name from ModData where isneedlemod = 1"));

   while (!q.eof())
   {
      LPCWSTR pszKey = q.fieldValue((L"name"));
      if (pszKey)
      {
         CString sKey;
         sKey = pszKey;
         vecNames.push_back(sKey);
      }

      q.nextRow();
   }

   if (pvecNames)
   {
      pvecNames->swap(vecNames);
   }

   return TRUE;
}