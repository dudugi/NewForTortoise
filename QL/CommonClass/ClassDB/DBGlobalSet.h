/*************************************************
// <�ļ�>: DBGlobalSet.h
// <˵��>: ȫ��������Ϣ��
// <����>: wangzl
// <����>: 2019/01/30 10:32:46
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/
#pragma once

#include "DataMid.h"
#include "DBKeyDef.h"
#include "DBKeyDef_V.h"
#include "DBKeyDef_Cust.h"

class CADOConn;

#define DBGlobalSet_DelOrder					_T("����ɾ��")		//���ָ�  �ɻָ�
//����������������ƿ���		by WangZY 2018/03/09
#define DBGlogalSet_TitleFilter_OrderLimitCount				_T("��������������ݼ�¼������������")
#define DBGlogalSet_TitleFilter_ContentLimitCount			_T("������������б�������������")
#define DBGlobalSet_AbleProAutoFinish        _T("�����Զ����δɨ����")  //add by wangzl 2018-7-16
#define DBGlobalSet_FirstForbidSubmitProcess _T("��ֹ������ύ���׸�����") //add by duchen 2018-10-29
#define DBGlobalSet_AbleMustProcessAutoFinish   _T("�����ɨ�����Զ����") //add by wangzl 2018-7-16 Ĭ�Ϸ�
#define DBGlobalSet_TaskReworkEffectProcess  _T("�������Ӱ�칤������") //add by wangzl 2018-7-18 Ĭ�Ϸ�

#define DBGlobalSet_ColorState_CheckIn          _T("������ɫ״̬��ʾ-����")          //add by wangzl 2019-5-24
#define DBGlobalSet_ColorState_CheckoutEdit     _T("������ɫ״̬��ʾ-����ɱ༭")    //add by wangzl 2019-5-24
#define DBGlobalSet_ColorState_CheckoutRead     _T("������ɫ״̬��ʾ-������ɱ༭")  //add by wangzl 2019-5-24
#define DBGlobalSet_ColorState_FixVersion       _T("������ɫ״̬��ʾ-��ʽ����")      //add by wangzl 2019-5-24

#define DBGlobalSet_PictureMaxSize        _T("ͼƬ�ϴ����ߴ�����")   //add by anjie 2018-8-3
#define DBGlobalset_DisableOrder          _T("�ϻ����������϶���")     //add by wangzl 2018/09/12
#define DBGlobalset_VERSION_NAME          _T("�汾����")              //add by liuhw 2018/09/30
#define DBGlobalset_AbleUnExistsStyleOrder _T("��ʽδά�������µ�")  //add by wangzl 2019/04-04
#define DBGlobalset_ShowPicNum            _T("��ʾ��ʽͼƬ����/ҳ")  // add by lida 2019/05/23
#define DBGlobalset_RefreshTime           _T("��ʽ�����Զ�ˢ��ʱ��")  // add by wangzl 2019/07/19

#define ID_DEFAULT		-1
#define MAX_SIZE  600

struct tag_sql_data
{
	tag_sql_data()
	{
		nID = ID_DEFAULT;
		strName = _T("");
		strValue = _T("");
		strRemark = _T("");
	}
	int				nID;			//����ID
	CString			strName;		//����
	CString			strValue;		//ֵ
	CString			strRemark;	//��ע
};
class CDBGlobalSetData :public CDataMid
{
	DECLARE_SERIAL( CDBGlobalSetData)//���л������л�����Ҫ��ӵ�����
public:
	int				m_nID;			//����ID
	CString			m_strName;		//����
	CString			m_strValue;		//ֵ
	CString			m_strRemark;	//��ע

public:
	CDBGlobalSetData();
	~CDBGlobalSetData();
	void ResetData();
	void Copy(CDBGlobalSetData *pData);
	void Serialize(CArchive& ar);
	BOOL GetAllDBInfo(CADOConn *pADOConn);			//��ȡһ����¼��Ϣ
	BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);	//ͨ��ID����һ����¼��Ϣ
	BOOL InsertAllDBInfo(CADOConn *pADOConn);		//���롾�������¼�¼
	CString GetTextUpdateAllDBInfoByID();
   CString GetTextInsertAllDBInfoByID();//��ȡ�������Ĳ���
	BOOL SetData_By_Key(CString strKey, CString strValue);
	CString GetDBValueByName(CADOConn* pADOConn,CString strName);//�����ݿ��ȡ��Ϣ
	tag_sql_data GetDBAllValueByName(CADOConn* pADOConn,CString strName);//�����ݿ��ȡĳ�����ݵ�ID
	static CDBGlobalSetData * Instance();			//��ȡ��ָ�룩ʵ��

#ifdef USING_GRIDCTRL_MARK
	MAP_GridCtrl_RowData CreateGridRowData();
#endif// USING_GRIDCTRL_MARK

private:
	static std::shared_ptr<CDBGlobalSetData> sm_inst;
};

class CDBGlobalSetList  : public CDataListMid
{
	DECLARE_SERIAL(CDBGlobalSetList)
public:
	CDBGlobalSetList();
	~CDBGlobalSetList();
	CDBGlobalSetData* GetItem(int nIndex);	//����������ȡItem
	void AddItem(CDBGlobalSetData* pItem);	//���Item
	void DeleteItem(int nIndex);			//ɾ���̶�����Item
	static CDBGlobalSetList * Instance();	//��ȡ��ָ�룩ʵ��
	void GetListFromDB(CADOConn *pADOConn);	//�������л�ȡ���ݵ�����

	//������Ҫ�����ƴ������л�ȡ��ص�ֵ
	CString GetValueByName(CString strName);

   COLORREF GetColorValueByName(CString strName);     //��ȡ��ɫֵ
	
	//������Ҫ�����ƴ������л�ȡ��ص���ֵ		by WangZY 2018/03/09
	int GetIntValueByName(CString strName, int nDef);

   //�������ƻ�ȡ��Ӧ����  
   CDBGlobalSetData* GetItemByName(CString strName);	//����������ȡItem

// #ifdef USING_GRIDCTRL_MARK
// 	MAP_GridCtrl_AllData CreatrGridData();
// #endif // USING_GRIDCTRL_MARK

private:
	static std::shared_ptr<CDBGlobalSetList> sm_inst;
};
