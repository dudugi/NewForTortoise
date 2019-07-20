#pragma once

/*************************************************
// <�ļ�>: DBSmallPic.h
// <˵��>: Сͼ��DB��
// <����>: huangym(ͷ�ļ�ע��)
// <����>: 2019/02/21 16:02:03
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/

#include "DataMid.h"
#include "Dib.h"
#include "ViewCtrl.h"
class CADOConn;

#ifndef Des_IMAGE
#define Des_IMAGE	1
#endif

class CDBSmallPic :
   public CDataMid
{
   DECLARE_SERIAL(CDBSmallPic)                         //���л������л�����Ҫ��ӵ�����
public:
   CDBSmallPic();
   ~CDBSmallPic();;
   void ResetData();                                   // ��������
   BOOL UpdateDBInfo(CADOConn * pADOConn);             // ����DB
   BOOL GetAllDBInfo(CADOConn *pADOConn);		          // ��ȡ����������Ϣ
   void Copy(CDBSmallPic *pData);                      // ��������

   
   CString GetInsertSQL();                             // ��ȡ�����SQL���
   static CDBSmallPic * Instance();                    // ��ȡ��ָ�룩ʵ��
   BOOL UpdateAllDBInfoByID(CADOConn * pADOConn);      // �������ݵ����ݿ�
   BOOL InsertAllDBInfoByID(CADOConn * pADOConn);      // ������ݵ����ݿ�
#ifdef Des_IMAGE
private:
   inline void ClearColorImage();
#endif // Des_IMAGE
private:
   static std::shared_ptr<CDBSmallPic> sm_inst;

public:
   __int64		               m_nID;              //����ID
   CString                    m_strName;          //����
   int                        m_nWidth;           //���
   int                        m_nHeight;          //�߶�
   bool                       m_bLoop;            //��Сѭ��
   bool                       m_bKeepLine;        //���湦����
   CString                    m_strContact;       //��ϵ��ʽ
   CString                    m_strType;          //Сͼ�Զ�������(����)
   CString                    m_strSavedUserID;   //�û�ID
   CString                    m_strSaveTime;      //����ʱ��
   CString                    m_strRemark;        //Сͼ˵��
#if Des_IMAGE
   Gdiplus::Image*				m_pSmallDetailPic;  //Ԥ��ͼ
#endif
};


class CDBSmallPicList : public CDataListMid
{
   DECLARE_SERIAL(CDBSmallPicList)
public:
   CDBSmallPicList();
   ~CDBSmallPicList();
   CDBSmallPic*  GetItem(int nIndex);
   void    AddItem(CDBSmallPic* pItem);
   void    DeleteItem(int nIndex);
   BOOL    DeleteUserByUserID(CADOConn * pADOConn, vector<CString> vecUserID);

   static CDBSmallPicList * Instance();		//��ȡ��ָ�룩ʵ��
   //���ɱ������
   MAP_GridCtrl_AllData CreateGridData(const CString & strUserDuty = _T(""));

private:
   static std::shared_ptr<CDBSmallPicList> sm_inst;
};
