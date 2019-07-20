#pragma once


// FoldGridCtrl
//菜单管理折叠表格
//#include "DBMenusInfo.h"
#include "QLBCGGridCtrl.h"
class CFoldGridCtrl : public CQLBCGGridCtrl
{
	DECLARE_DYNAMIC(CFoldGridCtrl)

public:
	CFoldGridCtrl();
	virtual ~CFoldGridCtrl();

   BCGP_GRID_COLOR_DATA	m_Themes;

   //父类方法重写
   virtual int CompareGroup(CBCGPGridRow* pRow1,CBCGPGridRow* pRow2,int);
   virtual CString GetGroupName(int,CBCGPGridItem*pItem);
   //void SetGridItemData(CDBMenusInfoList &menuList,int nPCount);
   void UpdateColorTheme();
protected:
   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()
};


