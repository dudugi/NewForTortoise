#pragma once
#include "DataMid.h"
class CADOConn;

/*************************************************
// <�ļ�>: DBDesignDataLib.h
// <˵��>: ������DB��
// <����>: huangym(ͷ�ļ�ע��)
// <����>: 2019/02/21 16:09:54
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/

#define DBDesignDataLib_nLength                        _T("��")        // ��
#define DBDesignDataLib_nBust                          _T("��Χ ")       // ��Χ 
#define DBDesignDataLib_nShoulderWidth                 _T("���")        // ���
#define DBDesignDataLib_nCollarWidth                   _T("���")        // ���
#define DBDesignDataLib_nCollarHeight                  _T("���")        // ���
#define DBDesignDataLib_nFront                         _T("ǰ�ؿ�")       // ǰ�ؿ�
#define DBDesignDataLib_nBehind                        _T("�󱳿�")       // �󱳿�
#define DBDesignDataLib_nMidWidth                      _T("������")       // ������
#define DBDesignDataLib_nMidHeight                     _T("������")       // ������
#define DBDesignDataLib_nBellowWidth                   _T("�°ڿ�")       // �°ڿ�
#define DBDesignDataLib_nBellowHeight                  _T("�°ڸ�")       // �°ڸ�
#define DBDesignDataLib_nShoulderSlanting              _T("��б")        // ��б
#define DBDesignDataLib_nShoulder                      _T("�Ҽ�")        // �Ҽ�
#define DBDesignDataLib_nShoulderHeight                _T("�Ҽ������")     // �Ҽ������
#define DBDesignDataLib_nShoudlerHor                   _T("�Ҽ�ƽ��")      // �Ҽ�ƽ��
#define DBDesignDataLib_nFrontDeep                     _T("ǰ����")       // ǰ����
#define DBDesignDataLib_nBehindDeep                    _T("������")       // ������
#define DBDesignDataLib_nSleeveLength                  _T("�䳤")        // �䳤
#define DBDesignDataLib_nSleeveWidth                   _T("���")        // ���
#define DBDesignDataLib_cTomid                         _T("������")       // ������
#define DBDesignDataLib_cToTop                         _T("���ඥ")       // ���ඥ
#define DBDesignDataLib_cWidth1                        _T("����1")       // ����1
#define DBDesignDataLib_cWidth2                        _T("����2")       // ����2
#define DBDesignDataLib_cHeight1                       _T("����1")       // ����1
#define DBDesignDataLib_cHeight2                       _T("����2")       // ����2
#define DBDesignDataLib_cTotalHeight                   _T("�ܴ���")       // �ܴ���
#define DBDesignDataLib_cTotalWidth                    _T("�ܴ���")       // �ܴ���

class CDBDesignDataLib :
   public CDataMid
{
   DECLARE_SERIAL(CDBDesignDataLib)                                       // ���л������л�����Ҫ��ӵ�����
public:
   CDBDesignDataLib();
   ~CDBDesignDataLib();;
   void ResetData();                                                      // ��������
   BOOL UpdateDBInfo(CADOConn *pADOConn);                                // ��������
   BOOL GetAllDBInfo(CADOConn *pADOConn);		                             // ��ȡ����������Ϣ
   void Copy(CDBDesignDataLib *pData);                                    // ��������


   CString GetInsertSQL();                                                // ��ȡ�����SQL���
   static CDBDesignDataLib * Instance();                                  // ��ȡ��ָ�룩ʵ��
   BOOL UpdateAllDBInfoByID(CADOConn * pADOConn);                         // �������ݵ����ݿ�
   BOOL InsertAllDBInfoByID(CADOConn * pADOConn);                         // �������ݵ����ݿ�
private:
   static std::shared_ptr<CDBDesignDataLib> sm_inst;

public:                                
   __int64	m_nID;                     // ����ID
   CString  m_strName;                 // ����
   CString  m_strSavedUserID;          // �û�ID
   CString  m_strSaveTime;             // ����ʱ��
   CString  m_strData;                 // ��������
   CString  m_strLibType;              // ������ ��Ƭ ������ ��״
   CString  m_strPosition;             // ��λ
   bool     m_bSymmetricByHor;         // ˮƽ
   bool     m_bSymmetricByPer;         // ��ֱ
   bool     m_bUseExpre;               // Ӧ�ù�ʽ
   bool     m_bUseLine;                // Ӧ�ø�����
   bool     m_bMark;                   // �Ǻ�����
   bool     m_bMatchPiece;             // ������Ƭ
   int      m_nLength;                 // ��
   int      m_nBust;                   // ��Χ 
   int      m_nShoulderWidth;          // ���
   int      m_nCollarWidth;            // ���
   int      m_nCollarHeight;           // ���
   int      m_nFront;                  // ǰ�ؿ�
   int      m_nBehind;                 // �󱳿�
   int      m_nMidWidth;               // ������
   int      m_nMidHeight;              // ������
   int      m_nBellowWidth;            // �°ڿ�
   int      m_nBellowHeight;           // �°ڸ�
   int      m_nShoulderSlanting;       // ��б
   int      m_nShoulder;               // �Ҽ�
   int      m_nShoulderHeight;         // �Ҽ������
   int      m_nShoudlerHor;            // �Ҽ�ƽ��
   int      m_nFrontDeep;              // ǰ����
   int      m_nBehindDeep;             // ������
   int      m_nSleeveLength;           // �䳤
   int      m_nSleeveWidth;            // ���
   CString  m_strTomid;                // ������
   CString  m_strToTop;                // ���ඥ
   CString  m_strWidth1;               // ����1
   CString  m_strWidth2;               // ����2
   CString  m_strHeight1;              // ����1
   CString  m_strHeight2;              // ����2
   CString  m_strTotalHeight;          // �ܴ���
   CString  m_strTotalWidth;           // �ܴ���
};


class CDBDesignDataLibList : public CDataListMid
{
   DECLARE_SERIAL(CDBDesignDataLibList)
public:
   CDBDesignDataLibList();
   ~CDBDesignDataLibList();
   CDBDesignDataLib*  GetItem(int nIndex);
   void    AddItem(CDBDesignDataLib* pItem);
   void    DeleteItem(int nIndex);
   BOOL    DeleteUserByUserID(CADOConn * pADOConn, vector<CString> vecUserID);

   static CDBDesignDataLibList * Instance();		                          //��ȡ��ָ�룩ʵ��
                                                                          //���ɱ������
   MAP_GridCtrl_AllData CreateGridData(const CString & strUserDuty = _T(""));

private:
   static std::shared_ptr<CDBDesignDataLibList> sm_inst;
};
