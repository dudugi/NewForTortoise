#include "StdAfx.h"
#include "CRecordList.h"
#include "MySerial.h"
//#include "dibapi.h"

IMPLEMENT_SERIAL(CRecord,CObject,1)

CRecord::CRecord()
:m_bActive(false), 
m_pData(NULL), 
m_dwDataLength(0),
m_Color(RGB(0, 0, 0)),
m_nId(-1),
m_Size(0, 0)
{

}

CRecord::~CRecord()
{
	if(m_pData)
	{
		delete [] m_pData; 
		m_pData = 0;
	}
}

void CRecord::Serialize(CArchive& ar)
{
	CString tagname;

	int dateSize=0;
	int tagsize=0;
	CString strname;
	int namesize;
	ar.Flush();
	if (ar.IsStoring())
	{
		MySerial.SaveDataInt(ar,_T("ID000000"),m_nId);

		MySerial.SaveDataStr(ar,_T("NAME0000"),m_sName);

		MySerial.SaveDataInt(ar,_T("POINTX00"),m_Point.x);

		MySerial.SaveDataInt(ar,_T("POINTY00"),m_Point.y);

		MySerial.SaveDataInt(ar,_T("SIZECX00"),m_Size.cx);

		MySerial.SaveDataInt(ar,_T("SIZECY00"),m_Size.cy);

		int nActive=m_bActive;
		MySerial.SaveDataInt(ar,_T("BACTIVE0"),nActive);

		// 		KDSApi.SaveDouble(ar,_T("LENGTH00"),m_dataLength);
		namesize=8;
		strname=_T("WMVDATA0");
		ar << namesize;
		ar << strname;
		tagsize=m_dwDataLength;
		ar << tagsize;
		ar.Flush();
		CFile *pFile = ar.GetFile();
		pFile->Write(m_pData, m_dwDataLength * sizeof(BYTE));

		pFile->Flush();
		ar.Flush();

		MySerial.SaveDataInt(ar, _T("COLOR000"), m_Color);

		MySerial.SaveDataStr(ar,_T("INFO0000"),m_sInfo);

		namesize=8;
		strname="DENDDEND";
		ar << namesize;
		ar << strname;
	}
	else
	{

		int nNumber=0;
		ar >> namesize;
		ar >> strname;
		if(strname.GetLength()!=namesize)return;

		while(strname != "DENDDEND")
		{
			if(nNumber > 150)
			{
				return;
			}		
			if(strname == "ID000000")
			{
				ar >> tagsize >> m_nId;
			}
			else if(strname== "NAME0000")
			{
				ar >> tagsize >> m_sName;
			}
			else if(strname== "POINTX00")
			{
				ar >> tagsize >> m_Point.x;
			}
			else if(strname== "POINTY00")
			{
				ar >> tagsize >> m_Point.y;
			}
			else if(strname== "SIZECX00")
			{
				ar >> tagsize >> m_Size.cx;
			}
			else if(strname== "SIZECY00")
			{
				ar >> tagsize >> m_Size.cy;
			}

			else if(strname== "BACTIVE0")
			{
				int nactive = 0;
				ar >> tagsize >> nactive;
				m_bActive = (nactive != 0)?true:false;
			}
			else if(strname== "WMVDATA0")
			{
				ar >> tagsize;
				m_dwDataLength=tagsize;
				ar.Flush();
				CFile *pFile = ar.GetFile();
				if (m_pData != NULL)
				{
					delete [] m_pData;
					m_pData = NULL;
				}
				if(m_dwDataLength > 0)
				{
					m_pData = new BYTE[m_dwDataLength];
					pFile->Read(m_pData, m_dwDataLength * sizeof(BYTE));
				}
			}
			else if(strname== "COLOR000")
			{
				ar >> tagsize >> m_Color;
			}
			else if(strname== "INFO0000")
			{
				ar >> tagsize >> m_sInfo;
			}
			else
			{
				ar >> tagsize;
				ar.Flush();
				char *buf = new char[tagsize];
				ar.GetFile()->Read(buf,tagsize);
				delete[] buf;
			}
			strname = "";
			ar >> namesize;
			ar >> strname;
			if(strname.GetLength()!=namesize)return;
			nNumber++;
		}
	}
}

void CRecord::Copy(CRecord *pRecord)
{
	if(this == pRecord)
		return;
	m_nId = pRecord->m_nId;
	m_sName = pRecord->m_sName;
	m_Point = pRecord->m_Point;
	m_Size = pRecord->m_Size;
	m_bActive = pRecord->m_bActive;
	m_dwDataLength = pRecord->m_dwDataLength;
	if(m_pData)
	{
		delete [] m_pData;
		m_pData = NULL;
	}
	if(pRecord->m_dwDataLength > 0)
	{
		m_pData = new BYTE[pRecord->m_dwDataLength];
		memcpy(m_pData, pRecord->m_pData, pRecord->m_dwDataLength * sizeof(BYTE));
	}
	m_Color = pRecord->m_Color;
	m_sInfo = pRecord->m_sInfo;
}

CRecordList::CRecordList()
	:m_DrawSize(24, 24), m_pWnd(NULL), 
	m_pLastRecord(NULL),
	m_nOffsetX(0), m_nOffsetY(0),
	m_pLastJumpRecord(NULL)
{

}

void CRecordList::ResetPoint(CPoint offPt,double lfScaling)
{
	for (int i=0;i<GetCount();i++)
	{
		CRecord *pRecord = (CRecord *)GetAt(FindIndex(i));
		pRecord->m_Point=CPoint(int((pRecord->m_Point.x/*+offPt.x*/)*lfScaling),int((pRecord->m_Point.y/*+offPt.y*/)*lfScaling));
 		pRecord->m_Point.Offset(offPt);
	}
}

/************************************************************************* 
 * 
 * DrawTransparentBitmap () 
 * 
 * Parameters: 
 * 
 * HDC hDC          - DC to do output to 
 * 
 * CDC* pMemDC       - DC of bitmap to draw transparently
 * 
 * LONG xStart, yStart   - start position to draw *
 *
 * COLORREF cTransparentColor - transparent color * 
 * Return Value: 
 * 
 * Description: none
 *		 Draw bitmap transparently
 * 
 ************************************************************************/ 
static void DrawTransparentBitmap1(HDC hdc, CDC* pMemDC, 
						   int xStart, int yStart, int Width,int Height,
						   int xSrc, int ySrc, COLORREF cTransparentColor)
{

   COLORREF   cColor;
   HBITMAP    bmAndBack, bmAndObject, bmAndMem, bmSave;
   HBITMAP    bmBackOld, bmObjectOld, bmMemOld, bmSaveOld;
   HDC        hdcMem, hdcBack, hdcObject, hdcTemp, hdcSave;
   POINT      ptSize;

   hdcTemp=(HDC)pMemDC->GetSafeHdc();
   ptSize.x = Width;            // Get width of bitmap
   ptSize.y = Height;           // Get height of bitmap
   DPtoLP(hdcTemp, &ptSize, 1);      // Convert from device
                                     // to logical points

   // Create some DCs to hold temporary data.
   hdcBack   = CreateCompatibleDC(hdc);
   hdcObject = CreateCompatibleDC(hdc);
   hdcMem    = CreateCompatibleDC(hdc);
   hdcSave   = CreateCompatibleDC(hdc);

   // Create a bitmap for each DC. DCs are required for a number of
   // GDI functions.

   // Monochrome DC
   bmAndBack   = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);

   // Monochrome DC
   bmAndObject = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);

   bmAndMem    = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);
   bmSave      = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);

   // Each DC must select a bitmap object to store pixel data.
   bmBackOld   = (HBITMAP)SelectObject(hdcBack, bmAndBack);
   bmObjectOld = (HBITMAP)SelectObject(hdcObject, bmAndObject);
   bmMemOld    = (HBITMAP)SelectObject(hdcMem, bmAndMem);
   bmSaveOld   = (HBITMAP)SelectObject(hdcSave, bmSave);

   // Set proper mapping mode.
   SetMapMode(hdcTemp, GetMapMode(hdc));

   // Save the bitmap sent here, because it will be overwritten.
   BitBlt(hdcSave, 0, 0, ptSize.x, ptSize.y, hdcTemp, xSrc, ySrc, SRCCOPY);

   // Set the background color of the source DC to the color.
   // contained in the parts of the bitmap that should be transparent
   cColor = SetBkColor(hdcTemp, cTransparentColor);

   // Create the object mask for the bitmap by performing a BitBlt
   // from the source bitmap to a monochrome bitmap.
   BitBlt(hdcObject, 0, 0, ptSize.x, ptSize.y, hdcTemp, xSrc, ySrc,
          SRCCOPY);

   // Set the background color of the source DC back to the original
   // color.
   SetBkColor(hdcTemp, cColor);

   // Create the inverse of the object mask.
   BitBlt(hdcBack, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0,
          NOTSRCCOPY);

   // Copy the background of the main DC to the destination.
   BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdc, xStart, yStart,
          SRCCOPY);

   // Mask out the places where the bitmap will be placed.
   BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0, SRCAND);

   // Mask out the transparent colored pixels on the bitmap.
   BitBlt(hdcTemp, 0, 0, ptSize.x, ptSize.y, hdcBack, 0, 0, SRCAND);

   // XOR the bitmap with the background on the destination DC.
   BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdcTemp, xSrc, ySrc, SRCPAINT);

   // Copy the destination to the screen.
   BitBlt(hdc, xStart, yStart, ptSize.x, ptSize.y, hdcMem, 0, 0,
          SRCCOPY);

   // Place the original bitmap back into the bitmap sent here.
   BitBlt(hdcTemp, 0, 0, ptSize.x, ptSize.y, hdcSave, 0, 0, SRCCOPY);

   // Delete the memory bitmaps.
   DeleteObject(SelectObject(hdcBack, bmBackOld));
   DeleteObject(SelectObject(hdcObject, bmObjectOld));
   DeleteObject(SelectObject(hdcMem, bmMemOld));
   DeleteObject(SelectObject(hdcSave, bmSaveOld));

   // Delete the memory DCs.
   DeleteDC(hdcMem);
   DeleteDC(hdcBack);
   DeleteDC(hdcObject);
   DeleteDC(hdcSave);
   DeleteDC(hdcTemp);
}

void CRecordList::Draw(CDC *pDc, double dlfScaling, BOOL bIcoSizeChange, int nXOffset, int nYOffset)
{	
	// 	mdc.SelectObject(bitmap);
	CGdiObject *pGdiObjectOld = pDc->SelectStockObject(NULL_BRUSH);

	int nBkModeOld = pDc->SetBkMode(TRANSPARENT);
	int nStretchModeOld = pDc->SetStretchBltMode(HALFTONE);
	for (POSITION pos = GetHeadPosition(); pos != NULL;)
	{
		CRecord *pRecord = (CRecord *)GetNext(pos);
		int posx=int(dlfScaling*pRecord->m_Point.x) + nXOffset;
		int posy=int(dlfScaling*pRecord->m_Point.y) + nYOffset;
		int sizex;
		int sizey;
		if(bIcoSizeChange)
		{
			sizex=int(dlfScaling*pRecord->m_Size.cx);
			sizey=int(dlfScaling*pRecord->m_Size.cy);
		}
		else
		{
			sizex=int(pRecord->m_Size.cx);
			sizey=int(pRecord->m_Size.cy);
		}
		//		pDc->StretchBlt(posx, posy,sizex, sizey,&mdc,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);
		CDC mdc; 
		CBitmap bitmap;
		mdc.CreateCompatibleDC(pDc);

// 		bitmap.m_hObject=(HBITMAP)::LoadImage(AfxGetInstanceHandle(),
// 			MAKEINTRESOURCE(IDB_BMP_TIPMSG) ,IMAGE_BITMAP,0,0,
// 			LR_CREATEDIBSECTION);   //加载位图

		BITMAP bmp;
		bitmap.GetBitmap(&bmp);
		mdc.SelectObject(bitmap);
		DrawTransparentBitmap1(pDc->GetSafeHdc(),&mdc,posx, posy,sizex, sizey,0,0,RGB(255,255,255));

		if(pRecord->m_bActive)
		{
			CPen Pen;
			Pen.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
			CPen *pPenOld = pDc->SelectObject(&Pen);
			pDc->Rectangle(posx, posy, posx + sizex, posy + sizey);

			CPen PenInner;
			PenInner.CreatePen(PS_SOLID, 1, RGB(50, 50, 50));
			pDc->SelectObject(&PenInner);
			pDc->Rectangle(posx + 1, posy + 1, posx + sizex - 1, posy + sizey - 1);

			pDc->SelectObject(&pPenOld);
		}
		COLORREF oldColor = pDc->SetTextColor(pRecord->m_Color);
		pDc->TextOut(posx + sizex,posy, pRecord->m_sName);
		pDc->SetTextColor(oldColor);
	}
	pDc->SetStretchBltMode(nStretchModeOld);
	pDc->SetBkMode(nBkModeOld);
	pDc->SelectObject(pGdiObjectOld);
}

//void CRecordList::Draw(CDC *pDc, double dlfScaling)
//{	
//	CDC mdc; 
//	CBitmap bitmap;
//	mdc.CreateCompatibleDC(pDc);
//
//	bitmap.m_hObject=(HBITMAP)::LoadImage(AfxGetInstanceHandle(),
//		MAKEINTRESOURCE(IDB_BITMAP_RECORD) ,IMAGE_BITMAP,0,0,
//		LR_CREATEDIBSECTION);   //加载位图
//
//	BITMAP bmp;
//	bitmap.GetBitmap(&bmp);
//	mdc.SelectObject(bitmap);
//	CGdiObject *pGdiObjectOld = pDc->SelectStockObject(NULL_BRUSH);
//
//	int nBkModeOld = pDc->SetBkMode(TRANSPARENT);
//	pDc->SetStretchBltMode(HALFTONE);
//	for (POSITION pos = GetHeadPosition(); pos != NULL;)
//	{
//		CRecord *pRecord = (CRecord *)GetNext(pos);
//		int posx=int(dlfScaling*pRecord->m_Point.x);
//		int posy=int(dlfScaling*pRecord->m_Point.y);
//		int sizex=int(dlfScaling*pRecord->m_Size.cx);
//		int sizey=int(dlfScaling*pRecord->m_Size.cy);
//		pDc->StretchBlt(posx, posy,sizex, sizey,&mdc,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);
//
//		if(pRecord->m_bActive)
//		{
//			pDc->Rectangle(posx, posy, posx + sizex,posy + sizey);
//		}
//		COLORREF oldColor = pDc->SetTextColor(pRecord->m_Color);
//		pDc->TextOut(posx + sizex,posy, pRecord->m_sName);
//		pDc->SetTextColor(oldColor);
//	}
//
//	pDc->SetBkMode(nBkModeOld);
//
//	pDc->SelectObject(pGdiObjectOld);
//}

//void CRecordList::Draw(CDC *pDc)
//{	
//	CDC mdc; 
//	CBitmap bitmap;
//	mdc.CreateCompatibleDC(pDc);
//
//	bitmap.m_hObject=(HBITMAP)::LoadImage(AfxGetInstanceHandle(),
//		MAKEINTRESOURCE(IDB_BITMAP_RECORD) ,IMAGE_BITMAP,0,0,
//		LR_CREATEDIBSECTION);   //加载位图
//
//	BITMAP bmp;
//	bitmap.GetBitmap(&bmp);
//	mdc.SelectObject(bitmap);
//	CGdiObject *pGdiObjectOld = pDc->SelectStockObject(NULL_BRUSH);
//
//	int nBkModeOld = pDc->SetBkMode(TRANSPARENT);
//
//	for (POSITION pos = GetHeadPosition(); pos != NULL;)
//	{
//		CRecord *pRecord = (CRecord *)GetNext(pos);
//
//		//pDc->StretchBlt(pRecord->m_point.x, pRecord->m_point.y,
//		//	pRecord->m_size.cx, pRecord->m_size.cy,&mdc,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);
//
//		::TransparentBlt(pDc->GetSafeHdc(),pRecord->m_point.x,pRecord->m_point.y,750,50,
//			ImageDC.GetSafeHdc(),0,0,bm.bmWidth,bm.bmHeight,RGB(0xff,0xff,0xff));
//
//
//		if(pRecord->m_active)
//		{
//			pDc->Rectangle(pRecord->m_point.x, pRecord->m_point.y, 
//				pRecord->m_point.x + pRecord->m_size.cx,
//				pRecord->m_point.y + pRecord->m_size.cy);
//		}
//		COLORREF oldColor = pDc->SetTextColor(pRecord->m_color);
//		pDc->TextOut(pRecord->m_point.x + pRecord->m_size.cx, pRecord->m_point.y, pRecord->m_sName);
//		pDc->SetTextColor(oldColor);
//	}
//
//	pDc->SetBkMode(nBkModeOld);
//
//	pDc->SelectObject(pGdiObjectOld);
//}
CRecord *CRecordList::Hittest(const CPoint &point)
{
	for (POSITION pos = GetHeadPosition(); pos != NULL;)
	{
		CRecord *pRecord = (CRecord *)GetNext(pos);

		if(point.x >= pRecord->m_Point.x 
			&& point.x < pRecord->m_Point.x + pRecord->m_Size.cx
			&& point.y >= pRecord->m_Point.y 
			&& point.y < pRecord->m_Point.y + pRecord->m_Size.cy)
		{
			return pRecord;
		}
	}

	return NULL;
}
void CRecordList::Delete()
{
	for (POSITION pos = GetHeadPosition(); pos != NULL;)
	{
		POSITION posBak = pos;
		CRecord *pRecord = (CRecord *)GetNext(pos);
		if(pRecord->m_bActive)
		{
			//if(pRecord == m_pDlg->GetCurRecord())
			//{
				//m_pDlg->EmptyDialog();
			//}
			delete pRecord;
			RemoveAt(posBak);
		}
	}

	if(m_pWnd)
		m_pWnd->Invalidate();
}

int CRecordList::DeleteItem(CRecord *pRecord)
{
	int ret = 0;
	for (POSITION pos = GetHeadPosition(); pos != NULL;)
	{
		POSITION posBak = pos;
		CRecord *pRecordTmp = (CRecord *)GetNext(pos);
		if(pRecordTmp == pRecord)
		{
			delete pRecordTmp;
			RemoveAt(posBak);
			ret++;
			if(m_pWnd)
				m_pWnd->Invalidate(FALSE);
			return ret;
		}
	}
	return ret;
}

void CRecordList::SaveFile(CFile *pFile)
{
	int tagsize=0;
	CString strname;
	int namesize;
	CArchive ar(pFile, CArchive::store);
	MySerial.SaveDataObjectList(ar,_T("KSITEM00"),this);
   MySerial.SaveDataStrList(ar,_T("KDVTEXT0"), &m_listKDVContent);
	namesize=8;
	strname=_T("DENDDEND");
	ar << namesize;
	ar << strname;
}
void CRecordList::LoadFile(CFile *pFile)
{
   m_listKDVContent.RemoveAll();
	int tagsize=0;
	CString strname;
	int namesize;

	CArchive ar(pFile, CArchive::load);
	int nNumber=0;
	ar >> namesize;
	ar >> strname;
	if(strname.GetLength()!=namesize)return;
	while(strname != _T("DENDDEND"))
	{
		if(nNumber > 150)
		{
			return;
		}	
		if (strname==_T("KSITEM00"))
		{
			EmptyList();
			int dateSize;
			ar >> tagsize;
			ar >> dateSize;

			for(int i=0; i<dateSize; i++)
			{
				CObject *pObject=new CRecord;
				pObject->Serialize(ar);
				AddTail((CObject *)pObject);
			}
		}
      else if (strname==_T("KDVTEXT0"))
      {
         int nDataSize;
         ar >> tagsize;
         ar >> nDataSize;

         for(int i=0; i<nDataSize; i++)
         {
            CString str;
            ar >> str;
            m_listKDVContent.AddTail(str);
         }
      }
		else
		{
			ar >> tagsize;
			ar.Flush();
			char *buf = new char[tagsize];
			ar.GetFile()->Read(buf,tagsize);
			delete[] buf;
		}
		strname=_T("");
		ar >> namesize;
		ar >> strname;
		if(strname.GetLength()!=namesize)return;
		nNumber++;
	}

	if(m_pWnd)
		m_pWnd->Invalidate();
}

void CRecordList::EmptyList()
{
	for (POSITION pos = GetHeadPosition(); pos != NULL;)
	{
		CRecord *pRecord = (CRecord *)GetNext(pos);
		delete pRecord;
		pRecord = 0;
	}

	RemoveAll();
}

void CRecordList::NoActiveAll()
{
	for (POSITION pos = GetHeadPosition(); pos != NULL;)
	{
		CRecord *pRecord = (CRecord *)GetNext(pos);
		pRecord->m_bActive = false;
	}
}

void CRecordList::Copy(CRecordList *pRecordList)
{
	if(this == pRecordList)
		return;
	EmptyList();
	for (POSITION pos = pRecordList->GetHeadPosition(); pos != NULL;)
	{
		CRecord *pRecord = (CRecord *)GetNext(pos);
		CRecord *pRecordNew = new CRecord;
		pRecordNew->Copy(pRecord);
		AddTail(pRecordNew);
	}
}

CRecordList::~CRecordList()
{
	EmptyList();
	/*if(m_pDlg)
	{
	delete m_pDlg;
	m_pDlg = 0;
	}*/
}

void CRecordList::SendMovePoint(const CPoint &Point)
{
	if(m_pLastRecord)
	{
		m_pLastRecord->m_Point.x = Point.x - m_nOffsetX;
		m_pLastRecord->m_Point.y = Point.y - m_nOffsetY;
		if(m_pWnd)
			m_pWnd->Invalidate(FALSE);
	}
}

CRecord *CRecordList::SendPoint(const CPoint &Point, BOOL bAddNew)
{
	CRecord *pRecord = Hittest(Point);
	BOOL isNew = FALSE;
	//CRecord tempNewRecord;
	if (pRecord == NULL && bAddNew)
	{
		m_pLastRecord = NULL;
		if(!bAddNew)
		{	
			return NULL;
		}

		NoActiveAll();

		isNew = TRUE;
		pRecord = new CRecord;
		pRecord->m_Point = Point;
		pRecord->m_Size = m_DrawSize;	
		pRecord->m_bActive = true;
		AddTail(pRecord);
	}
	else if (pRecord != NULL)
	{
		m_pLastRecord = pRecord;
		m_nOffsetX = Point.x - pRecord->m_Point.x;
		m_nOffsetY = Point.y - pRecord->m_Point.y;
		if(GetKeyState(VK_CONTROL)< 0)
			pRecord->m_bActive = !pRecord->m_bActive;
		else
		{
			NoActiveAll();
			pRecord->m_bActive = true;
		}
	}

	if(m_pWnd)
		m_pWnd->Invalidate(FALSE);

	//SetRecordToDlg(pRecord, TRUE);
	return pRecord;
}

//void CRecordList::SetRecordToDlg(CRecord *pRecord, BOOL bPlayImmediately)
//{
//	if(!m_pDlg)
//	{
//		m_pDlg = new CMyRecordDlg;
//		m_pDlg->Create(CMyRecordDlg::IDD);
//	}
//
//	m_pDlg->SetRecord(pRecord, this, m_pWnd, bPlayImmediately);
//
//	m_pDlg->ShowWindow(SW_SHOWNORMAL);
//}

void CRecordList::SetWnd(CWnd *p)
{
	m_pWnd = p;
}

CRecord *CRecordList::JumpToNextPoint(CPoint *pPoint)
{
	if (NULL == m_pLastJumpRecord)
	{
		if(GetCount() > 0)
		{
			m_pLastJumpRecord = (CRecord *)(GetHead());
			if(pPoint)
				*pPoint = m_pLastJumpRecord->m_Point;
			NoActiveAll();
			m_pLastJumpRecord->m_bActive = true;
			//SetRecordToDlg(m_pLastJumpRecord, FALSE);
			return m_pLastJumpRecord;
		}
		else
		{
			return NULL;
		}
	}
	else
	{
		//m_pLastJumpRecord
		int count = GetCount();
		if(count > 0)
		{
			int i;
			for (i = 0; i < count; i++)
			{
				CRecord *pRecord = (CRecord *)GetAt(FindIndex(i));
				if(pRecord == m_pLastJumpRecord)
				{
					break;
				}
			}
			if (i != count) //找到了
				i++;
			i %= count;
			m_pLastJumpRecord = (CRecord *)GetAt(FindIndex(i));
			if(pPoint)
				*pPoint = m_pLastJumpRecord->m_Point;
			NoActiveAll();
			m_pLastJumpRecord->m_bActive = true;
			//SetRecordToDlg(m_pLastJumpRecord, FALSE);
			return m_pLastJumpRecord;
		}
		else
		{
			return NULL;
		}
	}
}

CSize CRecordList::GetDrawSize()
{
	return m_DrawSize;
}