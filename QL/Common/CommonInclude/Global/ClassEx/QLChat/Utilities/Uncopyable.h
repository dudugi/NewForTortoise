#pragma  once
/*************************************************
// <文件>: Uncopyable.h
// <说明>: 作为一个类的基类，可使其不可复制，用来防止复制
// <作者>: duchen
// <日期>: 2019/02/22
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#include "stdafx.h"
class CUncopyable
{
protected:
   CUncopyable() {}
   ~CUncopyable() {}
private:  // emphasize the following members are private  
   CUncopyable(const CUncopyable&);
   const CUncopyable& operator=( const CUncopyable& );
};