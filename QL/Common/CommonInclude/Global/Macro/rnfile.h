#pragma once
/********************************************************************
//  ����:           linyp
//  CopyRight(c)    2010 Burnon All Rights Reserved 
//  ����ʱ��:       2014/04/17 15:08
//  ������:         �ļ��������
//  �޸�ʱ��:       
//  �޸�Ŀ��:       
*********************************************************************/
#include "rnstring.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <map>
using namespace std;


namespace RnFile
{//�ļ�����
   
   //************************************
   // ������:  [GetFileOnPath]
   // ����ֵ:  [std::vector<CString>]   
   // ����:    [CString strExt]    
   // ��������:��ȡ��ǰ�ļ�����ָ����׺�������ļ������������ļ��������׺Ϊ�յ�����·��ؿ�
   // ����:    linyp 2016/02/25 16:34
   // �޸�ʱ��:
   // �޸�Ŀ��:
   //************************************
   inline std::vector<CString> GetFileOnPath(CString strPath,CString strExt)
   {
      std::vector<CString> vecFileName;
      if (strExt.IsEmpty())
      {
         return vecFileName;
      }
      CFileFind finder;
      // build a string with wildcards
      CString strWildcard  = strPath + _T("//*.") + strExt;
      // start working for files
      BOOL bWorking = finder.FindFile(strWildcard);
      while (bWorking)
      {
         bWorking = finder.FindNextFile();
         if (finder.IsDots())
            continue;
         vecFileName.push_back(finder.GetFileName());
      }
      return vecFileName;
   }


   //�ļ����������
   /*-------------------------------------------------------------------
	-@brief [��ȡ�ļ�����ȥ��Ŀ¼�ͺ�׺]
	-
	-[������ϸ����]
	-@n<b>��������</b> : GetNameWithoutDirExt
	-@n@param const tstring & str : [ȫ·����]
	-@return             [����ļ���]
	-@see                [�μ�����]
	-@n<b>����</b>     :  
	-@n<b>����ʱ��</b> : 2009-3-17 17:46:25
	-@version    �޸���        ʱ��        ����@n
	-@n                     2009-03-17  [����]
	--------------------------------------------------------------------*/
	inline tstring GetNameWithoutDirExt(const tstring& str)
	{
		//���һ�����
		int nPointPos = static_cast<int>( str.find_last_of(STR_POINT) );
		//���һ��б��
		int nLastSlant = static_cast<int>( str.find_last_of(STR_SLANT) );
		int nStart = nLastSlant + 1;
		int nLength = nPointPos - nLastSlant - 1;
		tstring strTest = str.substr(nStart, nLength);
		return strTest;
	}

	/*-------------------------------------------------------------------
	-@brief [��ô�д���ļ���չ��]
	-
	-[������ϸ����]
	-@n<b>��������</b>: GetFileNameExtUpper
	-@n@param std     ::string & strFile : [��������]
	-@return            [����ֵ����]
	-@see               [�μ�����]
	-@n<b>����</b>    :  
	-@n<b>����ʱ��</b>: 2009-1-12 13:21:08
	-@version    �޸���        ʱ��        ����@n
	-@n                     2009-01-12  [����]
	--------------------------------------------------------------------*/
	inline tstring GetFileNameExtUpper( tstring &strFile )
	{
		int nPoint = static_cast<int>( strFile.find_last_of( _T('.') ) );
		int nAll = static_cast<int>( strFile.length() );
		tstring strFormat = strFile.substr( nPoint + 1, nAll-nPoint);	//��1Խ�����

		CString strUpper = strFormat.c_str();
		strUpper.MakeUpper();
		strFormat = strUpper.GetBuffer();
		strUpper.ReleaseBuffer();

		return strFormat;
	}


    /*************************************
   /* Method:    		GetModulePathFile
   /* Returns:   		CString		
   /* Parameter: 		CString strFileName ���ļ�����
   /* author:	  		JiangXh
   /* Modifier:  
   /* Last Modified: 	2010/05/21 15:15
   /* Purpose:			��ú�EXE�ļ���ͬһĿ¼�µ��ļ�ȫ·��
   /*************************************/
   inline CString GetModulePathFile(CString strFileName)
   {
      TCHAR  szModuleName[MAX_PATH] = {0};
      GetModuleFileName(NULL, szModuleName , MAX_PATH);
      CString strModuleName;
      strModuleName.Format(_T("%s"), szModuleName);
      int iPos = strModuleName.ReverseFind('\\');
      int iLen = strModuleName.GetLength();
      strModuleName = strModuleName.Left(iPos + 1);

      CString strRetFilePath = strModuleName + strFileName;

      return strRetFilePath;
   }

   //����ļ�������������չ��
   inline CString MyGetFileName(CString strPathName,CString strExt = L"")
   {
      ASSERT(AfxIsValidString(strPathName));
      //start Duchen 2016/04/17 17:59 dc170417
      strPathName.Replace(_T("/"), _T("\\"));
      //end   Duchen 2016/04/17 17:59 dc170417
      CString strFileName;
      int nPathSepPos = strPathName.ReverseFind('\\');
      if (-1 == nPathSepPos)
      {//û��б�ܺ�
         strFileName = strPathName;
      }
      else
      {
         strFileName = strPathName.Right(strPathName.GetLength() - nPathSepPos - 1);
      }
      //linyp �����жϺ�׺�����߼��������λ�õĸպ�Ϊ�ṩ�ĺ�׺�������޳���׺���أ������޳���׺
      if(strExt != L"" ) 
      {
         int suffixPos = strPathName.ReverseFind('.');
         CString strSuffixName = (-1 != suffixPos) ? strPathName.Right(strPathName.GetLength() -suffixPos ):strPathName;
         //��׺һ�·���0 ���ز�Ϊ0˵����׺��һ�� ����Ҫ�޳���׺����
         if(0 != strSuffixName.CompareNoCase(strExt))
         {
            return strFileName;
         }
      }
      int nDotPos = strFileName.ReverseFind('.'); //���һ��Dot��λ��
      if (nDotPos != -1)
      {
         strFileName = strFileName.Left(nDotPos); //���һ��Dotǰ���ַ���
      }
      return strFileName;
   }

   //��ð�����չ�����ļ���
   inline  CString MyGetFileNameWithExt(CString strPathName)
   {
      CString strFileName;
      int nPathSepPos = strPathName.ReverseFind('\\');
      strFileName = strPathName.Right(strPathName.GetLength() - nPathSepPos - 1);

      return strFileName;
   }

   //�����չ��
   inline CString MyGetFileExtName(CString strFileName)
   {
      ASSERT(AfxIsValidString(strFileName));
      CString strExtname;
      int nExtPos = strFileName.ReverseFind('.');

      if (-1 == nExtPos)
      {//û�к�׺��
         return _T("");
      }

      strExtname = strFileName.Right(strFileName.GetLength() - nExtPos -1);
      return strExtname;
   }

   //����ļ�·��
   inline CString MyGetFilePath(CString strFilePathName)
   {
      ASSERT(AfxIsValidString(strFilePathName));
      CString strPath;
      int nSepPos = strFilePathName.ReverseFind('\\');
      int nSepPos2 = strFilePathName.ReverseFind('/');
      if (nSepPos2>nSepPos)
      {
         nSepPos = nSepPos2;
      }
      strPath = strFilePathName.Left(nSepPos);
      return strPath;
   }

   //ȷ��·���а�����б��
   inline void MyAppendOppSlash(CString& strPath)
   {
      int nSlashPos = strPath.ReverseFind('\\');
      int nLen = strPath.GetLength() - 1;
      if (nSlashPos != nLen)
      {
         strPath.AppendChar('\\');
      }
   }

   /**
   * @brief [������Ҫ����]
   * ���ݾ���·������ļ������·��,��Ϊ��Ч�ʲ��ж�strAbsPath�Ƿ���strFileFullPathName���Ӵ���ʹ�ú�������ȷ�� strFileFullPathName.Find(strAbsPath) == 0��
   * [������ϸ����]
   * @n<b>��������</b>                    : MyGetRelativePath
   * @n@param CString strAbsPath          : [����·��]
   * @param   CString strFileFullPathName : [�ļ���ȫ·����]
   * @return                                [���·��]
   * @see                                   [�μ�����]
   * @n<b>����</b>                        :
   * @n<b>����ʱ��</b>                    : 2009-6-29 16:33:24
   * @version    �޸���        ʱ��        ����@n
   * @n          [�޸���]      2009-06-29  [����]
   */
   inline CString MyGetRelativePath(CString strAbsPath, CString strFileFullPathName)
   {
      ASSERT(strFileFullPathName.Find(strAbsPath) == 0);
      CString strAbsFilePath;
      strAbsFilePath= MyGetFilePath(strFileFullPathName);
      strAbsFilePath.Delete(0, strAbsPath.GetLength());
      return strAbsFilePath;
   }


   //��ø��ļ��У����������Ӳ�̷����Ļ������ؿ��ַ���
   inline CString MyGetParenteDir(CString strSubDir)
   {
      MyAppendOppSlash(strSubDir);
      CString strPath;
      strPath.Empty();

      int nSepPos = strSubDir.ReverseFind('\\');

      if (nSepPos == -1)
      {
         return strSubDir;
      }
      strSubDir = strSubDir.Left(nSepPos);

      nSepPos = strSubDir.ReverseFind('\\');

      if (nSepPos == -1)
      {
         return strSubDir;
      }

      strPath = strSubDir.Left(nSepPos);

      return strPath;
   }
   //��ȡ�ҵ��ĵ�·��
   inline CString MyGetMyDocumentPath()
   {
      //�ĵ�����·��Ĭ��·��Ϊ�ҵ��ĵ�
      TCHAR   szDocument[MAX_PATH]={0};
      TCHAR m_lpszDefaultDir[MAX_PATH] = {0};
      LPITEMIDLIST	pidl=NULL; 
      SHGetSpecialFolderLocation(NULL,   CSIDL_PERSONAL,   &pidl); 
      if   (pidl&&SHGetPathFromIDList(pidl,szDocument)) 
      { 
         GetShortPathName(szDocument,m_lpszDefaultDir,_MAX_PATH); 
      }
      CString strDocPath = szDocument;
      return strDocPath;
   }
   //����ļ��Ƿ����
   inline BOOL IsFileExist(CString &strFilePathName)
   {
      //00 ֻ�ж��Ƿ����
      //02 ֻ�ж��Ƿ���дȨ��
      //04 ֻ�ж��Ƿ��ж�Ȩ��
      //06 �ж��Ƿ��ж�������дȨ��
      //�ļ�����
      if(_waccess(strFilePathName.GetBuffer(), 0) == 0)
      {
         strFilePathName.ReleaseBuffer();
         return TRUE;
      }
      strFilePathName.ReleaseBuffer();
      return FALSE;
   }
   //����ļ��Ƿ���ڲ��ҿ��Զ�
   inline BOOL IsFileExistCanRead(CString &strFilePathName)
   {
      //00 ֻ�ж��Ƿ����
      //02 ֻ�ж��Ƿ���дȨ��
      //04 ֻ�ж��Ƿ��ж�Ȩ��
      //06 �ж��Ƿ��ж�������дȨ��
      //�ļ�����
      if(_waccess(strFilePathName.GetBuffer(), 04) == 0)
      {
         strFilePathName.ReleaseBuffer();
         return TRUE;
      }
      strFilePathName.ReleaseBuffer();
      return FALSE;
   }
    //����ļ��Ƿ���ڲ��ҿ��Զ�
   inline BOOL IsFileExistCanReadWrite(CString &strFilePathName)
   {
      //00 ֻ�ж��Ƿ����
      //02 ֻ�ж��Ƿ���дȨ��
      //04 ֻ�ж��Ƿ��ж�Ȩ��
      //06 �ж��Ƿ��ж�������дȨ��
      //�ļ�����
      if(_waccess(strFilePathName.GetBuffer(), 06) == 0)
      {
         strFilePathName.ReleaseBuffer();
         return TRUE;
      }
      strFilePathName.ReleaseBuffer();
      return FALSE;
   }
   //��������
   //�ú����������Ǽ��ָ��Ŀ¼�Ƿ���ڣ�����������򴴽�����Dirpath����ʾ������Ŀ¼��
   //����
   //Ҫ����Ŀ¼���������·�������ļ��������� '\' ��β��
   //����ֵ
   //���Ŀ¼���ڣ�����TRUE����������ڵ�ȫ��·�������ɹ�������TRUE��
   //����������Ҵ���ʧ�ܣ�����FALSE��
   inline BOOL WINAPI MakeSureDirectoryPathExists(LPCTSTR pszDirPath)
   {
      LPTSTR p, pszDirCopy;
      DWORD dwAttributes;
      // Make a copy of the string for editing.
      __try
      {
         pszDirCopy = (LPTSTR)RnString::_tCharAlloc(lstrlen(pszDirPath) + 1);
         if(pszDirCopy == NULL)
            return FALSE;
         lstrcpy(pszDirCopy, pszDirPath);
         p = pszDirCopy;
         // If the second character in the path is "\", then this is a UNC
         // path, and we should skip forward until we reach the 2nd \ in the path.
         if((*p == TEXT('\\')) && (*(p+1) == TEXT('\\')))
         {
            p++; // Skip over the first \ in the name.
            p++; // Skip over the second \ in the name.
            // Skip until we hit the first "\" (\\Server\).
            while(*p && *p != TEXT('\\'))
            {
               p = CharNext(p);
            }
            // Advance over it.
            if(*p)
            {
               p++;
            }
            // Skip until we hit the second "\" (\\Server\Share\).
            while(*p && *p != TEXT('\\'))
            {
               p = CharNext(p);
            }
            // Advance over it also.
            if(*p)
            {
               p++;
            }
         }
         else if(*(p+1) == TEXT(':')) // Not a UNC. See if it's <drive>:
         {
            p++;
            p++;
            // If it exists, skip over the root specifier
            if(*p && (*p == TEXT('\\')))
            {
               p++;
            }
         }
         while(*p)
         {
            if(*p == TEXT('\\'))
            {
               *p = TEXT('\0');
               dwAttributes = GetFileAttributes(pszDirCopy);
               // Nothing exists with this name. Try to make the directory name and error if unable to.
               if(dwAttributes == 0xffffffff)
               {
                  if(!CreateDirectory(pszDirCopy, NULL))
                  {
                     if(GetLastError() != ERROR_ALREADY_EXISTS)
                     {
                        RnString::_tCharFree(pszDirCopy);
                        return FALSE;
                     }
                  }
               }
               else
               {
                  if((dwAttributes & FILE_ATTRIBUTE_DIRECTORY) != FILE_ATTRIBUTE_DIRECTORY)
                  {
                     // Something exists with this name, but it's not a directory... Error
                     RnString::_tCharFree(pszDirCopy);
                     return FALSE;
                  }
               }
               *p = TEXT('\\');
            }
            p = CharNext(p);
         }
      }
      __except(EXCEPTION_EXECUTE_HANDLER)
      {
         // SetLastError(GetExceptionCode());
         RnString::_tCharFree(pszDirCopy);
         return FALSE;
      }
      RnString::_tCharFree(pszDirCopy);
      return TRUE;
   }
   
   //ɾ��һ���ļ����µ����������Լ��Լ�����
   inline void MyDeleteDirectory(CString directory_path)   
   {     
	   int nSlashPos = directory_path.ReverseFind('\\');
	   int nLen = directory_path.GetLength() - 1;
	   CString pathTmp = directory_path;
	   if (nSlashPos == nLen)
	   {
		   pathTmp = directory_path.Left(nLen);
	   }
	   CFileFind finder;  
	   CString path;  
	   path.Format(L"%s\\*.*",pathTmp);
	   BOOL bWorking = finder.FindFile(path);  
	   while(bWorking){  
		   bWorking = finder.FindNextFile();  
		   if(finder.IsDirectory() && !finder.IsDots()){//�����ļ���  
			   MyDeleteDirectory(finder.GetFilePath()); //�ݹ�ɾ���ļ���  
			   RemoveDirectory(finder.GetFilePath());  
		   }  
		   else{//�����ļ�  
			   DeleteFile(finder.GetFilePath());  
		   }  
	   }  
      finder.Close();
	   RemoveDirectory(pathTmp);      
   }//end of func


   //��ȡĳ���̵ľ��		by WangZY 2015/08/17
   //strPath: �̷� �磺 "H��\\"
   inline BOOL GetUDiskName(__in CString strPath,
							__out CString &strUDiskName)
   {
	   DWORD dwVolumeSerialNumber;
	   DWORD dwMaximumComponentLength;
	   DWORD dwFileSystemFlags;
	   TCHAR szFileSystemNameBuffer[MAX_PATH];      // #define BUF 1024
	   TCHAR szDirveName[MAX_PATH];
	   BOOL bRet = GetVolumeInformation(strPath,
		   szDirveName,                        
		   MAX_PATH,
		   &dwVolumeSerialNumber,
		   &dwMaximumComponentLength,
		   &dwFileSystemFlags,
		   szFileSystemNameBuffer,
		   MAX_PATH);
	   strUDiskName = szDirveName;

	   return bRet;
   }

	inline LPCTSTR GetFilterString(CString& sFilter)
	{
		LPTSTR psz = sFilter.GetBuffer(0);
		LPCTSTR pszRet = psz;
		while ( '\0' != *psz )
		{
			if ( '|' == *psz )
			*psz++ = '\0';
			else
			psz = CharNext ( psz );
		}
	  return pszRet;
	}

   //����U�����������		 	by WangZY 2015/10/23	
#include <Winioctl.h>
#define MEDIA_INFO_SIZE    sizeof(GET_MEDIA_TYPES)+15*sizeof(DEVICE_MEDIA_INFO)

   inline BOOL GetDriveGeometry(const TCHAR * filename, DISK_GEOMETRY * pdg)
   {
	   HANDLE hDevice;         // �豸���
	   BOOL bResult;           // DeviceIoControl�ķ��ؽ��
	   GET_MEDIA_TYPES *pmt;   // �ڲ��õ����������
	   DWORD dwOutBytes;       // ������ݳ���

	   // ���豸
	   hDevice = ::CreateFile(filename,           // �ļ���
		   GENERIC_READ,                          // ������Ҫ����
		   FILE_SHARE_READ | FILE_SHARE_WRITE,    // ����ʽ
		   NULL,                                  // Ĭ�ϵİ�ȫ������
		   OPEN_EXISTING,                         // ������ʽ
		   0,                                     // ���������ļ�����
		   NULL);                                 // �������ģ���ļ�

	   if (hDevice == INVALID_HANDLE_VALUE)
	   {
		   // �豸�޷���...
		   return FALSE;
	   }

	   // ��IOCTL_DISK_GET_DRIVE_GEOMETRYȡ���̲���
	   bResult = ::DeviceIoControl(hDevice,       // �豸���
		   IOCTL_DISK_GET_DRIVE_GEOMETRY,         // ȡ���̲���
		   NULL, 0,                               // ����Ҫ��������
		   pdg, sizeof(DISK_GEOMETRY),            // ������ݻ�����
		   &dwOutBytes,                           // ������ݳ���
		   (LPOVERLAPPED)NULL);                   // ��ͬ��I/O

	   // ���ʧ�ܣ�����IOCTL_STORAGE_GET_MEDIA_TYPES_EXȡ�������Ͳ���
	   if (!bResult)
	   {
		   pmt = (GET_MEDIA_TYPES *)new BYTE[MEDIA_INFO_SIZE];

		   bResult = ::DeviceIoControl(hDevice,    // �豸���
			   IOCTL_STORAGE_GET_MEDIA_TYPES_EX,   // ȡ�������Ͳ���
			   NULL, 0,                            // ����Ҫ��������
			   pmt, MEDIA_INFO_SIZE,               // ������ݻ�����
			   &dwOutBytes,                        // ������ݳ���
			   (LPOVERLAPPED)NULL);                // ��ͬ��I/O

		   if (bResult)
		   {
			   // ע�⵽�ṹDEVICE_MEDIA_INFO���ڽṹDISK_GEOMETRY�Ļ����������
			   // Ϊ�򻯳�����memcpy�������¶�����ֵ��䣺
			   // pdg->MediaType = (MEDIA_TYPE)pmt->MediaInfo[0].DeviceSpecific.DiskInfo.MediaType;
			   // pdg->Cylinders = pmt->MediaInfo[0].DeviceSpecific.DiskInfo.Cylinders;
			   // pdg->TracksPerCylinder = pmt->MediaInfo[0].DeviceSpecific.DiskInfo.TracksPerCylinder;
			   // ... ...
			   ::memcpy(pdg, pmt->MediaInfo, sizeof(DISK_GEOMETRY));
		   }

		   delete pmt;
	   }
	   // �ر��豸���
	   ::CloseHandle(hDevice);

	   return (bResult);
   }
   //�ж��Ƿ���U��	by WangZY 2015/10/23
   inline BOOL IsU_Disk(CString strDrivePath)
   {
	   DISK_GEOMETRY dg;
	   // 	TCHAR szPath[100] = _T("////.//");
	   // 	::_tcscat(szPath,sDrivePath);
	   // 	int nSize = ::_tcslen(szPath);
	   // 	szPath[nSize-1] = '/0';
	   CString strName;

	   strName = _T("//./");
	   strName += strDrivePath.Left(2);

	   BOOL bRetVal = GetDriveGeometry(strName.GetBuffer(0),&dg);
	   if(dg.MediaType == RemovableMedia)
	   {
		   //�����U��
		   return TRUE;
	   }

	   return FALSE;
   }

	//�ж�Ŀ¼�Ƿ����		by WangZY 2016/05/31
	inline BOOL FolderExist(CString strPath) 
	{      
		WIN32_FIND_DATA wfd;     
		BOOL rValue = FALSE;      
		HANDLE hFind = FindFirstFile(strPath, &wfd);     
		if ((hFind!=INVALID_HANDLE_VALUE) 
			&&(wfd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY))     
		{          
			rValue = TRUE;     
		}      
		FindClose(hFind);     
		
		return rValue; 
	}

	inline int GetTempPathNew(CString &strTmpPath)
	{
		//��ȡ��ʱĿ¼		by WangZY 2016/05/31
		DWORD dwLen = 0;
		TCHAR szBuf[MAX_PATH] = {0};
		dwLen = GetTempPath(MAX_PATH-1, szBuf);

		if (dwLen > MAX_PATH -1)
		{
			TCHAR *pszBuf = new TCHAR[dwLen+1];
			memset(pszBuf,0,sizeof(TCHAR)*(dwLen+1));
			dwLen = GetTempPath(dwLen, pszBuf);
			strTmpPath = pszBuf;

			delete []pszBuf;
			pszBuf = NULL;

			return -1;
		}
		else if (dwLen <= 0)
		{
			strTmpPath = _T("");
			int nError = GetLastError();
			
			return nError;
		}
		else
		{
			strTmpPath = szBuf;

			return 0;
		}
	}

#pragma region ini�����ļ���дUNICODE�汾
   //remove all blank space
   static CString &trimString(CString &str)
   {
      str.Trim(_T(" "));
      return str;
   }

   static bool readLineW(CFile &file, CStringW &str)
   {
      WCHAR wchar;   
      UINT ret = 0;
      std::wstring buf;
      buf.reserve(40);
      while(1)
      {
         ret = file.Read(&wchar, sizeof(wchar));
         if(ret > 0)
         {
            if(ret != sizeof(wchar))
            {
               return false;
            }

            if(wchar == L'\r')
            {
               ret = file.Read(&wchar, sizeof(wchar));
               if(ret != sizeof(wchar))
               {
                  return false;
               }
               if(wchar != L'\n')
               {
                  return false;
               }
               str = buf.c_str();
               return true;
            }
            else if(wchar == L'\n')
            {
               str = buf.c_str();
               return true;
            }
            else
            {
               buf.push_back(wchar);
            }
         }
         else //if(ret == 0)
         {
            if(buf.size() == 0)
            {
               return false;
            }
            else
            {
               str = buf.c_str();
               return true;
            }
         }
      }
   }

   class ININode
   {
   public:
      ININode(CString root, CString key, CString value)
      {
         this->root = root;
         this->key = key;
         this->value = value;
      }
      CString root;
      CString key;
      CString value;
   };

   class SubNode
   {
   public:
      void InsertElement(CString key, CString value)
      {
         sub_node.insert(pair<CString, CString>(key, value));
      }
      map<CString, CString> sub_node;
   };
   inline char* Ansi2Unicode(const char* str,int &iLength)  
   {  
      int dwUnicodeLen = MultiByteToWideChar(CP_ACP,0,str,-1,NULL,0);
      if(!dwUnicodeLen)  
      {  
         return _strdup(str);  
      }  
      size_t num = dwUnicodeLen*sizeof(wchar_t);  
      iLength = num;
      wchar_t *pwText = (wchar_t*)malloc(num);  
      memset(pwText,0,num);  
      MultiByteToWideChar(CP_ACP,0,str,-1,pwText,dwUnicodeLen);  
      return (char*)pwText;  
   }  
   class INIParser
   {
   public:
      int ReadINI(CString path)
      {
         {
            CFile file;
            if(!file.Open(path, CFile::modeReadWrite )) 
               return 0;

            CString str_line = _T("");
            CString str_root = _T("");
            vector<ININode> vec_ini;

            USHORT s = 0;
            file.Read(&s, sizeof(s));
            if(s != 0xfeff)
            {
               //��UNICODE����INI�����ļ�ת��ΪUNICODE����
               std::vector<char> byte;
               byte.resize(file.GetLength());
               file.SeekToBegin();
               file.Read(&(byte[0]),file.GetLength());
               int iNewLength = 0;
               char *pNewByte = Ansi2Unicode(&(byte[0]),iNewLength);
               file.SeekToBegin();
               USHORT head = 0xfeff;
               file.Write(&head, sizeof(head));
               file.Write(pNewByte,iNewLength);
               file.SeekToBegin();
               file.Read(&s, sizeof(s));
               free(pNewByte);
            }

            while(readLineW(file, str_line))
            {
               int left_pos = 0;
               int right_pos = 0;
               int equal_div_pos = 0;
               CString str_key = _T("");
               CString str_value = _T("");

               if((-1 != (left_pos = str_line.Find(_T("[")))) && (-1 != (right_pos = str_line.Find(_T("]")))))
               {
                  str_root = str_line.Mid(left_pos + 1, right_pos-1);
               }

               if(-1 != (equal_div_pos = str_line.Find(_T("="))))
               {
                  str_key = str_line.Mid(0, equal_div_pos);
                  str_value = str_line.Mid(equal_div_pos+1, str_line.GetLength()-1);
                  str_key = trimString(str_key);
                  str_value = trimString(str_value);
               }

               if((!str_root.IsEmpty()) && (!str_key.IsEmpty()) && (!str_value.IsEmpty()))
               {
                  ININode ini_node(str_root, str_key, str_value);
                  vec_ini.push_back(ini_node);
               }
            }

            map<CString, CString> map_tmp;
            for(vector<ININode>::iterator itr = vec_ini.begin(); itr != vec_ini.end(); ++itr)
            {
               map_tmp.insert(pair<CString, CString>(itr->root, ""));
            }

            SubNode sn;
            for(map<CString, CString>::iterator itr = map_tmp.begin(); itr != map_tmp.end(); ++itr)
            {
               sn.sub_node.clear();
               for(vector<ININode>::iterator sub_itr = vec_ini.begin(); sub_itr != vec_ini.end(); ++sub_itr)
               {
                  if(sub_itr->root == itr->first)
                  {
                     sn.InsertElement(sub_itr->key, sub_itr->value);
                  }
               }
               map_ini.insert(pair<CString, SubNode>(itr->first, sn));
            }
            return 1;
         }
      }
      CString GetValue(CString root, CString key) const
      {
         {
            map<CString, SubNode>::const_iterator itr = map_ini.find(root);
            if (itr==map_ini.end())
            {
               return _T("");
            }
            map<CString, CString>::const_iterator sub_itr = itr->second.sub_node.find(key);
            if (sub_itr==itr->second.sub_node.end())
            {
               return _T("");
            }
            if(!(sub_itr->second).IsEmpty())
               return sub_itr->second;
            return _T("");
         }
      }
      int GetThePrivateProfileInt(const CString &strGrpSectionName, const CString &strKeyName, int iDefaultValue) const
      {
         const CString &root = strGrpSectionName;
         const CString &key = strKeyName;
         map<CString, SubNode>::const_iterator itr = map_ini.find(root);
         if (itr == map_ini.end())
         {
            return iDefaultValue;
         }
         map<CString, CString>::const_iterator sub_itr = itr->second.sub_node.find(key);
         if (sub_itr == itr->second.sub_node.end())
         {
            return iDefaultValue;
         }
         if(!(sub_itr->second).IsEmpty())
         {
            int b =_ttoi(sub_itr->second);
            return b;
         }

         return iDefaultValue;
      }

      
      void GetThePrivateProfileString(const CString &strRoot, const CString &strKeyName, const CString &strDefault,
         CString *pStrReturnedString, DWORD nSize) const
      {
         if(!pStrReturnedString)
            return;

         map<CString, SubNode>::const_iterator itr = map_ini.find(strRoot);
         if (itr == map_ini.end())
         {
            *pStrReturnedString = strDefault;
            return;
         }
         map<CString, CString>::const_iterator sub_itr = itr->second.sub_node.find(strKeyName);
         if (sub_itr == itr->second.sub_node.end())
         {
            *pStrReturnedString = strDefault;
            return;
         }

         if(!(sub_itr->second).IsEmpty())
         {
            *pStrReturnedString = sub_itr->second;
            return;
         }

         *pStrReturnedString = strDefault;
         return;
      }
      vector<ININode>::size_type GetSize() const {return map_ini.size();}
      vector<ININode>::size_type SetValue(CString root, CString key, CString value)
      {
         map<CString, SubNode>::iterator itr = map_ini.find(root);
         if(map_ini.end() != itr)
            //itr->second.sub_node.insert(pair<CString, CString>(key, value));
            itr->second.sub_node[key] = value;
         else
         {
            SubNode sn;
            sn.InsertElement(key, value);
            map_ini.insert(pair<CString, SubNode>(root, sn));
         }
         return map_ini.size();
      }

      vector<ININode>::size_type SetValue(CString root, CString key, int iValue)
      {
         CString value = L"";
         value.Format(_T("%d"),iValue);
         map<CString, SubNode>::iterator itr = map_ini.find(root);
         if(map_ini.end() != itr)
            //itr->second.sub_node.insert(pair<CString, CString>(key, value));
            itr->second.sub_node[key] = value;
         else
         {
            SubNode sn;
            sn.InsertElement(key, value);
            map_ini.insert(pair<CString, SubNode>(root, sn));
         }
         return map_ini.size();
      }
      int WriteINI(CString path)
      {
         CFile file;

         if(FALSE == file.Open(path ,CFile::modeWrite | CFile::modeCreate))
            return -1;

         USHORT s = 0xfeff;
         file.Write(&s, sizeof(s));

         for(map<CString, SubNode>::iterator itr = map_ini.begin(); itr != map_ini.end(); ++itr)
         {
            CString tmp;
            tmp.Format(_T("[%s]\n"), itr->first);
            int len = tmp.GetLength();
            file.Write(tmp, len * sizeof(TCHAR));

            for(map<CString, CString>::iterator sub_itr = itr->second.sub_node.begin(); sub_itr != itr->second.sub_node.end(); ++sub_itr)
            {
               CString tmp;
               tmp.Format(_T("%s=%s\n"), sub_itr->first, sub_itr->second);
               int len = tmp.GetLength();
               file.Write(tmp, len * sizeof(TCHAR));
            }
         }

         file.Close();
         return 1;
      }
      void Clear(){map_ini.clear();}
   private:
      map<CString, SubNode> map_ini;
   };

#pragma endregion


}



