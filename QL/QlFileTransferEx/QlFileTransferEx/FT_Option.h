/*************************************************
// <文件>: FT_Option.h
// <说明>: 传输库结构体信息中相关信息的处理
// <作者>: wangzl
// <日期>: 2019/02/28
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#pragma once
#include "FileTransferDef.inl"


FileTransCode vsetopt(struct FileTrans_easy *pData, FileTransOption option,
                        va_list param);


