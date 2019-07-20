// EditDoubleNum.cpp : ʵ���ļ�
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



// CEditDoubleNum ��Ϣ�������

void CEditDoubleNum::OnChar( UINT nChar, UINT nRepCnt, UINT nFlags )
{
   //��Ч���������ֺ͸�������С����ͻ��˼� 
   //if(nChar == 12290)//ȫ�ǵ�С�����ֵ
   //{
   //   nChar = 46;
   //}

/*
	BOOL bCtrlState = GetKeyState(VK_CONTROL);
	if (bCtrlState && 0 != nFlags)
	{//CTRL+V ���޷����� ��û���� wangzl
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
   //������λ��
   int nPosCurbgn, nPosCurend;
   GetSel(nPosCurbgn, nPosCurend);
   CEdit::OnChar(  nChar,  nRepCnt,  nFlags);
   GetWindowText(sAfter);
   int nLength = sAfter.GetLength();
   int nPos = sAfter.Find(_T("."));
   //������ȳ������ó����򷵻�
   if(nLength > m_nLength)
   {
      SetWindowText(sBefore);
      SetSel(nPosCurbgn,nPosCurend,true);
      return;
   }
   //������ȳ������õľ����򷵻�
   if(nPos != CB_ERR && (nLength - nPos -1 > m_nDec || m_nDec==0))
   {
      SetWindowText(sBefore);
      SetSel(nPosCurbgn,nPosCurend,true);
      return;
   }
   //С���㲻����λ
   if(nLength > 0 && sAfter.Left(1) == _T("."))
   {
      SetWindowText(sBefore);
      SetSel(nPosCurbgn,nPosCurend,true);
      return;
   }
   //ֻ��һ��С����
   if(sBefore.Find(_T(".")) != CB_ERR && nChar == 46)
   {
      SetWindowText(sBefore);
      SetSel(nPosCurbgn,nPosCurend,true);
      return;
   }
}


void CEditDoubleNum::PreSubclassWindow()
{
	// TODO: �ڴ����ר�ô����/����û���
	ModifyStyle(ES_NUMBER,0,0);//�Ƴ�ԭ�е�number���� wangzl 2017-09-09
	CBCGPEdit::PreSubclassWindow();
}
