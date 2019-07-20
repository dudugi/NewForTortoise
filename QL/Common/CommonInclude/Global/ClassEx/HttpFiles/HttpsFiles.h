#pragma once
#include <afxinet.h>

class CQLHttpsFiles
{
private:
   CQLHttpsFiles();

public:
   ~CQLHttpsFiles();
   static CQLHttpsFiles* GetInstance();

   //strFileURLInServer: 待下载文件的URL, strFileURLInServer: 存放到本地的路径
   BOOL DownLoadFile(const CString& strFileURLInServer, const CString & strFileLocalFullPath);

    //负责接收上传操作的页面的URL, 待上传的本地文件路径
   BOOL UploadFile(LPCTSTR strURL,LPCTSTR strLocalFileName);

private:
   	static std::shared_ptr<CQLHttpsFiles> sm_inst;
};

//example code
//DownLoadFile(_T("http://139.196.243.169/BKPDM/%E8%AE%A2%E5%8D%95%E5%BA%93/w201807050002/%E5%9B%BE%E7%89%87%E6%96%87%E4%BB%B6/001.bmp"),
//   _T("C:\\Users\\Administrator\\Desktop\\测试\\001.bmp"));
