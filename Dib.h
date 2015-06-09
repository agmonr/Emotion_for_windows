// Dib.h: interface for the CDib class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIB_H__8CF66CF5_E926_4614_A806_E9C177D85817__INCLUDED_)
#define AFX_DIB_H__8CF66CF5_E926_4614_A806_E9C177D85817__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDib  
{
public:
	CDib();
	virtual ~CDib();

    BOOL Load(LPCTSTR szPathName);
	BOOL LoadFromClipboard();
    
	BOOL Draw(CDC* pDC);

	CDib(const CDib& SrcDib);
	CDib& operator=(const CDib& SrcDib);

	void DeleteObject();
	UINT GetNumPaletteColors();
	LPBYTE GetBits() const;
	BOOL Draw(CDC& dc, const CRect* rcDst, const CRect* rcSrc);

	void SetPixel(int x, int y, COLORREF c);
	void SetRect(int x0, int y0, int x1, int y1, COLORREF c);
	COLORREF GetPixel(int x, int y) const;
	CSize GetSize() const;
	long GetPosInArray(int x, int y) const;

	bool IsInitialized();

	// memory operations
	static void ReleaseAllMemory();
	static void ReleaseMemory(char* ptr);
	static char* GetMemory(long size);

	
	DWORD m_Len;
	BITMAPINFOHEADER* m_pbmih;
	HDRAWDIB m_hdd;
	LPBYTE m_pBits;
	// memory pool
	static CMap<char*, char*, long, long> m_FreeAllocations, m_BusyAllocations;
};

#endif // !defined(AFX_DIB_H__8CF66CF5_E926_4614_A806_E9C177D85817__INCLUDED_)
