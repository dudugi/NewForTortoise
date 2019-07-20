#include "StdAfx.h"
#include "WeightUnitOp.h"
#include "CGlobalDefine.h"
#include "CFormatDefine.h"

CString CWeightUnitOp::Func_GetWeightByJingDu(double dFinalWeight,int iNetWeightPointNum)
{
   CString strTemp;
   if (iNetWeightPointNum<1|| iNetWeightPointNum>4)
   {
      iNetWeightPointNum = 4;
   }  

   if (iNetWeightPointNum!=4)
   {
      double fAddValue = 0.5;
      for (int i=0;i<iNetWeightPointNum;++i)
      {
         fAddValue /= 10;
      } 
      dFinalWeight += fAddValue;
      CString strFormat;
      strFormat.Format(FORMAT_INT,iNetWeightPointNum);

      strTemp.Format(_T("%.")+strFormat+_T("f"),dFinalWeight);
      strTemp.Format(FORMAT_WEIGHT,_ttof(strTemp));
   }else
   {
      strTemp.Format(FORMAT_WEIGHT,dFinalWeight);
   }   
   return strTemp;
};

EM_TYPE_WEIGHTCONVERT CWeightUnitOp::GetWeightConvertInfo( __in CString strDBWeightUnit,__in CString strDlgWeightUnit)
{
   if (strDBWeightUnit == strDlgWeightUnit)
   {
      return em_TYPE_WEIGHT_NONE;
   }
   if (strDBWeightUnit == WEIGHTUNIT_GLOBAL_JIN && strDlgWeightUnit == WEIGHTUNIT_GLOBAL_KG)
   {
      return em_TYPE_WEIGHT_JIN2KG;
   }
   if (strDBWeightUnit ==WEIGHTUNIT_GLOBAL_KG && strDlgWeightUnit == WEIGHTUNIT_GLOBAL_JIN)
   {
      return em_TYPE_WEIGHT_KG2JIN;
   }
   return em_TYPE_WEIGHT_NONE;
}

void CWeightUnitOp::ConvertWeight( __in EM_TYPE_WEIGHTCONVERT convertType,double &fValue)
{
   if (em_TYPE_WEIGHT_JIN2KG == convertType)
   {
      fValue /=2; 
   }else if (em_TYPE_WEIGHT_KG2JIN == convertType)
   {
      fValue *=2; 
   }
}
