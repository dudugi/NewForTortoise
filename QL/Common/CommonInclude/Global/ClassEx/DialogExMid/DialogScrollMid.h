#pragma once
#include "DialogexMid.h"
#include "ScrollHelper.h"


/*************************************************
// <�ļ�>: DialogScrollMid.h
// <˵��>: �ɹ������� ����
// <����>: wangzl
// <����>: 2019/01/30 10:34:56
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
class CDialogScrollMid : public CDialogExMid
{
public:
	CDialogScrollMid(UINT nIDD,CWnd* pParent = NULL);	// ��׼���캯��
	~CDialogScrollMid();

protected:
	DECLARE_MESSAGE_MAP()

protected:
   CScrollHelper* m_pScrollHelper;

public:
   //����������ʾ�ĳߴ�
   void UpdateDisplaySize(int nWidth,int nHeight);

protected:
   virtual void PostNcDestroy();

public:
	virtual BOOL OnInitDialog();

	/*
	 * @brief	������Ϣ
	 * @author	
	 */
	virtual BOOL PreTranslateMessage(MSG* pMsg);

   afx_msg void OnSize(UINT nType, int cx, int cy);
   afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
   afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
   afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

};