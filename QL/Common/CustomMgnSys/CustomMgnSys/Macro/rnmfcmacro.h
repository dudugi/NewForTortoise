#pragma once
#include "rnstring.h"
#include <winnt.h>
#include <WinBase.h>
/*-------------------------------------------------------------------
-@brief [检查CRect是否为一个合法的区域]
-
-[函数详细描述]
-@n<b>函数名称</b>    : RectValid
-@n@param CRect & _rt : [参数描述]
-@return                [返回值描述]
-@see                   [参见函数]
-@n<b>作者</b>        :  
-@n<b>创建时间</b>    : 2009-3-17 15:12:48
-@version    修改者        时间        描述@n
-@n                     2009-03-17  [描述]
--------------------------------------------------------------------*/
inline BOOL RectValid(CRect& _rt)
{
   if ( _rt.left >= 0
      && _rt.top >= 0 
      && _rt.right >= _rt.left
      && _rt.bottom >= _rt.top )
   {
      return TRUE;
   }

   return FALSE;
}


//删除HObject
#define  SafeDeleteHObj(hObj) \
   if(NULL != hObj) \
   { \
   DeleteObject(hObj); \
   hObj = NULL; \
   }


//删除GDI对象
#define  SafeDeleteGdiObj(pObj) \
   if(NULL != pObj) \
   { \
   pObj->DeleteObject(); \
   pObj = NULL; \
   }

//删除线程
inline void DeleteThread(CWinThread* &_pThread)
{
   DWORD dw;
   if ( NOT_NULL(_pThread) )
   {
      GetExitCodeThread(_pThread->m_hThread, &dw);
      if ( EQUAL(STILL_ACTIVE, dw) )
      {
         TerminateThread(_pThread, dw);
      }
   }
}

//删除UI对象
#define DeleteUIObj(pUIObj) \
   if(NULL != pUIObj) \
{ \
   if(pUIObj->GetSafeHwnd()) \
{ \
   pUIObj->DestroyWindow(); \
   SAFE_DELETE(pUIObj); \
} \
}

inline void RnMessageBox( CString str )
{
   AfxMessageBox( str );
}

inline void DebugMessageBox( CString str )
{
#ifdef _DEBUG
   AfxMessageBox( str );
#endif
}

#define  DbgMsgBox_A() \
{ \
   int nL = __LINE__; \
   char* psz = __FILE__; \
   std::string strA( psz ); \
   CString strF = strA.c_str(); \
   strF = strF + IntToCStr( nL ); \
   DebugMessageBox( strF ); \
}

#define  DbgMsgBox_W() \
{ \
   int nL = __LINE__; \
   char* psz = __FILE__; \
   std::string strA( psz ); \
   std::wstring strW = _T(""); \
   ACP_TO_UNICODE(strA, strW); \
   CString strF = strW.c_str(); \
   strF = strF + IntToCStr( nL ); \
   DebugMessageBox( strF ); \
}

#define  DbgMsgBox_R() \
{ \
   DbgMsgBox; \
   return; \
}


#define DbgMsgBox() \
{ \
	DbgMsgBox_W(); \
}

namespace RnMfcMacro
{//界面效果的命名空间

   /*-------------------------------------------------------------------
   -@brief [圆角界面]
   -
   -[函数详细描述]
   -@n<b>函数名称</b>      : RoundDlgFace
   -@n@param CWnd * pWnd   : [要进行圆角处理的窗体]
   -@param   UINT   nAngel : [圆角程度]
   -@see                     [参见函数]
   -@n<b>作者</b>          :  
   -@n<b>创建时间</b>      : 2009-3-17 16:23:06
   -@version    修改者        时间        描述@n
   -@n                     2009-03-17  [描述]
   --------------------------------------------------------------------*/
   inline void RoundDlgFace(CWnd* pWnd, UINT nAngel = 20)
   {
      CRect rectUICircle;
      pWnd->GetClientRect( &rectUICircle );

      HRGN rgnUICircle;
      rgnUICircle = CreateRoundRectRgn( 0, 0, rectUICircle.Width(), rectUICircle.Height(), nAngel, nAngel );
      pWnd->SetWindowRgn( rgnUICircle, TRUE );
      SafeDeleteHObj(rgnUICircle);
   }
   //----------------------------------
   //获取控件上输入的字符串
   inline CString GetWndStr(const CWnd* pWnd)
   {
      ASSERT(pWnd->GetSafeHwnd());
      CString str;
      pWnd->GetWindowText(str);
      return str;
   }
   //获取控件上输入的整型值
   inline int GetWndInt(const CWnd* pWnd)
   {
      ASSERT(pWnd->GetSafeHwnd());
      CString str = TNULL;
      pWnd->GetWindowText(str);
      int nResult = _ttoi(str);
      return nResult;
   }
   //获取控件上输入的浮点值
   inline double GetWndDouble(const CWnd* pWnd)
   {
      ASSERT(pWnd->GetSafeHwnd());
      CString str = TNULL;
      pWnd->GetWindowText(str);
      double dResult = _tstof(str);
      return dResult;
   }

   //获取控件的客户区
   inline CRect GetRectClient(const CWnd* pWnd)
   {
      ASSERT(pWnd->GetSafeHwnd());
      CRect rectX;
      pWnd->GetClientRect( rectX );
      return rectX;
   }

   //获取控件的窗体区
   inline CRect GetRectWnd(const CWnd* pWnd)
   {
      ASSERT(pWnd->GetSafeHwnd());
      CRect rectX;
      pWnd->GetWindowRect( rectX );
      return rectX;
   }
   inline BOOL IsSystemWin7OrXP()
   {      
      BOOL retValue = FALSE;
      OSVERSIONINFOEX os; 
      os.dwOSVersionInfoSize=sizeof(OSVERSIONINFOEX);   
      if(GetVersionEx((OSVERSIONINFO *)&os))                  
      {
         //下面根据版本信息判断操作系统名称 
         switch(os.dwMajorVersion) //判断主版本号 
         {                       
         case 4: 
         case 5: 
            retValue = TRUE;
            break; 
         case 6:
            if(os.dwMinorVersion>1)
               retValue = FALSE;
            else
               retValue = TRUE;
            break; 
         default: 
            retValue = FALSE;
            break; 
         }          
      } 
     return retValue;
   }
}//end of namespace UIEffect