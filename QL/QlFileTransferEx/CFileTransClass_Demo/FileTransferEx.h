#pragma once
#include "stdafx.h"
#include <map>

//模式或者是文件类型等
enum {
   FTP_MODE_TYPE_PATTERN = 0     ,//制版文件
   FTP_MODE_TYPE_PROCESS         ,//工艺文件
   FTP_MODE_TYPE_DESIGN          ,//设计文件
   FTP_MODE_TYPE_ONLINE          ,//上机文件
   FTP_MODE_TYPE_OTHER           ,//其他文件
   FTP_MODE_TYPE_SIZE            ,//尺寸文件
   FTP_MODE_TYPE_PIC             ,//保存图片文件的模式    （指订单图 或者是款式的款式图 本质一样）
   FTP_MODE_TYPE_PIC_STYLE       ,//手机图片的文件夹 
   FTP_MODE_TYPE_CHATFILE        ,//聊天文件的上传
   FTP_MODE_TYPE_PIC_PRODETAIL   ,//生产流程图            （指平铺图）
   FTP_MODE_TYPE_PIC_MODEL       ,//模特图                （PDM 的模特图片 ） 
};

//库标识
enum{
	FTP_LIB_TYPE_BMP = 0,
	FTP_LIB_TYPE_STYLE,
	FTP_LIB_TYPE_PROCESS,
	FTP_LIB_TYPE_DENSITY,//密度库
	FTP_LIB_TYPE_COMPONENT,//部件库
	FTP_LIB_TYPE_PATTERNCONFIG,//制版配置库
	FTP_LIB_TYPE_MODFILE,//制版小图库
};

enum{
	FTP_WHOLE_TYPE_FILE = 0,
	FTP_WHOLE_TYPE_LIB,
	FTP_WHOLE_TYPE_EXCHANGE,//交互文件的wholetyoe
	FTP_WHOLE_TYPE_COMMUNICATION,//群聊
	FTP_WHOLE_TYPE_WEB,//web库
};


class CFileTransferEx
{
public:
	CFileTransferEx(CString strWorkPath,HWND hProcessHwnd = NULL,S_FileTrans_LoginType nLoginType = En_Login_User);
	~CFileTransferEx();
public:
	//上传文件的文件全路径列表
	CStringList m_UploadList;
	//删除文件的文件名称列表
	CStringList m_DelList;

	std::map<CString,CString> m_DownMsg;

	//复制文件夹的列表 pair中分别是org（源文件名） dst（目标文件名）
	std::vector<pair<CString,CString>> m_vecCopyList;
public:

	void Init(CString strOrderNo,int nFileType,int nWholeType = 0);

	int Upload(int nFlag = UNDESIGN_FLAG,BOOL bDelSrc = FALSE);

    /*******************************************************************
	 * @brief : 下载函数的接口
	 * @author : wzl
	 * @date : 2016/12/20 17:10
	 * @param : 
	 * @example : 
	 * @return : 
	 *******************************************************************/
	int DownLoad(int nFlag = UNDESIGN_FLAG);

	  /*******************************************************************
   * @brief : 基本同DownLoad，可下载指定版本下文件
   * @author : dc
   * @date : 2018/9/13 10:02
   * @param : 
   * @example : 
   * @return : 
   *******************************************************************/
   int DownLoadbyVersion(int nVersion, int nFlag = UNDESIGN_FLAG);

	/*******************************************************************
	* @brief : 上传函数，基本同Upload，可以指定上传到哪个备份文件夹
	* @author : dc
	* @date : 2018/9/13 8:52
	* @param : nVersion: 版本号，-1时同Upload, bDelSrc: 是否删除源文件的标识
	* @example : 
	* @return : (0-9)
	0-上传文件列表是空的
	*******************************************************************/

	int UploadToVersion(int nVersion, int nFlag = UNDESIGN_FLAG,BOOL bDelSrc = FALSE);

	/*******************************************************************
	 * @brief : 下载文件夹接口
	 * @author : wzl
	 * @date : 2017/1/18 11:39
	 * @param : 
	 * @example : 
	 * @return : 
	 *******************************************************************/
	int DownLoadDir(CString strLocalDir,int nFlag = UNDESIGN_FLAG);
	int DownLoadDir(CString strLocalDir,CString strOrderNo,int nFlag = UNDESIGN_FLAG);
   int DownLoadDirByVersion(int nVersion, CString strLocalDir, const CString &strOrderNo, int nFlag = UNDESIGN_FLAG);

   /*******************************************************************
	 * @brief : 下载文件夹时每个文件都给句柄发送消息
	 * @author : wzl
	 * @date : 2017/5/15
	 * @param : 
	 * @example : 
	 * @return : 
	 *******************************************************************/
	int DownLoadDirMsg(CString strLocalDir,int nFlag = UNDESIGN_FLAG,DWORD dwStyle = FS_DEFAULT);
	int DownLoadDirMsg(CString strLocalDir,CString strOrderNo,int nFlag = UNDESIGN_FLAG,DWORD dwStyle = FS_DEFAULT);

   /*******************************************************************
	 * @brief : 根据传入的错误数值，返回对应的错误信息
	 * @author : wzl
	 * @date : 2016/12/20 13:45
	 * @param : nerrno 要查询的错误数值
	 * @example : GetErrorMsg(0);->返回上传链未赋值;
	 * @return : 返回获取到的错误信息
	 *******************************************************************/
	CString GetErrorMsg(int nerrno);

   CString GetVersion();

   BOOL IsHttpMode();

   	/*******************************************************************
	 * @brief : 检查数据库中是否已经存在该订单号信息
	 * @author : wzl
	 * @date : 2017/3/1 11:31
	 * @param : 
	 * @example : 
	 * @return : 0不存在  1存在
	 *******************************************************************/
	int CheckOrderExit(CString strOrderNo);

	/*******************************************************************
	 * @brief : 检测配置文件中的信息能否登录数据库
	 * @author : wzl
	 * @date : 2017/2/10 10:31
	 * @param : 
	 * @example : 
	 * @return : 
	 *******************************************************************/
	BOOL CheckDBLogin();

	/*******************************************************************
	 * @brief : 弹出登录窗口 返回登录的结果
	 * @author : wzl
	 * @date : 2017/3/31
	 * @param : 
	 * @example : 
	 * @return : TRUE 登录成功  FALSE 登录失败
	 *******************************************************************/
	BOOL PopLogin();

	//获取单号对应的模板单号  
	CString GetSampleOrder(CString strOrderNo);
	//设置单号对应的模板单号
	int SetOrderSampleOrder(CString strOrderNo,CString strSampleNo);

	void SetHwnd(HWND hProcessHwnd);
	/*******************************************************************
	 * @brief : 设置订单号信息
	 * @author : wzl
	 * @date : 2016/12/20 13:50
	 * @param : strOrderNo 上传文件相关的订单号
	 * @example : 
	 * @return : 
	 *******************************************************************/
	void SetOrderInfo(CString strOrderNo);

	/*******************************************************************
	 * @brief : 设置传输文件的码型
	 * @author : wzl
	 * @date : 2017/4/25
	 * @param : 
	 * @example : 
	 * @return : 
	 *******************************************************************/
	void SetSize(CString strSize);

	/*******************************************************************
	 * @brief : 通过扩展名下载相应的文件 具体流程：
				1.获取相关文件夹下所有的文件信息
				2.扩展名比对
				3.加入下载队列下载
	 * @author : wzl
	 * @date : 2017/3/30
	 * @param : 
	 * @example : DownLoadByExt(_T(".txt"),0);
	 * @return : 
	 *******************************************************************/
	int DownLoadByExt( CString strLocalDir,CString strOrderNo,CString strExtension,int nFlag = UNDESIGN_FLAG,BOOL bDir = FALSE,DWORD dwStyle = FS_DEFAULT);

	
	int Del(int nFlag = UNDESIGN_FLAG);

	/*******************************************************************
	 * @brief : 根据传入的订单号和文件类型返回对应文件夹下的文件列表
	 * @author : wzl
	 * @date : 2016/12/21 9:31
	 * @param : strOrderNo  订单号  nType  文件类型0-制版 1-工艺
	 * @example : 
	 * @return : 
	 *******************************************************************/
	int GetList(int nFlag = UNDESIGN_FLAG);
   int GetListEx(int nFlag = UNDESIGN_FLAG,DWORD dwStyle = FS_DEFAULT);

   /*******************************************************************
	 * @brief : 根据传入版本号和当前订单获取文件列表
	 * @author : dc
	 * @date : 2018/9/12 16:05
	 * @param : nVersion 版本号， -1时同GetList
	 * @example : 
	 * @return : 
	 *******************************************************************/
   int GetListByVersion(int nVersion, int nFlag = UNDESIGN_FLAG);

	/*******************************************************************
	 * @brief : 删除文件夹
	 * @author : wzl
	 * @date : 2017/5/12
	 * @param : 
	 * @example : 
	 * @return : 
	 *******************************************************************/
	int DelDir(int nFlag = UNDESIGN_FLAG);
	int DelDir(CString strOrderNo,int nFlag = UNDESIGN_FLAG);

	//判断文件是否存在
	int IsFileExist(CString strFileName);


   /*******************************************************************
   * @brief : 备份当前订单的文件，如果是工艺，则是移动文件，如果是制版，则复制文件
   * @author : dc
   * @date : 2018/9/5 13:54
   * @param : bMove 表示是移动还是复制操作  内部不区分 外部自己区分
   * @example : 
   * @return : 
   *******************************************************************/
   int BackupFile(const CString &strVersionName, CString strOrderNo, int nFlag = UNDESIGN_FLAG,BOOL bMove = FALSE);

   /*******************************************************************
   * @brief : 复制指定版本到新当前版本（会先移动当前文件到备份文件夹）
   * @author : dc
   * @date : 2018/10/18 16:02
   * @param : 
   * @example : 
   * @return : 
   *******************************************************************/
   int CopyVersionToNewCreatedOne(const CString &strNewVersionName, const CString &strOldVersionName, CString strOrderNo, int nFlag = UNDESIGN_FLAG);

   /*******************************************************************
   * @brief : 远程复制文件或文件夹（/结尾的视作文件夹）
   * @author : dc
   * @date : 2018/9/5 13:54
   * @param : Org为复制源 Dst为复制目标
   * @example : 
   * @return : 
   *******************************************************************/
   int RemoteCopyFile(const CString &sOrgOrder, int nOrgVersion, int nOrgFileType, const CString &sOrgSize,  
      const CString &sDstOrder, int nDstVersion, int nDstFileType,  const CString &sDstSize, 
      int nFlag = UNDESIGN_FLAG);

   /*******************************************************************
   * @brief : 远程复制文件或文件夹（/结尾的视作文件夹）
   * @author : dc
   * @date : 2018/9/5 13:54
   * @param : Org为复制源 Dst为复制目标 增加库类型
   * @example : 
   * @return : 
   *******************************************************************/
   int RemoteCopyFile(const CString &sOrgOrder, int nOrgVersion, int nOrgFileType, const CString &sOrgSize,int nOrgWholeType ,  
      const CString &sDstOrder, int nDstVersion, int nDstFileType,  const CString &sDstSize ,int nDstWholeType  , 
      int nFlag = UNDESIGN_FLAG);

   CString GetStr(int nWholeType, int nFileType);

private:
	FILETRANS * m_pFileTrans;
   //一些需要缓存的信息 
	CString m_strOrderNo;//单号
   //尺码
   CString m_strSize;
};

