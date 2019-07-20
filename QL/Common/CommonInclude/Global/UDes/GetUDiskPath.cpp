#include "stdafx.h"
#include "GetUDiskPath.h"

CGetUDiskPath::CGetUDiskPath(void)
{
}

CGetUDiskPath::~CGetUDiskPath(void)
{
}

//-----------------------------------
// 函数名:  [GetDesPathList]
// 返回值:  [IGetDesPath::VEC_STR_DESPATH]   
// 函数描述: 获取路径列表 如插入可移动存储设备路径列表
// 作者:    LINYP 2012/02/20 12:09
// 修改时间:
// 修改目的:
//-----------------------------------
IGetDesPath::VEC_STR_DESPATH CGetUDiskPath::GetDesPathList()
{
   /* 能检测到的最大磁盘数 */
#define MAX_DISKNUM 30 
   m_vecDesPath.clear();

   //磁盘名存储，每个磁盘名占4个TCHAR长度
   TCHAR cDiskNameBuf[4*MAX_DISKNUM];

   //获取当前接入的所有磁盘盘符路径
   DWORD dwDiskNum=GetLogicalDriveStrings(4*MAX_DISKNUM, cDiskNameBuf);

   //遍历所有磁盘，判别并筛选出磁盘类型为可移动磁盘的
   for (DWORD i=0; i<dwDiskNum; i+=4)
   {
      //当前遍历到的磁盘名
      TCHAR *cCurDiskName=&cDiskNameBuf[i];

      //判别磁盘类型
      switch (GetDriveType(cCurDiskName))
      {
      case DRIVE_REMOVABLE:   //可移动媒体
         m_vecDesPath.push_back(cCurDiskName);
         break;
      case DRIVE_UNKNOWN:     //未知驱动器    
         break;
      case DRIVE_NO_ROOT_DIR: //路径无效
         break;
      case DRIVE_FIXED:       //硬盘    
         break;
      case DRIVE_REMOTE:      //网络驱动器
         break;
      case DRIVE_CDROM:       //CD-ROM   
         break;
      case DRIVE_RAMDISK:     //RAM 驱动器
         break;
      default:
         break;
      }
   }
   return m_vecDesPath;
}