#include "stdafx.h"
#include "GetUDiskPath.h"

CGetUDiskPath::CGetUDiskPath(void)
{
}

CGetUDiskPath::~CGetUDiskPath(void)
{
}

//-----------------------------------
// ������:  [GetDesPathList]
// ����ֵ:  [IGetDesPath::VEC_STR_DESPATH]   
// ��������: ��ȡ·���б� �������ƶ��洢�豸·���б�
// ����:    LINYP 2012/02/20 12:09
// �޸�ʱ��:
// �޸�Ŀ��:
//-----------------------------------
IGetDesPath::VEC_STR_DESPATH CGetUDiskPath::GetDesPathList()
{
   /* �ܼ�⵽���������� */
#define MAX_DISKNUM 30 
   m_vecDesPath.clear();

   //�������洢��ÿ��������ռ4��TCHAR����
   TCHAR cDiskNameBuf[4*MAX_DISKNUM];

   //��ȡ��ǰ��������д����̷�·��
   DWORD dwDiskNum=GetLogicalDriveStrings(4*MAX_DISKNUM, cDiskNameBuf);

   //�������д��̣��б�ɸѡ����������Ϊ���ƶ����̵�
   for (DWORD i=0; i<dwDiskNum; i+=4)
   {
      //��ǰ�������Ĵ�����
      TCHAR *cCurDiskName=&cDiskNameBuf[i];

      //�б��������
      switch (GetDriveType(cCurDiskName))
      {
      case DRIVE_REMOVABLE:   //���ƶ�ý��
         m_vecDesPath.push_back(cCurDiskName);
         break;
      case DRIVE_UNKNOWN:     //δ֪������    
         break;
      case DRIVE_NO_ROOT_DIR: //·����Ч
         break;
      case DRIVE_FIXED:       //Ӳ��    
         break;
      case DRIVE_REMOTE:      //����������
         break;
      case DRIVE_CDROM:       //CD-ROM   
         break;
      case DRIVE_RAMDISK:     //RAM ������
         break;
      default:
         break;
      }
   }
   return m_vecDesPath;
}