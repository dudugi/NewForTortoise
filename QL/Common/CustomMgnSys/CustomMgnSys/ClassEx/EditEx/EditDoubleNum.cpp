// EditDoubleNum.cpp : 实现文件
//

#include "stdafx.h"
#include "EditDoubleNum.h"


// CEditDoubleNum

IMPLEMENT_DYNAMIC(CEditDoubleNum, CBCGPEdit)

CEditDoubleNum::CEditDoubleNum()
{
   m_nLength = 40;
   m_nDec = 2;
}

CEditDoubleNum::CEditDoubleNum(int maxLength,int nDec)
{
   m_nLength = maxLength;
   m_nDec = nDec;
}

CEditDoubleNum::~CEditDoubleNum()
{
}


void CEditDoubleNum::SetEditDoubleNum(int maxLength,int nDec)
{
	m_nLength = maxLength;
	m_nDec = nDec;
}

BEGIN_MESSAGE_MAP(CEditDoubleNum, CBCGPEdit)
   ON_WM_CHAR()
END_MESSAGE_MAP()



// CEditDoubleNum 消息处理程序

void CEditDoubleNum::OnChar( UINT nChar, UINT nRepCnt, UINT nFlags )
{
   //有效按键是数字和负号正号小数点和回退键 
   //if(nChar == 12290)//全角的小数点的值
   //{
   //   nChar = 46;
   //}

/*
	BOOL bCtrlState = GetKeyState(VK_CONTROL);
	if (bCtrlState && 0 != nFlags)
	{//CTRL+V 暂无法拦截 （没处理） wangzl
		CEdit::OnChar(nChar,nRepCnt,nFlags);
		return;
	}*/

   BOOL bConitue = (nChar >= 48 && nChar <= 57) 
      || nChar == 43
      || nChar == 45
      || nChar == 46
      || nChar == 8;

   if(!bConitue)
      return;
   CString sBefore,sAfter;
   GetWindowText(sBefore);
   //保存光标位置
   int nPosCurbgn, nPosCurend;
   GetSel(nPosCurbgn, nPosCurend);
   CEdit::OnChar(  nChar,  nRepCnt,  nFlags);
   GetWindowText(sAfter);
   int nLength = sAfter.GetLength();
   int nPos = sAfter.Find(_T("."));
   //如果长度超过设置长度则返回
   if(nLength > m_nLength)
   {
      SetWindowText(sBefore);
      SetSel(nPosCurbgn,nPosCurend,true);
      return;
   }
   //如果精度超过设置的精度则返回
   if(nPos != CB_ERR && (nLength - nPos -1 > m_nDec || m_nDec==0))
   {
      SetWindowText(sBefore);
      SetSel(nPosCurbgn,nPosCurend,true);
      return;
   }
   //小数点不在首位
   if(nLength > 0 && sAfter.Left(1) == _T("."))
   {
      SetWindowText(sBefore);
      SetSel(nPosCurbgn,nPosCurend,true);
      return;
   }
   //只有一个小数点
   if(sBefore.Find(_T(".")) != CB_ERR && nChar == 46)
   {
      SetWindowText(sBefore);
      SetSel(nPosCurbgn,nPosCurend,true);
      return;
   }
}


void CEditDoubleNum::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	ModifyStyle(ES_NUMBER,0,0);//移除原有的number属性 wangzl 2017-09-09
	CBCGPEdit::PreSubclassWindow();
}
