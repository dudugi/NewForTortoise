// Directory.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QLSvrMgn.h"
#include "Directory.h"
#include <shellapi.h>
#include <string.h>
#include <tchar.h>


// CDirectory

IMPLEMENT_DYNAMIC(CDirectory, CWnd)

CDirectory::CDirectory()
{

}

CDirectory::~CDirectory()
{
}


BEGIN_MESSAGE_MAP(CDirectory, CWnd)
END_MESSAGE_MAP()



// CDirectory ��Ϣ�������

//ѡ���ļ��жԻ���ص�����   
int CALLBACK BrowseCallBackFun(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)  
{  
	switch(uMsg)
	{

	case BFFM_INITIALIZED:    //��ʼ����ϢBFFM_INITIALIZED
		::SendMessage(hwnd,BFFM_SETSELECTION,TRUE,(LPARAM)lpData);   //����Ĭ�ϴ�·�� 
		break;
	case BFFM_SELCHANGED:    //ѡ��·���仯��BFFM_SELCHANGED
		{
			TCHAR curr[MAX_PATH];   
			if(SHGetPathFromIDList((LPCITEMIDLIST)lParam,curr))
			{
				::SendMessage(hwnd,BFFM_SETSTATUSTEXT,0,(LPARAM)&curr[0]);  
			}		
		}
		break;
	default:
		break;
	} 
	return 0;
}  


BOOL CDirectory::OpenDirectory(CString &strRetPath,CString strDefPath)
{
	BOOL  bRet = FALSE;		//��������ֵ

	TCHAR pszPath[MAX_PATH];
	TCHAR defPath[MAX_PATH];
	BOOL bCallBack = FALSE;

	strRetPath.Empty();
	strDefPath.Trim();
	if (!strDefPath.IsEmpty())
	{
		bCallBack = TRUE;
		_tcscpy_s(defPath, strDefPath);
	}
	
	BROWSEINFO bi; 
	ZeroMemory(&bi,sizeof(BROWSEINFO));
	bi.ulFlags = BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT | BIF_USENEWUI | BIF_NEWDIALOGSTYLE;
	bi.lpszTitle = _T("��ѡ��Ŀ¼");  
	bi.hwndOwner = this->GetSafeHwnd();
	if(bCallBack)
	{
		bi.lpfn = BrowseCallBackFun;     //�ص����� 
		bi.lParam = (LPARAM)(&defPath);
	}

	LPITEMIDLIST pidl = SHBrowseForFolder(&bi); 
	if(pidl != NULL)  
	{  
		SHGetPathFromIDList(pidl,pszPath);
		strRetPath = pszPath;//��ֵ
		bRet = TRUE;
	}
	
	return bRet;
}

BOOL CDirectory::OpenDirFile(CString &strRetPath,CString strDefPath,CString strDefFile,CString strFilter,BOOL bOpen/*=TRUE*/)
{
	BOOL  bRet = FALSE;		//��������ֵ

	strRetPath.Empty();
	strDefPath.Trim();
	strFilter.Trim();
 
	DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	if (bOpen) dwFlags |= OFN_FILEMUSTEXIST;
	
	CFileDialog fileDlg(bOpen,strFilter,strDefFile,dwFlags,strFilter,this);
	fileDlg.m_ofn.lpstrInitialDir =  LPCTSTR(strDefPath);// Ĭ��Ŀ¼

	if(IDOK == fileDlg.DoModal())
	{
		strRetPath = fileDlg.GetPathName();
		bRet = TRUE;
	}

	return bRet;
}


BOOL CDirectory::CopyDirectory(CString strSrcPath, CString strDesPath)
{
	if(strSrcPath.IsEmpty() )
	{      
		OutputDebugString(_T("Դ�ļ���Ϊ�գ��޷����п���!"));   
		return FALSE;
	}
	CreateDirectory(strDesPath,NULL); //����Ŀ���ļ���     
    CFileFind finder;  
    CString srcSubPath;    
    BOOL rRet = FALSE;  
    srcSubPath.Format(_T("%s\\*.*"),strSrcPath);      
    BOOL bWorking = finder.FindFile(srcSubPath);    
    while(bWorking)  
    {    
        bWorking = finder.FindNextFile();    
        if(finder.IsDirectory() && !finder.IsDots())//���ļ��� ���� ���Ʋ��� . �� ..    
        {   
            //�ݹ鴴���ļ���+"/"+finder.GetFileName()  
            CopyDirectory(finder.GetFilePath(),strDesPath+_T("\\")+finder.GetFileName());     
        }    
        else//���ļ� ��ֱ�Ӹ���   
        {    
            CString stSrcFile = finder.GetFilePath();  
            BOOL result=(GetFileAttributes(stSrcFile) & FILE_ATTRIBUTE_DIRECTORY);  
            if (!result)  
            {  
               rRet = CopyFile(finder.GetFilePath(),strDesPath+_T("\\")+finder.GetFileName(),FALSE);    
// 				WCHAR src[256] = {0};
// 				WCHAR des[256] = {0};
// 
// 
// 
// 
// 				memset(src, 0, 256*sizeof(WCHAR));
// 				memset(des, 0, 256*sizeof(WCHAR));
// 				_tcscpy(src, finder.GetFilePath());//ע�����֮ǰcopy���ɹ�������Ϊ����
// 				_tcscpy(des, (strDesPath+_T("\\")+finder.GetFileName()));
// 
// 			SHFILEOPSTRUCT FileOp;
// 			FileOp.hwnd = this->m_hWnd;
// 			FileOp.wFunc = FO_COPY; //ִ���ļ�����
// 			CString strTitle = _T("���ڿ����ļ�,���Ժ�...");
// 			FileOp.pFrom = (WCHAR *)src;
// 			FileOp.pTo = (WCHAR *)des;
// 			FileOp.fFlags = FOF_ALLOWUNDO | FOF_NOCONFIRMATION;
// 			FileOp.hNameMappings = NULL;
// 			FileOp.lpszProgressTitle = strTitle;
// 			SHFileOperation(&FileOp);
            }  
        }    
    }    
    return rRet;  
}

BOOL CDirectory::CopyDirFileAPI(CString strSrcPath, CString strDesPath)
{
	//�����ļ�
	if(strSrcPath.IsEmpty())
	{
		OutputDebugString(_T("Դ�ļ�������Ϊ��!"));
		return FALSE;
	}
	if(strDesPath.IsEmpty())
	{
		OutputDebugString(_T("Ŀ���ļ�������Ϊ��!"));
		return FALSE;
	}
	if(!PathFileExists(strDesPath))
	{
		 CreateDirectory(strDesPath, NULL);
	}
   if (strSrcPath.GetAt(strSrcPath.GetLength()-1) == '\\' || strSrcPath.GetAt(strSrcPath.GetLength()-1) == '/')
   {
     strSrcPath = strSrcPath.Left(strSrcPath.GetLength()-1);
   }
   if (strDesPath.GetAt(strDesPath.GetLength()-1) == '\\' || strDesPath.GetAt(strDesPath.GetLength()-1) == '/')
   {
     strDesPath = strDesPath.Left(strDesPath.GetLength()-1);
   }
   strSrcPath = strSrcPath + _T("\\*.*");
     			/*strcpy(szFrom, (LPCTSTR)strSrcPath);*/
  /* szFrom[strSrcPath.GetLength()+1]='\0';*/
     			//strDes=strDes+"\\*.*";
     			/*strcpy(szTo,(LPCTSTR)strDesPath);*/
  /* szTo[strDesPath.GetLength()+1]='\0';*/
   int nOk = 2000;
   CString strTitle = _T("���ڿ����ļ�,���Ժ�...");
   SHFILEOPSTRUCT FileOp;
//    const char * From = (const char *)szFrom;
//    const char * To = (const char *)szTo;
   WCHAR src[256] = {0};
   WCHAR des[256] = {0};
   memset(src, 0, 256*sizeof(WCHAR));
   memset(des, 0, 256*sizeof(WCHAR));
   _tcscpy(src, strSrcPath);//ע�����֮ǰcopy���ɹ�������Ϊ����
   _tcscpy(des, strDesPath);
//    FileOp.hwnd = this->m_hWnd
//    FileOp.wFunc = FO_COPY; //ִ���ļ�����
//    FileOp.pFrom = src;
//    FileOp.pTo = des;
//    FileOp.fFlags = FOF_ALLOWUNDO | FOF_WANTNUKEWARNING | FOF_NOCONFIRMATION;
//    FileOp.hNameMappings = NULL;
//    FileOp.lpszProgressTitle = strTitle;
   FileOp.fFlags = FOF_NOCONFIRMATION | FOF_SILENT;
   FileOp.hNameMappings = NULL;
   FileOp.hwnd = NULL;
   FileOp.lpszProgressTitle = NULL;
   FileOp.pFrom = src;
   FileOp.pTo = des;
   FileOp.wFunc = FO_COPY;
   nOk = SHFileOperation(&FileOp);
   if (FileOp.fAnyOperationsAborted) //��ֹ���ֵ����ù���BUG
   {
     nOk=1;
   }
   if (nOk==1)
   {
    return FALSE;
   }
   Sleep(200);
   return TRUE;
}
