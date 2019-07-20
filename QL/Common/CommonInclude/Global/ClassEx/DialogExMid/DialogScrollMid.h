#pragma once
#include "DialogexMid.h"
#include "ScrollHelper.h"


/*************************************************
// <文件>: DialogScrollMid.h
// <说明>: 可滚动窗口 基类
// <作者>: wangzl
// <日期>: 2019/01/30 10:34:56
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
class CDialogScrollMid : public CDialogExMid
{
public:
	CDialogScrollMid(UINT nIDD,CWnd* pParent = NULL);	// 标准构造函数
	~CDialogScrollMid();

protected:
	DECLARE_MESSAGE_MAP()

protected:
   CScrollHelper* m_pScrollHelper;

public:
   //更新虚拟显示的尺寸
   void UpdateDisplaySize(int nWidth,int nHeight);

protected:
   virtual void PostNcDestroy();

public:
	virtual BOOL OnInitDialog();

	/*
	 * @brief	拦截消息
	 * @author	
	 */
	virtual BOOL PreTranslateMessage(MSG* pMsg);

   afx_msg void OnSize(UINT nType, int cx, int cy);
   afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
   afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
   afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

};