// FeiShaZhuanShu.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "FeiShaZhuanShu.h"
#include "CFileShapeGye.h"

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
         CFileShapeGye Gye;
         CShapeProfileData Data;
         //Gye.FileOpen(_T("单面后片.gye"), &Data);
         Gye.FileOpen(_T("1.CXC"), &Data);
         std::string strBuf;
         Gye.GetStream(strBuf, &Data);
         std::cout << strBuf << std::endl;
         Data.m_bNeckSplit = 5;
         Data.m_enShapeType = ShapeSpace::en_Shape_Right;
         Data.m_ParamSet.bSetWasteSecYarnLeft = TRUE;
         Data.x_Border_up = 777;
         Gye.FileWrite(&Data);

         {
            CShapeProfileData Data2;
            CFileShapeGye Gye2;
            Gye2.StreamParse(strBuf, &Data2);

            
            std::cout << Data2.m_bNeckSplit << std::endl;

            {
               CFileShapeGye Gye3;
               Gye3.GetStream(strBuf, &Data);
               std::cout << strBuf << std::endl;
            }
         }
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
