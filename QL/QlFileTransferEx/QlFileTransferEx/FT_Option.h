/*************************************************
// <�ļ�>: FT_Option.h
// <˵��>: �����ṹ����Ϣ�������Ϣ�Ĵ���
// <����>: wangzl
// <����>: 2019/02/28
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#pragma once
#include "FileTransferDef.inl"


FileTransCode vsetopt(struct FileTrans_easy *pData, FileTransOption option,
                        va_list param);


