/*************************************************
// <�ļ�>: DBProSet_Style.h
// <˵��>: ��ʽ�Ĺ��򷽰���
// <����>: wangzl
// <����>: 2019/01/30 10:28:22
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"
#include <map>

class CADOConn;

//��ʽ�������ñ�  �ñ����ÿ�ʽ��Ӧ�Ĺ���Ĭ��ָ���� 2017-11-08 wangzl
class CDBProSet_StyleData : public CDataMid
{
	DECLARE_SERIAL( CDBProSet_StyleData)//���л������л�����Ҫ��ӵ�����
public:
   enum{
      en_Person = 0,//����Ա
      en_Group,//����
   };
public:
	int			m_nID			;//����ID
	CString		m_strStyleNo	;//��ʽ��
	CString		m_strProName	;//��������
	CString		m_strUserID		;//�û�ID
	DWORD		   m_dwProTime		;//����ʱ��
   CString     m_strfPrice;      //���򹤼� yangjr 2018/5/3
   CString     m_strcIntro;      //˵�� yangjr 2018/5/3
   CString     m_strMark  ;      //Ĭ�Ϲ������ݱ�־λ   ���ڹ��򹤼������޸��Ǳ���Ƿ�λĬ�Ϲ��򹤼�   add anjie by 2018/11/22
   CString     m_strGXMark; // ������ luzw 2018/12/21
   int         m_nIsGroup     ;//�Ƿ���ָ�ɸ���ı�ʶ
public:
	CDBProSet_StyleData(void);
	~CDBProSet_StyleData(void);

	void ResetData();

	void Copy(CDBProSet_StyleData *pData);

	BOOL GetAllDBInfo(CADOConn *pADOConn);			//��ȡһ����¼��Ϣ
	BOOL InsertAllDBInfo(CADOConn *pADOConn);		//����һ���¼�¼
	BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);	//����һ����Ϣ
	BOOL DelAllDBInfoByID(CADOConn *pADOConn);		//�����û��˻�ɾ����¼

	BOOL ClearAllStyleInfo(CADOConn *pADOConn);//��տ�ʽ��Ӧ�����м�¼

   CString GetGongJiaByStyleNoAndProName(CADOConn *pADOConn,CString strStyleNo,CString strProName);		//���ݹ��������Լ���ʽ�Ż�ȡ��Ӧ�Ĺ���۸�

	CString GetInsertStr();
   CString GetUpdateStr(CString fieldStr,CString valueStr);
   CString GetUpdateStr2();   //���¹��ۺͱ�־λ�ֶ�
   CString GetDeleteByStyleNoSql(CString strStyleNo);  
   
};
typedef struct  
{
   int			m_nID			;//����ID   
   CString		m_strUserID		;//�û�ID
   DWORD		m_dwProTime		;//����ʱ��
}S_ONE_STYLEPROSET;
typedef std::map<CString,S_ONE_STYLEPROSET> MAP_OneStyleProSet;//һ����ʽ��Ӧ����Ĺ����¼��
class CDBProSet_StyleList  : public CDataListMid
{
	DECLARE_SERIAL(CDBProSet_StyleList)
public:
	CDBProSet_StyleList();
	~CDBProSet_StyleList();

   void Copy(CDBProSet_StyleList *pList);
	CDBProSet_StyleData* GetItem(int nIndex);			//����������ȡItem
	CDBProSet_StyleData* GetItemByName(CString strProName);
	void AddItem(CDBProSet_StyleData* pItem);			//���Item
   void AddItem_Before(int nIndex, CDBProSet_StyleData* pItem);
   void AddItem_After(int nIndex, CDBProSet_StyleData* pItem);
	void DeleteItem(int nIndex);					//ɾ���̶�����Item

	BOOL InsertAllDBInfo(CADOConn * pADOConn,CString strStyleNo);
   //���ݿ�ʽ�Ż�ȡ��Ӧ���� yangjr 2018/5/4
   BOOL GetProSetStyleData(CADOConn * pADOConn,CString strStyleNo);

   BOOL GetGongJiaMapByStyle(CADOConn *pADOConn,CString strStyleNo,std::map<CString,double> &mapData);		//���ݿ�ʽ�Ż�ȡ���еĹ���۸� yangjr 2018-1-17
   CString GetGongJiaByStyleNoAndProName(CADOConn *pADOConn,CString strStyleNo,CString strProName);		//���ݹ��������Լ���ʽ�Ż�ȡ��Ӧ�Ĺ���۸�

   BOOL UpdateZhiPaiPerson(CADOConn * pADOConn,CString strStyleNo);
   BOOL UpdateMemo(CADOConn * pADOConn,CString strStyleNo);

   //���ݿ�ţ������ȡ��Ӧ�ı�ע��Ϣ������Ϊ�����ȡȫ������Ϣ add by lida 2018/05/22
   CString GetStyleInfo(__in CADOConn * pADOConn,__in CString strStyleNo,__in vector<CString> vecGX=vector<CString>(),BOOL bWithProName = TRUE);
};


//���򹤼�excel����
typedef struct my_proset_style_info
{
   my_proset_style_info()
   {  
      m_strStyleNo	= _T("");
      m_strProName	= _T("");
      m_strUserID	= _T("");
      m_strfPrice = _T(""); 
   };

   CString GetUpdateSql(BOOL bIgnoreNull = TRUE);

   CString GetInsertSql();

   CString		m_strStyleNo	;//��ʽ��
   CString		m_strProName	;//��������
   CString		m_strUserID;//�û�ID
   CString      m_strfPrice;   //���򹤼� 
   CString      m_strMark;    //���۸��±�־������ȷ���Ƿ����Ĭ�Ϲ��򹤼ۣ� add anjie by 2019/03/26
}s_my_proset_style_info;

