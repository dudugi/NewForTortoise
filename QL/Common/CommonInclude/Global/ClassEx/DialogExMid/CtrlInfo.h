#pragma once


//控件信息，基类用来处理自动onsize add by lida 2018/05/17

//static、checkbox 控件要向下偏移5个位置，这样看起来才能和其他控件对齐

class ctrl_info      
{
public:
   ctrl_info()
   {
      m_hwnd      = nullptr;     
      m_iRow      = 0;        
      m_iIndex    = 0;      
      m_iWidth    = 0;      
      m_iHeight   = 0;    
      m_ideltx    = 0;
      m_idelty    = 0;
      m_iuse_rt_width = 0;
      m_iuse_rt_height = 0;
      m_iXBeilv = 1;//剩余宽度的几分之几
      m_iYBeilv = 1;//剩余高度的几分之几
   };
   ~ctrl_info()
   {
      m_hwnd      = nullptr;     
      m_iRow      = 0;        
      m_iIndex    = 0;      
      m_iWidth    = 0;      
      m_iHeight   = 0;    
      m_ideltx    = 0;
      m_idelty    = 0;
      m_iuse_rt_width = 0;
      m_iuse_rt_height = 0;
      m_iXBeilv = 1;//剩余宽度的几分之几
      m_iYBeilv = 1;//剩余高度的几分之几
   };

public:
   enum
   {
      idelt_top = 5,       //上间隔
      idelt_bottom = 5,    //下间隔
      idelt_left = 5,      //左
      idelt_right = 5,     //右
      ilast_height = -1,   //使用区域剩余高度用作当前高度
      ilast_width = -1,    //使用区域剩余宽度用作当前宽度
      iUseOldSize = -1000  //使用旧的宽度或高度
   };

public:
   HWND     m_hwnd;        //控件句柄
   int      m_iRow;        //行号
   int      m_iIndex;      //从左到右显示的顺序
   int      m_iWidth;      //宽
   int      m_iHeight;     //高
   int      m_ideltx;      //间隔，当前控件和上一控件之间的间隔
   int      m_idelty;      //间隔，控件和控件上下之间的间隔

   int      m_iuse_rt_width;
   int      m_iuse_rt_height;

   float m_iXBeilv;//剩余宽度的几分之几 yangjr2018/6/25
   float m_iYBeilv;//剩余高度的几分之几 yangjr 2018/6/25
};