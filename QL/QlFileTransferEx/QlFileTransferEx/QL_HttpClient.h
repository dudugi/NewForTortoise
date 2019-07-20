#pragma once
#include "FileTransferDef.inl"
#include "FileTrans_Handle.h"
#include "curl\curl.h"
#include "QL_HttpErrorCode.h"

//QL使用的http客户端
/*
   IP:http://192.168.2.77:8080
   与服务端对接连接接口：

   通用头
      userName:qildoc
      token:password   此处密码经过AES加密  
      randKey:         此处为加密的key
      公钥  woshijiamisuijis

   要求判断返回码  403表示用户名或者密码错误

   获取列表
      /file/get/dir?path=$$     路径要求经过URL编码

   上传
      /file/upload?cFileName=$$  POST  参数 file 文件路径   remoteFileName 云端文件名称  路径 云端文件名要求经过URL编码
   下载
      /file/download?cFileName=$$  POST 参数要求经过url编码
   删除
      /file/delete/dir POST 参数 cFileName=$$  参数要求经过url编码
   建立文件夹 因为服务器在目录不存在时会自动创建对应目录 因此目前没有提供相应接口
   移动 拷贝
      /file/command POST 
      JSON命令格式 {"command":"move/copy","params":[{"srcFile":"123","desFile":"456"}*N]}
      表单实现也可以
      要求srcFile desFile 参数都经过URL编码
*/

class QL_HttpClient
{
public:
   //************************************
   // 函数名称: QL_HttpClient
   // 访问权限: public 
   // 创建日期: 2019/01/04
   // 创 建 人: wangzl
   // 函数说明: 
   // 返 回 值: 
   // 函数参数: const CString & strIP
   // 函数参数: const CString & strUser
   // 函数参数: const CString & strPassword
   //************************************
   QL_HttpClient(const CString & strIP,const CString & strUser, const CString & strPassword);
   ~QL_HttpClient(void);

   void Http_ProcessMsg(HWND hWnd);
public:

   //************************************
   // 函数名称: Http_Delete
   // 访问权限: public 
   // 创建日期: 2019/01/04
   // 创 建 人: wangzl
   // 函数说明: 删除主机对应的文件或者文件夹
   // 返 回 值: int
   // 函数参数: const CString & strServerFileName
   //************************************
   int Http_Delete(const CString & strServerFileName);

   //************************************
   // 函数名称: Http_Getlist
   // 访问权限: public 
   // 创建日期: 2019/01/04
   // 创 建 人: wangzl
   // 函数说明: 获取远程目录下文件列表
   // 返 回 值: int 0:失败;1:成功.
   // 函数参数: const CString & strPath
   // 函数参数: FileMsg * * ppItems
   // 函数参数: int * num
   // 函数参数: DWORD dwStyle 是否忽略文件夹 FS_NODIR 忽略文件夹
   //************************************
   int Http_Getlist(const CString & strPath,FileMsg **ppItems,int *num,DWORD dwStyle);

   //************************************
   // 函数名称: Http_Download
   // 访问权限: public 
   // 创建日期: 2019/01/04
   // 创 建 人: wangzl
   // 函数说明: 下载文件到本地
   // 返 回 值: int 0 失败 ;1 成功;2 文件不存在;
   // 函数参数: const CString & strLocalPath 下载的文件路径
   // 函数参数: const CString & strServerPath 服务器路径
   //************************************
   int Http_Download(const CString &strLocalPath, const CString & strServerPath);

   //************************************
   // 函数名称: Http_DownDir
   // 访问权限: public 
   // 创建日期: 2019/01/04
   // 创 建 人: wangzl
   // 函数说明: 下载文件夹中的内容到指定路径
   // 返 回 值: int 0失败 1成功
   // 函数参数: const CString & strLocalDir 本地文件路径
   // 函数参数: const CString & strServerDirName 服务器文件路径
   // 函数参数: int & nFileNum 文件数量
   // 函数参数: int & nDirNum 文件夹数量
   // 函数参数: HWND hWnd 接受消息用的句柄  每个文件
   // 函数参数: DWORD wpMsg  消息
   // 函数参数: int nFlag 标志
   // 函数参数: BOOL bNoDir  下载子文件夹时是否建立文件夹  TRUE 不建立子文件夹将所有文件都下载到指定的目录
   // 函数参数: BOOL bZipDel 解压成功后是否删除
   // 函数参数: BOOL bUnZipFailRename 解压失败后是否重命名
   //************************************
   int Http_DownDir(const CString & strLocalDir, const CString &strServerDirName,int &nFileNum, int &nDirNum,HWND hWnd,DWORD wpMsg,int nFlag,BOOL bNoDir,BOOL bZipDel,BOOL bUnZipFailRename);

   //************************************
   // 函数名称: Http_DownByEx
   // 访问权限: public 
   // 创建日期: 2019/01/04
   // 创 建 人: wangzl
   // 函数说明: 根据后缀名下载指定文件夹的文件
   // 返 回 值: int 0失败 1成功 2目录不存在
   // 函数参数: const CString & strLocalDir 本地文件夹
   // 函数参数: const CString & strServerDirName 云端文件夹名称
   // 函数参数: const CString & strExtension 扩展名
   // 函数参数: FilePathMsg * * szFilePath 文件的信息
   // 函数参数: int & nFileNum 文件的个数
   // 函数参数: BOOL bDir 是否检查子文件夹的内容并下载  TRUE 检查
   // 函数参数: HWND hWnd 接收消息的句柄
   // 函数参数: DWORD wpMsg 接收的消息
   // 函数参数: int nFlag 标志
   // 函数参数: BOOL bNoDir 是否建立子文件夹用来存储子文件夹的文件 TRUE 时 子文件夹的所有文件都下载到当前文件夹
   // 函数参数: BOOL bZipDel 解压后是否删除文件
   // 函数参数: BOOL bUnZipFailRename 解压失败后是否重命名文件
   //************************************
   int Http_DownByEx( const CString & strLocalDir, const CString &strServerDirName, const CString & strExtension,FilePathMsg ** szFilePath,int &nFileNum,BOOL bDir,HWND hWnd,DWORD wpMsg,int nFlag,BOOL bNoDir,BOOL bZipDel,BOOL bUnZipFailRename);

   //************************************
   // 函数名称: Http_Upload
   // 访问权限: public 
   // 创建日期: 2019/01/04
   // 创 建 人: wangzl
   // 函数说明: 上传文件
   // 返 回 值: int 0失败 1成功
   // 函数参数: const CString & strLocalPath 上传的本地文件
   // 函数参数: const CString & strServerPath 上传到云端的路径
   // 函数参数: const CString & strServerFileName 上传到云端以后对应的文件名
   //************************************
   int Http_Upload(const CString & strLocalPath, const CString & strServerPath,const CString & strServerFileName);

   //************************************
   // 函数名称: Http_Move
   // 访问权限: public 
   // 创建日期: 2019/01/04
   // 创 建 人: wangzl
   // 函数说明: 移动操作
   // 返 回 值: int 0失败 1成功 
   // 函数参数: const CString & strOrgPath 需要移动的文件或者文件夹
   // 函数参数: const CString & strDstPath 需要移动到的文件路径（目前仅支持路径） 不支持文件移动修改名称
   // 示例: Http_Move(_T("订单库/123/test.txt"),_T("订单库/456"))   不支持Http_Move(_T("订单库/123/test.txt"),_T("订单库/123/456.txt")) 
   //************************************
   int Http_Move(const CString & strOrgPath, const CString & strDstPath);

   //************************************
   // 函数名称: Http_Copy
   // 访问权限: public 
   // 创建日期: 2019/01/04
   // 创 建 人: wangzl
   // 函数说明: 文件复制
   // 返 回 值: int
   // 函数参数: const CString & strOrgPath 需要复制的文件或者文件夹的路径
   // 函数参数: const CString & strDstPath 需要复制到的文件夹路径
   //************************************
   int Http_Copy(const CString & strOrgPath, const CString & strDstPath);

private:
   //内部使用的一些接口

   //************************************
   // 函数名称: IsLoginError
   // 访问权限: private 
   // 创建日期: 2019/01/04
   // 创 建 人: wangzl
   // 函数说明: 判断是不是登录失败 目前检测值为403状态码
   // 返 回 值: BOOL
   // 函数参数: CURL * cUrl
   //************************************
   BOOL IsLoginError(CURL * cUrl);

   //************************************
   // 函数名称: Http_Commond
   // 访问权限: private 
   // 创建日期: 2019/01/04
   // 创 建 人: wangzl
   // 函数说明: http move copy命令的接口  
   // 返 回 值: int 0失败 1成功
   // 函数参数: const char * szCommand
   // 函数参数: vector<pair<CString,CString>> vec_CommandParams//命令对应的参数信息 key 对应src value对应 dstPath
   //************************************
   int Http_Commond(const char * szCommand,vector<pair<CString,CString>> vec_CommandParams);

   //************************************
   // 函数名称: AppendUserInfo
   // 访问权限: private 
   // 创建日期: 2019/01/04
   // 创 建 人: wangzl
   // 函数说明: 追加用户信息到头信息中 
   // 返 回 值: curl_slist *
   // 函数参数: curl_slist * plist 可以为NULL
   //************************************
   curl_slist * AppendUserInfo(curl_slist * plist);

   //加密的
   void GetEntryString( const CString & strUnEncrypted , CString & strEncodeString, CString & strEncryptKey );
   bool Init(const std::string& key, const std::string& iv);
   std::string Encrypt(const std::string& plainText);
   std::string Decrypt(const std::string& cipherTextHex);

   //URL编码 
   CString EncodeParam(const CString & strParam);
   
private:
   CString m_strIP;//IP地址
   CString m_strUserName;//用户名
   CString m_strUserPassword;//密码

   HWND m_hProcess;//用于接收消息的句柄
};

