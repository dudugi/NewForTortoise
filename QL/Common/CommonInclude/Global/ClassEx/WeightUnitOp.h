#pragma once
using namespace std;

typedef enum
{
   em_TYPE_WEIGHT_NONE,
   em_TYPE_WEIGHT_KG2JIN,
   em_TYPE_WEIGHT_JIN2KG
}EM_TYPE_WEIGHTCONVERT; //重量转换枚举类型 yangjr 2018/12/19

class CWeightUnitOp
{
public:
   CWeightUnitOp(){}
   ~CWeightUnitOp(){}
   static EM_TYPE_WEIGHTCONVERT GetWeightConvertInfo(__in CString strDBWeightUnit,__in CString strDlgWeightUnit);
   static void ConvertWeight(__in EM_TYPE_WEIGHTCONVERT convertType,double &fValue);
   static CString Func_GetWeightByJingDu(double dFinalWeight,int iNetWeightPointNum);
};
