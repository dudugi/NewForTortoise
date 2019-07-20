#pragma once
#include "rnstring.h"
#include <winnt.h>
#include <WinBase.h>
/*-------------------------------------------------------------------
-@brief [���CRect�Ƿ�Ϊһ���Ϸ�������]
-
-[������ϸ����]
-@n<b>��������</b>    : RectValid
-@n@param CRect & _rt : [��������]
-@return                [����ֵ����]
-@see                   [�μ�����]
-@n<b>����</b>        :  
-@n<b>����ʱ��</b>    : 2009-3-17 15:12:48
-@version    �޸���        ʱ��        ����@n
-@n                     2009-03-17  [����]
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


//ɾ��HObject
#define  SafeDeleteHObj(hObj) \
   if(NULL != hObj) \
   { \
   DeleteObject(hObj); \
   hObj = NULL; \
   }


//ɾ��GDI����
#define  SafeDeleteGdiObj(pObj) \
   if(NULL != pObj) \
   { \
   pObj->DeleteObject(); \
   pObj = NULL; \
   }

//ɾ���߳�
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

//ɾ��UI����
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
{//����Ч���������ռ�

   /*-------------------------------------------------------------------
   -@brief [Բ�ǽ���]
   -
   -[������ϸ����]
   -@n<b>��������</b>      : RoundDlgFace
   -@n@param CWnd * pWnd   : [Ҫ����Բ�Ǵ���Ĵ���]
   -@param   UINT   nAngel : [Բ�ǳ̶�]
   -@see                     [�μ�����]
   -@n<b>����</b>          :  
   -@n<b>����ʱ��</b>      : 2009-3-17 16:23:06
   -@version    �޸���        ʱ��        ����@n
   -@n                     2009-03-17  [����]
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
   //��ȡ�ؼ���������ַ���
   inline CString GetWndStr(const CWnd* pWnd)
   {
      ASSERT(pWnd->GetSafeHwnd());
      CString str;
      pWnd->GetWindowText(str);
      return str;
   }
   //��ȡ�ؼ������������ֵ
   inline int GetWndInt(const CWnd* pWnd)
   {
      ASSERT(pWnd->GetSafeHwnd());
      CString str = TNULL;
      pWnd->GetWindowText(str);
      int nResult = _ttoi(str);
      return nResult;
   }
   //��ȡ�ؼ�������ĸ���ֵ
   inline double GetWndDouble(const CWnd* pWnd)
   {
      ASSERT(pWnd->GetSafeHwnd());
      CString str = TNULL;
      pWnd->GetWindowText(str);
      double dResult = _tstof(str);
      return dResult;
   }

   //��ȡ�ؼ��Ŀͻ���
   inline CRect GetRectClient(const CWnd* pWnd)
   {
      ASSERT(pWnd->GetSafeHwnd());
      CRect rectX;
      pWnd->GetClientRect( rectX );
      return rectX;
   }

   //��ȡ�ؼ��Ĵ�����
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
         //������ݰ汾��Ϣ�жϲ���ϵͳ���� 
         switch(os.dwMajorVersion) //�ж����汾�� 
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