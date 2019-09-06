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

   db.open(pszFilePath);

   CString Key=_T("Raynen_Soft");

   db.OpenKey(Key,Key.GetLength());
  

   if(!db.tableExists(_T("ModData")))
   {
      return FALSE;
   }

   CppSQLite3Query q = db.execQuery(_T("select name from ModData where isneedlemod = 1"));

   while (!q.eof())
   {
      LPCTSTR pszKey = q.fieldValue(_T("name"));
      if (pszKey)
      {
         vecNames.push_back(pszKey);
      }

      q.nextRow();
   }

   if (pvecNames)
   {
      pvecNames->swap(vecNames);
   }

   return TRUE;
}