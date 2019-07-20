#pragma once
/********************************************************************
//  ����:           linyp
//  CopyRight(c)    2014 Fujian Raynen Technology Co.,Ltd. All Rights Reserved 
//  ����ʱ��:       2014/12/10 14:00
//  ������:         ������ѧ�㷨
//  �޸�ʱ��:       
//  �޸�Ŀ��:       
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

   //�ж������߶��Ƿ�����ص������� �˵��ص�Ҳ�� 
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
   //���Ƿ���������������
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