#pragma once

#include <memory>
#include "ADOConn.h"
#include <windef.h>
using namespace std;

/*************************************************
// <文件>: DBImage.h
// <说明>: 数据库图片获取存储类
// <作者>: wangzl
// <日期>: 2019/02/22
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
class CDBImage
{
public:
	CDBImage();
	~CDBImage();

	static CDBImage* Instance();//获取（指针）实例

	/*
	 * @brief	获取从数据库获取图片保存到指定路径下
	 * @author	zhangt 2017/08/08
	 * @example 
	 CDBImage *pDBImage = CDBImage::Instance();
	 CString strPng = _T("");
	 strPng.Format(_T("F:\\Photo\\%s.png"),m_strcUserID);
	 pDBImage->SaveImagePathFromDB(_T("cUserPhoto"),strPng,pADOConn->GetRecoPtr());
	 */
	BOOL SaveImagePathFromDB(CString strField,CString strPath,_RecordsetPtr ptSet);


	 /*
	 * @brief	将Image保持jpg格式文件
	 * @author	zhangt 2018/02/07
	 * @example 
	 */
	BOOL SaveJPG(Gdiplus::Image *pImg,CString strPath);

	/*
	 * @brief	从数据库中New一个Image指针(note：Image需要手动释放delete)
	 * @author	zhangt 2017/08/10
	 * @example 
	 CDBImage *pDBImage = CDBImage::Instance();
	 Image *pImg = pDBImage->NewImageFromDB(_T("cUserPhoto"),pADOConn->GetRecoPtr());
	 */
	Gdiplus::Image* NewImageFromDB(CString strField,_RecordsetPtr ptSet);

	/*
	 * @brief	HBITMAP转Image指针(note：Image需要手动释放delete)
	 * @author	zhangt 2017/12/04
	 * @example 
	 */
	Gdiplus::Image*	NewImageFromHBitmap(HBITMAP hBitmap);


	/*
	 * @brief	Image转HBITMAP
	 * @author	zhangt 2017/12/04
	 * @example 
	 */
	HBITMAP	Image2HBitmap(Gdiplus::Image* pImg);


	/*
	 * @brief	加载指定路径下图片到数据库中
	 * @author	zhangt 2017/08/08
	 * @example 
	 strSQL.Format(_T("Select %s from %s where %s = '%s'"), DBPerson_key_UserPhoto,DB_TABLE_PERSON,DBPerson_key_UserID,m_strUserID);
	 pADOConn->GetRecordSet(strSQL);	
	 CDBImage *pDBImage = CDBImage::Instance();
	 pDBImage->LoadImagePath2DB(_T("cUserPhoto"),_T("F:\\软件产品分类.png"),pADOConn->GetRecoPtr());
	 */
	BOOL LoadImagePath2DB(CString strField,CString strPath,_RecordsetPtr ptSet,BOOL bJpgFormat=TRUE);

	BOOL LoadImage2DB(CString strField, Gdiplus::Image* pImg,_RecordsetPtr ptSet);

private:
	static std::shared_ptr<CDBImage> sm_inst;

	/***************************
	 * @brief 获取图片文件的编码方式，支持bmp、jpg、jpeg、gif、tiff和png等格式图片
	 * @author	zhangt 2017/08/03
	 * @param [in]  format 图片格式 值可以为以下几种
	 * @"image/bmp"
	 * @"image/jpeg"
	 * @"image/gif"
	 * @"image/tiff"
	 * @"image/png"
	 * @param [in]  pClsid
	 * @return  成功则返回值 >= 0，失败则返回值为-1
	 ***************************/
	int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);

	Gdiplus::Image *m_pImage;
};

