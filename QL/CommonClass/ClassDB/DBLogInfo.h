/*************************************************
// <�ļ�>: DBLogInfo.h
// <˵��>: ��־��Ϣ��
// <����>: wangzl
// <����>: 2019/01/30 10:33:01
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#pragma once

#include "DataMid.h"
#include "DBKeyDef.h"
#include "DBKeyDef_V.h"
#include "DBKeyDef_Cust.h"
#include <map>
#include <vector>
class CADOConn;

struct new_and_old
{
   CString strID;         //���ֶ����ڵ�����ID
   CString strFiledName;  //�ֶ�����
   CString strOldValue;   //�ɵ��ֶε�ֵ
   CString strNewValue;   //�µ��ֶε�ֵ
};

typedef std::map<CString ,new_and_old> table_log_map_row;
typedef std::map<int , table_log_map_row> table_log_map;

class CDBLogInfoData :public CDataMid
{
	DECLARE_SERIAL( CDBLogInfoData)//���л������л�����Ҫ��ӵ�����
public:
	int				m_nID;			//����ID
	CString			m_strCate;		//���
	CString			m_strCode;		//���Ż��ʽ��/����
	COleDateTime	m_dDate;		//����ʱ��
	CString			m_strMaker;		//������
	CString			m_strType;		//��������
	CString			m_strAction;	//����Ĳ�����Ϊ
	CString			m_strInterFace; //��������
	CString         m_strProject;	//��Ŀ����
   CString        m_strMacAddr; //Mac��ַ liuhw 2018/10/21

public:
	CDBLogInfoData();
	~CDBLogInfoData();
   void SetLogData(CString strCate,CString strCode,CString strMaker,CString strType,CString strAction,CString strMacAddr,CString strInterFaceName = _T(""),CString strProjectName = _T(""));
   void ResetData();
   void EmptyLogAction();
	void Copy(CDBLogInfoData *pData);
	void Serialize(CArchive& ar);
	BOOL GetAllDBInfo(CADOConn *pADOConn);			//��ȡһ����¼��Ϣ
	BOOL InsertAllDBInfoByAct(CADOConn *pADOConn);	//����һ���¼�¼
   CString GetSQLInsertAllDBInfoByAct();
	BOOL InsertAllDBInfoWithLocalTime(CADOConn *pADOConn);
   CString GetSQLInsertAllDBInfoWithLocalTime();

	BOOL DelAllDBInfoByAct(CADOConn *pADOConn);		//�����û��˻�ɾ����¼
	CString GetInsertSQL();//���ز����SQL���
   //�޸�ʱ���жϱ�������Ƿ����޸ģ�����н��ֶ������Map�С� add liuhw 2018/09/17
   static void TestOperatLog(table_log_map &mapLog, int nRowID,CString strID,CString strFiledID,CString strFiledName, CString strNewValue, CString strOldValue);
   //��Map�е�������� add liuhw 2018/09/17
   static CString WriteChangeLog(table_log_map &old_map);

	static CDBLogInfoData * Instance();			//��ȡ��ָ�룩ʵ��

   enum              //������־�����ݿ�������� liuhw 2018/09/05
   {
      TYPE_ADD,
      TYPE_MODIFY,
   };
   
private:
	static std::shared_ptr<CDBLogInfoData> sm_inst;
};

class CDBLogInfoList  : public CDataListMid
{
	DECLARE_SERIAL(CDBLogInfoList)
public:
	CDBLogInfoList();
	~CDBLogInfoList();
	CDBLogInfoData* GetItem(int nIndex);			//����������ȡItem
	void AddItem(CDBLogInfoData* pItem);			//���Item
	void DeleteItem(int nIndex);					//ɾ���̶�����Item
	static CDBLogInfoList * Instance();			//��ȡ��ָ�룩ʵ��

	//��ȡ������־ ���ݶ�����
	//add by lida 2017/07/11
	std::map<CString,CDBLogInfoData*> GetOrderLogByOrderCode(CADOConn *pADOConn,CString strOrderCode);

	//��ȡlog������Ҫ������
	void GetListData(CADOConn *pADOConn , CString startTime , CString endTime , CString strUser ,
		CString projectName, CString strKey , std::vector<CString> strOpTypeLst);
   /*******************************************************************
   * @brief :  ��־Ӣ�ı���ת���ı���
   * @author : liuhw 2019/02/21 13:41:33
   * @param :   key:Ӣ�ı��� ��value ���ı���Map
   * @example : 
   * @return :  
   *******************************************************************/
   void SetCateEnglishToChinese(__in std::map<CString , CString> tableNameMap);
#ifdef USING_GRIDCTRL_MARK
	MAP_GridCtrl_AllData CreatrGridData(CADOConn *pADOConn);
#endif
private:
   std::map<CString , CString> m_tableNameMap;// Key:Ӣ�ı�����value:���ı��� liuhw 2019/02/21
private:
	static std::shared_ptr<CDBLogInfoList> sm_inst;
};