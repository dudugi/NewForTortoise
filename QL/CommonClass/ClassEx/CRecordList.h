#pragma once
/*************************************************
// <�ļ�>: CRecordList.h
// <˵��>: KDV�е���Ƶ������ ����������ģ�鱣��һ�� �����޸�
// <����>: wangzl
// <����>: 2019/02/22
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
class CRecord: public CObject 
{
	DECLARE_SERIAL(CRecord)
public:
	CRecord();
	~CRecord();
	int m_nId;
	CString m_sName;
	CPoint m_Point;
	CSize m_Size;
	bool m_bActive;
	DWORD m_dwDataLength;
	BYTE *m_pData;
	COLORREF m_Color; // DWORD
	CString m_sInfo;

	void Serialize(CArchive& ar);
	void Copy(CRecord *pRecord);
};

class CMyRecordDlg;
typedef CList<CString,CString&>		STRList;
class CRecordList: public CObList  
{
	//DECLARE_SERIAL(CRecordList)
public:
	CRecordList();
	~CRecordList();
	//��������С����
	void Draw(CDC *pDc, double dlfScaling = 1, BOOL bIcoSizeChange = TRUE, int nXOffset = 0, int nYOffset = 0);
	void Delete();
	void SaveFile(CFile *pFile);
	void LoadFile(CFile *pFile);
	void EmptyList();
	CRecord *SendPoint(const CPoint &Point, BOOL bAddNew = 0);
	void SendMovePoint(const CPoint &Point);
	void SetWnd(CWnd *p);
	void Copy(CRecordList *pRecordList);
	int DeleteItem(CRecord *pRecord);
	void ResetPoint(CPoint offPt, double lfScaling);
	CRecord *JumpToNextPoint(CPoint *pPoint);
	CSize GetDrawSize();
   STRList m_listKDVContent; //��������ṩ�༭KDV����
private:
	CRecord *Hittest(const CPoint &point);
	void NoActiveAll();
	//void SetRecordToDlg(CRecord *pRecord, BOOL bPlayImmediately);
	const CSize m_DrawSize;
	//CMyRecordDlg *m_pDlg;
	CWnd *m_pWnd;
	CRecord *m_pLastRecord;
	CRecord *m_pLastJumpRecord;
	int m_nOffsetX;
	int m_nOffsetY;
};