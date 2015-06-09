// Utils.cpp: implementation of the CUtils class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Utils.h"
#include "Dib.h"
#include "CameraPicture.h"
#include "BaseDraw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUtils::CUtils()
{
	
}

CUtils::~CUtils()
{
	
}

bool CUtils::SelectPic(const CString& PicturesFolder, CStringList& Files,
					   CString& ResultFile)
{
	if (Files.IsEmpty()) {
		CFileFind Finder;
		CString Filename;
		CString Path = PicturesFolder + "\\*.bmp";
		BOOL bMoreFiles = Finder.FindFile(Path);
		while (bMoreFiles) {
			bMoreFiles = Finder.FindNextFile();
			CString FullFilePath = Finder.GetFilePath();
			Files.AddTail(FullFilePath);
		}
	}
	
	if (! Files.IsEmpty()) {
		ResultFile = Files.RemoveHead();
		Files.AddTail(ResultFile);
		return true;
	} else {
		ResultFile.Empty();
		return false;
	}
}

void CUtils::CalcColorChage(CCameraPicture* pCameraPicture,
							long& RAll, long& GAll, long& BAll)
{
	long Count(0);
	CDib* pCameraDib = pCameraPicture->GetCurrCameraDib();
	CDib* pPrevCameraDib = pCameraPicture->GetPrevCameraDib();
	CSize CameraSize = pCameraDib->GetSize();
	
	for (int x=0; x < CameraSize.cx; x+=CameraResFactor)
	{
		for (int y=0; y < CameraSize.cy; y+=CameraResFactor)
		{	
			COLORREF c1 = pCameraDib->GetPixel(x,y);
			COLORREF c0 = pPrevCameraDib->GetPixel(x,y);
			
			long Diff = c1 - c0;
			long R = GetRValue(Diff);
			long G = GetGValue(Diff);
			long B = GetBValue(Diff);
			
			if (R == G && R == B && (R < ColorDiffThreshold || R > 255 - ColorDiffThreshold)) {
			} else {
				RAll += GetRValue(c1);
				GAll += GetGValue(c1);
				BAll += GetBValue(c1);
				Count++;
			} 
		}
	}
	if (Count > 0) {
		RAll /= Count;
		GAll /= Count;
		BAll /= Count;
		
		const int Inc = 40;
		const int Div = 2;
		
		if (RAll > GAll && RAll > BAll) {
			GAll /= Div;
			BAll /= Div;
			RAll = min(RAll + Inc, 255);
		} else if (GAll > RAll && GAll > BAll) {
			RAll /= Div;
			BAll /= Div;
			GAll = min(GAll + Inc, 255);
		} else {
			RAll /= Div;
			GAll /= Div;
			BAll = min(BAll + Inc, 255);
		}
	}
}


/* HLSMAX BEST IF DIVISIBLE BY 6 */ 
/* RGBMAX, HLSMAX must each fit in a byte. */ 

/* Hue is undefined if Saturation is 0 (grey-scale) */ 
/* This value determines where the Hue scrollbar is */ 
/* initially set for achromatic colors */ 
#define UNDEFINED ((WORD)(HLSMAX*2/3))
#define  HLSMAX   240 /* H,L, and S vary over 0-HLSMAX */ 
#define  RGBMAX   255   /* R,G, and B vary over 0-RGBMAX */ 

void CUtils::RGBtoHLS(DWORD lRGBColor, WORD& H, WORD& L, WORD& S)
{
	WORD R,G,B;          /* input RGB values */ 
	BYTE cMax,cMin;      /* max and min RGB values */ 
	WORD  Rdelta,Gdelta,Bdelta; /* intermediate value: % of spread from max */ 
	/* get R, G, and B out of DWORD */ 
	R = GetRValue(lRGBColor);
	G = GetGValue(lRGBColor);
	B = GetBValue(lRGBColor);
	
	/* calculate lightness */ 
	cMax = (BYTE)max( max(R,G), B);
	cMin = (BYTE)min( min(R,G), B);
	L = ( ((cMax+cMin)*HLSMAX) + RGBMAX )/(2*RGBMAX);
	
	if (cMax == cMin) {           /* r=g=b --> achromatic case */ 
		S = 0;                     /* saturation */ 
		H = UNDEFINED;             /* hue */ 
	}
	else {                        /* chromatic case */ 
		 /* saturation */ 
		 if (L <= (HLSMAX/2))
			 S = ( ((cMax-cMin)*HLSMAX) + ((cMax+cMin)/2) ) / (cMax+cMin);
		 else
			 S = ( ((cMax-cMin)*HLSMAX) + ((2*RGBMAX-cMax-cMin)/2) )
			 / (2*RGBMAX-cMax-cMin);
		 
		 /* hue */ 
		 Rdelta = ( ((cMax-R)*(HLSMAX/6)) + ((cMax-cMin)/2) ) / (cMax-cMin);
		 Gdelta = ( ((cMax-G)*(HLSMAX/6)) + ((cMax-cMin)/2) ) / (cMax-cMin);
		 Bdelta = ( ((cMax-B)*(HLSMAX/6)) + ((cMax-cMin)/2) ) / (cMax-cMin);
		 
		 if (R == cMax)
			 H = Bdelta - Gdelta;
		 else if (G == cMax)
			 H = (HLSMAX/3) + Rdelta - Bdelta;
		 else /* B == cMax */ 
			 H = ((2*HLSMAX)/3) + Gdelta - Rdelta;
		 
		 if (H < 0)
			 H += HLSMAX;
		 if (H > HLSMAX)
			 H -= HLSMAX;
	}
}

/* utility routine for HLStoRGB */ 
WORD CUtils::HueToRGB(WORD n1, WORD n2, WORD hue)
{
	/* range check: note values passed add/subtract thirds of range */ 
	if (hue < 0)
		hue += HLSMAX;
	
	if (hue > HLSMAX)
		hue -= HLSMAX;
	
	/* return r,g, or b value from this tridrant */ 
	if (hue < (HLSMAX/6))
		return ( n1 + (((n2-n1)*hue+(HLSMAX/12))/(HLSMAX/6)) );
	if (hue < (HLSMAX/2))
		return ( n2 );
	if (hue < ((HLSMAX*2)/3))
		return ( n1 +    (((n2-n1)*(((HLSMAX*2)/3)-hue)+(HLSMAX/12))/(HLSMAX/6))
		);
	else
		return ( n1 );
}


DWORD CUtils::HLStoRGB(WORD hue, WORD lum, WORD sat)
{
	WORD R,G,B;                /* RGB component values */ 
	WORD  Magic1,Magic2;       /* calculated magic numbers (really!) */ 
	
	if (sat == 0) {            /* achromatic case */ 
		R=G=B=(lum*RGBMAX)/HLSMAX;
		if (hue != UNDEFINED) {
            /* ERROR */ 
		}
	}
	else  {                    /* chromatic case */ 
		/* set up magic numbers */ 
		if (lum <= (HLSMAX/2))
            Magic2 = (lum*(HLSMAX + sat) + (HLSMAX/2))/HLSMAX;
		else
            Magic2 = lum + sat - ((lum*sat) + (HLSMAX/2))/HLSMAX;
		Magic1 = 2*lum-Magic2;
		
		/* get RGB, change units from HLSMAX to RGBMAX */ 
		R = (HueToRGB(Magic1,Magic2,hue+(HLSMAX/3))*RGBMAX +
			(HLSMAX/2))/HLSMAX;
		G = (HueToRGB(Magic1,Magic2,hue)*RGBMAX + (HLSMAX/2)) / HLSMAX;
		B = (HueToRGB(Magic1,Magic2,hue-(HLSMAX/3))*RGBMAX +
			(HLSMAX/2))/HLSMAX;
	}
	return(RGB(R,G,B));
}

PBITMAPINFO CUtils::CreateBitmapInfoStruct(HBITMAP hBmp)
{ 
    BITMAP bmp; 
    PBITMAPINFO pbmi; 
    WORD    cClrBits; 
	
    // Retrieve the bitmap's color format, width, and height. 
    if (!GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bmp)) {
        AfxMessageBox("GetObject"); 
		return NULL;
	}
	
    // Convert the color format to a count of bits. 
    cClrBits = (WORD)(bmp.bmPlanes * bmp.bmBitsPixel); 
    if (cClrBits == 1) 
        cClrBits = 1; 
    else if (cClrBits <= 4) 
        cClrBits = 4; 
    else if (cClrBits <= 8) 
        cClrBits = 8; 
    else if (cClrBits <= 16) 
        cClrBits = 16; 
    else if (cClrBits <= 24) 
        cClrBits = 24; 
    else cClrBits = 32; 
	
    // Allocate memory for the BITMAPINFO structure. (This structure 
    // contains a BITMAPINFOHEADER structure and an array of RGBQUAD 
    // data structures.) 
	
	if (cClrBits != 24) 
		pbmi = (PBITMAPINFO) LocalAlloc(LPTR, 
		sizeof(BITMAPINFOHEADER) + 
		sizeof(RGBQUAD) * (1<< cClrBits)); 
	
	// There is no RGBQUAD array for the 24-bit-per-pixel format. 
	
	else 
		pbmi = (PBITMAPINFO) LocalAlloc(LPTR, 
		sizeof(BITMAPINFOHEADER)); 
	
    // Initialize the fields in the BITMAPINFO structure. 
	
    pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER); 
    pbmi->bmiHeader.biWidth = bmp.bmWidth; 
    pbmi->bmiHeader.biHeight = bmp.bmHeight; 
    pbmi->bmiHeader.biPlanes = bmp.bmPlanes; 
    pbmi->bmiHeader.biBitCount = bmp.bmBitsPixel; 
    if (cClrBits < 24) 
        pbmi->bmiHeader.biClrUsed = (1<<cClrBits); 
	
    // If the bitmap is not compressed, set the BI_RGB flag. 
    pbmi->bmiHeader.biCompression = BI_RGB; 
	
    // Compute the number of bytes in the array of color 
    // indices and store the result in biSizeImage. 
    // For Windows NT/2000, the width must be DWORD aligned unless 
    // the bitmap is RLE compressed. This example shows this. 
    // For Windows 95/98, the width must be WORD aligned unless the 
    // bitmap is RLE compressed.
    pbmi->bmiHeader.biSizeImage = ((pbmi->bmiHeader.biWidth * cClrBits +31) & ~31) /8
		* pbmi->bmiHeader.biHeight; 
    // Set biClrImportant to 0, indicating that all of the 
    // device colors are important. 
	pbmi->bmiHeader.biClrImportant = 0; 
	return pbmi; 
} 

void CUtils::CreateBMPFile(LPCTSTR pszFile, HBITMAP hBMP, HDC hDC) 
{ 
    PBITMAPINFOHEADER pbih;     // bitmap info-header 
    LPBYTE lpBits;              // memory pointer 
    BYTE *hp;                   // byte pointer 
	
    PBITMAPINFO pbi = CreateBitmapInfoStruct(hBMP);
	if (! pbi) {
		return;
	}
	pbih = &pbi->bmiHeader;
    lpBits = (LPBYTE) GlobalAlloc(GMEM_FIXED, pbih->biSizeImage);
	
    if (!lpBits) { 
		AfxMessageBox("GlobalAlloc"); 
		return;
	}
	
    // Retrieve the color table (RGBQUAD array) and the bits 
    // (array of palette indices) from the DIB. 
    if (!GetDIBits(hDC, hBMP, 0, (WORD) pbih->biHeight, lpBits, pbi, 
        DIB_RGB_COLORS)) 
    {
        AfxMessageBox("GetDIBits"); 
		return;
    }
	
    // Create the .BMP file. 
    HANDLE hf = CreateFile(pszFile, 
		GENERIC_READ | GENERIC_WRITE, 
		(DWORD) 0, 
		NULL, 
		CREATE_ALWAYS, 
		FILE_ATTRIBUTE_NORMAL, 
		(HANDLE) NULL); 
    if (hf == INVALID_HANDLE_VALUE)  {
        AfxMessageBox("CreateFile"); 
		return;
	}
    BITMAPFILEHEADER hdr;       // bitmap file-header 
    hdr.bfType = 0x4d42;        // 0x42 = "B" 0x4d = "M" 
    // Compute the size of the entire file. 
    hdr.bfSize = (DWORD) (sizeof(BITMAPFILEHEADER) + 
		pbih->biSize + pbih->biClrUsed 
		* sizeof(RGBQUAD) + pbih->biSizeImage); 
    hdr.bfReserved1 = 0; 
    hdr.bfReserved2 = 0; 
	
    // Compute the offset to the array of color indices. 
    hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) + 
		pbih->biSize + pbih->biClrUsed 
		* sizeof (RGBQUAD); 
	
    // Copy the BITMAPFILEHEADER into the .BMP file. 
    DWORD dwTmp; 
    if (!WriteFile(hf, (LPVOID) &hdr, sizeof(BITMAPFILEHEADER), 
        (LPDWORD) &dwTmp,  NULL)) 
    {
		AfxMessageBox("WriteFile"); 
		return;
    }
	
    // Copy the BITMAPINFOHEADER and RGBQUAD array into the file. 
    if (!WriteFile(hf, (LPVOID) pbih, sizeof(BITMAPINFOHEADER) 
		+ pbih->biClrUsed * sizeof (RGBQUAD), 
		(LPDWORD) &dwTmp, ( NULL))) 
	{
        AfxMessageBox("WriteFile"); 
		return;
	}
    // Copy the array of color indices into the .BMP file. 
    DWORD cb = pbih->biSizeImage; // incremental count of bytes 
    hp = lpBits; 
    if (!WriteFile(hf, (LPSTR) hp, (int) cb, (LPDWORD) &dwTmp,NULL)) 
	{
		AfxMessageBox("WriteFile"); 
		return;
	}
	
    // Close the .BMP file. 
	if (!CloseHandle(hf)) 
	{
		AfxMessageBox("CloseHandle"); 
		return;
	}
    // Free memory. 
    GlobalFree((HGLOBAL)lpBits);
}
