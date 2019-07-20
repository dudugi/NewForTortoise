#pragma once

/*************************************************
// <�ļ�>: DBControlsPermission.h
// <˵��>: �û��ؼ�Ȩ��������
// <����>: wangzl
// <����>: 2019/02/21
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 

#include "DataMid.h"
class CADOConn;

class CDBControlsPermissionData  : public CDataMid
{
   DECLARE_SERIAL( CDBControlsPermissionData)//���л������л�����Ҫ��ӵ�����
public:
   typedef enum EM_CONTROL_TYPE
   {
      en_Control_Normal = 1,//��ͨ�ؼ��簴ť �༭�� ��̬�ı� ��
      en_Control_Menu = 2,//�˵�
   };
public:
   INT64       m_nID          ;//����ID
   int         m_nDlgID       ;//�Ի���ID
   int         m_nDlgFlag     ;//�Ի����Զ����־
   int         m_nControlID   ;//�ؼ�ID
   int         m_nControlType ;//�ؼ�����
   CString     m_strDescription;//�ؼ�˵��

public:
   CDBControlsPermissionData();
   ~CDBControlsPermissionData();
   void ResetData();
   void Copy(CDBControlsPermissionData *pData);

   BOOL GetAllDBInfo(CADOConn *pADOConn);    //��ȡ����������Ϣ
   //BOOL UpdateAllDBInfo(CADOConn *pADOConn); //���¡���������Ϣ
   BOOL DelAllDBInfo(CADOConn *pADOConn);    //ɾ������������¼
   BOOL InsertAllDBIno(CADOConn *pADOConn);  //����������������¼

   CString GetInsertSQL() const;
};


class CDBControlsPermissionList  : public CDataListMid
{
   DECLARE_SERIAL(CDBControlsPermissionList)
public:
   CDBControlsPermissionList();
   ~CDBControlsPermissionList();
   CDBControlsPermissionData* GetItem(int nIndex);       //����������ȡItem
   void AddItem(CDBControlsPermissionData* pItem);       //���Item
   void DeleteItem(int nIndex);                          //ɾ���̶�����Item

   //��ȡ���е��û�Ȩ���б�
   void GetListFromDB(CADOConn *pADOConn);
   //�����û���Ȩ������û��Ȩ�޵��б�
   void GetListFromDB(CADOConn *pADOConn,const CString & strUserPermission);//�����ݿ��ȡ���� strUserPermission���û���Ȩ���ַ���

   //����Ի���������ͨ�ؼ���Ȩ��
   void HandleWindowNormalControlPermission(CWnd * pWnd,UINT nIDTemplete,int nDlgFlag);

   //����Ի�������˵���Ȩ��
   void HandleWindowMenuControlPermission(CMenu* pPopup,UINT nIDTemplete,int nDlgFlag);

   //�ж϶�Ӧ���Ƿ���������
   BOOL HasItemInControlPermission(UINT nIDTemplete,int nDlgFlag,UINT nControlID,CDBControlsPermissionData::EM_CONTROL_TYPE nControlType);

   //ʹ�õ�ǰ�����е����ݳ�ʼ��ϵͳ������
   BOOL InitDBControlPermission(CADOConn * pADOConn);

   static CDBControlsPermissionList * Instance();        //��ȡ��ָ�룩ʵ��

private:
   static std::shared_ptr<CDBControlsPermissionList> sm_inst;
};



