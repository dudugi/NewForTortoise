/*************************************************
// <文件>: FT_params.h
// <说明>: 传输库参数相关处理的文件
// <作者>: wangzl
// <日期>: 2019/02/27
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#pragma once
#include "FileTransData.h"
#include "tinyxml\tinyxml.h"

//使用类避免外面调用一些私有接口
class CFT_params
{
public:
   CFT_params(){};
   ~CFT_params(){};
   void InitDataParams(FileTrans_easy * pData,const CString & strWorkPath);
protected:
private:
   //从配置文件中获取相关的信息并提取到数据中 如果配置文件不存在 则从资源中提取文件到相关的文件路径下
   void InitConfigInfo(FileTrans_easy * pData,const CString & strWorkPath);
   //解析路径设置
   void ParsePathSetting_byFile(const CString & strSettingFile, map<CString,S_PathParam> & map_PathSetting);
   void ParsePathSetting(TiXmlDocument & doc, map<CString, S_PathParam> &map_PathSetting);
   //整合路径设置
   void CombinePathSetting(const map<CString,S_PathParam> & map_DefaultSetting,map<CString,S_PathParam> & map_UserSetting);

   //从配置文件中初始化参数信息
   void InitParamInfoFromConfig(FileTrans_easy * pData,const CString & strWorkPath);
   void GetSvrIniMsg( _In_ const CString & strSvrIniPath ,FileTrans_easy * pData);
   void GetFileMgnIniMsg( _In_ const CString & strFileMgnIniPath ,_Inout_ FileTrans_easy * pData);
};






