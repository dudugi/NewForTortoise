// ValidCharEdit.cpp : 实现文件
//
#include "stdafx.h"
#include "ValidCharEdit.h"
#include <afxtagmanager.h>


// CValidCharEdit

IMPLEMENT_DYNAMIC(CValidCharEdit, CEdit)

CValidCharEdit::CValidCharEdit()
{
	m_bPasteProcessing = FALSE;
	m_bSetTextProcessing = FALSE;
}

CValidCharEdit::~CValidCharEdit()
{
}


BEGIN_MESSAGE_MAP(CValidCharEdit, CEdit)
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_CREATE()
	ON_MESSAGE(WM_PASTE, &CValidCharEdit::OnPaste)
	ON_MESSAGE(WM_SETTEXT, &CValidCharEdit::OnSetText)
	ON_MESSAGE(WM_GETTEXT, &CValidCharEdit::OnGetText)
	ON_MESSAGE(WM_GETTEXTLENGTH, &CValidCharEdit::OnGetTextLength)
	ON_MESSAGE(WM_MFC_INITCTRL, &CValidCharEdit::OnInitControl)
   ON_WM_KEYDOWN()
END_MESSAGE_MAP()



// CValidCharEdit 消息处理程序

void CValidCharEdit::SetValidChars(LPCTSTR lpszValid /*= NULL*/)
{
	if (lpszValid != NULL)
	{
		m_strValid = lpszValid;
	}
	else
	{
		m_strValid.Empty();
	}
}

void CValidCharEdit::SetWindowText(LPCTSTR lpszString)
{
	CEdit::SetWindowText(lpszString);
}

BOOL CValidCharEdit::IsMaskedChar(TCHAR chChar, TCHAR chMaskChar) const
{
	// Check the key against the mask
	switch (chMaskChar)
	{
	case _T('D'): // digit only
		if (_istdigit(chChar))
		{
			return TRUE;
		}
		break;
	case _T('d'): // digit or space
		if (_istdigit(chChar))
		{
			return TRUE;
		}
		if (_istspace(chChar))
		{
			return TRUE;
		}
		break;
	case _T('+'): // '+' or '-' or space
		if (chChar == _T('+') || chChar == _T('-'))
		{
			return TRUE;
		}
		if (_istspace(chChar))
		{
			return TRUE;
		}
		break;
	case _T('C'): // alpha only
		if (_istalpha(chChar))
		{
			return TRUE;
		}
		break;
	case _T('c'): // alpha or space
		if (_istalpha(chChar))
		{
			return TRUE;
		}
		if (_istspace(chChar))
		{
			return TRUE;
		}
		break;
	case _T('A'): // alpha numeric only
		if (_istalnum(chChar))
		{
			return TRUE;
		}
		break;
	case _T('a'): // alpha numeric or space
		if (_istalnum(chChar))
		{
			return TRUE;
		}
		if (_istspace(chChar))
		{
			return TRUE;
		}
		break;
	case _T('*'): // a printable character
		if (_istprint(chChar))
		{
			return TRUE;
		}
		break;
	}
	return FALSE; // not allowed symbol
}

BOOL CValidCharEdit::SetValue(LPCTSTR lpszString, BOOL bWithDelimiters /*= TRUE*/)
{
	ENSURE(lpszString != NULL);

	// Make sure the string is not longer than the mask
	CString strSource = lpszString;
	
	// Make sure the value has only valid string characters
	if (!m_strValid.IsEmpty())
	{
		BOOL bOk = TRUE;
		for (int iPos = 0; bOk && iPos < strSource.GetLength(); iPos++)
		{
			bOk = (m_strValid.Find(strSource[iPos]) != -1);
		}

		if (!bOk)
		{
			return FALSE;
		}
	}

	// Use mask, validate against the mask
	if (!m_strMask.IsEmpty())
	{
		CString strResult = _T("");

		int iSrcChar = 0;
		int iDstChar = 0;
		while ((iSrcChar<strSource.GetLength()))
		{
			TCHAR chChar = strSource[iSrcChar];
			
			if (!IsMaskedChar(chChar, m_strMask[iDstChar]))
			{
				return FALSE;
			}
			strResult.SetAt(iDstChar, chChar);
			iSrcChar++;
			iDstChar++;

		}
		m_str = strResult;
	}
	else // Don't use mask
	{
		m_str = strSource;
	}

	return TRUE;
}

BOOL CValidCharEdit::CheckChar(TCHAR chChar, int nPos)
{
	ASSERT(nPos >= 0);

	// Don't use mask
	if (m_strMask.IsEmpty())
	{
		// Use valid string characters
		if (!m_strValid.IsEmpty())
		{
			return(m_strValid.Find(chChar) != -1);
		}
		// Don't use valid string characters
		else
		{
			return TRUE;
		}
	}
	else
	{
		ASSERT(nPos < m_strMask.GetLength());
	}

	// Use mask
	BOOL bIsMaskedChar = IsMaskedChar(chChar, m_strMask[nPos]);

	// Use valid string characters
	if (!m_strValid.IsEmpty())
	{
		return bIsMaskedChar &&(m_strValid.Find(chChar) != -1);
	}
	// Don't use valid string characters
	else
	{
		return bIsMaskedChar;
	}
	
}

BOOL CValidCharEdit::DoUpdate(BOOL bRestoreLastGood /*= TRUE*/, int nBeginOld /*= -1*/, int nEndOld /*= -1*/)
{
	if (m_bPasteProcessing)
	{
		return FALSE;
	}

	m_bPasteProcessing = TRUE;

	CString strNew;
	GetWindowText(strNew);

	BOOL bRet = SetValue(strNew, TRUE);
	if (!bRet)
	{
		MessageBeep((UINT)-1);
	}

	if (!bRet && bRestoreLastGood)
	{
		CString strOld = m_str;
		SetWindowText (strOld);

		if (nBeginOld != -1)
		{
			CEdit::SetSel(nBeginOld, nEndOld);
		}
	}

	m_bPasteProcessing = FALSE;
	return bRet;
}

void CValidCharEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	TCHAR chChar = (TCHAR) nChar;
	if (_istprint(chChar) && !(::GetKeyState(VK_CONTROL)&0x80))
	{
		int nStartPos, nEndPos;
		CEdit::GetSel(nStartPos, nEndPos);
		if (!CheckChar(chChar, nStartPos))
		{
			MessageBeep((UINT)-1);
			return;
		}
	}
	else if ((nChar == VK_DELETE || nChar == VK_BACK) &&(!m_strMask.IsEmpty()))
	{
		return;
	}
	else if (1 == nChar)//CTRL+A
	{
		CEdit::SetSel(0,-1);
		return;
	}

	int nBeginOld, nEndOld;
	CEdit::GetSel(nBeginOld, nEndOld);

	CEdit::OnChar(nChar, nRepCnt, nFlags);

	DoUpdate(TRUE, nBeginOld, nEndOld);
}

int CValidCharEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;

	CWnd::SetWindowText(m_str);
	return 0;
}

LRESULT CValidCharEdit::OnPaste(WPARAM, LPARAM)
{
	m_bPasteProcessing = TRUE;

	int nBeginOld, nEndOld;
	CEdit::GetSel(nBeginOld, nEndOld);

	Default();

	int nBegin, nEnd;
	CEdit::GetSel(nBegin, nEnd);
	nEnd = max(nBegin, nEnd);

	CString str;
	CWnd::GetWindowText(str);

	CString strPaste = str.Mid(nBeginOld, nEnd - nBeginOld);
	CString strOld;
	int nLeft = nBeginOld;

	strOld = GetValue();

	CString strNew = strOld.Left(nLeft) + strPaste;
	/*BOOL bOverwrite = !m_strMask.IsEmpty();
	int nRight = nLeft + strPaste.GetLength();
	if (nRight < strOld.GetLength())
	{*/
	strNew += strOld.Mid(nEndOld);
	/*}*/

	if (!SetValue(strNew, TRUE))
	{
		MessageBeep((UINT)-1);
	}

	CWnd::SetWindowText(m_str);

	CEdit::SetSel(nBeginOld, nBeginOld);

	m_bPasteProcessing = FALSE;

	return 0L;
}

LRESULT CValidCharEdit::OnSetText(WPARAM, LPARAM lParam)
{
	if (m_bSetTextProcessing || m_bPasteProcessing)
	{
		return Default();
	}

	m_bSetTextProcessing = TRUE;

	BOOL bSetValueRes = SetValue((LPCTSTR)lParam, TRUE);
	if (bSetValueRes)
	{
		LRESULT lRes = FALSE;
		CString strNewValidated = GetValue();
		if (strNewValidated.Compare((LPCTSTR)lParam) != 0)
		{
			// validated new value should differ from lParam
			lRes = (LRESULT)::SetWindowText(GetSafeHwnd(), (LPCTSTR)strNewValidated);
		}
		else
		{
			lRes = Default();
		}

		m_bSetTextProcessing = FALSE;
		return lRes;
	}

	m_bSetTextProcessing = FALSE;
	return FALSE;
}

LRESULT CValidCharEdit::OnGetText(WPARAM wParam, LPARAM lParam)
{
	if (m_bPasteProcessing)
	{
		return Default();
	}

	int nMaxCount = (int)wParam;
	if (nMaxCount == 0)
	{
		return 0;       // nothing copied
	}

	LPTSTR lpszDestBuf = (LPTSTR)lParam;
	if (lpszDestBuf == NULL)
	{
		return 0;       // nothing copied
	}

	CString strText;
	
	strText = GetValue();

	// Copy text
	int nCount = min(nMaxCount, strText.GetLength());
	LPCTSTR lpcszTmp = strText;
	CopyMemory(lpszDestBuf, lpcszTmp, nCount * sizeof(TCHAR));

	// Add terminating null character if possible
	if (nMaxCount > nCount)
	{
		lpszDestBuf[nCount] = _T('\0');
	}

	return(nCount * sizeof(TCHAR));
}

LRESULT CValidCharEdit::OnGetTextLength(WPARAM, LPARAM)
{
	if (m_bPasteProcessing)
	{
		return Default();
	}

	CString strText;
	strText = GetValue();
	
	return (LRESULT) strText.GetLength();
}

LRESULT CValidCharEdit::OnInitControl(WPARAM wParam, LPARAM lParam)
{
	DWORD dwSize = (DWORD)wParam;
	BYTE* pbInitData = (BYTE*)lParam;

	CString strDst;
	CMFCControlContainer::UTF8ToString((LPSTR)pbInitData, strDst, dwSize);

	CTagManager tagManager(strDst);

	m_strMask = _T("");
	m_strValid.Empty();

	CString strValidChars;
	if (tagManager.ExcludeTag(PS_MFCMaskedEdit_ValidChars, strValidChars, TRUE))
	{
		SetValidChars(strValidChars);
	}

	return 0;
}

void CValidCharEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
   CEdit::OnKeyDown(nChar, nRepCnt, nFlags);

   if (nChar == VK_DELETE)
   {
      int nBeginOld, nEndOld;
      CEdit::GetSel(nBeginOld, nEndOld);

      DoUpdate(TRUE, nBeginOld, nEndOld);
   }
}
