#pragma  once
/*************************************************
// <文件>: QLChatImage.h
// <说明>: 获得CLSID
// <作者>: duchen
// <日期>: 2019/02/22
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
namespace QLChat
{
   int GetEncoderClsid( const WCHAR* format, CLSID* pClsid); //获得CLSID， 给GDI+接口用
}