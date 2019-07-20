#pragma once
/********************************************************************
//  作者:           linyp
//  CopyRight(c)    2014 Fujian Raynen Technology Co.,Ltd. All Rights Reserved 
//  创建时间:       2014/12/10 14:00
//  类描述:         常用数学算法
//  修改时间:       
//  修改目的:       
*********************************************************************/
namespace RnMathFun
{
	inline BOOL IsCross(int iLef1, int iRig1, int iLef2, int iRig2)
	{
		BOOL bRes = TRUE;
		if (iLef1 > iRig2 || iRig1 < iLef2)
		{
			bRes =  FALSE;
		}
		return bRes;
	}

   //判断两个线段是否存在重叠的区域 端点重叠也算 
   inline BOOL isLineOverLap(int left,int right,int left1,int right1)
   {
      if((left >= left1 && left <= right1)||
         (right >= left1 && right <= right1)||
         (left1 >= left &&  left1 <= right)||
         (right1 >= left &&  right1 <= right)
         ) 
      {
         return TRUE;
      }
      return FALSE;
   }
   //点是否落在左右区间内
   inline BOOL isPointInRange(int ipoint,int ileft,int iright)
   {
      if (ipoint >= ileft && ipoint <= iright)
      {
         return TRUE;
      }
      return FALSE;
   }
	//bool IsEqual(int iLef1, int iRig1, int iLef2, int iRig2)
	//{
	//	bool bRes = false;
	//	if (iLef1 == iLef2 && iRig1 == iRig2)
	//	{
	//		bRes = true;
	//	}
	//	return bRes;
	//}

}