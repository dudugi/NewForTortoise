/*************************************************
// <�ļ�>: DBCloudModuleInfo_V_Data.h
// <˵��>: ��ģ����Ϣ��ͼDB��
// <����>: WangZY
// <����>: 2019/06/04 11:09:55
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 

#pragma once
#include "datamid.h"
class CDBCloudModuleInfo_V_Data :
   public CDataMid
{
   DECLARE_SERIAL( CDBCloudModuleInfo_V_Data)//���л������л�����Ҫ��ӵ�����
public:
   CDBCloudModuleInfo_V_Data(void);
   ~CDBCloudModuleInfo_V_Data(void);

public:
   int      m_nID;                        //ģ���ļ�ID
   CString  m_strOldFileName;             //ģ���ļ���
   CString  m_strFileSavePath;            //ģ���ļ�·��
   int      m_nFileType;                  //ģ���ļ�����:(Ŀǰ�Ǽ�¼ģ���Ƿ���ѣ�0Ϊ���ܣ�1Ϊ��ѣ�
   int      m_nUploadSuccess;             //ģ���ļ��Ƿ��ϴ����
   int      m_nState;                     //ģ���ļ�״̬
   CString  m_strDescription;             //ģ���ļ�����
   CString  m_strVerifyComment;           //ģ���ļ����������
   CString  m_strCheckCode;               //ģ���ļ�У����(MD5ֵ)
   CString  m_strModType;                 //ģ������(����)
   CString  m_strProvider;                //ģ���ļ��Ĺ�Ӧ��
   CString  m_strTelPhone;                //ģ���ļ���ϵ�绰
   int      m_nDownLoadNum;               //ģ���ļ����ش���
   CString  m_strUserID;                  //�ϴ���ID
   CString  m_strUserName;                //�ϴ�������
   CString  m_strUserPower;               //�ϴ���Ȩ��
   CString  m_strRegeditTime;             //�ϴ���ע��ʱ��
   int      m_nUserState;                 //�ϴ���״̬
   CString  m_strWechat;                  //�ϴ���΢��
   CString  m_strQQ;                      //�ϴ���QQ
   CString  m_strRemark;                  //�ϴ��߱�ע
   CString  m_strSignature;               //�ϴ����޸�ǩ��
   CString  m_strPhoneNum;                //�ϴ��ߵ绰����



public:
   void ResetData();
   void Copy(CDBCloudModuleInfo_V_Data *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);				//��ȡ����������Ϣ

   //��ȡģ�������˵�SQL��䣬����Ĭ��ֵΪ-1������˱�ʶ���ɣ����򰴴���Ĳ�������; 	by WangZY 2019/06/04
   CString GetUpdateCheckModuleInfoSQL(int nCheck=-1); 

   //��ȡģ�����ɾ����־��SQL��䣬����Ĭ��ֵΪ-1�����ϴ��ı�ʶ���ɣ����򰴴���Ĳ�������;
   CString GetUpdateModuleInfoDeleteFlagSQL(int nDeleteFlag =-1); 

#ifdef USING_GRIDCTRL_MARK
   //����ת��Ϊmap�б�����   	by WangZY 2019/06/04
   static BOOL ConvertDataToMapData(__out MAP_GridCtrl_RowData &mapData, __in CDBCloudModuleInfo_V_Data *pData);
#endif


};


class CDBCloudModuleInfo_V_List :public CDataListMid
{
   DECLARE_SERIAL( CDBCloudModuleInfo_V_List)//���л������л�����Ҫ��ӵ�����
public:
   CDBCloudModuleInfo_V_List(void);
   ~CDBCloudModuleInfo_V_List(void);
public:
   void Copy(CDBCloudModuleInfo_V_List *pList);
   CDBCloudModuleInfo_V_Data*  GetItem(int nIndex);
   CDBCloudModuleInfo_V_Data*  GetItemByID(const CString & strID);
   CDBCloudModuleInfo_V_Data*  GetItemByID(const int & nID);
   int  GetIndexByID(const int & nID);
   int  GetIndexByID(const CString & strID);
   void AddItem(CDBCloudModuleInfo_V_Data *pItem);
   void DeleteItemByIndex(int nIndex);
   void DeleteItemByID(CString strID);
   void DeleteItemByID(int nID);

   //�����ݿ��ȡ��ģ����Ϣ  	by WangZY 2019/06/04
   BOOL GetCloudModuleInfo(CADOConn *pADOConn, const CString &strFilter);

#ifdef USING_GRIDCTRL_MARK
   //List�б�ת��ΪMap�б�     	by WangZY 2019/06/04
   static BOOL ConvertListToGridMap(__out MAP_GridCtrl_AllData &mapData,__in CDBCloudModuleInfo_V_List &listData);
#endif


};

