/*************************************************
// <�ļ�>: FT_params.h
// <˵��>: ����������ش�����ļ�
// <����>: wangzl
// <����>: 2019/02/27
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#pragma once
#include "FileTransData.h"
#include "tinyxml\tinyxml.h"

//ʹ��������������һЩ˽�нӿ�
class CFT_params
{
public:
   CFT_params(){};
   ~CFT_params(){};
   void InitDataParams(FileTrans_easy * pData,const CString & strWorkPath);
protected:
private:
   //�������ļ��л�ȡ��ص���Ϣ����ȡ�������� ��������ļ������� �����Դ����ȡ�ļ�����ص��ļ�·����
   void InitConfigInfo(FileTrans_easy * pData,const CString & strWorkPath);
   //����·������
   void ParsePathSetting_byFile(const CString & strSettingFile, map<CString,S_PathParam> & map_PathSetting);
   void ParsePathSetting(TiXmlDocument & doc, map<CString, S_PathParam> &map_PathSetting);
   //����·������
   void CombinePathSetting(const map<CString,S_PathParam> & map_DefaultSetting,map<CString,S_PathParam> & map_UserSetting);

   //�������ļ��г�ʼ��������Ϣ
   void InitParamInfoFromConfig(FileTrans_easy * pData,const CString & strWorkPath);
   void GetSvrIniMsg( _In_ const CString & strSvrIniPath ,FileTrans_easy * pData);
   void GetFileMgnIniMsg( _In_ const CString & strFileMgnIniPath ,_Inout_ FileTrans_easy * pData);
};






