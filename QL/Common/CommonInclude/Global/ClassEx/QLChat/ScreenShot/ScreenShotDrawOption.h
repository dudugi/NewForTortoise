#pragma once
/*************************************************
// <文件>: ScreenShotDrawOption.h
// <说明>: 截屏工具条选项窗口
// <作者>: duchen
// <日期>: 2019/02/22
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#include <functional>

class CScreenShotDrawOption : public CWnd
{
	DECLARE_DYNAMIC(CScreenShotDrawOption)

public:
	CScreenShotDrawOption();   // 标准构造函数
	virtual ~CScreenShotDrawOption();

   BOOL MyCreate(HWND hParent); //创建窗口，无需资源文件
   void SetShowStatus(BOOL bShowFontSize, int nColorIndex, int nSizeIndex); //设置显示状态（是否是显示字体大小，颜色，笔粗/字体大小）

   std::function<void (int nPenWidth, int nSizeIndex)> m_funcChangePenWidth; //笔粗变化回调函数
   std::function<void (COLORREF NewColor, int nColorIndex)> m_funcChangeColor; //颜色变化回调函数
   std::function<void (int nSize, int nSizeIndex)> m_funcSizeChange; //字体大小变化回调函数
protected:
	DECLARE_MESSAGE_MAP()
private:
   int m_nPenWidth; //当前笔粗
   COLORREF m_curColor; //当前颜色
   CComboBox m_cboFontSize; //当前字体大小
   BOOL m_bShowFontSize; //是否是显示字体大小
   afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
   afx_msg void OnPaint();
   afx_msg int OnCreate(LPCREATESTRUCT p);
   afx_msg void OnCbnSelchangeComboFontSize();
   afx_msg BOOL OnEraseBkgnd(CDC* pDC); //背景色涂白
   afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};
