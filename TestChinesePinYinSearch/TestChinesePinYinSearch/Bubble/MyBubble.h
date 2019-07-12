
// MyBubble.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"

class CMyBubble: public CWnd
{
public:
   CMyBubble();
   BOOL Create(int nX, int nY, HWND hParent, const CString &sText);
   BOOL Show();
   BOOL Hide();
   void SetPos(int nX, int nY);
   void SetText(const CString &sText);
   void SetBrush(int nBrush){m_nBrush = nBrush;}
private:
   DECLARE_MESSAGE_MAP()
   void OnPaint();
   void OnShowWindow(BOOL bShow, UINT nStatus);
   void OnTimer(UINT_PTR nIDEvent);
   CFont m_Font;
   CString m_sText;
   int m_nWindowWidth;
   int m_nBrush; //背景色
};