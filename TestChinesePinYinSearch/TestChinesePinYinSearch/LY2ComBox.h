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
	// 组合框所在的边框部分的样式枚举：
	// ONLYONE：只有一种边框颜色
	// TWO：有焦点和无焦点两种
	// THREEDGR：3D样式，即左上边框和右下边框颜色不一样
	// WIN7：系统默认的样式
	enum FRAMESTYLE { ONLYONE = 1, TWO = 2, THREEDGR = 3, WIN7 = 4};
	CEdit*			m_pEdit; // 编辑框指针
	BOOL			m_bFocus; // 控件具有鼠标焦点//2016/08/10 wangqy 从private到public，为了处理“一个对话框上，有多个此控件时，判断鼠标焦点”
private:
	// 下拉按钮的的不同状态
	enum STATE { NORMAL = 1, RAISED = 2, PRESSED = 3 };
	CListBox*		m_pListBox; // 列表框指针
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
	BOOL			m_bReadOnly; // 编辑框只读

	BOOL			m_bBtnFlags; // 鼠标在按钮上的标识
	BOOL			m_bDown; // 下拉按钮被按下
	BOOL			m_bPaint; // 辅助绘制标识

	FRAMESTYLE	m_fsFremeStyle; // 编辑框边框样式
	COLORREF	m_clrEdtFrame; // 编辑框颜色，当只设一种颜色时可用，也可用SetEdtFrameColor函数设置所有边框相关颜色为相同
	COLORREF	m_clr3DHilight; // 3D 高亮色
	COLORREF	m_clr3DShadow; // 3D 阴影色
	COLORREF	m_clr3DFace; // 3D 正常色

	BOOL			m_bDisableAC; // 编辑框输入自动完成功能是否有效
	BOOL			m_bAComplete; // 是否允许编辑框输入自动完成功能
	CBitmap		m_bmButton; // 下拉按钮位图

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
	// win7 默认边框颜色值
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

// 自定义函数，内部接口
protected:
	void	SetEdtFontHelper(); // 创建组合框中编辑框的字体
	void	SetListFontHelper(); // 创建组合框中下拉列表框的字体

// 自定义函数，外部接口
public:
	void	SetCombNewFont(int nPtSize, CString csFontName=_T("微软雅黑")); // 设置组合框字体
	void	SetEdtNewFont(int nPtSize, CString csFontName=_T("微软雅黑")); // 设置编辑框字体
	void	SetListNewFont(int nPtSize, CString csFontName=_T("微软雅黑")); // 设置下拉列表字体
	void	SetCombTextColor(COLORREF clrCombText); // 设置组合框文本颜色
	void	SetEdtTextColor(COLORREF clrEdtText); // 设置编辑框文本颜色
	void	SetListTextColor(COLORREF clrListText); // 设置下拉列表文本颜色
	void SetEdtTextBgColor(BOOL bEditTextHasBgColor, COLORREF clrEditTextBg=RGB(255, 255, 255)); // 设置编辑框文本背景颜色和标记
	void SetListTextBgColor(BOOL bListTextHasBgColor, COLORREF clrListTextBg=RGB(255, 255, 255)); // 设置列表框文本背景颜色和标记
	void SetEdtReadOnly(BOOL bEdtReadOnly=TRUE); // 设置编辑框是否只读
	void AotuAdjustDroppedWidth(); // 根据下拉列表的字体和最长项自适应宽度，若需全自动，可在设置字体函数中调用，并另设一个自适应标识
	void SetAutoComplete(BOOL bAutoComplete); // 自动完成
	void SetFrameStyle(FRAMESTYLE fsFrameStyle); // 设置边框样式，参数为 FRAMESTYLE 中的一个
	void SetEdtFrameColor(COLORREF clrEdtFrame=RGB(51, 153, 255)); // 设置边框的颜色全都相同
	void Set3DFrameColor(COLORREF clr3Dface, COLORREF clr3DHilight, COLORREF clr3DShadow); // 设置3D边框颜色
	void Set3DFrameColorDefault(); // 把3D边框颜色设为内置默认值

protected:
	BOOL PointInRect(); // 鼠标是否移到组合框上
	BOOL PointInBtn(); // 鼠标是否移到下拉箭头区域
	void OnNoFlickerPaint(CDC* pDC); // OnPaint 调用的绘制函数
	void DrawCombo(CDC* pDC, STATE eState, COLORREF clrTopLeft, COLORREF clrBottomRight); // 绘制组合框边框函数
	void DrawBtnImg( CDC* pDC, CRect rcButton ); // 绘制下拉按钮图片

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
	void DrawListBox(CDC* pDC, int nItemID, UINT uState, CRect rcItem); // 画下拉列表
	void DrawListItem(CDC* pDC, CString csText, CRect rcItem, COLORREF clrText, COLORREF clrBg, COLORREF clrFrame ); // 画下拉列表项背景
	// 列表框颜色设置
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
   int  AddStringNew(LPCTSTR lpszString);//新添加函数，要实现联想功能，需要用到这个
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
   BOOL m_flagVKBack;//是否按下back键
   BOOL m_bDropdownShowAll;
   CString m_strLastEditText;
   int m_nCaretStart;
   int m_nCaretEnd;

   static WNDPROC m_CBoldProc;
   static LRESULT CBProc(HWND hWnd,  UINT message, WPARAM wParam, LPARAM lParam );
};


