#pragma once
/********************************************************************
//  ����:           LINYP
//  CopyRight(c)    2012 Burnon All Rights Reserved 
//  ����ʱ��:       2012/02/20 12:08
//  ������:         ��ȡ��ǰ����Ŀ��ƶ�ý��·��
//  �޸�ʱ��:       
//  �޸�Ŀ��:       
*********************************************************************/
#include "IGetDesPath.h"

class CGetUDiskPath :
   public IGetDesPath
{
public:
   CGetUDiskPath(void);
public:
   virtual ~CGetUDiskPath(void);
public:
   //-----------------------------------
   // ������:  [GetDesPathList]
   // ����ֵ:  [IGetDesPath::VEC_STR_DESPATH]   
   // ��������: ��ȡ·���б� �������ƶ��洢�豸·���б�
   // ����:    LINYP 2012/02/20 12:09
   // �޸�ʱ��:
   // �޸�Ŀ��:
   //-----------------------------------
   virtual VEC_STR_DESPATH GetDesPathList();
};
