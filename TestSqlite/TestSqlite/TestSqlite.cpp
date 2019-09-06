// TestSqlite.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "TestSqlite.h"
#include "CppSQLite3U.h"
#include <vector>
#include "GetNeedleModNames.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// 初始化 MFC 并在失败时显示错误
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: 更改错误代码以符合您的需要
			_tprintf(_T("错误: MFC 初始化失败\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: 在此处为应用程序的行为编写代码。

         cout.imbue(std::locale("chs"));

//          CppSQLite3DB db;
//          TCHAR appPath[MAX_PATH+1];
//          GetModuleFileName(NULL,appPath,MAX_PATH);
//          PathRemoveFileSpec(appPath);
//          _tcscat(appPath,L"\\chat.db");
         //db.open(appPath);

         {
            std::vector<CString> vecNeedleNames;
            if (!GetNeedleModNames(_T("D:\\svnD\\QL-Cloth6-20190216\\KDS\\制版模块\\用户文件\\制版\\用户配置\\UserModDb.db"),
               &vecNeedleNames))
            {
               return 0;
            }

            for (auto Iter = vecNeedleNames.begin(); Iter != vecNeedleNames.end(); ++Iter)
            {
               std::cout << (LPCTSTR)*Iter
                  << std::endl;
            }
            system(("pause"));
            return 0;
         }
#ifdef UNICODE
         CppSQLite3DB db;
         //db.open(appPath);
         //db.open(_T("D:\\svnD\\PDM-source\\版房数据中心系统\\KDS-TaskTableBFThird\\Debug\\chat.db"));
         db.open(_T("chat.db"));

         if(!db.tableExists(_T("Chat_MsgMgn")))
         {
            //db.execDML(_T("create table TABLE2(key integer PRIMARY KEY autoincrement, language TEXT, value TEXT);"));
            db.execDML(_T("create table Chat_MsgMgn(AutoID integer PRIMARY KEY, cOrderNo TEXT, cSendUserID TEXT, dSendTime timestamp, \
               cContent TEXT, cFile TEXT, iMsgType INTEGER, iMsgState INTEGER);"));
         }

         //try
         //{
         //   int n = db.execDML(_T("update Chat_MsgMgn set corderno = 'dgy0001' where corderno = 'w531'"));
         //   std::wcout << n << std::endl;
         //}
         //catch (CppSQLite3Exception &e)
         //{
         //  CString s =  e.errorMessage();
         //  TRACE(s);
         //}
         //
         //return 0;

         CppSQLite3Query q = db.execQuery(_T("select * from Chat_MsgMgn"));
         while (!q.eof())
         {
            //std::wstring wstring1 = q.fieldValue(_T("TEXT"));

            LPCTSTR pszKey = q.fieldValue(_T("AutoID"));
            if (pszKey)
            {
               CString sFile = _T("[NULL]");
               LPCTSTR pszFile = q.fieldValue(_T("cFile"));
               if (pszFile)
               {
                  sFile = CString(pszFile);
               }

               CString sMsgType = _T("[NULL]");
               LPCTSTR pszMsgType = q.fieldValue(_T("iMsgType"));
               if (pszMsgType)
               {
                  sMsgType = CString(pszMsgType);
               }

               LPCTSTR psziMsgState = q.fieldValue(_T("iMsgState"));
               

               std::wcout << pszKey << _T(" ") << q.fieldValue(_T("cSendUserID")) 
                  << _T(" ") << q.fieldValue(_T("cOrderNo"))
                  << _T(" ") << (LPCTSTR)sFile 
                  << _T(" ") << (LPCTSTR)sMsgType 
                  << _T(" ") << q.fieldValue(_T("cContent"))
                  << _T(" ") << psziMsgState
                  << std::endl;
            }

            q.nextRow();
         }

         system(("pause"));
         return FALSE;
        
         //create table Chat_MsgMgn(AutoID integer PRIMARY KEY, cOrderNo TEXT, cSendUserID TEXT, dSendTime timestamp,
         //   cContent TEXT, cFile TEXT, iMsgType INTEGER, iMsgState INTEGER)

         int nTick1 = GetTickCount();

         srand(time(NULL));
         int nTimes = (rand() % 200);

         int nTick2 = GetTickCount() + nTimes;
         int nTick3 = nTick2 + nTimes;


         TCHAR szChinese[] = _T("\'hahahaha你们这群笨蛋ha2222\'");

         CString sSql;
         sSql.Format(_T("insert or replace into Chat_MsgMgn (AutoID, cOrderNo, cSendUserID, dSendTime, cContent, cFile, iMsgType, iMsgState) \
               select %d, '%s', '%s', '%s', '%s', '%s', '%s', '%s' \
               union all select %d, '%s', '%s', '%s', '%s',  '%s', NULL, %d \
               union all select %d, '%s', '%s', '%s', %s,  '%s', NULL, %d "), 
               nTick1,
               _T("112233"), _T("dudu"), COleDateTime::GetCurrentTime().Format(_T("%Y-%m-%d %H:%M")), 
               _T("hahahahaha"), _T("#bmp.bmp#"), _T("0"), _T("0"),

               nTick2,
               _T("334455"), _T("wys"), COleDateTime::GetCurrentTime().Format(_T("%Y-%m-%d %H:%M")), 
               _T(";File1.bmp;File2.bmp;"), /*NULL,*/ _T("0"), 1,
               nTick3,
               _T("336655"), _T("wzl"), COleDateTime::GetCurrentTime().Format(_T("%Y-%m-%d %H:%M")), 
               szChinese, /*NULL,*/ _T("0"), 1);
         //sSql.Format(_T("insert into TABLE2 (key, language, value) VALUES ('%d', 'aaa', 'bbb')"), GetTickCount());
         //sSql = _T("insert into TABLE2 (language, value) VALUES ( 'aaa', 'bbb')");


         int res;
         try
         {
            res = db.execDML(sSql);
         }
         catch(CppSQLite3Exception e)
         {
            TRACE( e.errorMessage() );
            _tprintf(_T("error: %s"), e.errorMessage());

            

            db.close();

            //ASSERT(0);
            //throw e; 若有用到事务
            return FALSE;
         }

#endif

//          int nRet = db.execDML(sSql);
//          if (SQLITE_OK != nRet)
//          {
//             wprintf(_T("error:"));
//          }
//          wprintf(_T("%d\n"), nRet);

         system(("pause"));
		}
	}
	else
	{
		// TODO: 更改错误代码以符合您的需要
		_tprintf(_T("错误: GetModuleHandle 失败\n"));
		nRetCode = 1;
	}

	return nRetCode;
}
