#pragma  once
/*************************************************
// <�ļ�>: Uncopyable.h
// <˵��>: ��Ϊһ����Ļ��࣬��ʹ�䲻�ɸ��ƣ�������ֹ����
// <����>: duchen
// <����>: 2019/02/22
// Copyright (C), 2016-2020, �������. Co., Ltd.
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