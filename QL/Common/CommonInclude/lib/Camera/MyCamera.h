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
	BOOL             m_bClearPhoto;//���ͼƬ
	BOOL             m_bAvalibleClearPhoto;
public:
	BOOL StartCamera();
	//Ԥ�����ļ�·�������ƣ�*.bmp������Ƭ���洢�ڴ�·���£��뱣֤·�����ļ����Ϸ�,��filepath = D:\1.bmp
	BOOL StartCamera(CString filepath);
	void SetDefaultFilePath(CString filepath);
	//����ļ�����·������Ԥ�����ļ�·�������ƣ����ؿմ�����δ����StartCamera������Ԥ��ֵ
	CString GetFilePath();     //��ȡ�ļ�����·��
	CxImage GetPhoto();        //��ȡ��Ƭ
	void AvalibleClearPhoto(BOOL avalile = TRUE);
	BOOL IsClearPhoto();
};