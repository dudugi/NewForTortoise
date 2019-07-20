#include "StdAfx.h"
#include "DBImage.h"
#include <GdiplusImaging.h>

using namespace Gdiplus;

std::shared_ptr<CDBImage> CDBImage::sm_inst;

CDBImage::CDBImage()
{
	m_pImage = NULL;
}


CDBImage::~CDBImage()
{
	if (NULL != m_pImage)
	{
		delete m_pImage;
		m_pImage = NULL;
	}
}

CDBImage* CDBImage::Instance()
{
	if(sm_inst.get() == 0)
	{
		sm_inst = shared_ptr<CDBImage>(new CDBImage);
	}

	return sm_inst.get();
}

int CDBImage::GetEncoderClsid(const WCHAR* format, CLSID* pClsid)  
{  
	UINT  num = 0;          // number of image encoders  
	UINT  size = 0;         // size of the image encoder array in bytes  

	ImageCodecInfo* pImageCodecInfo = NULL;  

	//获取GDI+支持的图像格式编码器种类数以及ImageCodecInfo数组的存放大小  
	GetImageEncodersSize(&num, &size);  
	if(size == 0)  
		return -1;  // Failure  

	//为ImageCodecInfo数组分配足额空间  
	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));  
	if(pImageCodecInfo == NULL)  
		return -1;  // Failure  

	//获取所有的图像编码器信息  
	GetImageEncoders(num, size, pImageCodecInfo);  

	//查找符合的图像编码器的Clsid  
	for(UINT j = 0; j < num; ++j)  
	{  
		if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )  
		{  
			*pClsid = pImageCodecInfo[j].Clsid;  
			free(pImageCodecInfo);  
			return j;  // Success  
		}      
	}  

	//释放内存  
	free(pImageCodecInfo);  
	return -1;  // Failure  
}

Image* CDBImage:: NewImageFromDB(CString strField,_RecordsetPtr ptSet)
{
	strField.Trim();
	ASSERT(!strField.IsEmpty());

	ASSERT(ptSet != NULL);
	Image* pImage = NULL; 

	LPVOID Data = NULL;
	char* pBuf = NULL;
	long lDataSize = ptSet->GetFields()->GetItem((LPCTSTR)strField)->ActualSize; //数据库中图像数据长度
	if (lDataSize > 0)
	{
		_variant_t varBLOB;
		varBLOB = ptSet->GetFields()->GetItem((LPCTSTR)strField)->GetChunk(lDataSize);
		Data = new char[lDataSize+1];
		if (varBLOB.vt == (VT_ARRAY|VT_UI1))//判断数据类型是否正确
		{
			SafeArrayAccessData(varBLOB.parray, (void **)&pBuf);
			memcpy(Data, pBuf, lDataSize);//拷贝数据中数据到Data
			SafeArrayUnaccessData(varBLOB.parray);
		}
	}

	//Data转IStream
	IStream* pStm;
	LONGLONG cb = lDataSize;
	HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, cb);
	LPVOID pvData;
	if (hGlobal != NULL && Data != NULL)
	{
		pvData = GlobalLock(hGlobal);
		memcpy(pvData, Data, cb);
		GlobalUnlock(hGlobal);
		CreateStreamOnHGlobal(hGlobal, TRUE, &pStm);
		if (NULL != Data)
		{
			delete Data;
			Data = NULL;
		}

		pImage = Image::FromStream(pStm);    
		ASSERT( pImage != NULL );
		pStm->Release();		
	}
	else
	{
		//TRACE(_T("Get Image Error\n"));
	}

	return pImage;
}

BOOL CDBImage::SaveJPG(Image *pImg,CString strPath)
{
	strPath.Trim();
	ASSERT(!strPath.IsEmpty());
	ASSERT(pImg != NULL);

	CLSID encoderClsid;
	GetEncoderClsid(L"image/jpeg",&encoderClsid);//确定编码格式是格式：jpeg
#ifdef _UNICODE
   BOOL bRet = pImg->Save(strPath,&encoderClsid,NULL);
#else
   USES_CONVERSION;
   BOOL bRet = pImg->Save(A2W(strPath),&encoderClsid,NULL);
#endif
	//BOOL bRet = pImg->Save(strPath,&encoderClsid,NULL);

	return bRet;
}


BOOL CDBImage::SaveImagePathFromDB(CString strField,CString strPath,_RecordsetPtr ptSet)
{
	strField.Trim();
	ASSERT(!strField.IsEmpty());

	ASSERT(ptSet != NULL);

	BOOL bRet = FALSE;

	LPVOID Data = NULL;
	char* pBuf = NULL;
	long lDataSize = ptSet->GetFields()->GetItem((LPCTSTR)strField)->ActualSize; //数据库中图像数据长度
	if (lDataSize > 0)
	{
		_variant_t varBLOB;
		varBLOB = ptSet->GetFields()->GetItem((LPCTSTR)strField)->GetChunk(lDataSize);
		Data = new char[lDataSize+1];
		if (varBLOB.vt == (VT_ARRAY|VT_UI1))//判断数据类型是否正确
		{
			SafeArrayAccessData(varBLOB.parray, (void **)&pBuf);
			memcpy(Data, pBuf, lDataSize);//拷贝数据中数据到Data
			SafeArrayUnaccessData(varBLOB.parray);
		}
	}

	//Data转IStream
	IStream* pStm;
	LONGLONG cb = lDataSize;
	HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, cb);
	LPVOID pvData;
	if (hGlobal != NULL)
	{
		pvData = GlobalLock(hGlobal);
		memcpy(pvData, Data, cb);
		GlobalUnlock(hGlobal);
		CreateStreamOnHGlobal(hGlobal, TRUE, &pStm);
		if (NULL != Data)
		{
			delete Data;
			Data = NULL;
		}	
	}
	else
	{
		//TRACE(_T("Get Image Error\n"));
		return bRet;
	}


	CLSID encoderClsid;
	GetEncoderClsid(L"image/jpeg",&encoderClsid);//确定编码格式是格式：jpeg
	Image image(pStm, TRUE);//Image加载IStream

#ifdef _UNICODE
	if(Gdiplus::Ok == image.Save(strPath, &encoderClsid, NULL))//把image中的数据按照png编码格式存到本地
#else
	USES_CONVERSION;
	if(Gdiplus::Ok == image.Save(A2W(strPath), &encoderClsid, NULL))
#endif
	{
		bRet = TRUE;
	}
	pStm->Release();

	return bRet;
}


BOOL CDBImage::LoadImage2DB(CString strField,Image* pImg,_RecordsetPtr ptSet)
{
	strField.Trim();
	ASSERT(!strField.IsEmpty());

	ASSERT(ptSet != NULL);
	ASSERT(pImg != NULL);

	BOOL bRet = FALSE;

	HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, 0);
	IStream *pStm = NULL;
	CreateStreamOnHGlobal(hMem, TRUE, &pStm);
	CLSID encoderClsid;
	GetEncoderClsid(L"image/jpeg",&encoderClsid);//确定编码格式是格式：jpeg
	pImg->Save(pStm,&encoderClsid,NULL);
	if (pStm != NULL)
	{
		LARGE_INTEGER liBeggining = { 0 };
		pStm->Seek(liBeggining, STREAM_SEEK_SET, NULL);
		DWORD nLen = GlobalSize(hMem);
		LPBYTE lpData = (LPBYTE)GlobalLock(hMem);

		if (lpData)
		{
			VARIANT varChunk;
			SAFEARRAY *psa;
			SAFEARRAYBOUND rgsabound[1];

			rgsabound[0].lLbound = 0;
			rgsabound[0].cElements = nLen;

			psa = SafeArrayCreate(VT_UI1, 1, rgsabound); //创建SAFEARRAY对象
			for (long i = 0; i < static_cast<long>(nLen); i++)
				SafeArrayPutElement (psa, &i, lpData++);

			varChunk.vt = VT_ARRAY | VT_UI1; //将varChunk的类型设置为BYTE类型的数组
			varChunk.parray = psa; //为varChunk变量赋值
			try
			{
				ptSet->Fields->GetItem((LPCTSTR)strField)->AppendChunk(varChunk);
				bRet = TRUE;
			}
			catch (_com_error e)
			{
				//保存图片到数据库出错;
				bRet = FALSE;
			}
			::VariantClear(&varChunk);
			::SafeArrayDestroyData(psa);

			HRESULT hr=0;
#ifdef ADO_ENUM_ERR
         adoLockTypeEnum emLockType = ptSet->LockType;
#else
         LockTypeEnum emLockType = ptSet->LockType;
#endif
			if (emLockType == adLockBatchOptimistic)
			{
				hr = ptSet->UpdateBatch(adAffectAll);
			}
			else
			{
				hr = ptSet->Update();
			}

			if (SUCCEEDED(hr))
			{
				TRACE(_T("Save DBImage Success\n"));
			}
			else
			{
				TRACE(_T("Save DBImage Error\n"));
			}
		}

		GlobalUnlock(hMem);
	}

	GlobalFree(hMem);
	pStm->Release();

	return bRet;
}

Image*	CDBImage::NewImageFromHBitmap(HBITMAP hBitmap)
{
	ASSERT(hBitmap != NULL);

	Image* pImg = new Bitmap(hBitmap,NULL); //子类强转父类：Bitmap->Image

	return pImg;
}

HBITMAP CDBImage::Image2HBitmap(Image* pImg)
{
	ASSERT(pImg != NULL);

	HBITMAP hBitmap = NULL;

	HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, 0);
	IStream *pStm = NULL;
	CreateStreamOnHGlobal(hMem, TRUE, &pStm);
	CLSID encoderClsid;
	GetEncoderClsid(L"image/jpeg",&encoderClsid);//确定编码格式是格式：jpeg
	pImg->Save(pStm,&encoderClsid,NULL);
	if (pStm != NULL)
	{
		Bitmap bmp(pStm);
		bmp.GetHBITMAP(NULL,&hBitmap);
	}

	GlobalFree(hMem);
	pStm->Release();

	return hBitmap;
}


BOOL CDBImage::LoadImagePath2DB(CString strField,CString strPath,_RecordsetPtr ptSet,BOOL bJpgFormat/*=TRUE*/)
{
	strField.Trim();
	ASSERT(!strField.IsEmpty());

	ASSERT(ptSet != NULL);

	strPath.Trim();
	ASSERT(!strPath.IsEmpty());

	BOOL bRet = FALSE;

	if (bJpgFormat)
	{
#ifdef _UNICODE
      Image ImagePath(strPath);
#else
      CStringW strwPath = CT2W(strPath);
      Image ImagePath(strwPath);
#endif 
		bRet = LoadImage2DB(strField,&ImagePath,ptSet);
	}
	else
	{
		VARIANT varChunk;
		SAFEARRAY* psa;
		SAFEARRAYBOUND rgsabound[1];
		CFile f(strPath.operator LPCTSTR(),CFile::modeRead);
		int ChunkSize=128;
		BYTE bval[128/*ChunkSize*/+1];
		long uIsRead=0;
		while (1)
		{
			uIsRead=f.Read(bval,ChunkSize);
			if (uIsRead==0) break;
			rgsabound[0].cElements=uIsRead;
			rgsabound[0].lLbound=0;
			psa=SafeArrayCreate(VT_UI1,1,rgsabound);
			for (long index=0;index<uIsRead;index++)
			{
				if (FAILED(SafeArrayPutElement(psa,&index,&bval[index])))
					AfxMessageBox(_T("图片转内存出错"));

			}
			varChunk.vt =VT_ARRAY|VT_UI1;
			varChunk.parray=psa;
			try
			{
				ptSet->Fields->GetItem((LPCTSTR)strField)->AppendChunk(varChunk);
				bRet = TRUE;
			}
			catch (_com_error e)
			{
				//AfxMessageBox(_T("保存图片到数据库出错"));
				bRet = FALSE;
			}
			::VariantClear(&varChunk);
			::SafeArrayDestroyData(psa);
			if (uIsRead<ChunkSize)break;
		}
		f.Close();

		//adLockBatchOptimistic 当数据源正在更新时，其他用户必须将CursorLocation改为adUdeClientBatch才能对数据进行增、删、改的操作。
		//CursorLocationEnum emCursorLocation = ptSet->CursorLocation;
		//ptSet->CursorLocation = adUseClientBatch;
		//ptSet->CursorType = adOpenStatic;
		HRESULT hr=0;
#ifdef ADO_ENUM_ERR
      adoLockTypeEnum emLockType = ptSet->LockType;
#else
      LockTypeEnum emLockType = ptSet->LockType;
#endif
		if (emLockType == adLockBatchOptimistic)
		{
			hr = ptSet->UpdateBatch(adAffectAll);
		}
		else
		{
			hr = ptSet->Update();
		}

		if (SUCCEEDED(hr))
		{
			TRACE(_T("Save DBImage Success\n"));
		}
		else
		{
			TRACE(_T("Save DBImage Error\n"));
		}
	}

	return bRet;
}