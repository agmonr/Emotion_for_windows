// Utils.h: interface for the CUtils class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UTILS_H__EAAFD59E_09BE_4991_95F6_34FB9B3B8C39__INCLUDED_)
#define AFX_UTILS_H__EAAFD59E_09BE_4991_95F6_34FB9B3B8C39__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCameraPicture;

class CUtils  
{
public:
	CUtils();
	virtual ~CUtils();
	
	static bool SelectPic(const CString& PicturesFolder, CStringList& Files,
							 CString& ResultFile);
	
	static void CalcColorChage(CCameraPicture* pCameraPicture,
		long& RAll, long& GAll, long& BAll);
	
	static void RGBtoHLS(DWORD lRGBColor, WORD& H, WORD& L, WORD& S);
	static WORD HueToRGB(WORD n1, WORD n2, WORD hue);
	static DWORD HLStoRGB(WORD hue, WORD lum, WORD sat);

	static PBITMAPINFO CreateBitmapInfoStruct(HBITMAP hBmp);
	static void CreateBMPFile(LPCTSTR pszFile, HBITMAP hBMP, HDC hDC);

};

#endif // !defined(AFX_UTILS_H__EAAFD59E_09BE_4991_95F6_34FB9B3B8C39__INCLUDED_)
