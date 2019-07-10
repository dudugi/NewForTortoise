#pragma once
#include "CArcItem.h"
struct CArcItemExt:public CArcItem
{
   CArcItemExt():nDiff(0),bByForce(FALSE){}
   CPoint CurrentPoint; //此次坐标点
   int nDiff; //此次水平误差
   BOOL bByForce;
};