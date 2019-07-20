#pragma once

#include "CtrlInfo.h"
/************************************************************************
 * 创建日期：2015-11-02     作者：zhangtao
 * 对话框中间类
 * 基类：CDialogEx
 * 目的：方便在此类CDialogExMid处理的动作
 ************************************************************************/


#ifdef USING_LIB_BCGP
#include <BCGCBProInc.h>	// BCGControlBar Pro
#else
//...
#endif // USING_LIB_BCGP
using namespace std;
#include <map>
#include <deque>


#ifdef USING_LIB_BCGP
class CDialogExMid : public CBCGPDialog
#else
class CDialogExMid : public CDialogEx
#endif // USING_LIB_BCGP
{
public:
	CDialogExMid(UINT nIDD,CWnd* pParent = NULL);	// 标准构造函数
	~CDialogExMid();
	UINT m_nIDD;// 对话框ID数据

protected:
	BOOL m_bMoveParent;//2017/05/23 zhangt 是否移动父窗口
   int m_nDlgFlag;//2019-2-21 wangzl 对话框标志 用于区分同样的资源ID但是不同的对话框默认标志为0

   //多国语言相关定义 yangjr 2019/04/09
   CString        m_LanTableName;         //对应界面存储多国语言时的表名
   bool           m_flagUsed;          //对话框被初始化过
   bool           m_isAllwaysChangeWhenInit;
   int            m_language;          // 语言   
   bool           m_isUINeedTranslate;   //是否需要翻译处理
   std::map<UINT,UINT> m_unLanguageCTRLID;  //不需要翻译的ID  
   BOOL                   m_bTranslateDlgTitle;  //是否自动翻译对话框标题
protected:
	DECLARE_MESSAGE_MAP()
	/*
	 * @brief	防止在对话框中安Enter键对话框消失
	 * @author	
	 */
	afx_msg LRESULT OnGetDefID(WPARAM wParam,LPARAM lParam); 

	/*
	 * @brief	响应客户区鼠标左键按下消息
	 * @author	
	 */
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	/*
	 * @brief	响应非客户区鼠标左键按下消息
	 * @author	
	 */
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);

   //获取对应控件id的控件类型字符串 yangjr 2017-12-14
   CString GetControlType(UINT nCtrlID);

   //从文件中获取数据刷新控件值 yangjr 2017-12-14
   void RefreshDefValue(int index);

   afx_msg void OnDestroy();
   
   void ClearCtrlInfo();

   void ResizeCtrl(const CRect rt);

   void UpdateControlsPermission();

private:
   std::map<int/*row*/,map<int/*index*/,ctrl_info*>>      m_map_ctrl_info;
   std::map<UINT,UINT> m_mapNewComboTranslation;	//comboBox下拉框内容需要新的翻译方式的控件ID
//窗口位置记忆相关 yangjr 2018/5/22
private:  
   //记录窗口位置相关变量	by yangjr 2018/05/22
   int		m_nWndPosX;					   //对话框窗口X位置
   int		m_nWndPosY;					   //对话框窗口Y位置
   bool		m_bIsRecordWndPos;			//是否记录对话框窗口位置
   CString	m_strRecordWndPosCfgPath;	//记录对话框窗口位置的配置文件路径
   bool		m_bCenterWnd;				   //是否第一次打开窗口时，中心显示
   bool		m_bIsRecordWndSize;			//是否记录窗口大小
   int		m_nWndCx;						//记录窗口大小
   int		m_nWndCy;						//记录窗口大小 
   bool		m_bRecordMinimizeState;		//是否记录最小化状态  
   bool		m_bRecordMaximizeState;		//是否记录最大化状态	
   DWORD		m_dwTickCount;					//记录初始化的时间点
   int		m_nDefaultWndCx;				//默认窗口宽度
   int		m_nDefaultWndCy;				//默认窗口高度

   void InitWndPosRecordVariable();	//初始化窗口位置记录功能的相关变量
   bool ReadWindowPosCfg();			//读取窗口位置信息配置
   void SaveWindowPosCfg();			//保存窗口位置信息配置
   void SetWindowPosByRecord();		//根据记录信息设置窗口位置
   void GetWindowPosRecord();			//获取窗口位置信息并记录  
   void SaveWindowMaximizeState();	//记录窗口最大化状态
   bool ReadWindowMaximizeState();	//读取窗口最大化状态

   void SaveWindowMinimizeState();	//记录窗口最小化状态
   bool ReadWindowMinimizeState();	//读取窗口最小化状态

   //获得当前子窗口连续CDialogExMid窗口的最顶层那个窗口，顺便获得中间所有窗口的IDD
   static CDialogExMid *GetTopParentWindowAndChildIDDs(CDialogExMid *pCurDlg, std::deque<int> *pdeqChildIDDs);
   CDialogExMid *GetTopParentWindowAndChildIDDs(std::deque<int> *pdeqChildIDDs);
   static CDialogExMid const* GetChildWindowByIDDs(const CDialogExMid *pWndParent, const std::deque<int> &deqIDDs);
   static CDialogExMid *GetChildWindowByIDD(const CDialogExMid *pWndParent, int nIDD);
protected:
   //开启窗口记录开关接口
   void EnableRecordWndPos(CString strRecordCfgPath, bool bRecord = true);
   //开启窗口中心显示接口（如果开启，且窗口为第一次打开，则窗口中心显示）；
   void EnableInitCenterWnd(bool bCenterWnd = true);

   void EnableRecordWndSize(bool bRecordSize = true);
   //设置默认窗口大小		
   void SetDefaultWndSize(int nWidth, int nHeight);   
   //开启记录最小化状态 的接口
   void EnableRecordMinimizeState(bool bRecordMinimizeState = true);
   //开启记录最大化状态
   void EnableRecordMaximizeState(bool bRecordMaximizeState = true);

   void AddNewTranslationComboBoxID(UINT combID);
   void AddUnLanguageCTRLID(UINT combID);//不需要读取数据库切换多国语言的控件ID,一般是combox yangjr 2019/04/09
public:
	virtual BOOL OnInitDialog();
   virtual void OnCancel();
   virtual void OnClose();
   virtual void OnOK();
   virtual BOOL ShowWindow(int nCmdShow);

   int GetDlgFlag(){return m_nDlgFlag;}
	/*
	 * @brief	触屏 长按可响应鼠标右击菜单
	 * @author	
	 */
	virtual ULONG GetGestureStatus(CPoint ptTouch){return 0;}

	/*
	 * @brief	拦截消息
	 * @author	
	 */
	virtual BOOL PreTranslateMessage(MSG* pMsg);

#ifdef USING_LIB_BCGP
   virtual void SetActiveMenu (CBCGPPopupMenu* pMenu);
#else
   void SetActiveMenu(CMFCPopupMenu* pMenu);
#endif //USING_LIB_BCGP
   afx_msg void OnInitMenu(CMenu* pMenu);
	/*
	 * @brief	设置MenuPopup菜单状态
	 * @author	
	 */
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);

   afx_msg void OnSize(UINT nType, int cx, int cy);

   /*
	 * @brief	通过当前对话框控件ID获取控件的默认值值
	 * 当前支持CEdit,CComboBox,CButton(CheckBox,RadioButton),CRichEditCtrl
	 * @author	2017/12/13 zhangt
	 * @note	1:CheckBox和RadioButton 获取值1表示选中 0表示未选中
	 */
	CString GetDefValueByID(UINT nCtrlID);

	/*
	 * @brief	通过当前对话框控件ID【注册】控件的默认值值
	 * 当前支持CEdit,CComboBox,CButton(CheckBox,RadioButton),CRichEditCtrl
	 * @author	2017/12/13 zhangt
	 * @note	1:CheckBox和RadioButton 获取值1表示选中 0表示未选中
	 */
	BOOL RegDefValueByID(UINT nCtrlID,CString strDefText);

   BOOL AddCtrlInfo(ctrl_info* p_ctl);

   //************************************
   // Parameter: UINT ID
   // Parameter: int irow     控件在第几行
   // Parameter: int index    当前行控件显示的顺序
   // Parameter: int width
   // Parameter: int height
   // Parameter: int ideltx      左右间隔
   // Parameter: int idelt_y     上下间隔
   //************************************
   BOOL AddCtrlInfo(HWND hwnd,int irow,int index,int width,int height,int ideltx = 0,int idelty = 0,float iXBeilv=1,float iYBeilv=1);
   //************************************
   // 按插入顺序自动排列
   // Parameter: UINT ID
   // Parameter: int irow     控件在第几行
   // Parameter: int width
   // Parameter: int height
   // Parameter: int ideltx      左右间隔
   // Parameter: int idelt_y     上下间隔
   //************************************
   BOOL AddCtrlInfo_auto_sort(HWND hwnd,int irow,int width,int height,int ideltx = 0,int idelty = 0,float iXBeilv=1,float iYBeilv=1);

   //************************************
   // Method:    ReplaceCtrlInfo
   // Parameter: int irow_old       旧的行号     --用来查找
   // Parameter: int index_old      旧的index    --用来查找
   // Parameter: HWND hwnd          新的窗口句柄
   // Parameter: int width
   // Parameter: int height
   // Parameter: int ideltx
   // Parameter: int idelty
   //************************************
   BOOL ReplaceCtrlInfo(int irow_old,int index_old,HWND hwnd_new,int width_new,int height_new,int ideltx_new = 0,int idelty_new = 0,float iXBeilv=1,float iYBeilv=1);

   //************************************
   // Method:    ReplaceCtrlInfo
   // Parameter: HWND hwnd_old      旧窗口句柄
   // Parameter: HWND hwnd_new      新窗口句柄
   // Parameter: int width_new      -1000表示使用旧的尺寸 
   // Parameter: int height_new     -1000表示使用旧的尺寸 
   // Parameter: int ideltx_new     -1000表示使用旧的尺寸 
   // Parameter: int idelty_new     -1000表示使用旧的尺寸 
   //************************************
   BOOL ReplaceCtrlInfo(HWND hwnd_old,HWND hwnd_new,int width_new = ctrl_info::iUseOldSize,int height_new =ctrl_info::iUseOldSize
      ,int ideltx_new = ctrl_info::iUseOldSize,int idelty_new = ctrl_info::iUseOldSize,float iXBeilv=1,float iYBeilv=1);
#ifdef USING_TAB_MANAGER
   //通过XML配置文件移动焦点
   static BOOL LeaveFocusByXML(WPARAM wParamKey, CWnd *pControl);
#endif /*USING_TAB_MANAGER*/

   virtual BOOL OnLanguageChange();  //语言变化时刷新界面显示   
   void ChangeLanguageWhenInit();//当此函数被调用，则每次OnInitDialog时，都会再次调用OnLanguageChange接口，读取语言数据

    CString m_DlgName;//对话框标识 
};