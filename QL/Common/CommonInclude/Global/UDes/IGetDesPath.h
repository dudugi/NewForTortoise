#pragma once
/********************************************************************
//  作者:           LINYP
//  CopyRight(c)    2012 Burnon All Rights Reserved 
//  创建时间:       2012/02/20 12:06
//  类描述:         获取目标路径列表 目前只有U盘，后续可能添加网络路径
//  修改时间:       
//  修改目的:       
*********************************************************************/
#include <vector>

class IGetDesPath
{
public:
   typedef std::vector<CString> VEC_STR_DESPATH;   //目标路径
protected:
   VEC_STR_DESPATH m_vecDesPath;                   //目标路径
public:
   IGetDesPath(void);
public:
   virtual ~IGetDesPath(void);
public:
   //-----------------------------------
   // 函数名:  [GetDesPathList]
   // 返回值:  [IGetDesPath::VEC_STR_DESPATH]   
   // 函数描述: 获取路径列表 如插入可移动存储设备路径列表
   // 作者:    LINYP 2012/02/20 12:09
   // 修改时间:
   // 修改目的:
   //-----------------------------------
   virtual VEC_STR_DESPATH GetDesPathList() = 0;
};
