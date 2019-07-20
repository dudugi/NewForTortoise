#pragma once
/*************************************************
// <文件>: MyBubble.h
// <说明>: 气泡状窗口（一个圆角矩形中间放文字）
// <作者>: duchen
// <日期>: 2019/02/22
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#include "afxcmn.h"
#include "afxwin.h"

class CMyBubble: public CWnd
{
public:
   CMyBubble();
   BOOL Create(int nX, int nY, HWND hParent, const CString &sText); //创建本窗口
   BOOL Show(); //显示
   BOOL Hide(); //隐藏
   void SetPos(int nX, int nY); //设置坐标
   void SetText(const CString &sText); //设置显示文字
   void SetBrush(int nBrush){m_nBrush = nBrush;} //设置画刷，通过GetStockObject(m_nBrush)获得句柄
private:
   DECLARE_MESSAGE_MAP()
   void OnPaint(); //画文字和圆角矩形
   void OnShowWindow(BOOL bShow, UINT nStatus); //目前没用
   void OnTimer(UINT_PTR nIDEvent); //时间到了隐藏本窗口
   CFont m_Font; //显示字体
   CString m_sText; //显示文字
   int m_nWindowWidth; //设置窗口宽度
   int m_nBrush; //通过GetStockObject(m_nBrush)获得句柄
};