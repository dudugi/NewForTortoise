// CMyTabCtrlEx.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyTabCtrlEx.h"
#include "../../QLSvrMgn.h"
#include "../TabDlg/TabDialog.h"


// CMyTabCtrlEx

IMPLEMENT_DYNAMIC(CMyTabCtrlEx, CMFCTabCtrl)

CMyTabCtrlEx::CMyTabCtrlEx()
{

}

CMyTabCtrlEx::~CMyTabCtrlEx()
{
}

void CMyTabCtrlEx::DoDataExchange(CDataExchange* pDX)
{
	CMFCTabCtrl::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyTabCtrlEx, CMFCTabCtrl)
	ON_COMMAND(IDM_CLOSE_CURTAB, &CMyTabCtrlEx::OnCloseCurTab)
	ON_COMMAND(IDM_CLOSE_OTHERTAB, &CMyTabCtrlEx::OnCloseOtherTab)
	ON_COMMAND(IDM_CLOSE_ALLTAB, &CMyTabCtrlEx::OnCloseAllTab)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_CONTEXTMENU()
	ON_WM_LBUTTONDBLCLK()
   ON_WM_SIZE()
END_MESSAGE_MAP()



// CCloseMFCTabCtrl ��Ϣ�������
BOOL CMyTabCtrlEx::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_COMMAND)
	{
		//2017/02/23 zhangt pPopup->TrackPopupMenu ����ӦON_COMMAND��Ӧ�ĺ��� ֻ��ͨ����Ϣ���ش���˵���Ϣ
		if (pMsg->wParam == IDM_CLOSE_CURTAB)
		{
			OnCloseCurTab();
		}
		else if (pMsg->wParam == IDM_CLOSE_OTHERTAB)
		{
			OnCloseOtherTab();
		}
		else if (pMsg->wParam == IDM_CLOSE_ALLTAB)
		{
			OnCloseAllTab();
		}
	}

	return CMFCTabCtrl::PreTranslateMessage(pMsg);
}

void CMyTabCtrlEx::OnCloseCurTab()
{
	int nSel = GetActiveTab();
	for (int i=1;i<GetTabsNum();i++)//��0����ǩ��ɾ��
	{
		if (i == nSel)
		{
			CWnd *pWnd = GetTabWnd(i);
			if ((pWnd != NULL)&&(pWnd->GetSafeHwnd()))
			{
				//pWnd->ShowWindow(SW_HIDE);
				//pWnd->DestroyWindow();
				//delete pWnd;
				//pWnd = NULL;

				//RemoveTab(i);

				//2017/07/31 zhangt
				SetRedraw(FALSE);
				SetActiveTab(i-1);//��Ӹþ䣬����Debug���Գ���
				RemoveTab(i);
				SetRedraw(TRUE);
				Invalidate(TRUE);

				CWnd *pWnd = GetTabWnd(i-1);
				if (NULL != pWnd && pWnd->GetSafeHwnd())
				{
					pWnd->Invalidate(TRUE);
				}//2017/07/31_end
			}

			break;
		}
	}
}

void CMyTabCtrlEx::OnCloseOtherTab()
{
	SetRedraw(FALSE);
	int nSel = GetActiveTab();
	MoveTab(nSel,1);//�ƶ�����1��λ��
	for (int i=GetTabsNum()-1;i>1;i--)//��0��1����ǩ��ɾ��
	{	
		CWnd *pWnd = GetTabWnd(i);
		if ((pWnd != NULL)&&(pWnd->GetSafeHwnd()))
		{
			//pWnd->ShowWindow(SW_HIDE);
			//pWnd->DestroyWindow();
			//delete pWnd;
			//pWnd = NULL;
			RemoveTab(i);
		}
	}
	SetRedraw(TRUE);
	Invalidate(TRUE);

	int nCurTab = GetActiveTab();
	CWnd *pWnd = GetTabWnd(nCurTab);
	if (NULL != pWnd && pWnd->GetSafeHwnd())
	{
		pWnd->Invalidate(TRUE);
	}
}

void CMyTabCtrlEx::OnCloseAllTab()
{
	SetRedraw(FALSE);
	SetActiveTab(0);//2017/07/31 zhangt ��Ӹþ䣬����Debug���Գ���
	for (int i=GetTabsNum()-1;i>0;i--)//��0����ǩ��ɾ��
	{	
		CWnd *pWnd = GetTabWnd(i);
		if ((pWnd != NULL)&&(pWnd->GetSafeHwnd()))
		{
			//pWnd->ShowWindow(SW_HIDE);
			//pWnd->DestroyWindow();
			//delete pWnd;
			//pWnd = NULL;
			RemoveTab(i);
		}
	}
	SetRedraw(TRUE);
	Invalidate(TRUE);

	int nCurTab = GetActiveTab();
	CWnd *pWnd = GetTabWnd(nCurTab);
	if (NULL != pWnd && pWnd->GetSafeHwnd())
	{
		pWnd->Invalidate(TRUE);
	}
}

void CMyTabCtrlEx::OnLButtonDown( UINT nFlags, CPoint point )
{
	int nPrevTab = GetActiveTab();

	CMFCTabCtrl::OnLButtonDown(nFlags, point);

	int nClickTab = GetTabFromPoint(point);

	m_bSameClick = !(nPrevTab == nClickTab);

	if (0 == nClickTab)
	{
		EnableActiveTabCloseButton(FALSE);
	}

	if (0 < nClickTab)
	{
		EnableActiveTabCloseButton(TRUE);
	}
}

void CMyTabCtrlEx::OnLButtonUp( UINT nFlags, CPoint point )
{
	ReleaseCapture();//2017/11/24 zhangt �ͷŽ���
	CMFCTabCtrl::OnLButtonUp(nFlags, point);

	if(m_rectCloseButton.PtInRect(point))
	{
		if (m_bSameClick)
		{
			return;
		}
		int nTab = GetActiveTab();
		if (nTab > 0)
		{
			/*CWnd * pWnd = GetTabWnd(nTab);
			pWnd->DestroyWindow();*/
			SetRedraw(FALSE);
			SetActiveTab(nTab-1);
			RemoveTab(nTab);
			SetRedraw(TRUE);
			// #5365  �رմ��ڶ�ʧ��������   ����   wangzl 2017-09-06
			Invalidate(TRUE);

			int nCurTab = GetActiveTab();
			CWnd *pWnd = GetTabWnd(nCurTab);
			if (NULL != pWnd && pWnd->GetSafeHwnd())
			{
				pWnd->Invalidate(TRUE);
			}

			/*int nActiveTab = GetActiveTab();
			SetActiveTab(nActiveTab);*/
		}

		int nTabNum = GetTabsNum();
		if (1 == nTabNum)
		{
			EnableActiveTabCloseButton(FALSE);
		}
	}
}


BOOL CMyTabCtrlEx::SetActiveTab(int iTab)
{

	int nPrevTab = GetActiveTab();

	if (iTab > 0)
	{
		EnableActiveTabCloseButton(TRUE);
	}
	else
	{
		EnableActiveTabCloseButton(FALSE);
	}

	return CMFCTabCtrl::SetActiveTab(iTab);
}


BOOL CMyTabCtrlEx::SetActiveTab(CWnd *pDialog,UINT nIDD,CString strCaption,WPARAM wpData/*=0*/)
{
	int nTabNum = GetTabsNum();

	if ((pDialog != NULL) && (::IsWindow(pDialog->GetSafeHwnd())))
	{
		for (int i=0;i<nTabNum;i++)
		{
			CWnd *pWnd = GetTabWnd(i);
			if (pWnd == pDialog)
			{
				MoveTab(i, nTabNum-1);
				SetActiveTab(nTabNum-1);
				pDialog->SetFocus();
				break;
			}
		}
	}
	else
	{
// 		if (nTabNum > 0)
// 			theApp.ShowLoading();

		if (pDialog->IsKindOf(RUNTIME_CLASS(CTabDialog)))
		{
			CTabDialog * pTabDlg = (CTabDialog *)pDialog;
			pTabDlg->Create(nIDD,this,wpData);//wpData
		}

		CRect rcTab;
		GetTabsRect(rcTab);
		ScreenToClient(rcTab);
		pDialog->MoveWindow(rcTab);
		//pDialog->ShowWindow(SW_SHOW);
		AddTab(pDialog,strCaption);
		SetActiveTab(nTabNum);

// 		if (nTabNum > 0)
// 			theApp.CloseLoading();

		pDialog->SetFocus();
	}

	return TRUE;
}

void CMyTabCtrlEx::SetTabsHeight()
{
	const int nImageHeight = m_sizeImage.cy <= 0 ? 0 : m_sizeImage.cy + 7; 
	m_nTabsHeight = (max(nImageHeight, afxGlobalData.GetTextHeight() + 12)); 
}

void CMyTabCtrlEx::OnContextMenu(CWnd* pWnd, CPoint point)
{
/*	CPoint pt = point;
	ScreenToClient(&pt);
 	int nClickTab = GetTabFromPoint(pt);

	if (nClickTab>-1)SetActiveTab(nClickTab);
	if ((nClickTab != 0) && (GetActiveTab() !=0))
	{
		CMenu popMenu;
		if (m_rectTabsArea.PtInRect(pt))
		{
			VERIFY(popMenu.LoadMenu(IDR_MENU_TABCTRL));
			CMenu* pPopup = popMenu.GetSubMenu(0);
			ASSERT(pPopup != NULL);
			

			pPopup->TrackPopupMenu( TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
			//theApp.OnShowCMFCPopupMenu(this,pPopup,point);
		}
	}*/
}

void CMyTabCtrlEx::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	OnCloseCurTab();

	CMFCTabCtrl::OnLButtonDblClk(nFlags, point);
}

void CMyTabCtrlEx::OnSize(UINT nType, int cx, int cy)
{
   //


   CMFCTabCtrl::OnSize(nType,cx,cy);
}