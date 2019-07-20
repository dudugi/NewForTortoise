#pragma once

#include <memory>
#include "ADOConn.h"
#include <windef.h>
using namespace std;

/*************************************************
// <�ļ�>: DBImage.h
// <˵��>: ���ݿ�ͼƬ��ȡ�洢��
// <����>: wangzl
// <����>: 2019/02/22
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
class CDBImage
{
public:
	CDBImage();
	~CDBImage();

	static CDBImage* Instance();//��ȡ��ָ�룩ʵ��

	/*
	 * @brief	��ȡ�����ݿ��ȡͼƬ���浽ָ��·����
	 * @author	zhangt 2017/08/08
	 * @example 
	 CDBImage *pDBImage = CDBImage::Instance();
	 CString strPng = _T("");
	 strPng.Format(_T("F:\\Photo\\%s.png"),m_strcUserID);
	 pDBImage->SaveImagePathFromDB(_T("cUserPhoto"),strPng,pADOConn->GetRecoPtr());
	 */
	BOOL SaveImagePathFromDB(CString strField,CString strPath,_RecordsetPtr ptSet);


	 /*
	 * @brief	��Image����jpg��ʽ�ļ�
	 * @author	zhangt 2018/02/07
	 * @example 
	 */
	BOOL SaveJPG(Gdiplus::Image *pImg,CString strPath);

	/*
	 * @brief	�����ݿ���Newһ��Imageָ��(note��Image��Ҫ�ֶ��ͷ�delete)
	 * @author	zhangt 2017/08/10
	 * @example 
	 CDBImage *pDBImage = CDBImage::Instance();
	 Image *pImg = pDBImage->NewImageFromDB(_T("cUserPhoto"),pADOConn->GetRecoPtr());
	 */
	Gdiplus::Image* NewImageFromDB(CString strField,_RecordsetPtr ptSet);

	/*
	 * @brief	HBITMAPתImageָ��(note��Image��Ҫ�ֶ��ͷ�delete)
	 * @author	zhangt 2017/12/04
	 * @example 
	 */
	Gdiplus::Image*	NewImageFromHBitmap(HBITMAP hBitmap);


	/*
	 * @brief	ImageתHBITMAP
	 * @author	zhangt 2017/12/04
	 * @example 
	 */
	HBITMAP	Image2HBitmap(Gdiplus::Image* pImg);


	/*
	 * @brief	����ָ��·����ͼƬ�����ݿ���
	 * @author	zhangt 2017/08/08
	 * @example 
	 strSQL.Format(_T("Select %s from %s where %s = '%s'"), DBPerson_key_UserPhoto,DB_TABLE_PERSON,DBPerson_key_UserID,m_strUserID);
	 pADOConn->GetRecordSet(strSQL);	
	 CDBImage *pDBImage = CDBImage::Instance();
	 pDBImage->LoadImagePath2DB(_T("cUserPhoto"),_T("F:\\�����Ʒ����.png"),pADOConn->GetRecoPtr());
	 */
	BOOL LoadImagePath2DB(CString strField,CString strPath,_RecordsetPtr ptSet,BOOL bJpgFormat=TRUE);

	BOOL LoadImage2DB(CString strField, Gdiplus::Image* pImg,_RecordsetPtr ptSet);

private:
	static std::shared_ptr<CDBImage> sm_inst;

	/***************************
	 * @brief ��ȡͼƬ�ļ��ı��뷽ʽ��֧��bmp��jpg��jpeg��gif��tiff��png�ȸ�ʽͼƬ
	 * @author	zhangt 2017/08/03
	 * @param [in]  format ͼƬ��ʽ ֵ����Ϊ���¼���
	 * @"image/bmp"
	 * @"image/jpeg"
	 * @"image/gif"
	 * @"image/tiff"
	 * @"image/png"
	 * @param [in]  pClsid
	 * @return  �ɹ��򷵻�ֵ >= 0��ʧ���򷵻�ֵΪ-1
	 ***************************/
	int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);

	Gdiplus::Image *m_pImage;
};

