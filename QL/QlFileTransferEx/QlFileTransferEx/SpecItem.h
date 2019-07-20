#pragma once



//2016/12/06 zhangt Create

class CSpecData :public CObject 
{
	DECLARE_SERIAL(CSpecData)
public:
	CSpecData();
	virtual ~CSpecData();

	void Copy(CSpecData *pData);
	void Serialize(CArchive& ar);

	//尺寸标识的类型
	typedef enum{
		SPECITEM_NORMAL = 0,
		SPECITEM_MUSTIN,
	}SpecItem_Type;


public:
	CString m_strPartName;
	CString m_strPartSize;//客户尺寸
	CString m_strRelSize;//成衣尺寸
	CString m_strRemark;//尺寸的备注信息
	int		m_nSizeType;//尺寸的标识  
};

class CSpecDataList : public CObList 
{
	DECLARE_SERIAL(CSpecDataList)
public:
	CSpecDataList();
	virtual ~CSpecDataList();
	void Copy(CSpecDataList *pDataList);
	void Serialize(CArchive& ar);
	void Empty();
	void AddItem(CSpecData* pItem);
	void DeleteItem(int nIndex);
	CSpecData* GetItem(int nIndex);
	CSpecData* GetItemByPartName(CString strPartName);
};

class CSpecItem :public CObject 
{
	DECLARE_SERIAL(CSpecItem)
public:
	CSpecItem();
	virtual ~CSpecItem();
	void Copy(CSpecItem *pItem);
	void Serialize(CArchive& ar);

public:
	CSpecDataList m_listSpecData;
	CString m_strSpecName;//规格名称
	int m_nBaseSpec;//1==标准规格  0==非标准规格
};

class CSpecItemList : public CObList
{
	DECLARE_SERIAL(CSpecItemList)
public:
	CSpecItemList();
	virtual ~CSpecItemList();
	void Copy(CSpecItemList *pItemList);
	void Serialize(CArchive& ar);
	void Empty();
	void AddItem(CSpecItem *pItem);
	void DeleteItem(int nIndex);
	CSpecItem* GetItem(int nIndex);
	CSpecItem* GetItemBySpecName(CString strSpecName);
	int GetIndexBySpecName(CString strSpecName);
	CSpecItem* GetBaseItem();

	//读写文件
	BOOL OnWriteFile(CString strFilePath,BOOL bDelOldFile=TRUE);
	BOOL OnReadFile(CString strFilePath,BOOL bDelFile=TRUE);
};

