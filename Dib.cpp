// Dib.cpp: implementation of the CDib class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Dib.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CMap<char*, char*, long, long>CDib::m_FreeAllocations;
CMap<char*, char*, long, long>CDib::m_BusyAllocations;
////////////////////////////////////////////////////////////////
// 1996 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// CDib - Device Independent Bitmap.
// This implementation uses the Video for Windows DrawDib API to draw.
//
#include "StdAfx.h"
#include "Dib.h"


CDib::CDib()
{
	m_pbmih = NULL;
	m_hdd = NULL;
	m_Len = 0;
}

CDib::CDib(const CDib& SrcDib)
{
	*this = SrcDib;
}

CDib& CDib::operator=(const CDib& SrcDib)
{
	DeleteObject();

	m_Len = SrcDib.m_Len;
	m_pbmih = (BITMAPINFOHEADER*)GetMemory(m_Len);
	CopyMemory(m_pbmih, SrcDib.m_pbmih, m_Len);
	m_hdd = NULL;

	// Set bits
	m_pBits = (LPBYTE)m_pbmih + m_pbmih->biSize 
		+ GetNumPaletteColors()*sizeof(RGBQUAD); 

	return *this;
}


CDib::~CDib()
{
	DeleteObject();
}

//////////////////

char* CDib::GetMemory(long size)
{
	POSITION pos = m_FreeAllocations.GetStartPosition();
	char* _ptr; long _size;
	while (pos) {
		m_FreeAllocations.GetNextAssoc(pos, _ptr, _size);
		if (size <= _size) {
			m_FreeAllocations.RemoveKey(_ptr);
			m_BusyAllocations.SetAt(_ptr, size);
			return _ptr;
		}
	}
	_ptr = new char[size];
	m_BusyAllocations.SetAt(_ptr, size);
	return _ptr;
}

void CDib::ReleaseMemory(char* ptr)
{
	long size;
	VERIFY(m_BusyAllocations.Lookup(ptr, size));
	m_BusyAllocations.RemoveKey(ptr);
	m_FreeAllocations.SetAt(ptr, size);
}

void CDib::ReleaseAllMemory()
{
	char* _ptr; long _size;
	POSITION pos = m_FreeAllocations.GetStartPosition();
	while (pos) {
		m_FreeAllocations.GetNextAssoc(pos, _ptr, _size);
		delete []_ptr;
	}
	pos = m_BusyAllocations.GetStartPosition();
	while (pos) {
		m_FreeAllocations.GetNextAssoc(pos, _ptr, _size);
		delete []_ptr;
	}
}
//////////////////
// Common function to delete stuff
//
void CDib::DeleteObject()
{
	if (m_hdd) {
		DrawDibClose(m_hdd);
		m_hdd = NULL;
	}
	m_Len = 0;
	if (m_pbmih) {
		ReleaseMemory((char*)m_pbmih);
		m_pbmih = NULL;
	}
	m_pBits = NULL;
}

//////////////////
// Get number of palette colors
// 
UINT CDib::GetNumPaletteColors()
{
	// Calculate # entries in color table:
	// if biClrUsed is not specified, then use:
	//    (2,16,256)  for (1,4,8)-bit bitmaps;
	//    0           for 24, 32-bit bitmaps (no color table)
	// 
	UINT nColors=m_pbmih->biClrUsed;
	if (nColors==0 && m_pbmih->biBitCount<=8)
		nColors = 1<<m_pbmih->biBitCount;
	return nColors;
}

//////////////////
// Get ptr to actual bits.
// 
LPBYTE CDib::GetBits() const
{
	return m_pBits; 
}

// First two bytes of bitmap file should be "BM"
const BITMAP_TYPE =  (WORD)('M' << 8) | 'B';

////////////////////////////////////////////////////////////////
// Draw routine for a DIB on caller's DC. Like above, but
// caller can specify source and destination rectangles.
// Use Video for Windows DrawDIB API to do the work.
//
BOOL CDib::Draw(CDC& dc, const CRect* rcDst, const CRect* rcSrc)
{
	if (!m_pbmih)
		return FALSE;
	
	if (!m_hdd)
		VERIFY(m_hdd = DrawDibOpen());
	
	CRect rc;
	if (!rcSrc) {
		// if no source rect, use whole bitmap
		rc.SetRect(0, 0, m_pbmih->biWidth, m_pbmih->biHeight);
		rcSrc=&rc;
	}
	if (!rcDst)
		// if no destination rect, use source
		rcDst=rcSrc;
	
	// This is as easy as it gets in Windows.
	return DrawDibDraw(m_hdd, dc,
		rcDst->left, rcDst->top, rcDst->Width(), rcDst->Height(),
		m_pbmih, GetBits(), 
		rcSrc->left, rcSrc->top, rcSrc->Width(), rcSrc->Height(), 0);
}

BOOL CDib::LoadFromClipboard()
{
	DeleteObject();
	
	if ( !::OpenClipboard(NULL) )
	{
		AfxMessageBox("Cannot open the Clipboard.", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	
	bool ret = false;
	if ( ::IsClipboardFormatAvailable(CF_DIB) )
	{
		// Unicode to text conversion
		HANDLE hClip = ::GetClipboardData(CF_DIB);
		if ( hClip != NULL )
		{
			HANDLE hDib = (HANDLE)GlobalLock(hClip);
			if ( hDib != NULL )
			{
				BITMAPINFOHEADER* hdr = (BITMAPINFOHEADER*)hDib;
				m_Len = hdr->biSizeImage + 40;
				m_pbmih = (BITMAPINFOHEADER*)GetMemory(m_Len);
				CopyMemory(m_pbmih, hdr, m_Len);
				m_hdd = NULL;

				// Set bits
				m_pBits = (LPBYTE)m_pbmih + m_pbmih->biSize 
					+ GetNumPaletteColors()*sizeof(RGBQUAD); 

				::GlobalUnlock(hClip);
				ret = true;
			}
		}
	}
	
	CloseClipboard();
	return ret;
}

BOOL CDib::Load(LPCTSTR lpszPathName)
{
	DeleteObject();

	CFile file(lpszPathName, CFile::modeRead);

	BITMAPFILEHEADER hdr;
	DWORD len = file.Read(&hdr, sizeof(hdr));
	if ((len!=sizeof(hdr)) || 
		(hdr.bfType!=BITMAP_TYPE)) {
		TRACE0("***CDib: bad BITMAPFILEHEADER\n");
		return FALSE;
	}
	
	m_Len = file.GetLength() - len;
	m_pbmih = (BITMAPINFOHEADER*)GetMemory(m_Len);
	file.Read(m_pbmih, m_Len);

	// Set bits
	m_pBits = (LPBYTE)m_pbmih + m_pbmih->biSize 
		+ GetNumPaletteColors()*sizeof(RGBQUAD); 

	return true;
}

bool CDib::IsInitialized()
{
	return m_pbmih != NULL;
}

long CDib::GetPosInArray(int x, int y) const
{
	ASSERT(x < m_pbmih->biWidth && y < m_pbmih->biHeight);
	// for now handle only
	ASSERT(m_pbmih->biBitCount >= 8);
	long BytesPerColor = m_pbmih->biBitCount / 8;

	long NewPos = 0;
	if (m_pbmih->biHeight > 0) {
		// origin in lower left corner
		y = m_pbmih->biHeight - y;
	} else {
		// origin in upper left corner
	}
	if (y > 0) {
		NewPos = ((((m_pbmih->biWidth * m_pbmih->biBitCount) + 31) & ~31) >> 3) * (y-1);
	}
	NewPos += x * BytesPerColor;

	return NewPos;
}

void CDib::SetRect(int x0, int y0, int x1, int y1, COLORREF c)
{
	BYTE r = GetRValue(c);
	BYTE g = GetGValue(c);
	BYTE b = GetBValue(c);

	LPBYTE pBits = GetBits();

	for (int i = x0; i < x1; i++) {
		for (int j = y0; j < y1; j++) {
			long NewPos = GetPosInArray(i,j);

			pBits[NewPos] = b;
			pBits[NewPos+1] = g;
			pBits[NewPos+2] = r;
		}
	}
}

void CDib::SetPixel(int x, int y, COLORREF c)
{
	long NewPos = GetPosInArray(x,y);

	BYTE r = GetRValue(c);
	BYTE g = GetGValue(c);
	BYTE b = GetBValue(c);

	LPBYTE pBits = GetBits();
	pBits[NewPos] = b;
	pBits[NewPos+1] = g;
	pBits[NewPos+2] = r;
}

COLORREF CDib::GetPixel(int x, int y) const
{
	const LPBYTE pBits = GetBits();
	long NewPos = GetPosInArray(x,y);
	return RGB(pBits[NewPos+2], pBits[NewPos+1], pBits[NewPos]);
}

CSize CDib::GetSize() const
{
	return CSize(m_pbmih->biWidth, m_pbmih->biHeight);
}

