#pragma once
/*************************************************
// <文件>: SizeBoxEdit.h
// <说明>: 透明且可调整大小的文本编辑框
// <作者>: duchen
// <日期>: 2019/02/22
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#include "SizeBox.h"
#include "MyTransparentRichEdit.h"

class CSizeBoxEdit: public CSizeBox
{
public:
   CSizeBoxEdit();
   virtual BOOL Create(int nX, int nY, int nWidth, int nHeight,
      HWND hParent, const CString &sText) override;
   virtual BOOL Show() override; //显示窗口 并使得编辑框获得焦点
   BOOL GetCurText(CString *psText, CRect *pRect); //获取当前能看到的文字
   BOOL SetEditFontHeight(int nHeight, int nFontSize = 0); //设置编辑文字高度 nHeight是创建字体用的高度，nFontSize是临时存的字体信息，通过GetEditFontSize获取
   int GetEditFontSize(){return m_nFontSize;} //获取SetEditFontHeight时存的第二个参数nFontSize
   BOOL SetEditColor(COLORREF color); //设置编辑框文字颜色
   void SetEditDrawBackgroundFunc(std::function<void(const CRect &RectInScreen, const CRect &RectInClient, CDC *pTargetDC)> funcBackGround); //设置画背景图的回调函数
   void SetBottomY(int nBottomY){m_nBottomY = nBottomY;} //设置最下方y坐标，当文字行数变多时，防止内容超出屏幕
   BOOL SetEditText(const CString &sText); //设置文字
   BOOL ReplaceSelEditText(const CString &sText); //替换选中的文字为sText
private:
   DECLARE_MESSAGE_MAP()
private:
   CMyTransparentRichEdit m_RichTransparent; //透明文本编辑框
   int m_nFontHeight;   //字体高度
   int m_nFontSize;     //临时存的字体高度信息
   int m_nBottomY;      //允许到达的最下方y坐标，当文字行数变多时，防止内容超出屏幕
   afx_msg void OnSize(UINT nType, int cx, int cy); //同时移动内部的透明的文本编辑框
   void OnMove(int x, int y);    //没用
   void OnEnChangeRichedit21();  //文字变化后，文字行数变多，则窗口高度也变高
   afx_msg BOOL OnEraseBkgnd(CDC* pDC); //没用
};