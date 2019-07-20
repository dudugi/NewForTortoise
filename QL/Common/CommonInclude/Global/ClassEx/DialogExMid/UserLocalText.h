#pragma once

#include "DataMid.h"

class CUserCtrlDefValue :public CDataMid
{
	DECLARE_SERIAL(CUserCtrlDefValue)
public:
	CUserCtrlDefValue();
	~CUserCtrlDefValue();
	void ResetData();
	static CUserCtrlDefValue * Instance();//��ȡ��ָ�룩ʵ��
	void	Copy(CUserCtrlDefValue *pData);
	void	Serialize(CArchive& ar);

	UINT	m_nDlgID;		//�Ի���ID
	UINT	m_nCtrlID;		//�ؼ�ID
	CString m_strCtrlType;	//�ؼ�����
	CString	m_strDefValue;	//Ĭ������

private:
	static std::shared_ptr<CUserCtrlDefValue> sm_inst;
};

class CUserCtrlDefValueList : public CDataListMid 
{
	DECLARE_SERIAL(CUserCtrlDefValueList)
public:
	CUserCtrlDefValueList();
	~CUserCtrlDefValueList();
	static CUserCtrlDefValueList * Instance();//��ȡ��ָ�룩ʵ��

	void	Serialize(CArchive& ar);
	CUserCtrlDefValue*	GetItem(int nIndex);
	void	DeleteItem(int nIndex);	
	void	DeleteItem(int nDlgID,int nCtrlID,CString strCtrlType=_T(""));
	int		FindDefVauleSel(int nDlgID,int nCtrlID,CString strCtrlType=_T(""));
	CString FindDefVaule(int nDlgID,int nCtrlID,CString strCtrlType=_T(""));
	BOOL	AddDefVaule(int nDlgID,int nCtrlID,CString strDefValue,CString strCtrlType=_T(""));
   int FindDefVauleSelNoCtrlType(int nDlgID,int nCtrlID);
private:
	static std::shared_ptr<CUserCtrlDefValueList> sm_inst;
};

/************************************************************************
 * Date��2016-12-25 ������
 * Author��zhangtao
 * brief: ��¼�û����õ����֣����浽�����ļ���
 ************************************************************************/

class CUserLocalText :public CDataMid
{
	DECLARE_SERIAL(CUserLocalText)
public:
	//m_nDlgID m_nCboID m_strType m_strName���ڲ��ҵ�����
	//m_strText ��Ҫ���ҵ�����
	int		m_nDlgID;	//�Ի���ID
	int		m_nCboID;	//�ؼ�ID��һ���ǿؼ���CComboBox��
	CString m_strType;	//��¼���ͣ�eg:��֯��ԭ��...��
	CString	m_strName;	//��¼��Ӧ������	 
	CString	m_strText;	//��¼����

public:
	CUserLocalText();
	virtual ~CUserLocalText();
	void	ResetData();
	void	Copy(CUserLocalText *pData);
	void	Serialize(CArchive& ar);
	static CUserLocalText * Instance();//��ȡ��ָ�룩ʵ��

private:
	static std::shared_ptr<CUserLocalText> sm_inst;
};

class CUserLocalTextList : public CDataListMid 
{
	DECLARE_SERIAL(CUserLocalTextList)
public:
	CUserLocalTextList();
	virtual ~CUserLocalTextList();

	void	Copy(CUserLocalTextList* pList);
	void	Serialize(CArchive& ar);
	CUserLocalText*	GetItem(int nIndex);
	void	DeleteItem(int nIndex);	
 	void	DeleteItem(int nDlgID,int nComboID);
 	int		FindTextSel(int nDlgID,int nComboID,CString strText);

 	BOOL	AddText(int nDlgID,int nComboID,CString strText);
 	void	GetText(int nDlgID,int nComboID,CUserLocalTextList *pList);
 	void	UpdateText(int nDlgID,int nComboID,CUserLocalTextList *pList);
// 	void	AddItem(CString strKey,int nDlgID,int nCtrlID);//�ո�
// 	void	AddItem2(CString strKey,int nDlgID,int nCtrlID);//�س�

	static CUserLocalTextList * Instance();//��ȡ��ָ�룩ʵ��

private:
	static std::shared_ptr<CUserLocalTextList> sm_inst;
};
