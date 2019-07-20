#include "stdafx.h"
#include "DialogexMid.h"
#include "UserLocalText.h"
#ifdef USING_TAB_MANAGER
#include "TabStopManager.h"
#endif // USING_TAB_MANAGER

#ifdef USING_CONTROLS_PERMISSION
//���Ҫ��Ȩ�޵Ĺ������Ҫ�������ļ�
#include "DBControlsPermission.h"
#endif // USING_CONTROLS_PERMISSION

#ifdef USING_LIB_SQLITE //�����԰汾 yangjr2019/04/09
#include "SqliteDll/include/CLanguageConf.h"
#define COMBOITME_KEY_BASE   2000000	//�����������ֵ��ʼ---�Ѷ��壬���
#else
#endif // USING_LIB_SQLITE

///////////////////////////////////////////////

/*********************�����Ŀؼ�����*************************/
#ifndef CONTROL_TYPE_CEdit
#define  CONTROL_TYPE_CEdit _T("CEdit")
#endif

#ifndef CONTROL_TYPE_CCombox
#define  CONTROL_TYPE_CCombox _T("CCombox")
#endif

#ifndef CONTROL_TYPE_CCheckOrRadioButton
#define  CONTROL_TYPE_CCheckOrRadioButton _T("CCheckOrRadioButton")
#endif

#ifndef CONTROL_TYPE_CStatic
#define CONTROL_TYPE_CStatic _T("CStatic")
#endif



const CString C_STR_RECORD_POS_X = _T("PosX");	//����λ��X����
const CString C_STR_RECORD_POS_Y = _T("PosY");	//����λ��Y����
const CString C_STR_RECORD_SIZE_CX = _T("SizeCX");		//���ڴ�С
const CString C_STR_RECORD_SIZE_CY = _T("SizeCY");		//���ڴ�С
const CString C_STR_RECORD_MAXIMIZE_STATE = _T("MaxFlag");		//�������״̬
const CString C_STR_RECORD_MINIMIZE_STATE = _T("MinFlag");		//������С��״̬

CDialogExMid::CDialogExMid(UINT nIDD,CWnd* pParent /*=NULL*/)
#ifdef USING_LIB_BCGP
	: CBCGPDialog(nIDD, pParent)
{
	EnableVisualManagerStyle(TRUE,TRUE); 
#else
	: CDialogEx(nIDD, pParent)
{
#endif // USING_LIB_BCGP
   m_nDlgFlag = 0;
	m_nIDD = nIDD;
	m_bMoveParent = TRUE;//2017/05/23 zhangt Ĭ��TRUE ��ʾ�ƶ�������
   InitWndPosRecordVariable();

   m_bTranslateDlgTitle = TRUE;
   m_flagUsed = false;
   m_isAllwaysChangeWhenInit = false;
   m_isUINeedTranslate = true;
}

CDialogExMid::~CDialogExMid()
{
   ClearCtrlInfo();
}

#ifdef USING_LIB_BCGP
BEGIN_MESSAGE_MAP(CDialogExMid, CBCGPDialog)
#else
BEGIN_MESSAGE_MAP(CDialogExMid, CDialogEx)
#endif // USING_LIB_BCGP
	ON_MESSAGE(DM_GETDEFID,&CDialogExMid::OnGetDefID)
	ON_WM_LBUTTONDOWN()
	ON_WM_NCLBUTTONUP()
   ON_WM_INITMENU()
	ON_WM_INITMENUPOPUP()
   ON_WM_SIZE()
   ON_WM_DESTROY()
END_MESSAGE_MAP()

CDialogExMid *CDialogExMid::GetTopParentWindowAndChildIDDs(CDialogExMid *pCurDlg, std::deque<int> *pdeqChildIDDs)
{
   if (!pCurDlg)
      return nullptr;

   CDialogExMid *pTmp = pCurDlg;
   std::deque<int> vecChildIDDS;
   do 
   {
      if ((pTmp->GetStyle() | WS_CHILD) == 0)
      {
         //return pTmp;
         break;
      }

      CWnd *pParent = pTmp->GetParent();
      if (!pParent)
      {
         //return pTmp;
         break;
      }
      CDialogExMid *pParent2 = dynamic_cast<CDialogExMid *>(pParent);
      if (!pParent2)
      {
         //return pTmp;
         break;
      }
      vecChildIDDS.push_front((UINT)(UINT_PTR) pTmp->m_lpszTemplateName);
      pTmp = pParent2;
   } while (1);

   if (pdeqChildIDDs)
      pdeqChildIDDs->swap(vecChildIDDS);

   return pTmp;
}

CDialogExMid *CDialogExMid::GetTopParentWindowAndChildIDDs(std::deque<int> *pdeqChildIDDs)
{
   return GetTopParentWindowAndChildIDDs(this, pdeqChildIDDs);
}

CDialogExMid const *CDialogExMid::GetChildWindowByIDDs(const CDialogExMid *pWndParent, const std::deque<int> &deqIDDs)
{
   const CDialogExMid *pTempWnd = pWndParent;
   for (auto Iter = deqIDDs.begin(); Iter != deqIDDs.end(); ++Iter)
   {
      pTempWnd = CDialogExMid::GetChildWindowByIDD(pTempWnd, *Iter);
      if (!pTempWnd)
         return nullptr;
   }
   return pTempWnd;
}

CDialogExMid *CDialogExMid::GetChildWindowByIDD(const CDialogExMid *pWndParent, int nIDD)
{
   auto hWndChild = ::GetWindow(pWndParent->GetSafeHwnd(), GW_CHILD);

   HWND hWndTemp    = ::GetWindow(hWndChild, GW_HWNDFIRST);
   do
   {
      CWnd * pWndChild = CWnd::FromHandle(hWndTemp);
      if (pWndChild)
      {
         CDialogExMid *pWndChildBaseDialogue = dynamic_cast<CDialogExMid *>(pWndChild);
         if (pWndChildBaseDialogue && nIDD == (UINT)(UINT_PTR)pWndChildBaseDialogue->m_lpszTemplateName)
         {
            return pWndChildBaseDialogue;
         }
      }
   } while (NULL != (hWndTemp = ::GetWindow(hWndTemp, GW_HWNDNEXT)));

   return nullptr;
}

#ifdef USING_TAB_MANAGER
//ͨ��XML�����ļ��ƶ�����
BOOL CDialogExMid::LeaveFocusByXML(WPARAM wParamKey, CWnd *pControl)
{
   if (!pControl)
      return FALSE;

   HWND hControlWnd = pControl->GetSafeHwnd();
   if (!hControlWnd)
      return FALSE;

   int nID = ::GetDlgCtrlID(hControlWnd);
   CWnd *pParent = pControl->GetParent();
   if (!pParent)
      return FALSE;
   CDialogExMid *pParentBCG = dynamic_cast<CDialogExMid *>(pParent);
   if (!pParentBCG)
      return FALSE;

   CTabStopManager::CtrlID deqChildIDD;
   CDialogExMid *pTopParent = CDialogExMid::GetTopParentWindowAndChildIDDs(pParentBCG, &deqChildIDD);

   if (pTopParent)
   {
      int nTopDialogID = (UINT)(UINT_PTR) pTopParent->m_lpszTemplateName;
      deqChildIDD.push_back(nID);

      CTabStopManager::CCtrlInfo Info;
      CTabStopManager::Instance().GetTabInfo(nTopDialogID, deqChildIDD, wParamKey, &Info);
      if (!Info.m_sType.IsEmpty() && !CTabStopManager::Instance().CheckCanLeave(Info.m_sType, Info.m_sCondition, hControlWnd))
      {
         return FALSE;
      }

      CTabStopManager::CtrlID IDNext = CTabStopManager::Instance().GetNextTabID(nTopDialogID, deqChildIDD, wParamKey);
      while (!IDNext.empty() && IDNext != deqChildIDD)
      {
         CTabStopManager::CtrlID deqChildIDD = IDNext;
         deqChildIDD.pop_back(); //���һ������IDD�����ǿؼ�ID������Ҫȥ��
         const CDialogExMid *pTargetChild = GetChildWindowByIDDs(pTopParent, deqChildIDD);
         if (pTargetChild)
         {
            CWnd *pNextWnd = pTargetChild->GetDlgItem(IDNext.back());
            if (pNextWnd && pNextWnd->IsWindowVisible() && pNextWnd->IsWindowEnabled())
            {
               pTargetChild->SendMessage(WM_NEXTDLGCTL, (WPARAM)pNextWnd->GetSafeHwnd(), TRUE);
               //��������2�ν��㣬��Ȼ���button������ѡ��״̬������ɷ�ѡ��״̬
               ::PostMessage(pTargetChild->GetSafeHwnd(), WM_NEXTDLGCTL, (WPARAM)pNextWnd->GetSafeHwnd(), TRUE);
               return TRUE;
            }
         }
         IDNext = CTabStopManager::Instance().GetNextTabID(nTopDialogID, IDNext, wParamKey);
      }
   }

   return FALSE;
}
#endif /*USING_TAB_MANAGER*/

BOOL CDialogExMid::OnInitDialog()
{
   //���öԻ���λ��	
   SetWindowPosByRecord();
   if (m_bCenterWnd
      &&-5000 >= m_nWndPosX
      && -5000>=m_nWndPosY)
   {//���ھ�����ʾ
      CenterWindow();
   }
   if (ReadWindowMinimizeState())
   {
      ShowWindow(SW_MINIMIZE);
   }
   if(ReadWindowMaximizeState())
   {
      ShowWindow(SW_MAXIMIZE);
   }

#ifdef USING_TAB_MANAGER
   //ָ�����õĵ�һ���ؼ���ý���
   CTabStopManager::CtrlID deqChildIDD;
   auto *pTopParent = this;
   if (CTabStopManager::Instance().IsUseTopWindow())
      pTopParent = GetTopParentWindowAndChildIDDs(&deqChildIDD);
   if (pTopParent)
   {
      int nIndex = (UINT)(UINT_PTR) pTopParent->m_lpszTemplateName;

      CTabStopManager::CtrlID nID = CTabStopManager::Instance().GetFirstID(nIndex);
      if (!nID.empty())
      {
         CTabStopManager::CtrlID deqChildIDD = nID;
         deqChildIDD.pop_back(); //���һ������IDD�����ǿؼ�ID������Ҫȥ��
         const CDialogExMid *pTargetChild = GetChildWindowByIDDs(pTopParent, deqChildIDD);
         if (pTargetChild && pTargetChild == this)
         {
            CWnd *pWndNewFocus = GetDlgItem(nID.back());
            if (pWndNewFocus)
            {
               PostMessage(WM_NEXTDLGCTL, (WPARAM)pWndNewFocus->GetSafeHwnd(), TRUE);
            }
         }
      }
   }
#endif //USING_TAB_MANAGER

#ifdef USING_LIB_SQLITE //������԰汾
   if(m_isAllwaysChangeWhenInit || m_language != CLanguageConf::GetTheOne()->Get() || (! m_flagUsed))//�Ի���δ����ʼ���������Ը��Ĺ�������������������Ϣ
   {
      m_flagUsed = true;   OnLanguageChange();
      m_language = CLanguageConf::GetTheOne()->Get();
   } 
#else
#endif // USING_LIB_SQLITE

#ifdef USING_LIB_BCGP
	if (m_bMoveParent)
	{
		EnableDragClientArea(TRUE);
	}
	return CBCGPDialog::OnInitDialog();
#else
	return CDialogEx::OnInitDialog();
#endif // USING_LIB_BCGP	
}

LRESULT CDialogExMid::OnGetDefID(WPARAM wParam,LPARAM lParam) //��ֹ�ڶԻ����а�Enter���Ի�����ʧ
{  
	return MAKELONG(0,DC_HASDEFID);    
}  

BOOL CDialogExMid::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam==VK_ESCAPE)//Esc
		{
			return TRUE;
		}
	}

#ifdef USING_TAB_MANAGER
   //tab��˳�����
   if (pMsg->message == WM_KEYDOWN)
   {
      if (pMsg->hwnd)
      {
         int nID = ::GetDlgCtrlID(pMsg->hwnd);
         if (nID == 1001) //combobox �ڲ���edit�ؼ�����Ҫ���⴦�����ҵ�combobox���ڣ����ҵ���ӦID
         {
            HWND hParent = ::GetParent(pMsg->hwnd);
            if (hParent)
            {
               CWnd * pWndChild = CWnd::FromHandle(hParent);
               if (pWndChild)
               {
                  CComboBox *pComboBox = dynamic_cast<CComboBox *>(pWndChild);
                  if (pComboBox)
                  {
                     nID = ::GetDlgCtrlID(hParent);
                  }
               }
            }
         }

         CTabStopManager::CtrlID deqChildIDD;
         auto *pTopParent = this;
         if (CTabStopManager::Instance().IsUseTopWindow())
            pTopParent = GetTopParentWindowAndChildIDDs(&deqChildIDD);
         if (pTopParent)
         {
            int nTopDialogID = (UINT)(UINT_PTR) pTopParent->m_lpszTemplateName;
            deqChildIDD.push_back(nID);

            CTabStopManager::CCtrlInfo Info;
            CTabStopManager::Instance().GetTabInfo(nTopDialogID, deqChildIDD, pMsg->wParam, &Info);
            if (!Info.m_sType.IsEmpty() && !CTabStopManager::Instance().CheckCanLeave(Info.m_sType, Info.m_sCondition, pMsg->hwnd))
            {
#ifdef USING_LIB_BCGP
               return CBCGPDialog::PreTranslateMessage(pMsg);
#else
               return CDialogEx::PreTranslateMessage(pMsg);
#endif // USING_LIB_BCGP	
            }

            CTabStopManager::CtrlID IDNext = CTabStopManager::Instance().GetNextTabID(nTopDialogID, deqChildIDD, pMsg->wParam);
            while (!IDNext.empty() && IDNext != deqChildIDD)
            {
               CTabStopManager::CtrlID deqChildIDD = IDNext;
               deqChildIDD.pop_back(); //���һ������IDD�����ǿؼ�ID������Ҫȥ��
               const CDialogExMid *pTargetChild = GetChildWindowByIDDs(pTopParent, deqChildIDD);
               if (pTargetChild)
               {
                  CWnd *pNextWnd = pTargetChild->GetDlgItem(IDNext.back());
                  if (pNextWnd && pNextWnd->IsWindowVisible() && pNextWnd->IsWindowEnabled())
                  {
                     HWND hNextHWND = pNextWnd->GetSafeHwnd();
                     pTargetChild->SendMessage(WM_NEXTDLGCTL, (WPARAM)hNextHWND, TRUE);
                     //��������2�ν��㣬��Ȼ���button������ѡ��״̬������ɷ�ѡ��״̬
                     ::PostMessage(pTargetChild->GetSafeHwnd(), WM_NEXTDLGCTL, (WPARAM)hNextHWND, TRUE);

                     CTabStopManager::CCtrlInfo Info;
                     CTabStopManager::Instance().GetTabInfo(nTopDialogID, IDNext, pMsg->wParam, &Info);
                     if (!Info.m_sType.IsEmpty())
                     {
                        CTabStopManager::Instance().DoOnEnter(Info.m_sType, Info.m_sOnEnter, hNextHWND);
                     }

                     return TRUE;
                  }
               }
               IDNext = CTabStopManager::Instance().GetNextTabID(nTopDialogID, IDNext, pMsg->wParam);
            }
         }
      }
   }
#endif //USING_TAB_MANAGER
#ifdef USING_LIB_BCGP
	return CBCGPDialog::PreTranslateMessage(pMsg);
#else
	return CDialogEx::PreTranslateMessage(pMsg);
#endif // USING_LIB_BCGP	
}

#ifdef USING_LIB_BCGP
void CDialogExMid::SetActiveMenu(CBCGPPopupMenu* pMenu)
#else
void CDialogExMid::SetActiveMenu(CMFCPopupMenu* pMenu)
#endif // USING_LIB_BCGP	
{
#ifdef USING_LIB_BCGP
   CBCGPDialog::SetActiveMenu(pMenu);
#else
   CDialogEx::SetActiveMenu(pMenu);
#endif // USING_LIB_BCGP

   if (NULL != pMenu)
   {
/*
#ifdef USING_CONTROLS_PERMISSION
      CDBControlsPermissionList::Instance()->HandleWindowMenuControlPermission(pMenu,m_nIDD,m_nDlgFlag);
#endif // USING_CONTROLS_PERMISSION*/
   }
}

void CDialogExMid::OnInitMenu(CMenu* pMenu)
{
#ifdef USING_LIB_BCGP
   return CBCGPDialog::OnInitMenu(pMenu);
#else
   return CDialogEx::OnInitMenu(pMenu);
#endif // USING_LIB_BCGP	
}

void CDialogExMid::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

#ifdef USING_LIB_BCGP

	CBCGPDialog::OnLButtonDown(nFlags, point);

#else
	if (m_bMoveParent)
	{
		//2016-05-25 �Ի�������ط����϶��Ի���
		HWND hWnd = GetSafeHwnd();
		while (hWnd != NULL)
		{
			LONG lStyle = ::GetWindowLong(hWnd,GWL_STYLE);
			//WS_CHILD �Ӵ���(������WS_POPUP����) 
			if ((lStyle & WS_CHILD) == WS_CHILD)
			{
				hWnd = ::GetParent(hWnd);
			}
			//WS_DLGFRAME ���Ի���߿���ʽ,��������� ����һ��Ի���ķ�񣬵�û�б�����
			else if (((lStyle & WS_DLGFRAME) == WS_DLGFRAME)||((lStyle & WS_POPUP) == WS_POPUP))
			{
				::PostMessage(hWnd,WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));
				break;//����ѭ��
			}
			else
			{
				hWnd = ::GetParent(hWnd);
			}
		}//2016-05-25_end
	}
	CDialogEx::OnLButtonDown(nFlags, point);
#endif // USING_LIB_BCGP
}

void CDialogExMid::OnNcLButtonUp(UINT nHitTest, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	TRACE(_T("CDialogExMid::OnNcLButtonUp\n"));

#ifdef USING_LIB_BCGP
	CBCGPDialog::OnNcLButtonUp(nHitTest, point);
#else
	CDialogEx::OnNcLButtonUp(nHitTest, point);
#endif // USING_LIB_BCGP
}


void CDialogExMid::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
#ifdef USING_LIB_BCGP
	CBCGPDialog::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
#else
	CDialogEx::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
#endif // USING_LIB_BCGP	

	// TODO: �ڴ˴������Ϣ����������
	ASSERT(pPopupMenu != NULL);
	// Check the enabled state of various menu items.
	CCmdUI state;
	state.m_pMenu = pPopupMenu;
	ASSERT(state.m_pOther == NULL);
	ASSERT(state.m_pParentMenu == NULL);
	// Determine if menu is popup in top-level menu and set m_pOther to
	// it if so (m_pParentMenu == NULL indicates that it is secondary popup).
	HMENU hParentMenu;
	if (AfxGetThreadState()->m_hTrackingMenu == pPopupMenu->m_hMenu)
		state.m_pParentMenu = pPopupMenu;    // Parent == child for tracking popup.
	else if ((hParentMenu = ::GetMenu(m_hWnd)) != NULL)
	{
		CWnd* pParent = this;
		// Child windows don't have menus--need to go to the top!
		if (pParent != NULL &&(hParentMenu = ::GetMenu(pParent->m_hWnd)) != NULL)
		{
			int nIndexMax = ::GetMenuItemCount(hParentMenu);
			for (int nIndex = 0; nIndex < nIndexMax; nIndex++)
			{
				if (::GetSubMenu(hParentMenu, nIndex) == pPopupMenu->m_hMenu)
				{
					// When popup is found, m_pParentMenu is containing menu.
					state.m_pParentMenu = CMenu::FromHandle(hParentMenu);
					break;
				}
			}
		}
	}
	state.m_nIndexMax = pPopupMenu->GetMenuItemCount();
	for (state.m_nIndex = 0; state.m_nIndex < state.m_nIndexMax;
		state.m_nIndex++)
	{
		state.m_nID = pPopupMenu->GetMenuItemID(state.m_nIndex);
		if (state.m_nID == 0)
			continue; // Menu separator or invalid cmd - ignore it.
		ASSERT(state.m_pOther == NULL);
		ASSERT(state.m_pMenu != NULL);
		if (state.m_nID == (UINT)-1)
		{
			// Possibly a popup menu, route to first item of that popup.
			state.m_pSubMenu = pPopupMenu->GetSubMenu(state.m_nIndex);
			if (state.m_pSubMenu == NULL ||
				(state.m_nID = state.m_pSubMenu->GetMenuItemID(0)) == 0 ||
				state.m_nID == (UINT)-1)
			{
				continue;       // First item of popup can't be routed to.
			}
			state.DoUpdate(this, TRUE);   // Popups are never auto disabled.
		}
		else
		{
			// Normal menu item.
			// Auto enable/disable if frame window has m_bAutoMenuEnable
			// set and command is _not_ a system command.
			state.m_pSubMenu = NULL;
			state.DoUpdate(this, FALSE);
		}
		// Adjust for menu deletions and additions.
		UINT nCount = pPopupMenu->GetMenuItemCount();
		if (nCount < state.m_nIndexMax)
		{
			state.m_nIndex -= (state.m_nIndexMax - nCount);
			while (state.m_nIndex < nCount &&
				pPopupMenu->GetMenuItemID(state.m_nIndex) == state.m_nID)
			{
				state.m_nIndex++;
			}
		}
		state.m_nIndexMax = nCount;


#ifdef USING_CONTROLS_PERMISSION
      //���������Ȩ�������б��� ����øò˵���
      if(CDBControlsPermissionList::Instance()->HasItemInControlPermission(m_nIDD,m_nDlgFlag,pPopupMenu->GetMenuItemID(state.m_nIndex),CDBControlsPermissionData::en_Control_Menu))
      {
         pPopupMenu->EnableMenuItem(state.m_nIndex,MF_BYPOSITION|MF_GRAYED);
      }
#endif // USING_CONTROLS_PERMISSION
	}
}

void CDialogExMid::OnSize(UINT nType, int cx, int cy)
{
#ifdef USING_LIB_BCGP

   // onsize�Ժ��ӿؼ�û�յ�paint��Ϣ���� ���ǻ�����˸ 2018-6-20 wangzl
   Invalidate(FALSE);


   CBCGPDialog::OnSize(nType,cx,cy);

   AdjustControlsLayout();

#else
   CDialogEx::OnSize(nType,cx,cy);
#endif // USING_LIB_BCGP

   CRect rt;
   GetClientRect(rt);
   ResizeCtrl(rt);
}

//���ļ��л�ȡ����ˢ�¿ؼ�ֵ yangjr 2017-12-14
void CDialogExMid::RefreshDefValue(int index)
{
   ASSERT(IsWindow(GetSafeHwnd()));
   CUserCtrlDefValueList *pList = CUserCtrlDefValueList::Instance();
   CUserCtrlDefValue *pData = pList->GetItem(index);
   if (pData)
   {
      int nCtrlID = pData->m_nCtrlID;
      CString strText = pData->m_strDefValue;
      CWnd *pWnd = GetDlgItem(nCtrlID);			
      if (nCtrlID>0 && pWnd)
      {
         if (pWnd->IsKindOf(RUNTIME_CLASS(CEdit)) && CONTROL_TYPE_CEdit== pData->m_strCtrlType) 
         {
            pWnd->SetWindowText(strText);
         }
         else if((pWnd->IsKindOf(RUNTIME_CLASS(CComboBox))||pWnd->IsKindOf(RUNTIME_CLASS(CRichEditCtrl))) && CONTROL_TYPE_CCombox== pData->m_strCtrlType)
         {
         #ifdef USING_LIB_BCGP
            CBCGPComboBox *pCbo = (CBCGPComboBox*)pWnd;
         #else
            CComboBox *pCbo = (CComboBox*)pWnd;
         #endif
            DWORD dwStyle = pCbo->GetStyle();
            if(CBS_DROPDOWNLIST == (dwStyle &  CBS_DROPDOWNLIST))
            {
				int nCount = pCbo->GetCount();
               int nSel = -1;
               if (strText.IsEmpty())
               {
                  pCbo->SetCurSel(nSel);
               }
               else
               {
                  CString strTmp = _T("");
                  for (int i=0;i<nCount;i++)
                  {
                     pCbo->GetLBText(i,strTmp);
                     if (strTmp == strText)
                     {
                        nSel = i;
                        break;
                     }
                  }
                  pCbo->SetCurSel(nSel);
               }
			   if (nCount>0 && pCbo->GetCurSel()==-1) pCbo->SetCurSel(0);
            }
            else
            {
               pCbo->SetWindowText(strText);
            }
         }
         else if(pWnd->IsKindOf(RUNTIME_CLASS(CButton))  && CONTROL_TYPE_CCheckOrRadioButton== pData->m_strCtrlType)
         {			
#ifdef USING_LIB_BCGP
            CBCGPButton *pCheck = (CBCGPButton*)pWnd;	
            if (pCheck->IsCheckBox() ||pCheck->IsRadioButton())
#else
            CButton *pCheck = (CButton*)pWnd;	
            DWORD dwStyle = pCheck->GetButtonStyle();//GetWindowLong(pCheck->GetSafeHwnd(), GWL_STYLE);
               dwStyle = dwStyle & SS_TYPEMASK;//BS_TYPEMASK
            if (BS_CHECKBOX==dwStyle || BS_RADIOBUTTON==dwStyle)
#endif // USING_LIB_BCGP			
            {	
               if (strText == _T("1"))
               {
                  pCheck->SetCheck(BST_CHECKED);
               }
               else if (strText == _T("2"))
               {
                  pCheck->SetCheck(BST_INDETERMINATE);
               }
               else
               {
                  pCheck->SetCheck(BST_UNCHECKED);
               }
            }
            else
            {
               //pWnd->SetWindowText(strText); //�������²�Ҫȥˢ���ı�����Ȼ���׵���checkbox���ı���仯 yangjr 2018/12/7
            }
         }
         else if(pWnd->IsKindOf(RUNTIME_CLASS(CStatic))
            && CONTROL_TYPE_CStatic== pData->m_strCtrlType)
         {
            pWnd->SetWindowText(strText);
         }
      }
   } 
}

CString CDialogExMid::GetDefValueByID(UINT nCtrlID)
{
	CString strDefValue = _T("");

	if (nCtrlID > 0)
	{
		CUserCtrlDefValueList *pList = CUserCtrlDefValueList::Instance();
		strDefValue = pList->FindDefVaule(m_nIDD,nCtrlID);
	}

	return strDefValue;
}

void CDialogExMid::OnDestroy()
{
   //�������λ�� wangzl 2019-3-11
   GetWindowPosRecord();

/*	CWnd *pWnd = this->GetWindow(GW_CHILD);
	while(pWnd) 
	{ 
		if (::IsWindow(pWnd->GetSafeHwnd()))
		{
			int nChildID = pWnd->GetDlgCtrlID();
			TCHAR szClass[128]; 
			GetClassName(pWnd-> m_hWnd, szClass, sizeof(szClass)); 
			if(lstrcmpi(szClass, _T("edit")) == 0)	
			{
				CString strText = _T("");
				pWnd->GetWindowText(strText);
				OutputDebugString(strText);
				TRACE(strText+_T(":%d-%d\n"),m_nIDD,nChildID);
			}
		}

		pWnd = pWnd->GetWindow(GW_HWNDNEXT); 		
	}
*/
	//����״ֵ̬
	CUserCtrlDefValueList *pList = CUserCtrlDefValueList::Instance();
   
	for(int i=0;i<pList->GetCount();i++)
	{
		CUserCtrlDefValue *pData = pList->GetItem(i);
		if (pData && (pData->m_nDlgID==m_nIDD))
		{
			int nCtrlID = pData->m_nCtrlID;
			CWnd *pWnd = GetDlgItem(nCtrlID);
			if (nCtrlID>0 && pWnd)
			{
				if (pWnd->IsKindOf(RUNTIME_CLASS(CEdit)) || pWnd->IsKindOf(RUNTIME_CLASS(CRichEditCtrl))) 
				{
					CString strText = _T("");
					pWnd->GetWindowText(strText);
					pList->AddDefVaule(m_nIDD,nCtrlID,strText,CONTROL_TYPE_CEdit);
				}
				else if(pWnd->IsKindOf(RUNTIME_CLASS(CComboBox)))
				{
					CString strText = _T("");
					pWnd->GetWindowText(strText);
					pList->AddDefVaule(m_nIDD,nCtrlID,strText,CONTROL_TYPE_CCombox);
				}
				else if(pWnd->IsKindOf(RUNTIME_CLASS(CButton)))
				{
					CString strText = _T("");
					pWnd->GetWindowText(strText);
#ifdef USING_LIB_BCGP
					CBCGPButton *pCheck = (CBCGPButton*)pWnd;	
					if (pCheck->IsCheckBox() ||pCheck->IsRadioButton())
#else
					CButton *pCheck = (CButton*)pWnd;	
					DWORD dwStyle = pCheck->GetButtonStyle();//GetWindowLong(pCheck->GetSafeHwnd(), GWL_STYLE);
						dwStyle = dwStyle & SS_TYPEMASK;//BS_TYPEMASK
					if (BS_CHECKBOX==dwStyle || BS_RADIOBUTTON==dwStyle)
#endif // USING_LIB_BCGP			
					{					
						if(BST_CHECKED == pCheck->GetCheck())
						{
							strText = _T("1");
						}
                  else if (BST_INDETERMINATE == pCheck->GetCheck())
                  {
                     strText = _T("2");
                  }
						else
						{
							strText = _T("0");
						}
					}
					pList->AddDefVaule(m_nIDD,nCtrlID,strText,CONTROL_TYPE_CCheckOrRadioButton);	
				}
            else if(pWnd->IsKindOf(RUNTIME_CLASS(CStatic)))
            {
               CString strText = _T("");
               pWnd->GetWindowText(strText);
               pList->AddDefVaule(m_nIDD,nCtrlID,strText,CONTROL_TYPE_CStatic);
            }
			}
		}
	}

   ClearCtrlInfo();

#ifdef USING_LIB_BCGP  
	CBCGPDialog::OnDestroy();
#else
   CDialogEx::OnDestroy();
#endif
	// TODO: �ڴ˴������Ϣ����������
}

//��ȡ��Ӧ�ؼ�id�Ŀؼ�����
CString CDialogExMid::GetControlType(UINT nCtrlID)
{
   ASSERT(nCtrlID>0);
   CWnd *pWnd = GetDlgItem(nCtrlID);
   CString strControlType = _T("");
   if (nCtrlID>0 && pWnd)
   {
      if (pWnd->IsKindOf(RUNTIME_CLASS(CEdit))) 
      {
         strControlType = CONTROL_TYPE_CEdit;
      }else if(pWnd->IsKindOf(RUNTIME_CLASS(CComboBox)))
      {
         strControlType = CONTROL_TYPE_CCombox;
      }else if(pWnd->IsKindOf(RUNTIME_CLASS(CButton)))
      {
#ifdef USING_LIB_BCGP
         CBCGPButton *pCheck = (CBCGPButton*)pWnd;	
         //if (pCheck->IsCheckBox() ||pCheck->IsRadioButton())
#else
         CButton *pCheck = (CButton*)pWnd;	
         //DWORD dwStyle = pCheck->GetButtonStyle()//GetWindowLong(pCheck->GetSafeHwnd(), GWL_STYLE);
         //   dwStyle = dwStyle & SS_TYPEMASK;//BS_TYPEMASK
         //if (BS_CHECKBOX==dwStyle || BS_RADIOBUTTON==dwStyle)
#endif // USING_LIB_BCGP	
         {
            strControlType = CONTROL_TYPE_CCheckOrRadioButton;
         }
      }
      else if (pWnd->IsKindOf(RUNTIME_CLASS(CStatic)))
      {
         strControlType = CONTROL_TYPE_CStatic;
      }
   }
   return strControlType;
}

BOOL CDialogExMid::RegDefValueByID(UINT nCtrlID,CString strDefText)
{
   BOOL bRet = TRUE;

   if (nCtrlID > 0)
   {
      CUserCtrlDefValueList *pList = CUserCtrlDefValueList::Instance();
      CString strControlType = GetControlType(nCtrlID);
      int index = pList->FindDefVauleSel(m_nIDD,nCtrlID,strControlType);      
      if (-1 == index)//֮ǰû��ע�������ע�� yangjr 2017-12-14
      {
         pList->AddDefVaule(m_nIDD,nCtrlID,strDefText,strControlType);
         index = 0;//��Ϊ0  ������AddDefVaule�Ǵ�AddHead
      }

      RefreshDefValue(index);
   }

   return bRet;
}

BOOL CDialogExMid::AddCtrlInfo(ctrl_info* p_ctl)
{
   if (p_ctl != NULL 
      && p_ctl->m_hwnd != nullptr 
      && p_ctl->m_iRow >=0 
      && IsWindow(p_ctl->m_hwnd))
   {
      auto itr_row = m_map_ctrl_info.find(p_ctl->m_iRow);
      if (itr_row == m_map_ctrl_info.end())
      {
         map<int,ctrl_info*> map_index;
         m_map_ctrl_info.insert(make_pair(p_ctl->m_iRow,map_index));
         itr_row = m_map_ctrl_info.find(p_ctl->m_iRow);
      }

      if (p_ctl->m_iIndex < 0)   //������˳���Զ�����
      {
         itr_row->second.insert(make_pair(itr_row->second.size(),p_ctl));
      }
      else
      {
         auto itr_index = itr_row->second.find(p_ctl->m_iIndex);
         if (itr_index == itr_row->second.end())
         {
            itr_row->second.insert(make_pair(p_ctl->m_iIndex,p_ctl));
         }
         else
         {
            TRACE(_T("�ظ���index"));
            return FALSE;
         }
      }

   }
   else
   {
      TRACE(_T("big mistake"));
      return FALSE;
   }

   return TRUE;
}

BOOL CDialogExMid::AddCtrlInfo(HWND hwnd,int irow,int index,int width,int height,int ideltx,int idelty,float iXBeilv,float iYBeilv)
{
   ctrl_info* p_ctrl = new ctrl_info;
   p_ctrl->m_hwnd = hwnd;
   p_ctrl->m_iRow = irow;
   p_ctrl->m_iWidth = width;
   p_ctrl->m_iHeight = height;
   p_ctrl->m_ideltx = ideltx;
   p_ctrl->m_idelty = idelty;
   p_ctrl->m_iIndex = index;
   p_ctrl->m_iuse_rt_width = width;
   p_ctrl->m_iuse_rt_height = height;
   if (iXBeilv<0)
   {
      iXBeilv  = 1;
   }
   if (iYBeilv<0)
   {
      iYBeilv  = 1;
   }
   p_ctrl->m_iXBeilv = iXBeilv;
   p_ctrl->m_iYBeilv = iYBeilv;
   if (FALSE == AddCtrlInfo(p_ctrl))
   {
      delete p_ctrl;
      p_ctrl = NULL;
      return FALSE;
   }
   else
      return TRUE;
}

BOOL CDialogExMid::AddCtrlInfo_auto_sort(HWND hwnd,int irow,int width,int height,int ideltx /*= 0*/,int idelty /*= 0*/,float iXBeilv,float iYBeilv)
{
   ctrl_info* p_ctrl = new ctrl_info;
   p_ctrl->m_hwnd = hwnd;
   p_ctrl->m_iRow = irow;
   p_ctrl->m_iWidth = width;
   p_ctrl->m_iHeight = height;
   p_ctrl->m_ideltx = ideltx;
   p_ctrl->m_idelty = idelty;
   p_ctrl->m_iIndex = -1;
   p_ctrl->m_iuse_rt_width = width;
   p_ctrl->m_iuse_rt_height = height;
   if (iXBeilv<0)
   {
      iXBeilv  = 1;
   }
   if (iYBeilv<0)
   {
      iYBeilv  = 1;
   }
   p_ctrl->m_iXBeilv = iXBeilv;
   p_ctrl->m_iYBeilv = iYBeilv;
   if (FALSE == AddCtrlInfo(p_ctrl))
   {
      delete p_ctrl;
      p_ctrl = NULL;
      return FALSE;
   }
   else
      return TRUE;
}

BOOL CDialogExMid::ReplaceCtrlInfo(int irow_old,int index_old,HWND hwnd_new,int width_new,int height_new,int ideltx_new /*= 0*/,int idelty_new /*= 0*/,float iXBeilv,float iYBeilv)
{
   if (iXBeilv<0)
   {
      iXBeilv  = 1;
   }
   if (iYBeilv<0)
   {
      iYBeilv  = 1;
   }
   
   auto itr_row = m_map_ctrl_info.find(irow_old);
   if (itr_row != m_map_ctrl_info.end())
   {
      auto itr_index = itr_row->second.find(index_old);
      if (itr_index != itr_row->second.end())
      {
         ctrl_info* p_ctrl = itr_index->second;
         if (p_ctrl == NULL)
         {
            p_ctrl = new ctrl_info;           
         }
         p_ctrl->m_hwnd = hwnd_new;
         p_ctrl->m_iRow = irow_old;
         p_ctrl->m_iWidth = width_new;
         p_ctrl->m_iHeight = height_new;
         p_ctrl->m_ideltx = ideltx_new;
         p_ctrl->m_idelty = idelty_new;
         p_ctrl->m_iIndex = index_old;
         p_ctrl->m_iuse_rt_width = width_new;
         p_ctrl->m_iuse_rt_height = height_new;
         p_ctrl->m_iXBeilv = iXBeilv;
         p_ctrl->m_iYBeilv = iYBeilv;
         return TRUE;
      }
   }
   else
   {
      return FALSE;
   }
   return FALSE;
}

BOOL CDialogExMid::ReplaceCtrlInfo(HWND hwnd_old,HWND hwnd_new,int width_new /*= -1*/,int height_new /*= -1*/,int ideltx_new /*= -1*/,int idelty_new /*= -1*/,float iXBeilv,float iYBeilv)
{
   if (iXBeilv<0)
   {
      iXBeilv  = 1;
   }
   if (iYBeilv<0)
   {
      iYBeilv  = 1;
   }
   for (auto itr_row = m_map_ctrl_info.begin(); itr_row != m_map_ctrl_info.end(); ++itr_row)
   {
      for (auto itr_index = itr_row->second.begin(); itr_index != itr_row->second.end();++itr_index)
      {
         ctrl_info* p_ctrl = itr_index->second;
         if (p_ctrl != NULL)
         {
            if ( p_ctrl->m_hwnd == hwnd_old)
            {
               p_ctrl->m_hwnd = hwnd_new;
               if (width_new != ctrl_info::iUseOldSize)
               { 
                  p_ctrl->m_iWidth = width_new; 
                  if (width_new == ctrl_info::ilast_width)
                  {
                      p_ctrl->m_iXBeilv = iXBeilv;
                  }
               }            
               
               if (height_new != ctrl_info::iUseOldSize)
               { 
                  p_ctrl->m_iHeight = height_new;
                  if (height_new == ctrl_info::ilast_height)
                  {
                     p_ctrl->m_iYBeilv = iYBeilv;
                  }
               }
               if (ideltx_new != ctrl_info::iUseOldSize){ p_ctrl->m_ideltx = ideltx_new;}
               if (idelty_new != ctrl_info::iUseOldSize){ p_ctrl->m_idelty = idelty_new;}

               return TRUE;
            }
         }   
      }
   }
   return FALSE;
}


void CDialogExMid::ClearCtrlInfo()
{
   //add by lida 2018/05/17
   for (auto itr_row = m_map_ctrl_info.begin(); itr_row != m_map_ctrl_info.end(); ++itr_row)
   {
      for (auto itr_index = itr_row->second.begin(); itr_index != itr_row->second.end(); ++itr_index)
      {
         if (itr_index->second != NULL)
         {
            delete itr_index->second;
            itr_index->second = NULL;
         }
      }
   }
   m_map_ctrl_info.clear();
}

void CDialogExMid::ResizeCtrl(const CRect rt)
{
   if (m_map_ctrl_info.size() <= 0)
      return;

   CRect rt_tmp(rt);

   for (auto itr_row = m_map_ctrl_info.begin(); itr_row != m_map_ctrl_info.end(); ++itr_row)
   {
      int irow_max_height = 0;
      rt_tmp.left = rt.left;
      rt_tmp.right = rt.right;
      rt_tmp.bottom = rt.bottom;
      for (auto itr_index = itr_row->second.begin(); itr_index != itr_row->second.end(); ++itr_index)
      {
         ctrl_info* p_ctrl = itr_index->second;
         if (p_ctrl && IsWindow(p_ctrl->m_hwnd) && FromHandlePermanent(p_ctrl->m_hwnd) != NULL && FromHandlePermanent(p_ctrl->m_hwnd)->GetStyle()&WS_VISIBLE)
         {
            if (p_ctrl->m_iuse_rt_width == ctrl_info::ilast_width)
            {
               p_ctrl->m_iWidth = rt_tmp.Width()*p_ctrl->m_iXBeilv-p_ctrl->m_ideltx;
            }

            if (p_ctrl->m_iuse_rt_height == ctrl_info::ilast_height)
            {
               p_ctrl->m_iHeight = rt_tmp.Height()*p_ctrl->m_iYBeilv-p_ctrl->m_idelty;
            }

            if (itr_index == itr_row->second.begin())    //ÿһ�еĵ�һ���ؼ�����֤ÿһ��������һ���ؼ�
            {
               CRect rt_ctrl(rt_tmp);
               rt_ctrl.top += p_ctrl->m_idelty;
               rt_ctrl.left += p_ctrl->m_ideltx;      //��߼��
               rt_ctrl.right = rt_ctrl.left + p_ctrl->m_iWidth;      //���
               rt_ctrl.bottom = rt_ctrl.top + p_ctrl->m_iHeight;    //�߶�
               FromHandlePermanent(p_ctrl->m_hwnd)->MoveWindow(rt_ctrl);

               rt_tmp.left = rt_ctrl.right;    //��һ�ؼ���߿�ʼλ��ƫ��
               if (irow_max_height < p_ctrl->m_iHeight + p_ctrl->m_idelty)
               {
                  irow_max_height = p_ctrl->m_iHeight + p_ctrl->m_idelty;      //��ǰ�����ĸ߶�
               }
            }
            else
            {
               BOOL bNew_row = FALSE;
               if (rt_tmp.Width() < p_ctrl->m_iWidth*0.8)    //�� 2��3��4��5......���ؼ�������Ŀ�Ȳ����Է��µ�ǰ�ؼ���ȵ�80%��������һ��
               {
                  rt_tmp.top += irow_max_height + ctrl_info::idelt_top;   //����һ��
                  rt_tmp.left = rt.left;                       //���λ�ûص���ʼλ��
                  bNew_row = TRUE;
               }

               CRect rt_ctrl(rt_tmp);
               if (FALSE == bNew_row)
               {
                  rt_ctrl.left += p_ctrl->m_ideltx;      //��߼��
               }

               rt_ctrl.top += p_ctrl->m_idelty;
               rt_ctrl.right = rt_ctrl.left + p_ctrl->m_iWidth;      //���
               rt_ctrl.bottom = rt_ctrl.top + p_ctrl->m_iHeight;    //�߶�
               FromHandlePermanent(p_ctrl->m_hwnd)->MoveWindow(rt_ctrl);

               rt_tmp.left = rt_ctrl.right;    //��һ�ؼ���߿�ʼλ��ƫ��
               if (irow_max_height < p_ctrl->m_iHeight + p_ctrl->m_idelty)
               {
                  irow_max_height = p_ctrl->m_iHeight + p_ctrl->m_idelty;      //��ǰ�����ĸ߶�
               }
            }
         }
      }
      rt_tmp.top += irow_max_height;
   }
}

void CDialogExMid::UpdateControlsPermission()
{
#ifdef USING_CONTROLS_PERMISSION
   CDBControlsPermissionList::Instance()->HandleWindowNormalControlPermission(this,m_nIDD,m_nDlgFlag);
#endif //USING_CONTROLS_PERMISSION
}

void CDialogExMid::InitWndPosRecordVariable()
{
   m_nWndPosX = 0;						//�Ի��򴰿�Xλ��
   m_nWndPosY = 0;						//�Ի��򴰿�Yλ��
   m_bIsRecordWndPos = false;			//��¼�Ի��򴰿�λ�ÿ��أ�Ĭ�ϲ�����
   m_strRecordWndPosCfgPath = _T("");	//��¼�Ի��򴰿�λ�õ������ļ�·��
   m_bIsRecordWndSize = false;			//�Ƿ��¼���ڴ�С
   m_nWndCx = -1;								//��¼���ڴ�С
   m_nWndCy = -1;								//��¼���ڴ�С
   m_bRecordMinimizeState = false;		//�Ƿ��¼��С��״̬
   m_bRecordMaximizeState = false;		//�Ƿ��¼���״̬	
   m_dwTickCount = 0;						//��¼��ʼ����ʱ���

   m_nDefaultWndCx = -1;					//Ĭ�ϴ��ڿ��
   m_nDefaultWndCy = -1;					//Ĭ�ϴ��ڸ߶�
}

bool CDialogExMid::ReadWindowPosCfg()
{   
   if (m_strRecordWndPosCfgPath.IsEmpty())
   {
      return false;
   }
   if (m_bIsRecordWndPos)
   {
      int nPosX = GetPrivateProfileInt(m_DlgName, C_STR_RECORD_POS_X,
         -5000, m_strRecordWndPosCfgPath);
      int nPosY = GetPrivateProfileInt(m_DlgName, C_STR_RECORD_POS_Y,
         -5000, m_strRecordWndPosCfgPath);

      m_nWndPosX = nPosX;
      m_nWndPosY = nPosY;
      if (-5000 == nPosX
         || -5000 == nPosY)
      {
         return false;
      }
   }
   
   if (m_bIsRecordWndSize)
   {
      if (0<=m_nDefaultWndCx
         && 0<=m_nDefaultWndCy)
      {
         m_nWndCx = GetPrivateProfileInt(m_DlgName, C_STR_RECORD_SIZE_CX,
            m_nDefaultWndCx, m_strRecordWndPosCfgPath);
         m_nWndCy = GetPrivateProfileInt(m_DlgName, C_STR_RECORD_SIZE_CY,
            m_nDefaultWndCy, m_strRecordWndPosCfgPath);
      }
      else
      {
         m_nWndCx = GetPrivateProfileInt(m_DlgName, C_STR_RECORD_SIZE_CX,
            -5000, m_strRecordWndPosCfgPath);
         m_nWndCy = GetPrivateProfileInt(m_DlgName, C_STR_RECORD_SIZE_CY,
            -5000, m_strRecordWndPosCfgPath);
      }
   }  

   return true;
}

void CDialogExMid::SaveWindowPosCfg()
{	
   if (m_strRecordWndPosCfgPath.IsEmpty())
   {
      return;
   }
   CString strTemp;
   if (m_bIsRecordWndPos)
   {
      strTemp.Format(_T("%d"), m_nWndPosX);
      WritePrivateProfileString(m_DlgName, C_STR_RECORD_POS_X,
         strTemp, m_strRecordWndPosCfgPath);
      strTemp.Format(_T("%d"), m_nWndPosY);
      WritePrivateProfileString(m_DlgName, C_STR_RECORD_POS_Y,
         strTemp, m_strRecordWndPosCfgPath);
   }
   
   if (m_bIsRecordWndSize)
   {
      strTemp.Format(_T("%d"), m_nWndCx);
      WritePrivateProfileString(m_DlgName, C_STR_RECORD_SIZE_CX,
         strTemp, m_strRecordWndPosCfgPath);
      strTemp.Format(_T("%d"), m_nWndCy);
      WritePrivateProfileString(m_DlgName, C_STR_RECORD_SIZE_CY,
         strTemp, m_strRecordWndPosCfgPath);
   }
}

void CDialogExMid::SetWindowPosByRecord()
{   
   bool bRe = ReadWindowPosCfg();
   if (!bRe)
   {
      return;
   }
   if (!m_bIsRecordWndPos)
   {
      CRect rtWnd;
      GetWindowRect(rtWnd);
      m_nWndPosX = rtWnd.left;
      m_nWndPosY = rtWnd.top;
   }
   if (!m_bIsRecordWndSize)
   {
      SetWindowPos(NULL, m_nWndPosX, m_nWndPosY, 0, 0, SWP_NOSIZE);
   }
   else
   {
      if (m_nWndCx<0
         ||m_nWndCy<0)
      {
         SetWindowPos(NULL, m_nWndPosX, m_nWndPosY, 0, 0, SWP_NOSIZE);
      }
      else
      {
         int nWndCx = m_nWndCx ;			
         int nWndCy = m_nWndCy ;			
         SetWindowPos(NULL, m_nWndPosX, m_nWndPosY, nWndCx, nWndCy, SWP_NOREDRAW);
      }
   }
}

void CDialogExMid::GetWindowPosRecord()
{
   CRect rtWnd;
   GetWindowRect(rtWnd);
   if (m_bIsRecordWndPos)
   {
      m_nWndPosX = rtWnd.left;
      m_nWndPosY = rtWnd.top;
   }  
   if (m_bIsRecordWndSize)
   {
      m_nWndCx = rtWnd.Width();
      m_nWndCy = rtWnd.Height();
   }
   SaveWindowPosCfg();
}

//��¼�������״̬
void CDialogExMid::SaveWindowMaximizeState()
{
   if (!m_bIsRecordWndPos)
   {
      return;
   }

   if (m_strRecordWndPosCfgPath.IsEmpty())
   {
      return;
   }
   CString strTemp;

   if (m_bRecordMaximizeState)
   {
      BOOL bMax = IsZoomed();
      strTemp.Format(_T("%d"), (int)bMax);
      WritePrivateProfileString(m_DlgName, C_STR_RECORD_MAXIMIZE_STATE,
         strTemp, m_strRecordWndPosCfgPath);
   }
}

//��ȡ�������״̬
bool CDialogExMid::ReadWindowMaximizeState()
{
   if (!m_bIsRecordWndPos)
   {
      return false;
   }
   if (m_strRecordWndPosCfgPath.IsEmpty())
   {
      return false;
   }
   if (!m_bRecordMaximizeState)
   {
      return false;
   }

   int nValue = GetPrivateProfileInt(m_DlgName, C_STR_RECORD_MAXIMIZE_STATE,
      0,	m_strRecordWndPosCfgPath);

   return nValue==0?false:true;
}

//��¼������С��״̬
void CDialogExMid::SaveWindowMinimizeState()
{
   if (!m_bIsRecordWndPos)
   {
      return;
   }

   if (m_strRecordWndPosCfgPath.IsEmpty())
   {
      return;
   }
   CString strTemp;

   if (m_bRecordMinimizeState)
   {
      BOOL bMin = IsIconic();
      strTemp.Format(_T("%d"), (int)bMin);
      WritePrivateProfileString(m_DlgName, C_STR_RECORD_MINIMIZE_STATE,
         strTemp, m_strRecordWndPosCfgPath);
   }
}

//��ȡ������С��״̬
bool CDialogExMid::ReadWindowMinimizeState()
{
   if (!m_bIsRecordWndPos)
   {
      return false;
   }
   if (m_strRecordWndPosCfgPath.IsEmpty())
   {
      return false;
   }
   if (!m_bRecordMinimizeState)
   {
      return false;
   }

   int nValue = GetPrivateProfileInt(m_DlgName, C_STR_RECORD_MINIMIZE_STATE,
      0,	m_strRecordWndPosCfgPath);

   return (nValue&0x01);
}
void CDialogExMid::EnableRecordWndPos(CString strRecordCfgPath,
   bool bRecord /*= true*/)
{
   m_strRecordWndPosCfgPath = strRecordCfgPath;
   m_bIsRecordWndPos = bRecord;
}

void CDialogExMid::EnableInitCenterWnd(bool bCenterWnd /*= true*/)
{
   m_bCenterWnd = bCenterWnd;
}

void CDialogExMid::EnableRecordWndSize(bool bRecordSize /*= true*/)
{
   m_bIsRecordWndSize = bRecordSize;
}

//����Ĭ�ϴ��ڴ�С		
void CDialogExMid::SetDefaultWndSize(int nWidth, int nHeight)
{
   m_nDefaultWndCx = nWidth;				//Ĭ�ϴ��ڿ��
   m_nDefaultWndCy = nHeight;				//Ĭ�ϴ��ڸ߶�
}

//������¼��С��״̬ �Ľӿ�		
void CDialogExMid::EnableRecordMinimizeState(bool bRecordMinimizeState /*= true*/)
{
   m_bRecordMinimizeState = bRecordMinimizeState;
}

//������¼���״̬		
void CDialogExMid::EnableRecordMaximizeState(bool bRecordMaximizeState /*= true*/)
{
   m_bRecordMaximizeState = bRecordMaximizeState;
}

void CDialogExMid::OnCancel()
{
   if (!IsIconic()
      &&!IsZoomed())
   {
      GetWindowPosRecord();
   }
   SaveWindowMaximizeState();
   SaveWindowMinimizeState();
#ifdef USING_LIB_BCGP
   CBCGPDialog::OnCancel();
#else  
   CDialogEx::OnCancel();
#endif
}

void CDialogExMid::OnClose()
{
   if (!IsIconic()
      &&!IsZoomed())
   {
      GetWindowPosRecord();
   }
   SaveWindowMaximizeState();
   SaveWindowMinimizeState();

#ifdef USING_LIB_BCGP
   CBCGPDialog::OnClose();
#else
   CDialogEx::OnClose();
#endif
}

void CDialogExMid::OnOK()
{
   if (!IsIconic()
      &&!IsZoomed())
   {
      GetWindowPosRecord();
   }
   SaveWindowMaximizeState();
   SaveWindowMinimizeState();
#ifdef USING_LIB_BCGP
   CBCGPDialog::OnOK();
#else
   CDialogEx::OnOK();
#endif
}

BOOL CDialogExMid::ShowWindow(int nCmdShow)
{
   if (SW_HIDE == nCmdShow)
   {
      if (!IsIconic()
         &&!IsZoomed())
      {
         GetWindowPosRecord();
      }
   }
#ifdef USING_LIB_BCGP
   return CBCGPDialog::ShowWindow(nCmdShow);
#else
   return CDialogEx::ShowWindow(nCmdShow);
#endif
}

void CDialogExMid::AddNewTranslationComboBoxID(UINT combID)
{
   m_mapNewComboTranslation.insert(std::make_pair(combID,combID));
}
void CDialogExMid::AddUnLanguageCTRLID(UINT combID)
{
   m_unLanguageCTRLID.insert(std::make_pair(combID,combID));
}
void CDialogExMid::ChangeLanguageWhenInit() 
{ 
   m_isAllwaysChangeWhenInit = true;
}
BOOL CDialogExMid::OnLanguageChange()
{
#ifdef USING_LIB_SQLITE
   if (!m_isUINeedTranslate)
   {
      return TRUE;
   }
   UINT   iComboIndex = COMBOITME_KEY_BASE;  //�����������ֵ

   CString s = _T("");

   DWORD id = 0;
   //����ı���
   GetWindowText(s);
   if (!s.IsEmpty() && m_bTranslateDlgTitle)
   {
      if (!m_LanTableName.IsEmpty())
      {
         CString  strTitleDlg = g_sql.Read(m_LanTableName, DIALOG_NAME_ID, s);
         SetWindowText(strTitleDlg);
      }
      else
         return FALSE;
   }

   HWND hChild = ::GetWindow(GetSafeHwnd(), GW_CHILD);
   CString text;
   while(NULL != hChild)
   {      
      id = GetWindowLongPtr(hChild, GWLP_ID);
      //�������ԵĿؼ�ID
      if(!m_unLanguageCTRLID.empty()&&m_unLanguageCTRLID.find(id)!= m_unLanguageCTRLID.end())
      {
         hChild = ::GetNextWindow(hChild, GW_HWNDNEXT);
         continue;
      }
      //�õ�����
      CString className;
      ::GetClassName(hChild, className.GetBuffer(20), 20);     


      //����CEdit���͵Ŀؼ�
      if (_T("Edit") == className)
      {
         hChild = ::GetNextWindow(hChild, GW_HWNDNEXT);
         continue;
      }
      //�õ�ʵ��
      CWnd * x = CWnd::FromHandle(hChild);

      if (_T("ComboBox") == className)
      {
         CComboBox * pComboBox = (CComboBox *)x;
         CString text;
         std::vector<CString> list;

         BOOL bNewTranslation = FALSE;
         if (!m_mapNewComboTranslation.empty()
            &&m_mapNewComboTranslation.find(id)!=m_mapNewComboTranslation.end())
         {
            bNewTranslation = TRUE;
         }
         int iCurSel = pComboBox->GetCurSel();		//��õ�ǰѡ�еĽ��

         int count = pComboBox->GetCount();
         for (int i = 0; i < count; ++i)
         {
            pComboBox->GetLBText(i, text);
            //���ComboBox���������ݷ��룬ƥ�䲻��ȷ������ by WangZY 2015/09/06
            //if ( bNewTranslation)
            //{
            // iComboIndex = i+id*10000;
            // list.push_back(g_sql.Read(m_LanTableName, iComboIndex, text));
            //}
            //else
            {
               list.push_back(g_sql.Read(m_LanTableName, iComboIndex++, text));
            }
         }

         pComboBox->ResetContent();

         for(int i = 0; i < count; ++i)
         {
            pComboBox->AddString(list[i]);
         }

         if (iCurSel != CB_ERR)
         {
            pComboBox->SetCurSel(iCurSel);
         }

         hChild = ::GetNextWindow(hChild, GW_HWNDNEXT);
         continue;
      }
      //һ��ؼ�����
      if (NULL != x)
      {
         x->GetWindowText(s);    
         if (!s.IsEmpty())
         {
            text = g_sql.Read(m_LanTableName, id, s);
            x->SetWindowText(text);
         }         
      }
      hChild = ::GetNextWindow(hChild, GW_HWNDNEXT);
   }
#else
#endif // USING_LIB_SQLITE
   return TRUE;
}
