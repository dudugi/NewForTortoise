// FeiShaZhuanShu.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "FeiShaZhuanShu.h"
#include "CFileShapeGye.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ψһ��Ӧ�ó������

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// ��ʼ�� MFC ����ʧ��ʱ��ʾ����
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: ���Ĵ�������Է���������Ҫ
			_tprintf(_T("����: MFC ��ʼ��ʧ��\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: �ڴ˴�ΪӦ�ó������Ϊ��д���롣
         CFileShapeGye Gye;
         CShapeProfileData Data;
         //Gye.FileOpen(_T("�����Ƭ.gye"), &Data);
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
		// TODO: ���Ĵ�������Է���������Ҫ
		_tprintf(_T("����: GetModuleHandle ʧ��\n"));
		nRetCode = 1;
	}

	return nRetCode;
}
