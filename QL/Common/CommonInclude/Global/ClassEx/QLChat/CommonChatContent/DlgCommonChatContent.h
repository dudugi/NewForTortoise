#pragma once
/*************************************************
// <文件>: DlgCommonChatContent.h
// <说明>: 常用聊天内容 可以选择候选项快速输出 可以编辑候选项
// <作者>: duchen
// <日期>: 2019/02/22
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#include "afxwin.h"
#include <functional>
#include <deque>
#include "ListBoxHover.h"
#include "..\Bubble\MyBubble.h"


// CDlgCommonChatContent 对话框

class CDlgCommonChatContent : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCommonChatContent)

public:
	CDlgCommonChatContent(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgCommonChatContent();

// 对话框数据

   std::function<void(const CString &sText)> m_funcOutputText; //输出文字的回调函数
   std::function<void(const CString &sText)> m_funcCreateText; //目前没用
   void SetSettingPath(const CString &sPath); //设置记录候选项的配置文件的路径
   BOOL CreateDlgIndirect(CWnd* pParent); //创建对话框用的接口 可以不依赖资源文件创建
   void Init(int nXLeft = -1, int nYBottom = -1); //初始化函数
protected:
	DECLARE_MESSAGE_MAP()
private:
   CListBoxHover m_lstBox; //候选项Listbox控件 点右侧的“笔”图标可以进入编辑画面
   CEdit m_EditFilter; //文字输入框控件 可以用来筛选候选项
   enum Status //画面状态
   {
      SELECT_CONTENT, //选择常用文字画面
      CREATE_CONTENT, //创建常用文字画面
      EDIT_CONTENT,   //编辑常用文字画面
      DELETE_CONFIRM, //删除常用文字确认画面
   };
   Status m_eStatus; //画面状态

   CButton m_btnAdd; //添加按钮
   CButton m_btnReturn; //返回按钮
   CButton m_btnDeleteConfirm; //删除确认按钮
   CStatic m_staticTitleCreate; //创建画面显示文字
   CFont m_ListFont; //列表字体
   CFont m_HintFont; //说明文字字体
   CFont m_BigHintFont; //大说明文字字体
   std::deque<CString> m_deqContents; //所有常用文字内容
   CButton m_btnCreateOK; //创建画面确定按钮
   CEdit m_editNew; //创建画面文字编辑控件
   CButton m_btnDelete; //删除按钮
   CButton m_btnEditFinish; //编辑完成按钮
   CString m_sEditItemStringOld; //编辑前字符串 用来判断编辑前后有无变化
   CMyBubble m_Bubble; //小提示窗（气泡状）
   int m_nXLeft; //窗口最左侧坐标
   int m_nYBottom; //窗口最下方坐标
   CString m_sSettingFilePath; //配置文件的路径（保存常用文字的地方）
   void ShowEditWindow(BOOL bNew, const CString &sInitText); //进入编辑画面（创建或修改）
   void TurnBack(); //返回前画面
   BOOL WriteFile(); //写入配置文件
   afx_msg void OnBnClickedBtnReturn(); //返回按钮
   afx_msg void OnLbnSelchangeListContent(); //选择文字
   afx_msg void OnEnChangeEditSearch(); //文字变化
   afx_msg void OnBnClickedBtnAdd(); //添加按钮
   virtual void OnOK(); //防止回车退出，所以覆盖了这个虚函数
   afx_msg void OnBnClickedBtnCreateOk(); //创建常用文字确定按钮按下
   virtual BOOL OnInitDialog(); //初始化，创建字体对象，设置内部控件的回调函数，设置内部控件坐标等
   afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized); //用来鼠标点击窗口其它区域时隐藏窗口
   afx_msg BOOL OnEraseBkgnd(CDC* pDC); //根据画面状态显示不同文字等
   afx_msg void OnShowWindow(BOOL bShow, UINT nStatus); //目前没用
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
   afx_msg void OnBnClickedBtnEditFinish(); //编辑完成
   afx_msg void OnBnClickedBtnDelete(); //删除
   afx_msg void OnBnClickedBtnDeleteConfirm(); //确认删除
   virtual BOOL PreTranslateMessage(MSG* pMsg); //将主窗口滚轮事件传给内部listbox，让listbox上下滚动
};
