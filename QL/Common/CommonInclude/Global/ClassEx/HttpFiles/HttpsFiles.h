#pragma once
#include <afxinet.h>

class CQLHttpsFiles
{
private:
   CQLHttpsFiles();

public:
   ~CQLHttpsFiles();
   static CQLHttpsFiles* GetInstance();

   //strFileURLInServer: �������ļ���URL, strFileURLInServer: ��ŵ����ص�·��
   BOOL DownLoadFile(const CString& strFileURLInServer, const CString & strFileLocalFullPath);

    //��������ϴ�������ҳ���URL, ���ϴ��ı����ļ�·��
   BOOL UploadFile(LPCTSTR strURL,LPCTSTR strLocalFileName);

private:
   	static std::shared_ptr<CQLHttpsFiles> sm_inst;
};

//example code
//DownLoadFile(_T("http://139.196.243.169/BKPDM/%E8%AE%A2%E5%8D%95%E5%BA%93/w201807050002/%E5%9B%BE%E7%89%87%E6%96%87%E4%BB%B6/001.bmp"),
//   _T("C:\\Users\\Administrator\\Desktop\\����\\001.bmp"));
