// FoldGridCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "FoldGridCtrl.h"

// FoldGridCtrl

IMPLEMENT_DYNAMIC(CFoldGridCtrl, CBCGPGridCtrl)

static BCGP_GRID_COLOR_DATA theme = 
{
   -1,	// Grid background color
   RGB (50, 50, 50),	// Grid foreground color
   -1,	// Header foreground color

   {	// Even rows colors:
      RGB (238, 238, 238), -1, -1, 0, -1
   },

   {	// Odd rows colors:
      -1, -1, -1, 0, -1
      },

      {	// Group colors:
         RGB (155, 230, 240), RGB (72, 105, 148), RGB (255, 255, 255), 90, -1
      },

      {	// Selected group colors:
         RGB (117, 150, 188), RGB (249, 250, 252), RGB (183, 200, 220), 90, -1
         },

         {	// Selected colors:
            RGB (175, 194, 217), RGB (52, 77, 108), RGB (222, 230, 240), 90, RGB (175, 194, 217)
         },

         {	// Header item colors:
            RGB (215, 218, 227), RGB (72, 105, 148), RGB (244, 245, 248), 90, RGB (173, 183, 205)
            },

            {	// Selected header item colors:
               RGB (251, 157, 105), RGB (52, 77, 108), RGB (254, 204, 153), 90, RGB (173, 183, 205)
            },

            {	// Left offset colors:
               RGB (215, 218, 227), -1, RGB (244, 245, 248), 0, RGB (173, 183, 205)
               },

               -1,	// Grid horizontal line
               -1,	// Grid vertical line
               -1,	// Description text color
};

CFoldGridCtrl::CFoldGridCtrl()
{
}

CFoldGridCtrl::~CFoldGridCtrl()
{
}


BEGIN_MESSAGE_MAP(CFoldGridCtrl, CBCGPGridCtrl)
   ON_WM_CREATE()
   ON_WM_DESTROY()
END_MESSAGE_MAP()


int CFoldGridCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
   if (CBCGPGridCtrl::OnCreate(lpCreateStruct) == -1)
      return -1;

   EnableMultipleSort();
   EnableHeader (TRUE, BCGP_GRID_HEADER_MOVE_ITEMS | BCGP_GRID_HEADER_SORT);
   EnableRowHeader (TRUE);
   EnableLineNumbers ();//行号显示
   EnableInvertSelOnCtrl ();//ctrl键选中取消
   SetScalingRange (0.1, 4.0);//设置缩放比例

   //列添加
   InsertColumn(0,_T("菜单名称"),300);
   InsertColumn(1,_T("修改菜单"),300);
   InsertColumn(2,_T("Group"),300);
   InsertColumn(3,_T("ID"),300);
   SetColumnVisible(2,FALSE);
   SetColumnVisible(3,FALSE);
   //-----------------------
   // Group by first column:
   //-----------------------
   InsertGroupColumn (0, 2);

   SetScalingRange (0.1, 4.0);

   UpdateColorTheme();
   //SetReadOnly(TRUE);
   AdjustLayout();
   return 0;
}

void CFoldGridCtrl::OnDestroy() 
{
   //SaveState (_T("ColorGrid"));
   CBCGPGridCtrl::OnDestroy();
} 

int CFoldGridCtrl::CompareGroup( CBCGPGridRow* pRow1,CBCGPGridRow* pRow2,int comlun)
{
   return CBCGPGridCtrl::CompareGroup (pRow1, pRow2, comlun);
}

CString CFoldGridCtrl::GetGroupName( int nComlun,CBCGPGridItem*pItem )
{
   ASSERT_VALID (this);
   ASSERT_VALID (pItem);

   CString str;
   int nValue = 0;
   str = _T("");
   nValue = pItem->GetValue();
   //if ((nValue-1) <DRAWER_MENU_NUM)
   //{
   //   str=g_szDrawerMenu[nValue-1];
   //}
   //else
   //{
   //     str.Format(_T("%d"),nComlun);
   //}
   return str;

}

// FoldGridCtrl 消息处理程序
//void CFoldGridCtrl::SetGridItemData(CDBMenusInfoList &menuLis,int nPCount)
//{
//   int nCount = menuLis.GetCount();
//   int nColumIndex = 0;
//   
//   for (int nIndex = 1;nIndex<=nCount;++nIndex)
//   {
//      auto pItem = menuLis.GetItem(nIndex);
//      if (NULL != pItem && 0 != pItem->m_nPID)
//      {
//         CBCGPGridRow* pRow = CreateRow (GetColumnCount ());
//
//         //0 原始菜单名称
//         //1 显示菜单名称
//         //2 pid
//         //3 id
//         pRow->GetItem(0)->SetValue((LPCTSTR)pItem->m_strItemName);
//         pRow->GetItem(0)->AllowEdit(FALSE);
//         pRow->GetItem(1)->SetValue((LPCTSTR)(pItem->m_strItemShow.IsEmpty() ? pItem->m_strItemName : pItem->m_strItemShow));
//         pRow->GetItem(1)->AllowEdit(TRUE);
//         pRow->GetItem(2)->SetValue(pItem->m_nPID);
//         pRow->GetItem(2)->AllowEdit(FALSE);
//         pRow->GetItem(3)->SetValue(pItem->m_nID);
//         pRow->GetItem(3)->AllowEdit(FALSE);
//
//         AddRow(pRow,FALSE);
//         nColumIndex++;
//      }
//   }
//}

void CFoldGridCtrl::UpdateColorTheme()
{
   CBCGPGridColors colors;
   colors.m_EvenColors.m_clrBackground = RGB(224,255,255);
   colors.m_SelColors.m_clrBackground = RGB(255,232,166);
    colors.m_LeftOffsetColors.m_clrBackground = RGB(255,255,255);
   //CBCGPVisualManager::GetInstance ()->OnSetGridColorTheme (this, colors);
   SetColorTheme (colors);
}

