#pragma once
/********************************************************************
//  作者:           LINYP
//  CopyRight(c)    2012 Burnon All Rights Reserved 
//  创建时间:       2012/02/20 12:08
//  类描述:         获取当前插入的可移动媒体路径
//  修改时间:       
//  修改目的:       
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
   // 函数名:  [GetDesPathList]
   // 返回值:  [IGetDesPath::VEC_STR_DESPATH]   
   // 函数描述: 获取路径列表 如插入可移动存储设备路径列表
   // 作者:    LINYP 2012/02/20 12:09
   // 修改时间:
   // 修改目的:
   //-----------------------------------
   virtual VEC_STR_DESPATH GetDesPathList();
};
