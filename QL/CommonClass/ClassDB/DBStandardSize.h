#pragma once

/*************************************************
// <�ļ�>: DBStandardSize.h
// <˵��>: ��׼�����DB��
// <����>: huangym(ͷ�ļ�ע��)
// <����>: 2019/02/21 16:10:26
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/

#include "DataMid.h"
#include "Resource.h"
#include <afxwin.h>
#ifdef USING_GRIDCTRL_MARK
#include "CDataTableDlgDefine.h"
#endif // USING_GRIDCTRL_MARK
#include "DBSizeInfo.h"
class CADOConn;

enum Enum_ListBox
{
   ListBox_Position = 0,
   ListBox_Size
};

#define STANDARD_SIZEMODIFY_ROWNAME  _T("��λ/����")
class CDBStandardSizeModifyList;
class CDBStandardSize :
   public CDataMid
{
   DECLARE_SERIAL(CDBStandardSize)                     //���л������л�����Ҫ��ӵ�����
public:
   CDBStandardSize();
   ~CDBStandardSize();;
   static CDBStandardSize * Instance();                // ��ȡ��ָ�룩ʵ��

   void Copy(CDBStandardSize *pData);                  // ��������
   void ResetData();                                   // ��������
   void UpdateDataValue();                             // ˢ����������
   CString GetInsertSQL();                             // ��ȡ�����SQL���

   BOOL UpdateDBInfo(CADOConn * pADOConn);             // ����DB
   BOOL GetAllDBInfo(CADOConn *pADOConn);		          // ��ȡ����������Ϣ
   BOOL UpdateAllDBInfoByID(CADOConn * pADOConn);      // �������ݵ����ݿ�
   BOOL InsertAllDBInfoByID(CADOConn * pADOConn);      // ������ݵ����ݿ�
   BOOL GetDataByGrid(CADOConn * pADOConn, const MAP_GridCtrl_AllData& data);            // ���ݱ�����ݴ���������
   BOOL GetStyleNoByFangAn(CADOConn *pADOConn,CString strStyleNo);
   BOOL GetStyleNoByPingMing(CADOConn *pADOConn,CString strPM);
private:
   static std::shared_ptr<CDBStandardSize> sm_inst;

public:
   __int64		               m_nID;              //����ID
   CString                    m_strName;          //����
   CString                    m_strRemark;        //˵��
   vector<CString>            m_vecSize;          //�ߴ缯��
   map<CString,CString>       m_mapPosition;      //��λ����+˵��
   vector<CString>            m_vecPinMing;       //Ʒ������
   CDBStandardSizeModifyList* m_pModifyList;      //��Ӧ�����б�
};

class CDBStandardSizeList : public CDataListMid
{
   DECLARE_SERIAL(CDBStandardSizeList)
public:
   CDBStandardSizeList();
   ~CDBStandardSizeList();
   void Copy( CDBStandardSizeList *pList );

   CDBStandardSize*  GetItem(int nIndex);
   void    AddItem(CDBStandardSize* pItem);
   void    DeleteItem(int nIndex);
   BOOL    DeleteUserByUserID(CADOConn * pADOConn, vector<CString> vecUserID);
   BOOL    GetAllDBInfo(CADOConn *pADOConn);// ��ȡ�������� liuhw 2019/05/16

   static CDBStandardSizeList * Instance();		//��ȡ��ָ�룩ʵ��
   MAP_GridCtrl_AllData CreateGridData(const CString & strUserDuty = _T(""));//���ɱ������
private:
   static std::shared_ptr<CDBStandardSizeList> sm_inst;
};

class CDBStandardSizeModify :   public CDataMid
{
   DECLARE_SERIAL(CDBStandardSizeModify)                         //���л������л�����Ҫ��ӵ�����
public:
   CDBStandardSizeModify();
   ~CDBStandardSizeModify();;
   static CDBStandardSizeModify * Instance();                // ��ȡ��ָ�룩ʵ��
   
   void ResetData();                                   // ��������
   CString GetInsertSQL();                             // ��ȡ�����SQL���
   void Copy(CDBStandardSizeModify *pData);            // ��������
   BOOL UpdateDBInfo(CADOConn * pADOConn);             // ����DB
   BOOL GetAllDBInfo(CADOConn *pADOConn);		          // ��ȡ����������Ϣ

   BOOL UpdateAllDBInfoByID(CADOConn * pADOConn);      // �������ݵ����ݿ�
   BOOL InsertAllDBInfoByID(CADOConn * pADOConn);      // ������ݵ����ݿ�
private:
   static std::shared_ptr<CDBStandardSizeModify> sm_inst;

public:
   __int64		               m_nID;              //����ID
   __int64		               m_nSizeID;          //���ID���ж�����
   CString                    m_strSize;          //�ߴ�
   CString                    m_strPosition;      //��λ
   CString                    m_strName;          //����
   double                     m_nNumber;          //�ߴ�ֵ
   CString                    m_cMemo;            //˵��
};


class CDBStandardSizeModifyList : public CDataListMid
{
   DECLARE_SERIAL(CDBStandardSizeModifyList)
public:
   CDBStandardSizeModifyList();
   ~CDBStandardSizeModifyList();
   void Copy( CDBStandardSizeModifyList *pList );
   CDBStandardSizeModify*  GetItem(int nIndex);
   BOOL GetItemBySize(CString strName);
   BOOL GetItemByPos(CString strName);
   void    AddItem(CDBStandardSizeModify* pItem);
   void    DeleteItem(int nIndex);
   BOOL    DeleteUserByUserID(CADOConn * pADOConn, vector<CString> vecUserID);
   BOOL    GetAllDBInfoByFangAnName(CADOConn *pADOConn,CString strFangAnNmae);// ���ݷ�������ȡ���гߴ����� liuhw 2019/05/16
   BOOL    GetAllDBInfoByPM(CADOConn *pADOConn,CString strPinMing);// ���ݿ�ŵ�Ʒ����ȡ���гߴ緽������ liuhw 2019/05/16

   void    SortList(CDBSizePartInfoList * pSizePartList);

   static CDBStandardSizeModifyList * Instance();		//��ȡ��ָ�룩ʵ��
#ifdef USING_GRIDCTRL_MARK
   MAP_GridCtrl_AllData CreateGridData(map<CString,CString> & map_Size);//���ɱ������
#endif // USING_GRIDCTRL_MARK
private:
   static std::shared_ptr<CDBStandardSizeModifyList> sm_inst;
};
