// dlg1.cpp : 实现文件
//

#include "stdafx.h"
#include "DlgCommonChatContent.h"
#include "afxdialogex.h"
#include <iterator>
#include <algorithm>
#include <vector>
#include "FrequentlyChatContentFile.h"
//参考 IDD_COMMON_CHAT_CONTENT

enum
{
   BACKGROUND_COLOR = RGB(255, 255, 255),
   FRAME_COLOR = RGB(130, 135, 144),
   DELETE_CONFIRM_TEXT_COLOR = RGB(255, 0, 0),
   LIST_MAX_COUNT = 10,
   LIST_ITEM_HEIGHT = 28,
   LIST_BOX_TOP_Y = 36,
   LIST_FONT_HEIGHT = 16,
   HINT_FONT_HEIGHT = 16,
   BIG_HINT_FONT_HEIGHT = 28,
};

enum
{
   IDC_LIST_CONTENT = 10000,
   IDC_EDIT_SEARCH,
   IDC_BTN_ADD,
   IDC_BTN_RETURN,
   IDC_STATIC_TITLE_CREATE,
   IDC_BTN_CREATE_OK,
   IDC_EDIT_NEW,
   IDC_BTN_DELETE,
   IDC_BTN_EDIT_FINISH,
   IDC_BTN_DELETE_CONFIRM
};

IMPLEMENT_DYNAMIC(CDlgCommonChatContent, CDialogEx)

CDlgCommonChatContent::CDlgCommonChatContent(CWnd* pParent /*=NULL*/)
   :m_eStatus(SELECT_CONTENT), m_nXLeft(0), m_nYBottom(0)
{

}

BOOL CDlgCommonChatContent::CreateDlgIndirect(CWnd* pParent)
{
   if (GetSafeHwnd())
      return FALSE;

   std::vector<WORD> vecTemplate(sizeof(DLGTEMPLATE)/sizeof(WORD), 0);
   DLGTEMPLATE *pTemplate = (DLGTEMPLATE *)vecTemplate.data();
   pTemplate->style =  DS_SETFONT | DS_FIXEDSYS | WS_POPUP | WS_SYSMENU;
   pTemplate->x = 0;
   pTemplate->y = 0;
   pTemplate->cx = 275;
   pTemplate->cy = 170;
   pTemplate->cdit = 10;
   vecTemplate.push_back(0); // 菜单
   vecTemplate.push_back(0); // class
   vecTemplate.push_back(0); // Caption

   //MS Shell Dlg(8)
   vecTemplate.push_back(8);

   USES_CONVERSION;
   WCHAR *p = T2W(_T("MS Shell Dlg"));
   while (*p != 0)
   {
      vecTemplate.push_back(*p);
      ++p;
   }
   vecTemplate.push_back(0);

   //Align
   if (vecTemplate.size() % 2 != 0)
      vecTemplate.push_back(0);

   { //list
      std::vector<WORD> vecItemTemplate(sizeof(DLGITEMTEMPLATE)/sizeof(WORD), 0);
      DLGITEMTEMPLATE *pItem = (DLGITEMTEMPLATE *)vecItemTemplate.data();
      DLGITEMTEMPLATE &item = *pItem;
      item.style = WS_VISIBLE | WS_BORDER | LBS_NOTIFY | LBS_SORT | LBS_OWNERDRAWFIXED | LBS_HASSTRINGS | LBS_NOINTEGRALHEIGHT | WS_VSCROLL | WS_TABSTOP;
      item.id = IDC_LIST_CONTENT;
      item.dwExtendedStyle = 0;
      item.x = 0;
      item.y = 22;
      item.cx = 275;
      item.cy = 136;
      vecItemTemplate.push_back(0xFFFF);
      vecItemTemplate.push_back(0x0083);
      vecItemTemplate.push_back(0); //title
      vecItemTemplate.push_back(0); //data

      vecTemplate.insert(vecTemplate.end(), vecItemTemplate.begin(), vecItemTemplate.end());
      if (vecTemplate.size() % 2 != 0)
         vecTemplate.push_back(0);
   }
   
   { //edit
      std::vector<WORD> vecItemTemplate(sizeof(DLGITEMTEMPLATE)/sizeof(WORD), 0);
      DLGITEMTEMPLATE *pItem = (DLGITEMTEMPLATE *)vecItemTemplate.data();
      DLGITEMTEMPLATE &item = *pItem;
      item.style = WS_VISIBLE | ES_AUTOHSCROLL; //NOT WS_BORDER
      item.id = IDC_EDIT_SEARCH;
      item.dwExtendedStyle = WS_EX_TRANSPARENT;
      item.x = 1;
      item.y = 6;
      item.cx = 229;
      item.cy = 14;
      vecItemTemplate.push_back(0xFFFF);
      vecItemTemplate.push_back(0x0081);
      vecItemTemplate.push_back(0); //title
      vecItemTemplate.push_back(0); //data

      vecTemplate.insert(vecTemplate.end(), vecItemTemplate.begin(), vecItemTemplate.end());
      if (vecTemplate.size() % 2 != 0)
         vecTemplate.push_back(0);
   }

   { //PUSHBUTTON
      std::vector<WORD> vecItemTemplate(sizeof(DLGITEMTEMPLATE)/sizeof(WORD), 0);
      DLGITEMTEMPLATE *pItem = (DLGITEMTEMPLATE *)vecItemTemplate.data();
      DLGITEMTEMPLATE &item = *pItem;
      item.style = WS_VISIBLE | BS_PUSHBUTTON;
      item.id = IDC_BTN_ADD;
      item.dwExtendedStyle = 0;
      item.x = 232;
      item.y = 3;
      item.cx = 37;
      item.cy = 14;
      vecItemTemplate.push_back(0xFFFF);
      vecItemTemplate.push_back(0x0080);
      //vecItemTemplate.push_back(0); //title
      p = T2W(_T("新建"));
      while (*p != 0)
      {
         vecItemTemplate.push_back(*p);
         ++p;
      }
      vecItemTemplate.push_back(0); //title
      vecItemTemplate.push_back(0); //data

      vecTemplate.insert(vecTemplate.end(), vecItemTemplate.begin(), vecItemTemplate.end());
      if (vecTemplate.size() % 2 != 0)
         vecTemplate.push_back(0);
   }

   { //PUSHBUTTON
      std::vector<WORD> vecItemTemplate(sizeof(DLGITEMTEMPLATE)/sizeof(WORD), 0);
      DLGITEMTEMPLATE *pItem = (DLGITEMTEMPLATE *)vecItemTemplate.data();
      DLGITEMTEMPLATE &item = *pItem;
      item.style = BS_PUSHBUTTON;
      item.id = IDC_BTN_RETURN;
      item.dwExtendedStyle = 0;
      item.x = 8;
      item.y = 4;
      item.cx = 37;
      item.cy = 14;
      vecItemTemplate.push_back(0xFFFF);
      vecItemTemplate.push_back(0x0080);
      //vecItemTemplate.push_back(0); //title
      p = T2W(_T("返回"));
      while (*p != 0)
      {
         vecItemTemplate.push_back(*p);
         ++p;
      }
      vecItemTemplate.push_back(0); //title
      vecItemTemplate.push_back(0); //data

      vecTemplate.insert(vecTemplate.end(), vecItemTemplate.begin(), vecItemTemplate.end());
      if (vecTemplate.size() % 2 != 0)
         vecTemplate.push_back(0);
   }

   { //LTEXT
      std::vector<WORD> vecItemTemplate(sizeof(DLGITEMTEMPLATE)/sizeof(WORD), 0);
      DLGITEMTEMPLATE *pItem = (DLGITEMTEMPLATE *)vecItemTemplate.data();
      DLGITEMTEMPLATE &item = *pItem;
      item.style = 0;
      item.id = IDC_STATIC_TITLE_CREATE;
      item.dwExtendedStyle = WS_EX_TRANSPARENT;
      item.x = 84;
      item.y = 6;
      item.cx = 65;
      item.cy = 8;
      vecItemTemplate.push_back(0xFFFF);
      vecItemTemplate.push_back(0x0082);
      //vecItemTemplate.push_back(0); //title
      p = T2W(_T("创建常用聊天内容"));
      while (*p != 0)
      {
         vecItemTemplate.push_back(*p);
         ++p;
      }
      vecItemTemplate.push_back(0); //title
      vecItemTemplate.push_back(0); //data

      vecTemplate.insert(vecTemplate.end(), vecItemTemplate.begin(), vecItemTemplate.end());
      if (vecTemplate.size() % 2 != 0)
         vecTemplate.push_back(0);
   }

   { //PUSHBUTTON
      std::vector<WORD> vecItemTemplate(sizeof(DLGITEMTEMPLATE)/sizeof(WORD), 0);
      DLGITEMTEMPLATE *pItem = (DLGITEMTEMPLATE *)vecItemTemplate.data();
      DLGITEMTEMPLATE &item = *pItem;
      item.style = 0;
      item.id = IDC_BTN_CREATE_OK;
      item.dwExtendedStyle = 0;
      item.x = 110;
      item.y = 156;
      item.cx = 50;
      item.cy = 14;
      vecItemTemplate.push_back(0xFFFF);
      vecItemTemplate.push_back(0x0080);
      //vecItemTemplate.push_back(0); //title
      p = T2W(_T("创建"));
      while (*p != 0)
      {
         vecItemTemplate.push_back(*p);
         ++p;
      }
      vecItemTemplate.push_back(0); //title
      vecItemTemplate.push_back(0); //data

      vecTemplate.insert(vecTemplate.end(), vecItemTemplate.begin(), vecItemTemplate.end());
      if (vecTemplate.size() % 2 != 0)
         vecTemplate.push_back(0);
   }

   { //EDITTEXT
      std::vector<WORD> vecItemTemplate(sizeof(DLGITEMTEMPLATE)/sizeof(WORD), 0);
      DLGITEMTEMPLATE *pItem = (DLGITEMTEMPLATE *)vecItemTemplate.data();
      DLGITEMTEMPLATE &item = *pItem;
      item.style = WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | ES_WANTRETURN;
      item.id = IDC_EDIT_NEW;
      item.dwExtendedStyle = 0;
      item.x = 0;
      item.y = 24;
      item.cx = 275;
      item.cy = 131;
      vecItemTemplate.push_back(0xFFFF);
      vecItemTemplate.push_back(0x0081);
      vecItemTemplate.push_back(0); //title
      vecItemTemplate.push_back(0); //data

      vecTemplate.insert(vecTemplate.end(), vecItemTemplate.begin(), vecItemTemplate.end());
      if (vecTemplate.size() % 2 != 0)
         vecTemplate.push_back(0);
   }

   { //PUSHBUTTON
      std::vector<WORD> vecItemTemplate(sizeof(DLGITEMTEMPLATE)/sizeof(WORD), 0);
      DLGITEMTEMPLATE *pItem = (DLGITEMTEMPLATE *)vecItemTemplate.data();
      DLGITEMTEMPLATE &item = *pItem;
      item.style = 0;
      item.id = IDC_BTN_EDIT_FINISH;
      item.dwExtendedStyle = 0;
      item.x = 192;
      item.y = 156;
      item.cx = 50;
      item.cy = 14;
      vecItemTemplate.push_back(0xFFFF);
      vecItemTemplate.push_back(0x0080);
      //vecItemTemplate.push_back(0); //title
      p = T2W(_T("完成"));
      while (*p != 0)
      {
         vecItemTemplate.push_back(*p);
         ++p;
      }
      vecItemTemplate.push_back(0); //title
      vecItemTemplate.push_back(0); //data

      vecTemplate.insert(vecTemplate.end(), vecItemTemplate.begin(), vecItemTemplate.end());
      if (vecTemplate.size() % 2 != 0)
         vecTemplate.push_back(0);
   }

   { //PUSHBUTTON
      std::vector<WORD> vecItemTemplate(sizeof(DLGITEMTEMPLATE)/sizeof(WORD), 0);
      DLGITEMTEMPLATE *pItem = (DLGITEMTEMPLATE *)vecItemTemplate.data();
      DLGITEMTEMPLATE &item = *pItem;
      item.style = 0;
      item.id = IDC_BTN_DELETE;
      item.dwExtendedStyle = 0;
      item.x = 28;
      item.y = 156;
      item.cx = 50;
      item.cy = 14;
      vecItemTemplate.push_back(0xFFFF);
      vecItemTemplate.push_back(0x0080);
      //vecItemTemplate.push_back(0); //title
      p = T2W(_T("删除"));
      while (*p != 0)
      {
         vecItemTemplate.push_back(*p);
         ++p;
      }
      vecItemTemplate.push_back(0); //title
      vecItemTemplate.push_back(0); //data

      vecTemplate.insert(vecTemplate.end(), vecItemTemplate.begin(), vecItemTemplate.end());
      if (vecTemplate.size() % 2 != 0)
         vecTemplate.push_back(0);
   }

   { //PUSHBUTTON
      std::vector<WORD> vecItemTemplate(sizeof(DLGITEMTEMPLATE)/sizeof(WORD), 0);
      DLGITEMTEMPLATE *pItem = (DLGITEMTEMPLATE *)vecItemTemplate.data();
      DLGITEMTEMPLATE &item = *pItem;
      item.style = 0;
      item.id = IDC_BTN_DELETE_CONFIRM;
      item.dwExtendedStyle = 0;
      item.x = 109;
      item.y = 155;
      item.cx = 50;
      item.cy = 14;
      vecItemTemplate.push_back(0xFFFF);
      vecItemTemplate.push_back(0x0080);
      //vecItemTemplate.push_back(0); //title
      p = T2W(_T("删除"));
      while (*p != 0)
      {
         vecItemTemplate.push_back(*p);
         ++p;
      }
      vecItemTemplate.push_back(0); //title
      vecItemTemplate.push_back(0); //data

      vecTemplate.insert(vecTemplate.end(), vecItemTemplate.begin(), vecItemTemplate.end());
      if (vecTemplate.size() % 2 != 0)
         vecTemplate.push_back(0);
   }

   if (!CreateIndirect((DLGTEMPLATE *)vecTemplate.data(), pParent))
      return FALSE;
   return TRUE;
}

CDlgCommonChatContent::~CDlgCommonChatContent()
{
}

void CDlgCommonChatContent::DoDataExchange(CDataExchange* pDX)
{
   CDialogEx::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_LIST_CONTENT, m_lstBox);
   DDX_Control(pDX, IDC_EDIT_SEARCH, m_EditFilter);
   DDX_Control(pDX, IDC_BTN_ADD, m_btnAdd);
   DDX_Control(pDX, IDC_BTN_RETURN, m_btnReturn);
   DDX_Control(pDX, IDC_STATIC_TITLE_CREATE, m_staticTitleCreate);
   DDX_Control(pDX, IDC_BTN_CREATE_OK, m_btnCreateOK);
   DDX_Control(pDX, IDC_EDIT_NEW, m_editNew);
   DDX_Control(pDX, IDC_BTN_DELETE, m_btnDelete);
   DDX_Control(pDX, IDC_BTN_EDIT_FINISH, m_btnEditFinish);
   DDX_Control(pDX, IDC_BTN_DELETE_CONFIRM, m_btnDeleteConfirm);
}


BEGIN_MESSAGE_MAP(CDlgCommonChatContent, CDialogEx)
   ON_WM_SHOWWINDOW()
   ON_WM_ACTIVATE()
   ON_WM_ERASEBKGND()
   ON_BN_CLICKED(IDC_BTN_RETURN, &CDlgCommonChatContent::OnBnClickedBtnReturn)
   ON_LBN_SELCHANGE(IDC_LIST_CONTENT, &CDlgCommonChatContent::OnLbnSelchangeListContent)
   ON_EN_CHANGE(IDC_EDIT_SEARCH, &CDlgCommonChatContent::OnEnChangeEditSearch)
   ON_BN_CLICKED(IDC_BTN_ADD, &CDlgCommonChatContent::OnBnClickedBtnAdd)
   ON_BN_CLICKED(IDC_BTN_CREATE_OK, &CDlgCommonChatContent::OnBnClickedBtnCreateOk)
   ON_BN_CLICKED(IDC_BTN_EDIT_FINISH, &CDlgCommonChatContent::OnBnClickedBtnEditFinish)
   ON_BN_CLICKED(IDC_BTN_DELETE, &CDlgCommonChatContent::OnBnClickedBtnDelete)
   ON_BN_CLICKED(IDC_BTN_DELETE_CONFIRM, &CDlgCommonChatContent::OnBnClickedBtnDeleteConfirm)
END_MESSAGE_MAP()


// dlg1 消息处理程序


void CDlgCommonChatContent::OnShowWindow(BOOL bShow, UINT nStatus)
{
   CDialogEx::OnShowWindow(bShow, nStatus);

   // TODO: 在此处添加消息处理程序代码
   //SetCapture();
}

BOOL CDlgCommonChatContent::OnInitDialog()
{
   CDialogEx::OnInitDialog();

   // TODO:  在此添加额外的初始化
   m_lstBox.SetItemHeight(0, LIST_ITEM_HEIGHT);

   m_ListFont.CreateFont(LIST_FONT_HEIGHT,0,0,0,FW_DONTCARE,FALSE,FALSE,0, 1,
      OUT_DEFAULT_PRECIS, 
      CLIP_DEFAULT_PRECIS,
      DEFAULT_QUALITY, 
      DEFAULT_PITCH|FF_SWISS,
      _T("宋体"));

   m_HintFont.CreateFont(HINT_FONT_HEIGHT,0,0,0,FW_DONTCARE,FALSE,FALSE,0, 1,
      OUT_DEFAULT_PRECIS, 
      CLIP_DEFAULT_PRECIS,
      DEFAULT_QUALITY, 
      DEFAULT_PITCH|FF_SWISS,
      _T("宋体"));

   m_BigHintFont.CreateFont(BIG_HINT_FONT_HEIGHT,0,0,0,FW_DONTCARE,FALSE,FALSE,0, 1,
      OUT_DEFAULT_PRECIS, 
      CLIP_DEFAULT_PRECIS,
      DEFAULT_QUALITY, 
      DEFAULT_PITCH|FF_SWISS,
      _T("宋体"));

   m_lstBox.SetFont(&m_ListFont);

   auto funcEditItem = [this](int nItem)
   {
      int nCount = m_lstBox.GetCount();
      if (nItem < nCount && nItem >= 0)
      {
         CString sText;
         m_lstBox.GetText(nItem, sText);
         m_sEditItemStringOld = sText;
         //OnBnClickedBtnAdd(); //tmpduchen
         ShowEditWindow(FALSE, sText);
      }
   };

   m_lstBox.m_funcEditItem = funcEditItem;

   m_EditFilter.SetFont(&m_ListFont);

   m_editNew.SetFont(&m_ListFont);

   //m_Edit.SetCueBanner(_T("搜索"));

   m_Bubble.Create(0, 0, GetSafeHwnd(), _T("1"));

   CRect RectNewEdit;
   m_editNew.GetWindowRect(&RectNewEdit);

   m_editNew.SetWindowPos(NULL, 0, 0, RectNewEdit.Width(),
      LIST_ITEM_HEIGHT * LIST_MAX_COUNT + 5 - 30, SWP_NOZORDER | SWP_NOMOVE);

   CRect RectBtn;
   m_btnDelete.GetWindowRect(&RectBtn);
   ScreenToClient(&RectBtn);
   m_btnDelete.SetWindowPos(NULL, RectBtn.left, LIST_BOX_TOP_Y + LIST_ITEM_HEIGHT * LIST_MAX_COUNT + 5 - 25,
      0, 0, SWP_NOSIZE | SWP_NOZORDER);

   m_btnEditFinish.GetWindowRect(&RectBtn);
   ScreenToClient(&RectBtn);
   m_btnEditFinish.SetWindowPos(NULL, RectBtn.left, LIST_BOX_TOP_Y + LIST_ITEM_HEIGHT * LIST_MAX_COUNT + 5 - 25,
      0, 0, SWP_NOSIZE | SWP_NOZORDER);

   m_btnDeleteConfirm.GetWindowRect(&RectBtn);
   ScreenToClient(&RectBtn);
   m_btnDeleteConfirm.SetWindowPos(NULL, RectBtn.left, LIST_BOX_TOP_Y + LIST_ITEM_HEIGHT * LIST_MAX_COUNT + 5 - 25,
      0, 0, SWP_NOSIZE | SWP_NOZORDER);

   m_btnCreateOK.GetWindowRect(&RectBtn);
   ScreenToClient(&RectBtn);
   m_btnCreateOK.SetWindowPos(NULL, RectBtn.left, LIST_BOX_TOP_Y + LIST_ITEM_HEIGHT * LIST_MAX_COUNT + 5 - 25,
      0, 0, SWP_NOSIZE | SWP_NOZORDER);

   return TRUE;  // return TRUE unless you set the focus to a control
   // 异常: OCX 属性页应返回 FALSE
}


void CDlgCommonChatContent::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
   CDialogEx::OnActivate(nState, pWndOther, bMinimized);

   // TODO: 在此处添加消息处理程序代码

   if (nState == WA_INACTIVE)
   {
      ShowWindow(SW_HIDE);
   }
}


BOOL CDlgCommonChatContent::OnEraseBkgnd(CDC* pDC)
{
   // TODO: 在此添加消息处理程序代码和/或调用默认值
   CRect Rect;
   GetClientRect(&Rect);

   CBrush Brush;
   Brush.CreateSolidBrush(BACKGROUND_COLOR);

   CPen Pen;
   Pen.CreatePen(PS_SOLID, 1, FRAME_COLOR);
   pDC->SaveDC();
   pDC->SelectObject(&Brush);
   pDC->SelectObject(&Pen);
   pDC->Rectangle(&Rect);
   //pDC->PatBlt(0, 0, Rect.Width(), Rect.Height(),  PATCOPY);

   if (m_eStatus == CREATE_CONTENT)
   {
      pDC->SetBkMode(TRANSPARENT);
      pDC->SelectObject(&m_HintFont);
      pDC->TextOut(145, 10, _T("新建常用聊天内容"));
   }
   else if (m_eStatus == EDIT_CONTENT)
   {
      pDC->SetBkMode(TRANSPARENT);
      pDC->SelectObject(&m_HintFont);
      pDC->TextOut(145, 10, _T("编辑常用聊天内容"));
   }
   else if (m_eStatus == DELETE_CONFIRM)
   {
      pDC->SetBkMode(TRANSPARENT);
      pDC->SelectObject(&m_HintFont);
      pDC->TextOut(195, 10, _T("删除"));
      pDC->SelectObject(&m_BigHintFont);
      pDC->SetTextColor(DELETE_CONFIRM_TEXT_COLOR);
      pDC->TextOut(135, 70, _T("确认删除？"));
   }

   pDC->RestoreDC(-1);

   return TRUE;
}

void CDlgCommonChatContent::OnBnClickedBtnReturn()
{
   TurnBack();
}


void CDlgCommonChatContent::OnLbnSelchangeListContent()
{
   // TODO: 在此添加控件通知处理程序代码
   int nSel = m_lstBox.GetCurSel();

   if (nSel != -1)
   {
      ShowWindow(SW_HIDE);

      if (m_funcOutputText)
      {
         CString sSelText;
         m_lstBox.GetText(nSel, sSelText);
         m_funcOutputText(sSelText);
      }
   }
}

void CDlgCommonChatContent::TurnBack()
{
   if (m_eStatus == DELETE_CONFIRM)
   {
      m_editNew.ShowWindow(SW_SHOW);

      m_btnDelete.ShowWindow(SW_SHOW);
      m_btnEditFinish.ShowWindow(SW_SHOW);
      m_btnDeleteConfirm.ShowWindow(SW_HIDE);
      m_eStatus = EDIT_CONTENT;

      Invalidate();
   }
   else
   {
      m_btnReturn.ShowWindow(SW_HIDE);
      m_lstBox.ShowWindow(SW_SHOW);
      int nCount = m_lstBox.GetCount();

      if (nCount > LIST_MAX_COUNT)
         nCount = LIST_MAX_COUNT;

      CRect WindowRect;
      GetWindowRect(&WindowRect);
      SetWindowPos(NULL, 0, 0, WindowRect.Width(), LIST_BOX_TOP_Y + LIST_ITEM_HEIGHT * nCount + 5, SWP_NOMOVE | SWP_NOZORDER);

      CRect ListBoxRect;
      m_lstBox.GetWindowRect(&ListBoxRect);
      m_lstBox.SetWindowPos(NULL, 0, 0, ListBoxRect.Width(), 4 + LIST_ITEM_HEIGHT * nCount, SWP_NOMOVE | SWP_NOZORDER);

      m_btnAdd.ShowWindow(SW_SHOW);
      m_EditFilter.ShowWindow(SW_SHOW);

      m_EditFilter.SetFocus();

      m_btnCreateOK.ShowWindow(SW_HIDE);

      m_editNew.ShowWindow(SW_HIDE);

      m_btnDelete.ShowWindow(SW_HIDE);
      m_btnEditFinish.ShowWindow(SW_HIDE);

      m_eStatus = SELECT_CONTENT;

      if (m_nXLeft != -1 && m_nYBottom != -1)
      {
         int nCount = m_deqContents.size();
         if (nCount > LIST_MAX_COUNT)
            nCount = LIST_MAX_COUNT;
         SetWindowPos(NULL, m_nXLeft, 
            /*         nYBottom - (37 + LIST_ITEM_HEIGHT * LIST_MAX_COUNT), */
            m_nYBottom - (LIST_BOX_TOP_Y + LIST_ITEM_HEIGHT * nCount + 5),
            0, 0, SWP_NOSIZE | SWP_NOZORDER);
      }

      Invalidate();
   }
}

void CDlgCommonChatContent::Init(int nXLeft/* = -1*/, int nYBottom/* = -1*/)
{
   if (nXLeft != -1)
      m_nXLeft = nXLeft;
   if (nYBottom != -1)
      m_nYBottom = nYBottom;
   m_btnReturn.ShowWindow(SW_HIDE);
   m_lstBox.ShowWindow(SW_SHOW);
   m_lstBox.SetCurSel(-1);

   m_lstBox.ResetContent();

   CFrequentlyChatContentFile ContentFile;
   if (!m_sSettingFilePath.IsEmpty())
      ContentFile.ReadFile(m_sSettingFilePath);

   m_deqContents.assign(ContentFile.m_vecContent.begin(), ContentFile.m_vecContent.end());

   for (auto Iter = m_deqContents.begin(); Iter != m_deqContents.end(); ++Iter)
   {
      m_lstBox.InsertString(-1, *Iter);
   }

   int nCount = m_lstBox.GetCount();

   if (nCount > LIST_MAX_COUNT)
      nCount = LIST_MAX_COUNT;

   CRect WindowRect;
   GetWindowRect(&WindowRect);
   SetWindowPos(NULL, 0, 0, WindowRect.Width(), LIST_BOX_TOP_Y + LIST_ITEM_HEIGHT * nCount + 5, SWP_NOMOVE | SWP_NOZORDER);

   CRect ListBoxRect;
   m_lstBox.GetWindowRect(&ListBoxRect);

   m_lstBox.SetWindowPos(NULL, 0, 0, ListBoxRect.Width(), LIST_ITEM_HEIGHT * nCount + 4, SWP_NOMOVE | SWP_NOZORDER);

   m_btnAdd.ShowWindow(SW_SHOW);
   m_EditFilter.ShowWindow(SW_SHOW);


   m_EditFilter.SetWindowText(_T(""));

   m_EditFilter.SetFocus();

   m_btnCreateOK.ShowWindow(SW_HIDE);
   m_editNew.ShowWindow(SW_HIDE);
   m_btnDelete.ShowWindow(SW_HIDE);
   m_btnEditFinish.ShowWindow(SW_HIDE);
   m_btnDeleteConfirm.ShowWindow(SW_HIDE);

   m_eStatus = SELECT_CONTENT;

   if (m_nXLeft != -1 && m_nYBottom != -1)
   {
      int nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
      if (m_nXLeft + ListBoxRect.Width() > nScreenWidth)
         m_nXLeft = nScreenWidth - ListBoxRect.Width();
      int nContentCount = m_deqContents.size();
      if (nContentCount > LIST_MAX_COUNT)
         nContentCount = LIST_MAX_COUNT;
      SetWindowPos(NULL, m_nXLeft, 
         m_nYBottom - (LIST_BOX_TOP_Y + LIST_ITEM_HEIGHT * nContentCount + 5),
         0, 0, SWP_NOSIZE | SWP_NOZORDER);
   }

   Invalidate();
}

void CDlgCommonChatContent::OnEnChangeEditSearch()
{
   // TODO:  如果该控件是 RICHEDIT 控件，它将不
   // 发送此通知，除非重写 CDialogEx::OnInitDialog()
   // 函数并调用 CRichEditCtrl().SetEventMask()，
   // 同时将 ENM_CHANGE 标志“或”运算到掩码中。

   // TODO:  在此添加控件通知处理程序代码
   CString sFilter;
   m_EditFilter.GetWindowText(sFilter);
   sFilter.MakeUpper();
   
   m_lstBox.ResetContent();

   for (auto Iter = m_deqContents.begin(); Iter != m_deqContents.end(); ++Iter)
   {
      CString sTextUpper(*Iter);
      sTextUpper.MakeUpper();
      
      if (!sFilter.IsEmpty() && -1 == sTextUpper.Find(sFilter))
         continue;
      m_lstBox.InsertString(-1, *Iter);
   }

   int nCount = m_lstBox.GetCount();

   if (nCount > LIST_MAX_COUNT)
      nCount = LIST_MAX_COUNT;

   CRect WindowRect;
   GetWindowRect(&WindowRect);
   SetWindowPos(NULL, 0, 0, WindowRect.Width(), LIST_BOX_TOP_Y + LIST_ITEM_HEIGHT * nCount + 5, SWP_NOMOVE | SWP_NOZORDER);

   CRect ListBoxRect;
   m_lstBox.GetWindowRect(&ListBoxRect);
   m_lstBox.SetWindowPos(NULL, 0, 0, ListBoxRect.Width(), LIST_ITEM_HEIGHT * nCount + 4, SWP_NOMOVE | SWP_NOZORDER);
}


void CDlgCommonChatContent::OnBnClickedBtnAdd()
{
   // TODO: 在此添加控件通知处理程序代码
   CString sText;
   m_EditFilter.GetWindowText(sText);
   ShowEditWindow(TRUE, sText);
}


void CDlgCommonChatContent::OnOK()
{
   // TODO: 在此添加专用代码和/或调用基类
}


void CDlgCommonChatContent::OnBnClickedBtnCreateOk()
{
   // TODO: 在此添加控件通知处理程序代码
   CString sNewString;
   m_editNew.GetWindowText(sNewString);

   CString sTestEmpty = sNewString;
   sTestEmpty.Trim();
   if (sTestEmpty.IsEmpty())
   {
      m_Bubble.SetText(_T("内容不能为空"));
      m_Bubble.SetPos(157, 125);
      m_Bubble.Show();
      return;
   }

   auto IterFindAlreadyExist = std::find(m_deqContents.begin(), m_deqContents.end(), sNewString);
   if (IterFindAlreadyExist != m_deqContents.end())
   {
      //已存在
      m_Bubble.SetText(_T("已存在"));
      m_Bubble.SetPos(162, 125);
      m_Bubble.Show();
      return;
   }

   m_deqContents.push_front(sNewString);

   WriteFile();
   
//    ShowWindow(SW_HIDE);
// 
//    if (m_funcCreateText)
//       m_funcCreateText(sNewString);
   Init();
}

BOOL CDlgCommonChatContent::WriteFile()
{
   if (m_sSettingFilePath.IsEmpty())
      return TRUE;
   CFrequentlyChatContentFile FrequentlyChat;
   FrequentlyChat.m_vecContent.assign(m_deqContents.begin(), m_deqContents.end());
   return FrequentlyChat.WriteFile(m_sSettingFilePath);
}

void CDlgCommonChatContent::ShowEditWindow(BOOL bNew, const CString &sInitText)
{
   if (bNew)
   {
      m_eStatus = CREATE_CONTENT;
      m_btnDelete.ShowWindow(SW_HIDE);
      m_btnEditFinish.ShowWindow(SW_HIDE);
      m_btnCreateOK.ShowWindow(SW_SHOW);
   }
   else
   {
      m_eStatus = EDIT_CONTENT;
      m_btnDelete.ShowWindow(SW_SHOW);
      m_btnEditFinish.ShowWindow(SW_SHOW);
      m_btnCreateOK.ShowWindow(SW_HIDE);
   }
   m_btnReturn.ShowWindow(SW_SHOW);
   m_lstBox.ShowWindow(SW_HIDE);
   m_btnAdd.ShowWindow(SW_HIDE);
   m_EditFilter.ShowWindow(SW_HIDE);
   

   m_editNew.ShowWindow(SW_SHOW);
   m_editNew.SetSel(0, -1);
   m_editNew.ReplaceSel(sInitText);
   m_editNew.SetFocus();

   //m_eStatus = CREATE_CONTENT;

   CRect WindowRect;
   GetWindowRect(WindowRect);
   SetWindowPos(NULL, 0, 0, WindowRect.Width(), LIST_BOX_TOP_Y + LIST_ITEM_HEIGHT * LIST_MAX_COUNT + 5, SWP_NOMOVE | SWP_NOREPOSITION);

   if (m_nXLeft != -1 && m_nYBottom != -1)
   {
      SetWindowPos(NULL, m_nXLeft, 
         m_nYBottom - (LIST_BOX_TOP_Y + LIST_ITEM_HEIGHT * LIST_MAX_COUNT + 5),
         0, 0, SWP_NOSIZE | SWP_NOZORDER);
   }

   Invalidate();
}

void CDlgCommonChatContent::OnBnClickedBtnEditFinish()
{
   CString sNewContent;
   m_editNew.GetWindowText(sNewContent);

   CString sTestEmpty = sNewContent;
   sTestEmpty.Trim();
   if (sTestEmpty.IsEmpty())
   {//无内容
      m_Bubble.SetText(_T("内容不能为空"));
      m_Bubble.SetPos(157, 125);
      m_Bubble.Show();
      return;
   }

   if (sNewContent == m_sEditItemStringOld)
   {
      //无变化
      TurnBack();
      return;
   }

   auto IterFindAlreadyExist = std::find(m_deqContents.begin(), m_deqContents.end(), sNewContent);
   if (IterFindAlreadyExist != m_deqContents.end())
   {
      //已存在
      m_Bubble.SetText(_T("已存在"));
      m_Bubble.SetPos(162, 125);
      m_Bubble.Show();
      return;
   }

   auto Iter = std::find(m_deqContents.begin(), m_deqContents.end(), m_sEditItemStringOld);
   ASSERT(Iter != m_deqContents.end());
   m_deqContents.erase(Iter);
   m_deqContents.push_front(sNewContent);

   WriteFile();

   Init();
}


void CDlgCommonChatContent::OnBnClickedBtnDelete()
{
   // TODO: 在此添加控件通知处理程序代码
   m_editNew.ShowWindow(SW_HIDE);
   m_btnDelete.ShowWindow(SW_HIDE);
   m_btnEditFinish.ShowWindow(SW_HIDE);
   m_btnDeleteConfirm.ShowWindow(SW_SHOW);

   m_eStatus = DELETE_CONFIRM;

   Invalidate();
}


void CDlgCommonChatContent::OnBnClickedBtnDeleteConfirm()
{
   auto Iter = std::find(m_deqContents.begin(), m_deqContents.end(), m_sEditItemStringOld);
   ASSERT(Iter != m_deqContents.end());
   m_deqContents.erase(Iter);

   WriteFile();

   Init();
}


BOOL CDlgCommonChatContent::PreTranslateMessage(MSG* pMsg)
{
   // TODO: 在此添加专用代码和/或调用基类
   if (pMsg->message == WM_MOUSEWHEEL)
   {
      pMsg->hwnd = m_lstBox.GetSafeHwnd();
   }
   return CDialogEx::PreTranslateMessage(pMsg);
}

void CDlgCommonChatContent::SetSettingPath(const CString &sPath)
{
   m_sSettingFilePath = sPath;
}