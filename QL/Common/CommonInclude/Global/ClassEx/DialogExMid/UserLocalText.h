#pragma once

#include "DataMid.h"

class CUserCtrlDefValue :public CDataMid
{
	DECLARE_SERIAL(CUserCtrlDefValue)
public:
	CUserCtrlDefValue();
	~CUserCtrlDefValue();
	void ResetData();
	static CUserCtrlDefValue * Instance();//获取（指针）实例
	void	Copy(CUserCtrlDefValue *pData);
	void	Serialize(CArchive& ar);

	UINT	m_nDlgID;		//对话框ID
	UINT	m_nCtrlID;		//控件ID
	CString m_strCtrlType;	//控件类型
	CString	m_strDefValue;	//默认内容

private:
	static std::shared_ptr<CUserCtrlDefValue> sm_inst;
};

class CUserCtrlDefValueList : public CDataListMid 
{
	DECLARE_SERIAL(CUserCtrlDefValueList)
public:
	CUserCtrlDefValueList();
	~CUserCtrlDefValueList();
	static CUserCtrlDefValueList * Instance();//获取（指针）实例

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
 * Date：2016-12-25 星期日
 * Author：zhangtao
 * brief: 记录用户常用的文字，保存到本地文件中
 ************************************************************************/

class CUserLocalText :public CDataMid
{
	DECLARE_SERIAL(CUserLocalText)
public:
	//m_nDlgID m_nCboID m_strType m_strName属于查找的条件
	//m_strText 需要查找的内容
	int		m_nDlgID;	//对话框ID
	int		m_nCboID;	//控件ID（一般是控件：CComboBox）
	CString m_strType;	//记录类型（eg:组织、原料...）
	CString	m_strName;	//记录对应的名称	 
	CString	m_strText;	//记录内容

public:
	CUserLocalText();
	virtual ~CUserLocalText();
	void	ResetData();
	void	Copy(CUserLocalText *pData);
	void	Serialize(CArchive& ar);
	static CUserLocalText * Instance();//获取（指针）实例

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
// 	void	AddItem(CString strKey,int nDlgID,int nCtrlID);//空格
// 	void	AddItem2(CString strKey,int nDlgID,int nCtrlID);//回车

	static CUserLocalTextList * Instance();//获取（指针）实例

private:
	static std::shared_ptr<CUserLocalTextList> sm_inst;
};
