#pragma once
/********************************************************************
//  ����:           LINYP
//  CopyRight(c)    2012 Burnon All Rights Reserved 
//  ����ʱ��:       2012/02/20 12:06
//  ������:         ��ȡĿ��·���б� Ŀǰֻ��U�̣����������������·��
//  �޸�ʱ��:       
//  �޸�Ŀ��:       
*********************************************************************/
#include <vector>

class IGetDesPath
{
public:
   typedef std::vector<CString> VEC_STR_DESPATH;   //Ŀ��·��
protected:
   VEC_STR_DESPATH m_vecDesPath;                   //Ŀ��·��
public:
   IGetDesPath(void);
public:
   virtual ~IGetDesPath(void);
public:
   //-----------------------------------
   // ������:  [GetDesPathList]
   // ����ֵ:  [IGetDesPath::VEC_STR_DESPATH]   
   // ��������: ��ȡ·���б� �������ƶ��洢�豸·���б�
   // ����:    LINYP 2012/02/20 12:09
   // �޸�ʱ��:
   // �޸�Ŀ��:
   //-----------------------------------
   virtual VEC_STR_DESPATH GetDesPathList() = 0;
};
