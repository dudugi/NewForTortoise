#pragma once
#include "resource.h"
#include <set>
#include <vector>
#define COMBOX_SELCHANGE   WM_USER+1005
#define COMBOX_DELITEM     WM_USER+1006
#define COMBOX_EDITCHANGE     WM_USER+1007


// CLY2ComBox

class CLY2ComBox : public CComboBox
{
	DECLARE_DYNAMIC(CLY2ComBox)

public:
	CLY2ComBox();
	virtual ~CLY2ComBox();

protected:
	DECLARE_MESSAGE_MAP()

public:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual void PreSubclassWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

public:
	// ��Ͽ����ڵı߿򲿷ֵ���ʽö�٣�
	// ONLYONE��ֻ��һ�ֱ߿���ɫ
	// TWO���н�����޽�������
	// THREEDGR��3D��ʽ�������ϱ߿�����±߿���ɫ��һ��
	// WIN7��ϵͳĬ�ϵ���ʽ
	enum FRAMESTYLE { ONLYONE = 1, TWO = 2, THREEDGR = 3, WIN7 = 4};
	CEdit*			m_pEdit; // �༭��ָ��
	BOOL			m_bFocus; // �ؼ�������꽹��//2016/08/10 wangqy ��private��public��Ϊ�˴���һ���Ի����ϣ��ж���˿ؼ�ʱ���ж���꽹�㡱
private:
	// ������ť�ĵĲ�ͬ״̬
	enum STATE { NORMAL = 1, RAISED = 2, PRESSED = 3 };
	CListBox*		m_pListBox; // �б��ָ��
	CFont*			m_pEdtFont;
	CFont*			m_pListFont;
	int				m_nEdtFontPtSize;
	int				m_nListFontPtSize;
	CString			m_csListFontName;
	CString			m_csEdtFontName;
	COLORREF	m_clrEditText;
	COLORREF	m_clrListText;
	COLORREF	m_clrEditTextBg;
	COLORREF	m_clrListTextBg;
	BOOL			m_bEditTextHasBgColor;
	BOOL			m_bListTextHasBgColor;
	BOOL			m_bReadOnly; // �༭��ֻ��

	BOOL			m_bBtnFlags; // ����ڰ�ť�ϵı�ʶ
	BOOL			m_bDown; // ������ť������
	BOOL			m_bPaint; // �������Ʊ�ʶ

	FRAMESTYLE	m_fsFremeStyle; // �༭��߿���ʽ
	COLORREF	m_clrEdtFrame; // �༭����ɫ����ֻ��һ����ɫʱ���ã�Ҳ����SetEdtFrameColor�����������б߿������ɫΪ��ͬ
	COLORREF	m_clr3DHilight; // 3D ����ɫ
	COLORREF	m_clr3DShadow; // 3D ��Ӱɫ
	COLORREF	m_clr3DFace; // 3D ����ɫ

	BOOL			m_bDisableAC; // �༭�������Զ���ɹ����Ƿ���Ч
	BOOL			m_bAComplete; // �Ƿ�����༭�������Զ���ɹ���
	CBitmap		m_bmButton; // ������ťλͼ

	COLORREF	m_clrListItemBg;
	COLORREF	m_clrListHilightItemBg;
	COLORREF	m_clrListFrame;
	COLORREF	m_clrListEvenItem;
	COLORREF	m_clrListOddItem;
	COLORREF	m_clrListItemPartLine;
	COLORREF	m_clrListHilightItemText;

	BOOL			m_bListItemFocus;
	int				m_nPreFocusListItem;
	int				m_nCurrFocusListItem;
	BOOL			m_bAllowDel;

protected:
	// win7 Ĭ�ϱ߿���ɫֵ
	COLORREF m_clrNormalCombFrameLeft;
	COLORREF m_clrNormalCombFrameTop;
	COLORREF m_clrNormalCombFrameRight;
	COLORREF m_clrNormalCombFrameBottom;
	COLORREF m_clrNormalCombFrame;

	COLORREF m_clrFocusCombFrameLeft;
	COLORREF m_clrFocusCombFrameTop;
	COLORREF m_clrFocusCombFrameRight;
	COLORREF m_clrFocusCombFrameBottom;
	COLORREF m_clrFocusCombFrame;

// �Զ��庯�����ڲ��ӿ�
protected:
	void	SetEdtFontHelper(); // ������Ͽ��б༭�������
	void	SetListFontHelper(); // ������Ͽ��������б�������

// �Զ��庯�����ⲿ�ӿ�
public:
	void	SetCombNewFont(int nPtSize, CString csFontName=_T("΢���ź�")); // ������Ͽ�����
	void	SetEdtNewFont(int nPtSize, CString csFontName=_T("΢���ź�")); // ���ñ༭������
	void	SetListNewFont(int nPtSize, CString csFontName=_T("΢���ź�")); // ���������б�����
	void	SetCombTextColor(COLORREF clrCombText); // ������Ͽ��ı���ɫ
	void	SetEdtTextColor(COLORREF clrEdtText); // ���ñ༭���ı���ɫ
	void	SetListTextColor(COLORREF clrListText); // ���������б��ı���ɫ
	void SetEdtTextBgColor(BOOL bEditTextHasBgColor, COLORREF clrEditTextBg=RGB(255, 255, 255)); // ���ñ༭���ı�������ɫ�ͱ��
	void SetListTextBgColor(BOOL bListTextHasBgColor, COLORREF clrListTextBg=RGB(255, 255, 255)); // �����б���ı�������ɫ�ͱ��
	void SetEdtReadOnly(BOOL bEdtReadOnly=TRUE); // ���ñ༭���Ƿ�ֻ��
	void AotuAdjustDroppedWidth(); // ���������б��������������Ӧ��ȣ�����ȫ�Զ��������������庯���е��ã�������һ������Ӧ��ʶ
	void SetAutoComplete(BOOL bAutoComplete); // �Զ����
	void SetFrameStyle(FRAMESTYLE fsFrameStyle); // ���ñ߿���ʽ������Ϊ FRAMESTYLE �е�һ��
	void SetEdtFrameColor(COLORREF clrEdtFrame=RGB(51, 153, 255)); // ���ñ߿����ɫȫ����ͬ
	void Set3DFrameColor(COLORREF clr3Dface, COLORREF clr3DHilight, COLORREF clr3DShadow); // ����3D�߿���ɫ
	void Set3DFrameColorDefault(); // ��3D�߿���ɫ��Ϊ����Ĭ��ֵ

protected:
	BOOL PointInRect(); // ����Ƿ��Ƶ���Ͽ���
	BOOL PointInBtn(); // ����Ƿ��Ƶ�������ͷ����
	void OnNoFlickerPaint(CDC* pDC); // OnPaint ���õĻ��ƺ���
	void DrawCombo(CDC* pDC, STATE eState, COLORREF clrTopLeft, COLORREF clrBottomRight); // ������Ͽ�߿���
	void DrawBtnImg( CDC* pDC, CRect rcButton ); // ����������ťͼƬ

public:
	afx_msg void OnPaint();
	afx_msg void OnKillFocus();
	afx_msg void OnSetFocus();
	afx_msg void OnSysColorChange();

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	afx_msg void OnCbnDropdown();
	afx_msg void OnCbnCloseup();
	afx_msg void OnCbnEditupdate();

	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

public:
	virtual	void	MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual	void	DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual	void	DeleteItem(LPDELETEITEMSTRUCT lpDeleteItemStruct);
	virtual	int	CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
	void DrawListBox(CDC* pDC, int nItemID, UINT uState, CRect rcItem); // �������б�
	void DrawListItem(CDC* pDC, CString csText, CRect rcItem, COLORREF clrText, COLORREF clrBg, COLORREF clrFrame ); // �������б����
	// �б����ɫ����
	void SetListFrameColor(COLORREF clrListFrame);
	void SetListHilightItemBgColor(COLORREF clrListHilightItemBg);
	void SetListItemBgColor(COLORREF clrListItemBg);
	void SetListEvenItemColor(COLORREF clrListEvenItem);
	void SetListOddItemColor(COLORREF clrListOddItem);
	void SetListPartLineColor(COLORREF clrListPartLine);
	void setListHilightItemTextColor(COLORREF clrListHilightItemText);
	void SetAllowDeleteList(BOOL bAllowDelistItem=FALSE);

	afx_msg void OnCbnSelchange();
   afx_msg BOOL OnCbnEditchange();
   afx_msg void OnCbnCommandEditchange();
   afx_msg void OnCbnCommandEditComposing();
public:
   int  AddStringNew(LPCTSTR lpszString);//����Ӻ�����Ҫʵ�����빦�ܣ���Ҫ�õ����
   void SetStrings(const std::set<CString> &setData);
   int InsertStringNew(int nIndex, LPCTSTR lpszString);
   void ResetContentNew();
   int DeleteString(UINT nIndex);
private:
   struct ComboItem
   {
      CString m_sOrg;
      CString m_sPinYin;
      CString m_sShortHand;
   };
   std::vector<ComboItem> m_vecItem;
   BOOL m_flagVKBack;//�Ƿ���back��
   BOOL m_bDropdownShowAll;
   CString m_strLastEditText;
   int m_nCaretStart;
   int m_nCaretEnd;

   static WNDPROC m_CBoldProc;
   static LRESULT CBProc(HWND hWnd,  UINT message, WPARAM wParam, LPARAM lParam );
};


