#include "StdAfx.h"
#include "DBProcessRecords_V.h"
#include "DBKeyDef_V.h"
#ifdef USING_GRIDCTRL_MARK
#include "CGlobalDefine.h"
#endif // USING_GRIDCTRL_MARK

///////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CDBProcessRecords_VData,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBProcessRecords_VList,  CDataListMid, 1)

std::shared_ptr<CDBProcessRecords_VList> CDBProcessRecords_VList::sm_inst;

CDBProcessRecords_VData::CDBProcessRecords_VData()
{
   ResetData(); 
} 

CDBProcessRecords_VData::~CDBProcessRecords_VData()
{
}

void CDBProcessRecords_VData::ResetData()
{
   m_nID                = 0;
   m_strCode            = _T("");
   m_strGXName          = _T("");
   m_strDate1           = _T("");
   m_strDate3           = _T("");
   m_strPersonCode      = _T("");
   m_fGongjia           = 0;
   m_fFujia             = 0;
   m_strMemo            = _T("");
   m_nState             = 0;
   m_strAllotPersonCode = _T("");
   m_nPriority          = 0;
   m_nFlag              = 0;
   m_nCurProcess        = 0;
   m_strDateAssign      = _T("");
   m_nChecked           = 0;
   m_nRewindNum         = 0;
   m_nRewindFrom        = 0;
   m_strCate            = _T("");
   m_strDate            = _T("");
   m_strMaker           = _T("");
   m_strCusCode         = _T("");
   m_strInvCustCode     = _T("");
   m_strInvCustName     = _T("");
   m_nAllJianshu        = 0;
   m_strInvKuanhao      = _T("");
   m_strInvJinxian      = _T("");
   m_strInvLingxing     = _T("");
   m_strInvDibian       = _T("");
   m_strInvJiagongfei   = _T("");
   m_strInvFujiafei     = _T("");
   m_strSexType         = _T("");
   m_strShouYao         = _T("");
   m_strZhiYiCode       = _T("");
   m_strJiaoDate        = _T("");
   m_strTrueTime        = _T("");
   m_strNeedleType      = _T("");
   m_nOtherFlag         = 0;
   m_nOrdCreateFlag     = 0;
   m_strMacType         = _T("");
   m_strClassType       = _T("");
   m_strAmountType      = _T("");
   m_strGoodsType       = _T("");
   m_strInvXiukou       = _T("");
   m_strInvJiaji        = _T("");
   m_strInvMemo         = _T("");
   m_strInvState        = _T("");
   m_strInvFahuoDate    = _T("");
   m_strInvState2       = _T("");
   m_strInvSehao        = _T("");
   m_strInvPeise        = _T("");
   m_strCusName         = _T("");
   m_strCusMobile       = _T("");
   m_strKuanming        = _T("");
   m_strTreeName        = _T("");
   m_strChenfen         = _T("");
   m_strColorCate       = _T("");
   m_strCusCate         = _T("");
   m_nChuguan           = 0;
   m_fChuweight         = 0;
   m_nHuiguan           = 0;
   m_fHuiweight         = 0;
   m_fPianweight        = 0;
   m_fGuanweight        = 0;
   m_strPihao           = _T("");
   m_strPersonName      = _T("");
   m_strAllotPersonName = _T("");
   m_strbiflag = _T("0");


}

void CDBProcessRecords_VData:: Copy(CDBProcessRecords_VData *pData)
{
   ASSERT(pData != NULL);
   CDataMid::Copy(pData);

   m_nID                = pData->m_nID               ;
   m_strCode            = pData->m_strCode           ;
   m_strGXName          = pData->m_strGXName         ;
   m_strDate1           = pData->m_strDate1          ;
   m_strDate3           = pData->m_strDate3          ;
   m_strPersonCode      = pData->m_strPersonCode     ;
   m_fGongjia           = pData->m_fGongjia          ;
   m_fFujia             = pData->m_fFujia            ;
   m_strMemo            = pData->m_strMemo           ;
   m_nState             = pData->m_nState            ;
   m_strAllotPersonCode = pData->m_strAllotPersonCode;
   m_nPriority          = pData->m_nPriority         ;
   m_nFlag              = pData->m_nFlag             ;
   m_nCurProcess        = pData->m_nCurProcess       ;
   m_strDateAssign      = pData->m_strDateAssign     ;
   m_nChecked           = pData->m_nChecked          ;
   m_nRewindNum         = pData->m_nRewindNum        ;
   m_nRewindFrom        = pData->m_nRewindFrom       ;
   m_strCate            = pData->m_strCate           ;
   m_strDate            = pData->m_strDate           ;
   m_strMaker           = pData->m_strMaker          ;
   m_strCusCode         = pData->m_strCusCode        ;
   m_strInvCustCode     = pData->m_strInvCustCode    ;
   m_strInvCustName     = pData->m_strInvCustName    ;
   m_nAllJianshu        = pData->m_nAllJianshu       ;
   m_strInvKuanhao      = pData->m_strInvKuanhao     ;
   m_strInvJinxian      = pData->m_strInvJinxian     ;
   m_strInvLingxing     = pData->m_strInvLingxing    ;
   m_strInvDibian       = pData->m_strInvDibian      ;
   m_strInvJiagongfei   = pData->m_strInvJiagongfei  ;
   m_strInvFujiafei     = pData->m_strInvFujiafei    ;
   m_strSexType         = pData->m_strSexType        ;
   m_strShouYao         = pData->m_strShouYao        ;
   m_strZhiYiCode       = pData->m_strZhiYiCode      ;
   m_strJiaoDate        = pData->m_strJiaoDate       ;
   m_strTrueTime        = pData->m_strTrueTime       ;
   m_strNeedleType      = pData->m_strNeedleType     ;
   m_nOtherFlag         = pData->m_nOtherFlag        ;
   m_nOrdCreateFlag     = pData->m_nOrdCreateFlag    ;
   m_strMacType         = pData->m_strMacType        ;
   m_strClassType       = pData->m_strClassType      ;
   m_strAmountType      = pData->m_strAmountType     ;
   m_strGoodsType       = pData->m_strGoodsType      ;
   m_strInvXiukou       = pData->m_strInvXiukou      ;
   m_strInvJiaji        = pData->m_strInvJiaji       ;
   m_strInvMemo         = pData->m_strInvMemo        ;
   m_strInvState        = pData->m_strInvState       ;
   m_strInvFahuoDate    = pData->m_strInvFahuoDate   ;
   m_strInvState2       = pData->m_strInvState2      ;
   m_strInvSehao        = pData->m_strInvSehao       ;
   m_strInvPeise        = pData->m_strInvPeise       ;
   m_strCusName         = pData->m_strCusName        ;
   m_strCusMobile       = pData->m_strCusMobile      ;
   m_strKuanming        = pData->m_strKuanming       ;
   m_strTreeName        = pData->m_strTreeName       ;
   m_strChenfen         = pData->m_strChenfen        ;
   m_strColorCate       = pData->m_strColorCate      ;
   m_strCusCate         = pData->m_strCusCate        ;
   m_nChuguan           = pData->m_nChuguan          ;
   m_fChuweight         = pData->m_fChuweight        ;
   m_nHuiguan           = pData->m_nHuiguan          ;
   m_fHuiweight         = pData->m_fHuiweight        ;
   m_fPianweight        = pData->m_fPianweight       ;
   m_fGuanweight        = pData->m_fGuanweight       ;
   m_strPihao           = pData->m_strPihao          ;
   m_strPersonName      = pData->m_strPersonName     ;
   m_strAllotPersonName = pData->m_strAllotPersonName;
   m_strbiflag          = pData->m_strbiflag;
  
}

BOOL CDBProcessRecords_VData::GetAllDBInfo(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);

   BOOL bRet = FALSE;

   if (NULL != pADOConn)
   {
      m_nID               = pADOConn->GetValueInt64 (DBProcessRecords_V_key_ID               );
      m_strCode           = pADOConn->GetValueString(DBProcessRecords_V_key_cCode            );
      m_strGXName         = pADOConn->GetValueString(DBProcessRecords_V_key_cGXName          );
      m_strDate1          = pADOConn->GetValueString(DBProcessRecords_V_key_dDate1           );
      m_strDate3          = pADOConn->GetValueString(DBProcessRecords_V_key_dDate3           );
      m_strPersonCode     = pADOConn->GetValueString(DBProcessRecords_V_key_cPersonCode      );
      m_fGongjia          = pADOConn->GetValueDouble(DBProcessRecords_V_key_iGongjia         );
      m_fFujia            = pADOConn->GetValueDouble(DBProcessRecords_V_key_iFujia           );
      m_strMemo           = pADOConn->GetValueString(DBProcessRecords_V_key_cMemo            );
      m_nState            = pADOConn->GetValueInt   (DBProcessRecords_V_key_iState           );
      m_strAllotPersonCode= pADOConn->GetValueString(DBProcessRecords_V_key_cAllotPersonCode );
      m_nPriority         = pADOConn->GetValueInt   (DBProcessRecords_V_key_iPriority        );
      m_nFlag             = pADOConn->GetValueInt   (DBProcessRecords_V_key_iFlag            );
      m_nCurProcess       = pADOConn->GetValueInt   (DBProcessRecords_V_key_iCurProcess      );
      m_strDateAssign     = pADOConn->GetValueString(DBProcessRecords_V_key_dDateAssign      );
      m_nChecked          = pADOConn->GetValueInt   (DBProcessRecords_V_key_iChecked         );
      m_nRewindNum        = pADOConn->GetValueInt   (DBProcessRecords_V_key_nRewindNum       );
      m_nRewindFrom       = pADOConn->GetValueInt64 (DBProcessRecords_V_key_nRewindFrom      );
      m_strCate           = pADOConn->GetValueString(DBProcessRecords_V_key_cCate            );
      m_strDate           = pADOConn->GetValueString(DBProcessRecords_V_key_dDate            );
      m_strMaker          = pADOConn->GetValueString(DBProcessRecords_V_key_cMaker           );
      m_strCusCode        = pADOConn->GetValueString(DBProcessRecords_V_key_cCusCode         );
      m_strInvCustCode    = pADOConn->GetValueString(DBProcessRecords_V_key_cInvCustCode     );
      m_strInvCustName    = pADOConn->GetValueString(DBProcessRecords_V_key_cInvCustName     );
      m_nAllJianshu       = pADOConn->GetValueInt   (DBProcessRecords_V_key_iAllJianshu      );
      m_strInvKuanhao     = pADOConn->GetValueString(DBProcessRecords_V_key_cInvKuanhao      );
      m_strInvJinxian     = pADOConn->GetValueString(DBProcessRecords_V_key_cInvJinxian      );
      m_strInvLingxing    = pADOConn->GetValueString(DBProcessRecords_V_key_cInvLingxing     );
      m_strInvDibian      = pADOConn->GetValueString(DBProcessRecords_V_key_cInvDibian       );
      m_strInvJiagongfei  = pADOConn->GetValueString(DBProcessRecords_V_key_cInvJiagongfei   );
      m_strInvFujiafei    = pADOConn->GetValueString(DBProcessRecords_V_key_cInvFujiafei     );
      m_strSexType        = pADOConn->GetValueString(DBProcessRecords_V_key_cSexType         );
      m_strShouYao        = pADOConn->GetValueString(DBProcessRecords_V_key_cShouYao         );
      m_strZhiYiCode      = pADOConn->GetValueString(DBProcessRecords_V_key_cZhiYiCode       );
      m_strJiaoDate       = pADOConn->GetValueString(DBProcessRecords_V_key_dJiaoDate        );
      m_strTrueTime       = pADOConn->GetValueString(DBProcessRecords_V_key_dTrueTime        );
      m_strNeedleType     = pADOConn->GetValueString(DBProcessRecords_V_key_cNeedleType      );
      m_nOtherFlag        = pADOConn->GetValueInt   (DBProcessRecords_V_key_iOtherFlag       );
      m_nOrdCreateFlag    = pADOConn->GetValueInt   (DBProcessRecords_V_key_iOrdCreateFlag   );
      m_strMacType        = pADOConn->GetValueString(DBProcessRecords_V_key_cMacType         );
      m_strClassType      = pADOConn->GetValueString(DBProcessRecords_V_key_cClassType       );
      m_strAmountType     = pADOConn->GetValueString(DBProcessRecords_V_key_cAmountType      );
      m_strGoodsType      = pADOConn->GetValueString(DBProcessRecords_V_key_cGoodsType       );
      m_strInvXiukou      = pADOConn->GetValueString(DBProcessRecords_V_key_cInvXiukou       );
      m_strInvJiaji       = pADOConn->GetValueString(DBProcessRecords_V_key_cInvJiaji        );
      m_strInvMemo        = pADOConn->GetValueString(DBProcessRecords_V_key_cInvMemo         );
      m_strInvState       = pADOConn->GetValueString(DBProcessRecords_V_key_cInvState        );
      m_strInvFahuoDate   = pADOConn->GetValueString(DBProcessRecords_V_key_cInvFahuoDate    );
      m_strInvState2      = pADOConn->GetValueString(DBProcessRecords_V_key_cInvState2       );
      m_strInvSehao       = pADOConn->GetValueString(DBProcessRecords_V_key_cInvSehao        );
      m_strInvPeise       = pADOConn->GetValueString(DBProcessRecords_V_key_cInvPeise        );
      m_strCusName        = pADOConn->GetValueString(DBProcessRecords_V_key_cCusName         );
      m_strCusMobile      = pADOConn->GetValueString(DBProcessRecords_V_key_cCusMobile       );
      m_strKuanming       = pADOConn->GetValueString(DBProcessRecords_V_key_cKuanming        );
      m_strTreeName       = pADOConn->GetValueString(DBProcessRecords_V_key_cTreeName        );
      m_strChenfen        = pADOConn->GetValueString(DBProcessRecords_V_key_cChenfen         );
      m_strColorCate      = pADOConn->GetValueString(DBProcessRecords_V_key_cColorCate       );
      m_strCusCate        = pADOConn->GetValueString(DBProcessRecords_V_key_cCusCate         );
      m_nChuguan          = pADOConn->GetValueInt   (DBProcessRecords_V_key_iChuguan         );
      m_fChuweight        = pADOConn->GetValueDouble(DBProcessRecords_V_key_iChuweight       );
      m_nHuiguan          = pADOConn->GetValueInt   (DBProcessRecords_V_key_iHuiguan         );
      m_fHuiweight        = pADOConn->GetValueDouble(DBProcessRecords_V_key_iHuiweight       );
      m_fPianweight       = pADOConn->GetValueDouble(DBProcessRecords_V_key_iPianweight      );
      m_fGuanweight       = pADOConn->GetValueDouble(DBProcessRecords_V_key_iGuanweight      );
      m_strPihao          = pADOConn->GetValueString(DBProcessRecords_V_key_cPihao           );
      m_strPersonName     = pADOConn->GetValueString(DBProcessRecords_V_key_cPersonName      );
      m_strAllotPersonName= pADOConn->GetValueString(DBProcessRecords_V_key_cAllotPersonName );

      m_strbiflag          = pADOConn->GetValueString(DBProcessRecords_V_key_biFlag           );


      bRet = TRUE;
   }
   
   return bRet;
}

CDBProcessRecords_VList::CDBProcessRecords_VList()
{

}
CDBProcessRecords_VList::~CDBProcessRecords_VList()
{

}

CDBProcessRecords_VData* CDBProcessRecords_VList::GetItem(int nIndex)
{
   if (nIndex<0||nIndex>=GetCount())
      return NULL;
   return (CDBProcessRecords_VData*)GetAt(FindIndex(nIndex));
}

void CDBProcessRecords_VList::AddItem(CDBProcessRecords_VData* pItem)
{
   CDBProcessRecords_VData*pData=new CDBProcessRecords_VData;
   pData->Copy(pItem);
   AddTail(pData);
}

void CDBProcessRecords_VList::DeleteItem(int nIndex)
{
   if (nIndex<0||nIndex>GetCount())
      return;
   CDBProcessRecords_VData *pObject=(CDBProcessRecords_VData*)GetItem(nIndex);
   delete pObject;
   pObject=NULL;
   RemoveAt(FindIndex(nIndex));
}

CDBProcessRecords_VList * CDBProcessRecords_VList::Instance()
{
   if(sm_inst.get() == 0)
      sm_inst = shared_ptr<CDBProcessRecords_VList>(new CDBProcessRecords_VList);

   return sm_inst.get();
}
