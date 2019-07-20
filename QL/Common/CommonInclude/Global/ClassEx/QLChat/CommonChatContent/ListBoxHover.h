#pragma once
/*************************************************
// <文件>: ListBoxHover.h
// <说明>: 可以在鼠标悬停到item上时显示高亮背景色的Listbox
// <作者>: duchen
// <日期>: 2019/02/22
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#include <afxwin.h>
#include <map>
#include <afxdd_.h>
#include <functional>

class CListBoxHover:public CListBox
{

public:
   CListBoxHover();
   ~CListBoxHover();
   std::function<void (int nIndex)> m_funcEditItem; //点击某个item右侧图标时的回调函数
protected:
   virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS) override; //自绘item
   virtual void MeasureItem(LPMEASUREITEMSTRUCT) override;
   virtual BOOL SetHoverIndex(int nIndex, BOOL bPenHeight, const CRect &PenRect) ; //指定项高亮，之前高亮的项恢复
   virtual BOOL ClearHoverIndex(); //取消所有高亮
   enum
   {
      enClearHoverIndex = -2
   };
   int  m_nHoverIndex; //当前高亮项，如果为enClearHoverIndex则表示无高亮
   DECLARE_MESSAGE_MAP()
private:
   CRect GetPenRectByItemIndex(int nIndex); //某个item右侧图标的坐标范围

   afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam); //鼠标离开listbox，需要清除高亮
   afx_msg void OnMouseMove(UINT nFlags, CPoint point);        //用来控制高亮，取消高亮，鼠标离开前设置时间等
   void OnLButtonDown(UINT nFlags, CPoint point);              //鼠标点击某个item右侧图标时的处理

   bool m_bIsPressed;      //目前没用
   BOOL m_bIsMouseTrack;   // 鼠标追踪
   BOOL m_bPenHeight;      //某个item右侧图标(一支笔)是否高亮（highlight)
   HICON m_hIconHighlight; //高亮图标icon句柄
   HICON m_hIconNormal;    //普通图标icon句柄
};