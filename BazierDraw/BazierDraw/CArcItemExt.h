#pragma once
#include "CArcItem.h"
struct CArcItemExt:public CArcItem
{
   CArcItemExt():nDiff(0),bByForce(FALSE){}
   CPoint CurrentPoint; //�˴������
   int nDiff; //�˴�ˮƽ���
   BOOL bByForce;
};