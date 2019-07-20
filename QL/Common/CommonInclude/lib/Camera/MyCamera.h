// MyCamera.h

#pragma once

#ifdef MYCAMERA_EXPORTS
#define MYCAMERA_API __declspec(dllexport)
#else
#define MYCAMERA_API __declspec(dllimport)
#endif
//using namespace System;

class CxImage;

namespace MyCamera {

// 	public ref class Class1
// 	{
// 		// TODO: Add your methods for this class here.
// 	};
}
class CDlgCamera;
class MYCAMERA_API MyCameraInterface
{
public:
	MyCameraInterface(void);
public:
	~MyCameraInterface(void);
private:
	CString          m_DefaultFilePath;
	CDlgCamera*      m_pdlgCamera;
	BOOL             m_bClearPhoto;//清除图片
	BOOL             m_bAvalibleClearPhoto;
public:
	BOOL StartCamera();
	//预设置文件路径及名称（*.bmp），相片将存储在此路径下，请保证路径及文件名合法,如filepath = D:\1.bmp
	BOOL StartCamera(CString filepath);
	void SetDefaultFilePath(CString filepath);
	//获得文件储存路径，若预设置文件路径及名称，返回空串，若未运行StartCamera，返回预设值
	CString GetFilePath();     //获取文件保存路径
	CxImage GetPhoto();        //获取照片
	void AvalibleClearPhoto(BOOL avalile = TRUE);
	BOOL IsClearPhoto();
};